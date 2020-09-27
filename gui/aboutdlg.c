/*
	aboutdlg.c

	Virtual Floppy Drive for Windows
	GUI Control Panel
	"About" dialog functions

	Copyright (C) 2003-2005 Ken Kato
*/

#ifdef __cplusplus
#pragma message( __FILE__ ": Compiled as C++ for testing purpose.\n" )
#endif	// __cplusplus

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(push,3)
#include <shellapi.h>
#pragma warning(pop)

#include "vfdwin.h"
#include "vfdmsg.h"
#include "vfdver.h"
#include "resource.h"

//
//	local functions
//
static void OnInitDialog(HWND hDlg);
static void OnUrlClick(HWND hDlg);

//
//	About dialog message dispatcher
//
BOOL CALLBACK AboutProc(
	HWND hDlg,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (msg) {
	case WM_INITDIALOG:
		OnInitDialog(hDlg);
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_ABOUT_URL) {
			OnUrlClick(hDlg);
		}
		break;
	}

	return 0;
}

//
//	initialize about tab dialog
//
void OnInitDialog(HWND hDlg)
{
	//	Program name & version

	SetDlgItemText(hDlg, IDC_ABOUT_TITLE, VFD_PRODUCT_DESC);
	SetDlgItemText(hDlg, IDC_ABOUT_COPYRIGHT, VFD_COPYRIGHT_STR);

	//	Web page URL

	SetControlText(hDlg, IDC_ABOUT_URL, MSG_ABOUT_URL);

	//	Command line help

	SetControlText(hDlg, IDC_ABOUT_HELP, MSG_HELP_TEXT);
}

//
//	Goto VFD web page
//
void OnUrlClick(HWND hDlg)
{
	CHAR buf[100];

	if (GetLocalMessage(MSG_ABOUT_URL, buf, sizeof(buf))) {
		ShellExecute(hDlg, NULL, buf, NULL, NULL, SW_SHOWNORMAL);
	}
}
