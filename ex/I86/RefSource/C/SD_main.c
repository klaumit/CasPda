/******************************************************************************
	[ﾀｲﾄﾙ]
		Referencer

	[機種]
		通信電子手帳(海外)

	[概要]
		Referencer メイン

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


byte			DicStatus;				/* 状態変数 */
byte			dlp[16];

LFBUF far		Ibuf;			/* FLASH BIOS用ﾃﾞｰﾀﾊﾞｯﾌｧ1 */
LFBUF far		Dbuf;			/* FLASH BIOS用ﾃﾞｰﾀﾊﾞｯﾌｧ2 */
LFBUF far		Gbuf;			/* FLASH BIOS用ﾃﾞｰﾀﾊﾞｯﾌｧ3 */
FILE_INFO		Iinf;			/* FLASH BIOS用ﾃﾞｰﾀ情報1 */
FILE_INFO		Dinf;			/* FLASH BIOS用ﾃﾞｰﾀ情報2 */
FILE_INFO		Ginf;			/* FLASH BIOS用ﾃﾞｰﾀ情報3 */

byte			DBname[DBN_LEN+1];	/* 使用中DBﾌｧｲﾙ名称 */
byte			DBfc;				/* ｲﾝｽﾄｰﾙ済みDBﾌｧｲﾙ数(0～2) */



/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		メイン処理

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void main(void)
/*TAIL*/
{
	DicStatus	= ST_MODEINI;

	for(;;){

		switch(DicStatus){

		/******************************/
		/*      初期設定              */
		/******************************/
			case ST_MODEINI:			/* ﾓｰﾄﾞ初期設定 */
				DicInit();
				break;

		/******************************/
		/*      検索結果ﾘｽﾄ表示       */
		/******************************/
			case ST_LFILEINI:				/* ﾌｧｲﾙ初期設定 */
				DicLstFileInit();
				break;

			case ST_LTCHINI:			/* ﾀｯﾁ初期設定 */
				DicLstTchInit();
				break;

			case ST_LBKDSP:				/* 背景描画 */
				DicLstBk();
				break;

			case ST_LDATASET:			/* ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰｾｯﾄ */
				DicLstDataSet();
				break;

			case ST_LDATADSP:			/* ﾘｽﾄﾃﾞｰﾀ表示 */
				DicLstDisp();
				break;

			case ST_LTCHIDLE:			/* ﾀｯﾁ待ち */
				DicLstTchIdle();
				break;

		/******************************/
		/*      検索結果ﾃﾞｰﾀ表示      */
		/******************************/
			case ST_SINI:				/* 初期化 */
				DicShowInit();
				break;

			case ST_SBKDSP:				/* 背景描画 */
				DicShowBk();
				break;

			case ST_SDATADSP:			/* 表示ﾃﾞｰﾀｾｯﾄ */
				DicShowDataDsp();
				break;

			case ST_SSBARDSP:			/* 表示ﾃﾞｰﾀｾｯﾄ */
				DicShowSbarDsp();
				break;

			case ST_STCHIDLE:			/* ﾀｯﾁ待ち */
				DicShowTchIdle();
				break;

		/******************************/
		/*      検索文字列入力        */
		/******************************/
			case ST_IINI:				/* 初期設定 */
				DicSrcInit();
				break;

			case ST_ILOOP:				/* ｻｰﾁ文字列入力 */
				DicSrcInput();
				break;

		/******************************/
		/*      その他                */
		/******************************/
			default:					/* ｽﾃｰﾀｽｴﾗｰ */
				DicStatus = ST_MODEINI;	/* Fale Safe */
				break;
		}
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		辞書ﾓｰﾄﾞ初期化

	[引数]		なし
	[戻り値]	なし
******************************************************************************/
void DicInit(void)
/*TAIL*/
{
	byte	sben;
	byte	dbn[DBN_LEN+1];

	DBfc = 0;						/* とりあえずDBﾌｧｲﾙは無し */
	srcflg = FALSE;					/* initialｻｰﾁ */
	srcbf[0] = 0;					/* ｻｰﾁﾊﾞｯﾌｧ初期化 */
	dic_sben = 0xff;
	DBname[0] = 0;

	if(LibGetSubEntNum()>0){		/* 登録済みﾕｰｻﾞｰﾌｧｲﾙがあった時 */

		/* 先頭DBﾌｧｲﾙの名称取得 */
		for(sben=1; sben<=15; sben++){
			if(GetDicFileName(sben,dbn)>0){	/* DBﾌｧｲﾙ発見時 */
				DBfc ++;
				if(DBfc==1){		/* 先頭DBﾌｧｲﾙ名取得 */
					dic_sben = sben;
					strcpy(DBname,dbn);
				}else if(DBfc>1){	/* DBﾌｧｲﾙが２個以上あったら... */
					break;
				}
			}
		}
	}

	if(DBfc>0){						/* DBﾌｧｲﾙが1個でもあったら... */
		FilePointerInit();			/* ﾌｧｲﾙﾎﾟｲﾝﾀｰ初期化 */
		DicHeadRead();				/* DBﾍｯﾀﾞｰ読み込み */
	}

	/*** ﾘｽﾄ表示ｽｸﾛｰﾙﾊﾞｰ初期設定 ***/
	DicLstScr.x		= L_EDX+3;		/* ｽｸﾛｰﾙﾊﾞｰ位置(X)  */
	DicLstScr.y		= L_STY+1;		/* ｽｸﾛｰﾙﾊﾞｰ位置(Y)  */
	DicLstScr.size	= L_EDY-L_STY-5;/* ｽｸﾛｰﾙﾊﾞｰ高さ     */
	DicLstScr.dsp	= L_LNC;		/* 表示件数         */
	DicLstScr.pos	= 0;			/* ｽｸﾛｰﾙﾊﾞｰ初期位置 */

	DicStatus	= ST_IINI;			/* ｻｰﾁ語入力へ */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		辞書ﾃﾞｰﾀﾍﾞｰｽﾌｧｲﾙ名取得

	[引数]
		byte	sben		: in	ｻﾌﾞｴﾝﾄﾘｰ番号
		byte	*fname		: out	DB名称

	[戻り値]
		DBﾌｧｲﾙ名称文字列長（0:該当ﾌｧｲﾙは辞書DBではない）

	[処理ｸﾗｽ]
	[処理内容]
		Ibufにﾕｰｻﾞｰﾌｧｲﾙを読み込み、辞書DBならばDB名称を取得する
******************************************************************************/
byte GetDicFileName(byte sben, byte *fname)
/*TAIL*/
{
	bool	len = 0;
	byte	uf[16];				/* ﾕｰｻﾞｰﾌｧｲﾙ名読み出し用 */

	/* ｻﾌﾞｴﾝﾄﾘｰ番号からﾕｰｻﾞｰﾌｧｲﾙ名取得 */
	if(LibGetSubEntrySt(uf, sben) == TRUE){

		if(uf[0]!=NULL){
			if(FileTopRead(sben,FALSE)==TRUE){		/* 先頭ﾌｧｲﾙ読み込み */
				fname[0] = NULL;					/* とりあえず */
				if(far_memcmp(&Ibuf.bin_buf[0],headtop,JC_LEN)==0){
													/* ﾍｯﾀﾞｰ文字列確認 */
					far_strcpy(fname,(&Ibuf.bin_buf[0])+OFS_FNAME);
													/* DB名取得 */
					len = strlen(fname);
				}
			}
		}
	}
	return(len);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		辞書DB,ﾍｯﾀﾞｰﾌｧｲﾙ読み込み

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void DicHeadRead(void)
/*TAIL*/
{
	/* ﾍｯﾀﾞｰﾌｧｲﾙ読み込み */
	if(FileTopRead(dic_sben,TRUE)==TRUE){
		topfp = Iinf.fp;					/* 辞書ﾃﾞｰﾀTOPﾌｧｲﾙﾎﾟｲﾝﾀｰ取得 */
		tidxc = *((long far *)(&Ibuf.bin_buf[0]+OFS_TIDXC));
											/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ数取得 */
		ttopbk = *((word far *)(&Ibuf.bin_buf[0]+OFS_TTOP));
											/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ先頭ﾌﾞﾛｯｸ取得 */
		ttopof = *((word far *)(&Ibuf.bin_buf[0]+OFS_TTOP+2));
											/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ先頭ｵﾌｾｯﾄ取得 */
		gtopbk = *((word far *)(&Ibuf.bin_buf[0]+OFS_GTOP));
											/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ先頭ﾌﾞﾛｯｸ取得 */
		gtopof = *((word far *)(&Ibuf.bin_buf[0]+OFS_GTOP+2));
											/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ先頭ｵﾌｾｯﾄ取得 */
		gidxc = *((word far *)(&Ibuf.bin_buf[0]+OFS_GIDXC));
											/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ数取得 */
		ltopbk = *((word far *)(&Ibuf.bin_buf[0]+OFS_LTOP));
											/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ先頭ﾌﾞﾛｯｸ取得 */
		ltopof = *((word far *)(&Ibuf.bin_buf[0]+OFS_LTOP+2));
											/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ先頭ｵﾌｾｯﾄ取得 */
		lidxc = *((word far *)(&Ibuf.bin_buf[0]+OFS_LIDXC));
											/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ数取得 */
		lcp = 0;							/* ﾘｽﾄｶｰｿﾙﾎﾟｲﾝﾀｰ初期化 */

	}else{
		DBname[0] = NULL;					/* ﾌｧｲﾙ名称ｸﾘｱ */
		tidxc = 0;							/* ｲﾝﾃﾞｯｸｽ数ｸﾘｱ */
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾌｧｲﾙ先頭部分読み込み

	[引数]
	[戻り値]
		TRUE	:	正常終了
		FALSE	:	読み込みｴﾗｰ

	[処理内容]
******************************************************************************/
bool FileTopRead(byte sben, bool all)
/*TAIL*/
{

	byte		fname[16];
	bool		jdg = FALSE;
	byte		mode_entry, sub_entry;

	if(sben==0xff)
		return(jdg);

	/* ｻﾌﾞｴﾝﾄﾘｰ番号からﾌｧｲﾙ名取得 */
	if(LibGetSubEntrySt(fname, sben)==TRUE){

		/* ﾌｧｲﾙ名よりｴﾝﾄﾘｰｺｰﾄﾞ､ｻﾌﾞｴﾝﾄﾘｰを取得 */
		if(LibGetAllEntry(fname, &mode_entry, &sub_entry)==TRUE){

			/* ﾌｧｲﾙ先頭ﾚｺｰﾄﾞｻｰﾁ */
			FilePointerInit();						/* 先頭ﾌｧｲﾙに設定 */
			FbufInit(mode_entry,sub_entry,&Ibuf);	/* ｲﾝﾃﾞｯｸｽﾊﾞｯﾌｧ初期化 */
			FbufInit(mode_entry,sub_entry,&Dbuf);	/* ﾃﾞｰﾀﾊﾞｯﾌｧ初期化 */
			FbufInit(mode_entry,sub_entry,&Gbuf);	/* ｸﾞﾗﾌｨｯｸﾊﾞｯﾌｧ初期化 */

			if(LibLFileFindNext(IBUF_A,&Iinf,0x00)==TRUE){

				if(all==TRUE)
		/*			jdg = LibLFileRead(&FileBuf,&FileInf);		*/
					jdg = DicFileRead(&Ibuf,&Iinf);
				else
				/* ﾌｧｲﾙ先頭ﾚｺｰﾄﾞ256byteのみ読み込み */
					jdg = LibLFileReadEx(IBUF_A,&Iinf, 4);
			}
		}
	}
	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾌｧｲﾙﾊﾞｯﾌｧ初期化

	[引数]
		LFBUF far	*f_buf		:out	FLASH BIOS用ﾃﾞｰﾀﾊﾞｯﾌｧ

	[戻り値]
		なし

	[処理内容]
		Flashﾗｲﾌﾞﾗﾘ用のﾊﾞｯﾌｧを初期化する.

******************************************************************************/
void FbufInit(byte en, byte sben, LFBUF far *f_buf)
/*TAIL*/
{
	f_buf->fsb_main_entry_		= en;			/* ﾓｰﾄﾞｴﾝﾄﾘｰﾅﾝﾊﾞｰ     */
	f_buf->fsb_sub_entry_		= sben;			/* ｻﾌﾞｴﾝﾄﾘｰﾅﾝﾊﾞｰ      */

	f_buf->fsb_scrt_info_		= 0x80;			/* ｵｰﾌﾟﾝ/ｼｰｸﾚｯﾄ情報   */
	f_buf->fsb_ararm_chk_		= 0x00;			/* ｱﾗｰﾑﾁｪｯｸ情報       */
	f_buf->fsb_todo_chek_		= 0x04;			/* TODOﾁｪｯｸ情報       */
	f_buf->fsb_todo_rank_		= 0xff;			/* TODOﾗﾝｸ情報        */
	f_buf->fsb_date1_buf_[0]	= 0;			/* 日付/期限日付      */
	f_buf->fsb_date2_buf_[0]	= 0;			/* ﾁｪｯｸ日付           */
	f_buf->fsb_date_aram_[0]	= 0;			/* ｱﾗｰﾑ日付           */
	f_buf->fsb_time1_buf_[0]	= 0;			/* 開始/期限時刻      */
	f_buf->fsb_time2_buf_[0]	= 0;			/* 終了/期限時刻      */
	f_buf->fsb_time3_buf_[0]	= 0;			/* ﾁｪｯｸ時間           */
	f_buf->fsb_time_aram_[0]	= 0;			/* ｱﾗｰﾑ時刻           */
	f_buf->fsb_date_srch_[0]	= 0;			/* 日付ｻｰﾁ用ﾊﾞｯﾌｧ     */
	f_buf->fsb_time_srch_[0]	= 0;			/* 時間ｻｰﾁ用ﾊﾞｯﾌｧ     */
	f_buf->fsb_text_srch_[0]	= 0;			/* ｻｰﾁ用ﾊﾞｯﾌｧ         */

	f_buf->dummy_16by[0]		= 0;			/* ﾒﾓﾘ差分ﾀﾞﾐｰ        */
	f_buf->char_num				= 0;			/* ﾊﾞｲﾅﾘｰﾃﾞｰﾀﾊﾞｲﾄ数   */
	f_buf->bin_buf[0]			= 0;			/* 実ﾃﾞｰﾀﾊﾞｯﾌｧ(ﾊﾞｲﾅﾘ) */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾀｯﾁｴﾘｱ ｾｯﾄ

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void TchComSet(void)
/*TAIL*/
{
	LibTchStackPush( NULL );
	LibTchStackPush( TchHardIcon );
	LibTchStackPush( TchModeIcon );		/* Pop Up Tools */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		辞書選択ｳｨﾝﾄﾞｳ表示

	[引数]
	[処理内容]
******************************************************************************/
void DicDBSelWinBk(void)
/*TAIL*/
{
	LibPutGraph(0,13,DBnameFrame);		/* DB名称枠 */
	if(DBfc<2)							/* DBﾌｧｲﾙが2個以上の時 */
		LibPutGraph(126,13,DBwinM);		/* DBｳｨﾝﾄﾞｳﾏｽｸ */
	LibPutProStr(IB_PFONT1,3,15,DBname,121);	/* DB名称表示 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		辞書選択ｳｨﾝﾄﾞｳ処理

	[引数]
	[処理内容]
******************************************************************************/
bool DicDBSelWin(TCHSTS *tsts, bool btn)
/*TAIL*/
{
	SLW2_ST		win_prm;
	byte		sel_ret;
	byte		i,lc,dft;
	int			j;
	byte		sben;
	bool		jdg = FALSE;
	byte		cmnt[15*(DBN_LEN+1)];
	byte		rtv[15+1];

	if(DBfc<2)			/* DBﾌｧｲﾙが2個未満の時 */
		return(FALSE);

	if(btn==TRUE){
		if(LibIconClick(&TicnDBSel,tsts)==FALSE)
			return(FALSE);
	}

	/* DBﾌｧｲﾙ名一覧取得 */
	for(j=0,lc=0,sben=1; sben<=15; sben++){	/* 登録済み全ﾕｰｻﾞｰﾌｧｲﾙをｻｰﾁ */
		i = GetDicFileName(sben,&cmnt[j]);
		if(i>0){
			jdg = TRUE;			/* DBﾌｧｲﾙ名取得完了 */ 
			j += i;
			cmnt[j] = 0xfe;
			j ++;
			rtv[lc] = sben;			/* "LibSelWindow" 戻り値 */
			if(sben==dic_sben)		/* 現在使用中のDBﾌｧｲﾙの時 */
				dft = lc;			/* ﾃﾞﾌｫﾙﾄ反転位置 */
			lc++;
		}
	}
	cmnt[j] = 0xff;					/* 終端付加 */
	rtv[lc] = 0xff;					/* 終端付加 */

	/*** 選択ｳｨﾝﾄﾞｳ処理 ***/
	win_prm.x	 =   -1;
	win_prm.y	 =   23;
	win_prm.xs	 =  128;
	win_prm.t_xs =    3;
	win_prm.ity	 =    9;
	win_prm.np	 =    dft;			/* ﾃﾞﾌｫﾙﾄ反転位置 */
	win_prm.cmnt = &cmnt[0];		/* 表示ｺﾒﾝﾄﾃｰﾌﾞﾙ指定 */
	win_prm.rtv  = &rtv[0];			/* 戻り値ﾃｰﾌﾞﾙ指定 */

	if(lc>15)						/* ｴﾗｰの時 */
		return(FALSE);
	else if(lc==15)					/* DBが15の時 */
		win_prm.y -= 5	;			/* ｳｲﾝﾄﾞｳ開始位置を上げる */

	sel_ret = LibSelWindowExt(&win_prm);	/* 選択ｳｨﾝﾄﾞｳ */
	if(sel_ret!=0xff){
		dic_sben = sel_ret;			/* DBﾌｧｲﾙ変更 */
		FilePointerInit();			/* 全ﾎﾟｲﾝﾀｰ先頭ﾌｧｲﾙに設定 */
		GetDicFileName(dic_sben,&DBname[0]);
		DicHeadRead();				/* DBﾍｯﾀﾞｰ読み込み */

	/*	DicStatus = ST_IINI;		/* ｻｰﾁ語入力へ */
		return(TRUE);
	}
	return(FALSE);
}


