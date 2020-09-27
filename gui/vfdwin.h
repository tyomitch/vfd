/*
	vfdwin.h

	Virtual Floppy Drive for Windows
	GUI Control Panel local header

	Copyright (C) 2003-2005 Ken Kato
*/

#ifndef _VFDWIN_H_
#define _VFDWIN_H_

#define VFDWIN_APP_BASENAME			"vfdwin"

#ifndef RC_INVOKED

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

#define VFD_REFRESH_MSG				(WM_USER + 1000)

#define	VFD_OPEN_SWITCH				"/open"
#define VFD_CFG_LINK_NAME			"VFD Control Panel"

//	icon index enumeration

enum {
	VFD_ICON_IDX_CONFIG = 0,
	VFD_ICON_IDX_OPEN,
	VFD_ICON_IDX_IMAGE,
};

//	dialog procedures

BOOL CALLBACK MainProc	(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ImageProc	(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DriverProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AssocProc	(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ShellProc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutProc	(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

//	Message Functions

void SetControlText(HWND hDlg, UINT nID, DWORD msg, ...);
void AppendLogMessage(DWORD err, DWORD msg, ...);
void ShowErrorMessage(DWORD err, DWORD msg, ...);
DWORD GetLocalMessage(DWORD msg, LPTSTR buf, DWORD size, ...);
const char *GetSystemMessage(DWORD err);

//	Global variables

extern HINSTANCE	hAppInst;
extern CHAR			sAppPath[];
extern PSTR			pAppBase;
extern HWND			hMainWnd;

//
//	utility macro
//
#define IS_WINDOWS_NT()		((GetVersion() & 0xff) < 5)

//
//	Debug routines
//
#ifdef _DEBUG

extern ULONG TraceFlags;
extern PCHAR TraceFile;
extern ULONG TraceLine;

#define VFDTRACE(LEVEL,STRING)					\
	if ((TraceFlags & (LEVEL)) == (LEVEL)) {	\
		TraceFile = __FILE__;					\
		TraceLine = __LINE__;					\
		DebugTrace STRING;						\
	}

void DebugTrace(PCSTR sFormat, ...);

#else	// _DEBUG
#define VFDTRACE(LEVEL,STRING)
#endif	// _DEBUG

#ifdef __cplusplus
}
#endif	// _cplusplus

#endif	// RC_INVOKED

#endif	// _VFDWIN_H_
