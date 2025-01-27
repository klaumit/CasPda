#########################################################################
#	MAKE file for debug application  (MOD.2)
#########################################################################
ALLOBJ = $(USERALLOBJ)

#------------------------------------------------------------------------
all:	SHCENV \
	$(ALLOBJ) \
	"$(OUTDIR)\$(TARGET).abs"
#------------------------------------------------------------------------
!MESSAGE
!MESSAGE Executing OptLinker phase
!MESSAGE

"$(OUTDIR)\$(TARGET).abs" : $(ALLOBJ) $(LNKINF0)
	$(LNK) -subcommand=<<
sdebug
noprelink
nomessage 
list "$(OUTDIR)\$(TARGET).map"
show symbol
start R/0803C0000,B_heap/0803E0000,B_SYSRAM/08C000800,C_binaryinfo/0A0080100,C_programinfo/0A0080180,P,C,D,B/0A0081200
nologo
nooptimize
input $(STARTUP)
input $(SETUP)
input $(SECT)
input $(SYSRAM)
input $(BOOTINF)
input $(ALLOBJ)
library $(LLIB)
library $(ADDLIB)
library $(HILIB)
library $(SHCLIB)
output "$(BINOUTDIR)\$(TARGET).abs"
exit
<<
	copy make\fin "$(BINOUTDIR)\findbg"
