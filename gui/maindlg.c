/*
	maindlg.c

	Virtual Floppy Drive for Windows
	GUI Control Panel
	main dialog functions

	Copyright (C) 2003-2005 Ken Kato
*/

#ifdef __cplusplus
#pragma message( __FILE__ ": Compiled as C++ for testing purpose.\n" )
#endif	// __cplusplus

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(push,3)
#include <commctrl.h>
#pragma warning(pop)

#include "vfdtypes.h"
#include "vfdapi.h"
#include "vfdwin.h"
#include "vfdmsg.h"
#include "resource.h"

//
//	child dialogs enumeration
//
enum {
	VFD_CHILD_DRIVE0 = 0,		// Drive 0 dialog
	VFD_CHILD_DRIVE1,			// Drive 1 dialog
	VFD_CHILD_DRIVER,			// Driver dialog
	VFD_CHILD_ASSOC,			// Association dialog
	VFD_CHILD_SHELL,			// Shell dialog
	VFD_CHILD_ABOUT,			// About dialog
	VFD_CHILD_MAX
};

//
//	Constant table for child dialog creation
//
static const struct _CHILD_TABLE {
	UINT	nTitleStr;			// Dialog title string
	UINT	nDlgTempl;			// Dialog template
	DLGPROC	pDlgProc;			// Dialog procedure
	PCSTR	sFallback;			// fallback title string
}
ChildTable[VFD_CHILD_MAX] = {
	{ MSG_DRIVE0_TITLE,	IDD_IMAGE,	ImageProc,	"Drive0"		},
	{ MSG_DRIVE1_TITLE,	IDD_IMAGE,	ImageProc,	"Drive1"		},
	{ MSG_DRIVER_TITLE,	IDD_DRIVER,	DriverProc,	"Driver"		},
	{ MSG_ASSOC_TITLE,	IDD_ASSOC,	AssocProc,	"Association"	},
	{ MSG_SHELL_TITLE,	IDD_SHELL,	ShellProc,	"Shell"			},
	{ MSG_ABOUT_TITLE,	IDD_ABOUT,	AboutProc,	"About"			},
};

//
//	child dialogs
//
static int	nChildIdx = 0;				// cuurent active child
static HWND hChildWnd[VFD_CHILD_MAX] = { 0 };

//
//	window message handlers
//
static void OnInitDialog(HWND hDlg);
static void OnTabNotify	(HWND hDlg, LPNMHDR pNMHDR);
static void OnVfdRefresh(HWND hDlg, WPARAM reason, LPARAM param);

static DWORD WINAPI WatchDriverState(LPVOID param);

static void ShowContextMenu(
	HWND	hDlg,
	HWND	hCtrl,
	LPARAM	lParam);

static void ShowHelpWindow(HWND hDlg, UINT nCtrl);

//
//	Main Dialog Procedure
//
BOOL CALLBACK MainProc(
	HWND hDlg,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	static UINT uDeviceMsg = 0;	// VFD broadcast message

	switch (msg) {
	case WM_INITDIALOG:
		uDeviceMsg = VfdGetNotifyMessage();

		OnInitDialog(hDlg);
		break;

	case WM_CLOSE:
		DestroyWindow(hDlg);
		break;

	case WM_NOTIFY:
		if (wParam == IDC_TAB_CONTROL) {
			OnTabNotify(hDlg, (LPNMHDR)lParam);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_REFRESH:
			OnVfdRefresh(hDlg, VFD_OPERATION_NONE, 0);
			break;
		}
		break;

	case WM_CONTEXTMENU:
		ShowContextMenu(
			hChildWnd[nChildIdx],
			(HWND)wParam, lParam);
		break;

	case WM_HELP:
		{
			LPHELPINFO info = (LPHELPINFO)lParam;

			if (info->iContextType == HELPINFO_WINDOW) {
				ShowHelpWindow(
					GetParent((HWND)info->hItemHandle),
					info->iCtrlId);
			}
		}
		return TRUE;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		if (msg == uDeviceMsg) {
			OnVfdRefresh(hDlg, wParam, lParam);
		}
		break;
	}

	return 0;
}

//
//	Main Dialog Initialize
//
void OnInitDialog(
	HWND	hDlg)
{
	TCITEM	item;
	CHAR	title[50];
	HWND	hTab;
	RECT	rect;
	DWORD	i;
	HICON	hIcon;
	HMENU	hMenu;
	DWORD	err;
	POINT	pt;

	//
	//	Set Window Title
	//
	if (GetLocalMessage(MSG_APPLICATION_TITLE, title, sizeof(title), "")) {
		SetWindowText(hDlg, title);
	}

	//
	//	Set Window icon
	//
	hIcon = (HICON)LoadImage(hAppInst,
		MAKEINTRESOURCE(IDI_CONFIG_ICON),
		IMAGE_ICON, 16, 16, 0);

	if (hIcon) {
		SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	}

	//
	//	Adjust system menu (required for Windows NT, because
	//	Miximize and Size system menu commands are displayed
	//	even though they are disabled in the dialog resource)
	//
	hMenu = GetSystemMenu(hDlg, FALSE);

	if (hMenu) {
		DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
		DeleteMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
	}

	//
	//	Prepare tab control
	//
	hTab = GetDlgItem(hDlg, IDC_TAB_CONTROL);

	if (hTab == NULL) {
		err = GetLastError();

		VFDTRACE(0,("OnMainInitDialog : GetDlgItem - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	memset(&item, 0, sizeof(item));
	item.mask = TCIF_TEXT;
	item.pszText = title;

	for (i = 0; i < VFD_CHILD_MAX; i++) {
		if (!GetLocalMessage(ChildTable[i].nTitleStr, title, sizeof(title))) {

			VFDTRACE(0,("%s", GetSystemMessage(GetLastError())));

			strcpy(title, ChildTable[i].sFallback);
		}

		if (TabCtrl_InsertItem(hTab, i, &item) == -1) {
			err = GetLastError();

			VFDTRACE(0,("%s", GetSystemMessage(err)));

			ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

			return;
		}
	}

	//
	//	Calculate Tab control's client area
	//
	if (!GetWindowRect(hTab, &rect)) {
		err = GetLastError();

		VFDTRACE(0,("OnMainInitDialog : GetWindowRect - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	pt.x = rect.left;
	pt.y = rect.top;

	if (!ScreenToClient(hDlg, &pt)) {
		err = GetLastError();

		VFDTRACE(0,("OnMainInitDialog : ScreenToClient - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	rect.left = pt.x;
	rect.top = pt.y;

	pt.x = rect.right;
	pt.y = rect.bottom;

	if (!ScreenToClient(hDlg, &pt)) {
		err = GetLastError();

		VFDTRACE(0,("OnMainInitDialog : ScreenToClient - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	rect.right = pt.x;
	rect.bottom = pt.y;

	TabCtrl_AdjustRect(hTab, FALSE, &rect);

	//
	//	Create each child dialog
	//
	for (i = 0; i < VFD_CHILD_MAX; i++) {

		hChildWnd[i] = CreateDialogParam(
			hAppInst,
			MAKEINTRESOURCE(ChildTable[i].nDlgTempl),
			hDlg,
			ChildTable[i].pDlgProc,
			i);

		if (hChildWnd[i] == NULL) {
			err = GetLastError();

			VFDTRACE(0,("OnMainInitDialog : CreateDialog - %s",
				GetSystemMessage(err)));

			ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

			continue;
		}

		if (!SetWindowPos(hChildWnd[i], NULL, rect.left,
			rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE)) {

			err = GetLastError();

			VFDTRACE(0,("OnMainInitDialog : SetWindowPos - %s",
				GetSystemMessage(err)));

			ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

			continue;
		}
	}

	//
	//	Show initial child
	//
	VfdGetDriverState(&i);

	if (i == SERVICE_RUNNING) {
		nChildIdx = VFD_CHILD_DRIVE0;
	}
	else {
		nChildIdx = VFD_CHILD_DRIVER;
	}

	TabCtrl_SetCurSel(hTab, nChildIdx);
	ShowWindow(hChildWnd[nChildIdx], SW_SHOW);
	SetFocus(hChildWnd[nChildIdx]);

	//
	//	Get latest driver status
	//
	OnVfdRefresh(hDlg, VFD_OPERATION_NONE, 0);

	return;
}

//
//	Switch child dialog according to currently selected tab
//
void OnTabNotify(HWND hDlg, LPNMHDR pNMHDR)
{
	if (pNMHDR->code == TCN_SELCHANGE) {

		int idx  = TabCtrl_GetCurSel(pNMHDR->hwndFrom);

		if (idx >= 0 && idx < VFD_CHILD_MAX && idx != nChildIdx) {

			// selected tab is actually changed, so switch child dialog
			ShowWindow(hChildWnd[idx], SW_SHOW);
			ShowWindow(hChildWnd[nChildIdx], SW_HIDE);

			ShowWindow(GetDlgItem(hDlg, IDC_LOG_MESSAGE),
				idx <= VFD_CHILD_DRIVER ? SW_SHOW : SW_HIDE);

			nChildIdx = idx;

			SetFocus(pNMHDR->hwndFrom);
		}
	}
}

//
//	refreshes state text and child windows
//
void OnVfdRefresh(HWND hDlg, WPARAM reason, LPARAM param)
{
	static HANDLE hWatchThread = NULL;
	DWORD	driver_state;
	DWORD	driver_version = 0;
	DWORD	ret;
	UINT	msgid;
	HANDLE	hDevice = INVALID_HANDLE_VALUE;
	DWORD	media_state = ERROR_NOT_READY;
	BOOL	pending = FALSE;
	int		i;

	//
	//	is previous watch thread still alive?
	//
	if (hWatchThread) {
		if (!GetExitCodeThread(hWatchThread, &ret) ||
			ret != STILL_ACTIVE) {
			//	the watch thread is already terminated
			CloseHandle(hWatchThread);
			hWatchThread = NULL;
		}
	}

	//
	//	Print driver status on the status line
	//
	ret = VfdGetDriverState(&driver_state);

	if (ret != ERROR_SUCCESS) {
		VFDTRACE(0,("OnVfdRefresh : VfdGetDriverState - %s", ret));
		return;
	}

	switch (driver_state) {
	case SERVICE_STOPPED:
		msgid = MSG_STAT_DRIVER_STOPPED;
		break;

	case SERVICE_START_PENDING:
		msgid = MSG_STAT_DRIVER_START_PENDING;
		break;

	case SERVICE_STOP_PENDING:
		msgid = MSG_STAT_DRIVER_STOP_PENDING;
		break;

	case SERVICE_RUNNING:
		msgid = MSG_STAT_DRIVER_RUNNING;

		hDevice = VfdOpenDevice(param);

		if (hDevice != INVALID_HANDLE_VALUE) {
			VfdGetDriverVersion(hDevice, &driver_version);
			media_state = VfdGetMediaState(hDevice);
			CloseHandle(hDevice);
		}
		break;

	case SERVICE_CONTINUE_PENDING:
		msgid = MSG_STAT_DRIVER_CONTINUE_PENDING;
		break;

	case SERVICE_PAUSE_PENDING:
		msgid = MSG_STAT_DRIVER_PAUSE_PENDING;
		break;

	case SERVICE_PAUSED:
		msgid = MSG_STAT_DRIVER_PAUSED;
		break;

	case VFD_NOT_INSTALLED:
		msgid = MSG_STAT_DRIVER_NOT_INSTALLED;
		break;

	default:
		driver_state = 0;
		msgid = MSG_STAT_DRIVER_UNKNOWN_STATE;
		break;
	}

	SetControlText(hDlg, IDC_CURRENT_STATE, msgid,
		HIWORD(driver_version) & 0x7fff,
		LOWORD(driver_version),
		(driver_version & 0x80000000) ? " (debug)" : "");

	//
	//	Print performed operation in the log window
	//
	msgid = 0;

	switch (reason) {
	case VFD_OPERATION_INSTALL:
		if (driver_state != VFD_NOT_INSTALLED) {
			msgid = MSG_LOG_DRIVER_INSTALLED;
		}
		break;

	case VFD_OPERATION_CONFIG:
		msgid = MSG_LOG_DRIVER_CONFIGURED;
		break;

	case VFD_OPERATION_REMOVE:
		if (driver_state == VFD_NOT_INSTALLED) {
			msgid = MSG_LOG_DRIVER_REMOVED;
		}
		else {
			msgid = MSG_LOG_DRIVER_REMOVE_PENDING;
			pending = TRUE;
		}
		break;

	case VFD_OPERATION_START:
		if (driver_state == SERVICE_RUNNING) {
			msgid = MSG_LOG_DRIVER_STARTED;
		}
		else if (driver_state == SERVICE_START_PENDING) {
			msgid = MSG_LOG_DRIVER_START_PENDING;
			pending = TRUE;
		}
		break;

	case VFD_OPERATION_STOP:
		if (driver_state == SERVICE_STOPPED ||
			driver_state == VFD_NOT_INSTALLED) {
			msgid = MSG_LOG_DRIVER_STOPPED;
		}
		else if (driver_state == SERVICE_STOP_PENDING) {
			msgid = MSG_LOG_DRIVER_STOP_PENDING;
			pending = TRUE;
		}
		break;

	case VFD_OPERATION_OPEN:
		if (media_state == ERROR_SUCCESS ||
			media_state == ERROR_WRITE_PROTECT) {
			msgid = MSG_LOG_IMAGE_OPENED;
		}
		break;

	case VFD_OPERATION_CLOSE:
		if (media_state != ERROR_SUCCESS &&
			media_state != ERROR_WRITE_PROTECT) {
			msgid = MSG_LOG_IMAGE_CLOSED;
		}
		break;

	case VFD_OPERATION_SETLINK:
		msgid = MSG_LOG_LETTER_ASSIGNED;
		break;

	case VFD_OPERATION_DELLINK:
		msgid = MSG_LOG_LETTER_REMOVED;
		break;

	case VFD_OPERATION_PROTECT:
		if (media_state == ERROR_SUCCESS) {
			msgid = MSG_LOG_PROTECT_DISABLED;
		}
		else if (media_state == ERROR_WRITE_PROTECT) {
			msgid = MSG_LOG_PROTECT_ENABLED;
		}
		break;
	}

	if (msgid) {
		AppendLogMessage(0, msgid, param);
	}

	//	Refresh child dialogs

	for (i = 0; i < VFD_CHILD_MAX; i++) {
		SendMessage(hChildWnd[i], VFD_REFRESH_MSG, 0, 0);
	}

	//	start a watch thread if not already watching

	if (pending && !hWatchThread) {
		hWatchThread = CreateThread(
			NULL, 0, WatchDriverState, (LPVOID)driver_state, 0, NULL);
	}
}

//
//	watch driver state thread routine
//
DWORD WINAPI WatchDriverState(LPVOID param)
{
	DWORD ret;
	DWORD state;
	ULONG reason;

	do {
		Sleep(1000);

		ret = VfdGetDriverState(&state);

		if (ret != ERROR_SUCCESS) {
			VFDTRACE(0,("WatchDriverState : VfdGetDriverState - %s", ret));
			return 0;
		}
	}
	while (state == (DWORD)param);

	if (state == SERVICE_RUNNING) {
		reason = VFD_OPERATION_START;
	}
	else if (state == SERVICE_STOPPED) {
		reason = VFD_OPERATION_STOP;
	}
	else if (state == VFD_NOT_INSTALLED) {
		reason = VFD_OPERATION_REMOVE;
	}
	else {
		reason = VFD_OPERATION_NONE;
	}

	PostMessage(hMainWnd, VfdGetNotifyMessage(), reason, 0);

	return 0;
}

void ShowContextMenu(
	HWND	hDlg,
	HWND	hCtrl,
	LPARAM	lParam)
{
	POINT	pt;
	UINT	id;
	HMENU	hMenu;

	pt.x = ((int)(short)LOWORD(lParam));
	pt.y = ((int)(short)HIWORD(lParam));

	if (pt.x == -1 || pt.y == -1) {
		RECT rc;

		GetWindowRect(hCtrl, &rc);
		pt.x = (rc.left + rc.right) / 2;
		pt.y = (rc.top + rc.bottom) / 2;

		id = GetDlgCtrlID(hCtrl);
	}
	else {
		POINT pt2 = pt;

		ScreenToClient(hDlg, &pt2);

		id = GetDlgCtrlID(ChildWindowFromPoint(hDlg, pt2));
	}

	if (id < IDC_TAB_CONTROL ||
		id > IDC_PERSISTENT) {
		return;
	}

	hMenu = CreatePopupMenu();

	AppendMenu(hMenu, MF_STRING, 1, "&What's This");

	if (TrackPopupMenu(hMenu, TPM_RETURNCMD,
		pt.x, pt.y, 0, hDlg, NULL))
	{
		ShowHelpWindow(hDlg, id);
	}

	DestroyMenu(hMenu);
}

//
//	Show tool tip help
//
void ShowHelpWindow(HWND hDlg, UINT nCtrl)
{
	CHAR buf[MAX_PATH];
	UINT msg;
	RECT rc;

	switch (nCtrl) {
	case  IDC_TAB_CONTROL:
		msg = MSG_HELP_TAB_CONTROL;
		break;
	case  IDC_LOG_MESSAGE:
		msg = MSG_HELP_LOG_MESSAGE;
		break;
	case  IDC_CURRENT_STATE:
		msg = MSG_HELP_STATE;
		break;
	case  IDC_LETTER_LABEL:
	case  IDC_DRIVE_LETTER:
		msg = MSG_HELP_LETTER;
		break;
	case  IDC_CHANGE:
		msg = MSG_HELP_CHANGE;
		break;
	case  IDC_IMAGEFILE_LABEL:
	case  IDC_IMAGEFILE:
		msg = MSG_HELP_IMAGEFILE;
		break;
	case  IDC_DESCRIPTION_LABEL:
	case  IDC_DESCRIPTION:
		msg = MSG_HELP_DESCRIPTION;
		break;
	case  IDC_DISKTYPE_LABEL:
	case  IDC_DISKTYPE:
		msg = MSG_HELP_DISKTYPE;
		break;
	case  IDC_MEDIATYPE_LABEL:
	case  IDC_MEDIATYPE:
		msg = MSG_HELP_MEDIATYPE;
		break;
	case  IDC_PROTECT:
		msg = MSG_HELP_PROTECT;
		break;
	case  IDC_OPEN:
		msg = MSG_HELP_OPEN;
		break;
	case  IDC_SAVE:
		msg = MSG_HELP_SAVE;
		break;
	case  IDC_CLOSE:
		msg = MSG_HELP_CLOSE;
		break;
	case  IDC_FORMAT:
		msg = MSG_HELP_FORMAT;
		break;
	case  IDC_DRIVER_LABEL:
	case  IDC_DRIVER_PATH:
		msg = MSG_HELP_DRIVER;
		break;
	case  IDC_BROWSE:
		msg = MSG_HELP_BROWSE;
		break;
	case  IDC_VERSION_LABEL:
	case  IDC_VERSION:
		msg = MSG_HELP_VERSION;
		break;
	case  IDC_START_LABEL:
	case  IDC_START_MANUAL:
	case  IDC_START_AUTO:
		msg = MSG_HELP_STARTTYPE;
		break;
	case  IDC_INSTALL:
		msg = MSG_HELP_INSTALL;
		break;
	case  IDC_START:
		msg = MSG_HELP_START;
		break;
	case  IDC_STOP:
		msg = MSG_HELP_STOP;
		break;
	case  IDC_REMOVE:
		msg = MSG_HELP_REMOVE;
		break;
	case  IDC_ASSOC_LIST:
		msg = MSG_HELP_LIST;
		break;
	case  IDC_ASSOC_MESSAGE:
		msg = MSG_HELP_MESSAGE;
		break;
	case  IDC_NEW:
		msg = MSG_HELP_NEW;
		break;
	case  IDC_ALL:
		msg = MSG_HELP_ALL;
		break;
	case  IDC_CLEAR:
		msg = MSG_HELP_CLEAR;
		break;
	case  IDC_APPLY:
		msg = MSG_HELP_APPLY;
		break;
	case  IDC_SHELL_TREE:
		msg = MSG_HELP_TREE;
		break;
	case  IDC_ABOUT_TITLE:
		msg = MSG_HELP_PRODUCT;
		break;
	case  IDC_ABOUT_URL:
		msg = MSG_HELP_URL;
		break;
	case  IDC_ABOUT_HELP:
		msg = MSG_HELP_HELP;
		break;
	case  IDC_ABOUT_COPYRIGHT:
		msg = MSG_HELP_COPYRIGHT;
		break;
	case  IDC_NEWEXT_LABEL:
	case  IDC_EXTENSION:
		msg = MSG_HELP_EXTENSION;
		break;
	case  IDC_PERSISTENT:
		msg = MSG_HELP_PERSISTENT;
		break;
	default:
		return;
	}

	GetLocalMessage(msg, buf, sizeof(buf));

	GetWindowRect(GetDlgItem(hDlg, nCtrl), &rc);

	VfdToolTip(hDlg, buf, rc.left, (rc.top + rc.bottom) / 2, TRUE);
}

