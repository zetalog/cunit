# Microsoft Developer Studio Project File - Name="cunit_addin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=cunit_addin - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cunit_addin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cunit_addin.mak" CFG="cunit_addin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cunit_addin - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cunit_addin - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cunit_addin - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\bin\release"
# PROP BASE Intermediate_Dir "..\..\obj\release\cunit_addin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin\release"
# PROP Intermediate_Dir "..\..\obj\release\cunit_addin"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FLASHPUT_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /I "..\naming" /I "..\..\wui" /I "..\..\include" /I "..\..\extern\hhws\include" /D "NDEBUG" /D "_USRDLL" /D "FLASHPUT_EXPORTS" /D "_WINDOWS" /D "_MBCS" /D "WIN32" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /map /debug /machine:I386 /libpath:"..\..\bin\release" /libpath:"..\..\extern\hhws\lib"

!ELSEIF  "$(CFG)" == "cunit_addin - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\bin\debug"
# PROP BASE Intermediate_Dir "..\..\obj\debug\cunit_addin"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\bin\debug"
# PROP Intermediate_Dir "..\..\obj\debug\cunit_addin"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FLASHPUT_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\naming" /I "..\..\wui" /I "..\..\include" /I "..\..\extern\hhws\include" /D "_DEBUG" /D "_USRDLL" /D "FLASHPUT_EXPORTS" /D "_WINDOWS" /D "_MBCS" /D "WIN32" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\bin\debug" /libpath:"..\..\extern\hhws\lib"

!ENDIF 

# Begin Target

# Name "cunit_addin - Win32 Release"
# Name "cunit_addin - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\comhpr.cpp
# End Source File
# Begin Source File

SOURCE=.\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\cunit_addin.def
# End Source File
# Begin Source File

SOURCE=.\cunit_addin.odl
# ADD MTL /h "cunit_types.h"
# End Source File
# Begin Source File

SOURCE=.\cunit_addin.rc
# End Source File
# Begin Source File

SOURCE=.\ds_addin.cpp
# End Source File
# Begin Source File

SOURCE=.\events.cpp
# End Source File
# Begin Source File

SOURCE=.\glue.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\comhpr.h
# End Source File
# Begin Source File

SOURCE=.\cunit_addin.h
# End Source File
# Begin Source File

SOURCE=.\cunit_commands.h
# End Source File
# Begin Source File

SOURCE=.\cunit_includes.h
# End Source File
# Begin Source File

SOURCE=.\cunit_resource.h
# End Source File
# Begin Source File

SOURCE=.\cunit_types.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\enable_context.ico
# End Source File
# Begin Source File

SOURCE=.\res\qute_container.bmp
# End Source File
# Begin Source File

SOURCE=.\qute_container.ico
# End Source File
# Begin Source File

SOURCE=.\res\qute_container.ico
# End Source File
# Begin Source File

SOURCE=.\res\qutecont.bmp
# End Source File
# Begin Source File

SOURCE=.\res\share_folder.bmp
# End Source File
# Begin Source File

SOURCE=.\res\share_folder.ico
# End Source File
# Begin Source File

SOURCE=.\share_folder.ico
# End Source File
# Begin Source File

SOURCE=.\res\tape_archive.ico
# End Source File
# Begin Source File

SOURCE=.\res\TBarLrge.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TBarMedm.bmp
# End Source File
# End Group
# End Target
# End Project
