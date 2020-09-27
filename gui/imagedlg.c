/*
	imagedlg.c

	Virtual Floppy Drive for Windows
	GUI Control Panel
	"Image" dialog functions

	Copyright (C) 2003-2005 Ken Kato
*/

#ifdef __cplusplus
#pragma message( __FILE__ ": Compiled as C++ for testing purpose.\n" )
#endif	// __cplusplus

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

#include "vfdtypes.h"
#include "vfdapi.h"
#include "vfdwin.h"
#include "vfdmsg.h"
#include "resource.h"

#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES	(DWORD)-1
#endif	//	INVALID_FILE_ATTRIBUTES
//
//	Windows message handlers
//
static void OnInitDialog	(HWND hDlg, LPARAM lParam);

static void OnChangeClicked	(HWND hDlg);
static void OnProtectClicked(HWND hDlg, HWND hButton);
static void OnOpenClicked	(HWND hDlg, HWND hButton);
static void OnSaveClicked	(HWND hDlg);
static void OnCloseClicked	(HWND hDlg, HWND hButton);
static void OnFormatClicked	(HWND hDlg);
static void OnRefreshDialog	(HWND hDlg);

//	Drive letter change dialog

static BOOL CALLBACK LetterProc(
	HWND hDlg,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

static BOOL OnLetterInit	(HWND hDlg, ULONG nDrive);
static void OnLetterChange	(HWND hDlg);
static void OnLetterOK		(HWND hDlg);

//
//	window message dispatcher
//
BOOL CALLBACK ImageProc(
	HWND	hDlg,
	UINT	msg,
	WPARAM	wParam,
	LPARAM	lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		OnInitDialog(hDlg, lParam);
		break;

	case WM_COMMAND:
		switch (wParam) {
		case IDC_CHANGE:
			OnChangeClicked(hDlg);
			break;

		case IDC_PROTECT:
			OnProtectClicked(hDlg, (HWND)lParam);
			break;

		case IDC_OPEN:
			OnOpenClicked(hDlg, (HWND)lParam);
			break;

		case IDC_SAVE:
			OnSaveClicked(hDlg);
			break;

		case IDC_CLOSE:
			OnCloseClicked(hDlg, (HWND)lParam);
			break;

		case IDC_FORMAT:
			OnFormatClicked(hDlg);
			break;
		}
		break;

	case WM_SHOWWINDOW:
		if (!wParam) {
			//	the window is being hidden
			break;
		}
		//	the window is being shown - refresh

	case VFD_REFRESH_MSG:
		OnRefreshDialog(hDlg);
		break;
	}

	return 0;
}

//
//	initialize image dialog
//
void OnInitDialog(HWND hDlg, LPARAM lParam)
{
	//	store the device number

	SetWindowLong(hDlg, GWL_USERDATA, lParam);

	//	set controls text

	SetControlText(hDlg, IDC_LETTER_LABEL,		MSG_LETTER_LABEL);
	SetControlText(hDlg, IDC_CHANGE,			MSG_CHANGE_BUTTON);
	SetControlText(hDlg, IDC_IMAGEFILE_LABEL,	MSG_IMAGEFILE_LABEL);
	SetControlText(hDlg, IDC_DESCRIPTION_LABEL,	MSG_DESCRIPTION_LABEL);
	SetControlText(hDlg, IDC_DISKTYPE_LABEL,	MSG_DISKTYPE_LABEL);
	SetControlText(hDlg, IDC_MEDIATYPE_LABEL,	MSG_MEDIATYPE_LABEL);
	SetControlText(hDlg, IDC_PROTECT,			MSG_PROTECT_BUTTON);
	SetControlText(hDlg, IDC_OPEN,				MSG_OPEN_BUTTON);
	SetControlText(hDlg, IDC_SAVE,				MSG_SAVE_BUTTON);
	SetControlText(hDlg, IDC_CLOSE,				MSG_CLOSE_BUTTON);
	SetControlText(hDlg, IDC_FORMAT,			MSG_FORMAT_BUTTON);
}

//
//	Image path is changed
//
void OnChangeClicked(HWND hDlg)
{
	DialogBoxParam(hAppInst, MAKEINTRESOURCE(IDD_LETTER),
		hDlg, LetterProc, GetWindowLong(hDlg, GWL_USERDATA));
}

//
//	protect button is clicked
//
void OnProtectClicked(HWND hDlg, HWND hButton)
{
	HANDLE	hDevice;
	DWORD	ret;

	hDevice = VfdOpenDevice(
		GetWindowLong(hDlg, GWL_USERDATA));

	if (hDevice != INVALID_HANDLE_VALUE) {

		if (SendMessage(hButton, BM_GETCHECK, 0, 0) == BST_CHECKED) {
			ret = VfdWriteProtect(hDevice, TRUE);
		}
		else {
			ret = VfdWriteProtect(hDevice, FALSE);
		}

		CloseHandle(hDevice);
	}
	else {
		ret = GetLastError();
	}

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, MSG_ERR_CHANGE_PROTECT);
	}
}

//
//	Open button is clicked
//
void OnOpenClicked(HWND hDlg, HWND hButton)
{
	DWORD	ret;

	ret = VfdGuiOpen(hDlg, GetWindowLong(hDlg, GWL_USERDATA));

	if (ret == ERROR_SUCCESS) {
		SendMessage(hButton, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);
		SetFocus(GetDlgItem(hDlg, IDC_CLOSE));
	}
	else if (ret != ERROR_CANCELLED) {
		AppendLogMessage(ret, MSG_ERR_IMAGE_OPEN, "");
	}
}

//
//	Save button is clicked
//
void OnSaveClicked(HWND hDlg)
{
	DWORD ret;

	ret = VfdGuiSave(hDlg, GetWindowLong(hDlg, GWL_USERDATA));

	if (ret == ERROR_SUCCESS) {
		AppendLogMessage(0, MSG_IMAGE_SAVED);
	}
	else if (ret != ERROR_CANCELLED) {
		AppendLogMessage(ret, MSG_ERR_IMAGE_SAVE);
	}
}

//
//	Close button is clicked
//
void OnCloseClicked(HWND hDlg, HWND hButton)
{
	DWORD ret;

	ret = VfdGuiClose(hDlg, GetWindowLong(hDlg, GWL_USERDATA));

	if (ret == ERROR_SUCCESS || ret == ERROR_NOT_READY) {
		SendMessage(hButton, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);
		SetFocus(GetDlgItem(hDlg, IDC_OPEN));
	}
	else {
		AppendLogMessage(ret, MSG_ERR_IMAGE_CLOSE,
			GetWindowLong(hDlg, GWL_USERDATA) + '0');
	}
}

//
//	Format button is clicked
//
void OnFormatClicked(HWND hDlg)
{
	DWORD ret;

	ret = VfdGuiFormat(hDlg, GetWindowLong(hDlg, GWL_USERDATA));

	if (ret == ERROR_SUCCESS) {
		AppendLogMessage(0, MSG_IMAGE_FORMATTED);
	}
	else {
		AppendLogMessage(ret, MSG_ERR_IMAGE_FORMAT);
	}
}

//
//	Refresh the Drive dialog
//
void OnRefreshDialog(HWND hDlg)
{
	DWORD			state;
	HANDLE			hDevice;
	CHAR			buf[MAX_PATH];
	VFD_DISKTYPE	disk_type;
	VFD_MEDIA		media_type;
	VFD_FLAGS		media_flags;
	VFD_FILETYPE	file_type;
	ULONG			image_size;
	CHAR			letter;
	DWORD			attrib;
	DWORD			ret;

	//	get the driver state

	ret = VfdGetDriverState(&state);

	if (ret != ERROR_SUCCESS) {
		return;
	}

	if (state != SERVICE_RUNNING) {

		//	the driver is not running
		//	clear all information and disable controls

		SetDlgItemText(hDlg, IDC_DRIVE_LETTER, NULL);
		SetDlgItemText(hDlg, IDC_IMAGEFILE, NULL);
		SetDlgItemText(hDlg, IDC_DISKTYPE,	NULL);
		SetDlgItemText(hDlg, IDC_MEDIATYPE, NULL);
		CheckDlgButton(hDlg, IDC_PROTECT, BST_UNCHECKED);

		EnableWindow(GetDlgItem(hDlg, IDC_CHANGE),	FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_PROTECT), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_OPEN),	FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_SAVE),	FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_CLOSE),	FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_FORMAT),	FALSE);

		return;
	}

	//	open the device

	hDevice = VfdOpenDevice(GetWindowLong(hDlg, GWL_USERDATA));

	if (hDevice == INVALID_HANDLE_VALUE) {
		AppendLogMessage(GetLastError(), 0);
		return;
	}

	//	get the current drive letter

	VfdGetGlobalLink(hDevice, &letter);

	buf[0] = '\0';

	if (isalpha(letter)) {
		sprintf(buf, "%c (", letter);
		GetLocalMessage(MSG_PERSISTENT, &buf[3], sizeof(buf) - 3);
		strcat(buf, ")");
	}
	else {
		VfdGetLocalLink(hDevice, &letter);

		if (isalpha(letter)) {
			sprintf(buf, "%c (", letter);
			GetLocalMessage(MSG_EPHEMERAL, &buf[3], sizeof(buf) - 3);
			strcat(buf, ")");
		}
	}

	SetDlgItemText(hDlg, IDC_DRIVE_LETTER, buf);
	EnableWindow(GetDlgItem(hDlg, IDC_CHANGE),	TRUE);

	//	get the current image information

	ret = VfdGetImageInfo(hDevice, buf, &disk_type,
		&media_type, &media_flags, &file_type, &image_size);

	CloseHandle(hDevice);

	if (ret != ERROR_SUCCESS) {
		AppendLogMessage(ret, 0);
		return;
	}

	if (media_type == VFD_MEDIA_NONE) {

		//	no media

		SetDlgItemText(hDlg, IDC_IMAGEFILE, NULL);
		SetDlgItemText(hDlg, IDC_DESCRIPTION, NULL);
		SetDlgItemText(hDlg, IDC_DISKTYPE,	NULL);
		SetDlgItemText(hDlg, IDC_MEDIATYPE, NULL);

		EnableWindow(GetDlgItem(hDlg, IDC_PROTECT), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_OPEN),	TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_SAVE),	FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_CLOSE),	FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_FORMAT),	FALSE);

		SendMessage(GetDlgItem(hDlg, IDC_OPEN),
			BM_SETSTYLE, BS_DEFPUSHBUTTON, TRUE);

		return;
	}

	//	set image file name

	if (buf[0]) {
		attrib = GetFileAttributes(buf);

		if (attrib == INVALID_FILE_ATTRIBUTES) {
			attrib = 0;
		}
	}
	else {
		if (disk_type != VFD_DISKTYPE_FILE) {
			strcpy(buf, "<RAM>");
		}
		file_type = VFD_FILETYPE_NONE;
		attrib = 0;
	}

	SetDlgItemText(hDlg, IDC_IMAGEFILE, buf);

	//	set description

	VfdMakeFileDesc(buf, sizeof(buf),
		file_type, image_size, attrib);

	SetDlgItemText(hDlg, IDC_DESCRIPTION, buf);

	//	set disk type text

	if (disk_type == VFD_DISKTYPE_FILE) {
		SetDlgItemText(hDlg, IDC_DISKTYPE, "FILE");
	}
	else {
		SetDlgItemText(hDlg, IDC_DISKTYPE, "RAM");
	}

	//	set media type text

	SetDlgItemText(hDlg, IDC_MEDIATYPE,
		VfdMediaTypeName(media_type));

	//	set write protected state

	if (media_flags & VFD_FLAG_WRITE_PROTECTED) {
		CheckDlgButton(hDlg, IDC_PROTECT, BST_CHECKED);
	}
	else {
		CheckDlgButton(hDlg, IDC_PROTECT, BST_UNCHECKED);
	}

	//
	//	enable / disable appropriate buttons
	//
	EnableWindow(GetDlgItem(hDlg, IDC_PROTECT), TRUE);
	EnableWindow(GetDlgItem(hDlg, IDC_OPEN),	FALSE);
	EnableWindow(GetDlgItem(hDlg, IDC_SAVE),	TRUE);
	EnableWindow(GetDlgItem(hDlg, IDC_CLOSE),	TRUE);
	EnableWindow(GetDlgItem(hDlg, IDC_FORMAT),	TRUE);

	SendMessage(GetDlgItem(hDlg, IDC_CLOSE),
		BM_SETSTYLE, BS_DEFPUSHBUTTON, TRUE);
}

//
//	change drive letter dialog procedure
//
BOOL CALLBACK LetterProc(
	HWND	hDlg,
	UINT	msg,
	WPARAM	wParam,
	LPARAM	lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		if (!OnLetterInit(hDlg, lParam)) {
			EndDialog(hDlg, 0);
		}
		return TRUE;

	case WM_COMMAND:
		switch (wParam) {
		case MAKELONG(IDC_DRIVE_LETTER, CBN_SELCHANGE):
		case MAKELONG(IDC_PERSISTENT, BN_CLICKED):
			OnLetterChange(hDlg);
			break;

		case IDOK:
			OnLetterOK(hDlg);
			//	fall through

		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}

	return 0;
}

//
//	initialize the drive letter dialog
//
BOOL OnLetterInit(HWND hDlg, ULONG nDevice)
{
	HANDLE	hDevice;
	CHAR	buf[20];
	HWND	hCombo;
	DWORD	logical;
	BOOL	persistent;

	//
	//	setup controls text
	//
	SetControlText(hDlg, 0,					MSG_LETTER_TITLE);
	SetControlText(hDlg, IDC_LETTER_LABEL,	MSG_LETTER_LABEL);
	SetControlText(hDlg, IDC_PERSISTENT,	MSG_PERSISTENT);
	SetControlText(hDlg, IDOK,				MSG_OK_BUTTON);
	SetControlText(hDlg, IDCANCEL,			MSG_CANCEL_BUTTON);

	//
	//	setup the drive letter combo box
	//
	hCombo = GetDlgItem(hDlg, IDC_DRIVE_LETTER);

	if (hCombo == NULL) {
		ShowErrorMessage(GetLastError(), 0);
		return FALSE;
	}

	//	initialize the list

	SendMessage(hCombo, CB_RESETCONTENT, 0, 0);

	//	add <none>

	if (!GetLocalMessage(MSG_GENERIC_NONE, buf, sizeof(buf))) {
		strcpy(buf, "(none)");
	}

	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)buf);

	//	add unused drive letters

	logical = GetLogicalDrives();

	if (logical == 0) {
		ShowErrorMessage(GetLastError(), 0);
		return FALSE;
	}

	strcpy(buf, "A:");

	while (buf[0] <= 'Z') {
		if (!(logical & 0x01)) {
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)buf);
		}

		logical >>= 1;
		buf[0]++;
	}

	SendMessage(hCombo, CB_SETCURSEL, 0, 0);

	//	Get the drive letter of the VFD drive

	hDevice = VfdOpenDevice(nDevice);

	if (hDevice == INVALID_HANDLE_VALUE) {
		ShowErrorMessage(GetLastError(), MSG_ERR_APP_INTERNAL);
		return FALSE;
	}

	persistent = TRUE;

	VfdGetGlobalLink(hDevice, &buf[0]);

	if (!isalpha(buf[0])) {
		if (VfdGetLocalLink(hDevice, &buf[0]) == ERROR_SUCCESS &&
			isalpha(buf[0])) {
			persistent = FALSE;
		}
	}

	CloseHandle(hDevice);

	if (isalpha(buf[0])) {
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)buf);
		SendMessage(hCombo, CB_SELECTSTRING, (WPARAM)-1, (LPARAM)buf);
	}

	//	set the persistent button state
	CheckDlgButton(hDlg, IDC_PERSISTENT,
		persistent ? BST_CHECKED : BST_UNCHECKED);

	//	store the device number
	SetWindowLong(hDlg, GWL_USERDATA, nDevice);

	//	store the current drive letter
	SetWindowLong(hDlg, DWL_USER, MAKELONG(buf[0], persistent));

	return TRUE;
}

//
//	Drive letter selection is changed
//
void OnLetterChange(HWND hDlg)
{
	BOOL	persistent;
	ULONG	letter;
	CHAR	buf[10];

	//	Get combo box selection

	if (!GetDlgItemText(hDlg, IDC_DRIVE_LETTER, buf, sizeof(buf))) {
		ShowErrorMessage(GetLastError(), MSG_ERR_APP_INTERNAL);
		return;
	}

	//	Get the original drive letter

	letter = GetWindowLong(hDlg, DWL_USER);

	//	Drive letter changed ?

	if (!isalpha(LOWORD(letter)) && !isalpha(buf[0])) {
		EnableWindow(GetDlgItem(hDlg, IDOK), FALSE);
		return;
	}

	if ((LOWORD(letter) != buf[0])) {
		EnableWindow(GetDlgItem(hDlg, IDOK), TRUE);
		return;
	}

	//	Get persistent button state

	persistent = (IsDlgButtonChecked(hDlg, IDC_PERSISTENT) == BST_CHECKED);

	if (isalpha(buf[0]) && (HIWORD(letter) != persistent)) {
		EnableWindow(GetDlgItem(hDlg, IDOK), TRUE);
		return;
	}

	EnableWindow(GetDlgItem(hDlg, IDOK), FALSE);
}

//
//	OK button is clicked
//
void OnLetterOK(HWND hDlg)
{
	HANDLE	hDevice;
	ULONG	letter;
	BOOL	persistent;
	CHAR	buf[10];
	DWORD	ret = ERROR_SUCCESS;

	//	Get combo box selection

	if (!GetDlgItemText(hDlg, IDC_DRIVE_LETTER, buf, sizeof(buf))) {
		ShowErrorMessage(GetLastError(), MSG_ERR_APP_INTERNAL);
		return;
	}

	//	Get persistent button state

	persistent = (IsDlgButtonChecked(hDlg, IDC_PERSISTENT) == BST_CHECKED);

	//	Get the original drive letter

	letter = GetWindowLong(hDlg, DWL_USER);

	//	Open the VFD drive

	hDevice = VfdOpenDevice(
		GetWindowLong(hDlg, GWL_USERDATA));

	if (hDevice == INVALID_HANDLE_VALUE) {
		ShowErrorMessage(GetLastError(), MSG_ERR_APP_INTERNAL);
		return;
	}

	if (isalpha(LOWORD(letter))) {

		// delete the original drive letter

		if (HIWORD(letter)) {
			ret = VfdSetGlobalLink(hDevice, 0);
		}
		else {
			ret = VfdSetLocalLink(hDevice, 0);
		}
	}

	if (ret == ERROR_SUCCESS && isalpha(buf[0])) {

		//	create a new drive letter

		if (persistent) {
			ret = VfdSetGlobalLink(hDevice, buf[0]);
		}
		else {
			ret = VfdSetLocalLink(hDevice, buf[0]);
		}
	}

	CloseHandle(hDevice);

	if (ret != ERROR_SUCCESS) {
		ShowErrorMessage(GetLastError(), MSG_ERR_APP_INTERNAL);
		return;
	}
}

