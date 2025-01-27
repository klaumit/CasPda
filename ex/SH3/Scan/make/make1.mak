#########################################################################
#	MAKE file for release application (MOD.1)
#########################################################################

#------------------------------------------------------------------------
# Tools									|
# SH C/C++ Compiler phase
PVSDK_BASE=..

CC=$(TCDIR)\bin\shc.exe

# SH Assembler
ASM=$(TCDIR)\bin\asmsh.exe

# OptLinker
LNK=$(TCDIR)\bin\optlnk.exe

# Set Header
SETHED=$(PVSDK_BASE)\TOOLS\sethead.exe

# Put Name
PUTNAME=$(PVSDK_BASE)\TOOLS\putname.exe

# End of Tools 								|
#------------------------------------------------------------------------
#------------------------------------------------------------------------
# PV system config							|
STARTUP = $(PVSDK_BASE)\system\obj\startapl.obj
SETUP = $(PVSDK_BASE)\system\obj\setup.obj
SECT = $(PVSDK_BASE)\system\obj\section.obj
SYSRAM = $(PVSDK_BASE)\system\obj\rsysram.obj
BOOTINF = $(PVSDK_BASE)\system\obj\bootinf.obj

LDIR= $(PVSDK_BASE)\lib\LibH
SYSSRCDIR = $(PVSDK_BASE)\system
LCOM_H="$(LDIR)\define.h" "$(LDIR)\LIBC.H" "$(LDIR)\L_LIBC.H" "$(LDIR)\L_define.h"
LLIB   ="$(PVSDK_BASE)\lib\libc.lib"
ADDLIB ="$(PVSDK_BASE)\lib\addlibc.lib"

HIDIR = $(PVSDK_BASE)\lib\hilib
HILIB = "$(HIDIR)\HiLIB.LIB"
SHCLIB ="$(TCDIR)\shclib.lib"

#Common setting for Application
SOURCES = sources.def
SUBCOM = $(PVSDK_BASE)\tools\Makefile.sub
SRCDIR = src
OUTDIR = release
BINOUTDIR = user_bin
INC="def","$(LDIR)","$(HIDIR)"
LNKINF0=$(LCOM_H) $(LLIB) $(ADDLIB) $(SHCLIB) $(STARTUP) $(SOURCES)
CCINF0=-include=$(INC) -subcommand=$(SUBCOM)
SETHEDINF=-vl0100 -m1 -pA -o -bIicon\icon.bmp -bLicon\licon.bmp

PUTNAMEINF=-p0 -wp

# End of system config							|
#------------------------------------------------------------------------
# Description blocks
SHCENV : 
	set PATH=$(TCDIR)\bin
	set SHC_INC=$(TCDIR)\include
	set SHC_LIB=$(TCDIR)\bin
	set SHC_TMP=$(TCDIR)
