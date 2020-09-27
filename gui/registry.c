/*
	registry.c

	Virtual Floppy Drive for Windows
	GUI Control Panel
	Registry handling functions

	Copyright (C) 2003-2005 Ken Kato
*/

#ifdef __cplusplus
#pragma message( __FILE__ ": Compiled as C++ for testing purpose.\n" )
#endif	// __cplusplus

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

#include "vfdwin.h"
#include "registry.h"

//
//	local functions
//
static DWORD ReadRegStrValue(LPCTSTR subkey, LPCTSTR value, LPTSTR buf);
static DWORD DeleteRegistryTree(HKEY hKey, LPCTSTR subkey);
static DWORD CopyRegistryTree(HKEY hKeyTo, HKEY hKeyFrom);

//
//	Get associated program name for extension
//
DWORD GetAssociatedProgram(LPCTSTR ext, LPTSTR prog)
{
	char	subkey[MAX_PATH];
	char	buf[MAX_PATH];
	DWORD	ret;
	char	*top, *tail = NULL;

	*prog = '\0';

	//	Read [HKEY_CLASSES_ROOT\.ext] -- file type
	ret = ReadRegStrValue(ext, NULL, subkey);

	if (ret != ERROR_SUCCESS) {
		return ret == ERROR_FILE_NOT_FOUND ? ERROR_SUCCESS : ret;
	}

	//	Read [HKEY_CLASSES_ROOT\<file type>\shell] -- default verb

	strcat(subkey, "\\shell");

	ret = ReadRegStrValue(subkey, NULL, buf);

	if (ret != ERROR_SUCCESS && ret != ERROR_FILE_NOT_FOUND) {
		return ret;
	}

	//	Read [HKEY_CLASSES_ROOT\<file type>\shell\<verb>\command] -- command line

	sprintf(subkey + strlen(subkey), "\\%s\\command", buf[0] ? buf : "open");

	if ((ret = ReadRegStrValue(subkey, NULL, buf)) != ERROR_SUCCESS) {
		return ret == ERROR_FILE_NOT_FOUND ? ERROR_SUCCESS : ret;
	}

	//	Extract program name from string

	if (buf[0] == '\"') {
		// program path is quoted
		tail = &buf[1];

		// search trailing quote
		while (*tail != '\"' && *tail != '\0') {
			tail++;
		}

		// find top of program file name
		top = tail;

		while (top > buf && *(top - 1) != '\\' && *(top - 1) != '\"') {
			top--;
		}
	}
	else {
		BOOL found = FALSE;

		// program path is not quoted
		tail = buf;

		// first search for extension

		while (*tail) {

			// search blank or end of string
			while (*tail != '\0' && *tail != ' ') {
				tail++;
			}

			if (tail - buf >= 4) {
				if (!strnicmp(tail - 4, ".exe", 4) ||
					!strnicmp(tail - 4, ".cmd", 4) ||
					!strnicmp(tail - 4, ".bat", 4) ||
					!strnicmp(tail - 4, ".com", 4) ||
					!strnicmp(tail - 4, ".vbs", 4) ||
					!strnicmp(tail - 4, ".vbe", 4) ||
					!strnicmp(tail - 4, ".jse", 4) ||
					!strnicmp(tail - 4, ".wsf", 4) ||
					!strnicmp(tail - 4, ".wsh", 4))
				{
					found = TRUE;
					break;
				}
			}
			else if (tail - buf >= 3) {
				if (!strnicmp(tail - 3, ".js",	3)) {
					found = TRUE;
					break;
				}
			}

			tail++;
		}

		//	extension was not found in the text, so switch to simpler way

		if (!found) {
			tail = buf;

			// search first blank

			while (*tail != ' ' && *tail != '\0') {
				tail++;
			}
		}

		// find top of the program file name

		top = tail;

		while (top > buf && *(top - 1) != '\\') {
			top --;
		}
	}

	//	copy program file name to output buffer
	*tail = '\0';
	strcpy(prog, top);

	return ERROR_SUCCESS;
}

//
//	read a string value from a registry key
//
DWORD ReadRegStrValue(LPCTSTR subkey, LPCTSTR value, LPTSTR buf)
{
	HKEY hKey;
	DWORD size = MAX_PATH;
	DWORD type;
	LONG ret;

	*buf = '\0';

	ret = RegOpenKeyEx(HKEY_CLASSES_ROOT, subkey, 0, KEY_QUERY_VALUE, &hKey);

	if (ret != ERROR_SUCCESS) {
		if (ret != ERROR_FILE_NOT_FOUND) {
			VFDTRACE(0, (
				"ReadRegStrValue : RegOpenKeyEx(\"%s\")\n",
				subkey));
		}

		return ret;
	}

	ret = RegQueryValueEx(hKey, value, NULL, &type, (LPBYTE)buf, &size);

	RegCloseKey(hKey);

	if (ret == ERROR_SUCCESS) {
		if (type == REG_SZ || type == REG_MULTI_SZ || type == REG_EXPAND_SZ) {
			// ensure that the string is properly terminated

			if (*(buf + size)) {
				*(buf + size++) = '\0';
			}
			return ERROR_SUCCESS;
		}
		else {
			VFDTRACE(0, (
				"ReadRegStrValue : RegQueryValueEx(\"[%s] %s\") returned non-text data\n",
				subkey, value ? value : "@"));

			return ERROR_INVALID_DATA;
		}
	}
	else if (ret != ERROR_FILE_NOT_FOUND) {
		VFDTRACE(0, (
			"ReadRegStrValue : RegQueryValueEx(\"[%s] %s\")\n",
			subkey, value ? value : "@"));
	}

	return ret;
}

//
//	remove current association and restore
//	the backed up association if present
//
DWORD RestoreAssociation(LPCTSTR ext, LPCTSTR backup_value)
{
	TCHAR current[MAX_PATH], backup[MAX_PATH];
	DWORD size;
	HKEY hKey;
	LONG ret;

	//
	//	Get current filetype and backup filetype
	//

	ret = RegOpenKeyEx(HKEY_CLASSES_ROOT, ext, 0, KEY_ALL_ACCESS, &hKey);

	if (ret != ERROR_SUCCESS) {
		VFDTRACE(0, (
			"RemoveAssociation : RegOpenKeyEx(\"HKCR\\%s\")\n",
			ext));

		return ret;
	}

	// read current filetype

	size = sizeof(current);

	ret = RegQueryValueEx(hKey, NULL, NULL, NULL, (LPBYTE)current, &size);

	if (ret == ERROR_FILE_NOT_FOUND) {
		size = 0;
	}
	else if (ret != ERROR_SUCCESS) {
		VFDTRACE(0, (
			"RemoveAssociation : RegQueryValueEx(\"[HKCR\\%s] @\")\n",
			ext));

		RegCloseKey(hKey);
		return ret;
	}

	// make sure that the string is terminated

	if (current[size]) {
		current[size] = '\0';
	}

	// read backed up filetype

	if (backup_value && *backup_value) {
		size = sizeof(backup);

		ret = RegQueryValueEx(hKey, backup_value, NULL, NULL, (LPBYTE)backup, &size);

		if (ret == ERROR_FILE_NOT_FOUND) {
			size = 0;
		}
		else if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"RemoveAssociation : RegQueryValueEx(\"[HKCR\\%s] %s\")\n",
				ext, backup_value));

			RegCloseKey(hKey);
			return ret;
		}

		// make sure that the string is terminated

		if (backup[size]) {
			backup[size++] = '\0';
		}

	}
	else {
		backup[0] = '\0';
	}

	if (backup[0]) {
		//
		// buckup filetype exists so revert to it
		//

		ret = RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)backup, size);

		if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"RemoveAssociation : RegSetValueEx(\"[HKCR\\%s] @ = %s\")\n",
				ext, backup));

			RegCloseKey(hKey);
			return ret;
		}

		// delte backup value

		ret = RegDeleteValue(hKey, backup_value);

		if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"RemoveAssociation : RegDeleteValue(\"[HKCR\\%s] %s\")\n",
				ext, backup_value));

			RegCloseKey(hKey);
			return ret;
		}
	}
	else {
		// simply delete current filetype

		ret = RegDeleteValue(hKey, NULL);

		if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"RemoveAssociation : RegDeleteValue(\"[HKCR\\%s] @\")\n",
				ext));

			RegCloseKey(hKey);
			return ret;
		}
	}

	RegCloseKey(hKey);

	if (backup[0] == '\0') {

		// either backup filetype does not exist or backup value was not
		// specified, so delete the extension key

		ret = RegDeleteKey(HKEY_CLASSES_ROOT, ext);

		if (ret != ERROR_SUCCESS && ret != ERROR_ACCESS_DENIED) {
			VFDTRACE(0, (
				"RemoveAssociation : RegDeleteKey(\"[HKCR\\%s]\")\n",
				ext));

			// this is not really fatal
		}
	}

	if (current[0]) {

		// successfully reverted or removed extention key, so now
		// delte filetype subkey

		return DeleteRegistryTree(HKEY_CLASSES_ROOT, current);
	}

	return ERROR_SUCCESS;
}

//
//	recursively delete a registry subtree
//
DWORD DeleteRegistryTree(HKEY hKey, LPCTSTR subkey)
{
	HKEY hSubKey;
	LONG ret;
	DWORD keysize;

	//	open subkey to delete

	ret = RegOpenKeyEx(hKey, subkey, 0, KEY_READ, &hSubKey);

	if (ret != ERROR_SUCCESS) {
		VFDTRACE(0, (
			"DeleteRegistryTree : RegOpenKeyEx(\"%s\")\n", subkey));

		return ret;
	}

	//	get maximum subkey name length

	ret = RegQueryInfoKey(hSubKey, NULL, NULL, NULL, NULL, &keysize, NULL, NULL, NULL, NULL, NULL, NULL);

	if (ret != ERROR_SUCCESS) {
		VFDTRACE(0, (
			"DeleteRegistryTree : RegOpenKeyEx(\"%s\")\n", subkey));

		goto cleanup;
	}

	if (keysize) {
		//	allocate buffer for subkey name

		LPTSTR keyname = (LPTSTR)LocalAlloc(LPTR, ++keysize);

		if (!keyname) {
			ret = GetLastError();

			VFDTRACE(0, (
				"DeleteRegistryTree : LocalAlloc(%lu)\n", keysize));

			goto cleanup;
		}

		// enumerate each sub-subkey

		for (;;) {
			ret = RegEnumKey(hSubKey, 0, keyname, keysize);

			if (ret == ERROR_NO_MORE_ITEMS) {
				break;
			}
			else if (ret != ERROR_SUCCESS) {
				VFDTRACE(0, (
					"DeleteRegistryTree(\"%s\"): RegEnumKey\n", subkey));
				break;
			}

			// delete sub-subkey

			ret = DeleteRegistryTree(hSubKey, keyname);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0, (
					"DeleteRegistryTree(\"%s\"): DeleteRegistryTree(\"%s\")\n",
					subkey, keyname));
				break;
			}
		}

		LocalFree(keyname);
	}

cleanup:
	// close target subkey

	RegCloseKey(hSubKey);

	//	delete target subkey

	if (ret == ERROR_SUCCESS || ret == ERROR_NO_MORE_ITEMS) {
		ret = RegDeleteKey(hKey, subkey);

		if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"DeleteRegistryTree : RegDeleteKey(\"%s\")\n",
				subkey));
		}
	}

	return ret;
}

//
//	Add filetype association
//	-- preserve current association as much as possible
//
DWORD AddAssociation(
	LPCTSTR ext,
	LPCTSTR type_prefix,
	LPCTSTR type_desc,
	LPCTSTR verb,
	LPCTSTR verb_desc,
	LPCTSTR program,
	int icon_idx)
{
	HKEY hExtKey, hNewKey, hSub;
	char filetype[MAX_PATH], backup[MAX_PATH], buf[MAX_PATH];
	DWORD created;
	DWORD size;
	LONG ret;

	//
	//	Create a new filetype subkey
	//
	{
		int i = 0;

		for (;;) {
			sprintf(filetype, "%s%s.%d", type_prefix, ext, i++);

			ret = RegCreateKeyEx(
				HKEY_CLASSES_ROOT, filetype, 0, "", 0, KEY_WRITE, NULL, &hNewKey, &created);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0, (
					"AddAssociation : RegCreateKeyEx(\"[HKCR\\%s]\")\n",
					filetype));

				return ret;
			}

			if (created == REG_CREATED_NEW_KEY) {
				break;
			}
			else {
				RegCloseKey(hNewKey);
			}
		}
	}

	//
	//	Open the extension subkey
	//

	ret = RegCreateKeyEx(
		HKEY_CLASSES_ROOT, ext, 0, "", 0, KEY_ALL_ACCESS, NULL, &hExtKey, &created);

	if (ret != ERROR_SUCCESS) {
		RegCloseKey(hNewKey);

		VFDTRACE(0, (
			"AddAssociation : RegCreateKeyEx(\"[HKCR\\%s]\")\n", ext));

		return ret;
	}

	if (created == REG_OPENED_EXISTING_KEY) {

		//	extension subkey already exists -- get current filetype

		size = sizeof(backup);

		ret = RegQueryValueEx(hExtKey, NULL, NULL, NULL, (LPBYTE)backup, &size);

		if (ret == ERROR_FILE_NOT_FOUND) {
			size = 0;
		}
		else if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"AddAssociation : RegQueryValueEx(\"[HKCR\\%s] @\")\n", ext));

			goto cleanup;
		}

		if (backup[size]) {
			backup[size++] = '\0';
		}
	}
	else {
		backup[0] = '\0';
	}

	// If the extension is already assigned a filetype
	// then copy from the original filetype subtree to a new tree

	if (backup[0]) {
		HKEY hOldKey;

		ret = RegOpenKeyEx(HKEY_CLASSES_ROOT, backup, 0, KEY_READ, &hOldKey);

		if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"AddAssociation : RegOpenKeyEx(\"[HKCR\\%s]\")\n", backup));

			goto cleanup;
		}

		ret = CopyRegistryTree(hNewKey, hOldKey);

		RegCloseKey(hOldKey);

		if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"AddAssociation : CopyRegistryTree(\"%s\", \"%s\")\n",
				filetype, backup));

			goto cleanup;
		}
	}

	//
	//	OK, now set new filetype entries
	//

	//	create a mandatory subkey first

	if (verb && !*verb) {
		verb = "open";
	}

	// create command line subkey

	sprintf(buf, "shell\\%s\\command", verb);

	ret = RegCreateKeyEx(hNewKey, buf, 0, "", 0, KEY_WRITE, NULL, &hSub, NULL);

	if (ret != ERROR_SUCCESS) {
		VFDTRACE(0, (
			"AddAssociation : RegCreateKeyEx(\"[HKCR\\%s]\")\n",
			buf));

		goto cleanup;
	}

	// set command line value

	sprintf(buf, "\"%s\" \"%%1\"", program);

	ret = RegSetValueEx(hSub, NULL, 0, REG_SZ, (LPBYTE)buf, strlen(buf) + 1);

	RegCloseKey(hSub);

	if (ret != ERROR_SUCCESS) {
		VFDTRACE(0, (
			"AddAssociation : RegSetValueEx(\"[HKCR\\%s\\shell\\%s\\command] @= %s\")\n",
			filetype, verb, buf));

		goto cleanup;
	}

	//	default verb

	ret = RegOpenKeyEx(hNewKey, "shell", 0, KEY_WRITE, &hSub);

	if (ret == ERROR_SUCCESS) {
		ret = RegSetValueEx(hSub, NULL, 0, REG_SZ, (LPBYTE)verb, strlen(verb) + 1);

		RegCloseKey(hSub);

		if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"AddAssociation : RegSetValueEx(\"[HKCR\\%s\\shell] @=%s\")\n",
				filetype, verb));
			// this is not fatal
		}
	}
	else {
		VFDTRACE(0, (
			"AddAssociation : RegOpenKeyEx(\"[HKCR\\%s\\shell]\")\n",
			filetype));
		// this is not fatal
	}

	//	verb description

	if (verb_desc && *verb_desc) {
		sprintf(buf, "shell\\%s", verb);

		ret = RegOpenKeyEx(hNewKey, buf, 0, KEY_WRITE, &hSub);

		if (ret == ERROR_SUCCESS) {
			ret = RegSetValueEx(hSub, NULL, 0, REG_SZ, (LPBYTE)verb_desc, strlen(verb_desc) + 1);

			RegCloseKey(hSub);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0, (
					"AddAssociation : RegSetValueEx(\"[HKCR\\%s\\shell\\%s] @=%s\")\n",
					filetype, verb, verb_desc));
				// this is not fatal
			}
		}
		else {
			VFDTRACE(0, (
				"AddAssociation : RegOpenKeyEx(\"[HKCR\\%s\\shell\\%s]\")\n",
				filetype, verb));
			// this is not fatal
		}
	}

	//	filetype description

	if (type_desc && *type_desc) {
		ret = RegSetValueEx(hNewKey, NULL, 0, REG_SZ, (LPBYTE)type_desc, strlen(type_desc) + 1);

		if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"AddAssociation : RegSetValueEx(\"[HKCR\\%s] @=%s\")\n",
				filetype, type_desc));
			// this is not fatal
		}
	}

	//	default icon

	if (program && *program && icon_idx >= 0) {
		ret = RegCreateKeyEx(hNewKey, "DefaultIcon", 0, "", 0, KEY_WRITE, NULL, &hSub, NULL);

		if (ret == ERROR_SUCCESS) {
			sprintf(buf, "%s,%d", program, icon_idx);

			ret = RegSetValueEx(hSub, NULL, 0, REG_SZ, (LPBYTE)buf, strlen(buf) + 1);

			RegCloseKey(hSub);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0, (
					"AddAssociation : RegSetValueEx(\"[HKCR\\%s\\DefaultIcon] @=%s\")\n",
					filetype, buf));
				// this is not fatal
			}
		}
		else {
			VFDTRACE(0, (
				"AddAssociation : RegCreateKeyEx(\"[HKCR\\%s\\DefaultIcon]\")\n",
				filetype));
			// this is not fatal
		}
	}

	//
	//	New filetype tree successfully created, so update the extension's filetype
	//
	if (backup[0]) {
		ret = RegSetValueEx(hExtKey, type_prefix, 0, REG_SZ, (LPBYTE)backup, strlen(backup) + 1);

		if (ret != ERROR_SUCCESS) {
			VFDTRACE(0, (
				"AddAssociation : RegSetValueEx(\"[HKCR\\%s] %s=%s\")\n",
				ext, type_prefix, backup));

			goto cleanup;
		}
	}

	ret = RegSetValueEx(hExtKey, NULL, 0, REG_SZ, (LPBYTE)filetype, strlen(filetype) + 1);

	if (ret != ERROR_SUCCESS) {
		VFDTRACE(0, (
			"AddAssociation : RegSetValueEx(\"[HKCR\\%s] @=%s\")\n",
			ext, filetype));
	}

cleanup:
	if (hNewKey) {
		RegCloseKey(hNewKey);
	}
	if (hExtKey) {
		RegCloseKey(hExtKey);
	}

	if (ret != ERROR_SUCCESS) {

		//	failed somethere so delete (probably) incomplete subkeys

		DeleteRegistryTree(HKEY_CLASSES_ROOT, filetype);

		if (backup[0] == 0) {
			RegDeleteKey(HKEY_CLASSES_ROOT, ext);
		}
	}

	return ret;
}

//
//	Recursively copy registry subtree
//
DWORD CopyRegistryTree(HKEY hKeyTo, HKEY hKeyFrom)
{
	LONG ret;
	DWORD keycnt, keymax, clsmax, valcnt, namemax, valmax;

	ret = RegQueryInfoKey(
		hKeyFrom,
		NULL,
		NULL,
		NULL,
		&keycnt,
		&keymax,
		&clsmax,
		&valcnt,
		&namemax,
		&valmax,
		NULL,
		NULL);

	if (ret != ERROR_SUCCESS) {
		VFDTRACE(0, (
			"CopyRegistryTree : RegQueryInfoKey\n"));
		return ret;
	}

	//
	//	copy subkeys
	//

	if (keycnt) {
		LPTSTR clsname = NULL, keyname = NULL;

		// prepare buffers
		keyname = (LPTSTR)LocalAlloc(LPTR, ++keymax);

		if (keyname == NULL) {
			VFDTRACE(0, (
				"CopyRegistryTree : malloc(%lu)\n", keymax));

			goto cleanup_subkey;
		}

		clsname = (LPTSTR)LocalAlloc(LPTR, ++clsmax);

		if (clsname == NULL) {
			VFDTRACE(0, (
				"CopyRegistryTree : LocalAlloc(%lu)\n", clsmax));

			goto cleanup_subkey;
		}

		//	process each subkey

		while (keycnt--) {
			DWORD clslen, keylen;
			HKEY hSubTo, hSubFrom;
			FILETIME ft;

			keylen = keymax;
			clslen = clsmax;

			// get existing subkey info

			ret = RegEnumKeyEx(hKeyFrom, keycnt, keyname, &keylen, NULL, clsname, &clslen, &ft);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0, (
					"CopyRegistryTree : RegEnumKeyEx\n"));

				break;
			}

			// create new subkey

			ret = RegCreateKeyEx(hKeyTo, keyname, 0, clsname, 0, KEY_WRITE, NULL, &hSubTo, NULL);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0, (
					"CopyRegistryTree : RegCreateKeyEx(\"%s\")\n", keyname));

				break;
			}

			// open existing subkey

			ret = RegOpenKeyEx(hKeyFrom, keyname, 0, KEY_READ, &hSubFrom);

			if (ret != ERROR_SUCCESS) {
				RegCloseKey(hSubFrom);

				VFDTRACE(0, (
					"CopyRegistryTree : RegOpenKeyEx(\"%s\")\n", keyname));

				break;
			}

			// copy subkey contents

			ret = CopyRegistryTree(hSubTo, hSubFrom);

			RegCloseKey(hSubFrom);
			RegCloseKey(hSubTo);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0, (
					"CopyRegistryTree : CopyRegistryTree(\"%s\")\n", keyname));

				break;
			}
		}

cleanup_subkey:
		if (clsname) {
			LocalFree(clsname);
		}
		if (keyname) {
			LocalFree(keyname);
		}
	}

	//
	//	copy values
	//

	if (ret == ERROR_SUCCESS && valcnt) {
		LPTSTR valname = NULL;
		LPBYTE value = NULL;

		// prepare buffers
		valname = (LPTSTR)LocalAlloc(LPTR, ++namemax);

		if (valname == NULL) {
			VFDTRACE(0, (
				"CopyRegistryTree : LocalAlloc(%lu)\n", namemax));

			goto cleanup_value;
		}

		value = (LPBYTE)LocalAlloc(LPTR, ++valmax);

		if (value == NULL) {
			VFDTRACE(0, (
				"CopyRegistryTree : LocalAlloc(%lu)\n", valmax));

			goto cleanup_value;
		}

		// process each value

		while (valcnt--) {
			DWORD namelen, vallen, type;

			namelen = namemax;
			vallen = valmax;

			ret = RegEnumValue(hKeyFrom, valcnt, valname, &namelen, NULL, &type, value, &vallen);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0, (
					"CopyRegistryTree : RegEnumValue\n"));

				break;
			}

			ret = RegSetValueEx(hKeyTo, valname, 0, type, value, vallen);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0, (
					"CopyRegistryTree : RegSetValueEx(%s)\n", valname));

				break;
			}
		}

cleanup_value:
		if (valname) {
			LocalFree(valname);
		}
		if (value) {
			LocalFree(value);
		}
	}

	return ret;
}
