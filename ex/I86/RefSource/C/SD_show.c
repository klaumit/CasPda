/******************************************************************************
	[����]
		Referencer

	[�@��]
		�ʐM�d�q�蒠(�C�O)

	[�T�v]
		Referencer �ް��ڍו\��

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

XT_SCR_POS	DicDataScr;			/* �ް��\���p��۰��ް */
XT_SCR_POS	LinkDataScr;		/* Link�ް��\���p��۰��ް */
byte far	*dttop;				/* ���ޯ��ް��J�n���ڽ */
DSPCT		dctrl;				/* �\������p���Ұ� */
DSPCT		lctrl;				/* �\������p���Ұ�2 */
byte		idxsp;				/* ���ޯ�������߲��� */
byte		ttn[TT_LEN+4];		/* �ް����ٖ� */
word		sel_sp;				/* �I���J�n���� */
word		sel_ep;				/* �I���I������ */
word		rsp;				/* ���]�J�n���� */
word		rep;				/* ���]�I������ */
bool		lktch;				/* �ݸ������׸� */
bool		jprv;				/* �ݸ������]���׸� */
bool		jprvbk;				/* �ݸ������]���׸ޑޔ�ر */
byte far	*lnksp;				/* �ݸ�J�n�߲��� */
byte far	*lnkep;				/* �ݸ�I���߲���(+1) */
DSPCT		ddct;				/* �\������p���Ұ� */

/*HEAD*/
/******************************************************************************
	[����]
		�ް��\��������

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_SINI

	[�������e]
******************************************************************************/
void DicShowInit(void)
/*TAIL*/
{
	/*** ����ر�ݒ� ***/
	LibTchStackClr();
	LibTchInit();
	TchComSet();						/* ����ر������ */
	LibTchStackPush(TchDtHead);			/* �擪�s��������ر */
	LibTchStackPush(TchLoupe);			/* ���ዾ��������ر */
	LibTchStackPush(TchDicShow);		/* �ް��\��������ر */
	LibTchStackPush(TchActionKey);		/* ����ݷ�  ���ð��� */

	/*** ��۰��ް�����ݒ� ***/
	DicDataScr.x	= D_EDX+3;			/* ��۰��ް�ʒu(X) */
	DicDataScr.y	= D_STY+1;			/* ��۰��ް�ʒu(Y) */
	DicDataScr.size	= D_EDY-D_STY-3;	/* ��۰��ް���� */
	DicDataScr.dsp	= D_LNC;			/* �\������     */
	sdp[idxsp].pos	= 0;				/* �擪�s����\�� */

	DicStatus	= ST_SBKDSP;			/* �w�i�\���� */
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\���w�i�`��

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_SBKDSP

	[�������e]
******************************************************************************/
void DicShowBk(void)
/*TAIL*/
{
	byte far	*tgt;
	long		vol;
	DSPCT		dctwk;

	SelRevOff();						/* ���]�׸މ��� */
	LibClrDisp();						/* ��ʏ��� */

	LibLine(1,13,158,1,1);				/* �w�i�\��(���) */
	LibLine(1,159,158,1,1);				/* �w�i�\��(����) */

	LibLine(  0,14,1,145,1);			/* �w�i�\��(����) */
	LibLine(147,14,1,145,1);			/* �w�i�\��(����) */
	LibLine(159,14,1,145,1);			/* �w�i�\��(�E��) */

	LibModeIconDsp();					/* Pop Up Tools */
	LibPutGraph(0,1,micn);				/* ����Ӱ�ޱ��� */

	LibPutGraph(14,0,ShowTopBtn);		/* �擪�s���� */
	if(idxsp<=0)						/* ���ޯ����������̎� */
		LibGdsMesh(69,0,94,11);			/* Back���݂͖Ԋ|�� */

	LibPutFarData(98,0,44);				/* ���ዾ���ݱ���   */
	LibPutGraph(108,1,loupe);			/* ���ዾ�̊G */

	if(DicDataRead(&sdp[idxsp],&tgt)==FALSE){	/* ���ޯ��ް��ǂݍ��� */
		DicStatus = ST_MODEINI;			/* Fail Safe */
		return;
	}
	dttop = tgt-3;						/* �{���J�n���ڽ */

	/*** ��۰��ް�����ݒ� ***/
	dctwk.x		= D_STX;
	dctwk.sx	= D_STX;
	dctwk.sy	= D_STY;
	dctwk.ex	= D_EDX;
	dctwk.ey	= D_EDY;
	dctwk.ity	= D_ITY;
	vol = GetDicDspL(dttop,&dctwk);		/* �S�̏c���擾(�s��) */
	DicDataScr.vol	= vol;				/* ��۰��ް�S�̗� */
	DicDataScr.pos	= sdp[idxsp].pos;	/* ��۰��ް�����ʒu */

	DicStatus	= ST_SDATADSP;			/* �\���ް���Ă� */
}


/*HEAD*/
/******************************************************************************
	[����]
		�\���ް����

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_SDATADSP

	[�������e]
******************************************************************************/
void DicShowDataDsp(void)
/*TAIL*/
{
	int			ltc;				/* �ް��\���J�n�s�ʒu */

	LibGdsClr(D_STX-D_SFTX*2,D_STY,D_EDX-1,D_EDY-1);	/* �g����ʏ��� */

	/*** �\�������ʒu�ݒ� ***/
	ddct.sx		= D_STX;
	ddct.sy		= D_STY;
	ddct.ex		= D_EDX;
	ddct.ey		= D_EDY;
	ddct.lnc	= D_LNC;
	ddct.fnt	= IB_PFONT1;
	ddct.ity	= D_ITY;
	ddct.pot 	= dttop;				/* �ޯ̧�擪 */
	ddct.lkpt	= dttop;				/* �Ƃ肠�����ݸ���� */
	ddct.jpf	= FALSE;				/* �Ƃ肠�����ެ��ߖ��� */
	ddct.st		= 0;					/* �Ƃ肠�����ʏ핶�� */
	ltc = DicDataScr.pos;
	DicDspTopSrc(&ddct, ltc);			/* �\���J�n�ʒu��� */

	dctrl = ddct;						/* ��ʐ擪���Ұ��ޔ� */
/*	if(dctrl.lkpt < dctrl.pot)
/*		lkpsp = 0;
*/
	DicDltpClear(&ddct);				/* �s���Ұ������� */
	DicTxtDsp(&ddct);					/* �w��s�ʒu�����ʕ\�� */

	DicStatus	= ST_SSBARDSP;			/* ��۰��ް�\���� */
}

/*HEAD*/
/******************************************************************************
	[����]
		�ް��\����۰��ް���

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_SSBARDSP

	[�������e]
******************************************************************************/
void DicShowSbarDsp(void)
/*TAIL*/
{
	DLibScrollPrint(DicDataScr);		/* ��۰��ް�\�� */

	/** BIOS�޸ޑ΍� **/
	LibGdsClr(D_EDX,D_STY,D_EDX+2,D_EDY-1);	/* ��۰��ް������ʏ��� */
	LibLine(147,14,1,145,1);				/* �w�i�\��(����) */

	/** �O���ް����Ԋ|������ **/
	if(sdp[idxsp].num<=0)					/* �擪�ް��\���� */
		LibPutGraph(14+29,0,MeshArrow[0]);	/* �O�ް����Ԕ����\�� */
	if(sdp[idxsp].num>=tidxc-1)				/* �ŏI�ް��\���� */
		LibPutGraph(14+42,0,MeshArrow[1]);	/* ���ް����Ԕ����\�� */

	DicStatus	= ST_STCHIDLE;				/* ����҂��� */
}


/*HEAD*/
/******************************************************************************
	[����]
		�\���J�n�ʒu���

	[����]
		DSPCT		*dct	: in/out	
		int			tlc		: ÷�ďc��(D_ITY)����s�Ƃ��āA�\���J�n�s��

	[�������e]
		÷�ďc��(D_ITY)����s�Ƃ��āA�w��s������۰ق�������Ԃ�
		�\���J�n�ް��߲����A�y�ѕ\���J�n���W(Y)���擾����
******************************************************************************/
void DicDspTopSrc(DSPCT *dct, int tlc)
/*TAIL*/
{
	int 		lc, lcbk;
	byte far	*ltop;

	/*** �\��ٰ�� ***/
	lc = lcbk = 0;
	for(;;){
		ltop = dct->pot;
		dct->y = dct->sy;
		if(DicDsp1L(dct,FALSE)==FALSE)	/* ��s������ */
			break;

	/* ����÷�čs�����擾 */
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
	[����]
		�ް��\���s���Ұ�������

	[����]
	[�߂�l]
	[�������e]
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
	[����]
		÷�ĕ\��Ҳ�

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void DicTxtDsp(DSPCT *dct)
/*TAIL*/
{
	int		i,j;
	word	gt;
	word	ntop;			/* �ް��\���I�����̾�� */

	AdjustStartX(dct);		/* �\���J�n�����W�ݒ� */

	/*** �\��ٰ�� ***/
	while(1){
		if(dct->y>=dct->sy){
			j = (dct->y-dct->sy)/dct->ity;
			if(j>dct->lnc){
				break;					/* Fale Safe */
			}
			dltp[j].ofs = (word)(dct->pot - dttop);		/* �s���߲������ */
			dltp[j].fnt = dct->fnt;						/* �s������̫�ľ�� */
			dltp[j].lnk = (word)(dct->lkpt - dttop);	/* �s���ݸ��� */
			dltp[j].jpf = dct->jpf;						/* �ެ��ߏ�Ծ�� */
			dltp[j].st  = dct->st;						/* �s��������Ծ�� */
		}
		if(dct->y >= dct->sy+D_ITY*dct->lnc){		/* ���ʕ��\���I�� */
			break;
		}
		if(DicDsp1L(dct,TRUE)==FALSE)	/* ��s������ */
			break;						/* �I�����ޔ����� */
	}
	ntop = (word)(dct->pot - dttop);

	/* �摜�r���s��܂����ް����ȍ~�s�߲����ݒ� */
	gt = ntop;			/* �Ƃ肠������ʐ擪 */
	for(i=dct->lnc-1;i>=0;i--){
		if(dltp[i].ofs==0xffff)		/* �Ώۍs�H */
			dltp[i].ofs = ntop;		/* ���擪���߰ */
		else
			ntop = dltp[i].ofs;		/* ���擪�߲������X�V */
	}
	return;
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\���J�nX���W����

	[����]
	[�߂�l]
	[�������e]
		�ް��\���̍ہA�\���J�nX���W�𒲐�����B
		�ʏ�́ustx�v�����A���o��(�����o��)��\�����͍���12�ޯ�(6�ޯ�)
		��Ă�����B
******************************************************************************/
void AdjustStartX(DSPCT *dct)
/*TAIL*/
{
	dct->x = dct->sx;				/* �ʏ�͕\���J�n�ݒ�l���̂܂� */

	if(dct->st==1 || dct->st==2)	/* ���o��������o���̎� */
		dct->x -= dct->st*D_SFTX;	/* �J�n���W�����ɼ�� */
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\�� ����҂�

	[����]
	[�߂�l]

	[�����׽]
		�����		DicStatus = ST_STCHIDLE

	[�������e]
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
	byte far	*dttopbk;			/* ���ޯ��ް��J�n���ڽ�ޔ�ر */

	dct = dctrl;					/* ��ʐ擪���Ұ��߂� */

	/* ��۰��ް�㉺���Ԋ|������ */
	DLibScrollArrowPrint(DicDataScr,SCR_NO_MASK);
	amsk = DataArrowMask(&DicDataScr);
	DLibScrollArrowPrint(DicDataScr,amsk);

	while(DicStatus==ST_STCHIDLE){

		DicRevDisp(&dct);				/* �I�𔽓]�\�� */
		LibPutDisp();					/* ��ʍX�V */
		LibTchWait( &tsts );			/* ����҂� */
		DicRevDisp(&dct);				/* �I�𔽓]���� */

		switch(tsts.obj){

			case OBJ_LPSW_UP:			/* ����ݷ� Up */
				if(ChkScrlDwn(&DicDataScr)==TRUE){
					DicDataScr.pos --;
					SelRevOff();			/* ���]�׸މ��� */
					DicShowScrDwn();			/* ��۰ٱ��ߏ��� */
					DicStatus	= ST_SSBARDSP;	/* ��۰��ް�\���� */
					if(ChkScrlDwn(&DicDataScr)!=TRUE){
						LibRepOff();			/* ��߰� Off */
						LibTchInit();
					}
				}else{
					DicPrevBtn(&tsts,FALSE);
					LstCsrAdjust();				/* ؽĶ��ْ��� */
					LibRepOff();				/* ��߰� Off */
					LibTchInit();
				}
				break;

			case OBJ_LPSW_DOWN:			/* ����ݷ� Down */
				if(ChkScrlUp(&DicDataScr)==TRUE){
					DicDataScr.pos ++;
					SelRevOff();				/* ���]�׸މ��� */
					DicShowScrUp();				/* ��۰ٱ��ߏ��� */
					DicStatus	= ST_SSBARDSP;	/* ��۰��ް�\���� */
					if(ChkScrlUp(&DicDataScr)!=TRUE){
						LibRepOff();			/* ��߰� Off */
						LibTchInit();
					}
				}else{
					DicNextBtn(&tsts,FALSE);
					LstCsrAdjust();				/* ؽĶ��ْ��� */
					LibRepOff();				/* ��߰� Off */
					LibTchInit();
				}
				break;

			case OBJ_LPSW_PUSH:			/* ����ݷ� Push */
				LibCallListMenu();			/* Action Menu�� */
				break;

			case OBJ_SCR_BAR:			/* ScrollBar */
				ret = DicShowScBar(&tsts, &DicDataScr);
				if(ret==1){					/* ��۰��ް�����݂̎� */
					SelRevOff();				/* ���]�׸މ��� */
					DicShowScrDwn();			/* ��۰��޳ݏ��� */
					DicStatus	= ST_SSBARDSP;	/* ��۰��ް�\���� */

				}else if(ret==2){			/* ��۰��ް�����݂̎� */
					SelRevOff();				/* ���]�׸މ��� */
					DicShowScrUp();				/* ��۰ٱ��ߏ��� */
					DicStatus	= ST_SSBARDSP;	/* ��۰��ް�\���� */

				}else if(ret==3){			/* ���or��ׯ�ގ� */
					SelRevOff();				/* ���]�׸މ��� */
					DicStatus = ST_SDATADSP;	/* �ް��ĕ\�� */
				}
				break;

			case OBJ_AR_SHOW:			/* �\���ر */
				jdg = DicShowAreaTch(&tsts,&dct);	/* �ݸ��ެ��ߊY������? */
				if(jdg!=FALSE){				/* �ݸ�ެ��ߔ��� */
					DicRevDisp(&dct);				/* �����(�ް��\��)�I�𔽓]�\�� */
					ret = GetLinkIndex(jdg);		/* �ݸ�ެ��ߐ���ޯ���擾 */

					if(ret==1){				/* �ެ��߂̎� */
						DicStatus = ST_SBKDSP;		/* �\���ް��X�V */

					}else if(ret==2){		/* �ݸ�̎� */
						dttopbk	= dttop;			/* �ް��J�n���ڽ�ޔ� */
						DicLinkShowDsp();			/* �ݸ�ް��\�� */
						if(DicStatus!=ST_IINI)		/* ������͈ڍs���ȊO��... */
							DicStatus = ST_SBKDSP;	/* �ް��ĕ\�� */
						dttop	= dttopbk;			/* �ް��J�n���ڽ�߂� */

					}else{					/* ���ޯ����������t�̎� */
						LibWinIcnMsg(ICON_BIKKURI,500,1);
													/* ��b�\���"����ȏ�ެ��߂ł��܂���I" */
						DicRevDisp(&dct);			/* �����(�ް��\��)�I�𔽓]�߂� */
					}
				}
				break;

			case OBJ_HIC_ESC:
				if(idxsp==0){				/* �ʏ��ް��\���� */
					if(jprv!=FALSE){				/* ���]���Ȃ� */
						SelRevOff();				/* ���]�׸މ��� */
					}else{
						LstCsrAdjust();				/* ؽĶ��ْ��� */
						DicStatus = ST_LTCHINI;		/* ؽĕ\���� */
					}
				}else{						/* Jump����ް��\���� */
					DicBackBtnSub();				/* �O��\���ް��� */
				}
				break;

			case OBJ_IC_SRCKEY:
				DicSrcBtn(&tsts);
				break;

			case OBJ_IC_LSTKEY:
				if(LibBlockIconClick(&TicnDtLst,&tsts,B_ICON_LEFT)==TRUE){
					LstCsrAdjust();					/* ؽĶ��ْ��� */
					DicStatus = ST_LTCHINI;			/* ؽĕ\���� */
				}
				break;

			case OBJ_IC_PRVKEY:		/* "��"�� */
				DicPrevBtn(&tsts,TRUE);
				LstCsrAdjust();				/* ؽĶ��ْ��� */
				break;

			case OBJ_IC_NXTKEY:		/* "��"�� */
				DicNextBtn(&tsts,TRUE);
				LstCsrAdjust();				/* ؽĶ��ْ��� */
				break;

			case OBJ_IC_BCKKEY:		/* "��"�� */
				DicBackBtn(&tsts);
				break;

			case OBJ_HIC_MBAR:		/* �ƭ��ްʰ�ޱ��� */
				DicRevDisp(&dct);			/* �I�𔽓]�\�� */
				DicPdwnSet();				/* ����޳��ƭ��\���ݒ� */
				DicPdwnFnc(&tp);			/* ����޳ݏ��� */
				DicRevDisp(&dct);			/* �I�𔽓]���� */
				break;
		}
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\����۰ٱ���

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void DicShowScrUp(void)
/*TAIL*/
{
	SHWIDX		swk;				/* �\������p���Ұ� */
	DSPCT		dct;
	int			i, stl, cysp;

	/* �s���Ұ���� */
	swk = dltp[0];
	for(i=1;i<D_LNC;i++){			/* ��ʉ��s�ͼ�Ă��Ȃ� */
		dltp[i-1] = dltp[i];
	}

	for(i=D_LNC-1;i<=D_LNC;i++){	/* ��ʖ��s������ */
		dltp[i].ofs = 0xffff;
		dltp[i].fnt = 0xff;
		dltp[i].lnk = 0xffff;
		dltp[i].st  = 0;
	}

	/* ��ʕ\���J�n�s���Ұ��߂� */
	dctrl.sx	= D_STX;
	dctrl.sy	= D_STY;
	dctrl.ex	= D_EDX;
	dctrl.ey	= D_EDY;
	dctrl.lnc	= D_LNC;
	dctrl.ity	= D_ITY;

	if(dltp[0].fnt!=0xff){		/* �擪�s����\���\�Ȏ� */
		dctrl.fnt	= dltp[0].fnt;
		dctrl.pot 	= dttop+dltp[0].ofs;
		dctrl.lkpt	= dttop+dltp[0].lnk;
		dctrl.jpf	= dltp[0].jpf;
		dctrl.st	= dltp[0].st;
		dctrl.y		= D_STY;
	}else{						/* �擪�s���O����\�����鎞 */
		if(swk.fnt!=0xff){		/* -1�s����\�����鎞 */
			dctrl.fnt	= swk.fnt;
			dctrl.pot 	= dttop+swk.ofs;
			dctrl.lkpt	= dttop+swk.lnk;
			dctrl.jpf	= swk.jpf;
			dctrl.st	= swk.st;
			dctrl.y		= D_STY;
		}
		dctrl.y -= D_ITY;
	}

	/* �\���J�n�s�ʒu��� */
	for(stl=D_LNC-2;stl>=0;stl--){
		if(dltp[stl].fnt!=0xff){
			swk = dltp[stl];	/* ÷�Ă�����s����͸��̨���J�n�s����\���J�n */
			break;
		}
	}

	/* �ŉ��s�\�� */
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
								/* ��۰ٱ��� */
	}
	LibGdsClr(D_STX-D_SFTX*2, cysp, D_EDX, D_EDY-1);	/* ��ʸر */
	DicTxtDsp(&dct);			/* �w��s�ʒu�����ʕ\�� */
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\����۰��޳�

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void DicShowScrDwn(void)
/*TAIL*/
{
	int			i;
	SHWIDX		swk;
	DSPCT		dct;
	byte		lc;

	LibGrpDwn(D_STX-D_SFTX*2, D_STY, D_EDX-(D_STX-D_SFTX*2), D_EDY-D_STY, D_ITY);
									/* ��۰��޳� */
	/* �s���Ұ���� */
	for(i=D_LNC;i>0;i--){
		dltp[i] = dltp[i-1];
	}
	dltp[0].ofs = 0xffff;
	dltp[0].fnt = 0xff;
	dltp[0].lnk = 0xffff;
	dltp[0].st  = 0;

	if(dctrl.y<dctrl.sy){			/* �擪�s���O����\�����Ă����� */
		dctrl.y		+= D_ITY;
		dct			= dctrl;

	}else{
		swk = dltp[1];
		lc = PrvLineTop(&swk);		/* �O�s�擪��� */

		/*** �\�������ʒu�ݒ� ***/
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
	DicTxtDsp(&dct);			/* ��ʐ擪�s����\�� */
}


/*HEAD*/
/******************************************************************************
	[����]
		�O�s�擪���

	[����]
		SHWIDX	*swk	: in/out	���ݍs�擪/�O�s�擪���Ұ�

	[�߂�l]
		�O�s�\���c���K�v�s�� ��� (÷�Ă݂̂̍s�Ȃ�΂P)
									�װ���A�O
	[�������e]
******************************************************************************/
byte PrvLineTop(SHWIDX *swk)
/*TAIL*/
{
	DSPCT		dctemp;
	int			lc;
	byte far	*ntop;

	ntop = dttop+swk->ofs;
	PrvRtnTopSrc(swk,ntop);		/* �������s���ޑO����� */

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
		if(DicDsp1L(&dctemp,FALSE)==FALSE)	/* ��s������ */
			return(0);						/* Fale Safe */
		if(dctemp.pot>=ntop)
			break;
	}

	lc = (dctemp.y - D_STY)/D_ITY;
	return(lc);
}


/*HEAD*/
/******************************************************************************
	[����]
		�������s���ޑO�����

	[����]
	[�߂�l]
	[�������e]
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

	swk->ofs = 0;			/* �Ƃ肠���� */
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
					loop = FALSE;		/* ٰ�ߏI�� */
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

			case CD_CHA:			/* �������ށu00h�`7Fh�v */
			case CD_OVCHA:			/* 1�޲ĺ��ގw��(0x80�ȏ�)�u@\x??�v */
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

			case CD_LKDEF:			/* �ݸ�w��u@\l+������(1byte)�v */
			case CD_JPDEF:			/* �ެ��ߎw��u@\j+������(1byte)�v */
				llnk = tgt-dttop+(*tgt)+1;
				tgt ++;
				break;

			case CD_GPDEF:			/* �摜�w��u@\g????�v */
				tgt += 2;
				break;
		}
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\�����A���]�׸މ���
	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void SelRevOff(void)
/*TAIL*/
{
	jprv = FALSE;				/* �ݸ�I���׸޸ر */
	sel_sp = sel_ep = 0xffff;	/* ���]�\������ */
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\����ؽĕ\������وʒu����
	[����]
	[�߂�l]
	[�������e]
		�����ް��\�������ް���ؽĉ�ʓ��ɍ݂鎞�ɂ͂����ɶ��ق�
		�ړ������A�����Aؽď�ɖ����ꍇ�ɂͽ�۰ق����ĉ�ʓ���
		���ق��ړ�������B
******************************************************************************/
void LstCsrAdjust(void)
/*TAIL*/
{
	long	nownum;
	int		i;

	nownum = sdp[idxsp].num;

	/*** �ʏ���ް��\������̖߂�̏ꍇ ***/
	if(idxsp==0){

		/* ؽĔ͈͂��O(��)���ް��̎� */
		if(nownum<lip[0].num){
			DicLstScr.pos = nownum;
			lcp = 0;				/* ���ق͐擪�s */

		/* ؽĔ͈͂���(��)���ް��̎� */
		}else if((lip[L_LNC-1].num<nownum)&&(lip[L_LNC-1].num!=0xffffffff)){
			DicLstScr.pos += nownum - lip[L_LNC-1].num;
			lcp = L_LNC-1;			/* ���ق͍ŉ��s */

		/* ؽĔ͈͓��ɍ݂��ް��̎� */
		}else{
			lcp = 0;				/* �Ƃ肠���� (Fale Safe) */
			for(i=0;i<L_LNC;i++){
				if(lip[i].num==nownum){
					lcp = i;
					return;
				}
			}
		}

	/*** �ެ��ߐ悩��̖߂�̏ꍇ ***/
	}else{
		DicLstScr.pos = nownum;
		lcp = 0;				/* ���ق͐擪�s */
	}

	lip[0].num = DicLstScr.pos;
	for(i=1;i<L_LNC;i++){
		lip[i].num = lip[i-1].num + 1;
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\�������۰��ް�����������

	[����]
	[�߂�l]
		0	: ��ʖ��ύX
		1	: �㽸۰ٷ�
		2	: ����۰ٷ�
		3	: ��۰��ް��� or ��ׯ��

	[�������e]
******************************************************************************/
byte DicShowScBar(TCHSTS *tsts, XT_SCR_POS *scr)
/*TAIL*/
{
	int		ans;
	byte	type = 0;

	ans = DLibScrPosCheck(*tsts,*scr);
	if(ans==0){					/* �㽸۰ٷ������ */
		if(ChkScrlDwn(scr)==FALSE)
			return(type);					/* ��ړ��s�̎� */

	}else if(ans==1){			/* ����۰ٷ������ */
		if(ChkScrlUp(scr)==FALSE)
			return(type);					/* ���ړ��s�̎� */
	}

	ans = DLibScrollClick(tsts,scr);
	switch(ans){
		case 0:					/* �㽸۰ٷ������ */
			if(tsts->act==ACT_BREAK_IN){
				if(scr->pos > 0){
					(scr->pos)--;
					type = 1;
				}
			}
			break;

		case 1:					/* ����۰ٷ������ */
			if(tsts->act==ACT_BREAK_IN){
				if(scr->pos < scr->vol - scr->dsp){
					(scr->pos)++;
					type = 2;
				}
			}
			break;

		case 2:					/* ��۰��ް��� & ��ׯ�ގ� */
			type = 3;
			break;

		default:
			break;
	}
	return(type);
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\������㽸۰ى\����

	[�߂�l]
		TRUE	: ��۰ى\
		FALSE	: �s��
******************************************************************************/
bool ChkScrlUp(XT_SCR_POS *scr)
/*TAIL*/
{
	if(scr->pos >= scr->vol - scr->dsp){
		return(FALSE);		/* �ŉ��s�\�����͕s�� */
	}
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\���������۰ى\����

	[�߂�l]
		TRUE	: ��۰ى\
		FALSE	: �s��
******************************************************************************/
bool ChkScrlDwn(XT_SCR_POS *scr)
/*TAIL*/
{
	if(scr->pos == 0){
		return(FALSE);		/* �擪�s�\�����͕s�� */
	}
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\�����Prev���ݏ���

	[�߂�l]
******************************************************************************/
void DicPrevBtn(TCHSTS *tsts, bool btn)
/*TAIL*/
{
	long	tmp;

	if(sdp[idxsp].num<=0)			/* �擪�ް��\���� */
		return;

	if(btn==TRUE){
		if(LibBlockIconClick(&TicnDtPrv,tsts,B_ICON_CENTER)!=TRUE)
			return;
	}

	tmp = sdp[idxsp].num;				/* ���ݔԍ��ޔ� */

	idxsp =0;							/* ���ޯ�������ر */
	sdp[idxsp].num = tmp - 1;			/* �O�ް��� */
	GetIndex(&sdp[idxsp],0);			/* ���ޯ�����ڽ�擾 */
	sdp[idxsp].pos = 0;					/* �擪�s����\�� */

	DicStatus = ST_SBKDSP;				/* �\���ް��X�V */
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\�����Next���ݏ���

	[�߂�l]
******************************************************************************/
void DicNextBtn(TCHSTS *tsts, bool btn)
/*TAIL*/
{
	long	tmp;

	if(sdp[idxsp].num>=tidxc-1)			/* �ŏI�ް��\���� */
		return;

	if(btn==TRUE){
		if(LibBlockIconClick(&TicnDtNxt,tsts,B_ICON_CENTER)!=TRUE)
			return;
	}

	tmp = sdp[idxsp].num;				/* ���ݔԍ��ޔ� */

	idxsp =0;							/* ���ޯ�������ر */
	sdp[idxsp].num = tmp + 1;			/* ���ް��� */
	GetIndex(&sdp[idxsp],0);			/* ���ޯ�����ڽ�擾 */
	sdp[idxsp].pos = 0;					/* �擪�s����\�� */

	DicStatus = ST_SBKDSP;				/* �\���ް��X�V */
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\�����Back���ݏ���

	[�߂�l]
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
	[����]
		�ް��\�����Back���ݏ���2

	[�߂�l]
******************************************************************************/
void DicBackBtnSub(void)
/*TAIL*/
{
	idxsp --;
	DicStatus = ST_SBKDSP;		/* �\���ް��X�V */
}

/*HEAD*/
/******************************************************************************
	[����]
		�ް��\�����������ݏ���

	[�߂�l]
		TRUE	: ��۰ى\
		FALSE	: �s��
******************************************************************************/
void DicSrcBtn(TCHSTS *tsts)
/*TAIL*/
{
	bool	jdg;

	jdg = LibIconClick(&TicnLoupe,tsts);
	if(jdg==TRUE){
		srcbf[0] = NULL;		/* ÷���ޯ̧������ */
		DicStatus = ST_IINI;		/* ��������͂� */
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\��������]�I��\��

	[�߂�l]
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
		return;					/* �I�𔽓]�Ȃ� */

	dwk		= *dct;

	for(i=0;i<dwk.lnc;i++){

		if(dltp[i].fnt!=0xff){		/* ÷�Ă����݂���s�̎� */
			/* �s�擪�ݒ� */
			dwk.pot	= dttop + dltp[i].ofs;
			dwk.fnt	= dltp[i].fnt;
			dwk.lkpt= dttop + dltp[i].lnk;
			dwk.jpf	= dltp[i].jpf;
			dwk.st	= dltp[i].st;
			dwk.x	= dwk.sx;
			dwk.y	= dwk.sy + D_ITY*i;
			AdjustStartX(&dwk);		/* �\���J�n�����W�ݒ� */

			wtct = dwk;				/* �P��擪���Ƃ��đޔ� */

		/*	DicDsp1L(&dwk,FALSE);		/* ��s���� */
			while(1){					/* ��sٰ�� */
				jdg = DicDsp1C(&dwk,HALF,&ccd);	/* �ꕶ���\������ */
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
	[����]
		÷�Ĵر�����������
	[����]
	[�߂�l]
		TRUE	: �ݸ�������
		HALF	: �ެ����������
		FALSE	: �ݸ��ެ��ߖ�����(�ʏ�I��)

	[�������e]
******************************************************************************/
bool DicShowAreaTch(TCHSTS *tsts, DSPCT *dct)
/*TAIL*/
{
	word	mp, tmp1, tmp2, spbk;
	int		ln;
	bool	jdg = FALSE;

	ln = (tsts->y-dct->sy)/D_ITY;		/* ������W��÷�čs�� */
	GetTchMj(dct, tsts->x, ln, &mp);	/* ������W�Y�������擾 */

	switch(tsts->act){

		case ACT_MAKE:
			jprvbk = jprv;
			spbk = sel_sp;
			sel_sp = mp;
			sel_ep = mp;
			jprv = GetTchLink(&sel_sp,&sel_ep,ln);	/* �Y���ݸ�ر�擾 */
			if(spbk!=sel_sp)			/* ���]�������ς������ */
				jprvbk = FALSE;
			break;

		case ACT_MOVE_OUT:				/* ÷�Ĵر����O��čs������ */
			break;

		case ACT_BREAK:
			if(mp!=0xffff){
				tmp1 = sel_sp;
				tmp2 = mp;
				jprv = GetTchLink(&tmp1,&tmp2,ln);	/* �Y���ݸ�ر�擾 */
				if(jprv==FALSE){			/* �ݸ�ر�O������� */
					if(sel_sp==0xffff)
						sel_sp = mp;
					sel_ep = mp;
				}
			}
			if( sel_sp==sel_ep || sel_sp==0xffff || sel_ep==0xfffff ){
				sel_sp = sel_ep = 0xffff;
			}
			if((jprv!=FALSE)&&(jprv==jprvbk)){
				jdg = jprv;				/* �ݸ��ެ��ߔ��� */
			}
			break;

		case ACT_DOWN_IN:				/* ÷�Ĵر��������� */
			if(mp!=0xffff){
				tmp1 = sel_sp;
				tmp2 = mp;
				jprv = GetTchLink(&tmp1,&tmp2,ln);	/* �Y���ݸ�ر�擾 */
				if(jprv==FALSE){			/* �ݸ�ر�O������� */
					if(sel_sp==0xffff)
						sel_sp = mp;
					sel_ep = mp;
				}
			}
			break;

		case ACT_DOWN:					/* ÷�Ĵر�O������� */
			break;
	}

	/**** ��������ׯ�ގd�l�폜 ****/
	if(jprv==FALSE){
		sel_sp = sel_ep = 0xffff;
	}

	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[����]
		������ꂽ�������ް��擪����̵̾�Ă��擾

	[����]
		DSPCT	*dct	: in	�\������p���Ұ�
		int 	tx		: in	������W(X)
		int		ln		: in	����s�ʒu�i0�`�j
		word	*tgt	: out	�Y�������ް��擪����̵̾��

	[�߂�l]
		0	: �Y�������Ȃ�
		1	: �Y����������(�Y���ݸ��ެ��ߖ���)
		2	: �s�擪���O
		3	: �s�������
		4	: �Y���ݸ�L��

	[�������e]
******************************************************************************/
byte GetTchMj(DSPCT *dct, int tx, int ln, word *tgt)
/*TAIL*/
{
	DSPCT	dwk;
	byte	ccd;
	bool	jdg = TRUE;
	bool	ljflg = FALSE;

	lktch = FALSE;				/* �Ƃ肠����������N���� */
	*tgt = dltp[ln].ofs;		/* �Ƃ肠������s�擪 */

	if(dltp[ln].fnt==0xff){		/* �摜�r���s��܂����ް����ȍ~�s�̎� */
		return(0);
	}

	/* �s�擪�ݒ� */
	dwk		= *dct;
	dwk.pot	= dttop + dltp[ln].ofs;
	dwk.fnt	= dltp[ln].fnt;
	dwk.lkpt= dttop + dltp[ln].lnk;
	dwk.jpf	= dltp[ln].jpf;
	dwk.st	= dltp[ln].st;
	dwk.x	= dwk.sx;
	dwk.y	= dwk.sy + D_ITY*ln;
	AdjustStartX(&dwk);		/* �\���J�n�����W�ݒ� */

	wtct = dwk;				/* �P��擪���Ƃ��đޔ� */

	if(tx<dwk.x){
		return(2);			/* ����ʒu�͍s�擪���O */
	}

	*tgt = 0xffff;
	while(jdg==TRUE){
		jdg = DicDsp1C(&dwk,FALSE,&ccd);		/* �ꕶ���\������ */
		if(jdg==TRUE){			/* �s�r���̎� */
			if(tx<dwk.x){
				if(*tgt==0xffff){
					*tgt = (word)(dwk.pot-1-dttop);
					if(dwk.pot-1<dwk.lkpt){		/* �ݸ�ر���̎� */
						ljflg = TRUE;
						lnkep = dwk.lkpt;
					}
				}
			}

		}else if(jdg==HALF){	/* ���s�� */
			if(*tgt==0xffff){
				*tgt = (word)(dwk.pot-1-dttop);
				return(3);
			}

		}else{					/* �ް��I���� */
			if(*tgt==0xffff){
				*tgt = (word)(dwk.pot-dttop);
				return(3);
			}
		}
	}

	if(*tgt!=0xffff){				/* ܰ��ׯ�ߑΉ� */
		if((dwk.pot-dttop)<=*tgt){	/* ���s�擪�����o�����ʒu���O�̎� */
		/*	*tgt = dwk.pot-dttop;	/* ���s�擪���Y������ */
			*tgt = 0xffff;			/* �Y�������Ȃ� */
			return(0);
		}
	}else{
		return(0);
	}

	/** �Y�������L��̎� **/
	if(ljflg==TRUE){
		lktch = TRUE;			/* Link�L�� */
		return(4);
	}
	return(1);
}


/*HEAD*/
/******************************************************************************
	[����]
		��������A�Y���ݸ�ر�擾

	[����]
		word	*p1		: in/out	����J�n����/�Y���ݸ�J�n�����̾��
		word	*p2		: in/out	����I������/�Y���ݸ�J�n�����̾��
		byte	ln		: in		��������s�ʒu�i0 �` D_LNC-1�j

	[�߂�l]
		TRUE	: �Y���ݸ����
		HALF	: �Y���ެ��߂���
		FALSE	: �Y���ݸ��ެ��߂Ȃ�

	[�������e]
		���������ʏ�̕������ݸ�w�肳��Ă��邩���f����B
		Ҳ����́u*sp=*ep�v�ł��邱�ƁI
******************************************************************************/
bool GetTchLink(word *p1, word *p2, byte ln)
/*TAIL*/
{
	byte		cd,cdbk;
	int			i;
	byte far	*tgt;
	int			len;
	byte far	*lend;

	if((*p1!=0xffff)&&(*p2!=0xffff)){			/* ����Y����������H */

		if(lktch==TRUE){			/* �ݸ����H */

			/* �ݸ�J�n�ʒu��� */
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

					case CD_CHA:			/* �������ށu00h�`7Fh�v */
					case CD_OVCHA:			/* 1�޲ĺ��ގw��(0x80�ȏ�)�u@\x??�v */
						tgt++;
						break;

					case CD_GPDEF:			/* �摜�w��u@\g????�v */
						tgt += 2;
						break;

					case CD_LKDEF:			/* �ݸ�w��u@\l+������(1byte)�v */
					case CD_JPDEF:			/* �ެ��ߎw��u@\j+������(1byte)�v */
						tgt ++;
						lnksp = tgt;		/* �ݸ������J�n���ڽ(����) */
						lend = *(tgt-1)+tgt;	/* �ݸ�I�����ݒ� */
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
				if(lend!=0){				/* �ݸ�I����₪�ݒ肳��Ă��鎞 */
					if(lend==lnkep){			/* �ݸ�I���ʒu�ƈ�v������... */
						*p1 = lnksp-dttop;		/* ���]������J�n�̾�� */
						*p2 = lnkep-dttop;		/* ���]������I���̾�� */
						if(cdbk==CD_JPDEF)
							return(HALF);		/* �ެ��߂̎� */
						return(TRUE);			/* �ݸ�̎� */
					}
				}
			}
		}
	}
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[����]
		������ꂽ�ݸ�����̼ެ��ߐ�����߂�

	[����]
		bool	lj		: in	HALF : �ެ��ߕ�����������ꂽ��
								TRUE : �ݸ������������ꂽ��

	[�߂�l]
		0	: �ެ��ߕs��
		1	: ���ٲ��ޯ���ցi�ެ��߁j
		2	: �ݸ���ޯ���ցi�ݸ�j
	[�������e]
******************************************************************************/
byte GetLinkIndex(byte lj)
/*TAIL*/
{
	byte		ityp;
	int			len;
	byte		srcwd[TT_LEN+1];
	byte far	*tgt;

	/* ���������擾 */
	len = sel_ep-sel_sp;
	tgt = dttop+sel_sp;
	SelCharacter(srcwd,&tgt,len);			/* �������ނ𒊏o */
	sdp[idxsp].pos = DicDataScr.pos;		/* ���ݍs�ʒu�ޔ� */

	if(lj==TRUE){			/* Link�̎� */
		ityp = 1;			/* LinkIndex ���绰� */
	}else{					/* Jump�̎� */
		if(idxsp>=DCTSPMAX-1)
			return(0);		/* �ő�Jump�񐔵��ް */
		idxsp ++;			/* ���ޯ�������߲����X�V */
		ityp =0;			/* TitleIndex ���绰� */
	}
	DicIniSrc(&lnkdp.num,srcwd,strlen(srcwd),ityp,TRUE);
									/* ���ޯ���߲������ */
	GetIndex(&lnkdp,ityp);			/* ���ޯ�����ڽ�擾 */
	lnkdp.pos = 0;					/* �擪�s����\�� */
	if(ityp==0){					/* Jump�̎� */
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
	[����]
		�ݸ�ް��\��

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void DicLinkShowDsp(void)
/*TAIL*/
{
	TCHSTS		tsts;
	DSPCT		dct;				/* �\������p���Ұ� */
	byte		amsk;
	byte		st = 2;

	LibOpenWindow(1,72,158,87);		/* ����޳ open */

	/*** ����ر�ݒ� ***/
	LibTchStackPush( NULL );
	LibTchStackPush(TchLinkShow);		/* �ݸ�ް��\��������ر */
	LibTchStackPush(TchActionKey);		/* ����ݷ�  ���ð��� */
	LibTchStackPush( TchHardIcon );		/* ʰ�ޱ��� */
/*	LibTchStackPush( TchModeIcon );		/* Pop Up Tools */

	/*** ��۰��ް�����ݒ� ***/
	LinkDataScr.x		= W_EDX+3;			/* ��۰��ް�ʒu(X) */
	LinkDataScr.y		= W_STY+1;			/* ��۰��ް�ʒu(Y) */
	LinkDataScr.size	= W_EDY-W_STY-3;	/* ��۰��ް���� */
	LinkDataScr.dsp		= W_LNC;			/* �\������     */

	LinkShowBk();		/* �w�i�\�� */

	while(st>0){

		if(st>1){
			LinkShowData();					/* �\���ް���� */
			dct = lctrl;					/* ��ʐ擪���Ұ��߂� */

			/* ��۰��ް�㉺���Ԋ|������ */
			DLibScrollArrowPrint(LinkDataScr,SCR_NO_MASK);
			amsk = DataArrowMask(&LinkDataScr);
			DLibScrollArrowPrint(LinkDataScr,amsk);
			st = 1;
		}
		LibPutDisp();					/* ��ʍX�V */
		LibTchWait( &tsts );			/* ����҂� */

		switch(tsts.obj){

			case OBJ_LPSW_UP:		/* ����ݷ� Up */
				if(ChkScrlDwn(&LinkDataScr)==TRUE){
					LinkDataScr.pos --;
					st = 2;				/* �ް��ĕ\�� */
				}else{
					LibRepOff();		/* ��߰� Off */
				}
				break;

			case OBJ_LPSW_DOWN:		/* ����ݷ� Down */
				if(ChkScrlUp(&LinkDataScr)==TRUE){
					LinkDataScr.pos ++;
					st = 2;				/* �ް��ĕ\�� */
				}else{
					LibRepOff();		/* ��߰� Off */
				}
				break;

			case OBJ_LPSW_PUSH:		/* ����ݷ� Push */
				st = 0;					/* Loop End */
				break;

			case OBJ_SCR_BAR:			/* ScrollBar */
				if(DicShowScBar(&tsts, &LinkDataScr)!=0)
					st = 2;				/* �ް��ĕ\�� */
				break;

	/*		case OBJ_HIC_MBAR:		/* �ƭ��ްʰ�ޱ��� */
	/*			DicPdwnSet();				/* ����޳��ƭ��\���ݒ� */
	/*			if(DicPdwnFnc(&tp)==TRUE)	/* ����޳ݏ��� */
	/*				st = 0;
	/*			break;
	*/
			case OBJ_AR_LWOUT:			/* ����޳�O */
			case OBJ_HIC_ESC:			/* �ESC�ʰ�ޱ��� */
				st = 0;					/* Loop End */
				break;
		}
	}
	LibTchRelease();			/* �NULL��܂� POP */
	LibCloseWindow();
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\���w�i�`��

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void LinkShowBk(void)
/*TAIL*/
{
	byte far	*tgt;
	long		vol;
	DSPCT		dctwk;

	LibBox(2,73,155,84,1);				/* ����޳�g */
	LibLine(157,74,1,84,1);				/* ����޳�g(�E�e) */
	LibLine(3,157,155,1,1);				/* ����޳�g(���e) */
	LibLine(144,74,1,82,1);				/* ���� */

	sel_sp = sel_ep = 0xffff;			/* ���]�����ر */
	jprv = FALSE;						/* �ݸ������]���׸ޏ����� */

	if(DicDataRead(&lnkdp,&tgt)==FALSE){
		DicStatus = ST_MODEINI;			/* Fale Safe */
		return;
	}

	dttop = tgt-3;						/* �ݸ�ް��J�n���ڽ */

	/*** ��۰��ް�����ݒ� ***/
	dctwk.x		= W_STX;
	dctwk.sx	= W_STX;
	dctwk.sy	= W_STY;
	dctwk.ex	= W_EDX;
	dctwk.ey	= W_EDY;
	dctwk.ity	= D_ITY;
	vol = GetDicDspL(dttop,&dctwk);		/* �S�̏c���擾(�s��) */
	LinkDataScr.vol	= vol;				/* ��۰��ް�S�̗� */
	LinkDataScr.pos	= lnkdp.pos;		/* ��۰��ް�����ʒu */
}


/*HEAD*/
/******************************************************************************
	[����]
		�ݸ�ް��\��

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void LinkShowData(void)
/*TAIL*/
{
	int			ltc;				/* �ް��\���J�n�s�ʒu */
	DSPCT		dct;				/* �\������p���Ұ� */

	LibGdsClr(W_STX-W_SFTX*2,W_STY,W_EDX-1,W_EDY-1);	/* �g����ʏ��� */

	/*** �\�������ʒu�ݒ� ***/
	dct.sx		= W_STX;
	dct.sy		= W_STY;
	dct.ex		= W_EDX;
	dct.ey		= W_EDY;
	dct.lnc		= W_LNC;
	dct.fnt		= IB_PFONT1;
	dct.ity		= D_ITY;
	dct.pot 	= dttop;				/* �ޯ̧�擪 */
	dct.lkpt	= dttop;				/* �ݸ���� */
	dct.jpf		= FALSE;				/* �ެ��ߖ��� */
	ltc = LinkDataScr.pos;
	DicDspTopSrc(&dct, ltc);			/* �\���J�n�ʒu��� */

	lctrl = dct;						/* ��ʐ擪���Ұ��ޔ� */
/*	lkpsp = 0;							/* �ݸ�Ȃ� */

	DicDltpClear(&dct);						/* �s���Ұ������� */
	DicTxtDsp(&dct);					/* �w��s�ʒu�����ʕ\�� */
	DLibScrollPrint(LinkDataScr);		/* ��۰��ް�\�� */

	/** BIOS�޸ޑ΍� **/
	LibGdsClr(W_EDX,W_STY,W_EDX+2,W_EDY-1);	/* ��۰��ް������ʏ��� */
	LibLine(144,74,1,82,1);				/* ���� */
}
