#Makefile for PocketViewer Sample Program

include ..\COM_LNK\MakeSDK.1

### -------- Define Make Application -------- ###

#== TargetName ==
TARGET  = Referencer

#== Program Name ==
PROGNAME = "P. Referencer"

#== ProgramVersion(EX. 0100->Ver1.00) ==
VERSION = 0100

#== MenuIcon (Xsize=45dot,Ysize=28dot) ==
MICON = menuicon\icon.bmp

#== ListMenuIcon (Xsize=27dot,Ysize=20dot) ==
LICON = menuicon\Licon.bmp

#== CompileObjectFile ==
APLOBJS =	$(ODIR)\SD_main.obj \
		$(ODIR)\SD_list.obj \
		$(ODIR)\SD_show.obj \
		$(ODIR)\SD_lib.obj \
		$(ODIR)\SD_data.obj \
		$(ODIR)\SD_src.obj \
		$(ODIR)\SD_func.obj \
		$(ODIR)\SD_msg.obj \
		$(ODIR)\SD_scrbar.obj

#== IncludeHeaderFile ==
HEADFILE = 	$(HDIR)\SD_main.h \
		$(HDIR)\SD_scrbar.h \
		$(HDIR)\SD_msg.h

### ----------------------------------------- ###

include ..\COM_LNK\MakeSDK.2

