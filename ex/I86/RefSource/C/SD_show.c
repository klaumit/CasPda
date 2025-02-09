/******************************************************************************
	[ﾀｲﾄﾙ]
		Referencer

	[機種]
		通信電子手帳(海外)

	[概要]
		Referencer ﾃﾞｰﾀ詳細表示

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

XT_SCR_POS	DicDataScr;			/* ﾃﾞｰﾀ表示用ｽｸﾛｰﾙﾊﾞｰ */
XT_SCR_POS	LinkDataScr;		/* Linkﾃﾞｰﾀ表示用ｽｸﾛｰﾙﾊﾞｰ */
byte far	*dttop;				/* ﾀｰｹﾞｯﾄﾃﾞｰﾀ開始ｱﾄﾞﾚｽ */
DSPCT		dctrl;				/* 表示制御用ﾊﾟﾗﾒｰﾀ */
DSPCT		lctrl;				/* 表示制御用ﾊﾟﾗﾒｰﾀ2 */
byte		idxsp;				/* ｲﾝﾃﾞｯｸｽｽﾀｯｸﾎﾟｲﾝﾀｰ */
byte		ttn[TT_LEN+4];		/* ﾃﾞｰﾀﾀｲﾄﾙ名 */
word		sel_sp;				/* 選択開始文字 */
word		sel_ep;				/* 選択終了文字 */
word		rsp;				/* 反転開始文字 */
word		rep;				/* 反転終了文字 */
bool		lktch;				/* ﾘﾝｸﾀｯﾁ中ﾌﾗｸﾞ */
bool		jprv;				/* ﾘﾝｸﾀｯﾁ反転中ﾌﾗｸﾞ */
bool		jprvbk;				/* ﾘﾝｸﾀｯﾁ反転中ﾌﾗｸﾞ退避ｴﾘｱ */
byte far	*lnksp;				/* ﾘﾝｸ開始ﾎﾟｲﾝﾀｰ */
byte far	*lnkep;				/* ﾘﾝｸ終了ﾎﾟｲﾝﾀｰ(+1) */
DSPCT		ddct;				/* 表示制御用ﾊﾟﾗﾒｰﾀ */

/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示初期化

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_SINI

	[処理内容]
******************************************************************************/
void DicShowInit(void)
/*TAIL*/
{
	/*** ﾀｯﾁｴﾘｱ設定 ***/
	LibTchStackClr();
	LibTchInit();
	TchComSet();						/* ﾀｯﾁｴﾘｱ初期化 */
	LibTchStackPush(TchDtHead);			/* 先頭行ﾎﾞﾀﾝﾀｯﾁｴﾘｱ */
	LibTchStackPush(TchLoupe);			/* 虫眼鏡ﾎﾞﾀﾝﾀｯﾁｴﾘｱ */
	LibTchStackPush(TchDicShow);		/* ﾃﾞｰﾀ表示中ﾀｯﾁｴﾘｱ */
	LibTchStackPush(TchActionKey);		/* ｱｸｼｮﾝｷｰ  ﾀｯﾁﾃｰﾌﾞﾙ */

	/*** ｽｸﾛｰﾙﾊﾞｰ初期設定 ***/
	DicDataScr.x	= D_EDX+3;			/* ｽｸﾛｰﾙﾊﾞｰ位置(X) */
	DicDataScr.y	= D_STY+1;			/* ｽｸﾛｰﾙﾊﾞｰ位置(Y) */
	DicDataScr.size	= D_EDY-D_STY-3;	/* ｽｸﾛｰﾙﾊﾞｰ高さ */
	DicDataScr.dsp	= D_LNC;			/* 表示件数     */
	sdp[idxsp].pos	= 0;				/* 先頭行から表示 */

	DicStatus	= ST_SBKDSP;			/* 背景表示へ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示背景描画

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_SBKDSP

	[処理内容]
******************************************************************************/
void DicShowBk(void)
/*TAIL*/
{
	byte far	*tgt;
	long		vol;
	DSPCT		dctwk;

	SelRevOff();						/* 反転ﾌﾗｸﾞ解除 */
	LibClrDisp();						/* 画面消去 */

	LibLine(1,13,158,1,1);				/* 背景表示(上線) */
	LibLine(1,159,158,1,1);				/* 背景表示(下線) */

	LibLine(  0,14,1,145,1);			/* 背景表示(左線) */
	LibLine(147,14,1,145,1);			/* 背景表示(中線) */
	LibLine(159,14,1,145,1);			/* 背景表示(右線) */

	LibModeIconDsp();					/* Pop Up Tools */
	LibPutGraph(0,1,micn);				/* 左上ﾓｰﾄﾞｱｲｺﾝ */

	LibPutGraph(14,0,ShowTopBtn);		/* 先頭行ﾎﾞﾀﾝ */
	if(idxsp<=0)						/* ｲﾝﾃﾞｯｸｽｽﾀｯｸが空の時 */
		LibGdsMesh(69,0,94,11);			/* Backﾎﾞﾀﾝは網掛け */

	LibPutFarData(98,0,44);				/* 虫眼鏡ﾎﾞﾀﾝｱｲｺﾝ   */
	LibPutGraph(108,1,loupe);			/* 虫眼鏡の絵 */

	if(DicDataRead(&sdp[idxsp],&tgt)==FALSE){	/* ﾀｰｹﾞｯﾄﾃﾞｰﾀ読み込み */
		DicStatus = ST_MODEINI;			/* Fail Safe */
		return;
	}
	dttop = tgt-3;						/* 本文開始ｱﾄﾞﾚｽ */

	/*** ｽｸﾛｰﾙﾊﾞｰ初期設定 ***/
	dctwk.x		= D_STX;
	dctwk.sx	= D_STX;
	dctwk.sy	= D_STY;
	dctwk.ex	= D_EDX;
	dctwk.ey	= D_EDY;
	dctwk.ity	= D_ITY;
	vol = GetDicDspL(dttop,&dctwk);		/* 全体縦幅取得(行数) */
	DicDataScr.vol	= vol;				/* ｽｸﾛｰﾙﾊﾞｰ全体量 */
	DicDataScr.pos	= sdp[idxsp].pos;	/* ｽｸﾛｰﾙﾊﾞｰ初期位置 */

	DicStatus	= ST_SDATADSP;			/* 表示ﾃﾞｰﾀｾｯﾄへ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		表示ﾃﾞｰﾀｾｯﾄ

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_SDATADSP

	[処理内容]
******************************************************************************/
void DicShowDataDsp(void)
/*TAIL*/
{
	int			ltc;				/* ﾃﾞｰﾀ表示開始行位置 */

	LibGdsClr(D_STX-D_SFTX*2,D_STY,D_EDX-1,D_EDY-1);	/* 枠内画面消去 */

	/*** 表示初期位置設定 ***/
	ddct.sx		= D_STX;
	ddct.sy		= D_STY;
	ddct.ex		= D_EDX;
	ddct.ey		= D_EDY;
	ddct.lnc	= D_LNC;
	ddct.fnt	= IB_PFONT1;
	ddct.ity	= D_ITY;
	ddct.pot 	= dttop;				/* ﾊﾞｯﾌｧ先頭 */
	ddct.lkpt	= dttop;				/* とりあえずﾘﾝｸ無し */
	ddct.jpf	= FALSE;				/* とりあえずｼﾞｬﾝﾌﾟ無し */
	ddct.st		= 0;					/* とりあえず通常文章 */
	ltc = DicDataScr.pos;
	DicDspTopSrc(&ddct, ltc);			/* 表示開始位置ｻｰﾁ */

	dctrl = ddct;						/* 画面先頭ﾊﾟﾗﾒｰﾀ退避 */
/*	if(dctrl.lkpt < dctrl.pot)
/*		lkpsp = 0;
*/
	DicDltpClear(&ddct);				/* 行ﾊﾟﾗﾒｰﾀ初期化 */
	DicTxtDsp(&ddct);					/* 指定行位置から画面表示 */

	DicStatus	= ST_SSBARDSP;			/* ｽｸﾛｰﾙﾊﾞｰ表示へ */
}

/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示ｽｸﾛｰﾙﾊﾞｰｾｯﾄ

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_SSBARDSP

	[処理内容]
******************************************************************************/
void DicShowSbarDsp(void)
/*TAIL*/
{
	DLibScrollPrint(DicDataScr);		/* ｽｸﾛｰﾙﾊﾞｰ表示 */

	/** BIOSﾊﾞｸﾞ対策 **/
	LibGdsClr(D_EDX,D_STY,D_EDX+2,D_EDY-1);	/* ｽｸﾛｰﾙﾊﾞｰ左側画面消去 */
	LibLine(147,14,1,145,1);				/* 背景表示(中線) */

	/** 前次ﾃﾞｰﾀｷｰ網掛け処理 **/
	if(sdp[idxsp].num<=0)					/* 先頭ﾃﾞｰﾀ表示中 */
		LibPutGraph(14+29,0,MeshArrow[0]);	/* 前ﾃﾞｰﾀｷｰ網抜き表示 */
	if(sdp[idxsp].num>=tidxc-1)				/* 最終ﾃﾞｰﾀ表示中 */
		LibPutGraph(14+42,0,MeshArrow[1]);	/* 次ﾃﾞｰﾀｷｰ網抜き表示 */

	DicStatus	= ST_STCHIDLE;				/* ﾀｯﾁ待ちへ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		表示開始位置ｻｰﾁ

	[引数]
		DSPCT		*dct	: in/out	
		int			tlc		: ﾃｷｽﾄ縦幅(D_ITY)を一行として、表示開始行数

	[処理内容]
		ﾃｷｽﾄ縦幅(D_ITY)を一行として、指定行数分ｽｸﾛｰﾙさせた状態の
		表示開始ﾃﾞｰﾀﾎﾟｲﾝﾀｰ、及び表示開始座標(Y)を取得する
******************************************************************************/
void DicDspTopSrc(DSPCT *dct, int tlc)
/*TAIL*/
{
	int 		lc, lcbk;
	byte far	*ltop;

	/*** 表示ﾙｰﾌﾟ ***/
	lc = lcbk = 0;
	for(;;){
		ltop = dct->pot;
		dct->y = dct->sy;
		if(DicDsp1L(dct,FALSE)==FALSE)	/* 一行分処理 */
			break;

	/* 増加ﾃｷｽﾄ行数を取得 */
		lcbk = lc;
		lc += (dct->y - dct->sy) / (dct->ity);
		if(lc==tlc){
			lcbk = lc;
			ltop = dct->pot;
			break;
		}
		else if(lc>tlc){
			break;
		}
	}

	dct->pot = ltop;
	dct->y = dct->sy - (tlc-lcbk) * (dct->ity);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示行ﾊﾟﾗﾒｰﾀ初期化

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void DicDltpClear(DSPCT *dct)
/*TAIL*/
{
	int		i;

	for(i=0;i<dct->lnc;i++){
		dltp[i].ofs = 0xffff;
		dltp[i].fnt = 0xff;
		dltp[i].lnk = 0xffff;
		dltp[i].st  = 0;
	}
}

/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃｷｽﾄ表示ﾒｲﾝ

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void DicTxtDsp(DSPCT *dct)
/*TAIL*/
{
	int		i,j;
	word	gt;
	word	ntop;			/* ﾃﾞｰﾀ表示終了次ｵﾌｾｯﾄ */

	AdjustStartX(dct);		/* 表示開始横座標設定 */

	/*** 表示ﾙｰﾌﾟ ***/
	while(1){
		if(dct->y>=dct->sy){
			j = (dct->y-dct->sy)/dct->ity;
			if(j>dct->lnc){
				break;					/* Fale Safe */
			}
			dltp[j].ofs = (word)(dct->pot - dttop);		/* 行頭ﾎﾟｲﾝﾀｰｾｯﾄ */
			dltp[j].fnt = dct->fnt;						/* 行頭文字ﾌｫﾝﾄｾｯﾄ */
			dltp[j].lnk = (word)(dct->lkpt - dttop);	/* 行頭ﾘﾝｸｾｯﾄ */
			dltp[j].jpf = dct->jpf;						/* ｼﾞｬﾝﾌﾟ状態ｾｯﾄ */
			dltp[j].st  = dct->st;						/* 行頭文字状態ｾｯﾄ */
		}
		if(dct->y >= dct->sy+D_ITY*dct->lnc){		/* 一画面分表示終了 */
			break;
		}
		if(DicDsp1L(dct,TRUE)==FALSE)	/* 一行分処理 */
			break;						/* 終了ｺｰﾄﾞ発見時 */
	}
	ntop = (word)(dct->pot - dttop);

	/* 画像途中行､またはﾃﾞｰﾀ末以降行ﾎﾟｲﾝﾀｰ設定 */
	gt = ntop;			/* とりあえず画面先頭 */
	for(i=dct->lnc-1;i>=0;i--){
		if(dltp[i].ofs==0xffff)		/* 対象行？ */
			dltp[i].ofs = ntop;		/* 次先頭をｺﾋﾟｰ */
		else
			ntop = dltp[i].ofs;		/* 次先頭ﾎﾟｲﾝﾀｰを更新 */
	}
	return;
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示開始X座標調整

	[引数]
	[戻り値]
	[処理内容]
		ﾃﾞｰﾀ表示の際、表示開始X座標を調整する。
		通常は「stx」だが、見出し(小見出し)を表示中は左に12ﾄﾞｯﾄ(6ﾄﾞｯﾄ)
		ｼﾌﾄさせる。
******************************************************************************/
void AdjustStartX(DSPCT *dct)
/*TAIL*/
{
	dct->x = dct->sx;				/* 通常は表示開始設定値そのまま */

	if(dct->st==1 || dct->st==2)	/* 見出し､小見出しの時 */
		dct->x -= dct->st*D_SFTX;	/* 開始座標を左にｼﾌﾄ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示 ﾀｯﾁ待ち

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_STCHIDLE

	[処理内容]
******************************************************************************/
void DicShowTchIdle(void)
/*TAIL*/
{
	TCHSTS		tsts;
	TXTP		tp;
	byte		amsk;
	byte		ret;
	DSPCT		dct;
	bool		jdg;
	byte far	*dttopbk;			/* ﾀｰｹﾞｯﾄﾃﾞｰﾀ開始ｱﾄﾞﾚｽ退避ｴﾘｱ */

	dct = dctrl;					/* 画面先頭ﾊﾟﾗﾒｰﾀ戻し */

	/* ｽｸﾛｰﾙﾊﾞｰ上下矢印網掛け処理 */
	DLibScrollArrowPrint(DicDataScr,SCR_NO_MASK);
	amsk = DataArrowMask(&DicDataScr);
	DLibScrollArrowPrint(DicDataScr,amsk);

	while(DicStatus==ST_STCHIDLE){

		DicRevDisp(&dct);				/* 選択反転表示 */
		LibPutDisp();					/* 画面更新 */
		LibTchWait( &tsts );			/* ﾀｯﾁ待ち */
		DicRevDisp(&dct);				/* 選択反転消去 */

		switch(tsts.obj){

			case OBJ_LPSW_UP:			/* ｱｸｼｮﾝｷｰ Up */
				if(ChkScrlDwn(&DicDataScr)==TRUE){
					DicDataScr.pos --;
					SelRevOff();			/* 反転ﾌﾗｸﾞ解除 */
					DicShowScrDwn();			/* ｽｸﾛｰﾙｱｯﾌﾟ処理 */
					DicStatus	= ST_SSBARDSP;	/* ｽｸﾛｰﾙﾊﾞｰ表示へ */
					if(ChkScrlDwn(&DicDataScr)!=TRUE){
						LibRepOff();			/* ﾘﾋﾟｰﾄ Off */
						LibTchInit();
					}
				}else{
					DicPrevBtn(&tsts,FALSE);
					LstCsrAdjust();				/* ﾘｽﾄｶｰｿﾙ調整 */
					LibRepOff();				/* ﾘﾋﾟｰﾄ Off */
					LibTchInit();
				}
				break;

			case OBJ_LPSW_DOWN:			/* ｱｸｼｮﾝｷｰ Down */
				if(ChkScrlUp(&DicDataScr)==TRUE){
					DicDataScr.pos ++;
					SelRevOff();				/* 反転ﾌﾗｸﾞ解除 */
					DicShowScrUp();				/* ｽｸﾛｰﾙｱｯﾌﾟ処理 */
					DicStatus	= ST_SSBARDSP;	/* ｽｸﾛｰﾙﾊﾞｰ表示へ */
					if(ChkScrlUp(&DicDataScr)!=TRUE){
						LibRepOff();			/* ﾘﾋﾟｰﾄ Off */
						LibTchInit();
					}
				}else{
					DicNextBtn(&tsts,FALSE);
					LstCsrAdjust();				/* ﾘｽﾄｶｰｿﾙ調整 */
					LibRepOff();				/* ﾘﾋﾟｰﾄ Off */
					LibTchInit();
				}
				break;

			case OBJ_LPSW_PUSH:			/* ｱｸｼｮﾝｷｰ Push */
				LibCallListMenu();			/* Action Menuへ */
				break;

			case OBJ_SCR_BAR:			/* ScrollBar */
				ret = DicShowScBar(&tsts, &DicDataScr);
				if(ret==1){					/* ｽｸﾛｰﾙﾊﾞｰ▲ﾎﾞﾀﾝの時 */
					SelRevOff();				/* 反転ﾌﾗｸﾞ解除 */
					DicShowScrDwn();			/* ｽｸﾛｰﾙﾀﾞｳﾝ処理 */
					DicStatus	= ST_SSBARDSP;	/* ｽｸﾛｰﾙﾊﾞｰ表示へ */

				}else if(ret==2){			/* ｽｸﾛｰﾙﾊﾞｰ▼ﾎﾞﾀﾝの時 */
					SelRevOff();				/* 反転ﾌﾗｸﾞ解除 */
					DicShowScrUp();				/* ｽｸﾛｰﾙｱｯﾌﾟ処理 */
					DicStatus	= ST_SSBARDSP;	/* ｽｸﾛｰﾙﾊﾞｰ表示へ */

				}else if(ret==3){			/* ﾀｯﾁorﾄﾞﾗｯｸﾞ時 */
					SelRevOff();				/* 反転ﾌﾗｸﾞ解除 */
					DicStatus = ST_SDATADSP;	/* ﾃﾞｰﾀ再表示 */
				}
				break;

			case OBJ_AR_SHOW:			/* 表示ｴﾘｱ */
				jdg = DicShowAreaTch(&tsts,&dct);	/* ﾘﾝｸ･ｼﾞｬﾝﾌﾟ該当文字? */
				if(jdg!=FALSE){				/* ﾘﾝｸｼﾞｬﾝﾌﾟ発生 */
					DicRevDisp(&dct);				/* 下画面(ﾃﾞｰﾀ表示)選択反転表示 */
					ret = GetLinkIndex(jdg);		/* ﾘﾝｸｼﾞｬﾝﾌﾟ先ｲﾝﾃﾞｯｸｽ取得 */

					if(ret==1){				/* ｼﾞｬﾝﾌﾟの時 */
						DicStatus = ST_SBKDSP;		/* 表示ﾃﾞｰﾀ更新 */

					}else if(ret==2){		/* ﾘﾝｸの時 */
						dttopbk	= dttop;			/* ﾃﾞｰﾀ開始ｱﾄﾞﾚｽ退避 */
						DicLinkShowDsp();			/* ﾘﾝｸﾃﾞｰﾀ表示 */
						if(DicStatus!=ST_IINI)		/* ｻｰﾁ入力移行時以外は... */
							DicStatus = ST_SBKDSP;	/* ﾃﾞｰﾀ再表示 */
						dttop	= dttopbk;			/* ﾃﾞｰﾀ開始ｱﾄﾞﾚｽ戻し */

					}else{					/* ｲﾝﾃﾞｯｸｽｽﾀｯｸが一杯の時 */
						LibWinIcnMsg(ICON_BIKKURI,500,1);
													/* 一秒表示､"これ以上ｼﾞｬﾝﾌﾟできません！" */
						DicRevDisp(&dct);			/* 下画面(ﾃﾞｰﾀ表示)選択反転戻し */
					}
				}
				break;

			case OBJ_HIC_ESC:
				if(idxsp==0){				/* 通常ﾃﾞｰﾀ表示中 */
					if(jprv!=FALSE){				/* 反転中なら */
						SelRevOff();				/* 反転ﾌﾗｸﾞ解除 */
					}else{
						LstCsrAdjust();				/* ﾘｽﾄｶｰｿﾙ調整 */
						DicStatus = ST_LTCHINI;		/* ﾘｽﾄ表示へ */
					}
				}else{						/* Jump後のﾃﾞｰﾀ表示中 */
					DicBackBtnSub();				/* 前回表示ﾃﾞｰﾀへ */
				}
				break;

			case OBJ_IC_SRCKEY:
				DicSrcBtn(&tsts);
				break;

			case OBJ_IC_LSTKEY:
				if(LibBlockIconClick(&TicnDtLst,&tsts,B_ICON_LEFT)==TRUE){
					LstCsrAdjust();					/* ﾘｽﾄｶｰｿﾙ調整 */
					DicStatus = ST_LTCHINI;			/* ﾘｽﾄ表示へ */
				}
				break;

			case OBJ_IC_PRVKEY:		/* "↑"ｷｰ */
				DicPrevBtn(&tsts,TRUE);
				LstCsrAdjust();				/* ﾘｽﾄｶｰｿﾙ調整 */
				break;

			case OBJ_IC_NXTKEY:		/* "↓"ｷｰ */
				DicNextBtn(&tsts,TRUE);
				LstCsrAdjust();				/* ﾘｽﾄｶｰｿﾙ調整 */
				break;

			case OBJ_IC_BCKKEY:		/* "←"ｷｰ */
				DicBackBtn(&tsts);
				break;

			case OBJ_HIC_MBAR:		/* ﾒﾆｭｰﾊﾞｰﾊｰﾄﾞｱｲｺﾝ */
				DicRevDisp(&dct);			/* 選択反転表示 */
				DicPdwnSet();				/* ﾌﾟﾙﾀﾞｳﾝﾒﾆｭｰ表示設定 */
				DicPdwnFnc(&tp);			/* ﾌﾟﾙﾀﾞｳﾝ処理 */
				DicRevDisp(&dct);			/* 選択反転消去 */
				break;
		}
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示ｽｸﾛｰﾙｱｯﾌﾟ

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void DicShowScrUp(void)
/*TAIL*/
{
	SHWIDX		swk;				/* 表示制御用ﾊﾟﾗﾒｰﾀ */
	DSPCT		dct;
	int			i, stl, cysp;

	/* 行ﾊﾟﾗﾒｰﾀｼﾌﾄ */
	swk = dltp[0];
	for(i=1;i<D_LNC;i++){			/* 画面下行はｼﾌﾄしない */
		dltp[i-1] = dltp[i];
	}

	for(i=D_LNC-1;i<=D_LNC;i++){	/* 画面末行初期化 */
		dltp[i].ofs = 0xffff;
		dltp[i].fnt = 0xff;
		dltp[i].lnk = 0xffff;
		dltp[i].st  = 0;
	}

	/* 画面表示開始行ﾊﾟﾗﾒｰﾀ戻し */
	dctrl.sx	= D_STX;
	dctrl.sy	= D_STY;
	dctrl.ex	= D_EDX;
	dctrl.ey	= D_EDY;
	dctrl.lnc	= D_LNC;
	dctrl.ity	= D_ITY;

	if(dltp[0].fnt!=0xff){		/* 先頭行から表示可能な時 */
		dctrl.fnt	= dltp[0].fnt;
		dctrl.pot 	= dttop+dltp[0].ofs;
		dctrl.lkpt	= dttop+dltp[0].lnk;
		dctrl.jpf	= dltp[0].jpf;
		dctrl.st	= dltp[0].st;
		dctrl.y		= D_STY;
	}else{						/* 先頭行より前から表示する時 */
		if(swk.fnt!=0xff){		/* -1行から表示する時 */
			dctrl.fnt	= swk.fnt;
			dctrl.pot 	= dttop+swk.ofs;
			dctrl.lkpt	= dttop+swk.lnk;
			dctrl.jpf	= swk.jpf;
			dctrl.st	= swk.st;
			dctrl.y		= D_STY;
		}
		dctrl.y -= D_ITY;
	}

	/* 表示開始行位置ｻｰﾁ */
	for(stl=D_LNC-2;stl>=0;stl--){
		if(dltp[stl].fnt!=0xff){
			swk = dltp[stl];	/* ﾃｷｽﾄがある行､又はｸﾞﾗﾌｨｯｸ開始行から表示開始 */
			break;
		}
	}

	/* 最下行表示 */
	dct	= dctrl;
	cysp	= D_STY;
	if(stl>=0){
		dct.fnt	= dltp[stl].fnt;
		dct.pot = dttop+dltp[stl].ofs;
		dct.lkpt= dttop+dltp[stl].lnk;
		dct.jpf	= dltp[stl].jpf;
		dct.st	= dltp[stl].st;
		dct.y	= dct.sy + dct.ity*stl;
		cysp	+= D_ITY*stl;
		LibGrpUp(D_STX-D_SFTX*2, D_STY, D_EDX-(D_STX-D_SFTX*2),D_EDY-D_STY, D_ITY);
								/* ｽｸﾛｰﾙｱｯﾌﾟ */
	}
	LibGdsClr(D_STX-D_SFTX*2, cysp, D_EDX, D_EDY-1);	/* 画面ｸﾘｱ */
	DicTxtDsp(&dct);			/* 指定行位置から画面表示 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示ｽｸﾛｰﾙﾀﾞｳﾝ

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void DicShowScrDwn(void)
/*TAIL*/
{
	int			i;
	SHWIDX		swk;
	DSPCT		dct;
	byte		lc;

	LibGrpDwn(D_STX-D_SFTX*2, D_STY, D_EDX-(D_STX-D_SFTX*2), D_EDY-D_STY, D_ITY);
									/* ｽｸﾛｰﾙﾀﾞｳﾝ */
	/* 行ﾊﾟﾗﾒｰﾀｼﾌﾄ */
	for(i=D_LNC;i>0;i--){
		dltp[i] = dltp[i-1];
	}
	dltp[0].ofs = 0xffff;
	dltp[0].fnt = 0xff;
	dltp[0].lnk = 0xffff;
	dltp[0].st  = 0;

	if(dctrl.y<dctrl.sy){			/* 先頭行より前から表示していた時 */
		dctrl.y		+= D_ITY;
		dct			= dctrl;

	}else{
		swk = dltp[1];
		lc = PrvLineTop(&swk);		/* 前行先頭ｻｰﾁ */

		/*** 表示初期位置設定 ***/
	/*	dctrl.sx	= D_STX;
	/*	dctrl.sy	= D_STY;
	/*	dctrl.ex	= D_EDX;
	/*	dctrl.ey	= D_EDY;
	/*	dct.lnc		= D_LNC;
	*/
		dctrl.ity	= D_ITY;
		dctrl.fnt	= swk.fnt;
		dctrl.pot 	= dttop+swk.ofs;
		dctrl.lkpt	= dttop+swk.lnk;
		dctrl.jpf	= swk.jpf;
		dctrl.st	= swk.st;
		dctrl.y		= D_STY-(D_ITY*(lc-1));
		dct			= dctrl;
	}

	dct.ey	= dct.sy + D_ITY;
	dct.lnc	= 1;
	DicTxtDsp(&dct);			/* 画面先頭行分を表示 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		前行先頭ｻｰﾁ

	[引数]
		SHWIDX	*swk	: in/out	現在行先頭/前行先頭ﾊﾟﾗﾒｰﾀ

	[戻り値]
		前行表示縦幅必要行数 ･･･ (ﾃｷｽﾄのみの行ならば１)
									ｴﾗｰ時、０
	[処理内容]
******************************************************************************/
byte PrvLineTop(SHWIDX *swk)
/*TAIL*/
{
	DSPCT		dctemp;
	int			lc;
	byte far	*ntop;

	ntop = dttop+swk->ofs;
	PrvRtnTopSrc(swk,ntop);		/* 強制改行ｺｰﾄﾞ前方ｻｰﾁ */

	dctemp.x	= D_STX;
	dctemp.sx	= D_STX;
	dctemp.sy	= D_STY;
	dctemp.ex	= D_EDX;
	dctemp.ey	= D_EDY;
	dctemp.fnt	= swk->fnt;
	dctemp.ity	= D_ITY;
	dctemp.pot	= dttop+swk->ofs;
	dctemp.lkpt	= dttop+swk->lnk;
	dctemp.jpf	= swk->jpf;

	while(1){
		swk->ofs = dctemp.pot-dttop;
		swk->fnt = dctemp.fnt;
		swk->st  = dctemp.st;
		swk->lnk = dctemp.lkpt-dttop;
		swk->jpf = dctemp.jpf;

		dctemp.y = D_STY;
		if(DicDsp1L(&dctemp,FALSE)==FALSE)	/* 一行分処理 */
			return(0);						/* Fale Safe */
		if(dctemp.pot>=ntop)
			break;
	}

	lc = (dctemp.y - D_STY)/D_ITY;
	return(lc);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		強制改行ｺｰﾄﾞ前方ｻｰﾁ

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void PrvRtnTopSrc(SHWIDX *swk, byte far *ntop)
/*TAIL*/
{
	byte		cd;
	bool		loop = TRUE;
	word		ltop,llnk;
	byte far	*tgt;
	byte		lfnt = FNT_BASE;
	byte		ltst  = 0;

	tgt = dttop;
	ltop = llnk = 0;

	swk->ofs = 0;			/* とりあえず */
	swk->lnk = 0;

	while(loop){
		cd = JdgContCode(&tgt);
		switch(cd){

			case CD_END:
				break;

			case CD_RTN:
		/*		if(tgt >= dttop+swk->ofs){
		*/
				if(tgt >= ntop){
					loop = FALSE;		/* ﾙｰﾌﾟ終了 */
					break;
				}
				if(ltst!=0){
					lfnt = IB_PFONT1;
					ltst = 0;
				}
				swk->ofs = tgt-dttop;
				swk->fnt = lfnt;
				swk->st  = 0;
				swk->lnk = llnk;
				break;

			case CD_CHA:			/* 文字ｺｰﾄﾞ「00h～7Fh」 */
			case CD_OVCHA:			/* 1ﾊﾞｲﾄｺｰﾄﾞ指定(0x80以上)「@\x??」 */
				tgt++;
				break;

			case CD_TITLE:
				lfnt = IB_PFONT2;
				ltst = 2;
				break;

			case CD_SUBT:
				lfnt = IB_PFONT2;
				ltst = 1;
				break;

			case CD_LINK:
				lfnt = IB_PFONT2;
				ltst = 1;
				break;

			case CD_FNT57:
				lfnt = IB_CG57FONT;
				break;

			case CD_FNTPN:
				lfnt = IB_PFONT1;
				break;

			case CD_FNTPB:
				lfnt = IB_PFONT2;
				break;

			case CD_LKDEF:			/* ﾘﾝｸ指定「@\l+文字列長(1byte)」 */
			case CD_JPDEF:			/* ｼﾞｬﾝﾌﾟ指定「@\j+文字列長(1byte)」 */
				llnk = tgt-dttop+(*tgt)+1;
				tgt ++;
				break;

			case CD_GPDEF:			/* 画像指定「@\g????」 */
				tgt += 2;
				break;
		}
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中、反転ﾌﾗｸﾞ解除
	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void SelRevOff(void)
/*TAIL*/
{
	jprv = FALSE;				/* ﾘﾝｸ選択中ﾌﾗｸﾞｸﾘｱ */
	sel_sp = sel_ep = 0xffff;	/* 反転表示解除 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示→ﾘｽﾄ表示､ｶｰｿﾙ位置調整
	[引数]
	[戻り値]
	[処理内容]
		現在ﾃﾞｰﾀ表示中のﾃﾞｰﾀがﾘｽﾄ画面内に在る時にはそこにｶｰｿﾙを
		移動させ、もし、ﾘｽﾄ上に無い場合にはｽｸﾛｰﾙさせて画面内に
		ｶｰｿﾙを移動させる。
******************************************************************************/
void LstCsrAdjust(void)
/*TAIL*/
{
	long	nownum;
	int		i;

	nownum = sdp[idxsp].num;

	/*** 通常のﾃﾞｰﾀ表示からの戻りの場合 ***/
	if(idxsp==0){

		/* ﾘｽﾄ範囲より前(上)のﾃﾞｰﾀの時 */
		if(nownum<lip[0].num){
			DicLstScr.pos = nownum;
			lcp = 0;				/* ｶｰｿﾙは先頭行 */

		/* ﾘｽﾄ範囲より後(下)のﾃﾞｰﾀの時 */
		}else if((lip[L_LNC-1].num<nownum)&&(lip[L_LNC-1].num!=0xffffffff)){
			DicLstScr.pos += nownum - lip[L_LNC-1].num;
			lcp = L_LNC-1;			/* ｶｰｿﾙは最下行 */

		/* ﾘｽﾄ範囲内に在るﾃﾞｰﾀの時 */
		}else{
			lcp = 0;				/* とりあえず (Fale Safe) */
			for(i=0;i<L_LNC;i++){
				if(lip[i].num==nownum){
					lcp = i;
					return;
				}
			}
		}

	/*** ｼﾞｬﾝﾌﾟ先からの戻りの場合 ***/
	}else{
		DicLstScr.pos = nownum;
		lcp = 0;				/* ｶｰｿﾙは先頭行 */
	}

	lip[0].num = DicLstScr.pos;
	for(i=1;i<L_LNC;i++){
		lip[i].num = lip[i-1].num + 1;
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中､ｽｸﾛｰﾙﾊﾞｰ内ﾀｯﾁ時処理

	[引数]
	[戻り値]
		0	: 画面未変更
		1	: 上ｽｸﾛｰﾙｷｰ
		2	: 下ｽｸﾛｰﾙｷｰ
		3	: ｽｸﾛｰﾙﾊﾞｰﾀｯﾁ or ﾄﾞﾗｯｸﾞ

	[処理内容]
******************************************************************************/
byte DicShowScBar(TCHSTS *tsts, XT_SCR_POS *scr)
/*TAIL*/
{
	int		ans;
	byte	type = 0;

	ans = DLibScrPosCheck(*tsts,*scr);
	if(ans==0){					/* 上ｽｸﾛｰﾙｷｰﾀｯﾁ時 */
		if(ChkScrlDwn(scr)==FALSE)
			return(type);					/* 上移動不可の時 */

	}else if(ans==1){			/* 下ｽｸﾛｰﾙｷｰﾀｯﾁ時 */
		if(ChkScrlUp(scr)==FALSE)
			return(type);					/* 下移動不可の時 */
	}

	ans = DLibScrollClick(tsts,scr);
	switch(ans){
		case 0:					/* 上ｽｸﾛｰﾙｷｰﾀｯﾁ時 */
			if(tsts->act==ACT_BREAK_IN){
				if(scr->pos > 0){
					(scr->pos)--;
					type = 1;
				}
			}
			break;

		case 1:					/* 下ｽｸﾛｰﾙｷｰﾀｯﾁ時 */
			if(tsts->act==ACT_BREAK_IN){
				if(scr->pos < scr->vol - scr->dsp){
					(scr->pos)++;
					type = 2;
				}
			}
			break;

		case 2:					/* ｽｸﾛｰﾙﾊﾞｰﾀｯﾁ & ﾄﾞﾗｯｸﾞ時 */
			type = 3;
			break;

		default:
			break;
	}
	return(type);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中､上ｽｸﾛｰﾙ可能判定

	[戻り値]
		TRUE	: ｽｸﾛｰﾙ可能
		FALSE	: 不可
******************************************************************************/
bool ChkScrlUp(XT_SCR_POS *scr)
/*TAIL*/
{
	if(scr->pos >= scr->vol - scr->dsp){
		return(FALSE);		/* 最下行表示中は不可 */
	}
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中､下ｽｸﾛｰﾙ可能判定

	[戻り値]
		TRUE	: ｽｸﾛｰﾙ可能
		FALSE	: 不可
******************************************************************************/
bool ChkScrlDwn(XT_SCR_POS *scr)
/*TAIL*/
{
	if(scr->pos == 0){
		return(FALSE);		/* 先頭行表示中は不可 */
	}
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中､Prevﾎﾞﾀﾝ処理

	[戻り値]
******************************************************************************/
void DicPrevBtn(TCHSTS *tsts, bool btn)
/*TAIL*/
{
	long	tmp;

	if(sdp[idxsp].num<=0)			/* 先頭ﾃﾞｰﾀ表示中 */
		return;

	if(btn==TRUE){
		if(LibBlockIconClick(&TicnDtPrv,tsts,B_ICON_CENTER)!=TRUE)
			return;
	}

	tmp = sdp[idxsp].num;				/* 現在番号退避 */

	idxsp =0;							/* ｲﾝﾃﾞｯｸｽｽﾀｯｸｸﾘｱ */
	sdp[idxsp].num = tmp - 1;			/* 前ﾃﾞｰﾀへ */
	GetIndex(&sdp[idxsp],0);			/* ｲﾝﾃﾞｯｸｽｱﾄﾞﾚｽ取得 */
	sdp[idxsp].pos = 0;					/* 先頭行から表示 */

	DicStatus = ST_SBKDSP;				/* 表示ﾃﾞｰﾀ更新 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中､Nextﾎﾞﾀﾝ処理

	[戻り値]
******************************************************************************/
void DicNextBtn(TCHSTS *tsts, bool btn)
/*TAIL*/
{
	long	tmp;

	if(sdp[idxsp].num>=tidxc-1)			/* 最終ﾃﾞｰﾀ表示中 */
		return;

	if(btn==TRUE){
		if(LibBlockIconClick(&TicnDtNxt,tsts,B_ICON_CENTER)!=TRUE)
			return;
	}

	tmp = sdp[idxsp].num;				/* 現在番号退避 */

	idxsp =0;							/* ｲﾝﾃﾞｯｸｽｽﾀｯｸｸﾘｱ */
	sdp[idxsp].num = tmp + 1;			/* 次ﾃﾞｰﾀへ */
	GetIndex(&sdp[idxsp],0);			/* ｲﾝﾃﾞｯｸｽｱﾄﾞﾚｽ取得 */
	sdp[idxsp].pos = 0;					/* 先頭行から表示 */

	DicStatus = ST_SBKDSP;				/* 表示ﾃﾞｰﾀ更新 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中､Backﾎﾞﾀﾝ処理

	[戻り値]
******************************************************************************/
void DicBackBtn(TCHSTS *tsts)
/*TAIL*/
{
	if(idxsp>0){
		if(LibBlockIconClick(&TicnDtBck,tsts,B_ICON_RIGHT)!=TRUE)
			return;
		DicBackBtnSub();
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中､Backﾎﾞﾀﾝ処理2

	[戻り値]
******************************************************************************/
void DicBackBtnSub(void)
/*TAIL*/
{
	idxsp --;
	DicStatus = ST_SBKDSP;		/* 表示ﾃﾞｰﾀ更新 */
}

/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中､ｻｰﾁﾎﾞﾀﾝ処理

	[戻り値]
		TRUE	: ｽｸﾛｰﾙ可能
		FALSE	: 不可
******************************************************************************/
void DicSrcBtn(TCHSTS *tsts)
/*TAIL*/
{
	bool	jdg;

	jdg = LibIconClick(&TicnLoupe,tsts);
	if(jdg==TRUE){
		srcbf[0] = NULL;		/* ﾃｷｽﾄﾊﾞｯﾌｧ初期化 */
		DicStatus = ST_IINI;		/* 検索語入力へ */
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中､反転選択表示

	[戻り値]
******************************************************************************/
void DicRevDisp(DSPCT *dct)
/*TAIL*/
{
	int		i;
	DSPCT	dwk;
	bool	jdg;
	byte	ccd;

	if(sel_sp<=sel_ep){
		rsp = sel_sp;
		rep = sel_ep;
	}else{
		rsp = sel_ep;
		rep = sel_sp;
	}

	if((rsp==0xffff)||(rep==0xffff))
		return;					/* 選択反転なし */

	dwk		= *dct;

	for(i=0;i<dwk.lnc;i++){

		if(dltp[i].fnt!=0xff){		/* ﾃｷｽﾄが存在する行の時 */
			/* 行先頭設定 */
			dwk.pot	= dttop + dltp[i].ofs;
			dwk.fnt	= dltp[i].fnt;
			dwk.lkpt= dttop + dltp[i].lnk;
			dwk.jpf	= dltp[i].jpf;
			dwk.st	= dltp[i].st;
			dwk.x	= dwk.sx;
			dwk.y	= dwk.sy + D_ITY*i;
			AdjustStartX(&dwk);		/* 表示開始横座標設定 */

			wtct = dwk;				/* 単語先頭情報として退避 */

		/*	DicDsp1L(&dwk,FALSE);		/* 一行処理 */
			while(1){					/* 一行ﾙｰﾌﾟ */
				jdg = DicDsp1C(&dwk,HALF,&ccd);	/* 一文字表示処理 */
				if(jdg==FALSE)
					return;
				else if(jdg==HALF)
					break;
			}
		}
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃｷｽﾄｴﾘｱ内ﾀｯﾁ時処理
	[引数]
	[戻り値]
		TRUE	: ﾘﾝｸﾀｯﾁ発生
		HALF	: ｼﾞｬﾝﾌﾟﾀｯﾁ発生
		FALSE	: ﾘﾝｸ･ｼﾞｬﾝﾌﾟ未発生(通常終了)

	[処理内容]
******************************************************************************/
bool DicShowAreaTch(TCHSTS *tsts, DSPCT *dct)
/*TAIL*/
{
	word	mp, tmp1, tmp2, spbk;
	int		ln;
	bool	jdg = FALSE;

	ln = (tsts->y-dct->sy)/D_ITY;		/* ﾀｯﾁ座標のﾃｷｽﾄ行数 */
	GetTchMj(dct, tsts->x, ln, &mp);	/* ﾀｯﾁ座標該当文字取得 */

	switch(tsts->act){

		case ACT_MAKE:
			jprvbk = jprv;
			spbk = sel_sp;
			sel_sp = mp;
			sel_ep = mp;
			jprv = GetTchLink(&sel_sp,&sel_ep,ln);	/* 該当ﾘﾝｸｴﾘｱ取得 */
			if(spbk!=sel_sp)			/* 反転文字が変わった時 */
				jprvbk = FALSE;
			break;

		case ACT_MOVE_OUT:				/* ﾃｷｽﾄｴﾘｱから外れて行った時 */
			break;

		case ACT_BREAK:
			if(mp!=0xffff){
				tmp1 = sel_sp;
				tmp2 = mp;
				jprv = GetTchLink(&tmp1,&tmp2,ln);	/* 該当ﾘﾝｸｴﾘｱ取得 */
				if(jprv==FALSE){			/* ﾘﾝｸｴﾘｱ外をﾀｯﾁ中 */
					if(sel_sp==0xffff)
						sel_sp = mp;
					sel_ep = mp;
				}
			}
			if( sel_sp==sel_ep || sel_sp==0xffff || sel_ep==0xfffff ){
				sel_sp = sel_ep = 0xffff;
			}
			if((jprv!=FALSE)&&(jprv==jprvbk)){
				jdg = jprv;				/* ﾘﾝｸ･ｼﾞｬﾝﾌﾟ発生 */
			}
			break;

		case ACT_DOWN_IN:				/* ﾃｷｽﾄｴﾘｱ内でﾀｯﾁ中 */
			if(mp!=0xffff){
				tmp1 = sel_sp;
				tmp2 = mp;
				jprv = GetTchLink(&tmp1,&tmp2,ln);	/* 該当ﾘﾝｸｴﾘｱ取得 */
				if(jprv==FALSE){			/* ﾘﾝｸｴﾘｱ外をﾀｯﾁ中 */
					if(sel_sp==0xffff)
						sel_sp = mp;
					sel_ep = mp;
				}
			}
			break;

		case ACT_DOWN:					/* ﾃｷｽﾄｴﾘｱ外でﾀｯﾁ中 */
			break;
	}

	/**** 文字列ﾄﾞﾗｯｸﾞ仕様削除 ****/
	if(jprv==FALSE){
		sel_sp = sel_ep = 0xffff;
	}

	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾀｯﾁされた文字のﾃﾞｰﾀ先頭からのｵﾌｾｯﾄを取得

	[引数]
		DSPCT	*dct	: in	表示制御用ﾊﾟﾗﾒｰﾀ
		int 	tx		: in	ﾀｯﾁ座標(X)
		int		ln		: in	ﾀｯﾁ行位置（0～）
		word	*tgt	: out	該当文字ﾃﾞｰﾀ先頭からのｵﾌｾｯﾄ

	[戻り値]
		0	: 該当文字なし
		1	: 該当文字発見(該当ﾘﾝｸ･ｼﾞｬﾝﾌﾟ無し)
		2	: 行先頭より前
		3	: 行末より後ろ
		4	: 該当ﾘﾝｸ有り

	[処理内容]
******************************************************************************/
byte GetTchMj(DSPCT *dct, int tx, int ln, word *tgt)
/*TAIL*/
{
	DSPCT	dwk;
	byte	ccd;
	bool	jdg = TRUE;
	bool	ljflg = FALSE;

	lktch = FALSE;				/* とりあえず､リンク無し */
	*tgt = dltp[ln].ofs;		/* とりあえず､行先頭 */

	if(dltp[ln].fnt==0xff){		/* 画像途中行､またはﾃﾞｰﾀ末以降行の時 */
		return(0);
	}

	/* 行先頭設定 */
	dwk		= *dct;
	dwk.pot	= dttop + dltp[ln].ofs;
	dwk.fnt	= dltp[ln].fnt;
	dwk.lkpt= dttop + dltp[ln].lnk;
	dwk.jpf	= dltp[ln].jpf;
	dwk.st	= dltp[ln].st;
	dwk.x	= dwk.sx;
	dwk.y	= dwk.sy + D_ITY*ln;
	AdjustStartX(&dwk);		/* 表示開始横座標設定 */

	wtct = dwk;				/* 単語先頭情報として退避 */

	if(tx<dwk.x){
		return(2);			/* ﾀｯﾁ位置は行先頭より前 */
	}

	*tgt = 0xffff;
	while(jdg==TRUE){
		jdg = DicDsp1C(&dwk,FALSE,&ccd);		/* 一文字表示処理 */
		if(jdg==TRUE){			/* 行途中の時 */
			if(tx<dwk.x){
				if(*tgt==0xffff){
					*tgt = (word)(dwk.pot-1-dttop);
					if(dwk.pot-1<dwk.lkpt){		/* ﾘﾝｸｴﾘｱ内の時 */
						ljflg = TRUE;
						lnkep = dwk.lkpt;
					}
				}
			}

		}else if(jdg==HALF){	/* 改行時 */
			if(*tgt==0xffff){
				*tgt = (word)(dwk.pot-1-dttop);
				return(3);
			}

		}else{					/* ﾃﾞｰﾀ終了時 */
			if(*tgt==0xffff){
				*tgt = (word)(dwk.pot-dttop);
				return(3);
			}
		}
	}

	if(*tgt!=0xffff){				/* ﾜｰﾄﾞﾗｯﾌﾟ対応 */
		if((dwk.pot-dttop)<=*tgt){	/* 次行先頭が検出文字位置より前の時 */
		/*	*tgt = dwk.pot-dttop;	/* 次行先頭が該当文字 */
			*tgt = 0xffff;			/* 該当文字なし */
			return(0);
		}
	}else{
		return(0);
	}

	/** 該当文字有りの時 **/
	if(ljflg==TRUE){
		lktch = TRUE;			/* Link有り */
		return(4);
	}
	return(1);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾀｯﾁ文字、該当ﾘﾝｸｴﾘｱ取得

	[引数]
		word	*p1		: in/out	ﾀｯﾁ開始文字/該当ﾘﾝｸ開始文字ｵﾌｾｯﾄ
		word	*p2		: in/out	ﾀｯﾁ終了文字/該当ﾘﾝｸ開始文字ｵﾌｾｯﾄ
		byte	ln		: in		ﾀｯﾁ文字行位置（0 ～ D_LNC-1）

	[戻り値]
		TRUE	: 該当ﾘﾝｸあり
		HALF	: 該当ｼﾞｬﾝﾌﾟあり
		FALSE	: 該当ﾘﾝｸ･ｼﾞｬﾝﾌﾟなし

	[処理内容]
		ﾀｯﾁした画面上の文字にﾘﾝｸ指定されているか判断する。
		ﾒｲｸ時は「*sp=*ep」であること！
******************************************************************************/
bool GetTchLink(word *p1, word *p2, byte ln)
/*TAIL*/
{
	byte		cd,cdbk;
	int			i;
	byte far	*tgt;
	int			len;
	byte far	*lend;

	if((*p1!=0xffff)&&(*p2!=0xffff)){			/* ﾀｯﾁ該当文字あり？ */

		if(lktch==TRUE){			/* ﾘﾝｸあり？ */

			/* ﾘﾝｸ開始位置をｻｰﾁ */
			len = TT_LEN*6;
			tgt	= lnkep-4-len;
			if(tgt<dttop){
				tgt = dttop;
				len = lnkep-dttop;
			}

			lend = 0;
			for(i=0;i<len;i++){
				cd = JdgContCode(&tgt);
				switch(cd){

					case CD_END:
						return(FALSE);		/* Fale Sfae */

					case CD_CHA:			/* 文字ｺｰﾄﾞ「00h～7Fh」 */
					case CD_OVCHA:			/* 1ﾊﾞｲﾄｺｰﾄﾞ指定(0x80以上)「@\x??」 */
						tgt++;
						break;

					case CD_GPDEF:			/* 画像指定「@\g????」 */
						tgt += 2;
						break;

					case CD_LKDEF:			/* ﾘﾝｸ指定「@\l+文字列長(1byte)」 */
					case CD_JPDEF:			/* ｼﾞｬﾝﾌﾟ指定「@\j+文字列長(1byte)」 */
						tgt ++;
						lnksp = tgt;		/* ﾘﾝｸ文字列開始ｱﾄﾞﾚｽ(仮定) */
						lend = *(tgt-1)+tgt;	/* ﾘﾝｸ終了候補設定 */
						cdbk = cd;
						break;

					case CD_FNT57:
					case CD_FNTPN:
					case CD_FNTPB:
						if(lend!=0)
							lend +=5;
						break;

					default:
				/*	case CD_TITLE:
				/*	case CD_SUBT:
				/*	case CD_LINK:
				/*	case CD_RTN:
				*/
						break;

				}
				if(lend!=0){				/* ﾘﾝｸ終了候補が設定されている時 */
					if(lend==lnkep){			/* ﾘﾝｸ終了位置と一致したら... */
						*p1 = lnksp-dttop;		/* 反転文字列開始ｵﾌｾｯﾄ */
						*p2 = lnkep-dttop;		/* 反転文字列終了ｵﾌｾｯﾄ */
						if(cdbk==CD_JPDEF)
							return(HALF);		/* ｼﾞｬﾝﾌﾟの時 */
						return(TRUE);			/* ﾘﾝｸの時 */
					}
				}
			}
		}
	}
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾀｯﾁされたﾘﾝｸ文字のｼﾞｬﾝﾌﾟ先を求める

	[引数]
		bool	lj		: in	HALF : ｼﾞｬﾝﾌﾟ文字がﾀｯﾁされた時
								TRUE : ﾘﾝｸ文字がﾀｯﾁされた時

	[戻り値]
		0	: ｼﾞｬﾝﾌﾟ不可
		1	: ﾀｲﾄﾙｲﾝﾃﾞｯｸｽへ（ｼﾞｬﾝﾌﾟ）
		2	: ﾘﾝｸｲﾝﾃﾞｯｸｽへ（ﾘﾝｸ）
	[処理内容]
******************************************************************************/
byte GetLinkIndex(byte lj)
/*TAIL*/
{
	byte		ityp;
	int			len;
	byte		srcwd[TT_LEN+1];
	byte far	*tgt;

	/* ｻｰﾁ文字列取得 */
	len = sel_ep-sel_sp;
	tgt = dttop+sel_sp;
	SelCharacter(srcwd,&tgt,len);			/* 文字ｺｰﾄﾞを抽出 */
	sdp[idxsp].pos = DicDataScr.pos;		/* 現在行位置退避 */

	if(lj==TRUE){			/* Linkの時 */
		ityp = 1;			/* LinkIndex からｻｰﾁ */
	}else{					/* Jumpの時 */
		if(idxsp>=DCTSPMAX-1)
			return(0);		/* 最大Jump回数ｵｰﾊﾞｰ */
		idxsp ++;			/* ｲﾝﾃﾞｯｸｽｽﾀｯｸﾎﾟｲﾝﾀｰ更新 */
		ityp =0;			/* TitleIndex からｻｰﾁ */
	}
	DicIniSrc(&lnkdp.num,srcwd,strlen(srcwd),ityp,TRUE);
									/* ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰｻｰﾁ */
	GetIndex(&lnkdp,ityp);			/* ｲﾝﾃﾞｯｸｽｱﾄﾞﾚｽ取得 */
	lnkdp.pos = 0;					/* 先頭行から表示 */
	if(ityp==0){					/* Jumpの時 */
		sdp[idxsp].num = lnkdp.num;
		sdp[idxsp].flp = lnkdp.flp;
		sdp[idxsp].ofs = lnkdp.ofs;
		sdp[idxsp].pos = lnkdp.pos;
	}

	ityp ++;
	return(ityp);
}



/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘﾝｸﾃﾞｰﾀ表示

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void DicLinkShowDsp(void)
/*TAIL*/
{
	TCHSTS		tsts;
	DSPCT		dct;				/* 表示制御用ﾊﾟﾗﾒｰﾀ */
	byte		amsk;
	byte		st = 2;

	LibOpenWindow(1,72,158,87);		/* ｳｲﾝﾄﾞｳ open */

	/*** ﾀｯﾁｴﾘｱ設定 ***/
	LibTchStackPush( NULL );
	LibTchStackPush(TchLinkShow);		/* ﾘﾝｸﾃﾞｰﾀ表示中ﾀｯﾁｴﾘｱ */
	LibTchStackPush(TchActionKey);		/* ｱｸｼｮﾝｷｰ  ﾀｯﾁﾃｰﾌﾞﾙ */
	LibTchStackPush( TchHardIcon );		/* ﾊｰﾄﾞｱｲｺﾝ */
/*	LibTchStackPush( TchModeIcon );		/* Pop Up Tools */

	/*** ｽｸﾛｰﾙﾊﾞｰ初期設定 ***/
	LinkDataScr.x		= W_EDX+3;			/* ｽｸﾛｰﾙﾊﾞｰ位置(X) */
	LinkDataScr.y		= W_STY+1;			/* ｽｸﾛｰﾙﾊﾞｰ位置(Y) */
	LinkDataScr.size	= W_EDY-W_STY-3;	/* ｽｸﾛｰﾙﾊﾞｰ高さ */
	LinkDataScr.dsp		= W_LNC;			/* 表示件数     */

	LinkShowBk();		/* 背景表示 */

	while(st>0){

		if(st>1){
			LinkShowData();					/* 表示ﾃﾞｰﾀｾｯﾄ */
			dct = lctrl;					/* 画面先頭ﾊﾟﾗﾒｰﾀ戻し */

			/* ｽｸﾛｰﾙﾊﾞｰ上下矢印網掛け処理 */
			DLibScrollArrowPrint(LinkDataScr,SCR_NO_MASK);
			amsk = DataArrowMask(&LinkDataScr);
			DLibScrollArrowPrint(LinkDataScr,amsk);
			st = 1;
		}
		LibPutDisp();					/* 画面更新 */
		LibTchWait( &tsts );			/* ﾀｯﾁ待ち */

		switch(tsts.obj){

			case OBJ_LPSW_UP:		/* ｱｸｼｮﾝｷｰ Up */
				if(ChkScrlDwn(&LinkDataScr)==TRUE){
					LinkDataScr.pos --;
					st = 2;				/* ﾃﾞｰﾀ再表示 */
				}else{
					LibRepOff();		/* ﾘﾋﾟｰﾄ Off */
				}
				break;

			case OBJ_LPSW_DOWN:		/* ｱｸｼｮﾝｷｰ Down */
				if(ChkScrlUp(&LinkDataScr)==TRUE){
					LinkDataScr.pos ++;
					st = 2;				/* ﾃﾞｰﾀ再表示 */
				}else{
					LibRepOff();		/* ﾘﾋﾟｰﾄ Off */
				}
				break;

			case OBJ_LPSW_PUSH:		/* ｱｸｼｮﾝｷｰ Push */
				st = 0;					/* Loop End */
				break;

			case OBJ_SCR_BAR:			/* ScrollBar */
				if(DicShowScBar(&tsts, &LinkDataScr)!=0)
					st = 2;				/* ﾃﾞｰﾀ再表示 */
				break;

	/*		case OBJ_HIC_MBAR:		/* ﾒﾆｭｰﾊﾞｰﾊｰﾄﾞｱｲｺﾝ */
	/*			DicPdwnSet();				/* ﾌﾟﾙﾀﾞｳﾝﾒﾆｭｰ表示設定 */
	/*			if(DicPdwnFnc(&tp)==TRUE)	/* ﾌﾟﾙﾀﾞｳﾝ処理 */
	/*				st = 0;
	/*			break;
	*/
			case OBJ_AR_LWOUT:			/* ｳｲﾝﾄﾞｳ外 */
			case OBJ_HIC_ESC:			/* ｢ESC｣ﾊｰﾄﾞｱｲｺﾝ */
				st = 0;					/* Loop End */
				break;
		}
	}
	LibTchRelease();			/* ｢NULL｣まで POP */
	LibCloseWindow();
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示背景描画

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void LinkShowBk(void)
/*TAIL*/
{
	byte far	*tgt;
	long		vol;
	DSPCT		dctwk;

	LibBox(2,73,155,84,1);				/* ｳｲﾝﾄﾞｳ枠 */
	LibLine(157,74,1,84,1);				/* ｳｲﾝﾄﾞｳ枠(右影) */
	LibLine(3,157,155,1,1);				/* ｳｲﾝﾄﾞｳ枠(下影) */
	LibLine(144,74,1,82,1);				/* 中線 */

	sel_sp = sel_ep = 0xffff;			/* 反転文字ｸﾘｱ */
	jprv = FALSE;						/* ﾘﾝｸﾀｯﾁ反転中ﾌﾗｸﾞ初期化 */

	if(DicDataRead(&lnkdp,&tgt)==FALSE){
		DicStatus = ST_MODEINI;			/* Fale Safe */
		return;
	}

	dttop = tgt-3;						/* ﾘﾝｸﾃﾞｰﾀ開始ｱﾄﾞﾚｽ */

	/*** ｽｸﾛｰﾙﾊﾞｰ初期設定 ***/
	dctwk.x		= W_STX;
	dctwk.sx	= W_STX;
	dctwk.sy	= W_STY;
	dctwk.ex	= W_EDX;
	dctwk.ey	= W_EDY;
	dctwk.ity	= D_ITY;
	vol = GetDicDspL(dttop,&dctwk);		/* 全体縦幅取得(行数) */
	LinkDataScr.vol	= vol;				/* ｽｸﾛｰﾙﾊﾞｰ全体量 */
	LinkDataScr.pos	= lnkdp.pos;		/* ｽｸﾛｰﾙﾊﾞｰ初期位置 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘﾝｸﾃﾞｰﾀ表示

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void LinkShowData(void)
/*TAIL*/
{
	int			ltc;				/* ﾃﾞｰﾀ表示開始行位置 */
	DSPCT		dct;				/* 表示制御用ﾊﾟﾗﾒｰﾀ */

	LibGdsClr(W_STX-W_SFTX*2,W_STY,W_EDX-1,W_EDY-1);	/* 枠内画面消去 */

	/*** 表示初期位置設定 ***/
	dct.sx		= W_STX;
	dct.sy		= W_STY;
	dct.ex		= W_EDX;
	dct.ey		= W_EDY;
	dct.lnc		= W_LNC;
	dct.fnt		= IB_PFONT1;
	dct.ity		= D_ITY;
	dct.pot 	= dttop;				/* ﾊﾞｯﾌｧ先頭 */
	dct.lkpt	= dttop;				/* ﾘﾝｸ無し */
	dct.jpf		= FALSE;				/* ｼﾞｬﾝﾌﾟ無し */
	ltc = LinkDataScr.pos;
	DicDspTopSrc(&dct, ltc);			/* 表示開始位置ｻｰﾁ */

	lctrl = dct;						/* 画面先頭ﾊﾟﾗﾒｰﾀ退避 */
/*	lkpsp = 0;							/* ﾘﾝｸなし */

	DicDltpClear(&dct);						/* 行ﾊﾟﾗﾒｰﾀ初期化 */
	DicTxtDsp(&dct);					/* 指定行位置から画面表示 */
	DLibScrollPrint(LinkDataScr);		/* ｽｸﾛｰﾙﾊﾞｰ表示 */

	/** BIOSﾊﾞｸﾞ対策 **/
	LibGdsClr(W_EDX,W_STY,W_EDX+2,W_EDY-1);	/* ｽｸﾛｰﾙﾊﾞｰ左側画面消去 */
	LibLine(144,74,1,82,1);				/* 中線 */
}
