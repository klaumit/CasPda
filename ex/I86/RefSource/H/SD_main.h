/******************************************************************************
	[����]
		Referencer ͯ�ް

	[�@��]
		ZX400 Referencer

	[�T�v]

	[�쐬��]
		��ؖΐl

	Copyright (C) 2000 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#ifndef SD_MAIN_DEF
#define SD_MAIN_DEF

#include	"SD_scrbar.h"


#define ST_MODEINI		0x00	/* Ӱ�ޏ����� */
#define ST_LFILEINI		0x10	/* ؽĕ\��̧�ُ����� */
#define ST_LTCHINI		0x11	/* ؽĕ\����������� */
#define ST_LBKDSP		0x12	/* ؽĕ\���w�i�`�� */
#define ST_LDATASET		0x13	/* ؽĕ\���ް���� */
#define ST_LDATADSP		0x14	/* ؽĕ\���ް��\�� */
#define ST_LTCHIDLE		0x15	/* ؽĕ\������҂� */
#define ST_SINI			0x20	/* �ڍו\�������� */
#define ST_SBKDSP		0x21	/* �ڍו\���w�i�\�� */
#define ST_SDATADSP		0x22	/* �ڍו\���ް��\�� */
#define ST_SSBARDSP		0x23	/* �ڍו\����۰��ް�\�� */
#define ST_STCHIDLE		0x24	/* �ڍו\������҂� */
#define ST_IINI			0x30	/* ������͏����� */
#define ST_ILOOP		0x31	/* �������ٰ�� */

#define DBN_LEN			15		/* DB̧�ٖ��� */
#define	OBJ_AR_LIST		0xe000	/* LIST AREA */
#define	OBJ_IC_ISRC		0xe001	/* �Ƽ�ٻ������ */
#define	OBJ_IC_GSRC		0xe002	/* ����ٻ������ */
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
#define	OBJ_AR_LWOUT	0xe00e	/* Link Data Window�̊O */
#define	OBJ_AR_LWIN		0xe00f	/* Link Data Window�̓� */

#define	FNT_TITLE	IB_PFONT2	/* ���ٕ\��̫�� */
#define	FNT_SUBT	IB_PFONT2	/* ������ٕ\��̫�� */
#define	FNT_LINKT	IB_PFONT2	/* �ݸ���ٕ\��̫�� */
#define	FNT_BASE	IB_PFONT1	/* �{���\��̫�� */

#define	D_LNC		16			/* �ް��\���s�� */
#define	D_STX		14			/* �ް��\���J�n���W(X) */
#define	D_STY		15			/* �ް��\���J�n���W(Y) */
#define	D_EDX		146			/* �ް��\���ŏI���W(X)+1 */
#define	D_EDY		D_STY+D_ITY*D_LNC	/* �ް��\���ŏI���W(Y)+1 */
#define	D_ITY		9			/* �ް��\���s�Ԋu */
#define D_SFTX		6			/* ���o����\������ĕ� */
#define	D_STTX		D_STX-D_SFTX*2	/* �ް��\�����يJ�n���W(Y) */
#define	D_STTY		31				/* �ް��\�����يJ�n���W(Y) */
#define	D_ETTX		158				/* �ް��\�����ُI�����W(Y)+1 */
#define	D_ETTY		D_STTY+D_ITY*3	/* �ް��\�����ُI�����W(Y)+1 */

#define	W_LNC		9			/* �ݸ�ް��\���s�� */
#define	W_STX		16			/* �ݸ�ް��\���J�n���W(X) */
#define	W_STY		75			/* �ݸ�ް��\���J�n���W(Y) */
#define	W_EDX		143			/* �ݸ�ް��\���ŏI���W(X)+1 */
#define	W_EDY		W_STY+D_ITY*W_LNC	/* �ݸ�ް��\���ŏI���W(Y)+1 */
#define W_SFTX		6			/* ���o����\������ĕ� */

#define	L_LNC		13			/* ؽĕ\���s�� */
#define	L_STX		3			/* ؽĕ\���J�n���W(X) */
#define	L_STY		31			/* ؽĕ\���J�n���W(Y) */
#define	L_EDX		146			/* ؽĕ\���ŏI���W(X)+1 */
#define	L_EDY		L_STY+L_ITY*L_LNC	/* ؽĕ\���ŏI���W(Y)+1 */
#define	L_ITY		10			/* ؽĕ\���s�Ԋu */

#define	SI_ST_X		32		/* �������÷�Ĵر(st_x) */
#define	SI_ST_Y		45		/* �������÷�Ĵر(st_y) */
#define	SI_ED_X		129		/* �������÷�Ĵر(ed_x) */
#define	SI_IT_Y		9		/* �������÷�Ĵر(it_y) */
#define	SI_MAXG		1		/* �������÷�Ĵر(MAXGYO) */
#define	SRC_LEN		12		/* ������͍ő啶���� */

#define	CD_CHA		0x00			/* �������ށu00h�`7Fh�v */
#define	CD_RTN		0x01			/* ���s���ށu0Dh�v */
#define	CD_OVCHA	0x03			/* 1�޲ĺ��ގw��(0x80�ȏ�)�u@\x??�v */
#define	CD_TITLE	0x10			/* ���o���u@\T�v */
#define	CD_SUBT		0x11			/* �����o���u@\C�v */
#define	CD_GPDEF	0x12			/* �摜�w��u@\g????�v */
#define	CD_END		0x13			/* �I������(�����o��)�u@@@�v */
#define	CD_FNT57	0x14			/* 5x7̫�Ďw��        �u@\fNM�v */
#define	CD_FNTPN	0x15			/* ����߰����̫�Ďw�� �u@\fPN�v */
#define	CD_FNTPB	0x16			/* ������̫�Ďw��     �u@\fPB�v */
#define	CD_JPDEF	0x17			/* �ެ��ߎw��u@\j[������]�v */
#define	CD_LKDEF	0x18			/* �ݸ�w��u@\l[������]�v */
#define	CD_LINK		0x19			/* �ݸ���o���u@\L[������]�v */

#define	TT_LEN		64				/* ���ٍő啶���� */
#define	GL_LEN		2				/* ���̨�����ْ� */
#define BUFSIZE		10240			/* �ޯ̧����(10KB) */
#define DATAMAX		BUFSIZE			/* �ް�1���̍ő廲�� */

#define	OFS_FNAME	20				/* �ް��ް����� */
#define	OFS_TTOP	148				/* ���� ���ޯ�� �擪���ڽ */
#define	OFS_TIDXC	OFS_TTOP  + 4	/* ���� ���ޯ����  */
#define	OFS_LTOP	OFS_TIDXC + 4	/* �ݸ ���ޯ�� �擪���ڽ */
#define	OFS_LIDXC	OFS_LTOP  + 4	/* �ݸ ���ޯ����  */
#define	OFS_GTOP	OFS_LIDXC + 4	/* ���̨�� ���ޯ�� �擪���ڽ */
#define	OFS_GIDXC	OFS_GTOP  + 4	/* ���̨�� ���ޯ����  */

#define	JC_LEN		18				/* DB̧�َ��ʺ��ޒ� */
#define	SZ_BLOCK	1024*10			/* DB̧����ۯ��� */

#define	IT_TITLE	0x02			/* ���� ���ޯ����� */
#define	IT_LINK		0x04			/* �ݸ  ���ޯ����� */
#define	IT_GRAPH	0x05			/* �摜 ���ޯ����� */

#define	LST_RD		0x00			/* ؽĉ�ʍĕ\�� */
#define	LST_UP		0x01			/* ؽĽ�۰�UP(����������) */
#define	LST_DN		0x02			/* ؽĽ�۰�DOWN(�㷰������) */
#define	LST_CM		0x03			/* ���وړ�(��۰قȂ�) */

#define	DOT3		3 * 3			/* �u...�v�ޯĕ� */
/*	#define	LKPSCT		30				/* �ݸ�ʒu�ޔ�ر�� */
#define	DCTSPMAX	12+1			/* ���ޯ�������ő吔 */

 /** ̧ݸ��ݎw�� **/
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
/*              �^��`                          */
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
										/* ��а�ް�24Byte���l�����A�i160+1�j��ۯ��� */
} LFBUF;


typedef struct {
	/* ���͏��� */
	byte far	*pot;		/* ���ޯ��߲��� */
	int			sx;			/* �\���J�n���W(X) */
	int			sy;			/* �\���J�n���W(Y) */
	int			ex;			/* �\���I�����W(X)+1 */
	int			ey;			/* �\���I�����W(Y)+1 */
	int			ity;		/* ���s�� */
	byte		lnc;		/* �\��÷�čs�� */
	byte		fnt;		/* Font Type */

	/* ܰ� */
	byte		code;		/* ���ޯĕ������� */
	int			x;			/* �\���ʒu(X) */
	int			y;			/* �\���ʒu(Y) */
	byte far 	*lkpt;		/* Link�I��(+1)�߲��� */
	bool		jpf;		/* Jump�׸�(JUMP��:TRUE / Link��:FALSE) */
	byte		st;			/* ��� ��� (0:�ʏ�/1:�����o��/2:���o��) */
}DSPCT;

typedef struct {
	word	ofs;			/* �ް��\���eTEXT�s�̐擪�����̾�� */
	byte	fnt;			/* �ް��\���eTEXT�s�̐擪����̫�� */
	byte	st;				/* �ް��\���eTEXT�s�̐擪������� */
	word	lnk;			/* �ް��\���eTEXT�s�̐擪�����ݸ�ݒ�(�̾��) */
	bool	jpf;			/* Jump�׸�(JUMP��:TRUE / Link��:FALSE) */
}SHWIDX;

typedef struct {
	long	num;			/* ���ޯ���̔Ԗ�(0�`) */
	word	flp;			/* ���ޯ���̑��݂���̧���߲��� */
	word	ofs;			/* ���ޯ���ޯ̧�擪����̵̾�� */
	long	pos;			/* �\���擪�s�ʒu */
}LSTIDX;

typedef struct {
	word	smp;			/* �ް��\�����A�e�ݸ�̐擪�����̾�� */
	word	emp;			/* �ް��\�����A�e�ݸ�̏I������(+1)�̾�� */
}LNKIDX;


/************************************************/
/*              �O���[�o���ϐ�                  */
/************************************************/
extern byte			DBname[16];		/* �g�p��DB̧�ٖ��� */
extern byte			DBfc;			/* �ݽİٍς�DB̧�ِ�(0�`2) */
extern byte			DicStatus;
extern byte			dlp[];
extern byte			dic_en;			/* �����ް����ذ */
extern byte			dic_sben;		/* �����ް���޴��ذ */

/*extern LFILE_BUF far	FileBuf;		/* FLASH BIOS�p�ް��ޯ̧ */
extern LFBUF far	Ibuf;			/* FLASH BIOS�p�ް��ޯ̧1 */
extern LFBUF far	Dbuf;			/* FLASH BIOS�p�ް��ޯ̧2 */
extern LFBUF far	Gbuf;			/* FLASH BIOS�p�ް��ޯ̧3 */
/*extern FILE_INFO		FileInf;		/* FLASH BIOS�p�ް����  */
extern FILE_INFO	Iinf;			/* FLASH BIOS�p�ް����1 */
extern FILE_INFO	Dinf;			/* FLASH BIOS�p�ް����2 */
extern FILE_INFO	Ginf;			/* FLASH BIOS�p�ް����3 */

extern LSTIDX		lip[L_LNC];		/* ؽĕ\���s���ޯ�� */
extern LSTIDX		sdp[];			/* �ް��\�����ޯ������ */
extern LSTIDX		lnkdp;			/* �ݸ�ް��\�����ޯ�� */
extern long			tidxc;			/* ���ٲ��ޯ������ */
extern XT_SCR_POS	DicLstScr;		/* ؽĕ\���p��۰��ް */
extern int			lcp;			/* ؽĕ\�������߲��� */
extern bool			srcflg;			/* ����׸� */
extern byte			srcbf[];		/* ����ޯ̧ */
extern int			srclen;			/* ��������� */
extern bool			MesDone;		/* ү���ޕ\���ς݋敪 */
extern bool			passed;			/* 1�b�o�ߋ敪 */
extern byte far		*dttop;			/* ���ޯ��ް��J�n���ڽ */
extern word			sel_sp;			/* �I���J�n���� */
extern word			sel_ep;			/* �I���I������ */
extern word			rsp;			/* ���]�J�n���� */
extern word			rep;			/* ���]�I������ */
extern SHWIDX		dltp[D_LNC+2];	/* �s�擪�߲��� */
extern DSPCT		wtct;			/* �P��擪��� */
extern word			topfp;			/* �����ް�TOP̧���߲��� */
extern byte			idxsp;			/* ���ޯ�������߲��� */
extern long			tidxc;			/* ���ٲ��ޯ������ */
extern word			ttopbk;			/* ���ٲ��ޯ���߲���(��ۯ�) */
extern word			ttopof;			/* ���ٲ��ޯ���߲���(�̾��) */
extern word			gidxc;			/* ���̨�����ޯ������ */
extern word			gtopbk;			/* ���̨�����ޯ���߲���(��ۯ�) */
extern word			gtopof;			/* ���̨�����ޯ���߲���(�̾��) */
extern long			lidxc;			/* �ݸ���ޯ������ */
extern word			ltopbk;			/* �ݸ���ޯ���߲���(��ۯ�) */
extern word			ltopof;			/* �ݸ���ޯ���߲���(�̾��) */

#define	IBUF_A		(LFILE_BUF far *)(&Ibuf)
#define	DBUF_A		(LFILE_BUF far *)(&Dbuf)
#define	GBUF_A		(LFILE_BUF far *)(&Gbuf)

/************************************************/
/*              far �ر                         */
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

extern word srcgid[];				/* ������͎��޲��ݽð��� */

extern byte far headtop[];			/* DB̧�َ��ʺ��� */

extern byte far MeshArrow[2][28];		/* �Ԋ|����Ԃ̖�� */
extern byte far DBwinM[];			/* DB�I����޳����Ͻ� */
extern byte far ShowTopBtn[];		/* �ް��\���擪�s���� */
extern byte far loupe[];			/* ���ݓ��̒��ዾ���̨�� */
extern byte far micn[];				/* ��ʍ���Ӱ�ޱ��� */
extern byte far PullCal[];			/* �߯�߱��ߓd�앜�A������(�����) */
extern byte far PushCal[];			/* �߯�߱��ߓd�쉟�������� */
extern byte far PullClk[];			/* �����������ݕ��A������(�����) */
extern byte far PushClk[];			/* �����������݉��������� */
extern byte far DBChgBtn[2][28];	/* �����؂�ւ����� */
extern byte far DBnameFrame[];		/* �������\���g */

extern word PdEdt[];		/* [Edit] �ƭ��ްү���� */
extern word PdSys[];		/* [System] �ƭ��ްү���� */
extern word PdOpt[];		/* [Option] �ƭ��ްү���� */


/************************************************/
/*              �v���g�^�C�v�錾                */
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
