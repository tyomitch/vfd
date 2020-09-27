# Virtual Floppy Drive 2.1
This is a virtual floppy drive for Windows, developed by Ken Kato since 2003, and abandoned by him in 2008.

### Now, compatible with 64-bit Windows, incl. Windows 10!

You can mount a floppy image file as a virtual floppy drive and directly access the contents -- view, edit, rename, delete or create files on a virtual floppy, format a virtual floppy, launch a program on a virtual floppy... almost anything you can do with a real floppy.

## FILES and DIRECTORIES

    .\cmd\          VFD.EXE program source and VC++ project file
    .\gui\          VFDWIN.EXE program source and VC++ project file
    .\inc\          Files shared between user mode programs and the driver
    .\lib\          VFD.DLL library source and VC++ project file
    .\sys\          VFD.SYS driver source and DDK makefile

    .\vfd.vcxproj   wrapper VC++ project to build all vfd programms at once
    .\vfd.sln       VC++ workspace file

## BUILD

### User mode programs:

Use the `.\vfd.sln` workspace file

#### Requirements:
   -    Microsoft Visual C++
        - Compatible with Visual C++ 2019
        - If you can convert the project files, you should be able to use
          other compilers

   -    Preferably the latest Windows Platform SDK.

### Kernel mode driver:

Run the BUILD DDK utility from the `.\sys\` subdirectory

#### Requirements:
   -    Microsoft Windows DDK
        - Windows 2000 DDK or Windows XP DDK preferred,
          although Windows NT DDK should also be OK.

## FAQ & known issues (including unconfirmed)

* **Super FAQ**: NTFS compressed/encrypted files cannot be mounted directly. It is intentional to avoid the Windows cache manager dead lock.

* **Super FAQ**: Current VFD can not create image from or save to actual floppy disk. Use programs like WinImage or RawWriteWin for that purpose.

* Windows XP Explorer shows virtual drives as removable drives, not as floppy drives. Also it shows a 5.25" floppy icon if a virtual drive is A: or B:, and a removable drive icon otherwise. I'd say it's a bug of the Explorer. Other properly designed programs won't have any such problem.

* Windows XP Explorer sometimes doesn't respond properly when you add / change drive letters of virtual drives. I think it's also an Explorer bug, because the same thing happens when I change drive letters of a hard drive, a CD drive, etc. Restart the Explorer or, if that fails, log off and log on again and the the virtual drives will be recognized correctly.

* Windows Explorer's check disk does not work with VFD drives.
Use command line CHKDSK.EXE instead.

* Changing a virtual media between 3.5" and 5.25" does not update the drive type display of the Explorer. It's just cosmetic. Any programs which have to distinguish them should recognize the drive type correctly.

* Some programs (especially old ones) assume floppy drives to be either A: or B:. If certain programs don't recognize a VFD drive, try changing the drive letter to A: or B:.

* Windows 2000/XP sometimes assign conflicting drive letters, especially with removable devices such as USB drives and network drives. If a VFD drive suddenly becomes unaccessible, try changing the drive letter.

* Conflict with swapfs (http://www.acc.umu.se/~bosse/) is reported by Suzu. (unconfirmed)

* Some users have reported gradual system slow down and eventual lock up while copying a large amount of data to/from virtual drives. (unconfirmed)
