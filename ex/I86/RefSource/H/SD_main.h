/******************************************************************************
	[ﾀｲﾄﾙ]
		Referencer ﾍｯﾀﾞｰ

	[機種]
		ZX400 Referencer

	[概要]

	[作成者]
		鈴木茂人

	Copyright (C) 2000 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#ifndef SD_MAIN_DEF
#define SD_MAIN_DEF

#include	"SD_scrbar.h"


#define ST_MODEINI		0x00	/* ﾓｰﾄﾞ初期化 */
#define ST_LFILEINI		0x10	/* ﾘｽﾄ表示ﾌｧｲﾙ初期化 */
#define ST_LTCHINI		0x11	/* ﾘｽﾄ表示ﾀｯﾁ初期化 */
#define ST_LBKDSP		0x12	/* ﾘｽﾄ表示背景描画 */
#define ST_LDATASET		0x13	/* ﾘｽﾄ表示ﾃﾞｰﾀｾｯﾄ */
#define ST_LDATADSP		0x14	/* ﾘｽﾄ表示ﾃﾞｰﾀ表示 */
#define ST_LTCHIDLE		0x15	/* ﾘｽﾄ表示ﾀｯﾁ待ち */
#define ST_SINI			0x20	/* 詳細表示初期化 */
#define ST_SBKDSP		0x21	/* 詳細表示背景表示 */
#define ST_SDATADSP		0x22	/* 詳細表示ﾃﾞｰﾀ表示 */
#define ST_SSBARDSP		0x23	/* 詳細表示ｽｸﾛｰﾙﾊﾞｰ表示 */
#define ST_STCHIDLE		0x24	/* 詳細表示ﾀｯﾁ待ち */
#define ST_IINI			0x30	/* ｻｰﾁ入力初期化 */
#define ST_ILOOP		0x31	/* ｻｰﾁ入力ﾙｰﾌﾟ */

#define DBN_LEN			15		/* DBﾌｧｲﾙ名長 */
#define	OBJ_AR_LIST		0xe000	/* LIST AREA */
#define	OBJ_IC_ISRC		0xe001	/* ｲﾆｼｬﾙｻｰﾁｱｲｺﾝ */
#define	OBJ_IC_GSRC		0xe002	/* ｾﾞﾈﾗﾙｻｰﾁｱｲｺﾝ */
#define	OBJ_IC_CLRKEY	0xe003	/* CLR_Key */
#define	OBJ_IC_DTMKEY	0xe004	/* DayTime_Key */
#define	OBJ_IC_CALKEY	0xe005	/* CAL_Key */
#define	OBJ_IC_EXEKEY	0xe006	/* EXE_Key */
#define	OBJ_IC_DBSEL	0xe007	/* DataBase Select Key */
#define	OBJ_IC_LSTKEY	0xe008	/* List_Key */
#define	OBJ_IC_PRVKEY	0xe009	/* Prev_Key */
#define	OBJ_IC_NXTKEY	0xe00a	/* Next_Key */
#define	OBJ_IC_BCKKEY	0xe00b	/* BACK_Key */
#define	OBJ_IC_SRCKEY	0xe00c	/* Search_Key */
#define	OBJ_AR_SHOW		0xe00d	/* Data Disp Area */
#define	OBJ_AR_LWOUT	0xe00e	/* Link Data Windowの外 */
#define	OBJ_AR_LWIN		0xe00f	/* Link Data Windowの内 */

#define	FNT_TITLE	IB_PFONT2	/* ﾀｲﾄﾙ表示ﾌｫﾝﾄ */
#define	FNT_SUBT	IB_PFONT2	/* ｻﾌﾞﾀｲﾄﾙ表示ﾌｫﾝﾄ */
#define	FNT_LINKT	IB_PFONT2	/* ﾘﾝｸﾀｲﾄﾙ表示ﾌｫﾝﾄ */
#define	FNT_BASE	IB_PFONT1	/* 本文表示ﾌｫﾝﾄ */

#define	D_LNC		16			/* ﾃﾞｰﾀ表示行数 */
#define	D_STX		14			/* ﾃﾞｰﾀ表示開始座標(X) */
#define	D_STY		15			/* ﾃﾞｰﾀ表示開始座標(Y) */
#define	D_EDX		146			/* ﾃﾞｰﾀ表示最終座標(X)+1 */
#define	D_EDY		D_STY+D_ITY*D_LNC	/* ﾃﾞｰﾀ表示最終座標(Y)+1 */
#define	D_ITY		9			/* ﾃﾞｰﾀ表示行間隔 */
#define D_SFTX		6			/* 見出し語表示左ｼﾌﾄ幅 */
#define	D_STTX		D_STX-D_SFTX*2	/* ﾃﾞｰﾀ表示ﾀｲﾄﾙ開始座標(Y) */
#define	D_STTY		31				/* ﾃﾞｰﾀ表示ﾀｲﾄﾙ開始座標(Y) */
#define	D_ETTX		158				/* ﾃﾞｰﾀ表示ﾀｲﾄﾙ終了座標(Y)+1 */
#define	D_ETTY		D_STTY+D_ITY*3	/* ﾃﾞｰﾀ表示ﾀｲﾄﾙ終了座標(Y)+1 */

#define	W_LNC		9			/* ﾘﾝｸﾃﾞｰﾀ表示行数 */
#define	W_STX		16			/* ﾘﾝｸﾃﾞｰﾀ表示開始座標(X) */
#define	W_STY		75			/* ﾘﾝｸﾃﾞｰﾀ表示開始座標(Y) */
#define	W_EDX		143			/* ﾘﾝｸﾃﾞｰﾀ表示最終座標(X)+1 */
#define	W_EDY		W_STY+D_ITY*W_LNC	/* ﾘﾝｸﾃﾞｰﾀ表示最終座標(Y)+1 */
#define W_SFTX		6			/* 見出し語表示左ｼﾌﾄ幅 */

#define	L_LNC		13			/* ﾘｽﾄ表示行数 */
#define	L_STX		3			/* ﾘｽﾄ表示開始座標(X) */
#define	L_STY		31			/* ﾘｽﾄ表示開始座標(Y) */
#define	L_EDX		146			/* ﾘｽﾄ表示最終座標(X)+1 */
#define	L_EDY		L_STY+L_ITY*L_LNC	/* ﾘｽﾄ表示最終座標(Y)+1 */
#define	L_ITY		10			/* ﾘｽﾄ表示行間隔 */

#define	SI_ST_X		32		/* ｻｰﾁ入力ﾃｷｽﾄｴﾘｱ(st_x) */
#define	SI_ST_Y		45		/* ｻｰﾁ入力ﾃｷｽﾄｴﾘｱ(st_y) */
#define	SI_ED_X		129		/* ｻｰﾁ入力ﾃｷｽﾄｴﾘｱ(ed_x) */
#define	SI_IT_Y		9		/* ｻｰﾁ入力ﾃｷｽﾄｴﾘｱ(it_y) */
#define	SI_MAXG		1		/* ｻｰﾁ入力ﾃｷｽﾄｴﾘｱ(MAXGYO) */
#define	SRC_LEN		12		/* ｻｰﾁ入力最大文字数 */

#define	CD_CHA		0x00			/* 文字ｺｰﾄﾞ「00h～7Fh」 */
#define	CD_RTN		0x01			/* 改行ｺｰﾄﾞ「0Dh」 */
#define	CD_OVCHA	0x03			/* 1ﾊﾞｲﾄｺｰﾄﾞ指定(0x80以上)「@\x??」 */
#define	CD_TITLE	0x10			/* 見出し「@\T」 */
#define	CD_SUBT		0x11			/* 小見出し「@\C」 */
#define	CD_GPDEF	0x12			/* 画像指定「@\g????」 */
#define	CD_END		0x13			/* 終了ｺｰﾄﾞ(次見出し)「@@@」 */
#define	CD_FNT57	0x14			/* 5x7ﾌｫﾝﾄ指定        「@\fNM」 */
#define	CD_FNTPN	0x15			/* ﾌﾟﾛﾎﾟｰｼｮﾅﾙﾌｫﾝﾄ指定 「@\fPN」 */
#define	CD_FNTPB	0x16			/* 太文字ﾌｫﾝﾄ指定     「@\fPB」 */
#define	CD_JPDEF	0x17			/* ｼﾞｬﾝﾌﾟ指定「@\j[文字列]」 */
#define	CD_LKDEF	0x18			/* ﾘﾝｸ指定「@\l[文字列]」 */
#define	CD_LINK		0x19			/* ﾘﾝｸ見出し「@\L[文字列]」 */

#define	TT_LEN		64				/* ﾀｲﾄﾙ最大文字列長 */
#define	GL_LEN		2				/* ｸﾞﾗﾌｨｯｸﾗﾍﾞﾙ長 */
#define BUFSIZE		10240			/* ﾊﾞｯﾌｧｻｲｽﾞ(10KB) */
#define DATAMAX		BUFSIZE			/* ﾃﾞｰﾀ1件の最大ｻｲｽﾞ */

#define	OFS_FNAME	20				/* ﾃﾞｰﾀﾍﾞｰｽ名称 */
#define	OFS_TTOP	148				/* ﾀｲﾄﾙ ｲﾝﾃﾞｯｸｽ 先頭ｱﾄﾞﾚｽ */
#define	OFS_TIDXC	OFS_TTOP  + 4	/* ﾀｲﾄﾙ ｲﾝﾃﾞｯｸｽ数  */
#define	OFS_LTOP	OFS_TIDXC + 4	/* ﾘﾝｸ ｲﾝﾃﾞｯｸｽ 先頭ｱﾄﾞﾚｽ */
#define	OFS_LIDXC	OFS_LTOP  + 4	/* ﾘﾝｸ ｲﾝﾃﾞｯｸｽ数  */
#define	OFS_GTOP	OFS_LIDXC + 4	/* ｸﾞﾗﾌｨｯｸ ｲﾝﾃﾞｯｸｽ 先頭ｱﾄﾞﾚｽ */
#define	OFS_GIDXC	OFS_GTOP  + 4	/* ｸﾞﾗﾌｨｯｸ ｲﾝﾃﾞｯｸｽ数  */

#define	JC_LEN		18				/* DBﾌｧｲﾙ識別ｺｰﾄﾞ長 */
#define	SZ_BLOCK	1024*10			/* DBﾌｧｲﾙﾌﾞﾛｯｸ長 */

#define	IT_TITLE	0x02			/* ﾀｲﾄﾙ ｲﾝﾃﾞｯｸｽ種別 */
#define	IT_LINK		0x04			/* ﾘﾝｸ  ｲﾝﾃﾞｯｸｽ種別 */
#define	IT_GRAPH	0x05			/* 画像 ｲﾝﾃﾞｯｸｽ種別 */

#define	LST_RD		0x00			/* ﾘｽﾄ画面再表示 */
#define	LST_UP		0x01			/* ﾘｽﾄｽｸﾛｰﾙUP(下ｷｰ押下時) */
#define	LST_DN		0x02			/* ﾘｽﾄｽｸﾛｰﾙDOWN(上ｷｰ押下時) */
#define	LST_CM		0x03			/* ｶｰｿﾙ移動(ｽｸﾛｰﾙなし) */

#define	DOT3		3 * 3			/* 「...」ﾄﾞｯﾄ幅 */
/*	#define	LKPSCT		30				/* ﾘﾝｸ位置退避ｴﾘｱ個数 */
#define	DCTSPMAX	12+1			/* ｲﾝﾃﾞｯｸｽｽﾀｯｸ最大数 */

 /** ﾌｧﾝｸｼｮﾝ指定 **/
#define 	PDWN_EDT_CUT	PULLDOWN_EDIT | 0x0001		/* Cut					*/
#define 	PDWN_EDT_COPY	PULLDOWN_EDIT | 0x0002		/* Copy					*/
#define 	PDWN_EDT_PASTE	PULLDOWN_EDIT | 0x0004		/* Paste				*/
#define 	PDWN_EDT_SRCH	PULLDOWN_EDIT | 0x0008		/* Search				*/

#define 	PDWN_SYS_DTTM	PULLDOWN_SYSTEM | 0x0001	/* Set_date/time		*/
#define 	PDWN_SYS_SOUND	PULLDOWN_SYSTEM | 0x0002	/* Sound				*/
#define 	PDWN_SYS_FORMT	PULLDOWN_SYSTEM | 0x0004	/* Format				*/
#define 	PDWN_SYS_CAPCT	PULLDOWN_SYSTEM | 0x0008	/* Capacity				*/
#define 	PDWN_SYS_MMANE	PULLDOWN_SYSTEM | 0x0010	/* Memory_management	*/
#define 	PDWN_SYS_LANG	PULLDOWN_SYSTEM | 0x0020	/* Language				*/
#define 	PDWN_SYS_CNTRS	PULLDOWN_SYSTEM | 0x0040	/* Contrast				*/
#define 	PDWN_SYS_TPA	PULLDOWN_SYSTEM | 0x0080	/* Touch_Panel_Alignment*/

#define 	PDWN_OPT_SCPY	PULLDOWN_OPTION | 0x0001	/* Screen copy			*/


/************************************************/
/*              型定義                          */
/************************************************/

/* FLASH data buffer (BinaryBuffer 10KB) CAUTION:Allocate a buffer for FAR_BSS.*/
typedef struct LFBUF {
	byte	fsb_main_entry_;			/* MainEntryNo. */
	byte	fsb_sub_entry_;				/* SubEntryNo.  */

	byte	fsb_scrt_info_;				/* SecretInformation */
	byte	fsb_ararm_chk_;				/* AlarmCheckInformation */

	byte	fsb_todo_chek_;				/* TODO CheckInformation */
	byte	fsb_todo_rank_;				/* TODO RankInformation  */

	byte	fsb_date1_buf_[8];			/* Date/DueDate */
	byte	fsb_date2_buf_[8];			/* CheckDate    */
	byte	fsb_date_aram_[8];			/* AlarmDate    */
	byte	fsb_time1_buf_[4];			/* Time/DueTime(From)     */
	byte	fsb_time2_buf_[4];			/* Tiem/DueTime(To)       */
	byte	fsb_time3_buf_[4];			/* CheckTime              */
	byte	fsb_time_aram_[4];			/* AlarmTime              */

	byte	fsb_date_srch_[8];			/* SearchBuffer Date      */
	byte	fsb_time_srch_[4];			/* SearchBuffer Time      */
	byte	fsb_text_srch_[33];			/* SearchBuffer RealData(TEXT)  */

	byte	dummy_16by[22];				/* MemoryManagementWork   */
	word	char_num;					/* BinaryDataCapacity     */
	byte	bin_buf[10240+64];			/* Buffer to store real data (BINARY) 10KB  */
										/* ﾀﾞﾐｰﾃﾞｰﾀ24Byteを考慮し、（160+1）ﾌﾞﾛｯｸ分 */
} LFBUF;


typedef struct {
	/* 入力条件 */
	byte far	*pot;		/* ﾀｰｹﾞｯﾄﾎﾟｲﾝﾀｰ */
	int			sx;			/* 表示開始座標(X) */
	int			sy;			/* 表示開始座標(Y) */
	int			ex;			/* 表示終了座標(X)+1 */
	int			ey;			/* 表示終了座標(Y)+1 */
	int			ity;		/* 改行幅 */
	byte		lnc;		/* 表示ﾃｷｽﾄ行数 */
	byte		fnt;		/* Font Type */

	/* ﾜｰｸ */
	byte		code;		/* ﾀｰｹﾞｯﾄ文字ｺｰﾄﾞ */
	int			x;			/* 表示位置(X) */
	int			y;			/* 表示位置(Y) */
	byte far 	*lkpt;		/* Link終了(+1)ﾎﾟｲﾝﾀｰ */
	bool		jpf;		/* Jumpﾌﾗｸﾞ(JUMP時:TRUE / Link時:FALSE) */
	byte		st;			/* 状態 ･･･ (0:通常/1:小見出し/2:見出し) */
}DSPCT;

typedef struct {
	word	ofs;			/* ﾃﾞｰﾀ表示各TEXT行の先頭文字ｵﾌｾｯﾄ */
	byte	fnt;			/* ﾃﾞｰﾀ表示各TEXT行の先頭文字ﾌｫﾝﾄ */
	byte	st;				/* ﾃﾞｰﾀ表示各TEXT行の先頭文字状態 */
	word	lnk;			/* ﾃﾞｰﾀ表示各TEXT行の先頭文字ﾘﾝｸ設定(ｵﾌｾｯﾄ) */
	bool	jpf;			/* Jumpﾌﾗｸﾞ(JUMP時:TRUE / Link時:FALSE) */
}SHWIDX;

typedef struct {
	long	num;			/* ｲﾝﾃﾞｯｸｽの番目(0～) */
	word	flp;			/* ｲﾝﾃﾞｯｸｽの存在するﾌｧｲﾙﾎﾟｲﾝﾀｰ */
	word	ofs;			/* ｲﾝﾃﾞｯｸｽﾊﾞｯﾌｧ先頭からのｵﾌｾｯﾄ */
	long	pos;			/* 表示先頭行位置 */
}LSTIDX;

typedef struct {
	word	smp;			/* ﾃﾞｰﾀ表示中、各ﾘﾝｸの先頭文字ｵﾌｾｯﾄ */
	word	emp;			/* ﾃﾞｰﾀ表示中、各ﾘﾝｸの終了文字(+1)ｵﾌｾｯﾄ */
}LNKIDX;


/************************************************/
/*              グローバル変数                  */
/************************************************/
extern byte			DBname[16];		/* 使用中DBﾌｧｲﾙ名称 */
extern byte			DBfc;			/* ｲﾝｽﾄｰﾙ済みDBﾌｧｲﾙ数(0～2) */
extern byte			DicStatus;
extern byte			dlp[];
extern byte			dic_en;			/* 辞書ﾃﾞｰﾀｴﾝﾄﾘｰ */
extern byte			dic_sben;		/* 辞書ﾃﾞｰﾀｻﾌﾞｴﾝﾄﾘｰ */

/*extern LFILE_BUF far	FileBuf;		/* FLASH BIOS用ﾃﾞｰﾀﾊﾞｯﾌｧ */
extern LFBUF far	Ibuf;			/* FLASH BIOS用ﾃﾞｰﾀﾊﾞｯﾌｧ1 */
extern LFBUF far	Dbuf;			/* FLASH BIOS用ﾃﾞｰﾀﾊﾞｯﾌｧ2 */
extern LFBUF far	Gbuf;			/* FLASH BIOS用ﾃﾞｰﾀﾊﾞｯﾌｧ3 */
/*extern FILE_INFO		FileInf;		/* FLASH BIOS用ﾃﾞｰﾀ情報  */
extern FILE_INFO	Iinf;			/* FLASH BIOS用ﾃﾞｰﾀ情報1 */
extern FILE_INFO	Dinf;			/* FLASH BIOS用ﾃﾞｰﾀ情報2 */
extern FILE_INFO	Ginf;			/* FLASH BIOS用ﾃﾞｰﾀ情報3 */

extern LSTIDX		lip[L_LNC];		/* ﾘｽﾄ表示行ｲﾝﾃﾞｯｸｽ */
extern LSTIDX		sdp[];			/* ﾃﾞｰﾀ表示ｲﾝﾃﾞｯｸｽｽﾀｯｸ */
extern LSTIDX		lnkdp;			/* ﾘﾝｸﾃﾞｰﾀ表示ｲﾝﾃﾞｯｸｽ */
extern long			tidxc;			/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ総数 */
extern XT_SCR_POS	DicLstScr;		/* ﾘｽﾄ表示用ｽｸﾛｰﾙﾊﾞｰ */
extern int			lcp;			/* ﾘｽﾄ表示ｶｰｿﾙﾎﾟｲﾝﾀｰ */
extern bool			srcflg;			/* ｻｰﾁﾌﾗｸﾞ */
extern byte			srcbf[];		/* ｻｰﾁﾊﾞｯﾌｧ */
extern int			srclen;			/* ｻｰﾁ文字列長 */
extern bool			MesDone;		/* ﾒｯｾｰｼﾞ表示済み区分 */
extern bool			passed;			/* 1秒経過区分 */
extern byte far		*dttop;			/* ﾀｰｹﾞｯﾄﾃﾞｰﾀ開始ｱﾄﾞﾚｽ */
extern word			sel_sp;			/* 選択開始文字 */
extern word			sel_ep;			/* 選択終了文字 */
extern word			rsp;			/* 反転開始文字 */
extern word			rep;			/* 反転終了文字 */
extern SHWIDX		dltp[D_LNC+2];	/* 行先頭ﾎﾟｲﾝﾀｰ */
extern DSPCT		wtct;			/* 単語先頭情報 */
extern word			topfp;			/* 辞書ﾃﾞｰﾀTOPﾌｧｲﾙﾎﾟｲﾝﾀｰ */
extern byte			idxsp;			/* ｲﾝﾃﾞｯｸｽｽﾀｯｸﾎﾟｲﾝﾀｰ */
extern long			tidxc;			/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽ総数 */
extern word			ttopbk;			/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ﾌﾞﾛｯｸ) */
extern word			ttopof;			/* ﾀｲﾄﾙｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ｵﾌｾｯﾄ) */
extern word			gidxc;			/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ総数 */
extern word			gtopbk;			/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ﾌﾞﾛｯｸ) */
extern word			gtopof;			/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ｵﾌｾｯﾄ) */
extern long			lidxc;			/* ﾘﾝｸｲﾝﾃﾞｯｸｽ総数 */
extern word			ltopbk;			/* ﾘﾝｸｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ﾌﾞﾛｯｸ) */
extern word			ltopof;			/* ﾘﾝｸｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ(ｵﾌｾｯﾄ) */

#define	IBUF_A		(LFILE_BUF far *)(&Ibuf)
#define	DBUF_A		(LFILE_BUF far *)(&Dbuf)
#define	GBUF_A		(LFILE_BUF far *)(&Gbuf)

/************************************************/
/*              far ｴﾘｱ                         */
/************************************************/
extern TCHTBL far TchDicShow[];
extern TCHTBL far TchListArea[];
extern TCHTBL far TchSrcTopKey[];
extern TCHTBL far TchSrcTyp[];
extern TCHTBL far TchDtHead[];
extern TCHTBL far TchLoupe[];
extern TCHTBL far TchDBSel[];

extern TCHTBL far TchLinkShow[];

extern T_ICON far TicnClrKey;
extern T_ICON far TicnDTMKey;
extern T_ICON far TicnCalKey;
extern T_ICON far TicnExeKey;
extern T_ICON far TicnDtLst;
extern T_ICON far TicnDtPrv;
extern T_ICON far TicnDtNxt;
extern T_ICON far TicnDtBck;
extern T_ICON far TicnLoupe;
extern T_ICON far TicnDBSel;

extern word srcgid[];				/* ｻｰﾁ入力時ｶﾞｲﾀﾞﾝｽﾃｰﾌﾞﾙ */

extern byte far headtop[];			/* DBﾌｧｲﾙ識別ｺｰﾄﾞ */

extern byte far MeshArrow[2][28];		/* 網掛け状態の矢印 */
extern byte far DBwinM[];			/* DB選択ｳｨﾝﾄﾞｳﾎﾞﾀﾝﾏｽｸ */
extern byte far ShowTopBtn[];		/* ﾃﾞｰﾀ表示先頭行ﾎﾞﾀﾝ */
extern byte far loupe[];			/* ﾎﾞﾀﾝ内の虫眼鏡ｸﾞﾗﾌｨｯｸ */
extern byte far micn[];				/* 画面左上ﾓｰﾄﾞｱｲｺﾝ */
extern byte far PullCal[];			/* ﾎﾟｯﾌﾟｱｯﾌﾟ電卓復帰時ｱｲｺﾝ(正常体) */
extern byte far PushCal[];			/* ﾎﾟｯﾌﾟｱｯﾌﾟ電卓押下時ｱｲｺﾝ */
extern byte far PullClk[];			/* 時刻書き込み復帰時ｱｲｺﾝ(正常体) */
extern byte far PushClk[];			/* 時刻書き込み押下時ｱｲｺﾝ */
extern byte far DBChgBtn[2][28];	/* 辞書切り替えﾎﾞﾀﾝ */
extern byte far DBnameFrame[];		/* 辞書名表示枠 */

extern word PdEdt[];		/* [Edit] ﾒﾆｭｰﾊﾞｰﾒｯｾｰｼﾞ */
extern word PdSys[];		/* [System] ﾒﾆｭｰﾊﾞｰﾒｯｾｰｼﾞ */
extern word PdOpt[];		/* [Option] ﾒﾆｭｰﾊﾞｰﾒｯｾｰｼﾞ */


/************************************************/
/*              プロトタイプ宣言                */
/************************************************/

/*** SD_main.c ***/
void DicInit(void);
byte GetDicFileName(byte sben, byte *fname);
void DicHeadRead(void);
bool FileTopRead(byte sben, bool all);
void FbufInit(byte en, byte sben, LFBUF far *f_buf);
void TchComSet(void);
void DicDBSelWinBk(void);
bool DicDBSelWin(TCHSTS *tsts, bool btn);

/*** SD_list.c ***/
void DicLstFileInit(void);
void DicLstTchInit(void);
void DicLstBk(void);
void DicLstDataSet(void);
void DicLstDisp(void);
void Lst1DataDsp(byte ln);
bool GetIndex(LSTIDX *lidx, byte type);
bool GetNxtTitleIndex(LSTIDX *lidx);
bool GetPrvTitleIndex(LSTIDX *lidx);
void DicLstTchIdle(void);
void LstCsrDsp(int lc);
bool DicLstScBar(TCHSTS *tsts, long posbk);
bool LstCsrDwnChk(XT_SCR_POS *scr);
bool LstCsrUpChk(XT_SCR_POS *scr);
bool LstScBarUp(XT_SCR_POS *scr);
bool LstScBarDwn(XT_SCR_POS *scr);
bool LstCsrMv(TCHSTS *tsts, int *revl);
byte SelLstTchLn(word xp, word yp);

/*** SD_show.c ***/
void DicShowInit(void);
void DicShowBk(void);
void DicShowDataDsp(void);
void DicShowSbarDsp(void);
void DicDspTopSrc(DSPCT *dct, int tlc);
void DicDltpClear(DSPCT *dct);
void DicTxtDsp(DSPCT *dct);
void AdjustStartX(DSPCT *dct);
void DicShowTchIdle(void);
void DicShowScrUp(void);
void DicShowScrDwn(void);
byte PrvLineTop(SHWIDX *swk);
void PrvRtnTopSrc(SHWIDX *swk, byte far *ntop);
void SelRevOff(void);
void LstCsrAdjust(void);
bool DicShowScBar(TCHSTS *tsts, XT_SCR_POS *scr);
bool ChkScrlUp(XT_SCR_POS *scr);
bool ChkScrlDwn(XT_SCR_POS *scr);
void DicPrevBtn(TCHSTS *tsts, bool btn);
void DicNextBtn(TCHSTS *tsts, bool btn);
void DicBackBtn(TCHSTS *tsts);
void DicBackBtnSub(void);
void DicSrcBtn(TCHSTS *tsts);
void DicRevDisp(DSPCT *dct);
bool DicShowAreaTch(TCHSTS *tsts, DSPCT *dct);
byte GetTchMj(DSPCT *dct, int tx, int ln, word *tgt);
bool GetTchLink(word *sp, word *ep, byte ln);
byte GetLinkIndex(byte lj);
void DicLinkShowDsp(void);
void LinkShowBk(void);
void LinkShowData(void);

/*** SD_lib.c ***/
bool DicDsp1L(DSPCT *dct, bool den);
bool DicDsp1C(DSPCT *dct, bool den, byte *ccd);
byte JdgContCode(byte far **tgt);
bool Dsp1Cha(DSPCT *dct, bool den);
bool DspGraph(DSPCT *dct, bool den);
/* bool PutGraphE(int x, int y, const byte far *graph); */
bool PutGraphE(DSPCT *dct, const byte far *graph);
bool GetGraphSize(const byte far *graph, int *xs, int *ys);
void NextLine(DSPCT *dct);
bool TitleCodeSrc(byte far **tgt);
bool CodeSrc(byte far **tgt, byte cd);
bool DicGraphFileRead(word flp);
bool DicDataFileRead(word flp);
bool DicIndexFileRead(word flp);
bool DicFileRead(LFBUF far *buf, FILE_INFO *inf);
bool DicDataRead(LSTIDX *lidx, byte far **tgt);
bool DicGraphRead(LSTIDX *lidx);
bool JdgGraphIndex(word ofs, word gnum);
word GetGraphNum(byte far *tgt);
long GetDicDspL(byte far *tgt, DSPCT *dctwk);
bool CmpStr(byte far *stra, byte far *strb, int len);
bool LinkSet(DSPCT *dct, bool den, bool jpf);
/* bool DicTchEscScan(void);	*/
void DicWaitingMes(void);
byte LstArrowMask(XT_SCR_POS *scr);
byte DataArrowMask(XT_SCR_POS *scr);
void FilePointerInit();

/*** SD_src.c ***/
void DicSrcInit(void);
void SrcTxtInit(TXTP *tp, T_SCR_POS *scbar, TCHTBL *tcht);
void DicSrcInput(void);
void DicSrcInpBk(void);
void DicSrcDsp(void);
bool DicSrcExe(void);
void ChrS2L(byte far *d, byte far *s);
byte DicIniSrc(long *tgt, byte *buf, int len, byte type, bool ls);
byte JdgStrHighLow(long num, byte *buf, int len, byte type, bool lss);
void SelCharacter(byte *dbuf, byte far **sbuf, int len);

/*** SD_func.c ***/
void DicPdwnSet(void);
bool DicPdwnFnc(TXTP *tp);
bool PdwnFncEdt(word sel, TXTP *tp);
bool PdwnFncSys(word sel);
bool PdwnFncOpt(word sel);
void DicScrnShot(void);

#endif
