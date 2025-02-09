/******************************************************************************
	[����]
		Referencer

	[�@��]
		�ʐM�d�q�蒠(�C�O)

	[�T�v]
		Referencer �������

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


TXTP		srctp;
bool		srcflg;
byte		srcbf[SRC_LEN+1];		/* ������͗p÷���ޯ̧ */
TCHTBL		SrcTch[3];				/* ÷������رð��� */
int			srclen;					/* ��������� */

/*HEAD*/
/******************************************************************************
	[����]
		������͎���w�i�\��

	[�߂�l]
	[�����׽]
		�����		DicStatus = ST_IINI

	[�������e]
******************************************************************************/
void DicSrcInit(void)
/*TAIL*/
{
	T_SCR_POS	srcscr;

	LibTchStackClr();					/* ����ر������ */
	LibTchInit();
	TchComSet();

/***** �General�����d�l�폜 **************
/*	LibTchStackPush(TchSrcTyp);			/* ������ߑI�� ���ð��� */

	LibTchStackPush(TchSrcTopKey);		/* �Clr/DTM/Cal/Exe����� ���ð��� */
	LibTchStackPush(TchDBSel);			/* ����DB�I���������ð��� */
	LibTchStackPush(TchActionKey);		/* ����ݷ�  ���ð��� */

	SrcTxtInit(&srctp,&srcscr,SrcTch);	/* ����������͏����� */
	LibTxtInit(&srctp);					/* ÷�ē��͏����� */
	LibTxtTchSet(&srctp);				/* ÷������ر PUSH */

	DicStatus	= ST_ILOOP;				/* �����������͂� */
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\�����A�����������

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void SrcTxtInit(TXTP *tp, T_SCR_POS *scbar, TCHTBL *tcht)
/*TAIL*/
{
 /** ÷�ē��͐ݒ� **/
	tp->txbf	= srcbf;		/* ÷���ޯ̧�w�� */
	tp->st_x	= SI_ST_X;
	tp->ed_x	= SI_ED_X;
	tp->st_y	= SI_ST_Y;
	tp->it_y	= SI_IT_Y;
	tp->MAXGYO	= SI_MAXG;
	tp->font	= IB_PFONT1;
	tp->csen	= TRUE;			/* ���ٕ\������(��ܰ�ޓo�^�֎~) */
	tp->rtnen	= 0x02;			/* ���s���͕\���֎~ */
	tp->maxmj	= SRC_LEN;		/* �ő���͉\������ */
	tp->txtobj	= OBJ_TXTTCH;	/* ÷�Ĵر�������޼ު��  */
	tp->sbrobj	= OBJ_SCR_BAR;	/* ��۰��ް�������޼ު�� */
	tp->tchtb	= tcht;			/* ���ð����߲�� */
	tp->gdcmt	= srcgid;	/* �޲��ݽ����ð��� */
	tp->s_pos	= scbar;		/* ��۰��ް�ʒu����߲�� */
}


/*HEAD*/
/******************************************************************************
	[����]
		������������

	[����]
	[�����׽]
		�����		DicStatus = ST_ILOOP

	[�������e]
******************************************************************************/
void DicSrcInput()
/*TAIL*/
{
	byte		kycd;
	TCHSTS		tsts;

/*	LibOpenWindow(0,0,160,160);				/* �S��ʳ���޳����� */
	DicSrcInpBk();							/* �w�i�\�� */
	LibDispKey();							/* �����ķ��ް�ޕ\�� */

	if(DBfc<=0){
		LibWinIcnMsg(ICON_NONE,501,2);		/* "DB̧�ق�������܂���I" */
		LibJumpMenu();						/* MENU�� */
	}

	while(DicStatus==ST_ILOOP){

		DicSrcDsp();						/* �����������͒��\�� */
		kycd = LibGetKeyM(&tsts);			/* ��ķ��҂� */

		if(kycd==KEY_NONE){					/* ���ް�ވȊO������� */
			switch(tsts.obj){

				case OBJ_IC_DBSEL:		/* DB Select */
					if(DicDBSelWin(&tsts,TRUE)==TRUE)
						DicStatus = ST_IINI;	/* �������͏����� */
					break;

	/***** �General�����d�l�폜 **************
	/*			case OBJ_IC_ISRC:			/* �Initial���������̎� */
	/*				srcflg = FALSE;
	/*				break;
	/*
	/*			case OBJ_IC_GSRC:			/* �General���������̎� */
	/*				srcflg = HALF;
	/*				break;
	*/

				case OBJ_LPSW_UP:			/* ����ݷ� Up */
				case OBJ_LPSW_DOWN:			/* ����ݷ� Down */
					if(DicDBSelWin(&tsts,FALSE)==TRUE)
						DicStatus = ST_IINI;	/* �������͏����� */
					break;

				case OBJ_IC_EXEKEY:			/* �Exe���������̎� */
					if(LibIconClick(&TicnExeKey,&tsts)!=TRUE){
						break;				/* �ȉ������ݷ�PUSH�Ɠ��� */
					}
				case OBJ_LPSW_PUSH:			/* ����ݷ� Push */
					if(srcbf[0]!=0){		/* ÷�Ă��󔒂łȂ���� */
						if(DicSrcExe()==TRUE){	/* �������s */
							DicStatus	= ST_LTCHINI;		/* ؽĕ\���� */
						}else{			/* ����ٻ���Ŗ������� */
							LibWinIcnMsg(ICON_BIKKURI,323, 1);
										/* �Not_Found!� 1Sec�\�� */
						}
					}else{
						DicStatus	= ST_LFILEINI;		/* ؽĕ\���� */
					}
					break;

				case OBJ_IC_CALKEY:			/* �Cal���������̎� */
					if(LibIconClick(&TicnCalKey,&tsts)==TRUE){
						LibCalWin(ON);
					}
					break;

				case OBJ_IC_DTMKEY:		/* �u���ݎ����v��������̎� */
					if(LibIconClick(&TicnDTMKey,&tsts)==TRUE){
						srctp.txtst = TXTDYTIM;
					}
					break;

		/*		case OBJ_HIC_ESC:		/* ESC ��������� */
		/*			srcbf[0] = NULL;		/* ÷���ޯ̧������ */
		/*			LibTxtInit(&srctp);		/* ÷�ē��͏����� */
		/*			break;
		*/

				case OBJ_IC_CLRKEY:			/* �CLR/LIST���������̎� */
					if(LibIconClick(&TicnClrKey,&tsts)==TRUE){
						if(srcbf[0]!=NULL){		/* �CLR����݂̎� */
							srcbf[0] = NULL;	/* ÷���ޯ̧������ */
							LibTxtInit(&srctp);	/* ÷�ē��͏����� */
						}
					}
					break;

				case OBJ_HIC_MBAR:			/* �ƭ��ްʰ�ޱ��� */
					DicPdwnSet();				/* ����޳��ƭ��\���ݒ� */
					if(DicPdwnFnc(&srctp)==TRUE)	/* ����޳ݏ��� */
						return;
					break;
			}
		}

		if(DicStatus==ST_ILOOP)
			LibTxtInp(kycd,&tsts,&srctp);		/* ÷�ē���Ҳ� */
	}

/*	LibTchRelease();				/* �NULL��܂� POP */
/*	LibCloseWindow();				/* ����޳�۰�� */
}


/*HEAD*/
/******************************************************************************
	[����]
		������͎���w�i�\��

	[�������e]
******************************************************************************/
void DicSrcInpBk(void)
/*TAIL*/
{
	byte i;

	LibClrDisp();						/* ��ʏ��� */
	LibPutFarData( 0, 0, 96);			/* ���ዾ���ݕ\�� */

	LibPutFarData(14, 0,132);						/* �Clr����ݕ\��(�g) */
	LibPutMessageCenter(110, 14,42,2,IB_PFONT1);	/* �Clr����ݕ\��(����) */
	LibPutFarData(71, 0,133);						/* �Exe����ݕ\��(�g) */
	LibPutMessageCenter(111,99,127,2,IB_PFONT1);	/* �Exe����ݕ\��(����) */
	LibModeIconDsp();								/* �Tool����ݕ\��(�g) */

	LibLine(1, 13, 158, 1, 1);			/* �S�̘g��(��) */
	LibLine(0, 14, 1, 73, 1);			/* �S�̘g��(��) */
	LibLine(159, 14, 1, 73, 1);			/* �S�̘g��(�E) */
	LibLine(1, 87, 158, 1, 1);			/* �S�̘g��(��) */

	LibLine(0, 29, 159, 1, 1);			/* �S�̘g�� */
	LibLine(0, 67, 159, 1, 1);			/* �S�̘g�� */
	LibPutMessage(16,3,15,IB_PFONT2);	/* �Search����ĕ\�� */
	
	for (i=31;i<66;){
		LibGdsLineMesh(3,i,157,i);
		i=i+2;
	}
	for (i=32;i<65;){
		LibGdsLineMesh(2,i,156,i);
		i=i+2;
	}
	LibClrBox(24,38,111,22);
	LibBox(28,42,115-13+1,43-30+1,1);	/* �������͘g */

	LibLine(26,40,107,1,1);				/* �������͘g(��) */
	LibLine(26,41,106,1,1);				/* �������͘g(��) */
	LibLine(27,42,1,15,1);				/* �������͘g(��) */
	LibLine(26,42,1,16,1);				/* �������͘g(��) */
	
	LibLine(27,57,106,1,1);
	LibLine(132,40,1,18,1);
	LibDotOn(131,56);

	/***** �General�����d�l�폜 **************
	/*	LibPutMessage(31,37,73,IB_PFONT1);	/* �ALL����ĕ\�� */
	/*	LibPutMessage(66,97,73,IB_PFONT1);	/* �Initial����ĕ\�� */

	DicDBSelWinBk();					/* DB̧�ّI��g�w�i */
}

/*HEAD*/
/******************************************************************************
	[����]
		������͒��\��

	[�������e]
******************************************************************************/
void DicSrcDsp(void)
/*TAIL*/
{

	/***** �General�����d�l�폜 **************
	/*
	/*	if(srcflg==FALSE){				/*** �Ƽ�ٻ���̎� ***/
	/*		LibPutFarData(26,73,42);		/* ���۱��ݕ\�� */
	/*		LibPutFarData(86,73,43);		/* ���۱��ݕ\�� */
	/*
	/*	}else{							/*** ����ٻ���̎� ***/
	/*		LibPutFarData(26,73,43);		/* ���۱��ݕ\�� */
	/*		LibPutFarData(86,73,42);		/* ���۱��ݕ\�� */
	/*	}
	*/

	LibTxtDsp(&srctp);					/* ÷�ē��͒��\�� */
	LibPutDisp();						/* �\���X�V */
}


/*HEAD*/
/******************************************************************************
	[����]
		�����������

	[�߂�l]
		TRUE	: �Y���ް�������
		FALSE	: �Y���ް���������(����ٻ�����̂�)

	[�������e]
******************************************************************************/
bool DicSrcExe(void)
/*TAIL*/
{
	long	tgt;

	LibWinIcnMsg(ICON_COFFEE,337,0);	/* Searching...    */
	LibPutDisp();						/* �\���ɔ��f        */
	LibCloseWindow();					/* LibWinIcnMsg(0)�� */

	srclen = strlen(srcbf);			/* ��������� */

	/*** �Ƽ�ٻ���̎� ***/
	if(srcflg==FALSE){
		DicIniSrc(&tgt,srcbf,srclen,0,FALSE);
		DicLstScr.pos = tgt;

	/***** �General�����d�l�폜 **************
	/*
	/*	/*** ����ٻ���̎� ***/
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
	[����]
		�����啶����̧�ޯĕϊ�

	[����]
		byte	*d		: out	�ϊ��㕶����
		byte	*s		: in	�ϊ���������

	[�������e]
******************************************************************************/
void ChrS2L(byte far *d, byte far *s)
/*TAIL*/
{
	int		i;

	for(i=0;;i++){
		d[i] = s[i];
		if(d[i]==0x0d){					/* ���s������ */
			d[i] = 0;					/* �I�[�ɕϊ� */
		}else if('a'<=d[i] && d[i]<='z'){	/* ������������ */
			d[i] -= 'a'-'A';			/* �啶���ɕϊ� */
		}
		if(d[i]==NULL)					/* �I�[������ */
			break;
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�Ƽ�ٻ������

	[����]
		long	*tgt		: out	����Y���ް��ԍ�
		byte	*buf		: in	����������ޯ̧
		int		len			: in	���������
		byte	type		: in	�Ώ۲��ޯ�����(0:���ٲ��ޯ��/1:�ݸ���ޯ��)
		bool	ls			: in	�ݸ(�ެ���)�滰�����

	[�߂�l]
		0	: ���ޯĔԍ�������ʒu�i������ׂ��ʒu�𔭌��j
		1	: ���ޯĔԍ�������ʒu�i������ׂ��ʒu�͂����ƌ��j
		2	: ����ʒu�����ޯĔԍ��i������ׂ��ʒu�͂����ƑO�j

	[�������e]
******************************************************************************/
byte DicIniSrc(long *tgt, byte *buf, int len, byte type, bool ls)
/*TAIL*/
{
	long	stn;			/* ����͈͊J�n */
	long	ttn,ttnbk;		/* ����ް��� */
	long	dvn;			/* �����ʒu */
	byte	ret = 0;
	byte	rr = 0;
	byte	tmp[TT_LEN+1];

	ChrS2L(tmp, buf);				/* ��������񤏬���啶���� */

	stn = 0;						/* �ް��擪 */
	if(type==0)
		ttn = tidxc;				/* ���ٲ��ޯ������ */
	else
		ttn = lidxc;				/* �ݸ���ޯ������ */
	ttnbk = ttn;

	while(1){
		dvn = stn + ttn/2;		/* ���ޯĂ͑Ώی����̓񕪊��ʒu */
		ret = JdgStrHighLow(dvn,tmp,len,type,TRUE);	/* �㉺���f */

		if(ttn<=1)		/* �����s�� */
			break;

		switch(ret){

			/*** ���ޯĕ����񁁻�������� ***/
			case 0:
				while(rr==0){		/* �召��������̐擪��� */
					if(dvn==0)
						break;
					rr = JdgStrHighLow(dvn-1,tmp,len,type,TRUE);
									/* ��O���ް������� */
					if(rr!=0)
						break;
					dvn --;	
				}
				if(ls==TRUE){		/* �ݸ��͊��S��v���镨��� */
					while(dvn<ttnbk-1){
						rr = JdgStrHighLow(dvn,buf,len,type,FALSE);
						if(rr==0)
							break;
						dvn ++;
					}
				}
				goto LOOP_END;		/* LOOP �I�� */
				break;

			/*** ���ޯĕ����񁃻�������� ***/
			case 1:
				ttn = ttn - (dvn - stn);
				stn = dvn;
				break;

			/*** ������������ޯĕ����� ***/
		/*	case 2:	*/
			default:
				ttn = dvn - stn;
				break;
		}
	}

LOOP_END:
	if(ret==2){				/* ������������ޯĕ����� */
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
	[����]
		������㉺���f����

	[����]
		long	*tgt		: in	���ޯ��ް��ԍ�
		byte	*buf		: in	����Ώە�����
		int		len			: in	���������
		byte	type		: in	�Ώ۲��ޯ�����(0:���ٲ��ޯ��/1:�ݸ���ޯ��)
		bool	ls			: in	�召�������ꎋ�׸�

	[�߂�l]
		0	: ���ޯĔԍ�������ʒu�i������ׂ��ʒu�𔭌��j
		1	: ���ޯĔԍ�������ʒu�i������ׂ��ʒu�͂����ƌ��j
		2	: ����ʒu�����ޯĔԍ��i������ׂ��ʒu�͂����ƑO�j

	[�������e]
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

	GetIndex(&lidx,type);		/* ���ޯĕ������߲����擾 */
	DicDataRead(&lidx,&tgt);	/* ���ޯĕ������ް��擾 */
	if(type==1)					/* �ݸ���ޯ��������鎞 */
		tgt += 1;				/* 1�޲�(������)����� */
	SelCharacter(wrk,&tgt,len);	/* �������ނ𒊏o */

	if(lss==TRUE)
		ChrS2L(tmp, wrk);		/* ���ޯď����啶���� */
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
	[����]
		�������ޒ��o

	[����]
		byte		*d		: out	�������ޒ��o��
		byte far	*s		: in	���ޯ��ް�
		int			len		: in	

	[�߂�l]
	[�������e]
******************************************************************************/
void SelCharacter(byte *dbuf, byte far **sbuf, int len)
/*TAIL*/
{
	byte	ccd;
	int		i;

	for(i=0;i<len;i++){

		ccd = JdgContCode(sbuf);			/* ���亰�ޔ��f */

		switch(ccd){

			case CD_CHA:			/* �������ށu00h�`7Fh(0Dh�͏���)�v */
			case CD_OVCHA:			/* 1�޲ĺ��ގw��(0x80�ȏ�)�u@\x??�v */
				dbuf[i] = **sbuf;
				(*sbuf) ++;
				break;

			case CD_FNT57:		/* 5x7̫�Ďw��        �u@\fNM�v */
			case CD_FNTPN:		/* ����߰����̫�Ďw�� �u@\fPN�v */
			case CD_FNTPB:		/* ������̫�Ďw��     �u@\fPB�v */
				i--;
				break;

			default:				/* fale safe */
				goto LOOPEND;
				break;
		}
	}
LOOPEND:
	dbuf[i] = NULL;	/* �I�[�t�� */
}


#if 0
/*********** ����������ٻ���d�l�폜������ ***********/

/*HEAD*/
/******************************************************************************
	[����]
		����ٻ������

	[����]
		long	*tgt		: out	����Y���ް��ԍ�

	[�߂�l]
		TRUE	: �Y���ް�������
		FALSE	: �Y���ް���������

	[�������e]
******************************************************************************/
bool DicGenSrc(long *tgt, int len)
/*TAIL*/
{
	LSTIDX		lidx;
	byte		tmp[TT_LEN+1];
	byte far	*dt;
	long		i;

	lidx.num = 0;
	if(GetIndex(&lidx,0)==FALSE)			/* �擪���ٕ������߲����擾 */
		return(FALSE);
	if(DicDataRead(&lidx,&dt)==FALSE)		/* �擪���ٕ������ް��擾 */
		return(FALSE);
	ChrS2L(tmp, dt);						/* �擪���ُ����啶���� */

	if(JdgStrMach(tmp,len)==FALSE){				/* �擪�ް����s��v�̎� */
		if(NxtGenSrc(&lidx,len)==FALSE){		/* ����v�ް���� */
			return(FALSE);					/* ��v�ް����� */
		}
	}

	*tgt = lidx.num;

	/*** �S�Y���ް��������oٰ�� ***/
	for(i=1; i<tidxc; i++){
		if(NxtGenSrc(&lidx,len)==FALSE)		/* ����v�ް���� */
			break;
	}
	DicLstScr.vol = i;					/* ��۰��ް�S�� */

	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[����]
		�������v���f����

	[����]
		byte	*tgt		: in	��r�Ώە�����

	[�߂�l]
		TRUE	: ��v
		FALSE	: �s��v

	[�������e]
******************************************************************************/
bool JdgStrMach(byte *tgt, int len)
/*TAIL*/
{
	int		i,j;

	for(j=0;j<TT_LEN;j++){
		if(tgt[j]==srcbf[0]){			/* �擪��������v�̎� */

			for(i=1;i<len;i++){		/* ���������ƈ�v? */
				if(tgt[j+i]!=srcbf[i])
					break;
			}
			if(i==len)
				return(TRUE);			/* ��v */
		}
	}
	return(FALSE);						/* �s��v */
}


/*HEAD*/
/******************************************************************************
	[����]
		���ް��������(����ٻ��)

	[����]
		LSTIDX	*lidx		: in	����ؽĲ��ޯ���\����
			lidx.num					���ݲ��ޯ���ԍ�
			lidx.flp					���ݲ��ޯ���߲����̊܂܂��̧���߲���
			lidx.ofs					���ݲ��ޯ���߲����̵̾��
		byte	*buf		: in	���������(����ޯ̧��啶���ϊ���������)

	[�߂�l]
		FALSE	: �Y���ް���������
		TRUE	: �Y���ް�������

		LSTIDX	*lidx		: out	��ؽĲ��ޯ���\����
			lidx.num					�����ޯ���ԍ�
			lidx.flp					�����ޯ���߲����̊܂܂��̧���߲���
			lidx.ofs					�����ޯ���߲����̵̾��

	[�������e]
******************************************************************************/
bool NxtGenSrc(LSTIDX *lidx, int len)
/*TAIL*/
{
	byte		tmp[TT_LEN+1];
	byte far	*dt;
	long		i;
	bool		jdg = FALSE;

	for(i=lidx->num;i<tidxc;i++){

		if(GetNxtTitleIndex(lidx)==FALSE)	/* �����ٲ��ޯ���ް��擾 */
			break;
		if(DicDataRead(lidx,&dt)==FALSE)	/* ���ޯĕ������ް��擾 */
			break;
		ChrS2L(tmp,dt);						/* ���ޯď����啶���� */
		if(JdgStrMach(tmp,len)==TRUE){		/* �������v�� */
			jdg = TRUE;
			break;
		}
	}

	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[����]
		����ٻ������2

	[����]
		long	*tgt		: in	����ԍ��i0�`�j
		LSTIDX	*lidx		: out	�Y�������ް��߲���

	[�߂�l]
		TRUE	: �Y���ް�������
		FALSE	: �Y���ް���������

	[�������e]
		����ٻ���̈�v�����ް����A�w�肳�ꂽ���Ԃ��ް��ԍ���Ԃ�
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
	if(GetIndex(lidx,0)==FALSE)				/* �擪���ٕ������߲����擾 */
		return(FALSE);
	if(DicDataRead(lidx,&dt)==FALSE)		/* �擪���ٕ������ް��擾 */
		return(FALSE);
	ChrS2L(tmp, dt);						/* �擪���ُ����啶���� */

	if(JdgStrMach(tmp,srclen)==FALSE){		/* �擪�ް����s��v�̎� */
		if(NxtGenSrc(lidx, srclen)==FALSE){	/* ����v�ް���� */
			return(FALSE);					/* ��v�ް����� */
		}
	}
	for(i=0; i<tgt; i++){
		if(NxtGenSrc(lidx,srclen)==FALSE)	/* ����v�ް���� */
			break;
	}
	if(i < tgt)
		return(FALSE);
	return(TRUE);
}

/*********** ����������ٻ���d�l�폜������ ***********/
#endif
