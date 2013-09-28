# Microsoft Developer Studio Project File - Name="MPlayerGUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MPlayerGUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MPlayerGUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MPlayerGUI.mak" CFG="MPlayerGUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MPlayerGUI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MPlayerGUI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MPlayerGUI - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MPlayerGUI - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MPlayerGUI - Win32 Release"
# Name "MPlayerGUI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AppSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\cgfiltyp.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipPropertyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DragAndDropListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\functions.cpp
# End Source File
# Begin Source File

SOURCE=.\GotoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\INIfile.cpp
# End Source File
# Begin Source File

SOURCE=.\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\LogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Logoff.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\MPlayerGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\MPlayerGUI.rc
# End Source File
# Begin Source File

SOURCE=.\MPlayerGUIDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MPlayerGUIView.cpp
# End Source File
# Begin Source File

SOURCE=.\MyToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenURLDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PathInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerStatusbar.cpp
# End Source File
# Begin Source File

SOURCE=.\PlaylistDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageAdvanced.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageAssociation.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageContent.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageFile.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\PPagePath.cpp
# End Source File
# Begin Source File

SOURCE=.\PPagePlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageSubtitles.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageVideo.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressDlgBar.cpp
# End Source File
# Begin Source File

SOURCE=.\SeekSliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ShutdownDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ssdisabler.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VolumeSliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\XFont.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppSettings.h
# End Source File
# Begin Source File

SOURCE=.\cgfiltyp.h
# End Source File
# Begin Source File

SOURCE=.\ClipPropertyDlg.h
# End Source File
# Begin Source File

SOURCE=.\DragAndDropListBox.h
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.h
# End Source File
# Begin Source File

SOURCE=.\functions.h
# End Source File
# Begin Source File

SOURCE=.\GotoDlg.h
# End Source File
# Begin Source File

SOURCE=.\INIfile.h
# End Source File
# Begin Source File

SOURCE=.\Label.h
# End Source File
# Begin Source File

SOURCE=.\LimitSingleInstance.h
# End Source File
# Begin Source File

SOURCE=.\LogDlg.h
# End Source File
# Begin Source File

SOURCE=.\Logoff.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\memdc.h
# End Source File
# Begin Source File

SOURCE=.\MPlayer.h
# End Source File
# Begin Source File

SOURCE=.\MPlayerGUI.h
# End Source File
# Begin Source File

SOURCE=.\MPlayerGUIDoc.h
# End Source File
# Begin Source File

SOURCE=.\MPlayerGUIView.h
# End Source File
# Begin Source File

SOURCE=.\MyToolBar.h
# End Source File
# Begin Source File

SOURCE=.\OpenURLDlg.h
# End Source File
# Begin Source File

SOURCE=.\PathInfo.h
# End Source File
# Begin Source File

SOURCE=.\PlayerStatusbar.h
# End Source File
# Begin Source File

SOURCE=.\PlaylistDlg.h
# End Source File
# Begin Source File

SOURCE=.\PPageAdvanced.h
# End Source File
# Begin Source File

SOURCE=.\PPageAssociation.h
# End Source File
# Begin Source File

SOURCE=.\PPageCommands.h
# End Source File
# Begin Source File

SOURCE=.\PPageContent.h
# End Source File
# Begin Source File

SOURCE=.\PPageFile.h
# End Source File
# Begin Source File

SOURCE=.\PPageOutput.h
# End Source File
# Begin Source File

SOURCE=.\PPagePath.h
# End Source File
# Begin Source File

SOURCE=.\PPagePlayer.h
# End Source File
# Begin Source File

SOURCE=.\PPageSubtitles.h
# End Source File
# Begin Source File

SOURCE=.\PPageVideo.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDlgBar.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SeekSliderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ShutdownDlg.h
# End Source File
# Begin Source File

SOURCE=.\ssdisabler.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VolumeSliderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\XFont.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Advanced.ico
# End Source File
# Begin Source File

SOURCE=.\res\Alert.ico
# End Source File
# Begin Source File

SOURCE=.\res\Audio_Mono.ico
# End Source File
# Begin Source File

SOURCE=.\res\Audio_No_Audio.ico
# End Source File
# Begin Source File

SOURCE=.\res\Audio_StereoL.ico
# End Source File
# Begin Source File

SOURCE=.\res\Audio_StereoR.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_b.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_m.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\Engine.ico
# End Source File
# Begin Source File

SOURCE=.\res\File_Blank.ico
# End Source File
# Begin Source File

SOURCE=.\res\File_LocalMedia.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon_6.ico
# End Source File
# Begin Source File

SOURCE=.\res\Keyboard.ico
# End Source File
# Begin Source File

SOURCE=.\res\Logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Logo2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Logo3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MediaType.ico
# End Source File
# Begin Source File

SOURCE=.\res\MPlayer.ico
# End Source File
# Begin Source File

SOURCE=.\res\MPlayerGUI.ico
# End Source File
# Begin Source File

SOURCE=.\res\MPlayerGUI.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MPlayerGUIDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\MPlayerLogo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Net_Buffering.ico
# End Source File
# Begin Source File

SOURCE=.\res\Net_InOut.ico
# End Source File
# Begin Source File

SOURCE=.\res\Net_OK.ico
# End Source File
# Begin Source File

SOURCE=.\res\Net_Out.ico
# End Source File
# Begin Source File

SOURCE=.\res\Net_Receive_020.ico
# End Source File
# Begin Source File

SOURCE=.\res\NetRadio.ico
# End Source File
# Begin Source File

SOURCE=.\res\Output.ico
# End Source File
# Begin Source File

SOURCE=.\res\Shuwdown.ico
# End Source File
# Begin Source File

SOURCE=.\res\Subtitle.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Video.ico
# End Source File
# Begin Source File

SOURCE=.\res\videopanel.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
