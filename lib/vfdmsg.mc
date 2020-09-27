;/*
;   vfdmsg.h
;
;   Virtual Floppy Drive for Windows
;   Driver control library
;   Message definition
;
;   Copyright (c) 2003-2005 Ken Kato
;*/
;
;#ifndef _VFDMSG_H_
;#define _VFDMSG_H_
;

MessageIdTypedef=DWORD
LanguageNames=(English=0x409:msg0409)
LanguageNames=(Japanese=0x411:msg0411)

;
;//
;//	Context menu text
;//
;
MessageId=
SymbolicName=MSG_MENU_OPEN
Language=English
&Open VFD image...%0
.
Language=Japanese
VFDイメージを開く(&O)...%0
.

MessageId=
SymbolicName=MSG_HELP_OPEN
Language=English
Open a virtual floppy image.%0
.
Language=Japanese
仮想フロッピイメージを開きます。%0
.

MessageId=
SymbolicName=MSG_MENU_CLOSE
Language=English
&Close VFD image%0
.
Language=Japanese
VFDイメージを閉じる(&C)%0
.

MessageId=
SymbolicName=MSG_HELP_CLOSE
Language=English
Close the current virtual floppy image.%0
.
Language=Japanese
現在の仮想フロッピイメージを閉じます。%0
.


MessageId=
SymbolicName=MSG_MENU_SAVE
Language=English
&Save VFD image...%0
.
Language=Japanese
VFDイメージを保存(&S)...%0
.

MessageId=
SymbolicName=MSG_HELP_SAVE
Language=English
Save the current image into a file.%0
.
Language=Japanese
現在のイメージをファイルに保存します。%0
.


MessageId=
SymbolicName=MSG_MENU_PROTECT
Language=English
&Write Protect%0
.
Language=Japanese
書き込み保護(&W)%0
.

MessageId=
SymbolicName=MSG_HELP_PROTECT
Language=English
Enable/disable the media write protection.%0
.
Language=Japanese
メディアの書き込み保護を切り替えます。%0
.


MessageId=
SymbolicName=MSG_MENU_PROP
Language=English
VFD &Property%0
.
Language=Japanese
VFDプロパティ(&P)%0
.

MessageId=
SymbolicName=MSG_HELP_PROP
Language=English
Display the VFD property page.%0
.
Language=Japanese
VFDプロパティページを表示します。%0
.

MessageId=
SymbolicName=MSG_MENU_DROP
Language=English
&Open with VFD%0
.
Language=Japanese
VFDで開く(&O)%0
.

MessageId=
SymbolicName=MSG_HELP_DROP
Language=English
Open the file with VFD.%0
.
Language=Japanese
ファイルをVFDで開きます。%0
.

;
;//
;//	Dialog title text
;//
;

MessageId=
SymbolicName=MSG_OPEN_TITLE
Language=English
Open Virtual Floppy Image%0
.
Language=Japanese
仮想フロッピイメージを開く%0
.


MessageId=
SymbolicName=MSG_SAVE_TITLE
Language=English
Save Virtual Floppy Image%0
.
Language=Japanese
仮想フロッピイメージを保存%0
.

;
;//
;//	Dialog label text
;//
;

MessageId=
SymbolicName=MSG_IMAGEFILE_LABEL
Language=English
Image File:%0
.
Language=Japanese
イメージ:%0
.

MessageId=
SymbolicName=MSG_IMAGEFILE_ACCEL
Language=English
&Image File:%0
.
Language=Japanese
イメージ(&I):%0
.

MessageId=
SymbolicName=MSG_DESCRIPTION_LABEL
Language=English
Description:%0
.
Language=Japanese
詳細:%0
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
SymbolicName=MSG_MEDIATYPE_ACCEL
Language=English
&Media Type:%0
.
Language=Japanese
メディア種別(&M):%0
.



MessageId=
SymbolicName=MSG_TARGETFILE_LABEL
Language=English
&Target File:%0
.
Language=Japanese
保存先:%0
.

;
;//
;//	button text
;//
;

MessageId=
SymbolicName=MSG_OPEN_BUTTON
Language=English
&Open%0
.
Language=Japanese
開く(&O)%0
.


MessageId=
SymbolicName=MSG_CREATE_BUTTON
Language=English
&Create%0
.
Language=Japanese
作成(&C)%0
.


MessageId=
SymbolicName=MSG_SAVE_BUTTON
Language=English
&Save%0
.
Language=Japanese
保存(&S)%0
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


MessageId=
SymbolicName=MSG_CONTROL_BUTTON
Language=English
&VFD Control Panel%0
.
Language=Japanese
VFDコントロールパネル(&V)%0
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
SymbolicName=MSG_CANCEL_BUTTON
Language=English
Cancel%0
.
Language=Japanese
キャンセル%0
.

MessageId=
SymbolicName=MSG_OVERWRITE_CHECK
Language=English
Overwrite an existing file.%0
.
Language=Japanese
既存ファイルを上書きする。%0
.


MessageId=
SymbolicName=MSG_TRUNCATE_CHECK
Language=English
Truncate an existing file.%0
.
Language=Japanese
既存ファイルサイズを切り詰める。%0
.

;
;//
;//	file description text
;//
;
MessageId=
SymbolicName=MSG_FILETYPE_RAW
Language=English
RAW image%0
.
Language=Japanese
通常イメージ%0
.

MessageId=
SymbolicName=MSG_FILETYPE_ZIP
Language=English
ZIP image%0
.
Language=Japanese
ZIPイメージ%0
.

MessageId=
SymbolicName=MSG_DESC_NEW_FILE
Language=English
New file%0
.
Language=Japanese
新規ファイル%0
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


;
;//
;// ToolTip
;//
;
MessageId=
SymbolicName=MSG_WRITE_PROTECTED
Language=English
&Write Protected%0
.
Language=Japanese
書き込み保護%0
.

MessageId=
SymbolicName=MSG_WRITE_ALLOWED
Language=English
Write Allowed%0
.
Language=Japanese
書き込み可能%0
.

MessageId=
SymbolicName=MSG_IMAGE_INFOTIP
Language=English
%1!s!
%2!s!
Type: %3!s! disk
Media: %4!s!
%5!s!%0
.
Language=Japanese
%1!s!
%2!s!
種別: %3!s! ディスク
メディア: %4!s!
%5!s!%0
.

;
;//
;// Context help text
;//
;

MessageId=
SymbolicName=MSG_HELP_IMAGEFILE
Language=English
Image file name.%0
.
Language=Japanese
イメージファイル名。%0
.


MessageId=
SymbolicName=MSG_HELP_IMAGEDESC
Language=English
Information about the image file.%0
.
Language=Japanese
イメージファイルに関する情報。%0
.


MessageId=
SymbolicName=MSG_HELP_TARGETFILE
Language=English
Save target file name.%0
.
Language=Japanese
保存先のファイル名。%0
.


MessageId=
SymbolicName=MSG_HELP_DISKTYPE
Language=English
Virtual disk type.%0
.
Language=Japanese
仮想ディスク種別。%0
.


MessageId=
SymbolicName=MSG_HELP_MEDIATYPE
Language=English
Virtual floppy media type.%0
.
Language=Japanese
仮想フロッピメディア種別。%0
.


MessageId=
SymbolicName=MSG_HELP_FORMAT
Language=English
Click to format the
current image with FAT.%0
.
Language=Japanese
現在のイメージを FAT
でフォーマットします。%0
.



MessageId=
SymbolicName=MSG_HELP_CONTROL
Language=English
Start the VFD Control Panel.%0
.
Language=Japanese
VFD コントロールパネルを起動します。%0
.


MessageId=
SymbolicName=MSG_HELP_PROTECT_NOW
Language=English
Enable/disable the media write protection.
The change takes effect immediately.%0
.
Language=Japanese
メディアの書き込み保護を切り替えます。
変更は即座に適用されます。%0
.


MessageId=
SymbolicName=MSG_HELP_PROTECT_OPEN
Language=English
Open the image as a
write protected media.%0
.
Language=Japanese
イメージを書き込み保護
メディアとして開きます。%0
.


MessageId=
SymbolicName=MSG_HELP_BROWSE
Language=English
Browse for folders to
find the target file.%0
.
Language=Japanese
フォルダを参照して目的の
ファイルを検索します。%0
.


MessageId=
SymbolicName=MSG_HELP_OVERWRITE
Language=English
Overwrite the existing file
to save the current image.%0
.
Language=Japanese
既存ファイルを上書きして
現在のイメージを保存します。%0
.


MessageId=
SymbolicName=MSG_HELP_TRUNCATE
Language=English
Truncate the target file after
saving the current image.%0
.
Language=Japanese
現在のイメージを保存したのち、保存先
ファイルのサイズを切り詰めます。%0
.


;
;//
;// Hint text
;//
;
MessageId=
SymbolicName=MSG_CURRENT_FILE
Language=English
Current image file.%0
.
Language=Japanese
現在使用中のイメージファイルです。%0
.

MessageId=
SymbolicName=MSG_FILE_TOO_SMALL
Language=English
The file is too small for the selected media type.%0
.
Language=Japanese
メディアサイズがファイルサイズを超えています。%0
.

MessageId=
SymbolicName=MSG_SIZE_MISMATCH
Language=English
The file size does not match the selected media size.%0
.
Language=Japanese
ファイルサイズが選択したメディアサイズと一致していません。%0
.

MessageId=
SymbolicName=MSG_FILE_ACCESS_ERROR
Language=English
Cannot access the file.%0
.
Language=Japanese
ファイルにアクセスできません。%0
.

MessageId=
SymbolicName=MSG_TARGET_IS_ZIP
Language=English
Cannot overwrite a ZIP compressed file.%0
.
Language=Japanese
ZIP 圧縮ファイルに上書き保存はできません。%0
.

;
;//
;// Other text
;//
;
MessageId=
SymbolicName=MSG_OPEN_FILTER
Language=English
Common image files (bin,dat,fdd,flp,ima,img,vfd)|*.bin;*.dat;*.fdd;*.flp;*.ima;*.img;*.vfd|ZIP Compressed Image (imz,zip)|*.imz;*.zip|All files (*.*)|*.*|%0
.
Language=Japanese
一般的なイメージファイル (bin,dat,fdd,flp,ima,img,vfd)|*.bin;*.dat;*.fdd;*.flp;*.ima;*.img;*.vfd|ZIP圧縮イメージ (imz,zip)|*.imz;*.zip|すべてのファイル (*.*)|*.*|%0
.

MessageId=
SymbolicName=MSG_FORMAT_WARNING
Language=English
Warning: Formatting will erase all data on this disk.
Click [OK] to format the disk, [Cancel] to quit.%0
.
Language=Japanese
警告: フォーマットするとこのディスクのすべてのデータが消去されます。
ディスクをフォーマットするには［OK］を、取り消す場合は［キャンセル］をクリックしてください。%0
.


MessageId=
SymbolicName=MSG_MEDIA_MODIFIED
Language=English
Data on the RAM disk is modified.
Save to a file before closing ?%0
.
Language=Japanese
RAM ディスク内容が更新されています。
閉じる前にファイルに保存しますか？%0
.



MessageId=
SymbolicName=MSG_UNMOUNT_CONFIRM
Language=English
Failed to lock the volume.
Make sure that any files are not in use.
Continuing forces all files to be closed.%0
.
Language=Japanese
ボリュームをロックできませんでした。
使用中のファイルがないかどうか確認してください。
続行すると使用中のファイルは強制的に閉じられます。%0
.


MessageId=
SymbolicName=MSG_UNMOUNT_FAILED
Language=English
Failed to unmount the volume.
Make sure that any files are not in use.%0
.
Language=Japanese
ボリュームをアンマウントできませんでした。
使用中のファイルがないかどうか確認してください。%0
.
;
;#endif // _VFDMSG_H_
