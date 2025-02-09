/******************************************************************************
	[����]
		Referencer

	[�@��]
		�ʐM�d�q�蒠(�C�O)

	[�T�v]
		Referencer ���C��

	[�쐬��]
		��ؖΐl

	Copyright (C) 2000 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#include	<stdrom.h>
#include	"define.h"
#include	"libc.h"
#include	"L_define.h"
#include	"L_libc.h"

#include	"SD_main.h"


byte			DicStatus;				/* ��ԕϐ� */
byte			dlp[16];

LFBUF far		Ibuf;			/* FLASH BIOS�p�ް��ޯ̧1 */
LFBUF far		Dbuf;			/* FLASH BIOS�p�ް��ޯ̧2 */
LFBUF far		Gbuf;			/* FLASH BIOS�p�ް��ޯ̧3 */
FILE_INFO		Iinf;			/* FLASH BIOS�p�ް����1 */
FILE_INFO		Dinf;			/* FLASH BIOS�p�ް����2 */
FILE_INFO		Ginf;			/* FLASH BIOS�p�ް����3 */

byte			DBname[DBN_LEN+1];	/* �g�p��DB̧�ٖ��� */
byte			DBfc;				/* �ݽİٍς�DB̧�ِ�(0�`2) */



/*HEAD*/
/******************************************************************************
	[����]
		���C������

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void main(void)
/*TAIL*/
{
	DicStatus	= ST_MODEINI;

	for(;;){

		switch(DicStatus){

		/******************************/
		/*      �����ݒ�              */
		/******************************/
			case ST_MODEINI:			/* Ӱ�ޏ����ݒ� */
				DicInit();
				break;

		/******************************/
		/*      ��������ؽĕ\��       */
		/******************************/
			case ST_LFILEINI:				/* ̧�ُ����ݒ� */
				DicLstFileInit();
				break;

			case ST_LTCHINI:			/* ��������ݒ� */
				DicLstTchInit();
				break;

			case ST_LBKDSP:				/* �w�i�`�� */
				DicLstBk();
				break;

			case ST_LDATASET:			/* ���ޯ���߲������ */
				DicLstDataSet();
				break;

			case ST_LDATADSP:			/* ؽ��ް��\�� */
				DicLstDisp();
				break;

			case ST_LTCHIDLE:			/* ����҂� */
				DicLstTchIdle();
				break;

		/******************************/
		/*      ���������ް��\��      */
		/******************************/
			case ST_SINI:				/* ������ */
				DicShowInit();
				break;

			case ST_SBKDSP:				/* �w�i�`�� */
				DicShowBk();
				break;

			case ST_SDATADSP:			/* �\���ް���� */
				DicShowDataDsp();
				break;

			case ST_SSBARDSP:			/* �\���ް���� */
				DicShowSbarDsp();
				break;

			case ST_STCHIDLE:			/* ����҂� */
				DicShowTchIdle();
				break;

		/******************************/
		/*      �������������        */
		/******************************/
			case ST_IINI:				/* �����ݒ� */
				DicSrcInit();
				break;

			case ST_ILOOP:				/* ������������ */
				DicSrcInput();
				break;

		/******************************/
		/*      ���̑�                */
		/******************************/
			default:					/* �ð���װ */
				DicStatus = ST_MODEINI;	/* Fale Safe */
				break;
		}
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		����Ӱ�ޏ�����

	[����]		�Ȃ�
	[�߂�l]	�Ȃ�
******************************************************************************/
void DicInit(void)
/*TAIL*/
{
	byte	sben;
	byte	dbn[DBN_LEN+1];

	DBfc = 0;						/* �Ƃ肠����DB̧�ق͖��� */
	srcflg = FALSE;					/* initial��� */
	srcbf[0] = 0;					/* ����ޯ̧������ */
	dic_sben = 0xff;
	DBname[0] = 0;

	if(LibGetSubEntNum()>0){		/* �o�^�ς�հ�ް̧�ق��������� */

		/* �擪DB̧�ق̖��̎擾 */
		for(sben=1; sben<=15; sben++){
			if(GetDicFileName(sben,dbn)>0){	/* DB̧�ٔ����� */
				DBfc ++;
				if(DBfc==1){		/* �擪DB̧�ٖ��擾 */
					dic_sben = sben;
					strcpy(DBname,dbn);
				}else if(DBfc>1){	/* DB̧�ق��Q�ȏ゠������... */
					break;
				}
			}
		}
	}

	if(DBfc>0){						/* DB̧�ق�1�ł���������... */
		FilePointerInit();			/* ̧���߲��������� */
		DicHeadRead();				/* DBͯ�ް�ǂݍ��� */
	}

	/*** ؽĕ\����۰��ް�����ݒ� ***/
	DicLstScr.x		= L_EDX+3;		/* ��۰��ް�ʒu(X)  */
	DicLstScr.y		= L_STY+1;		/* ��۰��ް�ʒu(Y)  */
	DicLstScr.size	= L_EDY-L_STY-5;/* ��۰��ް����     */
	DicLstScr.dsp	= L_LNC;		/* �\������         */
	DicLstScr.pos	= 0;			/* ��۰��ް�����ʒu */

	DicStatus	= ST_IINI;			/* �������͂� */
}


/*HEAD*/
/******************************************************************************
	[����]
		�����ް��ް�̧�ٖ��擾

	[����]
		byte	sben		: in	��޴��ذ�ԍ�
		byte	*fname		: out	DB����

	[�߂�l]
		DB̧�ٖ��̕����񒷁i0:�Y��̧�ق͎���DB�ł͂Ȃ��j

	[�����׽]
	[�������e]
		Ibuf��հ�ް̧�ق�ǂݍ��݁A����DB�Ȃ��DB���̂��擾����
******************************************************************************/
byte GetDicFileName(byte sben, byte *fname)
/*TAIL*/
{
	bool	len = 0;
	byte	uf[16];				/* հ�ް̧�ٖ��ǂݏo���p */

	/* ��޴��ذ�ԍ�����հ�ް̧�ٖ��擾 */
	if(LibGetSubEntrySt(uf, sben) == TRUE){

		if(uf[0]!=NULL){
			if(FileTopRead(sben,FALSE)==TRUE){		/* �擪̧�ٓǂݍ��� */
				fname[0] = NULL;					/* �Ƃ肠���� */
				if(far_memcmp(&Ibuf.bin_buf[0],headtop,JC_LEN)==0){
													/* ͯ�ް������m�F */
					far_strcpy(fname,(&Ibuf.bin_buf[0])+OFS_FNAME);
													/* DB���擾 */
					len = strlen(fname);
				}
			}
		}
	}
	return(len);
}


/*HEAD*/
/******************************************************************************
	[����]
		����DB,ͯ�ް̧�ٓǂݍ���

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void DicHeadRead(void)
/*TAIL*/
{
	/* ͯ�ް̧�ٓǂݍ��� */
	if(FileTopRead(dic_sben,TRUE)==TRUE){
		topfp = Iinf.fp;					/* �����ް�TOP̧���߲����擾 */
		tidxc = *((long far *)(&Ibuf.bin_buf[0]+OFS_TIDXC));
											/* ���ٲ��ޯ�����擾 */
		ttopbk = *((word far *)(&Ibuf.bin_buf[0]+OFS_TTOP));
											/* ���ٲ��ޯ���擪��ۯ��擾 */
		ttopof = *((word far *)(&Ibuf.bin_buf[0]+OFS_TTOP+2));
											/* ���ٲ��ޯ���擪�̾�Ď擾 */
		gtopbk = *((word far *)(&Ibuf.bin_buf[0]+OFS_GTOP));
											/* ���̨�����ޯ���擪��ۯ��擾 */
		gtopof = *((word far *)(&Ibuf.bin_buf[0]+OFS_GTOP+2));
											/* ���̨�����ޯ���擪�̾�Ď擾 */
		gidxc = *((word far *)(&Ibuf.bin_buf[0]+OFS_GIDXC));
											/* ���̨�����ޯ�����擾 */
		ltopbk = *((word far *)(&Ibuf.bin_buf[0]+OFS_LTOP));
											/* ���̨�����ޯ���擪��ۯ��擾 */
		ltopof = *((word far *)(&Ibuf.bin_buf[0]+OFS_LTOP+2));
											/* ���̨�����ޯ���擪�̾�Ď擾 */
		lidxc = *((word far *)(&Ibuf.bin_buf[0]+OFS_LIDXC));
											/* ���̨�����ޯ�����擾 */
		lcp = 0;							/* ؽĶ����߲��������� */

	}else{
		DBname[0] = NULL;					/* ̧�ٖ��̸ر */
		tidxc = 0;							/* ���ޯ�����ر */
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		̧�ِ擪�����ǂݍ���

	[����]
	[�߂�l]
		TRUE	:	����I��
		FALSE	:	�ǂݍ��ݴװ

	[�������e]
******************************************************************************/
bool FileTopRead(byte sben, bool all)
/*TAIL*/
{

	byte		fname[16];
	bool		jdg = FALSE;
	byte		mode_entry, sub_entry;

	if(sben==0xff)
		return(jdg);

	/* ��޴��ذ�ԍ�����̧�ٖ��擾 */
	if(LibGetSubEntrySt(fname, sben)==TRUE){

		/* ̧�ٖ������ذ���ޤ��޴��ذ���擾 */
		if(LibGetAllEntry(fname, &mode_entry, &sub_entry)==TRUE){

			/* ̧�ِ擪ں��޻�� */
			FilePointerInit();						/* �擪̧�قɐݒ� */
			FbufInit(mode_entry,sub_entry,&Ibuf);	/* ���ޯ���ޯ̧������ */
			FbufInit(mode_entry,sub_entry,&Dbuf);	/* �ް��ޯ̧������ */
			FbufInit(mode_entry,sub_entry,&Gbuf);	/* ���̨���ޯ̧������ */

			if(LibLFileFindNext(IBUF_A,&Iinf,0x00)==TRUE){

				if(all==TRUE)
		/*			jdg = LibLFileRead(&FileBuf,&FileInf);		*/
					jdg = DicFileRead(&Ibuf,&Iinf);
				else
				/* ̧�ِ擪ں���256byte�̂ݓǂݍ��� */
					jdg = LibLFileReadEx(IBUF_A,&Iinf, 4);
			}
		}
	}
	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[����]
		̧���ޯ̧������

	[����]
		LFBUF far	*f_buf		:out	FLASH BIOS�p�ް��ޯ̧

	[�߂�l]
		�Ȃ�

	[�������e]
		Flashײ���ؗp���ޯ̧������������.

******************************************************************************/
void FbufInit(byte en, byte sben, LFBUF far *f_buf)
/*TAIL*/
{
	f_buf->fsb_main_entry_		= en;			/* Ӱ�޴��ذ���ް     */
	f_buf->fsb_sub_entry_		= sben;			/* ��޴��ذ���ް      */

	f_buf->fsb_scrt_info_		= 0x80;			/* �����/���گď��   */
	f_buf->fsb_ararm_chk_		= 0x00;			/* �װ��������       */
	f_buf->fsb_todo_chek_		= 0x04;			/* TODO�������       */
	f_buf->fsb_todo_rank_		= 0xff;			/* TODO�ݸ���        */
	f_buf->fsb_date1_buf_[0]	= 0;			/* ���t/�������t      */
	f_buf->fsb_date2_buf_[0]	= 0;			/* �������t           */
	f_buf->fsb_date_aram_[0]	= 0;			/* �װѓ��t           */
	f_buf->fsb_time1_buf_[0]	= 0;			/* �J�n/��������      */
	f_buf->fsb_time2_buf_[0]	= 0;			/* �I��/��������      */
	f_buf->fsb_time3_buf_[0]	= 0;			/* ��������           */
	f_buf->fsb_time_aram_[0]	= 0;			/* �װю���           */
	f_buf->fsb_date_srch_[0]	= 0;			/* ���t����p�ޯ̧     */
	f_buf->fsb_time_srch_[0]	= 0;			/* ���Ի���p�ޯ̧     */
	f_buf->fsb_text_srch_[0]	= 0;			/* ����p�ޯ̧         */

	f_buf->dummy_16by[0]		= 0;			/* ��؍�����а        */
	f_buf->char_num				= 0;			/* �޲�ذ�ް��޲Đ�   */
	f_buf->bin_buf[0]			= 0;			/* ���ް��ޯ̧(�޲��) */
}


/*HEAD*/
/******************************************************************************
	[����]
		����ر ���

	[����]
	[�߂�l]
	[�������e]
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
	[����]
		�����I����޳�\��

	[����]
	[�������e]
******************************************************************************/
void DicDBSelWinBk(void)
/*TAIL*/
{
	LibPutGraph(0,13,DBnameFrame);		/* DB���̘g */
	if(DBfc<2)							/* DB̧�ق�2�ȏ�̎� */
		LibPutGraph(126,13,DBwinM);		/* DB����޳Ͻ� */
	LibPutProStr(IB_PFONT1,3,15,DBname,121);	/* DB���̕\�� */
}


/*HEAD*/
/******************************************************************************
	[����]
		�����I����޳����

	[����]
	[�������e]
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

	if(DBfc<2)			/* DB̧�ق�2�����̎� */
		return(FALSE);

	if(btn==TRUE){
		if(LibIconClick(&TicnDBSel,tsts)==FALSE)
			return(FALSE);
	}

	/* DB̧�ٖ��ꗗ�擾 */
	for(j=0,lc=0,sben=1; sben<=15; sben++){	/* �o�^�ςݑSհ�ް̧�ق�� */
		i = GetDicFileName(sben,&cmnt[j]);
		if(i>0){
			jdg = TRUE;			/* DB̧�ٖ��擾���� */ 
			j += i;
			cmnt[j] = 0xfe;
			j ++;
			rtv[lc] = sben;			/* "LibSelWindow" �߂�l */
			if(sben==dic_sben)		/* ���ݎg�p����DB̧�ق̎� */
				dft = lc;			/* ��̫�Ĕ��]�ʒu */
			lc++;
		}
	}
	cmnt[j] = 0xff;					/* �I�[�t�� */
	rtv[lc] = 0xff;					/* �I�[�t�� */

	/*** �I����޳���� ***/
	win_prm.x	 =   -1;
	win_prm.y	 =   23;
	win_prm.xs	 =  128;
	win_prm.t_xs =    3;
	win_prm.ity	 =    9;
	win_prm.np	 =    dft;			/* ��̫�Ĕ��]�ʒu */
	win_prm.cmnt = &cmnt[0];		/* �\������ð��َw�� */
	win_prm.rtv  = &rtv[0];			/* �߂�lð��َw�� */

	if(lc>15)						/* �װ�̎� */
		return(FALSE);
	else if(lc==15)					/* DB��15�̎� */
		win_prm.y -= 5	;			/* ����޳�J�n�ʒu���グ�� */

	sel_ret = LibSelWindowExt(&win_prm);	/* �I����޳ */
	if(sel_ret!=0xff){
		dic_sben = sel_ret;			/* DB̧�ٕύX */
		FilePointerInit();			/* �S�߲����擪̧�قɐݒ� */
		GetDicFileName(dic_sben,&DBname[0]);
		DicHeadRead();				/* DBͯ�ް�ǂݍ��� */

	/*	DicStatus = ST_IINI;		/* �������͂� */
		return(TRUE);
	}
	return(FALSE);
}


