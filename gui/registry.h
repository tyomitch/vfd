/*
	registry.h

	Virtual Floppy Drive for Windows
	GUI Control Panel
	Registry handling functions header

	Copyright (C) 2003-2005 Ken Kato
*/

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*	Get the associated program name of an extension	*/
DWORD GetAssociatedProgram(
	LPCTSTR ext,
	LPTSTR prog);

/*	Restore the previous association				*/
DWORD RestoreAssociation(
	LPCTSTR ext,
	LPCTSTR backup_value);

/*	Add an association to an extension				*/
DWORD AddAssociation(
	LPCTSTR ext,
	LPCTSTR type_prefix,
	LPCTSTR type_desc,
	LPCTSTR verb,
	LPCTSTR verb_desc,
	LPCTSTR program,
	int icon_idx);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* _REGISTRY_H_	*/
