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

T_SCR_POS	ListScr;					/* Scrollbar Info  */
int			ListCount;					/* Number of Files */
byte		ListTop;					/* List Top */
int			CsLine;						/* List Cursor Pos */
int			CsBak;						/* List Cursor Pos (bakup) */
bool		CsFlg;						/* Cursor Flag */
ubf_t		Lbuf[_LIST_MAX];

void FileListPhase(void);
bool ListScBar(TCHSTS *tsts);
int ListCursorUp(void);
int ListCursorDown(void);
void ListInit(void);
void ListDispBk(void);
int GetListCount(void);
void SetFileList(void);
void ListCursorOn(void);
void ListCursorOff(void);
bool TchListArea(TCHSTS *tsts);
int ListCursorPos(TCHSTS *tsts);
void ListArrowMask(void);
void PdnFuncDelete(void);


/******************************************************************************
*  [Title]			main
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void main(void)
{
	ListTop = 0;
	ListCount = GetListCount();			/* Number of Files */

	CsLine = -1;
	CsBak = 0;
	CsFlg = FALSE;

	while(1){
		FileListPhase();				/* File List */
		FileEditPhase();				/* Text Edit */
	}
}


/******************************************************************************
*  [Title]			File Select Phase
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void FileListPhase(void)
{
	TCHSTS		tsts;
	bool		edtflg = FALSE;
	bool		rdsp = TRUE;

	if( CsLine<0 )
		CsLine = CsBak;
	ListInit();
	ListDispBk();

	while( edtflg==FALSE ){

		if( rdsp==TRUE ){
			ListScr.vol		= ListCount;	/* scroll bar vol set */
			ListScr.pos		= ListTop;		/* scroll bar top set */
			SetFileList();
			rdsp = FALSE;
		}

		LibScrollPrint(ListScr);			/* Scroll Bar Disp */
		ListArrowMask();					/* Scrollbar Arrow Mask */

		ListCursorOn();						/* cursor reverse */
		LibTchWait(&tsts);					/* Touch Wait */
		ListCursorOff();					/* cursor reverse */

		switch(tsts.obj){

			case OBJ_LPSW_RIGHT:	/* RIGHT KEY */
			case OBJ_LPSW_LEFT:		/* LEFT KEY */
				LibRepOff();				/* repeat off */
				break;

			case OBJ_LPSW_UP:		/* UP KEY */
				rdsp = ListCursorUp();
				break;

			case OBJ_LPSW_DOWN:		/* DOWN KEY */
				rdsp = ListCursorDown();
				break;

			case OBJ_LPSW_PUSH:		/* Push KEY */
				if( ListCount>0 ){
					CsBak = CsLine;
					edtflg = TRUE;			/* goto Edit */
				}
				break;

			case OBJ_AR_LIST:		/* LIST Area */
				edtflg = TchListArea(&tsts);
				break;

			case OBJ_SCR_BAR:		/* Scroll Bar */
				rdsp = ListScBar(&tsts);
				break;

			case OBJ_IC_NEW:		/* New Icon */
				if (LibIconClick(&TiconNew, &tsts) == TRUE){
					CsBak = CsLine;
					CsLine = -1;			/* New Name */
					edtflg = TRUE;			/* Phase Change */
				}
				break;

			case OBJ_HIC_MBAR:		/* PullDown Menu */
				ListCursorOn();				/* cursor reverse */
				ListPdwnSet();				/* menu set */
				rdsp = PulDwnFnc(NULL);
				ListCursorOff();			/* cursor reverse */
				break;
		}
	}
}


/******************************************************************************
*  [Title]			Scrollbar Function
*  [Arguments]
*  [ReturnVAL]		TRUE	: Scroll
*					FALSE	: non Scroll
*******************************************************************************/
bool ListScBar(TCHSTS *tsts)
{
	int		ans;
	bool	jdg = FALSE;
	int		tgt = ListTop+CsLine;

	ans = LibScrPosCheck(*tsts,ListScr);
	if( ans==0 ){						/* up scroll key */
		if( CsLine==0 && ListScr.pos==0 )
			return(jdg);				/* cannot move upper */

	}else if(ans==1){					/* down scroll key */
		if( tgt >= ListCount-1 )
			return(jdg);				/* cannot move lower */
	}

	ans = LibScrollClick(tsts,&ListScr);
	switch(ans){
		case 0:					/* up scroll key */
			if( tsts->act==ACT_BREAK_IN ){
				jdg = ListCursorUp();
			}
			break;

		case 1:					/* down scroll key */
			if( tsts->act==ACT_BREAK_IN ){
				jdg = ListCursorDown();
			}
			break;

		case 2:					/* scroll bar touch & drug */
			ListTop = ListScr.pos;
			CsLine = tgt - ListTop;
			if( CsLine<0 ){
				CsLine = 0;
			}else if( CsLine > _LIST_MAX-1 ){
				CsLine = _LIST_MAX-1;
			}
			jdg = TRUE;
			break;
	}
	return(jdg);
}


/******************************************************************************
*  [Title]			UP key Function
*  [Arguments]
*  [ReturnVAL]		TRUE	: Scroll
*					FALSE	: non Scroll
*******************************************************************************/
int ListCursorUp(void)
{
	if( ListTop+CsLine > 0 ){
		if( CsLine>0 ){
			CsLine --;
		}else{
			ListTop --;
			return(TRUE);
		}
	}
	return(FALSE);
}


/******************************************************************************
*  [Title]			DOWN key Function
*  [Arguments]
*  [ReturnVAL]		TRUE	: Scroll
*					FALSE	: non Scroll
*******************************************************************************/
int ListCursorDown(void)
{
	if( ListTop+CsLine < ListCount-1 ){
		if( CsLine < _LIST_MAX-1 ){
			CsLine++;
		}else{
			ListTop ++;
			return(TRUE);
		}
	}
	return(FALSE);
}


/******************************************************************************
*  [Title]			Text Edit Phase
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void ListInit(void)
{
	/*** Scroll Bar Setting ***/
	ListScr.x		= 149;
	ListScr.y		= 22;
	ListScr.size	= 135;
	ListScr.dsp		= _LIST_MAX;
	ListScr.vol		= ListCount;
	ListScr.pos		= ListTop;

	/*** Touch Area Setting ***/
	LibTchStackClr();
	LibTchStackPush(NULL);
	LibTchStackPush(TchHardIcon);		/* Hard icon */
	LibTchStackPush(TchActionKey);		/* Action Key */
	LibTchStackPush(TchModeIcon);		/* [Tool] icon */
	LibTchStackPush(TchNewIcon);		/* [New] icon */
	LibTchStackPush(TchList);			/* List Area */
	LibTchStackPush(TchScrBar);			/* Scroll Bar */

	LibTchInit();
}

/******************************************************************************
*  [Title]			Text Edit Phase
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void ListDispBk(void)
{
	LibClrDisp();

	LibPutGraph(0,0,TEicn);				/* mode icon  */
	LibPutProStr(IB_PFONT3, 14, 1, (byte *)"Text Edit", 130);	/* Title */

	LibPutFarData(98, 0,80);			/* [New] icon */
	LibPutMessageCenter(14, 98,126,2,IB_PFONT1);

	LibModeIconDsp();					/* [Tools] icon */

	/*** Line ***/
	LibGdsLine(  1, 19,158, 19);		/* Top */
	LibGdsLine(  1,159,158,159);		/* Botom */
	LibGdsLine(  0, 20,  0,158);		/* Left */
	LibGdsLine(147, 20,147,158);		/* Right1 */
	LibGdsLine(159, 20,159,158);		/* Right2 */
}


/******************************************************************************
*  [Title]			count the number of files
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
int GetListCount(void)
{
	int			sh, ct;
	ubf_t		ubuf;

	ct = 0;
	if( (sh=LibUbfFindFirst((byte *)"*.*",&ubuf))>=0 ){
		for(;;){
			ct ++;
			if( LibUbfFindNext(sh,&ubuf)<0 )
				break;
		}
		LibUbfFindClose(sh);
	}

	return(ct);
}


/******************************************************************************
*  [Title]			Set display faile names
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void SetFileList(void)
{
	int		ln, ct, sh;

	LibGdsClr(1,20,146,158);				/* Disp Box Clear */

	ln = 0;
	if( (sh=LibUbfFindFirst((byte *)"*.*",&Lbuf[ln]))>=0 ){	/* All File Search */
		for( ct=0;; ct++ ){
			if( (ListTop+ln)==ct ){
				LibStringDsp(&Lbuf[ln].name[0], 3, 21+ln*10, 144, IB_PFONT1 );
				ln ++;
			}
			if( ct>=ListCount )
				break;
			if( LibUbfFindNext(sh,&Lbuf[ln])<0 )
				break;
		}
		LibUbfFindClose(sh);
	}

	/*** Mesh Line Redisp ***/
	for( ln=0; ln<13; ln++ )
		LibGdsLineMesh(2,ln*10+29,144,ln*10+29);
}


/******************************************************************************
*  [Title]			Cursor ON
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void ListCursorOn(void)
{
	if( ListCount>0 ){
		LibGdsReverse(2,10*CsLine+20,145,10*CsLine+28);
		CsFlg = TRUE;
	}else{
		CsFlg = FALSE;
	}

	LibPutDisp();
}

/******************************************************************************
*  [Title]			Cursor Off
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void ListCursorOff(void)
{
	if( CsFlg==TRUE )
		LibGdsReverse(2,10*CsLine+20,145,10*CsLine+28);
}


/******************************************************************************
*  [Title]			
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
bool TchListArea(TCHSTS *tsts)
{
	int		cur_ptr;
	bool	dbt = FALSE;

	if(	/* Touch Area Check */
		!(	tsts->x >= TchList[0].x1 && tsts->y >= TchList[0].y1 &&
			tsts->x <= TchList[0].x2 && tsts->y <= TchList[0].y2
		)
	){
		return(FALSE);
	}

	cur_ptr = ListCursorPos(tsts);
	if( ListTop+cur_ptr>=ListCount )
		return(FALSE);

	switch( tsts->act ){
		case ACT_MAKE:
			CsBak = CsLine;
			if(cur_ptr != CsLine){
				CsLine = cur_ptr;
				ListArrowMask();		/* Scrollbar Arrow Mask */
			}
			break;

		case ACT_MOVE:
			if(cur_ptr != CsLine){
				CsLine = cur_ptr;
				ListArrowMask();		/* Scrollbar Arrow Mask */
			}
			break;

		case ACT_BREAK:
			CsLine = cur_ptr;
			if( CsLine==CsBak ){
				dbt = TRUE;
			}
			break;

		default:
			break;
	}
	return(dbt);
}


/******************************************************************************
*  [Title]			calculate cursor display pos
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
int ListCursorPos(TCHSTS *tsts)
{
	int		i,y;

	y = TchList[0].y1;

	for(i=0;i<_LIST_MAX;i++){
		if(tsts->y>=y+i*10 && tsts->y<=y+(i+1)*10-1)
			return(i);
	}
	return(0);
}


/******************************************************************************
*  [Title]			Scrollbar Arrow Mask
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void ListArrowMask(void)
{
	LibScrollArrowPrint(ListScr,SCR_NO_MASK);

	/* first page and current cursor position is at top row */
	if( CsLine==0 && ListScr.pos == 0){
		LibScrollArrowPrint(ListScr,SCR_UP_MASK);
	}

	/* check datas under current cursor position */
	if( CsLine < _LIST_MAX-1){
		if( ListTop+CsLine >= ListCount-1 ){
			LibScrollArrowPrint(ListScr,SCR_DWN_MASK);
		}
	}
	/* check last page and  current cursor position is at bottom row  */
	else if( ListScr.pos == ListScr.vol-ListScr.dsp ){
		LibScrollArrowPrint(ListScr,SCR_DWN_MASK);
	}
}


/******************************************************************************
*  [Title]			function  - DELETE -
*  [Arguments]
*  [ReturnVAL]
*******************************************************************************/
void PdnFuncDelete(void)
{
	LibUbfRemove(&Lbuf[CsLine].name[0]);	/* file delete */
	ListCount --;

	/*** list cursor pos modify ***/
	if( ListTop+CsLine > ListCount-1 ){		/* if bottom file deleted... */
		if( ListTop > 0 ){
			ListTop --;						/* scroll down */
		}else{
			if( CsLine > 0 )
				CsLine --;					/* cursor up */
		}
	}else{
		if( ListTop+_LIST_MAX > ListCount-1 ){
			if( ListTop > 0 ){
				ListTop --;
				CsLine ++;
			}
		}
	}
}
