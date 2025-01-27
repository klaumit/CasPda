#########################################################################
#	MAKE file for release application (MOD.2)
#########################################################################
# USER OPTIONS
SETHEDUINF =  -vp$(VERSION)
#########################################################################

ALLOBJ = $(USERALLOBJ)

all:	SHCENV \
	$(ALLOBJ) \
	"$(OUTDIR)\$(TARGET).pva"

#------------------------------------------------------------------------
!MESSAGE
!MESSAGE Executing OptLinker phase
!MESSAGE

"$(OUTDIR)\$(TARGET).rld" : $(ALLOBJ) $(LNKINF0)
	$(LNK) -subcommand=<<
form sectrel
noprelink
nomessage 
list "$(OUTDIR)\$(TARGET).map"
show symbol
nologo
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
output "$(OUTDIR)\$(TARGET).rld"
exit
<<

#------------------------------------------------------------------------
!MESSAGE
!MESSAGE Create PV Application Binary Object phase
!MESSAGE

"$(TARGET).pva" : $(ALLOBJ) $(LNKINF0)
	$(SETHED) "$(OUTDIR)\$(TARGET).rld" "$(BINOUTDIR)\$(TARGET).pva" $(SETHEDINF) $(SETHEDUINF)
	$(PUTNAME) $(PUTNAMEINF) "$(BINOUTDIR)\$(TARGET).pva" $(TITLE)
	copy make\fin "$(BINOUTDIR)\fin"
