/*
	driverdlg.c

	Virtual Floppy Drive for Windows
	GUI Control Panel
	"Driver" dialog functions

	Copyright (C) 2003-2005 Ken Kato
*/

#ifdef __cplusplus
#pragma message( __FILE__ ": Compiled as C++ for testing purpose.\n" )
#endif	// __cplusplus

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(push,3)
#include <commdlg.h>
#pragma warning(pop)
#include <stdio.h>

#include "vfdtypes.h"
#include "vfdapi.h"
#include "vfdver.h"
#include "vfdwin.h"
#include "vfdmsg.h"
#include "resource.h"

//
//	local definitions
//

//	OPENFILENAME flag values in commdlg.h for WINVER >= 0x0500
#ifndef OPENFILENAME_SIZE_VERSION_400
// Pre Win2K system header is used
// OPENFILENAME is defined without extra fields.
#define OPENFILENAME_SIZE_VERSION_400 sizeof(OPENFILENAME)
#endif

//	we don't want *.sys file to be added to recent docs folder
#ifndef OFN_DONTADDTORECENT
#define OFN_DONTADDTORECENT		0x02000000
#endif	//	OFN_DONTADDTORECENT

//	we want *.sys files to be shown in open dialog box
#ifndef OFN_FORCESHOWHIDDEN
#define OFN_FORCESHOWHIDDEN		0x10000000
#endif	//	OFN_FORCESHOWHIDDEN

//	Fallback text string

#define FALLBACK_DRIVER_FILTER	"VFD Driver (vfd.sys)\0vfd.sys\0"
#define FALLBACK_DRIVER_TITLE	"VFD Driver"

#define FALLBACK_CONFIRM_STOP					\
	"Failed to close the current image.\r\n"	\
	"The driver may not stop properly.\r\n"		\
	"Proceed?"

#define FALLBACK_CONFIRM_REMOVE					\
	"Failed to stop the driver.\r\n"			\
	"It may not unload properly.\r\n"			\
	"Proceed?"

//
//	Windows message handlers
//
static void OnInitDialog	(HWND hDlg);

static void OnPathChanged	(HWND hDlg, HWND hEdit);
static void OnBrowseClicked	(HWND hDlg);
static void OnInstallClicked(HWND hDlg, HWND hButton);
static void OnRemoveClicked	(HWND hDlg, HWND hButton);
static void OnStartClicked	(HWND hDlg, HWND hButton);
static void OnStopClicked	(HWND hDlg, HWND hButton);
static void OnStartChanged	(HWND hDlg);
static void OnApplyClicked	(HWND hDlg, HWND hButton);
static void OnRefreshDialog	(HWND hDlg);

//
//	local functions
//
static BOOL InstallDriver	(HWND hDlg);
static BOOL RemoveDriver	(HWND hDlg);
static BOOL StartDriver		(HWND hDlg);
static BOOL StopDriver		(HWND hDlg);
static BOOL ConfigDriver	(HWND hDlg);
static BOOL ConfirmContinue	(HWND hDlg, UINT msg, PCSTR fallback);

//
//	window message dispatcher
//

BOOL CALLBACK DriverProc(
	HWND hDlg,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		OnInitDialog(hDlg);
		break;

	case WM_COMMAND:
		switch (wParam) {
		case MAKELONG(IDC_DRIVER_PATH, EN_CHANGE):
			OnPathChanged(hDlg, (HWND)lParam);
			break;
		case IDC_BROWSE:
			OnBrowseClicked(hDlg);
			break;

		case IDC_INSTALL:
			OnInstallClicked(hDlg, (HWND)lParam);
			break;

		case IDC_REMOVE:
			OnRemoveClicked(hDlg, (HWND)lParam);
			break;

		case IDC_START:
			OnStartClicked(hDlg, (HWND)lParam);
			break;

		case IDC_STOP:
			OnStopClicked(hDlg, (HWND)lParam);
			break;

		case IDC_START_MANUAL:
		case IDC_START_AUTO:
			OnStartChanged(hDlg);
			break;

		case IDC_APPLY:
			OnApplyClicked(hDlg, (HWND)lParam);
			break;
		}
		break;

	case VFD_REFRESH_MSG:
		OnRefreshDialog(hDlg);
		break;
	}

	return 0;
}

//
//	initialize the driver dialog
//
void OnInitDialog(HWND hDlg)
{
	CHAR	buf[MAX_PATH];

	//	Set control text

	SetControlText(hDlg, IDC_DRIVER_LABEL,	MSG_DRIVER_LABEL);
	SetControlText(hDlg, IDC_BROWSE,		MSG_BROWSE_BUTTON);
	SetControlText(hDlg, IDC_VERSION_LABEL, MSG_VERSION_LABEL);
	SetControlText(hDlg, IDC_START_LABEL,	MSG_START_LABEL);
	SetControlText(hDlg, IDC_START_MANUAL,	MSG_START_MANUAL);
	SetControlText(hDlg, IDC_START_AUTO,	MSG_START_AUTO);
	SetControlText(hDlg, IDC_INSTALL,		MSG_INSTALL_BUTTON);
	SetControlText(hDlg, IDC_START,			MSG_START_BUTTON);
	SetControlText(hDlg, IDC_STOP,			MSG_STOP_BUTTON);
	SetControlText(hDlg, IDC_REMOVE,		MSG_REMOVE_BUTTON);
	SetControlText(hDlg, IDC_APPLY,			MSG_APPLY_BUTTON);

	//	prepare default driver path

	memcpy(buf, sAppPath, pAppBase - sAppPath);
	strcpy(&buf[pAppBase - sAppPath], VFD_DRIVER_FILENAME);

	SetDlgItemText(hDlg, IDC_DRIVER_PATH, buf);

	//	choose the default radio button (MANUAL)

	CheckRadioButton(hDlg,
		IDC_START_MANUAL, IDC_START_AUTO, IDC_START_MANUAL);

	return;
}

//
//	Driver path is changed
//
void OnPathChanged(HWND hDlg, HWND hEdit)
{
	CHAR	buf[MAX_PATH];
	int		len		= 0;
	DWORD	version	= 0;
	BOOL	valid	= FALSE;
	DWORD	ret;

	//	Get current text

	if (GetWindowText(hEdit, buf, sizeof(buf))) {

		//	See if the path is a valid VFD driver

		ret = VfdCheckDriverFile(buf, &version);

		if (version) {
			len = sprintf(buf, "%u.%u%s",
				HIWORD(version) & 0x7fff,
				LOWORD(version),
				(version & 0x80000000) ? " (debug)" : "");
		}

		if (ret == ERROR_SUCCESS) {
			valid = TRUE;
		}
		else {
			len += sprintf(buf + len, " [%s", GetSystemMessage(ret));

			while (buf[len - 1] == '\r' || buf[len - 1] == '\n') {
				buf[--len] = '\0';
			}

			buf[len] = ']';
		}
	}

	//	Show version text

	SetDlgItemText(hDlg, IDC_VERSION, buf);

	//	Enable the install and start buttons if the driver is valid

	EnableWindow(GetDlgItem(hDlg, IDC_START), valid);
	EnableWindow(GetDlgItem(hDlg, IDC_INSTALL), valid);
}

//
//	Driver path browse button is clicked
//
void OnBrowseClicked(HWND hDlg)
{
	OPENFILENAME ofn;
	TCHAR filter[50];
	TCHAR title[50];
	TCHAR path[MAX_PATH];

	//	get current text in path edit

	GetDlgItemText(hDlg, IDC_DRIVER_PATH, path, sizeof(path));

	//	prepare filter for the open file dialog

	if (GetLocalMessage(MSG_DRIVER_OPEN_FILTER, filter, sizeof(filter))) {

		LPTSTR p = filter;

		while (*p) {
			if (*p == '|') {
				*p = '\0';
			}
			p++;
		}
	}
	else {
		VFDTRACE(0,("OnBrowseClicked : LoadString - %s",
			GetSystemMessage(GetLastError())));

		memcpy(filter, FALLBACK_DRIVER_FILTER,
			sizeof(FALLBACK_DRIVER_FILTER));
	}

	//	prepare title text for the open file dialog

	if (!GetLocalMessage(MSG_DRIVER_OPEN_TITLE, title, sizeof(title))) {

		VFDTRACE(0,("OnBrowseClicked : LoadString - %s",
			GetSystemMessage(GetLastError())));

		strcpy(title, FALLBACK_DRIVER_TITLE);
	}

	//	prepare OPENFILENAME structure

	memset(&ofn, 0, sizeof(ofn));

	// Different structure sizes must be used for NT and 2K/XP
	ofn.lStructSize = IS_WINDOWS_NT() ?
		OPENFILENAME_SIZE_VERSION_400 : sizeof(ofn);

	ofn.hwndOwner	= hDlg;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile	= path;
	ofn.nMaxFile	= sizeof(path);
	ofn.lpstrTitle	= title;
	ofn.Flags		= OFN_FILEMUSTEXIST
					| OFN_NONETWORKBUTTON
					| OFN_HIDEREADONLY
					| OFN_DONTADDTORECENT
					| OFN_FORCESHOWHIDDEN
					| OFN_NOCHANGEDIR;

	//	show open file dialog

	if (GetOpenFileName(&ofn)) {
		SetDlgItemText(hDlg, IDC_DRIVER_PATH, path);
	}
}

//
//	Install button is clicked
//
void OnInstallClicked(HWND hDlg, HWND hButton)
{
	if (InstallDriver(hDlg)) {

		//	move focus to the start button

		SendMessage(hButton, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);
		SetFocus(GetDlgItem(hDlg, IDC_START));
	}
}

//
//	Uninstall button is clicked
//
void OnRemoveClicked(HWND hDlg, HWND hButton)
{
	if (RemoveDriver(hDlg)) {

		//	move focus to the install button

		SendMessage(hButton, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);
		SetFocus(GetDlgItem(hDlg, IDC_INSTALL));
	}
}

//
//	start button is clicked
//
void OnStartClicked(HWND hDlg, HWND hButton)
{
	if (StartDriver(hDlg)) {

		//	move focus to the stop button

		SendMessage(hButton, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);
		SetFocus(GetDlgItem(hDlg, IDC_STOP));
	}
}

//
//	stop button is clicked
//
void OnStopClicked(HWND hDlg, HWND hButton)
{
	if (StopDriver(hDlg)) {

		//	move focus to the start button

		SendMessage(hButton, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);
		SetFocus(GetDlgItem(hDlg, IDC_START));
	}
}

//
//	Start type is changed
//
void OnStartChanged(HWND hDlg)
{
	DWORD	start_old;
	DWORD	start_new;

	if (VfdGetDriverConfig(NULL, &start_old) != ERROR_SUCCESS) {
		//	driver is not installed - do not use the Apply button
		return;
	}

	//	driver is already installed - enable the Apply button

	if (IsDlgButtonChecked(hDlg, IDC_START_AUTO) == BST_CHECKED) {
		if (IS_WINDOWS_NT()) {

			//	On Windows NT, SYSTEM start drivers must be placed
			//	under the winnt\system32 directory.  Since I don't
			//	care to handle driver file copying, I use the AUTO
			//	start method for Windows NT.

			start_new = SERVICE_AUTO_START;
		}
		else {

			//	On Windows XP, the VFD driver must be running when
			//	the shell starts -- otherwise the shell doesn't
			//	recognize the VFD drives.  Since Windows XP allows
			//	SYSTEM start drivers to be placed in any local
			//	directories, I use the SYSTEM start method here.
			//
			//	This is not an issue when the driver is started
			//	manually because in that case VFD.EXE and VFDWIN.EXE
			//	notify the shell of the VFD drives.
			//
			//	On Windows 2000 both SYSTEM and AUTO work fine.

//			start_new = SERVICE_SYSTEM_START;
			start_new = SERVICE_AUTO_START;
		}
	}
	else {
		start_new = SERVICE_DEMAND_START;
	}

	EnableWindow(GetDlgItem(hDlg, IDC_APPLY), (start_old != start_new));
}

//
//	Apply button is clicked
//
void OnApplyClicked(HWND hDlg, HWND hButton)
{
	if (ConfigDriver(hDlg)) {

		//	move focus to the manual button

		SendMessage(hButton, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);

		if (IsDlgButtonChecked(hDlg, IDC_START_MANUAL) == BST_CHECKED) {
			SetFocus(GetDlgItem(hDlg, IDC_START_MANUAL));
		}
		else {
			SetFocus(GetDlgItem(hDlg, IDC_START_AUTO));
		}
	}
}

//
//	Refresh the Driver dialog
//
void OnRefreshDialog(HWND hDlg)
{
	DWORD	state;
	DWORD	ret;

	//	Apply button is disabled

	EnableWindow(GetDlgItem(hDlg, IDC_APPLY),			FALSE);

	//
	//	Get the current driver status
	//
	ret = VfdGetDriverState(&state);

	if (ret != ERROR_SUCCESS) {
		VFDTRACE(0,("OnVfdRefresh : VfdGetDriverState - %s",
			GetSystemMessage(ret)));
		return;
	}

	if (state == VFD_NOT_INSTALLED) {

		//	The driver is not installed
		//	- configure controls are enabled

		SendDlgItemMessage(hDlg, IDC_DRIVER_PATH, EM_SETREADONLY, 0, 0);

		EnableWindow(GetDlgItem(hDlg, IDC_BROWSE),			TRUE);
//		EnableWindow(GetDlgItem(hDlg, IDC_START_MANUAL),	TRUE);
//		EnableWindow(GetDlgItem(hDlg, IDC_START_AUTO),		TRUE);

		//	stop / remove buttons are disabled

		EnableWindow(GetDlgItem(hDlg, IDC_STOP),			FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_REMOVE),			FALSE);

		//	start and install buttons are enabled/disabled according
		//	to the path in the edit box

		OnPathChanged(hDlg, GetDlgItem(hDlg, IDC_DRIVER_PATH));
	}
	else {

		//	the driver is installed

		BOOL	start, stop;
		TCHAR	path[MAX_PATH];
		DWORD	start_type;

		//	get driver configuration

		ret = VfdGetDriverConfig(path, &start_type);

		if (ret == ERROR_SUCCESS) {

			//	set driver path into the edit box

			SetDlgItemText(hDlg, IDC_DRIVER_PATH, path);

			//	set start type radio button

			switch (start_type) {
			case SERVICE_AUTO_START:
			case SERVICE_SYSTEM_START:
				CheckRadioButton(hDlg, IDC_START_MANUAL,
					IDC_START_AUTO, IDC_START_AUTO);
				break;

			case SERVICE_DEMAND_START:
				CheckRadioButton(hDlg, IDC_START_MANUAL,
					IDC_START_AUTO, IDC_START_MANUAL);
				break;
			}
		}
		else {
			VFDTRACE(0,("OnDriveRefresh: VfdGetDriverConfig - %s",
				GetSystemMessage(ret)));
		}

		if (state == SERVICE_RUNNING) {

			//	the driver is running

			start	= FALSE;		// start button is disabled
			stop	= TRUE;			// stop button is enabled
		}
		else if (state == SERVICE_STOPPED ||
			state == SERVICE_PAUSED) {

			//	the driver is not running

			if (VfdCheckDriverFile(path, NULL) == ERROR_SUCCESS) {
				start	= TRUE;		// the driver path is valid
			}
			else {
				start	= FALSE;	// the driver path is not valid
			}

			stop	= FALSE;		// stop button is disabled
		}
		else {
			//	The driver is in pending state
			//	- cannot be started nor stopped

			start	= FALSE;
			stop	= FALSE;
		}

		//
		//	enable / disable controls according to current state
		//

		SendDlgItemMessage(hDlg, IDC_DRIVER_PATH, EM_SETREADONLY, TRUE, 0);

		EnableWindow(GetDlgItem(hDlg, IDC_BROWSE),			FALSE);
//		EnableWindow(GetDlgItem(hDlg, IDC_START_MANUAL),	TRUE);
//		EnableWindow(GetDlgItem(hDlg, IDC_START_AUTO),		TRUE);

		EnableWindow(GetDlgItem(hDlg, IDC_INSTALL),			FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_REMOVE),			TRUE);

		EnableWindow(GetDlgItem(hDlg, IDC_START),			start);
		EnableWindow(GetDlgItem(hDlg, IDC_STOP),			stop);
	}

	return;
}

//
//	Install the driver
//
BOOL InstallDriver(HWND hDlg)
{
	DWORD	state;
	TCHAR	path[MAX_PATH];
	DWORD	start_type;
	DWORD	ret;

	//	get current driver state

	ret = VfdGetDriverState(&state);

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_DRIVER_INSTALL);
		return FALSE;
	}

	if (state != VFD_NOT_INSTALLED) {
		//	already installed
		return TRUE;
	}

	//	get path text from the edit box

	if (!GetDlgItemText(hDlg, IDC_DRIVER_PATH, path, sizeof(path))) {
		AppendLogMessage(GetLastError(), MSG_ERR_DRIVER_INSTALL);
		return FALSE;
	}

	//	get start type

	if (IsDlgButtonChecked(hDlg, IDC_START_AUTO) == BST_CHECKED) {
		if (IS_WINDOWS_NT()) {

			//	On Windows NT, SYSTEM start drivers must be placed
			//	under the winnt\system32 directory.  Since I don't
			//	care to handle driver file copying, I use the AUTO
			//	start method for Windows NT.

			start_type = SERVICE_AUTO_START;
		}
		else {

			//	On Windows XP, the VFD driver must be running when
			//	the shell starts -- otherwise the shell doesn't
			//	recognize the VFD drives.  Since Windows XP allows
			//	SYSTEM start drivers to be placed in any local
			//	directories, I use the SYSTEM start method here.
			//
			//	This is not an issue when the driver is started
			//	manually because in that case VFD.EXE and VFDWIN.EXE
			//	notify the shell of the VFD drives.
			//
			//	On Windows 2000 both SYSTEM and AUTO work fine.

//			start_type = SERVICE_SYSTEM_START;
			start_type = SERVICE_AUTO_START;
		}
	}
	else {
		start_type = SERVICE_DEMAND_START;
	}

	//	install the driver

	ret = VfdInstallDriver(path, start_type);

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_DRIVER_INSTALL);
		return FALSE;
	}

	//	succeeded

	return TRUE;
}

//
//	Remove the driver
//
BOOL RemoveDriver(HWND hDlg)
{
	DWORD	state;
	DWORD	ret;

	//	get current driver status

	ret = VfdGetDriverState(&state);

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_DRIVER_REMOVE);
		return FALSE;
	}

	if (state == VFD_NOT_INSTALLED) {
		return TRUE;	//	not installed
	}

	//	ensure the driver is stopped

	if (state != SERVICE_STOPPED && !StopDriver(hDlg) &&
		!ConfirmContinue(hDlg, MSG_CONFIRM_REMOVE, FALLBACK_CONFIRM_REMOVE)) {

		AppendLogMessage(0, MSG_ERR_DRIVER_REMOVE);
		return FALSE;
	}

	//	remove the driver

	ret = VfdRemoveDriver();

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_DRIVER_REMOVE);
		return FALSE;
	}

	//	succeeded

	return TRUE;
}

//
//	start the driver
//
BOOL StartDriver(HWND hDlg)
{
	DWORD	state;
	DWORD	ret;

	//	get current driver state

	ret = VfdGetDriverState(&state);

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_DRIVER_START);
		return FALSE;
	}

	if (state == SERVICE_RUNNING) {
		return TRUE;	// already running
	}

	//	ensure the driver is installed

	if (state == VFD_NOT_INSTALLED && !InstallDriver(hDlg)) {
		AppendLogMessage(0, MSG_ERR_DRIVER_START);
		return FALSE;
	}

	//	start the driver

	ret = VfdStartDriver(NULL);

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_DRIVER_START);
		return FALSE;
	}

	//	succeeded

	return TRUE;
}

//
//	stop the driver
//
BOOL StopDriver(HWND hDlg)
{
	DWORD	state;
	ULONG	drive;
	DWORD	ret;

	//	get current driver state

	ret = VfdGetDriverState(&state);

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_DRIVER_STOP);
		return FALSE;
	}

	if (state == SERVICE_STOPPED) {
		return TRUE;	// not running
	}

	//
	//	ensure that all drives are empty
	//
	for (drive = 0; drive < VFD_MAXIMUM_DEVICES; drive++) {

		ret = VfdGuiClose(hDlg, drive);

		if (ret != ERROR_SUCCESS && ret != ERROR_NOT_READY) {
			AppendLogMessage(0, MSG_ERR_DRIVER_STOP);
			return FALSE;
		}
	}

	//	stop the driver

	ret = VfdStopDriver(NULL);

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_DRIVER_STOP);
		return FALSE;
	}

	//	succeeded

	return TRUE;
}

//
//	Configure the driver
//
BOOL ConfigDriver(HWND hDlg)
{
	DWORD	state;
	DWORD	start_type;
	DWORD	ret;

	//	get current driver state

	ret = VfdGetDriverState(&state);

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_DRIVER_INSTALL);
		return FALSE;
	}

	//	get start type

	if (IsDlgButtonChecked(hDlg, IDC_START_AUTO) == BST_CHECKED) {
		if (IS_WINDOWS_NT()) {

			//	On Windows NT, SYSTEM start drivers must be placed
			//	under the winnt\system32 directory.  Since I don't
			//	care to handle driver file copying, I use the AUTO
			//	start method for Windows NT.

			start_type = SERVICE_AUTO_START;
		}
		else {

			//	On Windows XP, the VFD driver must be running when
			//	the shell starts -- otherwise the shell doesn't
			//	recognize the VFD drives.  Since Windows XP allows
			//	SYSTEM start drivers to be placed in any local
			//	directories, I use the SYSTEM start method here.
			//
			//	This is not an issue when the driver is started
			//	manually because in that case VFD.EXE and VFDWIN.EXE
			//	notify the shell of the VFD drives.
			//
			//	On Windows 2000 both SYSTEM and AUTO work fine.

//			start_type = SERVICE_SYSTEM_START;
			start_type = SERVICE_AUTO_START;
		}
	}
	else {
		start_type = SERVICE_DEMAND_START;
	}

	//	configure the driver

	ret = VfdConfigDriver(start_type);

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_DRIVER_CONFIG);
		return FALSE;
	}

	//	succeeded

	return TRUE;
}

//	Ask whether to proceed when the current image cannot be closed
//	or the driver cannot be stopped

BOOL ConfirmContinue(HWND hDlg, UINT msg, PCSTR fallback)
{
	PSTR str;
	int ret;

	if (!FormatMessage(
		FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		hAppInst, msg, 0, (LPTSTR)&str, 0, NULL)) {

		VFDTRACE(0,("ConfirmRemove: FormatMessage - %s",
			GetSystemMessage(GetLastError())));

		str = NULL;
	}

	ret = MessageBox(hDlg, str ? str : fallback,
		VFDWIN_APP_BASENAME, MB_ICONQUESTION | MB_YESNO);

	if (str) {
		LocalFree(str);
	}

	return (ret == IDYES);
}
