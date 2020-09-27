/*
	vfdwin.c

	Virtual Floppy Drive for Windows
	GUI Control Panel main source

	Copyright (C) 2003-2008 Ken Kato
*/

#ifdef __cplusplus
#pragma message( __FILE__ ": Compiled as C++ for testing purpose.\n" )
#endif	// __cplusplus

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(push,3)
#include <objbase.h>
#include <commctrl.h>
#include <shellapi.h>
#pragma warning(pop)
#include <crtdbg.h>
#include <stdio.h>

#include "vfdtypes.h"
#include "vfdapi.h"
#include "vfdwin.h"
#include "vfdmsg.h"
#include "resource.h"

//
//	global variable instances
//
extern HINSTANCE	hAppInst = NULL;
extern CHAR			sAppPath[MAX_PATH] = {0};
extern PSTR			pAppBase = NULL;
extern HWND			hMainWnd = NULL;

//
//	local funtions
//
static void		CommandLine();

//
//	Application entry point
//
int WINAPI WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInst,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	HACCEL		hAccel;
	MSG			msg = { 0 };
	DWORD		err;

	UNREFERENCED_PARAMETER(hPrevInst);
	UNREFERENCED_PARAMETER(nCmdShow);

	//
	//	Reports memory leaks at process termination
	//
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	//
	//	Check the Operating System version
	//
	if (!VfdIsValidPlatform()) {
		ShowErrorMessage(0, MSG_ERR_WRONG_PLATFORM);
		return -1;
	}

	//
	//	Save the application instance handle
	//
	hAppInst = hInstance;

	//
	//	Process command line parameters
	//
	if (lpCmdLine && *lpCmdLine) {
		CommandLine();
		return 0;
	}

	//
	//	register the custom dialog window class
	//
	{
		WNDCLASS	wc;
		
		GetClassInfo(hInstance, WC_DIALOG, &wc);

		wc.lpszClassName = VFDWIN_APP_BASENAME;

		RegisterClass(&wc);
	}

	//
	//	Find if another instance of VfdWin is running
	//
	{
		HWND	hWnd;

		hWnd = FindWindow(VFDWIN_APP_BASENAME, NULL);

		if (hWnd) {

			//	bring to the foreground

			ShowWindow(hWnd, SW_RESTORE);
			SetForegroundWindow(hWnd);

			return 0;
		}
	}

	//
	//	Store application executable file path
	//
	err = GetModuleFileName(NULL, sAppPath, sizeof(sAppPath));

	if (err == 0) {
		err = GetLastError();

		VFDTRACE(0,("WinMain : GetModuleFileName() - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		goto cleanup;
	}

	pAppBase = sAppPath + err;

	while (pAppBase > sAppPath && *(pAppBase - 1) != '\\') {
		pAppBase--;
	}

	//
	//	initialize ole and common controls
	//
	if (!SUCCEEDED(CoInitialize(NULL))) {
		err = GetLastError();

		VFDTRACE(0,("WinMain : CoInitialize() - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		goto cleanup;
	}

	InitCommonControls();

	//
	//	Create the main dialog window
	//
	hMainWnd = CreateDialog(
		hInstance,
		MAKEINTRESOURCE(IDD_MAIN),
		NULL,
		MainProc);

	if (hMainWnd == NULL) {
		err = GetLastError();

		VFDTRACE(0,("WinMain : CreateDialog - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		goto cleanup;
	}

	hAccel = LoadAccelerators(hInstance,
		MAKEINTRESOURCE(IDR_ACCELERATOR));

	if (hAccel == NULL) {
		VFDTRACE(0,("WinMain : LoadAccelerators - %s",
			GetSystemMessage(GetLastError())));
	}

	//
	//	Message loop
	//
	for (;;) {
		BOOL ret = GetMessage(&msg, NULL, 0, 0);

		if (ret == 0) {
			break;
		}
		else if (ret == -1) {
			err = GetLastError();

			VFDTRACE(0,("WinMain: GetMessage - %s",
				GetSystemMessage(err)));

			ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

			break;
		}

		if (!TranslateAccelerator(hMainWnd, hAccel, &msg) &&
			!IsDialogMessage(hMainWnd, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

cleanup:
	CoUninitialize();

	return msg.wParam;
}

//
//	Close the current image and open the new image
//
void CommandLine()
{
	ULONG			target		= '0';
	PSTR			file_name	= NULL;
	VFD_DISKTYPE	disk_type	= VFD_DISKTYPE_FILE;
	VFD_MEDIA		media_type	= VFD_MEDIA_NONE;
	VFD_FLAGS		image_flags	= 0;
	VFD_FILETYPE	file_type;
	BOOL			five_inch	= FALSE;
	CHAR			protect		= 0;
	BOOL			open_folder	= TRUE;
	BOOL			close_only	= FALSE;
	HANDLE			hDevice;
	CHAR			letter;
	DWORD			driver_state;
	DWORD			ret;

	//
	//	process command line parameters
	//
	while (*(++__argv)) {

		//	Open switch
		if (_stricmp(*__argv, VFD_OPEN_SWITCH) == 0) {
			close_only = FALSE;
		}

		//	Close switch
		else if (_stricmp(*__argv, "/close") == 0) {
			close_only = TRUE;
		}

		//	Quiet mode switch
		else if (stricmp(*__argv, "/q") == 0) {
			open_folder = FALSE;
		}

		//	Disk type options
		else if (_stricmp(*__argv, "/ram") == 0) {
			disk_type = VFD_DISKTYPE_RAM;
		}

		//	Protect options
		else if (_stricmp(*__argv, "/p") == 0 ||
			_stricmp(*__argv, "/w") == 0) {

			protect = (CHAR)toupper(*(*__argv + 1));
		}

		//	media type options
		else if (strcmp(*__argv, "/160") == 0) {
			media_type = VFD_MEDIA_F5_160;
		}
		else if (strcmp(*__argv, "/180") == 0) {
			media_type = VFD_MEDIA_F5_180;
		}
		else if (strcmp(*__argv, "/320") == 0) {
			media_type = VFD_MEDIA_F5_320;
		}
		else if (strcmp(*__argv, "/360") == 0) {
			media_type = VFD_MEDIA_F5_360;
		}
		else if (strcmp(*__argv, "/640") == 0) {
			media_type = VFD_MEDIA_F3_640;
		}
		else if (strcmp(*__argv, "/720") == 0) {
			media_type = VFD_MEDIA_F3_720;
		}
		else if (strcmp(*__argv, "/820") == 0) {
			media_type = VFD_MEDIA_F3_820;
		}
		else if (strcmp(*__argv, "/120") == 0 ||
			strcmp(*__argv, "/1.20") == 0) {
			media_type = VFD_MEDIA_F3_1P2;
		}
		else if (strcmp(*__argv, "/144") == 0 ||
			strcmp(*__argv, "/1.44") == 0) {
			media_type = VFD_MEDIA_F3_1P4;
		}
		else if (strcmp(*__argv, "/168") == 0 ||
			strcmp(*__argv, "/1.68") == 0) {
			media_type = VFD_MEDIA_F3_1P6;
		}
		else if (strcmp(*__argv, "/172") == 0 ||
			strcmp(*__argv, "/1.72") == 0) {
			media_type = VFD_MEDIA_F3_1P7;
		}
		else if (strcmp(*__argv, "/288") == 0 ||
			strcmp(*__argv, "/2.88") == 0) {
			media_type = VFD_MEDIA_F3_2P8;
		}

		//	5.25 inch
		else if (strcmp(*__argv, "/5") == 0 ||
			strcmp(*__argv, "/525") == 0 ||
			strcmp(*__argv, "/5.25") == 0) {
			five_inch = TRUE;
		}

		//	target drive
		else if (isalnum(**__argv) &&
			*(*__argv + 1) == ':' &&
			*(*__argv + 2) == '\0') {

			target = toupper(**__argv);
		}
		else if (**__argv == '*' &&
			*(*__argv + 1) == ':' &&
			*(*__argv + 2) == '\0') {

			target = (ULONG)-1;
		}

		//	image filename
		else if (**__argv != '/') {
			file_name = *__argv;

			if (*file_name == '\"' && *(file_name + strlen(file_name) - 1) == '\"') {

				// remove quote characters if the path is quoted

				*(file_name + strlen(file_name) - 1) = '\0';
				file_name++;
			}
		}

		//	unknown options
		else {
			ShowErrorMessage(0, MSG_ERR_INVALID_PARAM, *__argv);
			return;
		}
	}

	//	check parameter consistency

	if (target == (ULONG)-1 && !close_only) {
		ShowErrorMessage(0, MSG_ERR_INVALID_PARAM, "*:");
		return;
	}

	//	Get the current driver state

	ret = VfdGetDriverState(&driver_state);

	if (ret != ERROR_SUCCESS) {
		ShowErrorMessage(ret, MSG_ERR_APP_INTERNAL);
		return;
	}

	if (close_only && driver_state != SERVICE_RUNNING) {
		//	nothing to do...
		return;
	}

	//	ensure that the driver is running

	if (driver_state == VFD_NOT_INSTALLED) {
		ret = VfdInstallDriver(NULL, SERVICE_DEMAND_START);

		if (ret != ERROR_SUCCESS) {
			ShowErrorMessage(ret, MSG_ERR_DRIVER_INSTALL);
			return;
		}
	}

	//	ensure that the driver is started

	if (driver_state != SERVICE_RUNNING) {
		ret = VfdStartDriver(&driver_state);

		if (ret != ERROR_SUCCESS ||
			driver_state != SERVICE_RUNNING) {
			ShowErrorMessage(ret, MSG_ERR_DRIVER_START);
			return;
		}
	}

	//
	//	close the current image (if any)
	//
	if (target == (ULONG)-1) {
		int i;
		for (i = 0; i < VFD_MAXIMUM_DEVICES; i++) {
			ret = VfdGuiClose(NULL, i);

			if (ret != ERROR_SUCCESS && ret != ERROR_NOT_READY) {
				ShowErrorMessage(ret, MSG_ERR_IMAGE_CLOSE, i + '0');
			}
		}
		return;
	}

	ret = VfdGuiClose(NULL, target);

	if (ret != ERROR_SUCCESS && ret != ERROR_NOT_READY) {
		ShowErrorMessage(ret, MSG_ERR_IMAGE_CLOSE, target);
		return;
	}

	if (close_only) {
		return;
	}

	//
	//	check target image file
	//
	if (file_name) {
		DWORD			file_attr;
		ULONG			image_size;

		ret = VfdCheckImageFile(
			file_name, &file_attr, &file_type, &image_size);

		if (ret == ERROR_FILE_NOT_FOUND) {

			//	If file does not exist, create a new image file

			if (media_type == VFD_MEDIA_NONE) {
				media_type = VFD_MEDIA_F3_1P4;
			}

			ret = VfdCreateImageFile(
				file_name, media_type, VFD_FILETYPE_RAW, FALSE);

			if (ret != ERROR_SUCCESS) {
				ShowErrorMessage(ret, MSG_ERR_FILE_CREATE, file_name);
				return;
			}

			ret = VfdCheckImageFile(
				file_name, &file_attr, &file_type, &image_size);

			if (ret != ERROR_SUCCESS) {
				ShowErrorMessage(ret, MSG_ERR_FILE_OPEN, file_name);
				return;
			}
		}
		else if (ret == ERROR_SUCCESS) {

			//	check file size / media size

			ULONG		media_size;
			VFD_MEDIA	def_media;

			media_size = VfdGetMediaSize(media_type);

			if (media_size > image_size) {

				ShowErrorMessage(0, MSG_ERR_IMAGE_TOO_SMALL);
				return;
			}

			def_media = VfdLookupMedia(image_size);

			if (def_media == VFD_MEDIA_NONE) {

				ShowErrorMessage(0, MSG_ERR_IMAGE_TOO_SMALL);
				return;
			}

			if (media_type == VFD_MEDIA_NONE) {
				media_type = def_media;
			}

			//	check file type

			if (file_type == VFD_FILETYPE_ZIP ||
				(file_attr & (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_COMPRESSED | FILE_ATTRIBUTE_ENCRYPTED))) {
				disk_type = VFD_DISKTYPE_RAM;
			}
		}
		else {
			ShowErrorMessage(ret, MSG_ERR_FILE_OPEN, file_name);
			return;
		}

		if (disk_type != VFD_DISKTYPE_FILE) {
			if (protect != 'W') {
				protect = 'P';
			}
		}
	}
	else {
		disk_type = VFD_DISKTYPE_RAM;

		if (media_type == VFD_MEDIA_NONE) {
			media_type = VFD_MEDIA_F3_1P4;
		}
	}

	if (protect == 'P') {
		image_flags |= VFD_FLAG_WRITE_PROTECTED;
	}

	if (five_inch &&
		VfdGetMediaSize(media_type) == VfdGetMediaSize((VFD_MEDIA)(media_type + 1))) {
		media_type = (VFD_MEDIA)(media_type + 1);
	}

	//	Open the target device

	hDevice = VfdOpenDevice(target);

	if (hDevice == INVALID_HANDLE_VALUE) {
		ShowErrorMessage(GetLastError(), MSG_ERR_DEVICE_OPEN, target);
		return;
	}

	//	assign a drive letter if the drive has none

	VfdGetGlobalLink(hDevice, &letter);

	if (!isalpha(letter)) {
		VfdGetLocalLink(hDevice, &letter);
	}

	if (!isalpha(letter)) {
		letter = VfdChooseLetter();
		VfdSetLocalLink(hDevice, letter);
	}

	//	Open the image file

	ret = VfdOpenImage(hDevice, file_name,
		disk_type, media_type, image_flags);

	CloseHandle(hDevice);

	if (ret != ERROR_SUCCESS) {
		ShowErrorMessage(ret, MSG_ERR_FILE_OPEN,
			file_name ? file_name : "<RAM>");
		return;
	}

	//
	//	Unless otherwise specified, open the drive
	//
	if (open_folder && isalpha(letter)) {
		CHAR drive[] = "A:\\";
		CHAR verb[20] = {0};
		LONG size = sizeof(verb);

		drive[0] = (CHAR)toupper(letter);

		//	get the default verb for folder object from the registry
		RegQueryValue(HKEY_CLASSES_ROOT, "Folder\\shell", verb, &size);

		ret = (DWORD)ShellExecute(
			NULL, verb[0] ? verb : NULL, drive, NULL, NULL, SW_SHOWNORMAL);

		if (ret <= 32) {
			VFDTRACE(0, ("OpenImage : ShellExecute - %s",
				GetSystemMessage(GetLastError())));
		}
	}

	return;
}
//
//	Get message text from the VfdWin module
//
DWORD GetLocalMessage(DWORD msg, LPTSTR buf, DWORD size, ...)
{
	DWORD ret;
	va_list	args;

	va_start(args, size);

	ret = FormatMessage(
		FORMAT_MESSAGE_FROM_HMODULE,
		hAppInst, msg, 0, buf, size, &args);

	va_end(args);

	return ret;
}

//
//	Displays error message box
//
void ShowErrorMessage(DWORD err, DWORD msg, ...)
{
	TCHAR buf[512];
	DWORD len = 0;

	if (msg) {
		va_list	args;

		va_start(args, msg);

		len = FormatMessage(FORMAT_MESSAGE_FROM_HMODULE,
			hAppInst, msg, 0, buf, sizeof(buf), &args);

		va_end(args);
	}

	if (err) {
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, err, 0, buf + len, sizeof(buf) - len, NULL);
	}

	MessageBox(hMainWnd, buf, VFDWIN_APP_BASENAME, MB_ICONSTOP);
}

//
//	Set control window text
//
void SetControlText(HWND hDlg, UINT nID, DWORD msg, ...)
{
	PSTR str;
	va_list args;

	va_start(args, msg);

	FormatMessage(
		FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		hAppInst, msg, 0, (LPTSTR)&str, 0, &args);

	va_end(args);

	if (nID) {
		SetDlgItemText(hDlg, nID, str);
	}
	else {
		SetWindowText(hDlg, str);
	}

	if (str) {
		LocalFree(str);
	}
}

//
//	append a text string to the message control
//
void AppendLogMessage(DWORD err, DWORD msg, ...)
{
	TCHAR	buf[200];
	DWORD	len;
	DWORD	max;
	DWORD	cur;
	HWND	hEdit;

	//	get edit control handle

	hEdit = GetDlgItem(hMainWnd, IDC_LOG_MESSAGE);

	if (hEdit == NULL) {
		VFDTRACE(0,("AppendMessage : GetDlgItem - %s",
			GetSystemMessage(GetLastError())));
		return;
	}

	//	max length of text the edit control can store

	max = SendMessage(hEdit, EM_GETLIMITTEXT, 0, 0);

	if (max == 0) {
		VFDTRACE(0,("AppendMessage : EM_GETLIMITTEXT - %s",
			GetSystemMessage(GetLastError())));
		return;
	}

	//	current length of text in the edit control

	cur = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);

	//	format the message

	len = 0;

	if (msg) {
		va_list	args;

		va_start(args, msg);

		len = FormatMessage(
			FORMAT_MESSAGE_FROM_HMODULE,
			hAppInst, msg, 0, buf, sizeof(buf), &args);

		va_end(args);
	}

	if (err) {
		len += FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, err, 0, buf + len, sizeof(buf) - len, NULL);
	}

	if (cur + len >= max) {
		//	remove first half of text in the edit control
		SendMessage(hEdit, EM_SETSEL, 0, cur / 2);
		SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)"");

		cur -= (cur / 2);
	}

	//	append the new text at the end

	SendMessage(hEdit, EM_SETSEL, cur, cur);
	SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)buf);
}

//
//	Get system error message string
//
PCSTR GetSystemMessage(
	DWORD	nError)
{
	static CHAR msg[256];

	if (!FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, nError, 0, msg, sizeof(msg), NULL)) {
		sprintf(msg, "Unknown system error %lu (0x%08x)\n", nError, nError);
	}

	return msg;
}

#ifdef _DEBUG
//
//	Format and output debug string
//
extern ULONG TraceFlags = (ULONG)-1;//0;
extern CHAR *TraceFile = NULL;
extern ULONG TraceLine = 0;

void DebugTrace(
	PCSTR	sFormat, ...)
{
	CHAR	buf[512];
	int		len;
	va_list	args;

	len = sprintf(buf, "%s(%lu) : ", TraceFile, TraceLine);

	va_start(args, sFormat);

	vsprintf(buf + len, sFormat, args);

	va_end(args);

	OutputDebugString(buf);
}
#endif	// _DEBUG
