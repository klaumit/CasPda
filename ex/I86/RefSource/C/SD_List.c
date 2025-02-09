/******************************************************************************
	[ﾀｲﾄﾙ]
		Referencer ﾘｽﾄ表示

	[機種]
		ZX400 Referencer

	[概要]
		ﾘｽﾄ表示処理群

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

XT_SCR_POS	DicLstScr;			/* ﾘｽﾄ表示用ｽｸﾛｰﾙﾊﾞｰ */
byte		dic_en;				/* 辞書ﾃﾞｰﾀｴﾝﾄﾘｰ */
byte		dic_sben;			/* 辞書ﾃﾞｰﾀｻﾌﾞｴﾝﾄﾘｰ */
word		topfp;				/* 辞書ﾃﾞｰﾀTOPﾌｧｲﾙﾎﾟｲﾝﾀｰ */
LSTIDX		lip[L_LNC];
LSTIDX		sdp[DCTSPMAX];		/* ﾃﾞｰﾀ表示ｲﾝﾃﾞｯｸｽｽﾀｯｸｴﾘｱ */
LSTIDX		lnkdp;				/* ﾘﾝｸﾃﾞｰﾀ表示ｲﾝﾃﾞｯｸｽ */
long		tidxc;				/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ総数 */
word		ttopbk;				/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ﾌﾞﾛｯｸ) */
word		ttopof;				/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ｵﾌｾｯﾄ) */
word		gidxc;				/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ総数 */
word		gtopbk;				/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ﾌﾞﾛｯｸ) */
word		gtopof;				/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ｵﾌｾｯﾄ) */
long		lidxc;				/* ﾘﾝｸｲﾝﾃﾞｯｸｽ総数 */
word		ltopbk;				/* ﾘﾝｸｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ﾌﾞﾛｯｸ) */
word		ltopof;				/* ﾘﾝｸｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ｵﾌｾｯﾄ) */
int			lcp;				/* ﾘｽﾄ表示ｶｰｿﾙﾎﾟｲﾝﾀｰ */
bool		MesDone;			/* ﾒｯｾｰｼﾞ表示済み区分 */
bool		passed;				/* 1秒経過区分 */


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示ﾌｧｲﾙ初期化

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_LFILEINI

	[処理内容]
******************************************************************************/
void DicLstFileInit(void)
/*TAIL*/
{
	/*** ﾘｽﾄ表示ｽｸﾛｰﾙﾊﾞｰ初期設定 ***/
	DicLstScr.pos	= 0;				/* ｽｸﾛｰﾙﾊﾞｰ初期位置 */
	lcp = 0;							/* ｶｰｿﾙ初期位置 */
	DicStatus = ST_LTCHINI;					/* ﾀｯﾁ初期化へ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示ﾀｯﾁ初期化

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_LTCHINI

	[処理内容]
******************************************************************************/
void DicLstTchInit(void)
/*TAIL*/
{
	if(srcflg!=TRUE)
		DicLstScr.vol = tidxc;			/* ｽｸﾛｰﾙﾊﾞｰ全体量はｲﾝﾃﾞｯｸｽ総数 */

	LibTchStackClr();					/* ﾀｯﾁｴﾘｱ初期化 */
	LibTchInit();
	TchComSet();
	LibTchStackPush(TchListArea);		/* ﾘｽﾄｴﾘｱ ﾀｯﾁﾃｰﾌﾞﾙ */
	LibTchStackPush(TchDBSel);			/* 辞書DB選択ﾎﾞﾀﾝﾀｯﾁﾃｰﾌﾞﾙ */
	LibTchStackPush(TchLoupe);			/* 虫眼鏡ﾎﾞﾀﾝﾀｯﾁｴﾘｱ */
	LibTchStackPush(TchActionKey);		/* ｱｸｼｮﾝｷｰ  ﾀｯﾁﾃｰﾌﾞﾙ */

	DicStatus = ST_LBKDSP;					/* 背景描画へ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示背景描画

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_LBKDSP

	[処理内容]
******************************************************************************/
void DicLstBk(void)
/*TAIL*/
{
	LibClrDisp();						/* 画面消去 */

	LibLine(   1,  13, 158,   1,  1);	/* 背景表示(ﾀｲﾄﾙ線) */
	LibLine(   1,  29, 158,   1,  1);	/* 背景表示(上線) */
	LibLine(   1, 159, 158,   1,  1);	/* 背景表示(下線) */

	LibLine(   0,  14,   1, 145,  1);	/* 背景表示(左線) */
	LibLine( 147,  30,   1, 129,  1);	/* 背景表示(中線) */
	LibLine( 159,  14,   1, 145,  1);	/* 背景表示(右線) */

	if(srcflg==TRUE)
		LibPutFarData( 0, 0, 96);		/* 左上虫眼鏡ｱｲｺﾝ表示 */
	else
		LibPutGraph(0,1,micn);			/* 左上ﾓｰﾄﾞｱｲｺﾝ */

	LibPutFarData(98,0,44);				/* 虫眼鏡ﾎﾞﾀﾝｱｲｺﾝ   */
	LibPutGraph(108,1,loupe);			/* 虫眼鏡の絵 */
	LibModeIconDsp();					/* Pop Up Tools */
	DicDBSelWinBk();					/* DB名称枠表示 */

	DicStatus	= ST_LDATASET;				/* ﾘｽﾄﾃﾞｰﾀ表示へ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示ﾃﾞｰﾀｾｯﾄ

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_LDATASET

	[処理内容]
******************************************************************************/
void DicLstDataSet(void)
/*TAIL*/
{
	#define SCHK_CNT	1

	byte		i;
	LSTIDX		lwk;
	long		ovf;
	bool		jdg;
	int			s_cnt;

  /*-- ﾌﾞﾚｰｸｷｰｻﾝﾌﾟﾙ初期化(Escは見ない) --*/
	LibBkSampleInitSub(NULL,0x00);
	MesDone = FALSE;					/* ﾒｯｾｰｼﾞ表示済み区分 = 未 */
	passed	= FALSE;					/* 1秒経過区分 = 未 */
	s_cnt	= 0;

	/** 先頭行指定 **/
	ovf = DicLstScr.pos + DicLstScr.dsp - DicLstScr.vol;
	if((ovf>0)&&(DicLstScr.pos>0)){		/* ﾘｽﾄ下部に空白行ができる時 */
		if(DicLstScr.pos<ovf)			/* ﾃﾞｰﾀ件数がﾘｽﾄ表示行数より小さい時 */
			ovf = DicLstScr.pos;
		DicLstScr.pos -= ovf;
		lcp += ovf;						/* ｶｰｿﾙｼﾌﾄ */
	}

	/***** ｾﾞﾈﾗﾙｻｰﾁ仕様削除 *****/
	/*	if(srcflg!=TRUE){
	/*		lip[0].num = DicLstScr.pos;
	/*	}else{
	/*		if(GenSrc2(DicLstScr.pos, &lip[0])==FALSE)
	/*			lip[0].num = 0;
	/*	}
	*/
		lip[0].num = DicLstScr.pos;
	/****************************/

	if(GetIndex(&lip[0],0)==FALSE)		/* ｲﾝﾃﾞｯｸｽ番号より先頭行ﾃﾞｰﾀ取得 */
		lip[0].num = 0xffffffff;

	for(i=1;i<L_LNC;i++){

		/*--- ﾌﾞﾚｰｸｷｰｻﾝﾌﾟﾙ処理 ---*/
		LibBkSampleCheck(&passed);
		if(passed)	DicWaitingMes();	/* "Please Wait..." */

		/*--- ESC ﾀｯﾁｽｷｬﾝ処理 ---*/
	/*	if( (++s_cnt) >=SCHK_CNT ){
	/*		if( DicTchEscScan() ){
	/*			LibWinIcnMsg(ICON_BIKKURI,387,2);	/* Stopped! */
	/*			DicStatus = ST_IINI;		/* 検索入力画面へ */
	/*			return;
	/*		}
	/*		s_cnt = 0;
	/*	}
	*/

		lwk = lip[i-1];
		if(lwk.num!=0xffffffff){

		/*** ｾﾞﾈﾗﾙｻｰﾁ仕様削除 ***/
		/*	if(srcflg==TRUE)			/* ｾﾞﾈﾗﾙｻｰﾁ中 */
		/*		jdg = NxtGenSrc(&lwk,srclen);
		/*	else
		/*		jdg = GetNxtTitleIndex(&lwk);
		*/
			jdg = GetNxtTitleIndex(&lwk);
		/************************/

			if(jdg==FALSE)				/* 次行ﾀｲﾄﾙｲﾝﾃﾞｯｸｽﾃﾞｰﾀ取得 */
				lwk.num = 0xffffffff;
		}
		lip[i] = lwk;
	}

	DicStatus	= ST_LDATADSP;				/* ﾘｽﾄﾃﾞｰﾀ表示へ */

	#undef SCHK_CNT
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄﾃﾞｰﾀ表示

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_LDATADSP

	[処理内容]
******************************************************************************/
void DicLstDisp(void)
/*TAIL*/
{
	byte		i;

	LibClrBox(L_STX-1,L_STY-1,L_EDX-L_STX+1,L_ITY*L_LNC-1);
										/* ﾘｽﾄｴﾘｱ画面消去 */
	for(i=0;i<L_LNC;i++){
		if(lip[i].num!=0xffffffff)
			Lst1DataDsp(i);				/* 一件表示 */
		if(i<L_LNC-1)
			LibMeshLine(L_STX-1,L_STY+L_ITY*(i+1)-2,L_EDX-L_STX+2,1);
										/* 行区切り点線表示 */
	}

	DLibScrollPrint(DicLstScr);			/* ｽｸﾛｰﾙﾊﾞｰ表示 */

	DicStatus	= ST_LTCHIDLE;			/* ﾀｯﾁ待ちへ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示１件ﾃﾞｰﾀｾｯﾄ

	[引数]
		byte	ln;		ﾃﾞｰﾀのﾘｽﾄ表示行位置(0～L_LNC-1)

	[戻り値]
	[処理内容]
******************************************************************************/
void Lst1DataDsp(byte ln)
/*TAIL*/
{
	byte far	*tgt;
	int			j, xp, yp, nw, lmt;
	byte		i;
	byte		tmp[TT_LEN+1];
	byte		ccd;
	bool		loop = TRUE;

	if(DicDataRead(&lip[ln],&tgt)==FALSE)		/* ﾃﾞｰﾀ読み込み */
		return;

	xp = L_STX;
	yp = L_STY+L_ITY*ln;

	lmt = i = 0;
	while(loop==TRUE){
		if(i>TT_LEN){
			loop = FALSE;
			break;
		}
		ccd = JdgContCode(&tgt);			/* 制御ｺｰﾄﾞ判断 */
		switch(ccd){

			case CD_CHA:		/* 文字ｺｰﾄﾞ「00h～7Fh」 */
			case CD_OVCHA:		/* 1ﾊﾞｲﾄｺｰﾄﾞ指定(0x80以上)「@\x??」 */
				nw = LibGetProFontSize(IB_PFONT1,*tgt);	/* 文字横幅取得 */
				if((xp+nw+DOT3>= L_EDX)&&(lmt==0))
					lmt = i;				/* ｢...｣挿入位置退避 */
				if(xp+nw>= L_EDX){			/* 一行に表示し切れなかった場合 */
					i = lmt;
					for(j=0;j<3;j++){		/* ｢...｣表示 */
						tmp[i] = '.';
						i++;
					}
					loop = FALSE;
					break;
				}
				tmp[i] = *tgt;
				tgt ++;
				i++;
				xp += nw;
				break;

			case CD_FNT57:		/* 5x7ﾌｫﾝﾄ指定        「@\fNM」 */
			case CD_FNTPN:		/* ﾌﾟﾛﾎﾟｰｼｮﾅﾙﾌｫﾝﾄ指定 「@\fPN」 */
			case CD_FNTPB:		/* 太文字ﾌｫﾝﾄ指定     「@\fPB」 */
				break;

		/*	case CD_RTN:		/* 改行ｺｰﾄﾞ「0Dh」 */
		/*	case CD_END:		/* 終了ｺｰﾄﾞ(次見出し)「@\T」 */
			default:			/* Fail Safe */
				loop = FALSE;
				break;
		}
	}

	tmp[i]=NULL;
	LibPutProStr(IB_PFONT1,L_STX,yp,tmp,L_EDX-L_STX);	/* 一行表示 */
	return;
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｲﾝﾃﾞｯｸｽ取得

	[引数]
		LSTIDX	*lidx		: ﾘｽﾄｲﾝﾃﾞｯｸｽ構造体
			lidx.num			in	取得ｲﾝﾃﾞｯｸｽ番号
			lidx.flp			out	該当ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰの含まれるﾌｧｲﾙﾎﾟｲﾝﾀｰ
			lidx.ofs			out	該当ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰのｵﾌｾｯﾄ

		byte	type		: in	取得ｲﾝﾃﾞｯｸｽ種別
										0:Title
										1:Link
	[戻り値]
		TRUE	: 正常終了
		FALSE	: 該当ｲﾝﾃﾞｯｸｽは存在しない

	[処理内容]
		num番目のｲﾝﾃﾞｯｸｽをｾｯﾄする
******************************************************************************/
bool GetIndex(LSTIDX *lidx, byte type)
/*TAIL*/
{
	byte	ityp;
	word	ofs, flp,tblk,tofs;
	long	bict,num,idxc;

	if(type==0){			/* Titleｲﾝﾃﾞｯｸｽが対象の時 */
		ityp = IT_TITLE;
		tblk = ttopbk;
		tofs = ttopof;
		idxc = tidxc;
	}else{					/* Linkｲﾝﾃﾞｯｸｽが対象の時 */
		ityp = IT_LINK;
		tblk = ltopbk;
		tofs = ltopof;
		idxc = lidxc;
	}

	num = lidx->num;
	if(num>idxc-1)
		return(FALSE);			/* ｲﾝﾃﾞｯｸｽ総数ｵｰﾊﾞｰ */

	flp = topfp + tblk;			/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ先頭が含まれるﾌｧｲﾙ */
	bict = (SZ_BLOCK-tofs)/8;
	ofs = tofs;

	while(1){
		if(bict<=num){
			num -= bict;
			flp ++;
		}else{
			if(DicIndexFileRead(flp)!=TRUE)		/* ｲﾝﾃﾞｯｸｽﾌｧｲﾙ読み出し */
				return(FALSE);
			break;
		}
		bict = SZ_BLOCK/8;
		ofs = 0;
	}

	ofs += num*8;

	if(Ibuf.bin_buf[ofs] != ityp)		/* ｲﾝﾃﾞｯｸｽ種別ﾁｪｯｸ */
		return(FALSE);

	lidx->flp = flp;					/* ﾌｧｲﾙﾎﾟｲﾝﾀｰ指定 */
	lidx->ofs = ofs;					/* ｵﾌｾｯﾄ指定 */
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		次ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ取得

	[引数]
		LSTIDX	*lidx		: in	現在ﾘｽﾄｲﾝﾃﾞｯｸｽ構造体
			lidx.num					現在ｲﾝﾃﾞｯｸｽ番号
			lidx.flp					現在ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰの含まれるﾌｧｲﾙﾎﾟｲﾝﾀｰ
			lidx.ofs					現在ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰのｵﾌｾｯﾄ

	[戻り値]
		FALSE	: 該当ｲﾝﾃﾞｯｸｽは存在しない
		TRUE	: 正常終了

		LSTIDX	*lidx		: out	次ﾘｽﾄｲﾝﾃﾞｯｸｽ構造体
			lidx.num					次ｲﾝﾃﾞｯｸｽ番号
			lidx.flp					次ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰの含まれるﾌｧｲﾙﾎﾟｲﾝﾀｰ
			lidx.ofs					次ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰのｵﾌｾｯﾄ

	[処理内容]
		次のﾀｲﾄﾙｲﾝﾃﾞｯｸｽのｱﾄﾞﾚｽを取得する

******************************************************************************/
bool GetNxtTitleIndex(LSTIDX *lidx)
/*TAIL*/
{
	word	flp,ofs;
	long	num;

	num = lidx->num;				/* 現在ﾘｽﾄｲﾝﾃﾞｯｸｽ構造体取得 */
	flp = lidx->flp;
	ofs = lidx->ofs;

	if((num >= tidxc-1)||(num == 0xffffffff)){
		num = 0xffffffff;
		return(FALSE);
	}

	/* 次ﾎﾟｲﾝﾀｰが現在ﾎﾟｲﾝﾀｰと同一ﾌｧｲﾙに有る時 */
	if(ofs+8 < SZ_BLOCK){
		if(DicIndexFileRead(flp)!=TRUE)
			return(FALSE);
		ofs += 8;

	/* 次ﾎﾟｲﾝﾀｰが現在ﾎﾟｲﾝﾀｰと同一ﾌｧｲﾙに無い時 */
	}else{
		flp ++;
		if(DicIndexFileRead(flp)!=TRUE)
			return(FALSE);
		ofs = 0;
	}

	lidx->num += 1;
	lidx->flp = flp;
	lidx->ofs = ofs;
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		前ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ取得

	[引数]
		LSTIDX	*lidx		: in	現在ﾘｽﾄｲﾝﾃﾞｯｸｽ構造体
			lidx.num					現在ｲﾝﾃﾞｯｸｽ番号
			lidx.flp					現在ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰの含まれるﾌｧｲﾙﾎﾟｲﾝﾀｰ
			lidx.ofs					現在ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰのｵﾌｾｯﾄ

	[戻り値]
		LSTIDX	*lidx		: out	前ﾘｽﾄｲﾝﾃﾞｯｸｽ構造体
			lidx.num					前ｲﾝﾃﾞｯｸｽ番号
			lidx.flp					前ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰの含まれるﾌｧｲﾙﾎﾟｲﾝﾀｰ
			lidx.ofs					前ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰのｵﾌｾｯﾄ

		TRUE	: 正常終了
		FALSE	: 該当ｲﾝﾃﾞｯｸｽは存在しない

	[処理内容]
		前のﾀｲﾄﾙｲﾝﾃﾞｯｸｽのｱﾄﾞﾚｽを取得する

******************************************************************************/
bool GetPrvTitleIndex(LSTIDX *lidx)
/*TAIL*/
{
	bool	jdg = FALSE;
	word	flp,ofs;
	long	num;

	num = lidx->num;				/* 現在ﾘｽﾄｲﾝﾃﾞｯｸｽ構造体取得 */
	flp = lidx->flp;
	ofs = lidx->ofs;

	if(num <= 0)
		return(FALSE);

	/* 前ﾎﾟｲﾝﾀｰが現在ﾎﾟｲﾝﾀｰと同一ﾌｧｲﾙに有る時 */
	if(ofs != 0){
		jdg = TRUE;
		if(DicIndexFileRead(flp)!=TRUE)
			return(FALSE);
		ofs -= 8;

	/* 前ﾎﾟｲﾝﾀｰが現在ﾎﾟｲﾝﾀｰと同一ﾌｧｲﾙに無い時 */
	}else{
		flp --;
		if(flp<topfp)
			return(FALSE);
		if(DicIndexFileRead(flp)!=TRUE)
			return(FALSE);
		ofs = BUFSIZE-8;
	}

	lidx->num -= 1;
	lidx->flp = flp;
	lidx->ofs = ofs;
	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示 ﾀｯﾁ待ち

	[引数]
	[戻り値]

	[処理ｸﾗｽ]
		基幹処理		DicStatus = ST_LTCHIDLE

	[処理内容]
******************************************************************************/
void DicLstTchIdle(void)
/*TAIL*/
{
	TCHSTS	tsts;
	int		revl,lcbk;
	int		mklc;				/* ﾘｽﾄ表示ｶｰｿﾙﾎﾟｲﾝﾀｰ退避ｴﾘｱ */
	bool	jdg;
	long	posbk;
	byte	amsk;
	TXTP	tp;
	bool	arw = TRUE;

	revl = lcp;
	posbk = DicLstScr.pos;
	while(DicStatus==ST_LTCHIDLE){

		/* ｽｸﾛｰﾙﾊﾞｰ上下矢印網掛け処理 */
		if(arw==TRUE){
			DLibScrollArrowPrint(DicLstScr,SCR_NO_MASK);
			amsk = LstArrowMask(&DicLstScr);
			DLibScrollArrowPrint(DicLstScr,amsk);
			arw = FALSE;
		}

		LstCsrDsp(lcp);					/* 反転ｶｰｿﾙ点灯 */
		LibPutDisp();					/* 画面更新 */
		LibTchWait( &tsts );			/* ﾀｯﾁ待ち */

		lcbk = lcp;
		switch(tsts.obj){

			case OBJ_LPSW_UP:		/* ｱｸｼｮﾝｷｰ Up */
				if(LstCsrUpChk(&DicLstScr)==TRUE){
					if(LstScBarUp(&DicLstScr)==TRUE){
						DicStatus = ST_LDATADSP;	/* 画面書き換え */
					}
				}else{
					LibRepOff();	/* ﾘﾋﾟｰﾄ Off */
				}
				break;

			case OBJ_LPSW_DOWN:		/* ｱｸｼｮﾝｷｰ Down */
				if(LstCsrDwnChk(&DicLstScr)==TRUE){
					if(LstScBarDwn(&DicLstScr)==TRUE){
						DicStatus = ST_LDATADSP;	/* 画面書き換え */
					}
				}else{
					LibRepOff();	/* ﾘﾋﾟｰﾄ Off */
				}
				break;

			case OBJ_LPSW_PUSH:		/* ｱｸｼｮﾝｷｰ Push */
				idxsp = 0;				/* 表示制御用ﾊﾟﾗﾒｰﾀﾎﾟｲﾝﾀｰ初期化 */
				sdp[idxsp] = lip[lcp];	/* ﾀｰｹﾞｯﾄ設定 */
				DicStatus = ST_SINI;	/* ﾃﾞｰﾀ詳細表示へ */
				break;

			case OBJ_IC_DBSEL:		/* DB Select */
				if(DicDBSelWin(&tsts,TRUE)==TRUE)
					DicStatus = ST_LFILEINI;
				break;

			case OBJ_SCR_BAR:		/* ScrollBar */
				arw = DicLstScBar(&tsts,posbk);
				break;

			case OBJ_AR_LIST:		/* List ｴﾘｱ */
				jdg = LstCsrMv(&tsts,&revl);		/* ﾘｽﾄｶｰｿﾙ移動処理 */
				if(jdg==TRUE){
					DicStatus	= ST_LTCHIDLE;		/* ｶｰｿﾙ再表示へ */
					if(tsts.act==ACT_MAKE){			/* make時 */
						mklc = lcp;
					}else if(tsts.act==ACT_BREAK){	/* break時 */
						if(mklc==revl){				/* makeﾗｲﾝでﾌﾞﾚｲｸ時 */
							idxsp = 0;				/* 表示制御用ﾊﾟﾗﾒｰﾀﾎﾟｲﾝﾀｰ初期化 */
							sdp[idxsp] = lip[mklc];	/* ﾀｰｹﾞｯﾄ設定 */
							DicStatus	= ST_SINI;	/* ﾃﾞｰﾀ詳細表示へ */
						}
					}
					lcp = revl;				/* 反転ｶｰｿﾙ移動 */
					arw = TRUE;
				}
				break;

			case OBJ_IC_SRCKEY:				/* 虫眼鏡ﾎﾞﾀﾝ */
				DicSrcBtn(&tsts);			/* ｻｰﾁ入力へ */
				break;

			case OBJ_HIC_ESC:
				if(srcflg==TRUE){
					DicLstScr.pos = lip[lcp].num;	/* ﾘｽﾄ先頭行に */
					lcp = 0;				/* ｶｰｿﾙを先頭行に */
					DicStatus = ST_LTCHINI;	/* ﾘｽﾄ再表示 */
					srcflg = HALF;			/* ｻｰﾁ解除 */
				}else{
					DicStatus = ST_IINI;	/* 検索語入力へ(ﾃｷｽﾄ初期化はしない) */
				}
				break;

			case OBJ_HIC_MBAR:		/* ﾒﾆｭｰﾊﾞｰﾊｰﾄﾞｱｲｺﾝ */
				DicPdwnSet();				/* ﾌﾟﾙﾀﾞｳﾝﾒﾆｭｰ表示設定 */
				if(DicPdwnFnc(&tp)==TRUE)	/* ﾌﾟﾙﾀﾞｳﾝ処理 */
					return;
				break;

			default:
				DicStatus = ST_LTCHIDLE;			/* NOP */
				break;
		}
		LstCsrDsp(lcbk);					/* 反転ｶｰｿﾙ消灯 */
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示の反転ｶｰｿﾙを表示（消去）する

	[引数]
		int		lc		: in	ｶｰｿﾙ表示(消去)行位置 （0～）

	[処理内容]
******************************************************************************/
void LstCsrDsp(int lc)
/*TAIL*/
{
	LibReverse(2, 30+lc*10, 144,9);	/* ﾘｽﾄｶｰｿﾙ 反転表示 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示中､ｽｸﾛｰﾙﾊﾞｰ内ﾀｯﾁ時処理
	[引数]
	[戻り値]
		TRUE	: ｽｸﾛｰﾙ､またはｶｰｿﾙ移動時
		FALSE	: NOP時

	[処理内容]
******************************************************************************/
bool DicLstScBar(TCHSTS *tsts, long posbk)
/*TAIL*/
{
	int		ans;
	bool	ret = FALSE;

	ans = DLibScrPosCheck(*tsts,DicLstScr);
	if(ans==0){					/* 上ｽｸﾛｰﾙｷｰﾀｯﾁ時 */
		if(LstCsrUpChk(&DicLstScr)==FALSE)
			return(ret);			/* 上移動不可の時 */

	}else if(ans==1){			/* 下ｽｸﾛｰﾙｷｰﾀｯﾁ時 */
		if(LstCsrDwnChk(&DicLstScr)==FALSE)
			return(ret);			/* 下移動不可の時 */
	}

	ans = DLibScrollClick(tsts,&DicLstScr);

	switch(ans){
		case 0:					/* 上ｽｸﾛｰﾙｷｰﾀｯﾁ時 */
			if(tsts->act==ACT_BREAK_IN){
				ret = TRUE;
				if(LstScBarUp(&DicLstScr)==TRUE){
					DicStatus = ST_LDATADSP;	/* 画面書き換え */
				}
			}
			break;

		case 1:					/* 下ｽｸﾛｰﾙｷｰﾀｯﾁ時 */
			if(tsts->act==ACT_BREAK_IN){
				ret = TRUE;
				if(LstScBarDwn(&DicLstScr)==TRUE){
					DicStatus = ST_LDATADSP;	/* 画面書き換え */
				}
			}
			break;

		case 2:					/* ｽｸﾛｰﾙﾊﾞｰﾀｯﾁ & ﾄﾞﾗｯｸﾞ時 */
			if(posbk!=DicLstScr.pos){
				lcp += (posbk - DicLstScr.pos);
				if(lcp>=L_LNC)
					lcp = L_LNC - 1;
				else if(lcp<0)
					lcp = 0;
				ret = TRUE;
				DicStatus = ST_LDATASET;			/* 全画面書き換え */
			}
			break;
	}
	return(ret);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示中､ｶｰｿﾙ下方向移動可能判定

	[戻り値]
		TRUE	: ｶｰｿﾙ下方向移動可能
		FALSE	: ｶｰｿﾙ下方向移動不可
******************************************************************************/
bool LstCsrDwnChk(XT_SCR_POS *scr)
/*TAIL*/
{
	if( (lcp==L_LNC-1)&&(scr->pos == scr->vol-scr->dsp) ){
		return(FALSE);
	}else if(lcp<L_LNC-1 && lip[lcp+1].num==0xffffffff){
		return(FALSE);
	}
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示中､ｶｰｿﾙ上方向移動可能判定

	[戻り値]
		TRUE	: ｶｰｿﾙ上方向移動可能
		FALSE	: ｶｰｿﾙ上方向移動不可
******************************************************************************/
bool LstCsrUpChk(XT_SCR_POS *scr)
/*TAIL*/
{
	if(lcp==0 && scr->pos==0)
		return(FALSE);			/* 移動不可 */
	return(TRUE);				/* 移動可能 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示中､ｽｸﾛｰﾙﾊﾞｰ UPﾎﾞﾀﾝﾀｯﾁ時処理

	[戻り値]
		TRUE	: ｶｰｿﾙ移動によるｽｸﾛｰﾙ発生
		FALSE	: ｽｸﾛｰﾙ未発生

	[処理内容]
******************************************************************************/
bool LstScBarUp(XT_SCR_POS *scr)
/*TAIL*/
{
	byte		i;
	LSTIDX		lwk;
	bool		jdg = FALSE;

	/** 現在､ｶｰｿﾙが2行目以降の時 **/
	if(lcp>0){
		if(lip[lcp-1].num!=0xffffffff){
			lcp--;
		}

	/** 現在､ｶｰｿﾙが先頭行の時 **/
	}else{
		lwk = lip[0];
		if(GetPrvTitleIndex(&lwk)==TRUE){	/* 前ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰｻｰﾁ */
			for(i=L_LNC-2;;i--){
				lip[i+1] = lip[i];		/* ﾘｽﾄﾎﾟｲﾝﾀｰ ｼﾌﾄDown */
				if(i==0)
					break;
			}
			lip[0] = lwk;
			jdg = TRUE;
			(scr->pos)--;
		}
	}
	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示中､ｽｸﾛｰﾙﾊﾞｰ Downﾎﾞﾀﾝﾀｯﾁ時処理

	[戻り値]
		TRUE	: ｶｰｿﾙ移動によるｽｸﾛｰﾙ発生
		FALSE	: ｽｸﾛｰﾙ未発生

	[処理内容]
******************************************************************************/
bool LstScBarDwn(XT_SCR_POS *scr)
/*TAIL*/
{
	byte		i;
	LSTIDX		lwk;
	bool		jdg = FALSE;

	/** 現在､ｶｰｿﾙが最下行以外の時 **/
	if(lcp<L_LNC-1){
		if(lip[lcp+1].num!=0xffffffff){
			lcp++;
		}

	/** 現在､ｶｰｿﾙが最下行の時 **/
	}else{
		lwk = lip[L_LNC-1];
		if(GetNxtTitleIndex(&lwk)==TRUE){	/* 次ﾃﾞｰﾀｻｰﾁ */
			for(i=0;i<L_LNC-1;i++){
				lip[i] = lip[i+1];	/* ﾘｽﾄﾎﾟｲﾝﾀｰ ｼﾌﾄUp */
			}
			lip[L_LNC-1] = lwk;
			jdg = TRUE;
			(scr->pos)++;
		}
	}
	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		辞書ﾘｽﾄ表示中、ﾘｽﾄｴﾘｱ ﾀｯﾁ時処理

	[引数]
		TCHSTS	*tsts	: in		ﾀｯﾁｽﾃｰﾀｽ
		int		*revl	: in/out	反転ｶｰｿﾙ行位置(0～)

	[戻り値]
		TRUE	: 有効ｴﾘｱ内ﾀｯﾁ時
		FALSE	: 無効ｴﾘｱﾀｯﾁ時

	[処理内容]
		ｶｰｿﾙ移動、またはﾃﾞｰﾀ表示への遷移を行う。
******************************************************************************/
bool LstCsrMv(TCHSTS *tsts, int *revl)
/*TAIL*/
{
	byte	sel;

	sel = SelLstTchLn(tsts->x,tsts->y);		/* ﾀｯﾁ該当行算出 */
	if(sel==0xff || lip[sel].num==0xffffffff)	/* ｴﾘｱから外れた時 */
		return(FALSE);							/* 反転ﾗｲﾝはそのまま */

	*revl = sel;						/* 反転位置更新 */
	return(TRUE);
}



/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示中、ﾀｯﾁ時行算出
	[引数]
	[戻り値]
		ﾀｯﾁ位置の行数（0,1,2... FFhはﾘｽﾄｴﾘｱ外）

	[処理内容]
		ﾘｽﾄ表示画面上でﾀｯﾁされた箇所が、画面上で何件目であるか算出する
******************************************************************************/
byte SelLstTchLn(word xp, word yp)
/*TAIL*/
{
	word	i,ly;

	if(xp<L_STX-1 || L_EDX<xp)				/* 横に外れている時 */
		return(0xff);
	if(yp<L_STY-1 || L_EDY<yp)				/* 縦に外れている時 */
		return(0xff);

	for(ly=L_STY-1,i=0; i<L_LNC-1; i++){
		ly += L_ITY;
		if(ly>yp)
			break;
	}
	return(i);
}


