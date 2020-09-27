/*
	sysincl.h

	Virtual Floppy Drive for Windows
	GUI Control Panel
	include system headers

	Copyright (C) 2003-2005 Ken Kato
*/

#ifndef _SYSINCL_H_
#define _SYSINCL_H_

#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOC

#pragma warning(push, 3)
#include <windows.h>
#include <commdlg.h>
//#include <commctrl.h>
#include <objbase.h>
#include <shellapi.h>
#include <shlobj.h>
#pragma warning(pop)
#pragma warning(disable: 4514)

#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif	// INVALID_FILE_ATTRIBUTES

#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <stdarg.h>


#endif	/* _SYSINCL_H_ */
