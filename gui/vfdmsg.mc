;/*
;   vfdmsg.h
;
;   Virtual Floppy Drive for Windows
;   GUI Control Panel
;   Message definition
;
;   Copyright (c) 2003-2008 Ken Kato
;*/
;
;#ifndef _VFDMSG_H_
;#define _VFDMSG_H_
;

MessageIdTypedef=DWORD
LanguageNames=(English=0x409:msg0409)
LanguageNames=(Japanese=0x411:msg0411)

;//====================================
;//	Message text for main dialog
;//====================================
;//
;//	VFDWIN window title
;//
MessageId=
SymbolicName=MSG_APPLICATION_TITLE
Language=English
VFD Control Panel%1!s!%0
.
Language=Japanese
VFD コントロールパネル%1!s!%0
.

;//
;//	Drive 0 tab title
;//
MessageId=
SymbolicName=MSG_DRIVE0_TITLE
Language=English
Drive0%0
.
Language=Japanese
ドライブ0%0
.

;//
;//	Drive 1 tab title
;//
MessageId=
SymbolicName=MSG_DRIVE1_TITLE
Language=English
Drive1%0
.
Language=Japanese
ドライブ1%0
.

;//
;//	Driver tab title
;//
MessageId=
SymbolicName=MSG_DRIVER_TITLE
Language=English
Driver%0
.
Language=Japanese
ドライバ%0
.

;//
;//	Shell tab title
;//
MessageId=
SymbolicName=MSG_SHELL_TITLE
Language=English
Shell%0
.
Language=Japanese
シェル%0
.

;//
;//	Association tab title
;//
MessageId=
SymbolicName=MSG_ASSOC_TITLE
Language=English
Association%0
.
Language=Japanese
関連付け%0
.

;//
;//	About tab title
;//
MessageId=
SymbolicName=MSG_ABOUT_TITLE
Language=English
About%0
.
Language=Japanese
About%0
.

;//
;//	Driver status on status area
;//
MessageId=
SymbolicName=MSG_STAT_DRIVER_STOPPED
Language=English
The VFD driver is stopped.%0
.
Language=Japanese
VFD ドライバは停止中です。%0
.


MessageId=
SymbolicName=MSG_STAT_DRIVER_START_PENDING
Language=English
The VFD driver is start pending.%0
.
Language=Japanese
VFD ドライバは開始処理中です。%0
.


MessageId=
SymbolicName=MSG_STAT_DRIVER_STOP_PENDING
Language=English
The VFD driver is stop pending.%0
.
Language=Japanese
VFD ドライバは停止処理中です。%0
.


MessageId=
SymbolicName=MSG_STAT_DRIVER_RUNNING
Language=English
The VFD driver %1!u!.%2!u!%3!s! is running.%0
.
Language=Japanese
VFD ドライバ %1!u!.%2!u!%3!s! が動作中です。%0
.


MessageId=
SymbolicName=MSG_STAT_DRIVER_CONTINUE_PENDING
Language=English
The VFD driver is continue pending.%0
.
Language=Japanese
VFD ドライバは再開処理中です。%0
.


MessageId=
SymbolicName=MSG_STAT_DRIVER_PAUSE_PENDING
Language=English
The VFD driver is pause pending.%0
.
Language=Japanese
VFD ドライバは一時停止処理中です。%0
.


MessageId=
SymbolicName=MSG_STAT_DRIVER_PAUSED
Language=English
The VFD driver is paused.%0
.
Language=Japanese
VFD ドライバは一時停止中です。%0
.


MessageId=
SymbolicName=MSG_STAT_DRIVER_NOT_INSTALLED
Language=English
The VFD driver is not installed.%0
.
Language=Japanese
VFD ドライバはインストールされていません。%0
.


MessageId=
SymbolicName=MSG_STAT_DRIVER_UNKNOWN_STATE
Language=English
Cannot get the VFD driver state.%0
.
Language=Japanese
VFD ドライバの状態を取得できません。%0
.

;//
;//	Log message text
;//
MessageId=
SymbolicName=MSG_LOG_DRIVER_INSTALLED
Language=English
The VFD driver is installed.
.
Language=Japanese
VFD ドライバがインストールされました。
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_CONFIGURED
Language=English
The VFD driver configuration is changed.
.
Language=Japanese
VFD ドライバ設定が変更されました。
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_REMOVED
Language=English
The VFD driver is uninstalled.
.
Language=Japanese
VFD ドライバがアンインストールされました。
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_REMOVE_PENDING
Language=English
The VFD driver is uninstall pending.
.
Language=Japanese
VFD ドライバがアンインストール処理中です。
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STARTED
Language=English
The VFD driver is started.
.
Language=Japanese
VFD ドライバが開始されました。
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_START_PENDING
Language=English
The VFD driver is start pending.
.
Language=Japanese
VFD ドライバは開始処理中です。
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STOPPED
Language=English
The VFD driver is stopped.
.
Language=Japanese
VFD ドライバが停止されました。
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STOP_PENDING
Language=English
The VFD driver is stop pending.
.
Language=Japanese
VFD ドライバは停止処理中です。
.

MessageId=
SymbolicName=MSG_LOG_IMAGE_OPENED
Language=English
Drive %1!lu!: A virtual floppy image is opened.
.
Language=Japanese
ドライブ %1!lu!: 仮想フロッピイメージがオープンされました。
.

MessageId=
SymbolicName=MSG_LOG_IMAGE_CLOSED
Language=English
Drive %1!lu!: A virtual floppy image is closed.
.
Language=Japanese
ドライブ %1!lu!: 仮想フロッピイメージがクローズされました。
.

MessageId=
SymbolicName=MSG_LOG_LETTER_ASSIGNED
Language=English
Drive %1!lu!: A drive letter is assigned.
.
Language=Japanese
ドライブ %1!lu!: ドライブ文字が割り当てられました。
.

MessageId=
SymbolicName=MSG_LOG_LETTER_REMOVED
Language=English
Drive %1!lu!: A drive letter is removed.
.
Language=Japanese
ドライブ %1!lu!: ドライブ文字が削除されました。
.

MessageId=
SymbolicName=MSG_LOG_PROTECT_ENABLED
Language=English
Drive %1!lu!: Write protected.
.
Language=Japanese
ドライブ %1!lu!: 書き込み保護されました。
.

MessageId=
SymbolicName=MSG_LOG_PROTECT_DISABLED
Language=English
Drive %1!lu!: Write unprotected.
.
Language=Japanese
ドライブ %1!lu!: 書き込み保護解除されました。
.


MessageId=
SymbolicName=MSG_ERR_CHANGE_PROTECT
Language=English
Failed to change the write protect state.
.
Language=Japanese
書き込み保護状態を変更できません。
.


MessageId=
SymbolicName=MSG_ERR_FILE_CREATE
Language=English
Failed to open file '%1!s!'.
.
Language=Japanese
ファイル '%1!s!' を作成できません。
.

MessageId=
SymbolicName=MSG_ERR_FILE_OPEN
Language=English
Failed to open '%1!s!'.
.
Language=Japanese
'%1!s!' をオープンできません。
.



MessageId=
SymbolicName=MSG_ERR_IMAGE_OPEN
Language=English
Failed to open an image.
.
Language=Japanese
イメージをオープンできません。
.


MessageId=
SymbolicName=MSG_ERR_IMAGE_TOO_SMALL
Language=English
The image is too small.
.
Language=Japanese
イメージが小さすぎます。
.


MessageId=
SymbolicName=MSG_ERR_DEVICE_OPEN
Language=English
Failed to open Drive %1!c!.
.
Language=Japanese
ドライブ %1!c! をオープンできません。
.


MessageId=
SymbolicName=MSG_ERR_IMAGE_SAVE
Language=English
Failed to save the image.
.
Language=Japanese
イメージを保存できません。
.


MessageId=
SymbolicName=MSG_IMAGE_SAVED
Language=English
Saved the current image.
.
Language=Japanese
イメージを保存しました。
.


MessageId=
SymbolicName=MSG_ERR_IMAGE_CLOSE
Language=English
Failed to close the image on drive %1!c!.
.
Language=Japanese
ドライブ %1!c! のイメージをクローズできません。
.


MessageId=
SymbolicName=MSG_ERR_IMAGE_FORMAT
Language=English
Failed to format the image.
.
Language=Japanese
イメージをフォーマットできません。
.


MessageId=
SymbolicName=MSG_IMAGE_FORMATTED
Language=English
Formatted the current image.
.
Language=Japanese
イメージがフォーマットされました。
.

;//====================================
;//	Generic text for controls
;//====================================

MessageId=
SymbolicName=MSG_GENERIC_NONE
Language=English
(none)%0
.
Language=Japanese
(なし)%0
.

MessageId=
SymbolicName=MSG_OK_BUTTON
Language=English
OK%0
.
Language=Japanese
OK%0
.

MessageId=
SymbolicName=MSG_CANCEL_BUTTON
Language=English
Cancel%0
.
Language=Japanese
キャンセル%0
.

MessageId=
SymbolicName=MSG_APPLY_BUTTON
Language=English
&Apply%0
.
Language=Japanese
適用(&A)%0
.

;//====================================
;//	Message text for image dialogs
;//====================================

MessageId=
SymbolicName=MSG_LETTER_LABEL
Language=English
Drive Letter: %0
.
Language=Japanese
ドライブ文字: %0
.

MessageId=
SymbolicName=MSG_PERSISTENT
Language=English
Persistent / Global%0
.
Language=Japanese
固定・グローバル%0
.

MessageId=
SymbolicName=MSG_EPHEMERAL
Language=English
Ephemeral / Local%0
.
Language=Japanese
一時・ローカル%0
.

MessageId=
SymbolicName=MSG_CHANGE_BUTTON
Language=English
Change...%0
.
Language=Japanese
変更...%0
.

MessageId=
SymbolicName=MSG_IMAGEFILE_LABEL
Language=English
Image File:%0
.
Language=Japanese
イメージファイル:%0
.

MessageId=
SymbolicName=MSG_DESCRIPTION_LABEL
Language=English
Description:%0
.
Language=Japanese
ファイル情報:%0
.

MessageId=
SymbolicName=MSG_DESC_FILESIZE
Language=English
%1!s! bytes (%2!s!)%0
.
Language=Japanese
%1!s! バイト (%2!s!)%0
.

MessageId=
SymbolicName=MSG_DESC_FILE_RAW
Language=English
RAW image%0
.
Language=Japanese
通常イメージ%0
.

MessageId=
SymbolicName=MSG_DESC_FILE_ZIP
Language=English
ZIP image%0
.
Language=Japanese
ZIPイメージ%0
.

MessageId=
SymbolicName=MSG_ATTR_READONLY
Language=English
ReadOnly%0
.
Language=Japanese
読み取り専用%0
.

MessageId=
SymbolicName=MSG_ATTR_COMPRESSED
Language=English
Compressed%0
.
Language=Japanese
圧縮%0
.

MessageId=
SymbolicName=MSG_ATTR_ENCRYPTED
Language=English
Encrypted%0
.
Language=Japanese
暗号化%0
.

MessageId=
SymbolicName=MSG_DISKTYPE_LABEL
Language=English
Disk Type:%0
.
Language=Japanese
ディスク種別:%0
.

MessageId=
SymbolicName=MSG_MEDIATYPE_LABEL
Language=English
Media Type:%0
.
Language=Japanese
メディア種別:%0
.

MessageId=
SymbolicName=MSG_PROTECT_BUTTON
Language=English
&Write Protect%0
.
Language=Japanese
書き込み保護(&W)%0
.

MessageId=
SymbolicName=MSG_OPEN_BUTTON
Language=English
&Open/Create...%0
.
Language=Japanese
開く/新規(&O)...%0
.


MessageId=
SymbolicName=MSG_SAVE_BUTTON
Language=English
&Save...%0
.
Language=Japanese
保存(&S)...%0
.


MessageId=
SymbolicName=MSG_CLOSE_BUTTON
Language=English
&Close%0
.
Language=Japanese
閉じる(&C)%0
.

MessageId=
SymbolicName=MSG_FORMAT_BUTTON
Language=English
&Format%0
.
Language=Japanese
フォーマット(&F)%0
.


;//====================================
;//	Drive letter dialog title
;//====================================

MessageId=
SymbolicName=MSG_LETTER_TITLE
Language=English
Drive Letter%0
.
Language=Japanese
ドライブ文字%0
.

;//====================================
;//	Message text for driver dialog
;//====================================

MessageId=
SymbolicName=MSG_DRIVER_LABEL
Language=English
Driver &File:%0
.
Language=Japanese
ドライバ(&D):%0
.

MessageId=
SymbolicName=MSG_BROWSE_BUTTON
Language=English
&Browse...%0
.
Language=Japanese
参照(&B)...%0
.

MessageId=
SymbolicName=MSG_VERSION_LABEL
Language=English
Version:%0
.
Language=Japanese
バージョン:%0
.

MessageId=
SymbolicName=MSG_START_LABEL
Language=English
Start Type:%0
.
Language=Japanese
開始種別:%0
.

MessageId=
SymbolicName=MSG_START_MANUAL
Language=English
&Manual%0
.
Language=Japanese
手動(&M)%0
.

MessageId=
SymbolicName=MSG_START_AUTO
Language=English
&Auto%0
.
Language=Japanese
自動(&A)%0
.

MessageId=
SymbolicName=MSG_INSTALL_BUTTON
Language=English
&Install%0
.
Language=Japanese
インストール(&I)%0
.

MessageId=
SymbolicName=MSG_START_BUTTON
Language=English
&Start%0
.
Language=Japanese
開始(&S)%0
.

MessageId=
SymbolicName=MSG_STOP_BUTTON
Language=English
&Stop%0
.
Language=Japanese
停止(&S)%0
.

MessageId=
SymbolicName=MSG_REMOVE_BUTTON
Language=English
&Uninstall%0
.
Language=Japanese
ｱﾝｲﾝｽﾄｰﾙ(&U)%0
.

MessageId=
SymbolicName=MSG_DRIVER_OPEN_TITLE
Language=English
VFD Driver%0
.
Language=Japanese
VFD ドライバ%0
.

MessageId=
SymbolicName=MSG_DRIVER_OPEN_FILTER
Language=English
VFD Driver (vfd.sys)|vfd.sys|%0
.
Language=Japanese
VFD ドライバ (vfd.sys)|vfd.sys|%0
.

MessageId=
SymbolicName=MSG_ERR_DRIVER_INSTALL
Language=English
Failed to install the VFD driver.
.
Language=Japanese
VFD ドライバをインストールできません。
.

MessageId=
SymbolicName=MSG_ERR_DRIVER_REMOVE
Language=English
Failed to uninstall the VFD driver.
.
Language=Japanese
VFD ドライバをアンインストールできません。
.

MessageId=
SymbolicName=MSG_ERR_DRIVER_START
Language=English
Failed to start the VFD driver.
.
Language=Japanese
VFD ドライバを開始できません。
.

MessageId=
SymbolicName=MSG_ERR_DRIVER_STOP
Language=English
Failed to stop the VFD driver.
.
Language=Japanese
VFD ドライバを停止できません。
.

MessageId=
SymbolicName=MSG_ERR_DRIVER_CONFIG
Language=English
Failed to configure the VFD driver.
.
Language=Japanese
VFD ドライバの設定を変更できません。
.

MessageId=
SymbolicName=MSG_CONFIRM_REMOVE
Language=English
Failed to stop the driver.
It may not unload properly.
Proceed?%0
.
Language=Japanese
ドライバを停止できませんでした。
正常にアンロードできない可能性があります。
処理を続行しますか？%0
.

;//====================================
;//	Message text for shell dialog
;//====================================

;//	text for tree view items
MessageId=
SymbolicName=MSG_TREE_SHELLEXT
Language=English
Shell Extensions%0
.
Language=Japanese
シェルエクステンション%0
.

MessageId=
SymbolicName=MSG_TREE_CONFIG
Language=English
Shortcut to the VFD Control Panel%0
.
Language=Japanese
VFDコントロールパネルのショートカット%0
.

MessageId=
SymbolicName=MSG_TREE_DRIVE0
Language=English
Shortcut to the VFD drive 0%0
.
Language=Japanese
VFDドライブ0のショートカット%0
.


MessageId=
SymbolicName=MSG_TREE_DRIVE1
Language=English
Shortcut to the VFD drive 1%0
.
Language=Japanese
VFDドライブ1のショートカット%0
.


MessageId=
SymbolicName=MSG_TREE_DRIVE1_NT
Language=English
Windows NT does not properly handle the shortcut to drive 1%0
.
Language=Japanese
Windows NTでは、ドライブ1のショートカットは正常に動作しません%0
.


MessageId=
SymbolicName=MSG_ITEM_SHELLEXT
Language=English
Context menu, drag & drop handler and drive property sheet%0
.
Language=Japanese
コンテキストメニュー、ドラッグ＆ドロップ、プロパティシート%0
.

MessageId=
SymbolicName=MSG_ITEM_SHELLEXT_NT
Language=English
Context menu and drive property sheet%0
.
Language=Japanese
コンテキストメニュー、プロパティシート%0
.

MessageId=
SymbolicName=MSG_ITEM_DESKTOP
Language=English
Create on the Desktop%0
.
Language=Japanese
デスクトップに作成する%0
.

MessageId=
SymbolicName=MSG_ITEM_STARTMENU
Language=English
Create in the Start Menu%0
.
Language=Japanese
スタートメニューに作成する%0
.

MessageId=
SymbolicName=MSG_ITEM_SENDTO
Language=English
Create in the SendTo folder%0
.
Language=Japanese
SendToフォルダに作成する%0
.

;// Shortcut link name for VFD drives

MessageId=
SymbolicName=MSG_LINK_DRIVE
Language=English
VFD drive %1!d!%0
.
Language=Japanese
VFDドライブ%1!d!%0
.

;// Shortcut link name for the VFD control panel
MessageId=
SymbolicName=MSG_LINK_CONFIG
Language=English
VFD Control Panel%0
.
Language=Japanese
VFDコントロールパネル%0
.

;//====================================
;//	Message text for association dialog
;//====================================

MessageId=
SymbolicName=MSG_NEW_BUTTON
Language=English
&New Extension%0
.
Language=Japanese
新規拡張子(&N)%0
.

MessageId=
SymbolicName=MSG_CHECK_ALL
Language=English
&Check All%0
.
Language=Japanese
全てチェック(&C)%0
.

MessageId=
SymbolicName=MSG_CLEAR_ALL
Language=English
&Uncheck All%0
.
Language=Japanese
全てクリア(&U)%0
.

MessageId=
SymbolicName=MSG_EXT_HEADER
Language=English
Extension%0
.
Language=Japanese
拡張子%0
.

MessageId=
SymbolicName=MSG_APP_HEADER
Language=English
Program%0
.
Language=Japanese
プログラム%0
.


MessageId=
SymbolicName=MSG_ASSOC_CANT_WRITE
Language=English
Not enough rights to edit file association.%0
.
Language=Japanese
関連付けを変更する権限がありません。%0
.


MessageId=
SymbolicName=MSG_ASSOC_CANT_READ
Language=English
Failed to read the association information.%0
.
Language=Japanese
関連付け情報を読み取れませんでした。%0
.


MessageId=
SymbolicName=MSG_ASSOC_FILETYPE_DESC
Language=English
Floppy Image%0
.
Language=Japanese
フロッピイメージ%0
.

MessageId=
SymbolicName=MSG_ASSOC_FILETYPE_VERB
Language=English
Open with &VFD%0
.
Language=Japanese
&VFD で開く%0
.

;//====================================
;//	New extension dialog title
;//====================================

MessageId=
SymbolicName=MSG_NEWEXT_TITLE
Language=English
New Extension%0
.
Language=Japanese
新規拡張子%0
.


MessageId=
SymbolicName=MSG_NEWEXT_LABEL
Language=English
Extension:%0
.
Language=Japanese
拡張子:%0
.

;//====================================
;//	Message text for about dialog
;//====================================
;//
;//	information url
;//
MessageId=
SymbolicName=MSG_ABOUT_URL
Language=English
http://chitchat.at.infoseek.co.jp/vmware/vfd.html%0
.
Language=Japanese
http://chitchat.at.infoseek.co.jp/vmware/vfdj.html%0
.

;//
;//	Help text
;//
MessageId=
SymbolicName=MSG_HELP_TEXT
Language=English
Command Line
============

VfdWin.exe
  Start the Virtual Floppy Drive Control Panel.

VfdWin.exe /OPEN [drive:] [file] [/RAM] [/P | /W] [/size] [/5] [/Q]
  Open an image on a Virtual Floppy Drive.

  drive:	Specifies a target Virtual Floppy drive, either by a drive
	number or a drive letter, such as "0:", "1:", "B:", "X:".
	The trailing ':' is required.
	The drive 0 is used if not specified.

  file	Specifies a Virtual Floppy image file to open.
	If the file does not exist, a new file is created.
	If not specified, an empty RAM disk is created.

  /RAM	RAM mode - Creates a copy of the file on RAM.
	Changes made to the disk are lost when the image is
	closed.  Read only files, NTFS encrypted/compressed files
	and WinImage compressed image (IMZ) files are always
	opened in RAM mode.
	This option is needed only to open other files, which are
	usually mounted directly, in RAM mode.

  /P	Opens the image as a write protected media.
	This is the default for RAM mode (except for empty RAM
	disks).

  /W	Opens the image as a writable media.
	This is the default for non-RAM and empty RAM disks.

  /size	Specifies a media size.
	The following options are accepted:

	/160 (160KB)    /820 (820KB)
	/180 (180KB)    /120 or /1.20 (1.20MB)
	/320 (320KB)    /144 or /1.44 (1.44MB)
	/360 (360KB)    /168 or /1.68 (1.68MB DMF)
	/640 (640KB)    /172 or /1.72 (1.72MB DMF)
	/720 (720KB)    /288 or /2.88 (2.88MB)

	If not specified, the media is decided from the file size
	for opening an existing file, and 1.44MB is selected for
	creating new file.
	Cannot specify a larger media than the target file.

  /5	Specifies a 5.25" media.  Takes effect only with
	640KB, 720KB and 1.2MB media.

  /Q	Do not open the drive folder afterward.

  If the target drive does not have a drive letter, this command also
  assigns the first available letter to the drive.

VfdWin.exe /CLOSE [drive:]
  Close the image.

  drive:	Specifies a target Virtual Floppy drive, either by a drive
	number or a drive letter, such as "0:", "1", "B:", "X".
	You may or may not add the trailing ':' to the drive letter.
	"*" stands for both drives.
	The drive 0 is used if not specified.
.
Language=Japanese
コマンドライン
==============

VfdWin.exe
  VFD コントロールパネルを起動します。

VfdWin.exe /OPEN [ドライブ:] [ファイル] [/RAM] [/P | /W] [/サイズ] [/5] [/Q]
  仮想フロッピイメージをオープンします。

  ドライブ:	対象ドライブを、ドライブ番号またはドライブ文字で指定します。
	"0:", "1:", "B:", "X:" のようにコロン（':'）は必須です。
	省略した場合ドライブ 0 が使用されます。

  ファイル	フロッピイメージファイルを指定します。
	指定ファイルが存在しない場合、新規ファイルが作成されます。
	省略した場合、空の RAM ディスクが作成されます。

  /RAM	RAM モード - RAM 上にファイルのコピーを作成します。
	ディスクに加えた変更は、イメージをクローズすると失われます。
	読み取り専用ファイル、NTFS 暗号化／圧縮ファイル、WinImage
	圧縮イメージ (IMZ) ファイルは常に RAM モードとなります。
	それ以外の通常は直接マウントされるファイルを RAM モードで
	オープンしたい場合にのみこのオプションが必要となります。

  /P	イメージを書き込み保護メディアとしてオープンします。
	RAM モード(空の RAM ディスクを除く) の場合のデフォルトです。

  /W	イメージを書き込み可能メディアとしてオープンします。
	直接モードおよび空の RAM ディスクの場合のデフォルトです。

  /size	メディアサイズを指定します。以下のオプションが使用できます:

	/160 (160KB)    /820 (820KB)
	/180 (180KB)    /120 or /1.20 (1.20MB)
	/320 (320KB)    /144 or /1.44 (1.44MB)
	/360 (360KB)    /168 or /1.68 (1.68MB DMF)
	/640 (640KB)    /172 or /1.72 (1.72MB DMF)
	/720 (720KB)    /288 or /2.88 (2.88MB)

	省略した場合、既存ファイルの場合はファイルサイズから選択され、
	新規イメージの場合は 1.44MB がデフォルトとなります。
	既存ファイルを開く場合、ファイルサイズより大きなメディアを指定
	することはできません。

  /5	5.25 インチメディアを指定します。
	640KB, 720KB, 1.2MB メディアの場合のみ意味を持ちます。

  /Q	イメージをオープンした後、ドライブフォルダを開きません。

  対象ドライブにドライブ文字が割り当てられていない場合、
  最初の使用可能な文字が割り当てられます。

VfdWin.exe /CLOSE [ドライブ:]
  仮想フロッピイメージをクローズします。

  ドライブ:	対象ドライブを、ドライブ番号またはドライブ文字で指定します。
	"0:", "1", "B:", "X" のようにコロン(':') は付けても付けなくても
	かまいません。
	"*" で両方のドライブが対象になります。
	省略した場合ドライブ 0 が対象になります。
.


MessageId=
SymbolicName=MSG_ERR_APP_INTERNAL
Language=English
Application intrnal error.
.
Language=Japanese
アプリケーション内部エラーです。
.

MessageId=
SymbolicName=MSG_ERR_WRONG_PLATFORM
Language=English
Virtual Floppy Drive does not run on Windows 95/98/Me.
.
Language=Japanese
Windows 95/98/Me では動作しません。
.

MessageId=
SymbolicName=MSG_ERR_INVALID_PARAM
Language=English
Invalid command line parameter %1!s!.
.
Language=Japanese
不正なコマンドライン引数です。%1!s!
.

MessageId=
SymbolicName=MSG_ERR_INVALID_SIZE
Language=English
Invalid image size.
.
Language=Japanese
イメージサイズが不正です。
.

MessageId=
SymbolicName=MSG_HELP_TAB_CONTROL
Language=English
Select a tab to display a child page.%0
.
Language=Japanese
タブを選択してページを表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_LOG_MESSAGE
Language=English
Displays operation log message.%0
.
Language=Japanese
操作ログを表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_STATE
Language=English
Displays the current driver state.%0
.
Language=Japanese
現在のドライバ状態を表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_LETTER
Language=English
A drive letter assigned to
the Virtual Floppy drive.%0
.
Language=Japanese
仮想フロッピドライブに割り当てた
ドライブ文字を表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_CHANGE
Language=English
Change drive letter assignment.%0
.
Language=Japanese
ドライブ文字の割り当てを変更します。%0
.
MessageId=
SymbolicName=MSG_HELP_IMAGEFILE
Language=English
Displays the current virtual floppy image.%0
.
Language=Japanese
現在の仮想フロッピイメージを表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_DESCRIPTION
Language=English
Displays the image information.%0
.
Language=Japanese
イメージ情報を表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_DISKTYPE
Language=English
Displays the virtual disk type.%0
.
Language=Japanese
仮想ディスク種別を表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_MEDIATYPE
Language=English
Displays the virtual media type.%0
.
Language=Japanese
仮想メディア種別を表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_PROTECT
Language=English
Enable/disable the write protection.
The change takes effect immediately.%0
.
Language=Japanese
書き込み可能／禁止を切り替えます。
変更は即座に適用されます。%0
.
MessageId=
SymbolicName=MSG_HELP_OPEN
Language=English
Open or create a virtual floppy image.%0
.
Language=Japanese
仮想フロッピイメージをオープンまたは新規作成します。%0
.
MessageId=
SymbolicName=MSG_HELP_SAVE
Language=English
Save the current image to a file.%0
.
Language=Japanese
現在のイメージをファイルに保存します。%0
.
MessageId=
SymbolicName=MSG_HELP_CLOSE
Language=English
Close the current image.%0
.
Language=Japanese
現在のイメージを閉じます。%0
.
MessageId=
SymbolicName=MSG_HELP_FORMAT
Language=English
Format the current virtual media with FAT.%0
.
Language=Japanese
現在の仮想メディアをFATフォーマットします。%0
.
MessageId=
SymbolicName=MSG_HELP_DRIVER
Language=English
The VFD driver file path.%0
.
Language=Japanese
VFDドライバファイルパス。%0
.
MessageId=
SymbolicName=MSG_HELP_BROWSE
Language=English
Browse for folders to find the driver file.%0
.
Language=Japanese
フォルダを参照してドライバファイルを検索します。%0
.
MessageId=
SymbolicName=MSG_HELP_VERSION
Language=English
Displays the driver file version.%0
.
Language=Japanese
ドライバファイルバージョンを表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_STARTTYPE
Language=English
The driver start type
Manual: the driver must be started manually.
Auto: the driver is started on system start up.%0
.
Language=Japanese
ドライバ開始方法
手動：ドライバは手動で開始します。
自動：ドライバはシステム起動時に開始されます。%0
.
MessageId=
SymbolicName=MSG_HELP_INSTALL
Language=English
Install the driver.%0
.
Language=Japanese
ドライバをインストールします。%0
.
MessageId=
SymbolicName=MSG_HELP_START
Language=English
Start the driver.%0
.
Language=Japanese
ドライバを開始します。%0
.
MessageId=
SymbolicName=MSG_HELP_STOP
Language=English
Stop the driver.%0
.
Language=Japanese
ドライバを停止します。%0
.
MessageId=
SymbolicName=MSG_HELP_REMOVE
Language=English
Uninstall the driver from system.
The driver file is not removed.%0
.
Language=Japanese
ドライバをシステムからアンインストールします。
ドライバファイルは削除されません。%0
.
MessageId=
SymbolicName=MSG_HELP_LIST
Language=English
List of the current association.%0
.
Language=Japanese
現在の関連付けの一覧。%0
.
MessageId=
SymbolicName=MSG_HELP_MESSAGE
Language=English
Displays the reason why the
association cannot be edited.%0
.
Language=Japanese
関連付けを編集できない理由を表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_NEW
Language=English
Add a new extension to show in the list.%0
.
Language=Japanese
リストに表示する拡張子を追加します。%0
.
MessageId=
SymbolicName=MSG_HELP_ALL
Language=English
Check all items in the list.%0
.
Language=Japanese
リスト内の全項目をチェックします。%0
.
MessageId=
SymbolicName=MSG_HELP_CLEAR
Language=English
Uncheck all items in the list.%0
.
Language=Japanese
リスト内の全項目のチェックをはずします。%0
.
MessageId=
SymbolicName=MSG_HELP_APPLY
Language=English
Apply the current change.%0
.
Language=Japanese
現在までの変更を適用します。%0
.
MessageId=
SymbolicName=MSG_HELP_TREE
Language=English
Displays a list of shell related features.%0
.
Language=Japanese
シェル関連機能の一覧を表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_PRODUCT
Language=English
Displays the product name.%0
.
Language=Japanese
プログラム名称を表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_URL
Language=English
Click to open the page in the browser.%0
.
Language=Japanese
クリックすると、ブラウザでページを開きます。%0
.
MessageId=
SymbolicName=MSG_HELP_HELP
Language=English
Displays the command line usage of this program.%0
.
Language=Japanese
コマンドラインの使用方法を表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_COPYRIGHT
Language=English
Displays the copyright information.%0
.
Language=Japanese
コピーライト情報を表示します。%0
.
MessageId=
SymbolicName=MSG_HELP_EXTENSION
Language=English
Enter a file extension to associate.
A leading period is optional.%0
.
Language=Japanese
関連付けする拡張子を入力します。
ピリオドは省略することができます。%0
.
MessageId=
SymbolicName=MSG_HELP_PERSISTENT
Language=English
Make the drive letter global/persistent.%0
.
Language=Japanese
グローバル・持続ドライブ文字を割り当てます。%0
.
;
;#endif // _VFDMSG_H_
