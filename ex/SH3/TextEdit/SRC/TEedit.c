/******************************************************************************
*	
*	[Title]		Binary Editor
*
*	[Model] 	PocketViewer
*
*	[Version]	Ver1.00
*
*	Copyright (C) 2002 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/

#include	"define.h"
#include	"libc.h"
#include	"TxtEdit.h"

byte		Txebf[_MAXMJ+1];		/* Text Buffer */
TXTP		Txpr;					/* Text Parameter */
T_SCR_POS	Txscb;					/* Scrollbar info */
TCHTBL		TxeTch[3];				/* Text Input Touch Table */
word		Txegd[] = { 0xFFFF };	/* Txet Input Guidance */

extern ubf_t	Lbuf[];
extern int		ListCount;
extern byte		ListTop;
extern int		CsLine;
extern word		MPdEdt[];
extern word		MPdSys[];
extern word		MPdOpt[];

void FileEditPhase(void);
void TargetFileLoad();
void FileEditInit();
void EditTchAreaSet();
void EditDispBk();
bool SaveFileWin();
void FileSaveDispBk();
bool TextFileSave(byte *fnm);
void ListCursorMove(byte *fnm);
int CursorFileSearch(byte *fnm);
void EditPdwnSet(TXTP *tp);
void ListPdwnSet(void);
bool PulDwnFnc(TXTP *tp);


/******************************************************************************
*  [Title]			Text Edit Phase
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void FileEditPhase(void)
{
	TCHSTS		tsts;
	byte		kycd;
	bool		loop = TRUE;
	bool		retval = FALSE;

	TargetFileLoad();					/* File Data Read */

	FileEditInit();						/* Text Area Setting */
	LibTxtInit(&Txpr);

	EditTchAreaSet();					/* Touch Area Setting */
	EditDispBk();						/* Back Ground Disp */
	LibDispKey();

	while( loop==TRUE ){

		if(LibTxtDsp(&Txpr)==TRUE)
			LibPutDisp();

		if( (kycd=LibGetKeyM(&tsts))==KEY_NONE ){

			switch(tsts.obj){

				case OBJ_IC_SAVE:		/* [Save] icon */
					if( LibIconClick(&TiconSave,&tsts)==TRUE ){
						if( (retval=SaveFileWin())==TRUE ){
							loop = FALSE;
						}
					}
					break;
	
				case OBJ_HIC_ESC:		/* [ESC] Hard icon **/
					loop = FALSE;
					break;

				case OBJ_HIC_MBAR:		/* PullDown Menu */
					EditPdwnSet(&Txpr);		/* menu set */
					PulDwnFnc(&Txpr);
					break;
			}
		}

		LibTxtInp(kycd,&tsts,&Txpr);
	}
	LibTchStackClr();
}


/******************************************************************************
*  [Title]			Read Text File
*  [Arguments]
*  [ReturnVAL]		TRUE	: Load OK
*					FALSE	: NG
*******************************************************************************/
void TargetFileLoad(void)
{
	int		rdsz, ret;
	int		fh = -1;
	bool	jdg = FALSE;

	if( CsLine>=0 ){			/* if New File... */

		if( Lbuf[CsLine].size<=0 )
			goto FL_END;

		if( Lbuf[CsLine].size>_MAXMJ ){
			LibWinIcnMsg(ICON_BIKKURI,341,0);	/* Under Window disp */
			/* Overwrite Mes. */
			LibGdsClr(50,70,130,90);
			LibStringDsp((byte *)"File size is too big.", 49, 65, 150, IB_PFONT1 );
			LibStringDsp((byte *)"Cannot load to", 49, 75, 150, IB_PFONT1 );
			LibStringDsp((byte *)"  the last !!", 49, 85, 150, IB_PFONT1 );

			LibPutDisp();
			LibWait(IB_1SWAIT);			/* 1 sec wait */
			LibCloseWindow();			/* WIN close */
			LibPutDisp();
		}

		if( (fh=LibUbfOpen(&Lbuf[CsLine].name[0],_UBFOPEN_READWRITE))>=0 ){	/* FILE OPEN */

			for( rdsz=0; rdsz<_MAXMJ; ){
				if( (ret=LibUbfRead(fh,&Txebf[rdsz],_SCTSZ)) <= 0 )		/* FILE READ */
					break;
				rdsz += ret;
			}

			LibUbfClose(fh);		/* FILE CLOSE */
			Txebf[rdsz] = 0;		/* limiter add. */
			jdg = TRUE;
		}
	}

FL_END:
	if( jdg==FALSE ){		
		Txebf[0] = 0;		/* limiter add. */
//		CsLine = -1;
	}
	return;
}


/******************************************************************************
*  [Title]			Text Area Setting
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void FileEditInit()
{
	Txpr.st_x	= _ST_X;
	Txpr.st_y	= _ST_Y;
	Txpr.ed_x	= _ED_X;
	Txpr.it_y	= _IT_Y;
	Txpr.MAXGYO	= _MAXG;
	Txpr.font	= IB_PFONT1;

	Txpr.csen	= TRUE;
	Txpr.rtnen	= TRUE;
	Txpr.maxmj	= _MAXMJ;		/* max char number */
	Txpr.txbf	= Txebf;		/* Text Buffer */
	Txpr.gdcmt	= Txegd;
	Txpr.txtobj	= OBJ_TXTTCH;
	Txpr.sbrobj	= OBJ_SCR_BAR;
	Txpr.tchtb	= TxeTch;
	Txpr.s_pos	= &Txscb;
}


/******************************************************************************
*  [Title]			Touch Area Setting
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void EditTchAreaSet(void)
{
	LibTchStackClr();

	LibTchStackPush( NULL );
	LibTxtTchSet(&Txpr);				/* Text Area */
	LibTchStackPush(TchHardIcon);		/* Hard Icon */
	LibTchStackPush(TchSaveIcon);		/* [SAVE] Icon */
}


/******************************************************************************
*  [Title]			Background Display
*  [Arguments]		None
*  [ReturnVAL]		None
*******************************************************************************/
void EditDispBk(void)
{
	LibClrDisp();

	LibPutGraph(0,0,TEicn);			/* mode icon  */

	if( CsLine<0 )
		LibStringDsp((byte *)"-- New File --", 16, 2, 128, IB_PFONT1 );
	else
		LibStringDsp(&Lbuf[CsLine].name[0], 16, 2, 128, IB_PFONT1 );

	LibPutFarData(130,0,44);		/* Save Button   */

	LibPutMessageCenter( 477, 130,157,2,IB_PFONT1);	/* [Save] */

	LibGdsBox( _ST_X-2, _ST_Y-2, 159, _ST_Y+(_IT_Y*_MAXG) );
	LibGdsLine( _ED_X+1, _ST_Y-2, _ED_X+1, _ST_Y+(_IT_Y*_MAXG) );
}


/******************************************************************************
*  [Title]			file name input window
*  [Arguments]
*  [ReturnVAL]		TRUE  : saved
*					FALSE : not save
*******************************************************************************/
bool SaveFileWin()
{
	TXTP		fstp;
	T_SCR_POS	fsscr;
	TCHSTS		tsts;
	byte		kycd;
	TCHTBL		fstch[3];
	byte		fsbuf[MAX_FILENAMELEN+1];
	int			i;
	bool		loop = TRUE;
	bool		jdg = FALSE;

	LibOpenWindow(0,0,160,160);			/* Full window open */

 	LibTchStackPush( NULL );
	LibTchStackPush(TchHardIcon);
	LibTchStackPush(TchSaveIcon);

	fstp.txbf	= fsbuf;
	fstp.st_x	= _FS_ST_X;
	fstp.ed_x	= _FS_ED_X;
	fstp.st_y	= _FS_ST_Y;
	fstp.it_y	= _FS_IT_Y;
	fstp.MAXGYO	= _FS_MAXG;
	fstp.font	= IB_PFONT1;
	fstp.csen	= TRUE;
	fstp.rtnen	= 0x02;
	fstp.maxmj	= _FS_MAXMJ;			/* file name max length */
	fstp.txtobj	= OBJ_TXTTCH;
	fstp.sbrobj	= OBJ_SCR_BAR;
	fstp.tchtb	= fstch;
	fstp.gdcmt	= Txegd;
	fstp.s_pos	= &fsscr;

	/** Text Buffer Init. **/
	if( 0<=CsLine && CsLine<_LIST_MAX ){
		for( i=0; i<_FS_MAXMJ; i++ )
			fsbuf[i] = Lbuf[CsLine].name[i];
		fsbuf[_FS_MAXMJ] = 0;
	}else{
		fsbuf[0] = 0;
	}

	LibTxtInit(&fstp);
	LibTxtTchSet(&fstp);

	FileSaveDispBk();					/* background disp */
	LibDispKey();

	while(loop==TRUE){

		LibTxtDsp(&fstp);					/* text disp */
		LibPutDisp();

		if( (kycd=LibGetKeyM(&tsts))==KEY_NONE ){	/* Keybord disp */
			switch(tsts.obj){

				case OBJ_IC_SAVE:			/* [SAVE] Icon */
					if( LibIconClick(&TiconSave,&tsts)==TRUE ){
						if( TextFileSave(fsbuf)==TRUE ){
							ListCursorMove(fsbuf);	/* ListPhase cursor move */
							loop = FALSE;
							jdg = TRUE;
						}
					}
					break;

				case OBJ_HIC_ESC:			/* [ESC] Hard icon **/
					loop = FALSE;
					break;

				case OBJ_HIC_MBAR:			/* PullDown Menu */
					EditPdwnSet(&fstp);			/* menu set */
					PulDwnFnc(&fstp);
					break;
			}
		}
		LibTxtInp(kycd,&tsts,&fstp);		/* text input */
	}

	LibTchRelease();				/* touch table POP */
	LibCloseWindow();
	LibPutDisp();

	return(jdg);
}


/******************************************************************************
*  [Title]			
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void FileSaveDispBk()
{
	LibClrDisp();

	LibPutGraph(0,0,TEicn);			/* mode icon  */

	LibPutFarData(130,0,44);		/* Save Button   */
	LibPutMessageCenter( 477, 130,157,2,IB_PFONT1);	/* [Save] */

	LibGdsReverse( 0, 14, 159, 85 );
	LibGdsMesh( 0, 14, 159, 85 );
	LibGdsBox( 0, 14, 159, 85 );

	LibGdsClr( _FS_ST_X-3, 35, _FS_ED_X+2, _FS_ST_Y+_FS_IT_Y+5 );
	LibPutProStr(IB_PFONT1, 6, 40, (byte *)" -- Please Input File Name -- ", 150);

	LibGdsClr( _FS_ST_X-2, _FS_ST_Y-2, _FS_ED_X+1, _FS_ST_Y+_FS_IT_Y );
	LibGdsBox( _FS_ST_X-2, _FS_ST_Y-2, _FS_ED_X+1, _FS_ST_Y+_FS_IT_Y );
}


/******************************************************************************
*  [Title]			
*  [Arguments]		byte *fnm	: save file name
*  [ReturnVAL]		TRUE	: success
*					FALSE	: save NG
*******************************************************************************/
bool TextFileSave(byte *fnm)
{
	int		hdl, pt, ret;
	bool	bkflg = FALSE;
	bool	jdg = FALSE;
	ubf_t	ubuf;
	byte	bk[MAX_FILENAMELEN+1];


	if( (hdl=LibUbfFindFirst(fnm,&ubuf))>=0 ){
		bkflg = TRUE;
		LibUbfFindClose(hdl);

		if( LibWinIcnMsg(ICON_BIKKURI,453,6)!=TRUE )	/* [Overwrite?] */
			return(FALSE);
	}

	LibWinIcnMsg(ICON_COFFEE,381, 0);	/* ¢Please_Wait...£ window disp */
	LibCloseWindow();

	/* if alredy same name file exist... */
	if( bkflg==TRUE ){
		/* make bak_file name */
		for( pt=0; pt<_FS_MAXMJ+1; pt++ ){
			bk[pt] = fnm[pt];
			if( fnm[pt]=='.' || fnm[pt]==0 ){
				bk[pt]   = '.';
				bk[pt+1] = 'b';
				bk[pt+2] = 'a';
				bk[pt+3] = 'k';
				bk[pt+4] = 0;
				break;
			}
		}
		/* if alredy bak_file exist */
		if( (hdl=LibUbfFindFirst(bk,&ubuf))>=0 ){
			LibUbfFindClose(hdl);
			LibUbfRemove(bk);				/* old bak_file delete */
			ListCount --;
		}

		LibUbfRename(fnm,bk);				/* rename to bak_file */
	}

	/*** new file make ***/
	for( pt=0; pt<_MAXMJ; pt++ ){					/* get file size  */
		if( Txebf[pt]==0 )
			break;
	}

	/*** File write ***/
	if( (hdl=LibUbfOpen(fnm,_UBFOPEN_READWRITE)) >= 0 ){

		if( (ret=LibUbfWrite(hdl,Txebf,pt))>=0 ){
			LibWinIcnMsg(ICON_OK,341, 1);			/* ¢DATA_STORED!£ 1 sec disp */

		}else if( ret==_UBFERR_MEMORY ){
			LibWinIcnMsg(ICON_BIKKURI, 324, 2);		/* [MEMORY IS FULL !] disp */
		}

		LibUbfClose(hdl);
		ListCount ++;
		jdg = TRUE;
	}
	return(jdg);
}


/******************************************************************************
*  [Title]			cursor move after save
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void ListCursorMove(byte *fnm)
{
	int		pt;

	if( (pt=CursorFileSearch(fnm))<0 )		/* if not found file... */
		return;

	if( pt<_LIST_MAX ){
		CsLine = pt;
		ListTop = 0;

	}else{
		CsLine = _LIST_MAX - 1;
		ListTop = pt - CsLine;
	}
}


/******************************************************************************
*  [Title]
*  [Arguments]
*  [ReturnVAL]		file number (>=0)
*					( -1	: target file not found )
*******************************************************************************/
int CursorFileSearch(byte *fnm)
{
	int			sh, ct, pt;
	ubf_t		ubuf;

	if( (sh=LibUbfFindFirst((byte *)"*.*",&ubuf))>=0 ){

		for( ct=0;; ct++ ){

			for( pt=0; pt<MAX_FILENAMELEN+1; pt++ ){
				if( fnm[pt]!=ubuf.name[pt] ){	/* name missmatch */
					break;
				}else if( fnm[pt]==0 ){			/* found file */
					LibUbfFindClose(sh);
					return(ct);
				}
			}
			if( LibUbfFindNext(sh,&ubuf)<0 )
				break;
		}
		LibUbfFindClose(sh);
	}

	return(-1);				/* not find */
}


/******************************************************************************
*  [Title]			
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void ListPdwnSet(void)
{
	word	p_set;

	LibPullDownInit(MPdEdt, MPdSys, MPdOpt);	/* PullDown Init */

	/*** [Edit] Menu  mask set ***/
 	p_set =	  PDWN_EDT_CUT
 			| PDWN_EDT_COPY
 			| PDWN_EDT_PASTE;

	if( ListCount==0 )
		p_set |=  PDWN_EDT_DELT;
	LibPullDownAtrSet( PULLDOWN_HTNDSP, PULLDOWN_EDIT, p_set);
}


/******************************************************************************
*  [Title]			
*  [Arguments]		None
*  [ReturnVAL]		None
*******************************************************************************/
void EditPdwnSet(TXTP *tp)
{
	word	p_set;

	LibPullDownInit(MPdEdt, MPdSys, MPdOpt);	/* PullDown Init */

	/*** [Edit] Menu  mask set ***/
	p_set =  PDWN_EDT_DELT;
	if(tp->selrv==FALSE){
	 	p_set |=  PDWN_EDT_CUT				/* [Cut] mask */
 				| PDWN_EDT_COPY;			/* [Copy] mask */
	}
	if(SYS_INP_BUF[0]==0){
 		p_set |=  PDWN_EDT_PASTE;			/* [Paste] mask */
 	}
	LibPullDownAtrSet( PULLDOWN_HTNDSP, PULLDOWN_EDIT, p_set);

	/*** [System] Menu  mask set ***/
	p_set =  PDWN_SYS_DTTM					/* [Set date/time] mask */
			| PDWN_SYS_FORMT				/* [Format] mask */
			| PDWN_SYS_MMANE;				/* [Memory Management] mask */
	LibPullDownAtrSet( PULLDOWN_HTNDSP, PULLDOWN_SYSTEM, p_set);
}


/******************************************************************************
*  [Title]			Pulldown Menu Function
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
bool PulDwnFnc(TXTP *tp)
{
	word	sel;
	bool	jdg = FALSE;

	sel = LibPullDown();

	/*** ¢Edit£ menu ***/
	if(sel & PULLDOWN_EDIT){
		switch(sel){
			case PDWN_EDT_COPY:			/* Copy */
				tp->txtst = TXTCOPY;
				break;
			case PDWN_EDT_CUT:			/* Cut */
				tp->txtst = TXTCUT;
				break;
			case PDWN_EDT_PASTE:		/* Paste */
				tp->txtst = TXTPASTE;
				break;
			case PDWN_EDT_DELT:			/* Delete */
				PdnFuncDelete();
				jdg = TRUE;
				break;
		}

	/*** ¢System£ menu ***/
	}else if(sel & PULLDOWN_SYSTEM){
		switch(sel){
			case PDWN_SYS_DTTM:		/* Set_date/time		*/
				LibFuncDateTime();
				break;
			case PDWN_SYS_SOUND:	/* Sound				*/
				LibFuncSound(0);
				break;
			case PDWN_SYS_FORMT:	/* Format				*/
				LibFuncFormat();
				break;
			case PDWN_SYS_CAPCT:	/* Capacity				*/
				LibFuncCapa();
				break;
			case PDWN_SYS_MMANE:	/* Memory_management	*/
				LibFuncMemoryManagement();
				break;
			case PDWN_SYS_CNTRS:	/* Contrast				*/
				LibFuncContrast();
				break;
			case PDWN_SYS_TPA:		/* Touch_Panel_Alignment*/
				LibFuncDigitizer();
				break;
		}

//	/*** ¢Option£ menu ***/
//	}else if(sel & PULLDOWN_OPTION){
//		jdg = PdwnFncOpt(sel,pot);
	}
	return(jdg);
}
