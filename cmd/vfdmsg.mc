;/*
;   vfdmsg.h
;
;   Virtual Floppy Drive for Windows
;   Driver control program (console version)
;   Message definition
;
;   Copyright (C) 2003-2005 Ken Kato
;*/
;
;#ifndef _VFDMSG_H_
;#define _VFDMSG_H_
;

MessageIdTypedef=DWORD
LanguageNames=(English=0x409:MSG0409)
LanguageNames=(Japanese=0x411:MSG0411)

;//==============================================
;// Generic error messages
;//==============================================
;

MessageId=
SymbolicName=MSG_WRONG_PLATFORM
Language=English
Virtual Floppy Drive does not run on Windows 95/98/Me.
.
Language=Japanese
Windows 95/98/Me では動作しません。
.


MessageId=
SymbolicName=MSG_TOO_MANY_ARGS
Language=English
Too many command line parameters.
.
Language=Japanese
コマンドラインパラメータが多すぎます。
.


MessageId=
SymbolicName=MSG_UNKNOWN_COMMAND
Language=English
Command '%1!s!' is unknown.
.
Language=Japanese
コマンド '%1!s!' が不正です。
.


MessageId=
SymbolicName=MSG_AMBIGUOUS_COMMAND
Language=English
Command '%1!s!' is ambiguous.
.
Language=Japanese
コマンド '%1!s!' は曖昧です。
.


MessageId=
SymbolicName=MSG_UNKNOWN_OPTION
Language=English
Option '%1!s!' is unknown.
.
Language=Japanese
オプション '%1!s!' は不正です。
.


MessageId=
SymbolicName=MSG_DUPLICATE_ARGS
Language=English
Parameter %1!s! is used more than once.
.
Language=Japanese
パラメータ %1!s! が重複しています。
.


;//==============================================
;// Command result message
;//==============================================
;

MessageId=
SymbolicName=MSG_INSTALL_OK
Language=English
Installed the Virtual Floppy driver.
.
Language=Japanese
仮想フロッピドライバをインストールしました。
.


MessageId=
SymbolicName=MSG_INSTALL_NG
Language=English
Failed to install the Virtual Floppy driver.
.
Language=Japanese
仮想フロッピドライバをインストールできません。
.


MessageId=
SymbolicName=MSG_CONFIG_OK
Language=English
Configured the Virtual Floppy driver start method.
.
Language=Japanese
仮想フロッピドライバの起動設定を変更しました。
.


MessageId=
SymbolicName=MSG_CONFIG_NG
Language=English
Failed to configure the Virtual Floppy driver start method.
.
Language=Japanese
仮想フロッピドライバの起動設定を変更できません。
.


MessageId=
SymbolicName=MSG_REMOVE_OK
Language=English
Uninstalled the Virtual Floppy driver.
.
Language=Japanese
仮想フロッピドライバをアンインストールしました。
.


MessageId=
SymbolicName=MSG_REMOVE_NG
Language=English
Failed to uninstall the Virtual Floppy driver.
.
Language=Japanese
仮想フロッピドライバをアンインストールできません。
.


MessageId=
SymbolicName=MSG_REMOVE_PENDING
Language=English
The Virtual Floppy driver is going to be removed on the next system start up.
You may need to restart the system before installing the driver again.
.
Language=Japanese
仮想フロッピドライバは次回のシステム起動時にアンインストールされます。
再インストールする前にシステムを再起動する必要があるかもしれません。
.


MessageId=
SymbolicName=MSG_START_OK
Language=English
Started the Virtual Floppy driver.
.
Language=Japanese
仮想フロッピドライバを開始しました。
.


MessageId=
SymbolicName=MSG_START_NG
Language=English
Failed to start the Virtual Floppy driver.
.
Language=Japanese
仮想フロッピドライバを開始できません。
.


MessageId=
SymbolicName=MSG_STOP_OK
Language=English
Stopped the Virtual Floppy driver.
.
Language=Japanese
仮想フロッピドライバを停止しました。
.


MessageId=
SymbolicName=MSG_STOP_NG
Language=English
Failed to stop the Virtual Floppy driver.
.
Language=Japanese
仮想フロッピドライバを停止できません。
.


MessageId=
SymbolicName=MSG_STOP_PENDING
Language=English
Stop operation has succeeded, but something
is preventing the driver from actually stopping.
You may need to reboot the system before restarting the driver.
.
Language=Japanese
停止処理は成功しましたが、何らかの理由によりドライバの停止が保留されています。
ドライバを再起動する前にシステムを再起動する必要があるかもしれません。
.


MessageId=
SymbolicName=MSG_GET_SHELLEXT_NG
Language=English
Failed to get the shell extension status.
.
Language=Japanese
シェルエクステンションの状態を取得できません。
.


MessageId=
SymbolicName=MSG_SET_SHELLEXT_NG
Language=English
Failed to set the shell extension status.
.
Language=Japanese
シェルエクステンションの状態を設定できません。
.


MessageId=
SymbolicName=MSG_SHELLEXT_ENABLED
Language=English
Shell extension is enabled.
.
Language=Japanese
シェルエクステンションは有効です。
.


MessageId=
SymbolicName=MSG_SHELLEXT_DISABLED
Language=English
Shell extension is disabled.
.
Language=Japanese
シェルエクステンションは無効です。
.


MessageId=
SymbolicName=MSG_OPEN_NG
Language=English
Failed to open the image '%1!s!'.
.
Language=Japanese
イメージ '%1!s!' をオープンできません。
.


MessageId=
SymbolicName=MSG_CLOSE_OK
Language=English
Closed the image on the drive %1!c!.
.
Language=Japanese
ドライブ %1!c! のイメージをクローズしました。
.


MessageId=
SymbolicName=MSG_CLOSE_NG
Language=English
Failed to close the image on the drive %1!c!.
.
Language=Japanese
ドライブ %1!c! のイメージをクローズできません。
.


MessageId=
SymbolicName=MSG_SAVE_OK
Language=English
Saved the image on the drive %1!c! into '%2!s!'.
.
Language=Japanese
ドライブ %1!c! のイメージを '%2!s!' に保存しました。
.


MessageId=
SymbolicName=MSG_SAVE_NG
Language=English
Failed to save the image on the drive %1!c! into '%2!s!'.
.
Language=Japanese
ドライブ %1!c! のイメージを '%2!s!' に保存できません。
.


MessageId=
SymbolicName=MSG_PROTECT_NG
Language=English
Failed to set write protect state on the drive %1!c!.
.
Language=Japanese
ドライブ %1!c! の書き込み保護状態を設定できません。
.


MessageId=
SymbolicName=MSG_FORMAT_OK
Language=English
Format complete.
.
Language=Japanese
フォーマット完了。
.


MessageId=
SymbolicName=MSG_FORMAT_NG
Language=English
Failed to format the drive %1!c!.
.
Language=Japanese
ドライブ %1!c! をフォーマットできません。
.


MessageId=
SymbolicName=MSG_LINK_NG
Language=English
Failed to assign '%2!c!' to the drive %1!lu!.
.
Language=Japanese
ドライブ %1!lu! に '%2!c!' を割り当てることができません。
.


MessageId=
SymbolicName=MSG_UNLINK_NG
Language=English
Failed to unlink the letter from the drive %1!lu!.
.
Language=Japanese
ドライブ %1!lu! のドライブ文字を削除できません。
.


;//==============================================
;// Supplemental result message
;//==============================================
;

MessageId=
SymbolicName=MSG_GET_STAT_NG
Language=English
Failed to get the driver status.
.
Language=Japanese
ドライバの状態を取得できません。
.


MessageId=
SymbolicName=MSG_GET_CONFIG_NG
Language=English
Failed to get the driver configuration.
.
Language=Japanese
ドライバの設定を取得できません。
.


MessageId=
SymbolicName=MSG_GET_VERSION_NG
Language=English
Failed to get the driver version.
.
Language=Japanese
ドライバのバージョンを取得できません。
.


MessageId=
SymbolicName=MSG_WRONG_DRIVER
Language=English
A wrong driver is installed.
.
Language=Japanese
不正なドライバがインストールされています。
.


MessageId=
SymbolicName=MSG_QUERY_UPDATE
Language=English
Update now (y / n) ? %0
.
Language=Japanese
更新しますか (y / n) ? %0
.


MessageId=
SymbolicName=MSG_GET_MEDIA_NG
Language=English
Failed to get the current media status.
.
Language=Japanese
現在のドライブ状態を取得できません。
.


MessageId=
SymbolicName=MSG_GET_FILE_NG
Language=English
Failed to get the image information.
.
Language=Japanese
イメージ情報を取得できません。
.


MessageId=
SymbolicName=MSG_GET_LINK_NG
Language=English
Failed to get the current drive letter.
.
Language=Japanese
現在のドライブ文字を取得できません。
.


MessageId=
SymbolicName=MSG_LINK_FULL
Language=English
No drive letter is available.
.
Language=Japanese
ドライブ文字の空きがありません。
.


MessageId=
SymbolicName=MSG_ACCESS_NG
Language=English
Failed to access the drive %1!c!.
.
Language=Japanese
ドライブ %1!c! にアクセスできません。
.


MessageId=
SymbolicName=MSG_DRIVER_EXISTS
Language=English
The Virtual Floppy driver is already installed.
.
Language=Japanese
仮想フロッピドライバはすでにインストールされています。
.


MessageId=
SymbolicName=MSG_NOT_INSTALLED
Language=English
The Virtual Floppy driver is not installed.
.
Language=Japanese
仮想フロッピドライバはインストールされていません。
.


MessageId=
SymbolicName=MSG_ALREADY_RUNNING
Language=English
The Virtual Floppy driver is already running.
.
Language=Japanese
仮想フロッピドライバは既に起動されています。
.


MessageId=
SymbolicName=MSG_NOT_STARTED
Language=English
The Virtual Floppy driver is not running.
.
Language=Japanese
仮想フロッピドライバは起動されていません。
.


MessageId=
SymbolicName=MSG_TARGET_NOTICE
Language=English
Using the default drive (%1!c!).
.
Language=Japanese
デフォルトドライブ (%1!c!) を使用します。
.


MessageId=
SymbolicName=MSG_CREATE_NOTICE
Language=English
Creating a new image file.
.
Language=Japanese
新規イメージファイルを作成します。
.

MessageId=
SymbolicName=MSG_CREATE_CONFIRM
Language=English
Create a new image file (Y:yes / N:no) ? %0
.
Language=Japanese
新規イメージファイルを作成しますか (Y:はい / N:いいえ) ? %0
.


MessageId=
SymbolicName=MSG_OVERWRITE_NOTICE
Language=English
Overwriting the existing file.
.
Language=Japanese
既存ファイルを上書きします。
.


MessageId=
SymbolicName=MSG_OVERWRITE_CONFIRM
Language=English
Overwrite the existing file (Y:yes / N:no) ? %0
.
Language=Japanese
既存ファイルを上書きしますか (Y:はい / N:いいえ) ? %0
.

MessageId=
SymbolicName=MSG_CREATE_NG
Language=English
Failed to create the new image file '%1!s!'.
.
Language=Japanese
イメージファイル '%1!s!' を作成できません。
.



MessageId=
SymbolicName=MSG_FILE_CREATED
Language=English
Created a new image file.
.
Language=Japanese
新規イメージファイルを作成しました。
.


MessageId=
SymbolicName=MSG_RAM_MEDIA_UNKNOWN
Language=English
A size is not specified for a new RAM image.
.
Language=Japanese
新規 RAM イメージのサイズが指定されていません。
.

MessageId=
SymbolicName=MSG_FILE_MEDIA_UNKNOWN
Language=English
A size is not specified for a new image file.
.
Language=Japanese
新規イメージファイルのサイズが指定されていません。
.

MessageId=
SymbolicName=MSG_CREATE144_NOTICE
Language=English
Creating a 1.44MB image.
.
Language=Japanese
1.44MB イメージを作成します。
.

MessageId=
SymbolicName=MSG_CREATE144_CONFIRM
Language=English
Create a 1.44MB image (Y:yes / N:no) ? %0
.
Language=Japanese
1.44MB イメージを作成しますか (Y:はい / N:いいえ) ? %0
.


MessageId=
SymbolicName=MSG_IMAGE_TOO_SMALL
Language=English
The image is too small.
.
Language=Japanese
イメージが小さすぎます。
.


MessageId=
SymbolicName=MSG_NO_MATCHING_MEDIA
Language=English
The image size (%1!lu! bytes) does not match any supported media.
.
Language=Japanese
イメージサイズ (%1!lu! バイト) に一致するメディアがありません。
.

MessageId=
SymbolicName=MSG_MEDIATYPE_NOTICE
Language=English
Opening as a %1!s! media (%2!lu! bytes).
.
Language=Japanese
%1!s! メディア (%2!lu! バイト) として開きます。
.

MessageId=
SymbolicName=MSG_MEDIATYPE_SUGGEST
Language=English
The largest possible media is %1!s! (%2!lu! bytes).
.
Language=Japanese
選択可能な最大のメディアは %1!s! (%2!lu! バイト) です。
.


MessageId=
SymbolicName=MSG_MEDIATYPE_CONFIRM
Language=English
Open as this media type (Y:yes / N:no) ? %0
.
Language=Japanese
このメディア種別で開きますか (Y:はい / N:いいえ) ? %0
.


MessageId=
SymbolicName=MSG_RAM_MODE_NOTICE
Language=English
Opening the image in RAM mode.
.
Language=Japanese
イメージを RAM モードで開きます。
.


MessageId=
SymbolicName=MSG_RAM_MODE_ONLY
Language=English
This file must be opened in RAM mode.
.
Language=Japanese
このファイルは RAM モードでしか開けません。
.

MessageId=
SymbolicName=MSG_RAM_MODE_CONFIRM
Language=English
Open in RAM mode (Y:yes / N:no) ? %0
.
Language=Japanese
RAM モードで開きますか (Y:はい / N:いいえ) ? %0
.



MessageId=
SymbolicName=MSG_DEFAULT_PROTECT
Language=English
The media will be write protected by default.
.
Language=Japanese
メディアはデフォルトで書き込み保護されます。
.


MessageId=
SymbolicName=MSG_DRIVE_BUSY
Language=English
An image is already opened.
.
Language=Japanese
既にイメージがオープンされています。
.


MessageId=
SymbolicName=MSG_TARGET_REQUIRED
Language=English
Specify a target file to save.
.
Language=Japanese
保存先ファイルを指定してください。
.


MessageId=
SymbolicName=MSG_TARGET_UP_TO_DATE
Language=English
The image file is up to date.
.
Language=Japanese
イメージファイルは最新の状態です。
.

MessageId=
SymbolicName=MSG_OVERWRITE_PROMPT
Language=English
Overwrite the existing file
(O: just overwrite / T: overwrite & truncate / C: cancel) ? %0
.
Language=Japanese
既存ファイルを上書きしますか
(O: 上書きのみ / T: 上書き & サイズ調整 / C: キャンセル) ? %0
.


MessageId=
SymbolicName=MSG_TARGET_IS_ZIP
Language=English
Cannot overwrite a ZIP compressed file.
.
Language=Japanese
ZIP圧縮ファイルへの上書き保存はできません。
.


MessageId=
SymbolicName=MSG_SAVE_FORCE
Language=English
The save operation is forced to continue.
.
Language=Japanese
保存処理は続行されます。
.

MessageId=
SymbolicName=MSG_SAVE_QUIT
Language=English
The save operation is aborted.
.
Language=Japanese
保存処理を中断します。
.


MessageId=
SymbolicName=MSG_FORMAT_FORCE
Language=English
The format operation is forced to continue.
.
Language=Japanese
フォーマット処理は続行されます。
.

MessageId=
SymbolicName=MSG_FORMAT_QUIT
Language=English
The format operation is aborted.
.
Language=Japanese
フォーマット処理を中断します。
.

MessageId=
SymbolicName=MSG_MEDIA_MODIFIED
Language=English
RAM disk data on the drive %1!c!: is modified.
.
Language=Japanese
ドライブ %1!c!: の RAM ディスク内容が更新されています。
.

MessageId=
SymbolicName=MSG_CLOSE_FORCE
Language=English
The close operation is forced to continue.
.
Language=Japanese
クローズ処理は続行されます。
.

MessageId=
SymbolicName=MSG_CLOSE_QUIT
Language=English
The close operation is aborted.
.
Language=Japanese
クローズ処理を中断します。
.

MessageId=
SymbolicName=MSG_CLOSE_CONFIRM
Language=English
Close the image anyway (Y:yes / N:no) ? %0
.
Language=Japanese
このままクローズしますか (Y:はい / N:いいえ) ? %0
.


MessageId=
SymbolicName=MSG_RETRY_FORCE_CANCEL
Language=English
R:retry / F:force / C:cancel ? %0
.
Language=Japanese
R:再試行 / F:強制 / C:キャンセル ? %0
.


MessageId=
SymbolicName=MSG_RETRY_CANCEL
Language=English
R:retry / C:cancel ? %0
.
Language=Japanese
R:再試行 / C:キャンセル ? %0
.


MessageId=
SymbolicName=MSG_LOCK_NG
Language=English
Failed to lock the drive %1!c!.  Some programs may be using the drive.
.
Language=Japanese
ドライブ %1!c! をロックできません。ドライブが使用中の可能性があります。
.


MessageId=
SymbolicName=MSG_STOP_FORCE
Language=English
Failed to close the all drives.  The operation is forced to continue.
.
Language=Japanese
全てのドライブをクローズすることができませんでした。処理は続行されます。
.


MessageId=
SymbolicName=MSG_STOP_QUIT
Language=English
Failed to close the all drives.  The operation is aborted.
.
Language=Japanese
全てのドライブをクローズすることができませんでした。処理を中断します。
.


MessageId=
SymbolicName=MSG_STOP_WARN
Language=English
Failed to close the all drives.  The driver may not be able to unload
properly.  Continue the stop operation?
.
Language=Japanese
全てのドライブをクローズすることができませんでした。ドライバを完全に
停止できない可能性があります。処理を続行しますか？
.


MessageId=
SymbolicName=MSG_REMOVE_FORCE
Language=English
Failed to stop the driver.  The operation is forced to continue;
.
Language=Japanese
ドライバを停止することができませんでしたが、処理は続行されます。
.

MessageId=
SymbolicName=MSG_REMOVE_QUIT
Language=English
Failed to stop the driver.  The operation is aborted.
.
Language=Japanese
ドライバを停止することができませんでした。処理を中断します。
.

MessageId=
SymbolicName=MSG_REMOVE_WARN
Language=English
Failed to stop the driver.  The driver may not be removed completely
until the system is restarted.  Continue the operation?
.
Language=Japanese
ドライバを停止することができませんでした。システムを再起動するまで
完全にアンインストールされない可能性があります。処理を続行しますか？
.


MessageId=
SymbolicName=MSG_UNKNOWN_LONG
Language=English
Unknown (0x%1!08x!)
.
Language=Japanese
不明 (0x%1!08x!)
.


MessageId=
SymbolicName=MSG_DRIVER_FILE
Language=English
Driver     : %1!s!
.
Language=Japanese
ドライバ   : %1!s!
.


MessageId=
SymbolicName=MSG_DRIVER_VERSION
Language=English
Version    : %1!d!.%2!d! %3!s!
.
Language=Japanese
バージョン : %1!d!.%2!d! %3!s!
.


MessageId=
SymbolicName=MSG_START_TYPE
Language=English
Start Type : %0
.
Language=Japanese
開始方法   : %0
.


MessageId=
SymbolicName=MSG_START_AUTO
Language=English
AUTO
.
Language=Japanese
自動
.


MessageId=
SymbolicName=MSG_START_BOOT
Language=English
BOOT
.
Language=Japanese
ブート
.


MessageId=
SymbolicName=MSG_START_DEMAND
Language=English
DEMAND
.
Language=Japanese
手動
.


MessageId=
SymbolicName=MSG_START_DISABLED
Language=English
DISABLED
.
Language=Japanese
無効
.


MessageId=
SymbolicName=MSG_START_SYSTEM
Language=English
SYSTEM
.
Language=Japanese
システム
.


MessageId=
SymbolicName=MSG_DRIVER_STATUS
Language=English
Status     : %0
.
Language=Japanese
現在の状態 : %0
.


MessageId=
SymbolicName=MSG_STATUS_STOPPED
Language=English
STOPPED
.
Language=Japanese
停止
.


MessageId=
SymbolicName=MSG_STATUS_START_P
Language=English
START_PENDING
.
Language=Japanese
開始処理中
.


MessageId=
SymbolicName=MSG_STATUS_STOP_P
Language=English
STOP_PENDING
.
Language=Japanese
停止処理中
.


MessageId=
SymbolicName=MSG_STATUS_RUNNING
Language=English
RUNNING
.
Language=Japanese
実行中
.


MessageId=
SymbolicName=MSG_STATUS_CONT_P
Language=English
CONTINUE_PENDING
.
Language=Japanese
再開処理中
.


MessageId=
SymbolicName=MSG_STATUS_PAUSE_P
Language=English
PAUSE_PENDING
.
Language=Japanese
一時停止処理中
.


MessageId=
SymbolicName=MSG_STATUS_PAUSED
Language=English
PAUSED
.
Language=Japanese
一時停止
.


MessageId=
SymbolicName=MSG_DRIVE_LETTER
Language=English
Drive %1!lu!    : %0
.
Language=Japanese
ドライブ %1!lu! : %0
.


MessageId=
SymbolicName=MSG_PERSISTENT
Language=English
%1!c! (Persistent) %0
.
Language=Japanese
%1!c! (固定) %0
.

MessageId=
SymbolicName=MSG_EPHEMERAL
Language=English
%1!c! (Ephemeral) %0
.
Language=Japanese
%1!c! (一時) %0
.

MessageId=
SymbolicName=MSG_IMAGE_NONE
Language=English
Image      : <none>
.
Language=Japanese
イメージ   : <なし>
.


MessageId=
SymbolicName=MSG_IMAGE_NAME
Language=English
Image      : %1!s!
.
Language=Japanese
イメージ   : %1!s!
.


MessageId=
SymbolicName=MSG_FILE_DESC
Language=English
Description: %1!s!
.
Language=Japanese
詳細       : %1!s!
.

MessageId=
SymbolicName=MSG_DISKTYPE_FILE
Language=English
Type       : FILE
.
Language=Japanese
種別       : ファイル
.


MessageId=
SymbolicName=MSG_DISKTYPE_RAM_CLEAN
Language=English
Type       : RAM (not modified)
.
Language=Japanese
種別       : RAM (データ更新なし)
.


MessageId=
SymbolicName=MSG_DISKTYPE_RAM_DIRTY
Language=English
Type       : RAM (modified)
.
Language=Japanese
種別       : RAM (データ更新あり)
.


MessageId=
SymbolicName=MSG_MEDIA_TYPE
Language=English
Media      : %1!s!
.
Language=Japanese
メディア   : %1!s!
.


MessageId=
SymbolicName=MSG_MEDIA_WRITABLE
Language=English
Access     : Writable
.
Language=Japanese
アクセス   : 書き込み可能
.


MessageId=
SymbolicName=MSG_MEDIA_PROTECTED
Language=English
Access     : Write Protected
.
Language=Japanese
アクセス   : 書き込み保護
.


;//
;// Help message text
;//
MessageId=
SymbolicName=MSG_HINT_INSTALL
Language=English
SYNTAX: %1!s!INSTALL [driver] [/AUTO | /A]
Try '%1!s!HELP INSTALL' for more information.
.
Language=Japanese
使用方法: %1!s!INSTALL [ドライバ] [/AUTO | /A]
詳しくは '%1!s!HELP INSTALL' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_REMOVE
Language=English
SYNTAX: %1!s!REMOVE [/FORCE | /F | /QUIT | /Q]
Try '%1!s!HELP REMOVE' for more information.
.
Language=Japanese
使用方法: %1!s!REMOVE [/FORCE | /F | /QUIT | /Q]
詳しくは '%1!s!HELP REMOVE' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_CONFIG
Language=English
SYNTAX: %1!s!CONFIG {/AUTO | /A | /MANUAL | /M}
Try '%1!s!HELP CONFIG' for more information.
.
Language=Japanese
使用方法: %1!s!CONFIG {/AUTO | /A | /MANUAL | /M}
詳しくは '%1!s!HELP CONFIG' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_START
Language=English
SYNTAX: %1!s!START
Try '%1!s!HELP START' for more information.
.
Language=Japanese
使用方法: %1!s!START
詳しくは '%1!s!HELP START' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_STOP
Language=English
SYNTAX: %1!s!STOP [/FORCE | /F | /QUIT | /Q]
Try '%1!s!HELP STOP' for more information.
.
Language=Japanese
使用方法: %1!s!STOP [/FORCE | /F | /QUIT | /Q]
詳しくは '%1!s!HELP STOP' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_SHELL
Language=English
SYNTAX: %1!s!SHELL [/ON | /OFF]
Try '%1!s!HELP SHELL' for more information.
.
Language=Japanese
使用方法: %1!s!SHELL [/ON | /OFF]
詳しくは '%1!s!HELP SHELL' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_OPEN
Language=English
SYNTAX: %1!s!OPEN [drive:] [file] [/NEW] [/RAM] [/P | /W]
            [ /160 | /180 | /320 | /360 | /640 | /720 | /820 | /120 | /1.20
              | /144 | /1.44 | /168 | /1.68 | /172 | /1.72 | /288 | /2.88 ]
            [ /5 | /525 | /5.25 ] [/F | /FORCE | /Q | QUIT]
Try '%1!s!HELP OPEN' for more information.
.
Language=Japanese
使用方法: %1!s!OPEN [ドライブ:] [ファイル] [/NEW] [/RAM] [/P | /W]
            [ /160 | /180 | /320 | /360 | /640 | /720 | /820 | /120 | /1.20
              | /144 | /1.44 | /168 | /1.68 | /172 | /1.72 | /288 | /2.88 ]
            [ /5 | /525 | /5.25 ] [/FORCE | /F | QUIT | /Q]
詳しくは '%1!s!HELP OPEN' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_CLOSE
Language=English
SYNTAX: %1!s!CLOSE [drive:] [/FORCE | /F | /QUIT | /Q]
Try '%1!s!HELP CLOSE' for more information.
.
Language=Japanese
使用方法: %1!s!CLOSE [ドライブ:] [/FORCE | /F | /QUIT | /Q]
詳しくは '%1!s!HELP CLOSE' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_SAVE
Language=English
SYNTAX: %1!s!SAVE [drive:] [file] [/OVER | /O | /TRUNC | /T]
                     [/FORCE | /F | /QUIT | /Q]
Try '%1!s!HELP SAVE' for more information.
.
Language=Japanese
使用方法: %1!s!SAVE [ドライブ:] [ファイル] [/OVER | /O | /TRUNC | /T]
                       [/FORCE | /F | /QUIT | /Q]
詳しくは '%1!s!HELP SAVE' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_PROTECT
Language=English
SYNTAX: %1!s!PROTECT [drive:] [/ON | /OFF]
Try '%1!s!HELP PROTECT' for more information.
.
Language=Japanese
使用方法: %1!s!PROTECT [ドライブ:] [/ON | /OFF]
詳しくは '%1!s!HELP PROTECT' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_FORMAT
Language=English
SYNTAX: %1!s!FORMAT [drive:] [/FORCE | /F | /QUIT | /Q]
Try '%1!s!HELP FORMAT' for more information.
.
Language=Japanese
使用方法: %1!s!FORMAT [ドライブ:] [/FORCE | /F | /QUIT | /Q]
詳しくは '%1!s!HELP FORMAT' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_LINK
Language=English
SYNTAX: %1!s!LINK [number] [letter] [/L]
Try '%1!s!HELP LINK' for more information.
.
Language=Japanese
使用方法: %1!s!LINK [ドライブ番号] [ドライブ文字] [/L]
詳しくは '%1!s!HELP LINK' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_ULINK
Language=English
SYNTAX: %1!s!ULINK [drive]
Try '%1!s!HELP ULINK' for more information.
.
Language=Japanese
使用方法: %1!s!ULINK [ドライブ]
詳しくは '%1!s!HELP ULINK' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_STATUS
Language=English
SYNTAX: %1!s!STATUS
Try '%1!s!HELP STATUS' for more information.
.
Language=Japanese
使用方法: %1!s!STATUS
詳しくは '%1!s!HELP STATUS' を参照してください.
.


MessageId=
SymbolicName=MSG_HINT_VERSION
Language=English
SYNTAX: %1!s!VERSION
Print version information.
.
Language=Japanese
使用方法: %1!s!VERSION
バージョン情報を表示します。
.


MessageId=
SymbolicName=MSG_HELP_GENERAL
Language=English
Usage:
  %1!s![command [options...]]

Commands:
  INSTALL   Install the Virtual Floppy driver.
  REMOVE    Uninstall the Virtual Floppy driver.
  CONFIG    Configure the Virtual Floppy driver.
  START     Start the Virtual Floppy driver.
  STOP      Stop the Virtual Floppy driver.
  SHELL     Enable/disable the shell extension.
  OPEN      Open a Virtual Floppy image.
  CLOSE     Close a Virtual Floppy image.
  SAVE      Save the current image into a file.
  PROTECT   Enable/disable drive write protect.
  FORMAT    Format the current Virtual Floppy media.
  LINK      Assign a drive letter to a Virtual Floppy drive.
  ULINK     Remove a drive letter from a Virtual Floppy drive.
  STATUS    Print the current status.
  HELP | ?  Print usage help.
  VERSION   Print version information

If a command is not specified, the interactive console is started.
Type '%1!s!HELP CONSOLE' for more information about the interactive
console.

All commands and options are case insensitive.

Shorter command name can be used as long as the command can be
distinguished uniquely: I for INSTALL, REM for REMOVE, etc. are
accepted, but ST is invalid because it is ambiguous.  You have
to type as much as STAR, STO or STAT in order to distinguish them.

'%1!s!command {/? | /h}' shows a brief hint about each command.
.
Language=Japanese
構文：
  %1!s![コマンド [オプション...]]

コマンド：
  INSTALL   ドライバをインストールします。
  REMOVE    ドライバをアンインストールします。
  CONFIG    ドライバの設定を変更します。
  START     ドライバを開始します。
  STOP      ドライバを停止します。
  SHELL     シェルエクステンションを有効／無効にします。
  OPEN      イメージをオープンします。
  CLOSE     現在のイメージをクローズします。
  SAVE      現在のイメージをファイルに保存します。
  PROTECT   ドライブの書き込み保護を有効／無効にします。
  FORMAT    現在の仮想メディアをフォーマットします。
  LINK      ドライブにドライブ文字を割り当てます。
  ULINK     ドライブのドライブ文字を削除します。
  STATUS    現在の状態を表示します。
  HELP | ?  使用方法を表示します。
  VERSION   バージョン情報を表示します。

コマンドを指定しない場合、対話式コンソールを起動します。
対話式コンソールの詳細は '%1!s!HELP CONSOLE' を参照してください。

コマンドおよびオプションの大文字、小文字は区別されません。

コマンドを一意に判別できる範囲でコマンド名を短縮することができます。
I (INSTALL), REM (REMOVE) などは使用可能ですが、ST はあいまいなため
使用できません。この場合は STAR, STO, STAT まで入力しないと区別でき
ません。

'%1!s!コマンド {/? | /h}' で各コマンドの簡単な説明を表示します。
.


MessageId=
SymbolicName=MSG_HELP_INSTALL
Language=English
Install the Virtual Floppy driver.

SYNTAX:
  %1!s!INSTALL [driver] [/AUTO | /A]

OPTIONS:
  driver    Specifies the path to the Virtual Floppy driver file.
            Default is VFD.SYS in the same directory as the VFD
            console program (Note: *NOT* current directory).

  /AUTO     Configures the driver to start at the system startup.
  /A        (Note: *NOT* to start the driver after installation.)
            By default the driver has to be started manually.

Administrator rights are required to install a devide driver.

Device drivers cannot be installed from network drives.
Make sure to place VFD.SYS on a local drive.

It is advised to install the driver with the /AUTO option if the
Virtual Floppy drive is going to be used by users other than
Administrators and Power Users, who don't have enough rights to
start device drivers.
.
Language=Japanese
仮想フロッピドライバをインストールします。

構文：
  %1!s!INSTALL [ドライバ] [/AUTO | /A]

オプション：
  ドライバ  仮想フロッピドライバのパスを指定します。
            省略時は VFD コンソールプログラムと同じディレクトリにある
            VFD.SYS です（カレントディレクトリではありません）。

  /AUTO     仮想フロッピドライバをシステム起動時に自動で開始するよう
  /A        設定します（インストール直後に自動で開始されるのではあり
            ません）。
            省略した場合は必要に応じて手動で開始しなければなりません。

デバイスドライバのインストールには Administrator 権限が必要です。

デバイスドライバはネットワークドライブからインストールすることができ
ません。VFD.SYS ファイルは必ずローカルドライブに置いてください。

Administrator や Power User 以外の、デバイスドライバの開始権限を持た
ないユーザで仮想フロッピドライブを使用する場合には /AUTO オプションを
付けてインストールしておくと良いでしょう。
.


MessageId=
SymbolicName=MSG_HELP_CONFIG
Language=English
Configure the Virtual Floppy driver start method.

SYNTAX:
  %1!s!CONFIG {/AUTO | /A | /MANUAL | /M}

OPTIONS:
  /AUTO     Configures the driver to start at the system startup.
  /A

  /MANUAL   Configures the driver to start on demand.
  /M

The change takes effect the next system start up.
Administrator rights are required to configure a devide driver.
.
Language=Japanese
仮想フロッピドライバの起動方法を設定します。

構文：
  %1!s!CONFIG {/AUTO | /A | /MANUAL | /M}

オプション：
  /AUTO     仮想フロッピドライバをシステム起動時に自動で開始するよう
  /A        設定します（インストール直後に自動で開始されるのではあり

  /MANUAL   仮想フロッピドライバを必要に応じて手動で起動するよう設定
  /M        します。

変更は次回システム起動時から有効になります。
デバイスドライバの設定には Administrator 権限が必要です。
.


MessageId=
SymbolicName=MSG_HELP_REMOVE
Language=English
Uninstall the Virtual Floppy driver.

SYNTAX:
  %1!s!REMOVE [/FORCE | /F | /QUIT | /Q]

OPTIONS:
  /FORCE    Suppress prompting and forces the remove operation when
  /F        the driver cannot be stopped.

  /QUIT     Suppress prompting and quits the remove operation when
  /Q        the driver cannot be stopped.

Closes all images and stops the driver if necessary, then removes the
Virtual Floppy driver entries from the system registry.
This command does not delete the driver file from the local disk.

There are cases, due to the condition of the system, when
uninstallation does not complete immediately and restarting of the
system is required.  In such cases you may not be able to install the
Virtual Floppy driver again until the system is restarted and
uninstallation process is complete.

Administrator rights are required to uninstall a device driver.
.
Language=Japanese
仮想フロッピドライバをアンインストールします。

構文：
  %1!s!REMOVE [/FORCE | /F | /QUIT | /Q]

オプション：
  /FORCE    ドライバが停止できない場合、ユーザに確認を要求せずにアン
  /F        インストール処理を続行します。

  /QUIT     ドライバが停止できない場合、ユーザに確認を要求せずにアン
  /Q        インストール処理を中止します。

必要に応じてイメージのクローズとドライバの停止を行い、システムから
仮想フロッピドライバのエントリを削除します。

ドライバファイル自体をローカルディスクから削除はしません。

システムの状態によってはアンインストールが即座に完了せず、システムの
再起動が必要となる場合があります。その場合、システムを再起動してアン
インストールが完了するまで 仮想フロッピドライバを再びインストールする
ことはできません。

デバイスドライバのアンインストールには Administrator 権限が必要です。
.


MessageId=
SymbolicName=MSG_HELP_START
Language=English
Start the Virtual Floppy driver.

SYNTAX:
  %1!s!START

OPTIONS:
  NONE

If the driver is not installed, this command attempts to install it
with thedefault options.

At least Power User rights are required to start a device driver.
.
Language=Japanese
仮想フロッピドライバを起動します。

構文：
  %1!s!START

オプション：
  なし

ドライバがインストールされていない場合、デフォルトオプションでのイン
ストールを試みます。

デバイスドライバの開始には Power User 以上の権限が必要です。
.


MessageId=
SymbolicName=MSG_HELP_STOP
Language=English
Stop the Virtual Floppy driver

SYNTAX:
  %1!s!STOP [/FORCE | /F | /QUIT | /Q]

OPTIONS:
  /FORCE    Suppress prompting and forces the stop operation when any
  /F        of the drives are in use and cannot be closed.

  /QUIT     Suppress prompting and quits the stop operation when any
  /Q        of the drives are in use and cannot be closed.

This command closes all images before stopping the driver.
An image cannot be closed if the virtual drive is used by any other
programs.  Forcing the stop operation with a drive in use may leave
the driver in stop pending state.  In such cases the driver cannot be
restarted until all programs stop using the drive and the driver is
properly unloaded.

At least Power User rights are required to stop a device driver.
.
Language=Japanese
仮想フロッピドライバを停止します。

構文：
  %1!s!STOP [/FORCE | /F | /QUIT | /Q]

オプション：
  /FORCE    使用中でクローズできないドライブがある場合に、ユーザ確認
  /F        を要求せずに停止処理を続行します。

  /QUIT     使用中でクローズできないドライブがある場合に、ユーザ確認
  /Q        を要求せずに停止処理を中止します。

オープン中のイメージを全てクローズしてからドライバを停止します。
仮想ドライブが他のプログラムから使用されているとイメージをクローズ
することができません。使用中のドライブがあるときに停止処理を強制する
と、ドライバが「停止予約」状態になることがあります。このような場合、
ドライバが完全に停止状態になるまで再起動ができません。

デバイスドライバの停止には Power User 以上の権限が必要です。
.


MessageId=
SymbolicName=MSG_HELP_SHELL
Language=English
Enable / disable the Virtual Floppy drive shell extension.

SYNTAX:
  %1!s!SHELL [/ON | /OFF]

OPTIONS:
  /ON       Enables the shell extension.

  /OFF      Disables the shell extension.

If an option is not specified, this command prints the current state
of the shell extension.
.
Language=Japanese
仮想フロッピドライブシェルエクステンションを有効／無効にします。

構文：
  %1!s!SHELL [/ON | /OFF]

オプション：
  /ON       シェルエクステンションを有効にします。

  /OFF      シェルエクステンションを無効にします。

オプション指定しない場合、現在の状態を表示します。
.


MessageId=
SymbolicName=MSG_HELP_OPEN
Language=English
Open a Virtual Floppy image.

SYNTAX:
  %1!s!OPEN [drive:] [file] [/NEW] [/RAM] [/P | /W]
        [/size] [/media] [/F | /FORCE | /Q | /QUIT]

OPTIONS:
  drive:    Specifies a target Virtual Floppy drive, either by a drive
            number or a drive letter, such as "0:", "1:", "B:", "X:".
            The trailing ':' is required.
            The drive 0 is assumed if not specified.

  file      Specifies a Virtual Floppy image file to open.
            An empty RAM disk is created if not specified.

  /NEW      Creates a new image file.
            Ignored if a file is not specified.

  /RAM      RAM mode - mounts an on-memory copy of the image, instead
            of directly mounting the image file.
            Changes made to the virtual media are lost when the image
            is closed, unless the image is explicitly saved to a file
            with the 'SAVE' command.
            Ignored if a file is not specified.

  /P        Opens the image as a write protected media.
            Write protection state can be chenged later with the
            'PROTECT' command.

  /W        Opens the image as a writable media.
            Write protection state can be chenged later with the
            'PROTECT' command.

  /size     Specifies a media size.  Acceptable options are:

              /160 (160KB)    /820 (820KB)
              /180 (180KB)    /120 or /1.20 (1.20MB)
              /320 (320KB)    /144 or /1.44 (1.44MB)
              /360 (360KB)    /168 or /1.68 (1.68MB DMF)
              /640 (640KB)    /172 or /1.72 (1.72MB DMF)
              /720 (720KB)    /288 or /2.88 (2.88MB)

  /5        Specifies a 5.25 inch media.  Takes effect only with
  /525      640KB, 720KB and 1.2MB media and otherwise ignored.
  /5.25     160KB, 180KB, 320KB and 360KB media are always 5.25".
            820KB, 1.44MB, 1.68MB, 1.72MB and 2.88MB media are always
            3.5".

  /FORCE    Suppress prompring on minor conflicts and/or omission of
  /F        necessary parameters and continues the operation as best
            as possible, employing default values if necessary.
            See below for details.

  /QUIT     Suppress prompring on minor conflicts and/or omission of
  /Q        necessary parameters and quits the operation on the first
            such occasion.
            See below for details.

If the target drive does not have a drive letter, this command also
assigns a local drive letter (see '%1!s!HELP LINK') using the first
available letter.

Read only files, NTFS encrypted/compressed files and ZIP compressed
image files (such as WinImage IMZ file) cannot be mounted directly
and must be opened in RAM mode.

Without a size option, size of a virtual media is decided from the
actual image size.  With an explicit size option you can mount a
file as a smaller media, in such cases surplus data at the end of
the image is ignored.
A virtual media size cannot exceed the actual image size.

The /F and /Q options affect the behavior of the OPEN command in
many ways:

  When the target file does not exist and the /NEW option
  is not present

    (none) ask user whether to create the target
      /F   create the target without asking
      /Q   abort the operation without asking

  The target file exists and the /NEW option is present

    (none) ask user whether to overwrite the existing file
      /F   overwrite the file without asking
      /Q   abort the operation without asking

  The target file cannot be mounted directly and the /RAM
  option is not present

    (none) ask user whether to open in RAM mode
      /F   open in RAM mode without asking
      /Q   abort the operation without asking

  A size option is not present for creating a new image

    (none) ask user whether to create a 1.44MB (default) image
      /F   create a 1.44MB image without asking
      /Q   abort the operation without asking

  A size option is not present and the target file size is
  not an exact match for any of supported media

    (none) ask user whether to mount as a largest media to fit
           in the actual image
      /F   mount as a largest media to fit in the actual image
           without asking
      /Q   abort the operation without asking
.
Language=Japanese
仮想フロッピイメージをオープンします。

構文：
  %1!s!OPEN [ドライブ:] [ファイル] [/NEW] [/RAM] [/P | /W]
        [/サイズ] [/メディア] [/F | /FORCE | /Q | /QUIT]

オプション：
  ドライブ: 対象ドライブをドライブ番号またはドライブ文字で指定します。
            "0:", "1:", "B:", "X:" のように ':' は必須です。
            省略した場合ドライブ 0 が使用されます。

  ファイル  フロッピイメージファイルを指定します。
            省略した場合、空の RAM ディスクが作成されます。

  /NEW      新規イメージファイルを作成します。
            ファイルが指定されていない場合無視されます。

  /RAM      RAM モード - メモリ上にファイルのコピーを作成してマウント
            します。ディスクに加えた変更は、'SAVE' コマンドで明示的に
            ファイルに保存しない限り、イメージをクローズするときに失
            われます。
            ファイルが指定されていない場合無視されます。

  /P        イメージを書き込み保護メディアとしてオープンします。
            書き込み保護状態は、'PROTECT' コマンドを使用して後で変更
            することができます。

  /W        イメージを書き込み可能メディアとしてオープンします。
            書き込み保護状態は、'PROTECT' コマンドを使用して後で変更
            することができます。

  /size     仮想メディアのサイズを指定します。
            以下のオプションが使用できます:

              /160 (160KB)    /820 (820KB)
              /180 (180KB)    /120 or /1.20 (1.20MB)
              /320 (320KB)    /144 or /1.44 (1.44MB)
              /360 (360KB)    /168 or /1.68 (1.68MB DMF)
              /640 (640KB)    /172 or /1.72 (1.72MB DMF)
              /720 (720KB)    /288 or /2.88 (2.88MB)

  /5        5.25 インチメディアを指定します。640KB、720KB および
  /525      1.2MB メディアの場合のみ効果をもち、それ以外の場合は指定
  /5.25     しても無視します。
            160KB, 180KB, 320KB および 360KB メディアは常に 5.25 イン
            チです
            820KB, 1.44MB, 1.68MB, 1.72MB および 2.88MB は常に 3.5 イ
            ンチです。

  /FORCE    オプションの衝突や必要なオプションが省略されていた場合に
  /F        ユーザ確認を要求せずに、必要に応じてデフォルト値を使用し
            たりして可能な限り処理を続行します。
            詳細は下記を参照してください。
            
  /QUIT     オプションの衝突や必要なオプションが省略されていた場合に
  /Q        ユーザ確認を要求せずに、即座に処理を中止します。
            詳細は下記を参照してください。

対象ドライブにドライブ文字が割り当てられていない場合、最初の使用可能
な文字を使用してローカルドライブ文字（'%1!s!HELP LINK' 参照）を
割り当てます。

読み取り専用ファイル、NTFS 暗号化／圧縮ファイル、ZIP 圧縮イメージファ
イル（WinImage IMZ ファイルなど）は直接マウントできないため、必ず RAM
モードモードでオープンしなければなりません。

サイズ指定オプションがない場合、仮想メディアサイズは実際のイメージサ
イズを元に選択されます。明示的にサイズを指定して、実際のイメージより
小さなメディアを選択することも出来ます。この場合、イメージ後半の余分
なデータ領域は無視されます。
実際のイメージサイズを超えるメディアを選択することはできません。

/F オプションおよび /Q オプションによる OPEN コマンドの動作：

  対象ファイルが存在せず、/NEW オプションが指定されていない場合

    (なし) ファイルを作成するかどうかをユーザに確認する
      /F   確認せずにファイルを新規作成する
      /Q   確認せずに処理を中止する

  対象ファイルが存在し、/NEW オプションが指定されている場合

    (なし) 既存ファイルを上書きするかどうかをユーザに確認する
      /F   確認せずにファイルを上書きする
      /Q   確認せずに処理を中止する

  対象ファイルが直接マウントできない種類で、/RAM オプションが
  指定されていない場合

    (なし) RAM モードで開くかどうかをユーザに確認する
      /F   確認せずに RAM モードで開く
      /Q   確認せずに処理を中止する

  新規イメージ作成時に、サイズオプションが指定されていない場合

    (なし) デフォルトの 1.44MB イメージを作成するかどうかを
           ユーザに確認する
      /F   確認せずに 1.44MB イメージを作成する
      /Q   確認せずに処理を中止する

  サイズオプションが指定されておらず、対象ファイルのサイズと
  正確に一致するメディアがない場合

    (なし) イメージ内に収まる最大のメディアを選択するかどうかを
           ユーザに確認する
      /F   確認せずに、イメージ内に収まる最大のメディアを選択する
      /Q   確認せずに処理を中止する
.



MessageId=
SymbolicName=MSG_HELP_CLOSE
Language=English
Close a Virtual Floppy image.

SYNTAX:
  %1!s!CLOSE [drive:] [/FORCE | /F | /QUIT | /Q]

OPTIONS:
  drive:    Specifies a target Virtual Floppy drive, either by a drive
            number or a drive letter, such as "0:", "1:", "B:", "X:".
            The trailing ':' is optional.
            "*" stands for both drives.
            The drive 0 is used if not specified.

  /FORCE    Suppress prompting and forces the close operation when RAM
  /F        disk data is modified or the drive is in use.
            Forcing with the drive in use will work only on Windows
            2000 and later (not on NT).

  /QUIT     Suppress prompting and quits the close operation when RAM
  /Q        disk data is modified or the drive is in use.

If neither /Q nor /F is specified, the user has to choose whether to
retry, force, or quit.

Unlike the previous versions of the VFD, this command does *NOT*
remove the drive letter of the target drive.
.
Language=Japanese
仮想フロッピイメージをクローズします。

構文：
  %1!s!CLOSE [ドライブ:] [/FORCE | /F | /QUIT | /Q]

オプション：
  ドライブ: 対象ドライブをドライブ番号またはドライブ文字で指定します。
            "0:", "1:", "B:", "X:" のように指定します。
            ':' はつけてもつけなくてもかまいません。
            "*" で両ドライブが対象となります。
            省略した場合ドライブ 0 が使用されます。

  /FORCE    RAM ディスクのデータが更新されている場合またはドライブが
  /F        使用中の場合に、ユーザ確認を要求せずにクローズ処理を続行
            します。
            ドライブが使用中の場合の強制クローズは Windows 2000 以降
            で可能です (NT では不可)。

  /QUIT     RAM ディスクのデータが更新されている場合またはドライブが
  /Q        使用中の場合に、ユーザ確認を要求せずにクローズ処理を中止
            します。

以前のバージョンの VFD と異なり、対象ドライブのドライブ文字は削除され
ません。
.


MessageId=
SymbolicName=MSG_HELP_SAVE
Language=English
Save the current image data into a file.

SYNTAX:
  %1!s!SAVE [drive:] [file] [/O | /OVER | /T | /TRUNC]
        [/FORCE | /F | /QUIT | /Q]

OPTIONS:
  drive:    Specifies a target Virtual Floppy drive, either by a drive
            number or a drive letter, such as "0:", "1:", "B:", "X:".
            The trailing ':' is required.
            The drive 0 is used if not specified.

  file      Specifies a file name to save data.
            If not specified, the current image file name is used.
            Required if the current image is a pure RAM disk.

  /OVER     Overwrite the file if the target file exists.
  /O        If the existing file is larger than the current image,
            file size is not changed and the surplus data at the end
            of the file is left unchanged.
            If the target is the current image file, this is the
            default behavior of this command.
            Ignored if the target does not exist.

  /TRUNC    Overwrite the file if the target file exists.
  /T        If the existing file is larger than the current image,
            the file is truncated to the image size and the surplus
            data at the end of the file is discarded.
            Ignored if the target does not exist.

  /FORCE    Suppress prompting when the target volume can not be
  /F        locked and forces the operation without locking.

  /QUIT     Suppress prompting when the target volume can not be
  /Q        locked and quits the operation.

If the target is the current image file, the file is always
overwritten without a question and the /O option is not necessary.
Otherwise this command fails if the target file exists and neither
/O or /T is present.

If the existing file is smaller than the current image, the file
is always expanded to the current image size either with /O or /T.

This program NEVER overwrites a ZIP compressed file regardless of /O
or /T option, or even if it is the current image file.
The SAVE command always fails if the target is a ZIP compressed file.
.
Language=Japanese
現在のイメージをファイルに保存します。

構文：
  %1!s!SAVE [ドライブ:] [ファイル] [/O | /OVER | /T | /TRUNC]
               [/FORCE | /F | /QUIT | /Q]

オプション：
  ドライブ: 対象ドライブをドライブ番号またはドライブ文字で指定します。
            "0:", "1:", "B:", "X:" のように指定します。
            ':' は必須です。
            省略した場合ドライブ 0 が使用されます。

  ファイル  保存先のファイル名を指定します。
            省略した場合は現在のイメージファイル名を使用します。
            ファイルなし RAM ディスクの場合は必須です。

  /OVER     保存先ファイルが存在する場合、上書き保存します。
  /O        既存ファイルが現在のイメージより大きい場合には、ファイル
			サイズは変更されず、ファイル後半のイメージサイズを超える
            部分のデータは変化しません。
            保存先ファイルが存在しない場合は無視されます。
            保存先が現在のイメージファイルの場合にはデフォルトの動作
            となります。

  /TRUNC    保存先ファイルが存在する場合、上書き保存します。
  /T        既存ファイルが現在のイメージより大きい場合には、ファイル
            はイメージサイズに切り詰められ、それ以降のデータは破棄さ
            れます。
            保存先ファイルが存在しない場合は無視されます。

  /FORCE    対象ドライブがロックできない場合に、ユーザ確認を要求せず
  /F        に処理を続行します。

  /QUIT     対象ドライブがロックできない場合に、ユーザ確認を要求せず
  /Q        に処理を中止します。

保存先が現在のイメージファイルの場合には /O オプションの指定は不要で
ファイルは無条件で上書きされます。
それ以外の場合、対象ファイルが存在し /T /O どちらも指定されていない
場合はエラーとなります。

既存ファイルが現在のイメージより小さい場合、/T /O どちらが指定された
場合でも、ファイルがイメージサイズまで拡張されます。

/O /T オプションや、現在のイメージファイルかどうかにかかわらず、ZIP
ファイルの上書きはできません。
保存先が ZIP ファイルの場合コマンドは常にエラーとなります。
.


MessageId=
SymbolicName=MSG_HELP_PROTECT
Language=English
Enable / disable drive write protect.

SYNTAX:
  %1!s!PROTECT [drive:] [/ON | /OFF]

OPTIONS:
  drive:    Specifies a target Virtual Floppy drive, either by a drive
            number or a drive letter, such as "0:", "1:", "B:", "X:".
            The trailing ':' is optional.
            The drive 0 is used if not specified.

  /ON       Enables the drive write protect - the drive becomes read only.

  /OFF      Disables the drive write protect - the drive becomes writable.

If an option is not specified, this command prints the current write
protect state of the drive.

After write protection is disabled with this command, Windows may not
notice the change immediately and claim that the media is still write
protected.  Refreshing the Explorer or retrying the faild operation
will fix that.
.
Language=Japanese
ドライブの書き込み保護を有効／無効にします。

構文：
  %1!s!PROTECT [ドライブ:] [/ON | /OFF]

オプション：
  ドライブ: 対象ドライブをドライブ番号またはドライブ文字で指定します。
            "0:", "1:", "B:", "X:" のように指定します。
            ':' はつけてもつけなくてもかまいません。
            省略した場合ドライブ 0 が使用されます。

  /ON       書き込み保護を有効にします。ドライブは読み取り専用になります。

  /OFF      書き込み保護を無効にします。ドライブは書き込み可能になります。

オプション指定しない場合、現在の状態を表示します。

このコマンドで書き込み保護を無効にした場合に、Windows が即座に変更を
認識せず、メディアがまだ書き込み保護されているとみなす場合があります。
エクスプローラの情報を更新したり、失敗した処理を繰り返せば直ります。
.


MessageId=
SymbolicName=MSG_HELP_FORMAT
Language=English
Format a Virtual Floppy media with FAT.

SYNTAX:
  %1!s!FORMAT [drive:] [/FORCE | /F | /QUIT | /Q]

OPTIONS:
  drive:    Specifies a target Virtual Floppy drive, either by a drive
            number or a drive letter, such as "0:", "1:", "B:", "X:".
            The trailing ':' is optional.
            The drive 0 is used if not specified.

  /FORCE    Suppress prompting when the target volume can not be
  /F        locked and forces the operation without locking.

  /QUIT     Suppress prompting when the target volume can not be
  /Q        locked and quits the operation.
.
Language=Japanese
仮想フロッピメディアを FAT フォーマットします

構文：
  %1!s!FORMAT [ドライブ] [/FORCE | /F | /QUIT | /Q]

オプション：
  ドライブ: 対象ドライブをドライブ番号またはドライブ文字で指定します。
            "0:", "1:", "B:", "X:" のように指定します。
            ':' はつけてもつけなくてもかまいません。
            省略した場合ドライブ 0 が使用されます。

  /FORCE    対象ドライブがロックできない場合に、ユーザ確認を要求せず
  /F        に処理を続行します。

  /QUIT     対象ドライブがロックできない場合に、ユーザ確認を要求せず
  /Q        に処理を中止します。
.


MessageId=
SymbolicName=MSG_HELP_LINK
Language=English
Assign a drive letter to a Virtual Floppy drive.

SYNTAX:
  %1!s!LINK [number] [letter] [/L]

OPTIONS:
  number    Specifies a target drive number.
            If not specified, drive 0 is used.
            "*" stands for both drives.

  letter    Spesifies a drive letter to assign.
            If not specified, the first available letter is used.
            If the target is both drives, letters for each drives can
            be specified like "BF" (B for 0, F for 1).

  /L        Assign an ephemeral / local drive letter.
            The default (without this option) is persistent / global.

Persistent / global drive letters are reclaimed each time the driver
starts.
On Windows 2000 SP2 and later they are not deleted on user logoff.
On Terminal Servers they are globaly visible to all users on the
system.

Ephemeral / local drive letters are not reclaimed on driver start up.
On Windows 2000 SP2 and later they are deleted on user logoff.
On Terminal Servers, they are visible only to the current user and
each user can assign different drive letter to the same drive.
.
Language=Japanese
仮想フロッピドライブにドライブ文字を割り当てます

構文：
  %1!s!LINK [番号] [文字] [/L]

オプション：
  番号      対象ドライブのドライブ番号を指定します。
            省略した場合ドライブ 0 が対象となります。
            "*" で両ドライブが対象となります。

  文字      割り当てるドライブ文字を指定します。
            省略した場合最初の利用可能な文字が割り当てられます。
            両ドライブを対象とする場合、"BF" のように各ドライブに割り
            当てる文字を順に記述することができます。

  /L        一時・ローカルドライブ文字を割り当てます。
            デフォルト (/Lオプションなし) は固定・グローバルです。

固定・グローバルドライブ文字は、ドライバ開始時に毎回割り当てられます。
Windows 2000 SP2 以降でユーザがログオフしても削除されません。
ターミナルサーバでは、ドライブ文字はすべてのユーザに共通となります。

一時・ローカルドライブ文字は、ドライバ開始時には割り当てられません。
Windows 2000 SP2 以降では、ユーザがログオフすると削除されます。
ターミナルサーバでは、ドライブ文字はユーザごとに固有となり、同一の
ドライブにユーザごとに違うドライブ文字を割り当てることもできます。
.


MessageId=
SymbolicName=MSG_HELP_ULINK
Language=English
Remove a drive letter from a Virtual Floppy drive.

SYNTAX:
  %1!s!ULINK [drive]

OPTIONS:
  drive     Specifies a target Virtual Floppy drive, either by a drive
            number or a drive letter.
            If not specified, drive 0 is used.
            "*" stands for both drives.

Drive letters can be removed even if the drive is being used.
Some applications such as Windows Explorer detects it and acts
accordingly, for example closes folder windows for the drive.
.
Language=Japanese
仮想フロッピドライブのドライブ文字を削除します。

構文：
  %1!s!ULINK [ドライブ]

オプション：
  ドライブ  対象ドライブをドライブ番号またはドライブ文字で指定します。
            省略した場合ドライブ 0 が対象となります。
            "*" で両ドライブが対象となります。

ドライブ文字は、ドライブが使用中の場合でも削除することができます。
Windows Explorer など一部のアプリケーションはそれを検知して、たとえば
対象ドライブのフォルダウィンドウを閉じるなど、それに応じた処理を行い
ます。
.


MessageId=
SymbolicName=MSG_HELP_STATUS
Language=English
Print the current status.

SYNTAX:
  %1!s!STATUS

OPTIONS:
  NONE

This command prints the following information:

  Driver file path
  Driver version
  Driver start type
  Driver running state

  Shell extension status

  Drive letter
  Image name
  Image description (file type, size, file attributes, etc.)
  Disk type (RAM or FILE)
  Write protection
.
Language=Japanese
仮想フロッピドライバの情報を表示します。

構文：
  %1!s!STAT

オプション：
  なし

ドライバおよび仮想ドライブの状態に応じて以下の情報を表示します。

  ドライバファイルパス
  ドライババージョン
  ドライバ開始方法
  ドライバの動作状態

  シェルエクステンション状態

  ドライブ文字
  イメージ名称
  イメージ詳細（ファイル種別、サイズ、ファイル属性など）
  ディスク種別（RAM または ファイル）
  書き込み保護
.


MessageId=
SymbolicName=MSG_HELP_HELP
Language=English
Print the VFD console help.

SYNTAX:
  %1!s!HELP [command | topic]

OPTIONS:
  command   Specifies one of the following commands

              INSTALL REMOVE  CONFIG  START   STOP
              SHELL   OPEN    CLOSE   SAVE    PROTECT
              FORMAT  LINK    ULINK   STATUS  HELP
              VERSION

  topic     Specifies one of the following topics

              CONSOLE

If an option is not specified, the general help is printed.
.
Language=Japanese
ヘルプを表示します。

構文：
  %1!s!HELP [コマンド | トピック]

オプション：
  コマンド  以下のコマンドが指定できます:

              INSTALL REMOVE  CONFIG  START   STOP
              SHELL   OPEN    CLOSE   SAVE    PROTECT
              FORMAT  LINK    ULINK   STATUS  HELP
              VERSION

  トピック  以下のトピックが指定できます:

              CONSOLE

オプションを省略した場合は概要ヘルプが表示されます。
.

MessageId=
SymbolicName=MSG_CONSOLE_HINT
Language=English

    ********** the VFD interactive console **********

you can use the following commands in addition to regular VFD commands:

    ATTRIB  CD      CHDIR   <drive>:
    DIR     EXIT    QUIT    BYE
    .(period) + Windows command

Type '? CONSOLE' or 'HELP CONSOLE' for more information

.
Language=Japanese

    ********** VFD 対話式コンソール **********

通常の VFD コマンドに加えて以下のコマンドが使用できます:

    ATTRIB  CD      CHDIR   <ドライブ>:
    DIR     EXIT    QUIT    BYE
    .(ピリオド) + Windows コマンド

詳しくは '? CONSOLE' または 'HELP CONSOLE' を使用してください。

.

MessageId=
SymbolicName=MSG_HELP_CONSOLE
Language=English
In the interactive console, you can use the following commands in
addition to regular VFD commands:

  CD | CHDIR
            Displays the name of or changes the current directory.
            Similar to the Windows CD/CHDIR command.

  <drive>:  Change the current directory to the root of the specified
            drive.  Similar to the Windows drive change command.

  DIR       Executes the Windows DIR command.
            All options for the Windows DIR command are available.

  ATTRIB    Executes the Windows ATTRIB command.
            All options for the Windows ATTRIB command are available.

  EXIT | QUIT | BYE | <Ctrl+C>
            Quits the VFD interactive console.

A command typed with a leading '.'(period) is executed by the Windows
command processor (cmd.exe).

  e.g.) .FORMAT [options ...]
          Executes the Windows format.exe.  All options are passed to
          the format.exe.

        FORMAT [options ...]
          Executes the VFD 'FORMAT' command.

To execute an external command with spaces in its name, put the
'.' (period) outside the quoteation.

  e.g.) ."C:\Program Files\My App\My Program.exe" [options ...]

DIR and ATTRIB Windows commands are recognized without a period,
for they are used very frequently.

Commands to affect current directory and environment variable have
effects only inside the Windows command processor.  You can execute
them but they have no effect on the VFD console.

  .CD .CHDIR .<drive>: to change the current directory
  .PUSHD .POPD
  .PATH to change the search path
  .PROMPT
  .SET to change the value of an environment variable
.
Language=Japanese
対話式コンソールでは、通常の VFD コマンドに加えて以下のコマンドが使用
できます。

  CD | CHDIR
            現在のディレクトリを変更したり、ディレクトリ名を表示したり
            します。Windows 標準の CD/CHDIR コマンドに類似の機能です。

  <ドライブ>:
            現在のディレクトリを指定ドライブのルートに変更します。
            Windows 標準のドライブ変更コマンドに類似の機能です。

  DIR       Windows 標準の DIR コマンドを実行します。
            標準コマンドのオプションは全て使用可能です。

  ATTRIB    Windows 標準の ATTRIB コマンドを実行します。
            標準コマンドのオプションは全て使用可能です。

  EXIT | QUIT | BYE | <Ctrl+C>
            VFD 対話式コンソールを終了します。

先頭に '.'(ピリオド)を付けて入力したコマンドは、Windows のコマンド
プロセッサ(cmd.exe)で実行されます。

  例）.FORMAT [オプション ...]
        Windows 標準の format.exe を実行します。指定したオプションは
        全て format.exe に渡されます。

      FORMAT [オプション ...]
        VFD コンソールの FORMAT コマンドを実行します。

スペースを含む外部コマンドを実行する場合、'.'(ピリオド)は引用符の外に
記述します。

  例) ."C:\Program Files\My App\My Program.exe" [オプション ...]

DIR および ATTRIB Windows 標準コマンドは頻繁に使用するため、ピリオド
なしでも使用できます。

環境変数またはカレントディレクトリを変更するようなコマンドはコマンド
プロセッサの内部でのみ効果を持ちます。ピリオドをつけて実行することは
できますが VFD コンソールには効果がありません：

  .CD .CHDIR <ドライブ>: でカレントディレクトリを変更する
  .PUSHD/.POPD
  .PATH で検索パスを変更する
  .PROMPT
  .SET で環境変数の値を変更する
.


MessageId=
SymbolicName=MSG_PAGER_PROMPT
Language=English
Press any key to continue ('Q' or <Ctrl+C> to quit) ...%0
.
Language=Japanese
続行するには何かキーを押してください ('Q' または <Ctrl+C> で終了）...%0
.

;
;#endif // _VFDMSG_H_
