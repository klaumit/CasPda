/******************************************************************************
	[ﾀｲﾄﾙ]
		Referencer

	[機種]
		通信電子手帳(海外)

	[概要]
		Referencer 各種機能処理

	[作成者]
		鈴木茂人

	Copyright (C) 2000 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#include	<stdrom.h>

#include	"define.h"
#include	"libc.h"
#include	"L_define.h"
#include	"L_libc.h"
#include	"SD_main.h"

SHOT_INF		Screen;			/* ｽｸﾘｰﾝｼｮｯﾄ用 */

/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示中､ﾌﾟﾙﾀﾞｳﾝﾒﾆｭｰ表示設定
	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void DicPdwnSet(void)
/*TAIL*/
{
	word	p_set;

	LibPullDownInit(PdEdt,PdSys,PdOpt);		/* PullDown 初期化 */

	/*== [Edit]網掛け指定 ==*/
	p_set = 0;
	if((DicStatus==ST_LTCHIDLE)||(DicStatus==ST_STCHIDLE)){
											/* ﾘｽﾄ表示､又はﾃﾞｰﾀ表示中 */
	 	p_set |=  PDWN_EDT_CUT
 				| PDWN_EDT_COPY
 				| PDWN_EDT_PASTE;

 	}else{									/* ｻｰﾁ入力中 */
	 	p_set |=  PDWN_EDT_SRCH;
 	}
	LibPullDownAtrSet( PULLDOWN_HTNDSP, PULLDOWN_EDIT, p_set);


	/*== [System]網掛け指定 ==*/
	p_set = 0;
	if(DicStatus==ST_ILOOP){				/* ｻｰﾁ入力中 */
	 	p_set |=  PDWN_SYS_DTTM	
 				| PDWN_SYS_FORMT
 				| PDWN_SYS_MMANE
 				| PDWN_SYS_LANG;
	}
	LibPullDownAtrSet( PULLDOWN_HTNDSP, PULLDOWN_SYSTEM, p_set);



	/*== [Option]網掛け指定 ==*/
	p_set = 0;
	if(DicStatus==ST_ILOOP){			/* ｻｰﾁ入力中 */
		p_set |= PDWN_OPT_SCPY;
	}
	LibPullDownAtrSet( PULLDOWN_HTNDSP, PULLDOWN_OPTION, p_set);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾌﾟﾙﾀﾞｳﾝﾒﾆｭｰ､各種機能処理
	[引数]
	[戻り値]
		FALSE	: 通常終了
		TRUE	: 画面再描画の必要あり
	[処理内容]
******************************************************************************/
bool DicPdwnFnc(TXTP *tp)
/*TAIL*/
{
	word	sel;
	bool	jdg = FALSE;

	sel = LibPullDown();		/* ﾌﾟﾙﾀﾞｳﾝﾒﾆｭｰ */

	if(sel & PULLDOWN_EDIT){	/* ｢Edit｣選択の時 */
		jdg = PdwnFncEdt(sel,tp);

	}else if(sel & PULLDOWN_SYSTEM){
		jdg = PdwnFncSys(sel);

	}else if(sel & PULLDOWN_OPTION){
		jdg = PdwnFncOpt(sel);
	}
	return(jdg);
}



/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾌﾟﾙﾀﾞｳﾝﾒﾆｭｰ､各種機能処理(Edit系)
	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
bool PdwnFncEdt(word sel, TXTP *tp)
/*TAIL*/
{
	bool	jdg = FALSE;

	switch(sel){

	/*** Copy ***/
		case PDWN_EDT_COPY:
			tp->txtst = TXTCOPY;
			break;

	/*** Cut ***/
		case PDWN_EDT_CUT:
			tp->txtst = TXTCUT;
			break;

	/*** Paste ***/
		case PDWN_EDT_PASTE:
			tp->txtst = TXTPASTE;
			break;

	/*** Search ***/
		case PDWN_EDT_SRCH:
			DicStatus = ST_IINI;		/* 検索語入力へ */
			jdg = TRUE;
			break;
	}
	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾌﾟﾙﾀﾞｳﾝﾒﾆｭｰ､各種機能処理(System系)
	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
bool PdwnFncSys(word sel)
/*TAIL*/
{
	bool	jdg = FALSE;
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

		case PDWN_SYS_LANG:		/* Language				*/
			jdg = LibFuncLang();
			if(jdg==TRUE){
				if(DicStatus==ST_LTCHIDLE)		/* 現在､ﾘｽﾄ表示中なら... */
					DicStatus = ST_LDATADSP;	/* ﾘｽﾄ画面書き換え */
				else if(DicStatus==ST_STCHIDLE)	/* 現在､ﾃﾞｰﾀ表示中なら... */
					DicStatus = ST_SBKDSP;		/* ﾃﾞｰﾀ再表示 */
			}
			break;

		case PDWN_SYS_CNTRS:	/* Contrast				*/
			LibFuncContrast();
			break;

		case PDWN_SYS_TPA:		/* Touch_Panel_Alignment*/
			LibFuncDigitizer();
			break;

	/*	case PDWN_SYS_DTCOM:	/* Data_communication	*/
	/*		LibDataCom();
	/*		break;
	*/
	}
	return(jdg);
}

/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾌﾟﾙﾀﾞｳﾝﾒﾆｭｰ､各種機能処理(Option系)
	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
bool PdwnFncOpt(word sel)
/*TAIL*/
{
	switch(sel){

	 /*** Screen Copy ***/
		case PDWN_OPT_SCPY:
			DicScrnShot();			/* ｽｸﾘｰﾝｼｮｯﾄ */
			break;
	}
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		Screen Shot 機能処理
	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void DicScrnShot(void)
/*TAIL*/
{
	Screen.x		= 0;				/* 左上横 */
	Screen.y		= 13;				/* 左上縦 */
	Screen.x_size	= 147-Screen.x+1;	/* 横ｻｲｽﾞ */
	Screen.y_size	= 140-Screen.y+1;	/* 縦ｻｲｽﾞ */
	Screen.p_x		= 6;				/* 貼り付け位置 横 */
	Screen.p_y		= 29;				/* 貼り付け位置 縦 */

	LibScrShot(&Screen);				/* ｽｸﾘｰﾝｼｮｯﾄ */
}
