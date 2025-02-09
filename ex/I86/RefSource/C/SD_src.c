/******************************************************************************
	[ﾀｲﾄﾙ]
		Referencer

	[機種]
		通信電子手帳(海外)

	[概要]
		Referencer ｻｰﾁ入力

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


TXTP		srctp;
bool		srcflg;
byte		srcbf[SRC_LEN+1];		/* ｻｰﾁ入力用ﾃｷｽﾄﾊﾞｯﾌｧ */
TCHTBL		SrcTch[3];				/* ﾃｷｽﾄﾀｯﾁｴﾘｱﾃｰﾌﾞﾙ */
int			srclen;					/* ｻｰﾁ文字列長 */

/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｻｰﾁ入力時､背景表示

	[戻り値]
	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_IINI

	[処理内容]
******************************************************************************/
void DicSrcInit(void)
/*TAIL*/
{
	T_SCR_POS	srcscr;

	LibTchStackClr();					/* ﾀｯﾁｴﾘｱ初期化 */
	LibTchInit();
	TchComSet();

/***** ｢General｣ｻｰﾁ仕様削除 **************
/*	LibTchStackPush(TchSrcTyp);			/* ｻｰﾁﾀｲﾌﾟ選択 ﾀｯﾁﾃｰﾌﾞﾙ */

	LibTchStackPush(TchSrcTopKey);		/* ｢Clr/DTM/Cal/Exe｣ｱｲｺﾝ ﾀｯﾁﾃｰﾌﾞﾙ */
	LibTchStackPush(TchDBSel);			/* 辞書DB選択ﾎﾞﾀﾝﾀｯﾁﾃｰﾌﾞﾙ */
	LibTchStackPush(TchActionKey);		/* ｱｸｼｮﾝｷｰ  ﾀｯﾁﾃｰﾌﾞﾙ */

	SrcTxtInit(&srctp,&srcscr,SrcTch);	/* ｻｰﾁ文字入力初期化 */
	LibTxtInit(&srctp);					/* ﾃｷｽﾄ入力初期化 */
	LibTxtTchSet(&srctp);				/* ﾃｷｽﾄﾀｯﾁｴﾘｱ PUSH */

	DicStatus	= ST_ILOOP;				/* ｻｰﾁ文字列入力へ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示中、ｻｰﾁ文字入力

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void SrcTxtInit(TXTP *tp, T_SCR_POS *scbar, TCHTBL *tcht)
/*TAIL*/
{
 /** ﾃｷｽﾄ入力設定 **/
	tp->txbf	= srcbf;		/* ﾃｷｽﾄﾊﾞｯﾌｧ指定 */
	tp->st_x	= SI_ST_X;
	tp->ed_x	= SI_ED_X;
	tp->st_y	= SI_ST_Y;
	tp->it_y	= SI_IT_Y;
	tp->MAXGYO	= SI_MAXG;
	tp->font	= IB_PFONT1;
	tp->csen	= TRUE;			/* ｶｰｿﾙ表示許可(ｷｰﾜｰﾄﾞ登録禁止) */
	tp->rtnen	= 0x02;			/* 改行入力表示禁止 */
	tp->maxmj	= SRC_LEN;		/* 最大入力可能文字数 */
	tp->txtobj	= OBJ_TXTTCH;	/* ﾃｷｽﾄｴﾘｱﾀｯﾁ時ｵﾌﾞｼﾞｪｸﾄ  */
	tp->sbrobj	= OBJ_SCR_BAR;	/* ｽｸﾛｰﾙﾊﾞｰﾀｯﾁ時ｵﾌﾞｼﾞｪｸﾄ */
	tp->tchtb	= tcht;			/* ﾀｯﾁﾃｰﾌﾞﾙﾎﾟｲﾝﾀ */
	tp->gdcmt	= srcgid;	/* ｶﾞｲﾀﾞﾝｽｺﾒﾝﾄﾃｰﾌﾞﾙ */
	tp->s_pos	= scbar;		/* ｽｸﾛｰﾙﾊﾞｰ位置情報ﾎﾟｲﾝﾀ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｻｰﾁ文字列入力

	[引数]
	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_ILOOP

	[処理内容]
******************************************************************************/
void DicSrcInput()
/*TAIL*/
{
	byte		kycd;
	TCHSTS		tsts;

/*	LibOpenWindow(0,0,160,160);				/* 全画面ｳｲﾝﾄﾞｳｵｰﾌﾟﾝ */
	DicSrcInpBk();							/* 背景表示 */
	LibDispKey();							/* 初回ｿﾌﾄｷｰﾎﾞｰﾄﾞ表示 */

	if(DBfc<=0){
		LibWinIcnMsg(ICON_NONE,501,2);		/* "DBﾌｧｲﾙが見つかりません！" */
		LibJumpMenu();						/* MENUへ */
	}

	while(DicStatus==ST_ILOOP){

		DicSrcDsp();						/* ｻｰﾁ文字列入力中表示 */
		kycd = LibGetKeyM(&tsts);			/* ｿﾌﾄｷｰ待ち */

		if(kycd==KEY_NONE){					/* ｷｰﾎﾞｰﾄﾞ以外のﾀｯﾁ時 */
			switch(tsts.obj){

				case OBJ_IC_DBSEL:		/* DB Select */
					if(DicDBSelWin(&tsts,TRUE)==TRUE)
						DicStatus = ST_IINI;	/* ｻｰﾁ語入力初期化 */
					break;

	/***** ｢General｣ｻｰﾁ仕様削除 **************
	/*			case OBJ_IC_ISRC:			/* ｢Initial｣ｱｲｺﾝﾀｯﾁの時 */
	/*				srcflg = FALSE;
	/*				break;
	/*
	/*			case OBJ_IC_GSRC:			/* ｢General｣ｱｲｺﾝﾀｯﾁの時 */
	/*				srcflg = HALF;
	/*				break;
	*/

				case OBJ_LPSW_UP:			/* ｱｸｼｮﾝｷｰ Up */
				case OBJ_LPSW_DOWN:			/* ｱｸｼｮﾝｷｰ Down */
					if(DicDBSelWin(&tsts,FALSE)==TRUE)
						DicStatus = ST_IINI;	/* ｻｰﾁ語入力初期化 */
					break;

				case OBJ_IC_EXEKEY:			/* ｢Exe｣ｱｲｺﾝﾀｯﾁの時 */
					if(LibIconClick(&TicnExeKey,&tsts)!=TRUE){
						break;				/* 以下､ｱｸｼｮﾝｷｰPUSHと同一 */
					}
				case OBJ_LPSW_PUSH:			/* ｱｸｼｮﾝｷｰ Push */
					if(srcbf[0]!=0){		/* ﾃｷｽﾄが空白でなければ */
						if(DicSrcExe()==TRUE){	/* 検索実行 */
							DicStatus	= ST_LTCHINI;		/* ﾘｽﾄ表示へ */
						}else{			/* ｾﾞﾈﾗﾙｻｰﾁで未発見時 */
							LibWinIcnMsg(ICON_BIKKURI,323, 1);
										/* ｢Not_Found!｣ 1Sec表示 */
						}
					}else{
						DicStatus	= ST_LFILEINI;		/* ﾘｽﾄ表示へ */
					}
					break;

				case OBJ_IC_CALKEY:			/* ｢Cal｣ｱｲｺﾝﾀｯﾁの時 */
					if(LibIconClick(&TicnCalKey,&tsts)==TRUE){
						LibCalWin(ON);
					}
					break;

				case OBJ_IC_DTMKEY:		/* 「現在時刻」ｱｲｺﾝﾀｯﾁの時 */
					if(LibIconClick(&TicnDTMKey,&tsts)==TRUE){
						srctp.txtst = TXTDYTIM;
					}
					break;

		/*		case OBJ_HIC_ESC:		/* ESC ｱｲｺﾝﾀｯﾁ時 */
		/*			srcbf[0] = NULL;		/* ﾃｷｽﾄﾊﾞｯﾌｧ初期化 */
		/*			LibTxtInit(&srctp);		/* ﾃｷｽﾄ入力初期化 */
		/*			break;
		*/

				case OBJ_IC_CLRKEY:			/* ｢CLR/LIST｣ｱｲｺﾝﾀｯﾁの時 */
					if(LibIconClick(&TicnClrKey,&tsts)==TRUE){
						if(srcbf[0]!=NULL){		/* ｢CLR｣ｱｲｺﾝの時 */
							srcbf[0] = NULL;	/* ﾃｷｽﾄﾊﾞｯﾌｧ初期化 */
							LibTxtInit(&srctp);	/* ﾃｷｽﾄ入力初期化 */
						}
					}
					break;

				case OBJ_HIC_MBAR:			/* ﾒﾆｭｰﾊﾞｰﾊｰﾄﾞｱｲｺﾝ */
					DicPdwnSet();				/* ﾌﾟﾙﾀﾞｳﾝﾒﾆｭｰ表示設定 */
					if(DicPdwnFnc(&srctp)==TRUE)	/* ﾌﾟﾙﾀﾞｳﾝ処理 */
						return;
					break;
			}
		}

		if(DicStatus==ST_ILOOP)
			LibTxtInp(kycd,&tsts,&srctp);		/* ﾃｷｽﾄ入力ﾒｲﾝ */
	}

/*	LibTchRelease();				/* ｢NULL｣まで POP */
/*	LibCloseWindow();				/* ｳｲﾝﾄﾞｳｸﾛｰｽﾞ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｻｰﾁ入力時､背景表示

	[処理内容]
******************************************************************************/
void DicSrcInpBk(void)
/*TAIL*/
{
	byte i;

	LibClrDisp();						/* 画面消去 */
	LibPutFarData( 0, 0, 96);			/* 虫眼鏡ｱｲｺﾝ表示 */

	LibPutFarData(14, 0,132);						/* ｢Clr｣ｱｲｺﾝ表示(枠) */
	LibPutMessageCenter(110, 14,42,2,IB_PFONT1);	/* ｢Clr｣ｱｲｺﾝ表示(ｺﾒﾝﾄ) */
	LibPutFarData(71, 0,133);						/* ｢Exe｣ｱｲｺﾝ表示(枠) */
	LibPutMessageCenter(111,99,127,2,IB_PFONT1);	/* ｢Exe｣ｱｲｺﾝ表示(ｺﾒﾝﾄ) */
	LibModeIconDsp();								/* ｢Tool｣ｱｲｺﾝ表示(枠) */

	LibLine(1, 13, 158, 1, 1);			/* 全体枠線(上) */
	LibLine(0, 14, 1, 73, 1);			/* 全体枠線(左) */
	LibLine(159, 14, 1, 73, 1);			/* 全体枠線(右) */
	LibLine(1, 87, 158, 1, 1);			/* 全体枠線(下) */

	LibLine(0, 29, 159, 1, 1);			/* 全体枠線 */
	LibLine(0, 67, 159, 1, 1);			/* 全体枠線 */
	LibPutMessage(16,3,15,IB_PFONT2);	/* ｢Search｣ｺﾒﾝﾄ表示 */
	
	for (i=31;i<66;){
		LibGdsLineMesh(3,i,157,i);
		i=i+2;
	}
	for (i=32;i<65;){
		LibGdsLineMesh(2,i,156,i);
		i=i+2;
	}
	LibClrBox(24,38,111,22);
	LibBox(28,42,115-13+1,43-30+1,1);	/* 文字入力枠 */

	LibLine(26,40,107,1,1);				/* 文字入力枠(上) */
	LibLine(26,41,106,1,1);				/* 文字入力枠(上) */
	LibLine(27,42,1,15,1);				/* 文字入力枠(左) */
	LibLine(26,42,1,16,1);				/* 文字入力枠(左) */
	
	LibLine(27,57,106,1,1);
	LibLine(132,40,1,18,1);
	LibDotOn(131,56);

	/***** ｢General｣ｻｰﾁ仕様削除 **************
	/*	LibPutMessage(31,37,73,IB_PFONT1);	/* ｢ALL｣ｺﾒﾝﾄ表示 */
	/*	LibPutMessage(66,97,73,IB_PFONT1);	/* ｢Initial｣ｺﾒﾝﾄ表示 */

	DicDBSelWinBk();					/* DBﾌｧｲﾙ選択枠背景 */
}

/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｻｰﾁ入力中表示

	[処理内容]
******************************************************************************/
void DicSrcDsp(void)
/*TAIL*/
{

	/***** ｢General｣ｻｰﾁ仕様削除 **************
	/*
	/*	if(srcflg==FALSE){				/*** ｲﾆｼｬﾙｻｰﾁの時 ***/
	/*		LibPutFarData(26,73,42);		/* 白丸ｱｲｺﾝ表示 */
	/*		LibPutFarData(86,73,43);		/* 黒丸ｱｲｺﾝ表示 */
	/*
	/*	}else{							/*** ｾﾞﾈﾗﾙｻｰﾁの時 ***/
	/*		LibPutFarData(26,73,43);		/* 黒丸ｱｲｺﾝ表示 */
	/*		LibPutFarData(86,73,42);		/* 白丸ｱｲｺﾝ表示 */
	/*	}
	*/

	LibTxtDsp(&srctp);					/* ﾃｷｽﾄ入力中表示 */
	LibPutDisp();						/* 表示更新 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		文字列ｻｰﾁ処理

	[戻り値]
		TRUE	: 該当ﾃﾞｰﾀ発見時
		FALSE	: 該当ﾃﾞｰﾀ未発見時(ｾﾞﾈﾗﾙｻｰﾁ時のみ)

	[処理内容]
******************************************************************************/
bool DicSrcExe(void)
/*TAIL*/
{
	long	tgt;

	LibWinIcnMsg(ICON_COFFEE,337,0);	/* Searching...    */
	LibPutDisp();						/* 表示に反映        */
	LibCloseWindow();					/* LibWinIcnMsg(0)分 */

	srclen = strlen(srcbf);			/* ｻｰﾁ文字列長 */

	/*** ｲﾆｼｬﾙｻｰﾁの時 ***/
	if(srcflg==FALSE){
		DicIniSrc(&tgt,srcbf,srclen,0,FALSE);
		DicLstScr.pos = tgt;

	/***** ｢General｣ｻｰﾁ仕様削除 **************
	/*
	/*	/*** ｾﾞﾈﾗﾙｻｰﾁの時 ***/
	/*	}else{
	/*		if(DicGenSrc(&tgt,srclen)==TRUE){
	/*			srcflg = TRUE;
	/*			lip[0].num = tgt;
	/*			DicLstScr.pos = 0;
	/*		}else{
	/*			return(FALSE);
	/*		}
	*/

	}
	lcp = 0;
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		小→大文字ｱﾙﾌｧﾍﾞｯﾄ変換

	[引数]
		byte	*d		: out	変換後文字列
		byte	*s		: in	変換元文字列

	[処理内容]
******************************************************************************/
void ChrS2L(byte far *d, byte far *s)
/*TAIL*/
{
	int		i;

	for(i=0;;i++){
		d[i] = s[i];
		if(d[i]==0x0d){					/* 改行発見時 */
			d[i] = 0;					/* 終端に変換 */
		}else if('a'<=d[i] && d[i]<='z'){	/* 小文字発見時 */
			d[i] -= 'a'-'A';			/* 大文字に変換 */
		}
		if(d[i]==NULL)					/* 終端発見時 */
			break;
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｲﾆｼｬﾙｻｰﾁ処理

	[引数]
		long	*tgt		: out	ｻｰﾁ該当ﾃﾞｰﾀ番号
		byte	*buf		: in	ｻｰﾁ文字列ﾊﾞｯﾌｧ
		int		len			: in	ｻｰﾁ文字列長
		byte	type		: in	対象ｲﾝﾃﾞｯｸｽ種別(0:ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ/1:ﾘﾝｸｲﾝﾃﾞｯｸｽ)
		bool	ls			: in	ﾘﾝｸ(ｼﾞｬﾝﾌﾟ)先ｻｰﾁｽｲｯﾁ

	[戻り値]
		0	: ﾀｰｹﾞｯﾄ番号＝ｻｰﾁ位置（ｻｰﾁすべき位置を発見）
		1	: ﾀｰｹﾞｯﾄ番号＜ｻｰﾁ位置（ｻｰﾁすべき位置はもっと後ろ）
		2	: ｻｰﾁ位置＜ﾀｰｹﾞｯﾄ番号（ｻｰﾁすべき位置はもっと前）

	[処理内容]
******************************************************************************/
byte DicIniSrc(long *tgt, byte *buf, int len, byte type, bool ls)
/*TAIL*/
{
	long	stn;			/* ｻｰﾁ範囲開始 */
	long	ttn,ttnbk;		/* ｻｰﾁﾃﾞｰﾀ数 */
	long	dvn;			/* 分割位置 */
	byte	ret = 0;
	byte	rr = 0;
	byte	tmp[TT_LEN+1];

	ChrS2L(tmp, buf);				/* ｻｰﾁ文字列､小→大文字化 */

	stn = 0;						/* ﾃﾞｰﾀ先頭 */
	if(type==0)
		ttn = tidxc;				/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ総数 */
	else
		ttn = lidxc;				/* ﾘﾝｸｲﾝﾃﾞｯｸｽ総数 */
	ttnbk = ttn;

	while(1){
		dvn = stn + ttn/2;		/* ﾀｰｹﾞｯﾄは対象件数の二分割位置 */
		ret = JdgStrHighLow(dvn,tmp,len,type,TRUE);	/* 上下判断 */

		if(ttn<=1)		/* 分割不可 */
			break;

		switch(ret){

			/*** ﾀｰｹﾞｯﾄ文字列＝ｻｰﾁ文字列 ***/
			case 0:
				while(rr==0){		/* 大小文字同一の先頭をｻｰﾁ */
					if(dvn==0)
						break;
					rr = JdgStrHighLow(dvn-1,tmp,len,type,TRUE);
									/* 一つ前のﾃﾞｰﾀをﾁｪｯｸ */
					if(rr!=0)
						break;
					dvn --;	
				}
				if(ls==TRUE){		/* ﾘﾝｸ先は完全一致する物をｻｰﾁ */
					while(dvn<ttnbk-1){
						rr = JdgStrHighLow(dvn,buf,len,type,FALSE);
						if(rr==0)
							break;
						dvn ++;
					}
				}
				goto LOOP_END;		/* LOOP 終了 */
				break;

			/*** ﾀｰｹﾞｯﾄ文字列＜ｻｰﾁ文字列 ***/
			case 1:
				ttn = ttn - (dvn - stn);
				stn = dvn;
				break;

			/*** ｻｰﾁ文字列＜ﾀｰｹﾞｯﾄ文字列 ***/
		/*	case 2:	*/
			default:
				ttn = dvn - stn;
				break;
		}
	}

LOOP_END:
	if(ret==2){				/* ｻｰﾁ文字列＜ﾀｰｹﾞｯﾄ文字列 */
		*tgt = dvn-1;
		if(*tgt<0)
			*tgt = 0;
	}else{
		*tgt = dvn;
	}
	return(ret);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		文字列上下判断処理

	[引数]
		long	*tgt		: in	ﾀｰｹﾞｯﾄﾃﾞｰﾀ番号
		byte	*buf		: in	ｻｰﾁ対象文字列
		int		len			: in	ｻｰﾁ文字列長
		byte	type		: in	対象ｲﾝﾃﾞｯｸｽ種別(0:ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ/1:ﾘﾝｸｲﾝﾃﾞｯｸｽ)
		bool	ls			: in	大小文字同一視ﾌﾗｸﾞ

	[戻り値]
		0	: ﾀｰｹﾞｯﾄ番号＝ｻｰﾁ位置（ｻｰﾁすべき位置を発見）
		1	: ﾀｰｹﾞｯﾄ番号＜ｻｰﾁ位置（ｻｰﾁすべき位置はもっと後ろ）
		2	: ｻｰﾁ位置＜ﾀｰｹﾞｯﾄ番号（ｻｰﾁすべき位置はもっと前）

	[処理内容]
******************************************************************************/
byte JdgStrHighLow(long num, byte *buf, int len, byte type, bool lss)
/*TAIL*/
{
	LSTIDX		lidx;
	byte far	*tgt;
	int			i;
	byte		ret = 0;
	byte		wrk[TT_LEN+1];
	byte		tmp[TT_LEN+1];

	lidx.num = num;

	GetIndex(&lidx,type);		/* ﾀｰｹﾞｯﾄ文字列ﾎﾟｲﾝﾀｰ取得 */
	DicDataRead(&lidx,&tgt);	/* ﾀｰｹﾞｯﾄ文字列ﾃﾞｰﾀ取得 */
	if(type==1)					/* ﾘﾝｸｲﾝﾃﾞｯｸｽをｻｰﾁする時 */
		tgt += 1;				/* 1ﾊﾞｲﾄ(文字列長)ｽｷｯﾌﾟ */
	SelCharacter(wrk,&tgt,len);	/* 文字ｺｰﾄﾞを抽出 */

	if(lss==TRUE)
		ChrS2L(tmp, wrk);		/* ﾀｰｹﾞｯﾄ小→大文字化 */
	else
		memcpy(tmp, wrk, len+1);

	for(i=0;i<len;i++){
		if( tmp[i] < buf[i] ){
			ret = 1;
			break;
		}else if( tmp[i] > buf[i] ){
			ret = 2;
			break;
		}
	}

	return(ret);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		文字ｺｰﾄﾞ抽出

	[引数]
		byte		*d		: out	文字ｺｰﾄﾞ抽出先
		byte far	*s		: in	ﾀｰｹﾞｯﾄﾃﾞｰﾀ
		int			len		: in	

	[戻り値]
	[処理内容]
******************************************************************************/
void SelCharacter(byte *dbuf, byte far **sbuf, int len)
/*TAIL*/
{
	byte	ccd;
	int		i;

	for(i=0;i<len;i++){

		ccd = JdgContCode(sbuf);			/* 制御ｺｰﾄﾞ判断 */

		switch(ccd){

			case CD_CHA:			/* 文字ｺｰﾄﾞ「00h～7Fh(0Dhは除く)」 */
			case CD_OVCHA:			/* 1ﾊﾞｲﾄｺｰﾄﾞ指定(0x80以上)「@\x??」 */
				dbuf[i] = **sbuf;
				(*sbuf) ++;
				break;

			case CD_FNT57:		/* 5x7ﾌｫﾝﾄ指定        「@\fNM」 */
			case CD_FNTPN:		/* ﾌﾟﾛﾎﾟｰｼｮﾅﾙﾌｫﾝﾄ指定 「@\fPN」 */
			case CD_FNTPB:		/* 太文字ﾌｫﾝﾄ指定     「@\fPB」 */
				i--;
				break;

			default:				/* fale safe */
				goto LOOPEND;
				break;
		}
	}
LOOPEND:
	dbuf[i] = NULL;	/* 終端付加 */
}


#if 0
/*********** ↓↓↓ｾﾞﾈﾗﾙｻｰﾁ仕様削除↓↓↓ ***********/

/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｾﾞﾈﾗﾙｻｰﾁ処理

	[引数]
		long	*tgt		: out	ｻｰﾁ該当ﾃﾞｰﾀ番号

	[戻り値]
		TRUE	: 該当ﾃﾞｰﾀ発見時
		FALSE	: 該当ﾃﾞｰﾀ未発見時

	[処理内容]
******************************************************************************/
bool DicGenSrc(long *tgt, int len)
/*TAIL*/
{
	LSTIDX		lidx;
	byte		tmp[TT_LEN+1];
	byte far	*dt;
	long		i;

	lidx.num = 0;
	if(GetIndex(&lidx,0)==FALSE)			/* 先頭ﾀｲﾄﾙ文字列ﾎﾟｲﾝﾀｰ取得 */
		return(FALSE);
	if(DicDataRead(&lidx,&dt)==FALSE)		/* 先頭ﾀｲﾄﾙ文字列ﾃﾞｰﾀ取得 */
		return(FALSE);
	ChrS2L(tmp, dt);						/* 先頭ﾀｲﾄﾙ小→大文字化 */

	if(JdgStrMach(tmp,len)==FALSE){				/* 先頭ﾃﾞｰﾀが不一致の時 */
		if(NxtGenSrc(&lidx,len)==FALSE){		/* 次一致ﾃﾞｰﾀｻｰﾁ */
			return(FALSE);					/* 一致ﾃﾞｰﾀ無し */
		}
	}

	*tgt = lidx.num;

	/*** 全該当ﾃﾞｰﾀ件数検出ﾙｰﾌﾟ ***/
	for(i=1; i<tidxc; i++){
		if(NxtGenSrc(&lidx,len)==FALSE)		/* 次一致ﾃﾞｰﾀｻｰﾁ */
			break;
	}
	DicLstScr.vol = i;					/* ｽｸﾛｰﾙﾊﾞｰ全体 */

	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		文字列一致判断処理

	[引数]
		byte	*tgt		: in	比較対象文字列

	[戻り値]
		TRUE	: 一致
		FALSE	: 不一致

	[処理内容]
******************************************************************************/
bool JdgStrMach(byte *tgt, int len)
/*TAIL*/
{
	int		i,j;

	for(j=0;j<TT_LEN;j++){
		if(tgt[j]==srcbf[0]){			/* 先頭文字が一致の時 */

			for(i=1;i<len;i++){		/* ｻｰﾁ文字列と一致? */
				if(tgt[j+i]!=srcbf[i])
					break;
			}
			if(i==len)
				return(TRUE);			/* 一致 */
		}
	}
	return(FALSE);						/* 不一致 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		次ﾃﾞｰﾀｻｰﾁ処理(ｾﾞﾈﾗﾙｻｰﾁ)

	[引数]
		LSTIDX	*lidx		: in	現在ﾘｽﾄｲﾝﾃﾞｯｸｽ構造体
			lidx.num					現在ｲﾝﾃﾞｯｸｽ番号
			lidx.flp					現在ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰの含まれるﾌｧｲﾙﾎﾟｲﾝﾀｰ
			lidx.ofs					現在ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰのｵﾌｾｯﾄ
		byte	*buf		: in	ｻｰﾁ文字列(ｻｰﾁﾊﾞｯﾌｧを大文字変換したもの)

	[戻り値]
		FALSE	: 該当ﾃﾞｰﾀ未発見時
		TRUE	: 該当ﾃﾞｰﾀ発見時

		LSTIDX	*lidx		: out	次ﾘｽﾄｲﾝﾃﾞｯｸｽ構造体
			lidx.num					次ｲﾝﾃﾞｯｸｽ番号
			lidx.flp					次ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰの含まれるﾌｧｲﾙﾎﾟｲﾝﾀｰ
			lidx.ofs					次ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰのｵﾌｾｯﾄ

	[処理内容]
******************************************************************************/
bool NxtGenSrc(LSTIDX *lidx, int len)
/*TAIL*/
{
	byte		tmp[TT_LEN+1];
	byte far	*dt;
	long		i;
	bool		jdg = FALSE;

	for(i=lidx->num;i<tidxc;i++){

		if(GetNxtTitleIndex(lidx)==FALSE)	/* 次ﾀｲﾄﾙｲﾝﾃﾞｯｸｽﾃﾞｰﾀ取得 */
			break;
		if(DicDataRead(lidx,&dt)==FALSE)	/* ﾀｰｹﾞｯﾄ文字列ﾃﾞｰﾀ取得 */
			break;
		ChrS2L(tmp,dt);						/* ﾀｰｹﾞｯﾄ小→大文字化 */
		if(JdgStrMach(tmp,len)==TRUE){		/* 文字列一致時 */
			jdg = TRUE;
			break;
		}
	}

	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｾﾞﾈﾗﾙｻｰﾁ処理2

	[引数]
		long	*tgt		: in	ｻｰﾁ番号（0～）
		LSTIDX	*lidx		: out	該当するﾃﾞｰﾀﾎﾟｲﾝﾀｰ

	[戻り値]
		TRUE	: 該当ﾃﾞｰﾀ発見時
		FALSE	: 該当ﾃﾞｰﾀ未発見時

	[処理内容]
		ｾﾞﾈﾗﾙｻｰﾁの一致するﾃﾞｰﾀ中、指定された順番のﾃﾞｰﾀ番号を返す
******************************************************************************/
bool GenSrc2(long tgt, LSTIDX *lidx)
/*TAIL*/
{
	byte		tmp[TT_LEN+1];
	byte far	*dt;
	long		i;

	if(tgt>=tidxc)
		return(FALSE);

	lidx->num = 0;
	if(GetIndex(lidx,0)==FALSE)				/* 先頭ﾀｲﾄﾙ文字列ﾎﾟｲﾝﾀｰ取得 */
		return(FALSE);
	if(DicDataRead(lidx,&dt)==FALSE)		/* 先頭ﾀｲﾄﾙ文字列ﾃﾞｰﾀ取得 */
		return(FALSE);
	ChrS2L(tmp, dt);						/* 先頭ﾀｲﾄﾙ小→大文字化 */

	if(JdgStrMach(tmp,srclen)==FALSE){		/* 先頭ﾃﾞｰﾀが不一致の時 */
		if(NxtGenSrc(lidx, srclen)==FALSE){	/* 次一致ﾃﾞｰﾀｻｰﾁ */
			return(FALSE);					/* 一致ﾃﾞｰﾀ無し */
		}
	}
	for(i=0; i<tgt; i++){
		if(NxtGenSrc(lidx,srclen)==FALSE)	/* 次一致ﾃﾞｰﾀｻｰﾁ */
			break;
	}
	if(i < tgt)
		return(FALSE);
	return(TRUE);
}

/*********** ↑↑↑ｾﾞﾈﾗﾙｻｰﾁ仕様削除↑↑↑ ***********/
#endif
