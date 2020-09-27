/*
	assocdlg.c

	Virtual Floppy Drive for Windows
	GUI Control Panel
	"Association" dialog functions

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

#include "vfdtypes.h"
#include "vfdapi.h"
#include "vfdver.h"
#include "vfdwin.h"
#include "vfdmsg.h"
#include "resource.h"
#include "registry.h"

//
//	Fallback text
//
#define FALLBACK_EXT_HEADER	"Extension"
#define FALLBACK_APP_HEADER	"Program"
#define FALLBACK_CANT_WRITE	"Registry is read-only"
#define FALLBACK_CANT_READ	"Cannot read the registry"

//
//	Window message handlers
//
static void OnInitDialog(HWND hDlg);
static void OnNewClicked(HWND hDlg, HWND hBtn);
static void OnCheckAllClicked(HWND hDlg, HWND hBtn, int check);
static void OnApplyClicked(HWND hDlg, HWND hBtn);
static void OnListNotify(HWND hDlg, LPNMHDR pNMHDR);

//
//	local functions
//
static void UpdateList(HWND hDlg);
static int	AddItem(HWND hList, char *ext, char *prog);
static void ToggleItem(HWND hList, int iItem);

//
//	Add extension dialog
//
static BOOL CALLBACK AddExtProc(
	HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static void OnAddExtEdit(HWND hDlg, HWND hEdit);

//
//	dialog state variables
//
static int	nCheckedItems = 0;
static int	nChangedItems = 0;
static BOOL	bRegWritable = FALSE;

//
//	window massage dispatcher
//
BOOL CALLBACK AssocProc(
	HWND hDlg,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		OnInitDialog(hDlg);
		break;

	case WM_ERASEBKGND:
		// somehow list control is not drawn correctly when this dialog is
		// brought forward if the control has input focus, so force redrawing it
		RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE);
		break;

	case WM_COMMAND:
		switch(wParam) {
		case IDC_NEW:
			OnNewClicked(hDlg, (HWND)lParam);
			break;

		case IDC_ALL:
			OnCheckAllClicked(hDlg, (HWND)lParam, 1);
			break;

		case IDC_CLEAR:
			OnCheckAllClicked(hDlg, (HWND)lParam, 0);
			break;

		case IDC_APPLY:
			OnApplyClicked(hDlg, (HWND)lParam);
			break;
		}
		break;

	case WM_NOTIFY:
		switch (wParam) {
		case IDC_ASSOC_LIST:
			OnListNotify(hDlg, (LPNMHDR)lParam);
			break;
		}
		break;
	}

	return 0;
}

//
//	Association dialog initialize
//
void OnInitDialog(HWND hDlg)
{
	HWND hList;
	HIMAGELIST hImage;
	LVCOLUMN column;
	RECT rect;
	char buf[50];
	DWORD err;

	//
	//	set buttons text
	//
	SetControlText(hDlg, IDC_NEW,	MSG_NEW_BUTTON);

	SetControlText(hDlg, IDC_ALL,	MSG_CHECK_ALL);

	SetControlText(hDlg, IDC_CLEAR, MSG_CLEAR_ALL);

	SetControlText(hDlg, IDC_APPLY, MSG_APPLY_BUTTON);

	//
	//	initialize associatoin list view
	//
	hList = GetDlgItem(hDlg, IDC_ASSOC_LIST);

	if (hList == NULL) {
		err = GetLastError();

		VFDTRACE(0,("OnInitDialog : GetDlgItem - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	if (!GetClientRect(hList, &rect)) {
		err = GetLastError();

		VFDTRACE(0,("OnInitDialog : GetClientRect - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	//	insert columns

	memset(&column, 0, sizeof(column));

	column.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	column.pszText = buf;

	//	first column -- extension

	if (!GetLocalMessage(MSG_EXT_HEADER, buf, sizeof(buf))) {

		VFDTRACE(0,("OnInitDialog : LoadString - %s",
			GetSystemMessage(GetLastError())));

		column.pszText = FALLBACK_EXT_HEADER;
	}

	column.cx = (rect.right - rect.left) / 3;
	column.iSubItem = 0;

	if (ListView_InsertColumn(hList, 0, &column) == -1) {
		err = GetLastError();

		VFDTRACE(0,("OnInitDialog : ListView_InsertColumn - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	//	second column -- associated program
	column.pszText = buf;

	if (!GetLocalMessage(MSG_APP_HEADER, buf, sizeof(buf))) {

		VFDTRACE(0,("OnInitDialog : LoadString - %s",
			GetSystemMessage(GetLastError())));

		column.pszText = FALLBACK_APP_HEADER;
	}

	column.cx = column.cx * 2 - GetSystemMetrics(SM_CXVSCROLL);
	column.iSubItem = 1;

	if (ListView_InsertColumn(hList, 1, &column) == -1) {
		err = GetLastError();

		VFDTRACE(0,("OnInitDialog : ListView_InsertColumn - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	//	set image list for the list control

	hImage = ImageList_LoadBitmap(hAppInst,
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

	hImage = ListView_SetImageList(hList, hImage, LVSIL_SMALL);

	if (hImage == NULL && GetLastError() != ERROR_SUCCESS) {
		err = GetLastError();

		VFDTRACE(0,("OnInitDialog : ListView_SetImageList - %s",
			GetSystemMessage(err)));

		ShowErrorMessage(err, MSG_ERR_APP_INTERNAL);

		return;
	}

	//	read current association from registry

	UpdateList(hDlg);

	//	set focus on the first item

	ListView_SetItemState(hList, 0,
		LVIS_SELECTED|LVIS_FOCUSED,
		LVIS_SELECTED|LVIS_FOCUSED);

	return;
}

//
//	read current association from registry and put them into list control
//
void UpdateList(HWND hDlg)
{
	HKEY	hKey;
	char	ext[MAX_PATH], prog[MAX_PATH];
	LONG	ret;
	HWND	hList;
	DWORD	index;

	//
	//	Reset list status
	//
	nCheckedItems = 0;
	nChangedItems = 0;

	hList = GetDlgItem(hDlg, IDC_ASSOC_LIST);

	if (hList == NULL) {
		VFDTRACE(0,("UpdateList : GetDlgItem - %s",
			GetSystemMessage(GetLastError())));

		return;
	}

	//
	//	Open registry root key
	//

	ret = RegOpenKeyEx(HKEY_CLASSES_ROOT, NULL, 0, KEY_ALL_ACCESS, &hKey);

	if (ret == ERROR_SUCCESS) {
		bRegWritable = TRUE;
	}
	else {
		//	Failed to open registry in read-write mode

		char msg[MAX_PATH];
		HWND hMsg;

		VFDTRACE(0,("UpdateList : RegOpenKeyEx(HKCR) - %s",
			GetSystemMessage(GetLastError())));

		bRegWritable = FALSE;

		//	Hide controls for manipulating association

		ShowWindow(GetDlgItem(hDlg, IDC_NEW),	SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_ALL),	SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_CLEAR), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, IDC_APPLY), SW_HIDE);

		//	open registry in read-only mode

		ret = RegOpenKeyEx(HKEY_CLASSES_ROOT, NULL, 0, KEY_READ, &hKey);

		if (ret == ERROR_SUCCESS) {
			// succeeded to open read-only

			if (!GetLocalMessage(MSG_ASSOC_CANT_WRITE, msg, sizeof(msg))) {

				VFDTRACE(0,("UpdateList : LoadString - %s",
					GetSystemMessage(GetLastError())));

				// in case LoadString has failed
				strcpy(msg, FALLBACK_CANT_WRITE);
			}
		}
		else {
			// failed even to open read-only

			VFDTRACE(0,("UpdateList : RegOpenKeyEx - %s",
				GetSystemMessage(ret)));

			EnableWindow(hList, FALSE);

			if (!GetLocalMessage(MSG_ASSOC_CANT_READ, msg, sizeof(msg))) {

				VFDTRACE(0,("UpdateList : LoadString - %s",
					GetSystemMessage(GetLastError())));

				// in case LoadString has failed
				strcpy(msg, FALLBACK_CANT_READ);
			}
		}

		// show why users can't modify association

		hMsg = GetDlgItem(hDlg, IDC_ASSOC_MESSAGE);

		if (hMsg == NULL) {
			VFDTRACE(0,("UpdateList : GetDlgItem - %s",
				GetSystemMessage(GetLastError())));
			return;
		}

		if (!SetWindowText(hMsg, msg)) {
			VFDTRACE(0,("UpdateList : SetWindowText - %s",
				GetSystemMessage(GetLastError())));
			return;
		}

		ShowWindow(hMsg, SW_SHOW);

		if (ret != ERROR_SUCCESS) {

			// cannot even read registry

			return;
		}
	}

	//
	//	Add common floppy image extensions to the list view
	//

	if ((ret = GetAssociatedProgram(".bin", prog)) == ERROR_SUCCESS) {
		AddItem(hList, ".bin", prog);
	}
	else {
		VFDTRACE(0,("UpdateList : GetAssociatedProgram(\".bin\") - %s",
			GetSystemMessage(ret)));
	}

	if ((ret = GetAssociatedProgram(".dat", prog)) == ERROR_SUCCESS) {
		AddItem(hList, ".dat", prog);
	}
	else {
		VFDTRACE(0,("UpdateList : GetAssociatedProgram(\".dat\") - %s",
			GetSystemMessage(ret)));
	}

	if ((ret = GetAssociatedProgram(".fdd", prog)) == ERROR_SUCCESS) {
		AddItem(hList, ".fdd", prog);
	}
	else {
		VFDTRACE(0,("UpdateList : GetAssociatedProgram(\".fdd\") - %s",
			GetSystemMessage(ret)));
	}

	if ((ret = GetAssociatedProgram(".flp", prog)) == ERROR_SUCCESS) {
		AddItem(hList, ".flp", prog);
	}
	else {
		VFDTRACE(0,("UpdateList : GetAssociatedProgram(\".flp\") - %s",
			GetSystemMessage(ret)));
	}

	if ((ret = GetAssociatedProgram(".img", prog)) == ERROR_SUCCESS) {
		AddItem(hList, ".img", prog);
	}
	else {
		VFDTRACE(0,("UpdateList : GetAssociatedProgram(\".img\") - %s",
			GetSystemMessage(ret)));
	}

	if ((ret = GetAssociatedProgram(".ima", prog)) == ERROR_SUCCESS) {
		AddItem(hList, ".ima", prog);
	}
	else {
		VFDTRACE(0,("UpdateList : GetAssociatedProgram(\".ima\") - %s",
			GetSystemMessage(ret)));
	}

	if ((ret = GetAssociatedProgram(".vfd", prog)) == ERROR_SUCCESS) {
		AddItem(hList, ".vfd", prog);
	}
	else {
		VFDTRACE(0,("UpdateList : GetAssociatedProgram(\".vfd\") - %s",
			GetSystemMessage(ret)));
	}

	//
	//	Search registry for other extensions associated with VfdWin
	//

	index = 0;

	for (;;) {
		DWORD size = sizeof(ext);

		ret = RegEnumKeyEx(hKey, index++, ext, &size, NULL, NULL, NULL, NULL);

		if (ret != ERROR_SUCCESS) {
			if (ret != ERROR_NO_MORE_ITEMS) {
				VFDTRACE(0,("UpdateList : RegEnumKeyEx - %s",
					GetSystemMessage(ret)));
			}
			break;
		}

		if (ext[0] != '.') {
			// not an extension - try next item
			continue;
		}

		ext[size] = '\0';

		if ((ret = GetAssociatedProgram(ext, prog)) == ERROR_SUCCESS) {
			if (strnicmp(prog, pAppBase, strlen(pAppBase)) == 0) {
				AddItem(hList, ext, prog);
			}
		}
		else {
			VFDTRACE(0,("UpdateList : GetAssociatedProgram(\"%s\") - %s",
				ext, GetSystemMessage(ret)));
		}
	}

	RegCloseKey(hKey);

	// Enable / Disable the "Check All" and "Clear All" button
	// according to the number of checked items

	EnableWindow(GetDlgItem(hDlg, IDC_CLEAR), nCheckedItems);
	EnableWindow(GetDlgItem(hDlg, IDC_ALL), (nCheckedItems < ListView_GetItemCount(hList)));
}

//
//	Insert an item to the list constrol
//
int AddItem(HWND hList, char *ext, char *prog)
{
	LVITEM item;

	memset(&item, 0, sizeof(item));

	//	make sure that extension is in lower case
	{
		char *p = ext;

		while (*p) {
			*p = (char)tolower(*p);
			p++;
		}
	}

	if (*prog == '\0') {
		if (!GetLocalMessage(MSG_GENERIC_NONE, prog, MAX_PATH)) {
			// in case LoadString failed

			VFDTRACE(0,("AddItem : LoadString - %s",
				GetSystemMessage(GetLastError())));

			strcpy(prog, "(none)");
		}
	}

	//	select check status

	if (strnicmp(prog, pAppBase, strlen(pAppBase)) == 0) {
		//	use checked icon
		item.iImage = 1;

		//	use full name if program is "vfdwin.exe"
		strcpy(prog, VFD_PRODUCT_NAME);
	}

	//	if registry is read-only, use grayed check icons

	if (!bRegWritable) {
		item.iImage += 2;
	}

	//	store initial icon state in lParam

	item.lParam = item.iImage;

	//	find if extension is already in the list
	{
		LVFINDINFO find;

		memset(&find, 0, sizeof(find));
		find.flags = LVFI_STRING;
		find.psz = ext;

		item.iItem = ListView_FindItem(hList, -1, &find);
	}

	//
	//	insert an item or update check status
	//

	if (item.iItem == -1) {

		// add a new item

		item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

		item.iItem = ListView_GetItemCount(hList);
		item.pszText = ext;

		item.iItem = ListView_InsertItem(hList, &item);

		if (item.iItem == -1) {
			VFDTRACE(0,("AddItem : ListView_InsertItem - %s",
				GetSystemMessage(GetLastError())));
		}
	}
	else {

		// update icon index

		item.mask = LVIF_IMAGE | LVIF_PARAM;

		if (!ListView_SetItem(hList, &item)) {
			VFDTRACE(0,("AddItem : ListView_SetItem - %s",
				GetSystemMessage(GetLastError())));
		}
	}

	if (item.iItem >= 0) {

		// set program name

		ListView_SetItemText(hList, item.iItem, 1, prog);

		// count items with 'checked' icon

		if (item.iImage == 1) {
			nCheckedItems++;
		}
	}

	return item.iItem;
}

//
//	handles list control notification messages
//	NM_CLICK	- an item is clicked
//	LVN_KEYDOWN	- a key is pressed
//
void OnListNotify(HWND hDlg, LPNMHDR pNMHDR)
{
	// if registry is read-only, do nothing

	if (!bRegWritable) {
		return;
	}

	switch (pNMHDR->code) {
	case NM_CLICK:
		{
			LVHITTESTINFO hit;

			memset(&hit, 0, sizeof(hit));

			if (!GetCursorPos(&hit.pt)) {
				VFDTRACE(0,("OnListNotify : GetCursorPos - %s",
					GetSystemMessage(GetLastError())));
				break;
			}

			if (!ScreenToClient(pNMHDR->hwndFrom, &hit.pt)) {
				VFDTRACE(0,("OnListNotify : ScreenToClient - %s",
					GetSystemMessage(GetLastError())));
				break;
			}

			ListView_HitTest(pNMHDR->hwndFrom, &hit);

			if (hit.iItem >= 0 && (hit.flags & LVHT_ONITEMICON)) {

				// icon of an item is clicked

				ToggleItem(pNMHDR->hwndFrom, hit.iItem);

				//	enable/disable 'clear' and 'apply' buttons

				EnableWindow(GetDlgItem(hDlg, IDC_CLEAR), nCheckedItems);
				EnableWindow(GetDlgItem(hDlg, IDC_ALL), (nCheckedItems < ListView_GetItemCount(pNMHDR->hwndFrom)));
				EnableWindow(GetDlgItem(hDlg, IDC_APPLY), nChangedItems);
			}
		}
		break;

	case LVN_KEYDOWN:
		if (((LPNMLVKEYDOWN)pNMHDR)->wVKey == VK_SPACE) {
			int item;

			item = ListView_GetNextItem(pNMHDR->hwndFrom, -1, LVNI_SELECTED);

			if (item >= 0) {

				// space key is pressed while the focus on an item

				ToggleItem(pNMHDR->hwndFrom, item);

				//	enable/disable 'clear' and 'apply' buttons

				EnableWindow(GetDlgItem(hDlg, IDC_CLEAR), nCheckedItems);
				EnableWindow(GetDlgItem(hDlg, IDC_ALL), (nCheckedItems < ListView_GetItemCount(pNMHDR->hwndFrom)));
				EnableWindow(GetDlgItem(hDlg, IDC_APPLY), nChangedItems);
			}
		}
		break;
	}

	return;
}

//
//	switch an item's checked state
//
void ToggleItem(HWND hList, int iItem)
{
	LVITEM item;

	memset(&item, 0, sizeof(item));

	item.mask = LVIF_IMAGE | LVIF_PARAM;
	item.iItem = iItem;

	if (!ListView_GetItem(hList, &item)) {
		VFDTRACE(0,("ToggleItem : ListView_GetItem - %s",
			GetSystemMessage(GetLastError())));

		return;
	}

	if (item.iImage == 0 || item.iImage == 1) {

		//	deal only with 'checked' or 'unchecked'
		//	ignore grayed icons

		//	is current state the same as the original state?

		if (item.iImage == item.lParam) {
			nChangedItems++;
		}
		else {
			nChangedItems--;
		}

		//	change icon index

		if (item.iImage == 0) {
			nCheckedItems++;
			item.iImage = 1;
		}
		else if (item.iImage == 1) {
			nCheckedItems--;
			item.iImage = 0;
		}

		if (!ListView_SetItem(hList, &item)) {
			VFDTRACE(0,("ToggleItem : ListView_SetItem - %s",
				GetSystemMessage(GetLastError())));
		}
	}

	return;
}

//
//	New button is clicked
//
void OnNewClicked(HWND hDlg, HWND hBtn)
{
	HWND hList;
	char ext[MAX_PATH], prog[MAX_PATH];
	LVITEM item;
	DWORD ret;

	if (!bRegWritable) {
		return;
	}

	ret = DialogBoxParam(hAppInst,
		MAKEINTRESOURCE(IDD_NEWEXT),
		hDlg, AddExtProc, (LPARAM)(ext + 1));

	if (ret <= 0) {
		if (ret != 0) {
			VFDTRACE(0,("OnNewClicked : DialogBoxParam - %s",
				GetSystemMessage(GetLastError())));
		}
		return;
	}

	hList = GetDlgItem(hDlg, IDC_ASSOC_LIST);

	if (hList == NULL) {
		VFDTRACE(0,("OnNewClicked : GetDlgItem - %s",
			GetSystemMessage(GetLastError())));
		return;
	}

	ext[0] = '.';

	memset(&item, 0, sizeof(item));

	ret = GetAssociatedProgram(ext[1] == '.' ? &ext[1] : ext, prog);

	if (ret != ERROR_SUCCESS) {
		VFDTRACE(0,("OnListNotify : GetAssociatedProgram(\"%s\") - %s",
			ext[1] == '.' ? &ext[1] : ext, GetSystemMessage(ret)));
	}

	//	Insert an item to the list control

	item.iItem = AddItem(hList, ext[1] == '.' ? &ext[1] : ext, prog);

	if (item.iItem == -1) {
		return;
	}

	//	Get the new image's check state

	item.mask = LVIF_IMAGE;

	if (!ListView_GetItem(hList, &item)) {
		VFDTRACE(0,("OnListNotify : ListView_GetItem - %s",
			GetSystemMessage(GetLastError())));
		return;
	}

	//	if the item is not checked, check it

	if (item.iImage == 0) {
		item.iImage = 1;

		if (!ListView_SetItem(hList, &item)) {
			VFDTRACE(0,("OnListNotify : ListView_SetItem - %s",
				GetSystemMessage(GetLastError())));
			return;
		}

		nCheckedItems++;
		nChangedItems++;
	}

	//	enable / disable 'clear' and 'apply' button

	EnableWindow(GetDlgItem(hDlg, IDC_CLEAR), nCheckedItems);
	EnableWindow(GetDlgItem(hDlg, IDC_ALL), nCheckedItems < ListView_GetItemCount(hList));
	EnableWindow(GetDlgItem(hDlg, IDC_APPLY), nChangedItems);

	SendMessage(hBtn, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);

	return;
}

//
//	check all / clear all button is clicked
//
void OnCheckAllClicked(HWND hDlg, HWND hBtn, int check)
{
	HWND hList;
	LVITEM item;

	if (!bRegWritable) {
		return;
	}

	hList = GetDlgItem(hDlg, IDC_ASSOC_LIST);

	if (hList == NULL) {
		VFDTRACE(0,("OnAssocClear : GetDlgItem - %s",
			GetSystemMessage(GetLastError())));

		return;
	}

	nChangedItems = 0;

	memset(&item, 0, sizeof(item));
	item.iItem = -1;

	while ((item.iItem = ListView_GetNextItem(hList, item.iItem, LVNI_ALL)) != -1) {
		item.mask = LVIF_PARAM;

		if (!ListView_GetItem(hList, &item)) {
			VFDTRACE(0,("OnAssocClear : ListView_GetItem - %s",
				GetSystemMessage(GetLastError())));
			break;
		}

		if (item.lParam != check) {
			nChangedItems++;
		}

		item.mask = LVIF_IMAGE;
		item.iImage = check;

		if (!ListView_SetItem(hList, &item)) {
			VFDTRACE(0,("OnAssocClear : ListView_SetItem - %s",
				GetSystemMessage(GetLastError())));
			break;
		}
	}

	nCheckedItems = check ? ListView_GetItemCount(hList) : 0;

	EnableWindow(GetDlgItem(hDlg, IDC_CLEAR), nCheckedItems);
	EnableWindow(GetDlgItem(hDlg, IDC_ALL), (nCheckedItems < ListView_GetItemCount(hList)));
	EnableWindow(GetDlgItem(hDlg, IDC_APPLY), nChangedItems);

	SetFocus(GetDlgItem(hDlg, IDC_ASSOC_LIST));

	SendMessage(hBtn, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);

	return;
}

//
//	apply button is clicked
//
void OnApplyClicked(HWND hDlg, HWND hBtn)
{
	HWND hList;
	LVITEM item;
	char type_desc[MAX_PATH], verb_desc[MAX_PATH];
	char ext[MAX_PATH], prog[MAX_PATH];

	if (!bRegWritable) {
		return;
	}

	hList = GetDlgItem(hDlg, IDC_ASSOC_LIST);

	if (hList == NULL) {
		VFDTRACE(0,("OnApplyClicked : GetDlgItem - %s",
			GetSystemMessage(GetLastError())));

		return;
	}

	if (!GetLocalMessage(MSG_ASSOC_FILETYPE_DESC, type_desc, sizeof(type_desc))) {
		VFDTRACE(0,("OnApplyClicked : LoadString - %s",
			GetSystemMessage(GetLastError())));

		type_desc[0] = '\0';

		// this is not fatal
	}

	if (!GetLocalMessage(MSG_ASSOC_FILETYPE_VERB, verb_desc, sizeof(verb_desc))) {
		VFDTRACE(0,("OnApplyClicked : LoadString - %s",
			GetSystemMessage(GetLastError())));

		verb_desc[0] = '\0';

		// this also is not fatal
	}

	nCheckedItems = 0;
	nChangedItems = 0;

	memset(&item, 0, sizeof(item));
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	item.iItem = -1;
	item.pszText = ext;
	item.cchTextMax = sizeof(ext);

	while ((item.iItem = ListView_GetNextItem(hList, item.iItem, LVNI_ALL)) != -1) {
		DWORD ret;

		if (!ListView_GetItem(hList, &item)) {
			VFDTRACE(0,("OnApplyClicked : ListView_GetItem - %s",
				GetSystemMessage(GetLastError())));
			break;
		}

		if (item.iImage == 0 && item.lParam == 1) {
			// initially checked, but currently unchecked

			ret = RestoreAssociation(ext, VFDWIN_APP_BASENAME);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0,("OnApplyClicked : RemoveAssociation(\"%s\") - %s",
					ext, GetSystemMessage(ret)));
				break;
			}
		}
		else if (item.iImage == 1 && item.lParam == 0) {
			// initially unchecked, and currently checked

			ret = AddAssociation(ext,
				VFDWIN_APP_BASENAME,
				type_desc,
				VFDWIN_APP_BASENAME,
				verb_desc,
				sAppPath,
				VFD_ICON_IDX_IMAGE);

			if (ret != ERROR_SUCCESS) {
				VFDTRACE(0,("OnApplyClicked : AddAssociation(\"%s\") - %s",
					ext, GetSystemMessage(ret)));
				break;
			}
		}

		if ((ret = GetAssociatedProgram(ext, prog)) == ERROR_SUCCESS) {
			AddItem(hList, ext, prog);
		}
		else {
			VFDTRACE(0,("OnApplyClicked : GetAssociatedProgram(\"%s\") - %s",
				ext, GetSystemMessage(ret)));
		}
	}

	EnableWindow(GetDlgItem(hDlg, IDC_CLEAR), nCheckedItems);
	EnableWindow(GetDlgItem(hDlg, IDC_ALL), (nCheckedItems < ListView_GetItemCount(hList)));
	EnableWindow(GetDlgItem(hDlg, IDC_APPLY), nChangedItems);

	SetFocus(GetDlgItem(hDlg, IDC_ASSOC_LIST));

	SendMessage(hBtn, BM_SETSTYLE, BS_PUSHBUTTON, TRUE);

	//
	//	notify the shell
	//
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);

	return;
}

//
//	Add extension dialog procedure
//
BOOL CALLBACK AddExtProc(
	HWND hDlg,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	static char *sExtension = NULL;

	switch (msg) {
	case WM_INITDIALOG:
		SetControlText(hDlg, 0,					MSG_NEWEXT_TITLE);
		SetControlText(hDlg, IDC_NEWEXT_LABEL,	MSG_NEWEXT_LABEL);
		SetControlText(hDlg, IDOK,				MSG_OK_BUTTON);
		SetControlText(hDlg, IDCANCEL,			MSG_CANCEL_BUTTON);
		sExtension = (char *)lParam;
		break;

	case WM_COMMAND:
		switch (wParam) {
		case IDOK:
			EndDialog(hDlg,
				GetDlgItemText(hDlg, IDC_EXTENSION, sExtension, MAX_PATH - 1));
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;

		case MAKELONG(IDC_EXTENSION, EN_CHANGE):
			OnAddExtEdit(hDlg, (HWND)lParam);
			break;
		}
	}
	return 0;
}

//
//	text in the extention edit box has been changed
//
void OnAddExtEdit(HWND hDlg, HWND hEdit)
{
	char buf[MAX_PATH], *p;
	BOOL valid = FALSE;

	if (!GetWindowText(hEdit, buf, sizeof(buf))) {
		if (GetLastError() != ERROR_SUCCESS) {
			VFDTRACE(0,("OnAssocEditChange : GetWindowText - %s",
				GetSystemMessage(GetLastError())));

			return;
		}
	}

	p = buf;

	if (*p == '.') {
		p++;
	}

	while (*p) {
		if (strchr(".\\/:,;*?\"<>| ", *p)) {
			valid = FALSE;
			break;
		}
		else {
			valid = TRUE;
		}
		p++;
	}

	//	enable 'OK' button if text is valid for an extension

	EnableWindow(GetDlgItem(hDlg, IDOK), valid);

	return;
}
