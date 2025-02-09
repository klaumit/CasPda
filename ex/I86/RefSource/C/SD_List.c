/******************************************************************************
	[����]
		Referencer ؽĕ\��

	[�@��]
		ZX400 Referencer

	[�T�v]
		ؽĕ\�������Q

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

XT_SCR_POS	DicLstScr;			/* ؽĕ\���p��۰��ް */
byte		dic_en;				/* �����ް����ذ */
byte		dic_sben;			/* �����ް���޴��ذ */
word		topfp;				/* �����ް�TOP̧���߲��� */
LSTIDX		lip[L_LNC];
LSTIDX		sdp[DCTSPMAX];		/* �ް��\�����ޯ�������ر */
LSTIDX		lnkdp;				/* �ݸ�ް��\�����ޯ�� */
long		tidxc;				/* ���ٲ��ޯ������ */
word		ttopbk;				/* ���ٲ��ޯ���߲���(��ۯ�) */
word		ttopof;				/* ���ٲ��ޯ���߲���(�̾��) */
word		gidxc;				/* ���̨�����ޯ������ */
word		gtopbk;				/* ���̨�����ޯ���߲���(��ۯ�) */
word		gtopof;				/* ���̨�����ޯ���߲���(�̾��) */
long		lidxc;				/* �ݸ���ޯ������ */
word		ltopbk;				/* �ݸ���ޯ���߲���(��ۯ�) */
word		ltopof;				/* �ݸ���ޯ���߲���(�̾��) */
int			lcp;				/* ؽĕ\�������߲��� */
bool		MesDone;			/* ү���ޕ\���ς݋敪 */
bool		passed;				/* 1�b�o�ߋ敪 */


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\��̧�ُ�����

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_LFILEINI

	[�������e]
******************************************************************************/
void DicLstFileInit(void)
/*TAIL*/
{
	/*** ؽĕ\����۰��ް�����ݒ� ***/
	DicLstScr.pos	= 0;				/* ��۰��ް�����ʒu */
	lcp = 0;							/* ���ُ����ʒu */
	DicStatus = ST_LTCHINI;					/* ����������� */
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\�����������

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_LTCHINI

	[�������e]
******************************************************************************/
void DicLstTchInit(void)
/*TAIL*/
{
	if(srcflg!=TRUE)
		DicLstScr.vol = tidxc;			/* ��۰��ް�S�̗ʂͲ��ޯ������ */

	LibTchStackClr();					/* ����ر������ */
	LibTchInit();
	TchComSet();
	LibTchStackPush(TchListArea);		/* ؽĴر ���ð��� */
	LibTchStackPush(TchDBSel);			/* ����DB�I���������ð��� */
	LibTchStackPush(TchLoupe);			/* ���ዾ��������ر */
	LibTchStackPush(TchActionKey);		/* ����ݷ�  ���ð��� */

	DicStatus = ST_LBKDSP;					/* �w�i�`��� */
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\���w�i�`��

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_LBKDSP

	[�������e]
******************************************************************************/
void DicLstBk(void)
/*TAIL*/
{
	LibClrDisp();						/* ��ʏ��� */

	LibLine(   1,  13, 158,   1,  1);	/* �w�i�\��(���ِ�) */
	LibLine(   1,  29, 158,   1,  1);	/* �w�i�\��(���) */
	LibLine(   1, 159, 158,   1,  1);	/* �w�i�\��(����) */

	LibLine(   0,  14,   1, 145,  1);	/* �w�i�\��(����) */
	LibLine( 147,  30,   1, 129,  1);	/* �w�i�\��(����) */
	LibLine( 159,  14,   1, 145,  1);	/* �w�i�\��(�E��) */

	if(srcflg==TRUE)
		LibPutFarData( 0, 0, 96);		/* ���㒎�ዾ���ݕ\�� */
	else
		LibPutGraph(0,1,micn);			/* ����Ӱ�ޱ��� */

	LibPutFarData(98,0,44);				/* ���ዾ���ݱ���   */
	LibPutGraph(108,1,loupe);			/* ���ዾ�̊G */
	LibModeIconDsp();					/* Pop Up Tools */
	DicDBSelWinBk();					/* DB���̘g�\�� */

	DicStatus	= ST_LDATASET;				/* ؽ��ް��\���� */
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\���ް����

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_LDATASET

	[�������e]
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

  /*-- ��ڰ�������ُ�����(Esc�͌��Ȃ�) --*/
	LibBkSampleInitSub(NULL,0x00);
	MesDone = FALSE;					/* ү���ޕ\���ς݋敪 = �� */
	passed	= FALSE;					/* 1�b�o�ߋ敪 = �� */
	s_cnt	= 0;

	/** �擪�s�w�� **/
	ovf = DicLstScr.pos + DicLstScr.dsp - DicLstScr.vol;
	if((ovf>0)&&(DicLstScr.pos>0)){		/* ؽĉ����ɋ󔒍s���ł��鎞 */
		if(DicLstScr.pos<ovf)			/* �ް�������ؽĕ\���s����菬������ */
			ovf = DicLstScr.pos;
		DicLstScr.pos -= ovf;
		lcp += ovf;						/* ���ټ�� */
	}

	/***** ����ٻ���d�l�폜 *****/
	/*	if(srcflg!=TRUE){
	/*		lip[0].num = DicLstScr.pos;
	/*	}else{
	/*		if(GenSrc2(DicLstScr.pos, &lip[0])==FALSE)
	/*			lip[0].num = 0;
	/*	}
	*/
		lip[0].num = DicLstScr.pos;
	/****************************/

	if(GetIndex(&lip[0],0)==FALSE)		/* ���ޯ���ԍ����擪�s�ް��擾 */
		lip[0].num = 0xffffffff;

	for(i=1;i<L_LNC;i++){

		/*--- ��ڰ�������ُ��� ---*/
		LibBkSampleCheck(&passed);
		if(passed)	DicWaitingMes();	/* "Please Wait..." */

		/*--- ESC ������ݏ��� ---*/
	/*	if( (++s_cnt) >=SCHK_CNT ){
	/*		if( DicTchEscScan() ){
	/*			LibWinIcnMsg(ICON_BIKKURI,387,2);	/* Stopped! */
	/*			DicStatus = ST_IINI;		/* �������͉�ʂ� */
	/*			return;
	/*		}
	/*		s_cnt = 0;
	/*	}
	*/

		lwk = lip[i-1];
		if(lwk.num!=0xffffffff){

		/*** ����ٻ���d�l�폜 ***/
		/*	if(srcflg==TRUE)			/* ����ٻ���� */
		/*		jdg = NxtGenSrc(&lwk,srclen);
		/*	else
		/*		jdg = GetNxtTitleIndex(&lwk);
		*/
			jdg = GetNxtTitleIndex(&lwk);
		/************************/

			if(jdg==FALSE)				/* ���s���ٲ��ޯ���ް��擾 */
				lwk.num = 0xffffffff;
		}
		lip[i] = lwk;
	}

	DicStatus	= ST_LDATADSP;				/* ؽ��ް��\���� */

	#undef SCHK_CNT
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽ��ް��\��

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_LDATADSP

	[�������e]
******************************************************************************/
void DicLstDisp(void)
/*TAIL*/
{
	byte		i;

	LibClrBox(L_STX-1,L_STY-1,L_EDX-L_STX+1,L_ITY*L_LNC-1);
										/* ؽĴر��ʏ��� */
	for(i=0;i<L_LNC;i++){
		if(lip[i].num!=0xffffffff)
			Lst1DataDsp(i);				/* �ꌏ�\�� */
		if(i<L_LNC-1)
			LibMeshLine(L_STX-1,L_STY+L_ITY*(i+1)-2,L_EDX-L_STX+2,1);
										/* �s��؂�_���\�� */
	}

	DLibScrollPrint(DicLstScr);			/* ��۰��ް�\�� */

	DicStatus	= ST_LTCHIDLE;			/* ����҂��� */
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\���P���ް����

	[����]
		byte	ln;		�ް���ؽĕ\���s�ʒu(0�`L_LNC-1)

	[�߂�l]
	[�������e]
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

	if(DicDataRead(&lip[ln],&tgt)==FALSE)		/* �ް��ǂݍ��� */
		return;

	xp = L_STX;
	yp = L_STY+L_ITY*ln;

	lmt = i = 0;
	while(loop==TRUE){
		if(i>TT_LEN){
			loop = FALSE;
			break;
		}
		ccd = JdgContCode(&tgt);			/* ���亰�ޔ��f */
		switch(ccd){

			case CD_CHA:		/* �������ށu00h�`7Fh�v */
			case CD_OVCHA:		/* 1�޲ĺ��ގw��(0x80�ȏ�)�u@\x??�v */
				nw = LibGetProFontSize(IB_PFONT1,*tgt);	/* ���������擾 */
				if((xp+nw+DOT3>= L_EDX)&&(lmt==0))
					lmt = i;				/* �...��}���ʒu�ޔ� */
				if(xp+nw>= L_EDX){			/* ��s�ɕ\�����؂�Ȃ������ꍇ */
					i = lmt;
					for(j=0;j<3;j++){		/* �...��\�� */
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

			case CD_FNT57:		/* 5x7̫�Ďw��        �u@\fNM�v */
			case CD_FNTPN:		/* ����߰����̫�Ďw�� �u@\fPN�v */
			case CD_FNTPB:		/* ������̫�Ďw��     �u@\fPB�v */
				break;

		/*	case CD_RTN:		/* ���s���ށu0Dh�v */
		/*	case CD_END:		/* �I������(�����o��)�u@\T�v */
			default:			/* Fail Safe */
				loop = FALSE;
				break;
		}
	}

	tmp[i]=NULL;
	LibPutProStr(IB_PFONT1,L_STX,yp,tmp,L_EDX-L_STX);	/* ��s�\�� */
	return;
}


/*HEAD*/
/******************************************************************************
	[����]
		���ޯ���擾

	[����]
		LSTIDX	*lidx		: ؽĲ��ޯ���\����
			lidx.num			in	�擾���ޯ���ԍ�
			lidx.flp			out	�Y�����ޯ���߲����̊܂܂��̧���߲���
			lidx.ofs			out	�Y�����ޯ���߲����̵̾��

		byte	type		: in	�擾���ޯ�����
										0:Title
										1:Link
	[�߂�l]
		TRUE	: ����I��
		FALSE	: �Y�����ޯ���͑��݂��Ȃ�

	[�������e]
		num�Ԗڂ̲��ޯ����Ă���
******************************************************************************/
bool GetIndex(LSTIDX *lidx, byte type)
/*TAIL*/
{
	byte	ityp;
	word	ofs, flp,tblk,tofs;
	long	bict,num,idxc;

	if(type==0){			/* Title���ޯ�����Ώۂ̎� */
		ityp = IT_TITLE;
		tblk = ttopbk;
		tofs = ttopof;
		idxc = tidxc;
	}else{					/* Link���ޯ�����Ώۂ̎� */
		ityp = IT_LINK;
		tblk = ltopbk;
		tofs = ltopof;
		idxc = lidxc;
	}

	num = lidx->num;
	if(num>idxc-1)
		return(FALSE);			/* ���ޯ���������ް */

	flp = topfp + tblk;			/* ���ٲ��ޯ���擪���܂܂��̧�� */
	bict = (SZ_BLOCK-tofs)/8;
	ofs = tofs;

	while(1){
		if(bict<=num){
			num -= bict;
			flp ++;
		}else{
			if(DicIndexFileRead(flp)!=TRUE)		/* ���ޯ��̧�ٓǂݏo�� */
				return(FALSE);
			break;
		}
		bict = SZ_BLOCK/8;
		ofs = 0;
	}

	ofs += num*8;

	if(Ibuf.bin_buf[ofs] != ityp)		/* ���ޯ��������� */
		return(FALSE);

	lidx->flp = flp;					/* ̧���߲����w�� */
	lidx->ofs = ofs;					/* �̾�Ďw�� */
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[����]
		�����ٲ��ޯ���擾

	[����]
		LSTIDX	*lidx		: in	����ؽĲ��ޯ���\����
			lidx.num					���ݲ��ޯ���ԍ�
			lidx.flp					���ݲ��ޯ���߲����̊܂܂��̧���߲���
			lidx.ofs					���ݲ��ޯ���߲����̵̾��

	[�߂�l]
		FALSE	: �Y�����ޯ���͑��݂��Ȃ�
		TRUE	: ����I��

		LSTIDX	*lidx		: out	��ؽĲ��ޯ���\����
			lidx.num					�����ޯ���ԍ�
			lidx.flp					�����ޯ���߲����̊܂܂��̧���߲���
			lidx.ofs					�����ޯ���߲����̵̾��

	[�������e]
		�������ٲ��ޯ���̱��ڽ���擾����

******************************************************************************/
bool GetNxtTitleIndex(LSTIDX *lidx)
/*TAIL*/
{
	word	flp,ofs;
	long	num;

	num = lidx->num;				/* ����ؽĲ��ޯ���\���̎擾 */
	flp = lidx->flp;
	ofs = lidx->ofs;

	if((num >= tidxc-1)||(num == 0xffffffff)){
		num = 0xffffffff;
		return(FALSE);
	}

	/* ���߲����������߲����Ɠ���̧�قɗL�鎞 */
	if(ofs+8 < SZ_BLOCK){
		if(DicIndexFileRead(flp)!=TRUE)
			return(FALSE);
		ofs += 8;

	/* ���߲����������߲����Ɠ���̧�قɖ����� */
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
	[����]
		�O���ٲ��ޯ���擾

	[����]
		LSTIDX	*lidx		: in	����ؽĲ��ޯ���\����
			lidx.num					���ݲ��ޯ���ԍ�
			lidx.flp					���ݲ��ޯ���߲����̊܂܂��̧���߲���
			lidx.ofs					���ݲ��ޯ���߲����̵̾��

	[�߂�l]
		LSTIDX	*lidx		: out	�OؽĲ��ޯ���\����
			lidx.num					�O���ޯ���ԍ�
			lidx.flp					�O���ޯ���߲����̊܂܂��̧���߲���
			lidx.ofs					�O���ޯ���߲����̵̾��

		TRUE	: ����I��
		FALSE	: �Y�����ޯ���͑��݂��Ȃ�

	[�������e]
		�O�����ٲ��ޯ���̱��ڽ���擾����

******************************************************************************/
bool GetPrvTitleIndex(LSTIDX *lidx)
/*TAIL*/
{
	bool	jdg = FALSE;
	word	flp,ofs;
	long	num;

	num = lidx->num;				/* ����ؽĲ��ޯ���\���̎擾 */
	flp = lidx->flp;
	ofs = lidx->ofs;

	if(num <= 0)
		return(FALSE);

	/* �O�߲����������߲����Ɠ���̧�قɗL�鎞 */
	if(ofs != 0){
		jdg = TRUE;
		if(DicIndexFileRead(flp)!=TRUE)
			return(FALSE);
		ofs -= 8;

	/* �O�߲����������߲����Ɠ���̧�قɖ����� */
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
	[����]
		ؽĕ\�� ����҂�

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_LTCHIDLE

	[�������e]
******************************************************************************/
void DicLstTchIdle(void)
/*TAIL*/
{
	TCHSTS	tsts;
	int		revl,lcbk;
	int		mklc;				/* ؽĕ\�������߲����ޔ�ر */
	bool	jdg;
	long	posbk;
	byte	amsk;
	TXTP	tp;
	bool	arw = TRUE;

	revl = lcp;
	posbk = DicLstScr.pos;
	while(DicStatus==ST_LTCHIDLE){

		/* ��۰��ް�㉺���Ԋ|������ */
		if(arw==TRUE){
			DLibScrollArrowPrint(DicLstScr,SCR_NO_MASK);
			amsk = LstArrowMask(&DicLstScr);
			DLibScrollArrowPrint(DicLstScr,amsk);
			arw = FALSE;
		}

		LstCsrDsp(lcp);					/* ���]���ٓ_�� */
		LibPutDisp();					/* ��ʍX�V */
		LibTchWait( &tsts );			/* ����҂� */

		lcbk = lcp;
		switch(tsts.obj){

			case OBJ_LPSW_UP:		/* ����ݷ� Up */
				if(LstCsrUpChk(&DicLstScr)==TRUE){
					if(LstScBarUp(&DicLstScr)==TRUE){
						DicStatus = ST_LDATADSP;	/* ��ʏ������� */
					}
				}else{
					LibRepOff();	/* ��߰� Off */
				}
				break;

			case OBJ_LPSW_DOWN:		/* ����ݷ� Down */
				if(LstCsrDwnChk(&DicLstScr)==TRUE){
					if(LstScBarDwn(&DicLstScr)==TRUE){
						DicStatus = ST_LDATADSP;	/* ��ʏ������� */
					}
				}else{
					LibRepOff();	/* ��߰� Off */
				}
				break;

			case OBJ_LPSW_PUSH:		/* ����ݷ� Push */
				idxsp = 0;				/* �\������p���Ұ��߲��������� */
				sdp[idxsp] = lip[lcp];	/* ���ޯĐݒ� */
				DicStatus = ST_SINI;	/* �ް��ڍו\���� */
				break;

			case OBJ_IC_DBSEL:		/* DB Select */
				if(DicDBSelWin(&tsts,TRUE)==TRUE)
					DicStatus = ST_LFILEINI;
				break;

			case OBJ_SCR_BAR:		/* ScrollBar */
				arw = DicLstScBar(&tsts,posbk);
				break;

			case OBJ_AR_LIST:		/* List �ر */
				jdg = LstCsrMv(&tsts,&revl);		/* ؽĶ��وړ����� */
				if(jdg==TRUE){
					DicStatus	= ST_LTCHIDLE;		/* ���ٍĕ\���� */
					if(tsts.act==ACT_MAKE){			/* make�� */
						mklc = lcp;
					}else if(tsts.act==ACT_BREAK){	/* break�� */
						if(mklc==revl){				/* makeײ݂���ڲ��� */
							idxsp = 0;				/* �\������p���Ұ��߲��������� */
							sdp[idxsp] = lip[mklc];	/* ���ޯĐݒ� */
							DicStatus	= ST_SINI;	/* �ް��ڍו\���� */
						}
					}
					lcp = revl;				/* ���]���وړ� */
					arw = TRUE;
				}
				break;

			case OBJ_IC_SRCKEY:				/* ���ዾ���� */
				DicSrcBtn(&tsts);			/* ������͂� */
				break;

			case OBJ_HIC_ESC:
				if(srcflg==TRUE){
					DicLstScr.pos = lip[lcp].num;	/* ؽĐ擪�s�� */
					lcp = 0;				/* ���ق�擪�s�� */
					DicStatus = ST_LTCHINI;	/* ؽčĕ\�� */
					srcflg = HALF;			/* ������� */
				}else{
					DicStatus = ST_IINI;	/* ��������͂�(÷�ď������͂��Ȃ�) */
				}
				break;

			case OBJ_HIC_MBAR:		/* �ƭ��ްʰ�ޱ��� */
				DicPdwnSet();				/* ����޳��ƭ��\���ݒ� */
				if(DicPdwnFnc(&tp)==TRUE)	/* ����޳ݏ��� */
					return;
				break;

			default:
				DicStatus = ST_LTCHIDLE;			/* NOP */
				break;
		}
		LstCsrDsp(lcbk);					/* ���]���ُ��� */
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\���̔��]���ق�\���i�����j����

	[����]
		int		lc		: in	���ٕ\��(����)�s�ʒu �i0�`�j

	[�������e]
******************************************************************************/
void LstCsrDsp(int lc)
/*TAIL*/
{
	LibReverse(2, 30+lc*10, 144,9);	/* ؽĶ��� ���]�\�� */
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\�������۰��ް�����������
	[����]
	[�߂�l]
		TRUE	: ��۰٤�܂��Ͷ��وړ���
		FALSE	: NOP��

	[�������e]
******************************************************************************/
bool DicLstScBar(TCHSTS *tsts, long posbk)
/*TAIL*/
{
	int		ans;
	bool	ret = FALSE;

	ans = DLibScrPosCheck(*tsts,DicLstScr);
	if(ans==0){					/* �㽸۰ٷ������ */
		if(LstCsrUpChk(&DicLstScr)==FALSE)
			return(ret);			/* ��ړ��s�̎� */

	}else if(ans==1){			/* ����۰ٷ������ */
		if(LstCsrDwnChk(&DicLstScr)==FALSE)
			return(ret);			/* ���ړ��s�̎� */
	}

	ans = DLibScrollClick(tsts,&DicLstScr);

	switch(ans){
		case 0:					/* �㽸۰ٷ������ */
			if(tsts->act==ACT_BREAK_IN){
				ret = TRUE;
				if(LstScBarUp(&DicLstScr)==TRUE){
					DicStatus = ST_LDATADSP;	/* ��ʏ������� */
				}
			}
			break;

		case 1:					/* ����۰ٷ������ */
			if(tsts->act==ACT_BREAK_IN){
				ret = TRUE;
				if(LstScBarDwn(&DicLstScr)==TRUE){
					DicStatus = ST_LDATADSP;	/* ��ʏ������� */
				}
			}
			break;

		case 2:					/* ��۰��ް��� & ��ׯ�ގ� */
			if(posbk!=DicLstScr.pos){
				lcp += (posbk - DicLstScr.pos);
				if(lcp>=L_LNC)
					lcp = L_LNC - 1;
				else if(lcp<0)
					lcp = 0;
				ret = TRUE;
				DicStatus = ST_LDATASET;			/* �S��ʏ������� */
			}
			break;
	}
	return(ret);
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\��������ى������ړ��\����

	[�߂�l]
		TRUE	: ���ى������ړ��\
		FALSE	: ���ى������ړ��s��
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
	[����]
		ؽĕ\��������ُ�����ړ��\����

	[�߂�l]
		TRUE	: ���ُ�����ړ��\
		FALSE	: ���ُ�����ړ��s��
******************************************************************************/
bool LstCsrUpChk(XT_SCR_POS *scr)
/*TAIL*/
{
	if(lcp==0 && scr->pos==0)
		return(FALSE);			/* �ړ��s�� */
	return(TRUE);				/* �ړ��\ */
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\�������۰��ް UP�������������

	[�߂�l]
		TRUE	: ���وړ��ɂ�齸۰ٔ���
		FALSE	: ��۰ٖ�����

	[�������e]
******************************************************************************/
bool LstScBarUp(XT_SCR_POS *scr)
/*TAIL*/
{
	byte		i;
	LSTIDX		lwk;
	bool		jdg = FALSE;

	/** ���ݤ���ق�2�s�ڈȍ~�̎� **/
	if(lcp>0){
		if(lip[lcp-1].num!=0xffffffff){
			lcp--;
		}

	/** ���ݤ���ق��擪�s�̎� **/
	}else{
		lwk = lip[0];
		if(GetPrvTitleIndex(&lwk)==TRUE){	/* �O���ޯ���߲������ */
			for(i=L_LNC-2;;i--){
				lip[i+1] = lip[i];		/* ؽ��߲��� ���Down */
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
	[����]
		ؽĕ\�������۰��ް Down�������������

	[�߂�l]
		TRUE	: ���وړ��ɂ�齸۰ٔ���
		FALSE	: ��۰ٖ�����

	[�������e]
******************************************************************************/
bool LstScBarDwn(XT_SCR_POS *scr)
/*TAIL*/
{
	byte		i;
	LSTIDX		lwk;
	bool		jdg = FALSE;

	/** ���ݤ���ق��ŉ��s�ȊO�̎� **/
	if(lcp<L_LNC-1){
		if(lip[lcp+1].num!=0xffffffff){
			lcp++;
		}

	/** ���ݤ���ق��ŉ��s�̎� **/
	}else{
		lwk = lip[L_LNC-1];
		if(GetNxtTitleIndex(&lwk)==TRUE){	/* ���ް���� */
			for(i=0;i<L_LNC-1;i++){
				lip[i] = lip[i+1];	/* ؽ��߲��� ���Up */
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
	[����]
		����ؽĕ\�����AؽĴر ���������

	[����]
		TCHSTS	*tsts	: in		����ð��
		int		*revl	: in/out	���]���ٍs�ʒu(0�`)

	[�߂�l]
		TRUE	: �L���ر�������
		FALSE	: �����ر�����

	[�������e]
		���وړ��A�܂����ް��\���ւ̑J�ڂ��s���B
******************************************************************************/
bool LstCsrMv(TCHSTS *tsts, int *revl)
/*TAIL*/
{
	byte	sel;

	sel = SelLstTchLn(tsts->x,tsts->y);		/* ����Y���s�Z�o */
	if(sel==0xff || lip[sel].num==0xffffffff)	/* �ر����O�ꂽ�� */
		return(FALSE);							/* ���]ײ݂͂��̂܂� */

	*revl = sel;						/* ���]�ʒu�X�V */
	return(TRUE);
}



/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\�����A������s�Z�o
	[����]
	[�߂�l]
		����ʒu�̍s���i0,1,2... FFh��ؽĴر�O�j

	[�������e]
		ؽĕ\����ʏ��������ꂽ�ӏ����A��ʏ�ŉ����ڂł��邩�Z�o����
******************************************************************************/
byte SelLstTchLn(word xp, word yp)
/*TAIL*/
{
	word	i,ly;

	if(xp<L_STX-1 || L_EDX<xp)				/* ���ɊO��Ă��鎞 */
		return(0xff);
	if(yp<L_STY-1 || L_EDY<yp)				/* �c�ɊO��Ă��鎞 */
		return(0xff);

	for(ly=L_STY-1,i=0; i<L_LNC-1; i++){
		ly += L_ITY;
		if(ly>yp)
			break;
	}
	return(i);
}


