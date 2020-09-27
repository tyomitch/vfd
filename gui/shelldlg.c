/*
	shelldlg.c

	Virtual Floppy Drive for Windows
	GUI Control Panel
	"Shell" dialog functions

	Copyright (C) 2003-2005 Ken Kato
*/

#ifdef __cplusplus
#pragma message( __FILE__ ": Compiled as C++ for testing purpose.\n" )
#endif	// __cplusplus

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(push,3)
#include <shlobj.h>
#pragma warning(pop)
#include <stdio.h>

#include "vfdtypes.h"
#include "vfdapi.h"
#include "vfdwin.h"
#include "vfdmsg.h"
#include "resource.h"

typedef struct _TVPARAMS {
	int		item_type;
	int		link_type;
	int		folder;
	UINT	desc_id;
	LPTSTR	path;
} TVPARAMS;

enum {
	ITEM_PARENT,
	ITEM_SHELLEXT,
	ITEM_SHORTCUT
};

//
//	dialog message handlers
//
static void OnInitDialog(HWND hDlg);
static void OnApplyClicked(HWND hDlg, HWND hCtrl);
static BOOL OnTreeNotify(HWND hDlg, LPNMHDR pNMHDR);

//
//	other internal functions
//
static HTREEITEM InsertTreeItem(
	HWND		hDlg,
	HWND		hTree,
	HTREEITEM	hPrent,
	UINT		nText,
	int			nImage,
	int			item_type,
	int			link_type,
	int			folder);

static void		ToggleTreeItem(HWND hTree, HTREEITEM hItem);
static void		AdjustButtons(HWND hDlg, HWND hTree);

static LPTSTR	SearchVfdLink(HWND hDlg, int folder, int type);
static LPTSTR	CreateVfdLink(HWND hDlg, int folder, int type, UINT desc_id);

static BOOL		GetFolderPath(HWND hDlg, int folder, LPTSTR link);
static HRESULT	LoadLink(IShellLink *pLink, LPCTSTR path);
static void		GetLinkParams(IShellLink *pLink, LPTSTR path, LPTSTR args);

static HRESULT	CreateLink(
	LPCTSTR link_path,
	LPCTSTR target_path,
	LPCTSTR arguments,
	LPCTSTR description,
	int icon_index);

static void		DeleteLink(LPTSTR path);

//
//	Shell Dialog Procedure
//
BOOL CALLBACK ShellProc(
	HWND	hDlg,
	UINT	msg,
	WPARAM	wParam,
	LPARAM	lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		OnInitDialog(hDlg);
		break;

	case WM_ERASEBKGND:
		// somehow tree control is not drawn correctly when this dialog is
		// brought forward if the control has input focus, so force redrawing it
		RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE);
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_APPLY) {
			OnApplyClicked(hDlg, (HWND)lParam);
			return TRUE;
		}
		break;

	case WM_NOTIFY:
		if (wParam == IDC_SHELL_TREE) {
			//	It seems both DWL_MSGRESULT *and* return value
			//	are necessary to prevent items from collapsing
			lParam = OnTreeNotify(hDlg, (LPNMHDR)lParam);
			SetWindowLong(hDlg, DWL_MSGRESULT, lParam);
			return lParam;
		}
		break;
	}

	return 0;
}

//
//	Initialize the Shell dialog
//
void OnInitDialog(HWND hDlg)
{
	HWND		hTree;
	HIMAGELIST	hImage;
	HTREEITEM	hParent;
	DWORD		err;

	//
	//	set apply button text
	//
	SetControlText(hDlg, IDC_APPLY, MSG_APPLY_BUTTON);

	//
	//	initialize the tree control
	//
	hTree = GetDlgItem(hDlg, IDC_SHELL_TREE);

	if (hTree == NULL) {
		err = GetLastError();

		VFDTRACE(0,("OnInitDialog : GetDlgItem - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	//	set image list for the list control

	hImage = ImageList_LoadBitmap(
		hAppInst,
		MAKEINTRESOURCE(IDB_IMAGELIST),
		16, 1, RGB(255, 0, 255));

	if (hImage == NULL) {
		err = GetLastError();

		VFDTRACE(0,("OnInitDialog : ImageList_LoadBitmap - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	SetLastError(ERROR_SUCCESS);

	hImage = TreeView_SetImageList(hTree, hImage, TVSIL_NORMAL);

	if (hImage == NULL && GetLastError() != ERROR_SUCCESS) {
		err = GetLastError();

		VFDTRACE(0,("OnInitDialog : ListView_SetImageList - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	//
	//	Insert tree control items
	//

	//	Shell extension node

	hParent = InsertTreeItem(hDlg, hTree, NULL,
		MSG_TREE_SHELLEXT, 4, ITEM_PARENT, 0, 0);

	//	Shell extension

	if (IS_WINDOWS_NT()) {

		//	Windows NT doesn't support Drag & Drop handlers ???

		InsertTreeItem(hDlg, hTree, hParent,
			MSG_ITEM_SHELLEXT_NT, 0, ITEM_SHELLEXT,
			(VfdCheckHandlers() == ERROR_SUCCESS), 0);
	}
	else {
		InsertTreeItem(hDlg, hTree, hParent,
			MSG_ITEM_SHELLEXT, 0, ITEM_SHELLEXT,
			(VfdCheckHandlers() == ERROR_SUCCESS), 0);
	}

	//	Control Panel node

	hParent = InsertTreeItem(hDlg, hTree, NULL,
		MSG_TREE_CONFIG, 5, ITEM_PARENT, 0, 0);

	//	Control Panel shortcut on desktop

	InsertTreeItem(hDlg, hTree, hParent,
		MSG_ITEM_DESKTOP, 0, ITEM_SHORTCUT,
		-1, CSIDL_DESKTOPDIRECTORY);

	//	Control Panel shortcut in start menu

	InsertTreeItem(hDlg, hTree, hParent,
		MSG_ITEM_STARTMENU, 0, ITEM_SHORTCUT,
		-1, CSIDL_STARTMENU);

	//	Drive 0 node

	hParent = InsertTreeItem(hDlg, hTree, NULL,
		MSG_TREE_DRIVE0, 6, ITEM_PARENT, 0, 0);

	//	Drive 0 shortcut on desktop

	InsertTreeItem(hDlg, hTree, hParent,
		MSG_ITEM_DESKTOP, 0, ITEM_SHORTCUT,
		0, CSIDL_DESKTOPDIRECTORY);

	//	Drive 0 shortcut on sendto folder

	InsertTreeItem(hDlg, hTree, hParent,
		MSG_ITEM_SENDTO, 0, ITEM_SHORTCUT,
		0, CSIDL_SENDTO);

	//	Drive 1 node

	if (IS_WINDOWS_NT()) {

		//	Windows NT shell does not combine shortcut parameters and
		//	dropped file path.	If a file is dropped onto a shortcut
		//	to "VFDWIN.EXE /OPEN 1:", the shell discards the parameters
		//	in the shortcut and simply executes "VFDWIN.EXE <file>"

		hParent = InsertTreeItem(hDlg, hTree, NULL,
			MSG_TREE_DRIVE1_NT, 7, ITEM_PARENT, 0, 0);
	}
	else {
		hParent = InsertTreeItem(hDlg, hTree, NULL,
			MSG_TREE_DRIVE1, 6, ITEM_PARENT, 0, 0);

		//	Drive 1 shortcut on desktop

		InsertTreeItem(hDlg, hTree, hParent,
			MSG_ITEM_DESKTOP, 0, ITEM_SHORTCUT,
			1, CSIDL_DESKTOPDIRECTORY);

		//	Drive 1 shortcut on sendto folder

		InsertTreeItem(hDlg, hTree, hParent,
			MSG_ITEM_SENDTO, 0, ITEM_SHORTCUT,
			1, CSIDL_SENDTO);
	}

	return;
}

//
//	apply button is clicked
//
void OnApplyClicked(HWND hDlg, HWND hCtrl)
{
	HTREEITEM	hParent;
	HWND		hTree;

	hTree	= GetDlgItem(hDlg, IDC_SHELL_TREE);

	hParent = TreeView_GetChild(hTree, NULL);

	while (hParent) {
		HTREEITEM hItem = TreeView_GetChild(hTree, hParent);

		while (hItem) {
			TVITEM item = {0};

			item.mask	= TVIF_HANDLE | TVIF_IMAGE | TVIF_PARAM;
			item.hItem	= hItem;

			if (TreeView_GetItem(hTree, &item) && item.lParam) {
				BOOL changed = FALSE;
				TVPARAMS *param = (TVPARAMS *)item.lParam;

				if (param->item_type == ITEM_SHELLEXT) {
					if (param->link_type && !item.iImage) {
						VfdUnregisterHandlers();
						param->link_type = (VfdCheckHandlers() == ERROR_SUCCESS);
						changed = TRUE;
					}
					else if (!param->link_type && item.iImage) {
						VfdRegisterHandlers();
						param->link_type = (VfdCheckHandlers() == ERROR_SUCCESS);
						changed = TRUE;
					}
				}
				else if (param->item_type == ITEM_SHORTCUT) {
					if (param->path && !item.iImage) {
						DeleteLink(param->path);
						LocalFree(param->path);
						param->path = SearchVfdLink(
							hDlg, param->folder, param->link_type);
						changed = TRUE;
					}
					else if (!param->path && item.iImage) {
						param->path = CreateVfdLink(
							hDlg, param->folder, param->link_type, param->desc_id);
						changed = TRUE;
					}
				}

				if (changed) {
					TreeView_SetItem(hTree, &item);
				}
			}

			hItem = TreeView_GetNextSibling(hTree, hItem);
		}

		hParent = TreeView_GetNextSibling(hTree, hParent);
	}

	SetFocus(GetDlgItem(hDlg, IDC_SHELL_TREE));

	EnableWindow(hCtrl, FALSE);
	SendMessage(hCtrl, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);
}

//
//	tree control notification
//
BOOL OnTreeNotify(HWND hDlg, LPNMHDR pNMHDR)
{
	switch (pNMHDR->code) {
	case TVN_ITEMEXPANDING:
		if (((LPNMTREEVIEW)pNMHDR)->action == TVE_COLLAPSE) {
			// return TRUE to prevent the item from collapsing
			return TRUE;
		}
		break;

	case TVN_DELETEITEM:
		{
			TVPARAMS *params =
				(TVPARAMS *)((LPNMTREEVIEW)pNMHDR)->itemOld.lParam;

			if (params) {
				if (params->path) {
					LocalFree(params->path);
				}
				LocalFree(params);
			}
		}
		break;

	case NM_CLICK:
		{
			TVHITTESTINFO hit = {0};

			if (!GetCursorPos(&hit.pt)) {
				VFDTRACE(0,("OnTreeNotify : GetCursorPos - %s",
					GetSystemMessage(GetLastError())));
				break;
			}

			if (!ScreenToClient(pNMHDR->hwndFrom, &hit.pt)) {
				VFDTRACE(0,("OnTreeNotify : ScreenToClient - %s",
					GetSystemMessage(GetLastError())));
				break;
			}

			TreeView_HitTest(pNMHDR->hwndFrom, &hit);

			if (hit.hItem && (hit.flags & TVHT_ONITEMICON)) {

				// icon of an item is clicked

				ToggleTreeItem(pNMHDR->hwndFrom, hit.hItem);
				AdjustButtons(hDlg, pNMHDR->hwndFrom);
			}
		}
		break;

	case LVN_KEYDOWN:
		if (((LPNMLVKEYDOWN)pNMHDR)->wVKey == VK_SPACE) {
			HTREEITEM hItem;

			hItem = TreeView_GetSelection(pNMHDR->hwndFrom);

			if (hItem) {

				// space key is pressed while the focus on an item

				ToggleTreeItem(pNMHDR->hwndFrom, hItem);
				AdjustButtons(hDlg, pNMHDR->hwndFrom);
			}
		}
		break;
	}

	return FALSE;
}

//
//	insert an item into the tree control
//
HTREEITEM InsertTreeItem(
	HWND			hDlg,
	HWND			hTree,
	HTREEITEM		hParent,
	UINT			nText,
	int				nImage,
	int				item_type,
	int				link_type,
	int				folder)
{
	TVINSERTSTRUCT	insert = {0};
	TCHAR			text[MAX_PATH];
	TVPARAMS		*params = NULL;

	if (!GetLocalMessage(nText, text, sizeof(text))) {
		return NULL;
	}

	if (item_type != ITEM_PARENT) {
		params = (TVPARAMS *)LocalAlloc(LPTR, sizeof(TVPARAMS));

		if (params == NULL) {
			return NULL;
		}

		params->item_type	= item_type;
		params->link_type	= link_type;
		params->folder		= folder;

		if (item_type == ITEM_SHORTCUT) {
			params->path	= SearchVfdLink(hDlg, folder, link_type);

			if (params->path) {
				nImage = 1;
			}
			else {
				nImage = 0;
			}
		}
		else {
			if (link_type) {
				nImage = 1;
			}
			else {
				nImage = 0;
			}
		}
	}

	insert.hParent		= hParent;
	insert.hInsertAfter	= TVI_LAST;
	insert.item.mask	= TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_STATE | TVIF_PARAM;
	insert.item.pszText	= text;
	insert.item.iImage	= insert.item.iSelectedImage = nImage;
	insert.item.state	= insert.item.stateMask = TVIS_EXPANDED;
	insert.item.lParam	= (LPARAM)params;

	return TreeView_InsertItem(hTree, &insert);
}

//
//	switch an item's checked state
//
void ToggleTreeItem(HWND hTree, HTREEITEM hItem)
{
	TVITEM item = {0};

	item.mask	= TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_HANDLE;
	item.hItem	= hItem;

	if (!TreeView_GetItem(hTree, &item)) {
		VFDTRACE(0,("ToggleTreeItem : TreeView_GetItem - %s",
			GetSystemMessage(GetLastError())));

		return;
	}

	if (item.iImage == 0 || item.iImage == 1) {

		//	deal only with 'checked' or 'unchecked'
		//	ignore category nodes

		//	change icon index

		if (item.iImage == 0) {
			item.iSelectedImage = item.iImage = 1;
		}
		else if (item.iImage == 1) {
			item.iSelectedImage = item.iImage = 0;
		}

		if (!TreeView_SetItem(hTree, &item)) {
			VFDTRACE(0,("ToggleTreeItem : TreeView_SetItem - %s",
				GetSystemMessage(GetLastError())));
		}
	}

	return;
}

//
//	adjust the apply button state
//
void AdjustButtons(HWND hDlg, HWND hTree)
{
	HTREEITEM	hParent = TreeView_GetChild(hTree, NULL);
	BOOL changed = FALSE;

	if (hTree == NULL) {
		hTree = GetDlgItem(hDlg, IDC_SHELL_TREE);
	}

	while (hParent) {
		HTREEITEM hItem = TreeView_GetChild(hTree, hParent);

		while (hItem) {
			TVITEM item = {0};

			item.mask	= TVIF_HANDLE | TVIF_IMAGE | TVIF_PARAM;
			item.hItem = hItem;

			if (TreeView_GetItem(hTree, &item)) {
				if (item.lParam) {
					TVPARAMS *param = (TVPARAMS *)item.lParam;

					if (param->item_type == ITEM_SHELLEXT) {
						if ((param->link_type && !item.iImage) ||
							(!param->link_type && item.iImage)) {
							changed = TRUE;
							goto exit_func;
						}
					}
					else if (param->item_type == ITEM_SHORTCUT) {
						if ((param->path && !item.iImage) ||
							(!param->path && item.iImage)) {
							changed = TRUE;
							goto exit_func;
						}
					}
				}
			}

			hItem = TreeView_GetNextSibling(hTree, hItem);
		}

		hParent = TreeView_GetNextSibling(hTree, hParent);
	}

exit_func:
	EnableWindow(GetDlgItem(hDlg, IDC_APPLY), changed);
}

//
//	search shortcuts for this application in a system folder
//
#ifdef __cplusplus
#define REF(a)					(a)
#define VFN(a)					(a)
#define QueryInterface(a,b,c)	QueryInterface(b,c)
#define Release(a)				Release()
#define Free(a,b)				Free(b)
#define Load(a,b,c)				Load(b,c)
#define Save(a,b,c)				Save(b,c)
#define GetPath(a,b,c,d,e)		GetPath(b,c,d,e)
#define SetPath(a,b)			SetPath(b)
#define GetArguments(a,b,c)		GetArguments(b,c)
#define SetArguments(a,b)		SetArguments(b)
#define SetDescription(a,b)		SetDescription(b)
#define SetIconLocation(a,b,c)	SetIconLocation(b,c)
#else
#define REF(a)					(&(a))
#define VFN(a)					((a)->lpVtbl)
#endif

LPTSTR SearchVfdLink(
	HWND			hDlg,
	int				folder,
	int				type)
{
	TCHAR			link_path[MAX_PATH];
	int				link_path_len;
	WIN32_FIND_DATA find;
	HANDLE			hFind;
	IShellLink		*pLink;
	HRESULT			res;
	BOOL			match = FALSE;
	DWORD			err;
	char			link_arg[10];
	LPTSTR			buf;

	//	format a link argument to look for

	if (type >= 0) {	//	look for a VFD drive shortcut
		sprintf(link_arg, VFD_OPEN_SWITCH " %d:", type);
	}
	else {
		link_arg[0] = '\0';
	}

	//	get the path indicated by the folder identifier

	if (!GetFolderPath(hDlg, folder, link_path)) {
		return NULL;
	}

	link_path_len = strlen(link_path);

	//	search files with *.lnk extension

	strcpy(link_path + link_path_len, "\\*.lnk");

	hFind = FindFirstFile(link_path, &find);

	if (hFind == INVALID_HANDLE_VALUE) {
		err = GetLastError();

		if (err != ERROR_FILE_NOT_FOUND) {
			VFDTRACE(0,("SearchVfdLink : FindFirstFile - %s",
				GetSystemMessage(err)));
		}

		//	no *.lnk file
		return NULL;
	}

	// create an IShellLink interface object

	res = CoCreateInstance(
		REF(CLSID_ShellLink),
		NULL,
		CLSCTX_INPROC_SERVER,
		REF(IID_IShellLink),
		(LPVOID *)&pLink);

	if (!SUCCEEDED(res)) {
		err = GetLastError();

		VFDTRACE(0,("SearchVfdLink : CoCreateInstance - %s",
			GetSystemMessage(err)));

		FindClose(hFind);
		return NULL;
	}

	//	keep folder path and a trailing \ character

	link_path_len++;

	do {
		char path[MAX_PATH], args[MAX_PATH];

		// compose the shortcut file's full path

		strcpy(link_path + link_path_len, find.cFileName);

		//	load the shortcut file into an IShellLink object

		res = LoadLink(pLink, link_path);

		if (!SUCCEEDED(res)) {
			break;
		}

		//	get the shortcut link parameters

		GetLinkParams(pLink, path, args);

		//	does the target path include this application name?

		if (!strstr(path, pAppBase)) {
			continue;
		}

		//	does the link argument match?

		if (type >= 0 && !strnicmp(args, link_arg, strlen(link_arg))) {
			match = TRUE;
			break;
		}
		else if (type < 0 && *args == '\0') {
			match = TRUE;
			break;
		}
	}
	while (FindNextFile(hFind, &find));

	//	cleanup the IShellLink interface

	VFN(pLink)->Release(pLink);

	//	close the find handle

	FindClose(hFind);

	//	if a match is not found, return a NULL pointer

	if (!match) {
		return NULL;
	}

	//	allocate a buffer, copy the link path

	buf = (LPTSTR)LocalAlloc(LPTR, strlen(link_path) + 1);

	if (!buf) {
		VFDTRACE(0,("SearchVfdLink : LocalAlloc(%lu) - %s",
			strlen(link_path) + 1, GetSystemMessage(GetLastError())));
		return NULL;
	}

	strcpy(buf, link_path);

	return buf;
}

//
//	load link object from a file object
//

HRESULT LoadLink(
	IShellLink		*pLink,
	LPCTSTR			path)
{
	IPersistFile	*pFile;
	HRESULT			res;
	WCHAR			wsz[MAX_PATH];

	// Get a pointer to the IPersistFile interface.

	res = VFN(pLink)->QueryInterface(
		pLink,
		REF(IID_IPersistFile),
		(LPVOID *)&pFile);

	if (!SUCCEEDED(res)) {
		VFDTRACE(0,("LoadLink : pLink->QueryInterface - %s",
			GetSystemMessage(GetLastError())));
		return res;
	}

	// convert the path into Unicode

	if (!MultiByteToWideChar(CP_OEMCP, 0, path, -1, wsz, MAX_PATH)) {
		DWORD err = GetLastError();

		VFDTRACE(0, ("LoadLink : MultiByteToWideChar - %s",
			GetSystemMessage(err)));

		return HRESULT_FROM_WIN32(err);
	}

	// Load the shortcut file

	res = VFN(pFile)->Load(pFile, wsz, STGM_READ);

	if (!SUCCEEDED(res)) {
		VFDTRACE(0,("LoadLink : pFile->Load - %s",
			GetSystemMessage(GetLastError())));
	}

	// Release the interface

	VFN(pFile)->Release(pFile);

	return res;
}

//
//	get parameters from a shortcut link object
//

void GetLinkParams(
	IShellLink		*pLink,
	LPTSTR			path,
	LPTSTR			args)
{
	HRESULT			res;

	*path = '\0';
	*args = '\0';

	//	get the link target path

	res = VFN(pLink)->GetPath(
		pLink, path, MAX_PATH, NULL, SLGP_UNCPRIORITY);

	if (!SUCCEEDED(res)) {
		VFDTRACE(0,("GetLinkParams : pLink->GetPath - %s",
			GetSystemMessage(GetLastError())));
		return;
	}

	//	convert the path into lower case to make comparison easier

	while (*path) {
		*path = (TCHAR)tolower(*path);
		path++;
	}

	//	get the link arguments

	res = VFN(pLink)->GetArguments(pLink, args, MAX_PATH);

	if (!SUCCEEDED(res)) {
		VFDTRACE(0,("GetLinkParams : pLink->GetArguments - %s",
			GetSystemMessage(GetLastError())));
		return;
	}

	//	convert the arguments into lower case to make comparison easier

	while (*args) {
		*args = (TCHAR)tolower(*args);
		args++;
	}

	return;
}

//
//	create a shortcut link (preparation)
//
LPTSTR CreateVfdLink(
	HWND			hDlg,
	int				folder,
	int				type,
	UINT			desc_id)
{
	char			path[MAX_PATH];
	char			args[10];
	char			desc[MAX_PATH];
	int				len;
	HRESULT			res;
	LPTSTR			buf;

	//	create fullpath for the link

	if (!GetFolderPath(hDlg, folder, path)) {
		return NULL;
	}

	strcat(path, "\\");

	len = strlen (path);

	if (type >= 0) {
		GetLocalMessage(MSG_LINK_DRIVE,
			path + len, sizeof(path) - len, type);

		sprintf(args, VFD_OPEN_SWITCH " %d:", type);
	}
	else {
		GetLocalMessage(MSG_LINK_CONFIG,
			path + len, sizeof(path) - len);

		args[0] = '\0';
	}

	strcat(path, ".lnk");

	//	load link description string

	if (!GetLocalMessage(desc_id, desc, sizeof(desc))) {
		VFDTRACE(0, (
			"CreateVfdLink : GetLocalMessage(%u) - %s",
			desc_id, GetSystemMessage(GetLastError())));

		desc[0] = '\0';
		// this is not fatal
	}

	//	Create a shortcut link

	res = CreateLink(
		path, sAppPath, args, desc,
		type >= 0 ? VFD_ICON_IDX_OPEN : VFD_ICON_IDX_CONFIG);

	if (!SUCCEEDED(res)) {
		return NULL;
	}

	// link was actually created so let the shell know it

	SHChangeNotify(SHCNE_CREATE, SHCNF_PATH, path, NULL);

	//	allocate a buffer for the new link path

	buf = (LPTSTR)LocalAlloc(LPTR, strlen(path) + 1);

	if (!buf) {
		VFDTRACE(0, ("CreateVfdLink : LocalAlloc(%u) - %s",
			strlen(path) + 1, GetSystemMessage(GetLastError())));
	}
	else {
		strcpy(buf, path);
	}

	return buf;
}

//
//	delete shortcut file
//
void DeleteLink(LPTSTR path)
{
	if (DeleteFile(path) || GetLastError() == ERROR_FILE_NOT_FOUND) {
		SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, path, NULL);
	}
	else {
		VFDTRACE(0,("DeleteLink : DeleteFile(%s) - %s",
			path, GetSystemMessage(GetLastError())));
	}
}

//
//	get the path to a system special folder
//

BOOL GetFolderPath(
	HWND			hDlg,
	int				folder,
	LPTSTR			path)
{
	LPMALLOC		pMalloc;
	LPITEMIDLIST	pidl;
	BOOL			ret;
	HRESULT			res;

	res = SHGetSpecialFolderLocation(hDlg, folder, &pidl);

	if (!SUCCEEDED(res)) {
		VFDTRACE(0,("GetFolderPath : SHGetSpecialFolderLocation(%d) - %s",
			folder, GetSystemMessage(res)));

		return FALSE;
	}

	ret = SHGetPathFromIDList(pidl, path);

	if (!ret) {
		VFDTRACE(0,("GetFolderPath : SHGetPathFromIDList(%d) - %s",
			folder, GetSystemMessage(GetLastError())));
	}

	res = SHGetMalloc(&pMalloc);

	if (SUCCEEDED(res)) {
		VFN(pMalloc)->Free(pMalloc, pidl);
		VFN(pMalloc)->Release(pMalloc);
	}
	else {
		VFDTRACE(0,("GetFolderPath : SHGetMalloc - %s",
			GetSystemMessage(res)));
	}

	return ret;
}

//
//	create a shortcut link
//
HRESULT CreateLink(
	LPCTSTR			link_path,
	LPCTSTR			target_path,
	LPCTSTR			arguments,
	LPCTSTR			description,
	int				icon_index)
{
	IShellLink		*pLink;
	IPersistFile	*pFile;
	HRESULT			res;
	WCHAR			wsz[MAX_PATH];

	// Get a pointer to the IShellLink interface.
	res = CoCreateInstance(
		REF(CLSID_ShellLink),
		NULL,
		CLSCTX_INPROC_SERVER,
		REF(IID_IShellLink),
		(LPVOID *)&pLink);

	if (!SUCCEEDED(res)) {
		VFDTRACE(0,("CreateLink : CoCreateInstance - %s",
			GetSystemMessage(res)));

		return res;
	}

	// Set link properties
	if (target_path) {
		res = VFN(pLink)->SetPath(pLink, target_path);

		if (!SUCCEEDED(res)) {
			VFDTRACE(0,("CreateLink : pLink->SetPath - %s",
				GetSystemMessage(res)));

			goto cleanup;
		}
	}

	if (arguments) {
		VFN(pLink)->SetArguments(pLink, arguments);

		if (!SUCCEEDED(res)) {
			VFDTRACE(0,("CreateLink : pLink->SetArguments - %s",
				GetSystemMessage(res)));

			goto cleanup;
		}
	}

	if (description) {
		VFN(pLink)->SetDescription(pLink, description);

		if (!SUCCEEDED(res)) {
			VFDTRACE(0,("CreateLink : pLink->SetDescription - %s",
				GetSystemMessage(res)));

			goto cleanup;
		}
	}

	if (icon_index) {
		VFN(pLink)->SetIconLocation(pLink, target_path, icon_index);

		if (!SUCCEEDED(res)) {
			VFDTRACE(0,("CreateLink : pLink->SetIconLocation - %s",
				GetSystemMessage(res)));

			goto cleanup;
		}
	}

   // Query IShellLink for the IPersistFile interface for saving the
   // shortcut in persistent storage.

	res = VFN(pLink)->QueryInterface(
		pLink,
		REF(IID_IPersistFile),
		(LPVOID*)&pFile);

	if (!SUCCEEDED(res)) {
		VFDTRACE(0,("CreateLink : pLink->QueryInterface - %s",
			GetSystemMessage(res)));

		goto cleanup;
	}

	// Ensure that the string is Unicode.

	if (MultiByteToWideChar(CP_OEMCP, 0, link_path,
		-1, wsz, sizeof(wsz) / sizeof(wsz[0]))) {

		// Save the link by calling IPersistFile::Save.
		res = VFN(pFile)->Save(pFile, wsz, TRUE);

		if (!SUCCEEDED(res)) {
			VFDTRACE(0,("CreateLink : pFile->Save - %s",
				GetSystemMessage(res)));
		}
	}
	else {
		res = HRESULT_FROM_WIN32(GetLastError());

		VFDTRACE(0, ("CreateLink : MultiByteToWideChar - %s",
			GetSystemMessage(GetLastError())));
	}

	VFN(pFile)->Release(pFile);

cleanup:
	VFN(pLink)->Release(pLink);

	return res;
}
