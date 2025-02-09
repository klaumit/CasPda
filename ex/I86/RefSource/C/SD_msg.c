/******************************************************************************
	[����]
		Referencer Ӱ��  ү���ޏ����Q

	[�@��]
		ZX400 Referencer

	[�T�v]
		5�J���ꌾ��ү���ޏ����Ɋւ��鏈���Q.
		�{�̂ɓ������Ă��Ȃ�ү���ނ�����ײ���ز���̪���ŕ\���ł���悤��,
		�����̏����ŋz������.

	[�쐬��]
		��ؖΐl

	[���l]
		ZX481�\�v�ZӰ�ނ�藬�p�����

	Copyright (C) 2000 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#include	<stdrom.h>
#include	"define.h"
#include	"libc.h"
#include	"l_define.h"
#include	"l_libc.h"
#include	"SD_main.h"
#include	"SD_msg.h"


/******************************************************************************/
/*               ����ײ���؏����Q (�֐�����ύX���Ă��̂܂܈ڐA)              */
/******************************************************************************/
/*HEAD*/
/******************************************************************************
	[����]
		�Œ�ү���ގ擾

	[����]
		no				:in     ү����NO
		buf				:out	�ǂݏo���p�ޯ̧���ڽ

	[�߂�l]
		�Ȃ�

	[�������e]
		ү����NO�ɑΉ�����Œ�ү���ޕ�������擾����.
		���e��,�ݒ肳��Ă��颍���̏��ɉ����Ď����I�ɕω�����.

******************************************************************************/
void _LibReadMessage(word no,byte *buf)
/*TAIL*/
{
	union	REGS	ireg,oreg;

	ireg.h.ah = IB_FMREAD;
	ireg.x.bx = no;
	ireg.x.dx = FP_SEG(buf);
	ireg.x.di = FP_OFF(buf);

	int86(GDSBIO, &ireg, &oreg);

}


/*HEAD*/
/******************************************************************************
	[����]
		�Œ�ү���ޕ\��

	[����]
		no				:in     ү����NO
		p_x				:in     �����W
		p_y				:in     �c���W
		type			:in     ̫�Ď��	IB_PFONT1	:�ް�����
											IB_PFONT2	:�w�i����
                                            IB_PFONT3	:���ٗp
                                            IB_CG57FONT	:5*7
	[�߂�l]
		�Ȃ�

	[�������e]
		ү����NO�ɑΉ�����Œ�ү���ނ�\������.�\���������e��,�ݒ肳��Ă��颍���̏��
		�ɉ����Ď����I�ɕω�����.

	[�⑫]
		5�̏C������݂��p�ӂ���Ă��邪,�����ł͏㏑��Ӱ�ނ݂̂Ƃ���.

******************************************************************************/
void _LibPutMessage(word no,int p_x,int p_y,byte type)
/*TAIL*/
{
	union	REGS	ireg,oreg;

	ireg.h.ah = IB_FMOVER;
	ireg.h.al = type;
	ireg.x.bx = no;
	ireg.x.cx = p_x;
	ireg.x.dx = p_y;

	int86(GDSBIO, &ireg, &oreg);

}


/*HEAD*/
/******************************************************************************
	[����]
		�Œ�ү���ޕ\��	(����ݸގw��)

	[����]
		no				:in     ү����NO
		p_x1			:in     ���[���W(�J�n)
		p_x2			:in     �E�[���W(�I��)
		p_y				:in     �c���W
		type			:in     ̫�Ď��	IB_PFONT1	:�ް�����
											IB_PFONT2	:�w�i����
                                            IB_PFONT3	:���ٗp
                                            IB_CG57FONT	:5*7
	[�߂�l]
		�Ȃ�

	[�������e]
		ү����NO�ɑΉ�����Œ�ү���ނ�,�w�肳�ꂽ�J�n�`�I���̗̈���ɾ���ݸޕ\������.
		�\���������e��,�ݒ肳��Ă��颍���̏��ɉ����Ď����I�ɕω�����.

******************************************************************************/
void _LibPutMessageCenter(word no,int p_x1,int p_x2,int p_y,byte type)
/*TAIL*/
{
	union	REGS	ireg,oreg;

	ireg.h.ah = IB_FMCENTER;
	ireg.h.al = type;
	ireg.x.bx = no;
	ireg.x.cx = p_x1;
	ireg.x.dx = p_y;
	ireg.x.di = p_x2;

	int86(GDSBIO, &ireg, &oreg);

}


/*HEAD*/
/******************************************************************************
	[����]
		�Œ�ү���ޕ\��	(�E�񂹎w��)

	[����]
		no				:in     ү����NO
		p_x				:in     �E�[���W
		p_y				:in     �c���W
		type			:in     ̫�Ď��	IB_PFONT1	:�ް�����
											IB_PFONT2	:�w�i����
                                            IB_PFONT3	:���ٗp
                                            IB_CG57FONT	:5*7
	[�߂�l]
		�Ȃ�

	[�������e]
		ү����NO�ɑΉ�����Œ�ү���ނ�,�w�肳�ꂽ�E�[���W�ɍ��킹�ĉE�񂹕\������.
		�\���������e��,�ݒ肳��Ă��颍���̏��ɉ����Ď����I�ɕω�����.

******************************************************************************/
void _LibPutMessageRight(word no,int p_x,int p_y,byte type)
/*TAIL*/
{

	union	REGS	ireg,oreg;

	ireg.h.ah = IB_FMRIGHT;
	ireg.h.al = type;
	ireg.x.bx = no;
	ireg.x.dx = p_y;
	ireg.x.di = p_x;

	int86(GDSBIO, &ireg, &oreg);

}


/*HEAD*/
/******************************************************************************
	[����]
		�޲�۸�ү���ޗp����޳���ގ擾

	[����]
		int		mes_no			:in		ү���ޔԍ�
		byte	w_pos			:in		����޳�\���ʒu
											0x00:			��ʉ�
											IX_MWIN_CENTER:	��ʒ���
		byte	b_cnt			:in		���ݐ�(0�`2)
		int		*y				:out	����޳�c���W
		int		*y_size			:out	����޳�c����

	[�߂�l]
		�Ȃ�

	[�������e]
		�޲�۸�ү���ޗp�̳���޳�ʒu,���ނ��擾����.

******************************************************************************/
void _LibGetWinMessSize(int mes_no,byte w_pos,byte b_cnt,int *y,int *y_size)
/*TAIL*/
{
	union	REGS	ireg,oreg;

	ireg.h.ah = IB_FMWINCALC;
	ireg.h.ch = w_pos;
	ireg.h.cl = b_cnt;
	ireg.x.bx = mes_no;

	int86(GDSBIO, &ireg, &oreg);

	*y		= oreg.x.cx;
	*y_size	= oreg.x.dx;
}


/*HEAD*/
/******************************************************************************
	[����]
		�޲�۸�ү���ޗp�\��

	[����]
		byte	g_no			:in		����(���̨��)�ԍ�
											IB_MWIN_NO_ICON �̎�,�Ȃ�
		int		mes_no			:in		ү���ޔԍ�
		byte	b_cnt			:in		���ݐ�(0�`2)
		byte	b_type			:in		���ݎ��
											IB_MWIN_NONE:		�Ȃ�
											IB_MWIN_YES_NO:		YES/NO(�{�^���Q��)
											IB_MWIN_SET_ESC:	SET/ESC(�{�^���Q��)
											IB_MWIN_OK:			OK(�{�^���P��)
											IB_MWIN_SET:		SET(�{�^���P��)
											IB_MWIN_ESC:		ESC(�{�^���P��)

											IX_MWIN_CENTER:		����޳�ʒu�����w��
	[�߂�l]
		�Ȃ�

	[�������e]
		�޲�۸�ү���ޗp�̕\�����s��.

******************************************************************************/
void _LibDspWinMessage(byte g_no,int mes_no,byte b_cnt,byte b_type)
/*TAIL*/
{
	union	REGS	ireg,oreg;

	ireg.h.ah = IB_FMWINMES;
	ireg.h.al = g_no;
	ireg.h.cl = b_cnt;
	ireg.h.ch = b_type;
	ireg.x.bx = mes_no;

	int86(GDSBIO, &ireg, &oreg);
}


/*HEAD*/
/******************************************************************************
	[����]
		�I����޳ ����ر��`

	[�������e]
******************************************************************************/
static void LibSelWinTchSet(void)
/*TAIL*/
{
	LibTchStackPush( NULL );
	LibTchStackPush(TchAllDsp);		/* �S�������ر */
	LibTchStackPush(TchHardIcon);	/* ʰ�ޱ��� ���ð��� */
	LibTchStackPush(TchActionKey);	/* ����ݷ�  ���ð��� */
	LibTchInit();
}


/*HEAD*/
/******************************************************************************
	[����]
		�I����޳�g�`��
	[����]
	[�������e]
******************************************************************************/
static void LibSelWinFlm(int x, int y, int xs, int ys)
/*TAIL*/
{
	LibLine(x+2,y+1,xs-4,1,1);			/* �g(��) */
	LibLine(x+1,y+2,1,ys-4,1);			/* �g(��) */
	LibLine(x+2,y+ys-3,xs-4,1,2);		/* �g(��) */
	LibLine(x+xs-3,y+2,1,ys-4,2);		/* �g(�E) */
}


/*HEAD*/
/******************************************************************************
	[����]
		�I����޳ �����
	[����]
		word *tbl	: ����ð���
	[�������e]
		�I����޳���J�������޳���ɺ��ĕ\������
******************************************************************************/
static void LibSelWinOpen(int x, int y, int ity, int xs, byte ln, SLW_TBL *ktb)
/*TAIL*/
{
	word	i,yy;
	int		ys;

	ys = ln*ity+6;					/* ����޳�c������ */
	if(ity==9)
		ys ++;

	LibOpenWindow(x,y,xs,ys);		/* �I����ް����� */
	LibSelWinFlm(x,y,xs,ys);		/* �g���`�� */

	yy = y+4;
	for(i=0;i<ln;i++,yy+=ity,ktb++){
		LibPutMessage(ktb->msg,x+4,yy,IB_PFONT1);	/* ���ĕ\�� */
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�I����޳�\�����A������s�Z�o
	[����]
		TCHSTS	*tsts	: ����ð��
		int		xp		: ����޳�\���J�n���W�iX�j
		int		yp		: ����޳�\���J�n���W�iY�j
		byte	iy		: ���ڕ\���Ԋu�iY�j
		int		xs		: ����޳�\�����iX�j
		byte	ln		: �I����޳���s��

	[�߂�l]
		����Y���s�ʒu(0,1,2,3,...,)    0xff : ����޳�O 
	[�������e]
		������ꂽ�ӏ�����I����޳��ŉ��s�ڂł��邩�Z�o����
******************************************************************************/
static byte LibSelWinTchLn(TCHSTS *tsts, int xp, int yp, byte iy, int xs, byte ln)
/*TAIL*/
{
	word	i,ly;

	if((tsts->x < xp) || (xp+xs-1 < tsts->x))		/* ���ɊO��Ă��鎞 */
		return(0xff);

	if((tsts->y < yp+2) || (yp+ln*iy+2 < tsts->y))	/* �c�ɊO��Ă��鎞 */
		return(0xff);

	for(ly=yp+2,i=0;i<ln;i++){
		ly += iy;
		if(ly>=tsts->y)
			break;
	}
	return(i);
}


/*HEAD*/
/******************************************************************************
	[����]
		����޳�ऍ��ڑI������

	[����]
		int		x		: ����޳�\���J�n���W�iX�j
		int		y		: ����޳�\���J�n���W�iY�j
		byte	iy		: ���ڕ\���Ԋu�iY�j
		int		xs		: ����޳�\�����iX�j
		byte	ln		: �I����޳���s��
		byte np			: ��̫�Ĕ��]�ʒu(��̫�Ĕ��]����������0xff)

	[�������e]
		����҂���y�є��]���ٕ\��
******************************************************************************/
static byte LibSelectWin(int x, int y, byte iy, int xs,  byte ln, byte np)
/*TAIL*/
{
	TCHSTS	tsts;
	byte	rvc;
	bool	scen;

	rvc = np;				/* �Ƃ肠�����I���ʒu�ͤ��̫�Ĉʒu */
/*	dfp = rvc;	*/

	for(scen=TRUE;;){
		if(rvc!=0xff){
			LibReverse(x+3,y+rvc*iy+3,xs-7,9);	/* ���]���ٕ\�� */

#if 0	/* '00. 2.15  Y.Itoh */
			LibPutDisp();						/* �\���X�V */
#endif
		}
#if 1	/* '00. 2.15  Y.Itoh */
		LibPutDisp();						/* �\���X�V */
#endif

		LibTchWait(&tsts);						/* ����҂� */
		if(rvc!=0xff)
			LibReverse(x+3,y+rvc*iy+3,xs-7,9);	/* ���]���ٖ߂� */

	/** ����ݷ� ����� **/
		if(tsts.obj==OBJ_LPSW_UP){
			if(rvc!=0){
				rvc --;
			}else{
				if(tsts.act==ACT_MAKE)
					rvc = ln-1;
				else
					LibRepOff();	/* '99. 4. 5  Y.Itoh */
			}

		}else if(tsts.obj==OBJ_LPSW_DOWN){
			if(rvc<ln-1){
				rvc++;
			}else{
				if(tsts.act==ACT_MAKE)
					rvc = 0;
				else
					LibRepOff();	/* '99. 4. 5  Y.Itoh */
			}

		}else if(tsts.obj==OBJ_LPSW_PUSH){
				break;

	/*** �ESC�ʰ�ޱ�������� ***/
		}else if(tsts.obj==OBJ_HIC_ESC){
			return(0xff);

	/*** ���(����޳���O)����� ***/
		}else if(tsts.obj==OBJ_ALLTCH){
			rvc = 0xff;
			if(scen==TRUE){
				rvc = LibSelWinTchLn(&tsts,x,y,iy,xs,ln);
											/* ����޳������s�Z�o */
		/*		if(rvc!=0xff)
		/*			dfp = rvc;				/* �ŏI�ʒu�X�V */
			}

		/** ��ݵݎ� **/
			if(tsts.act==ACT_MAKE){
				if(rvc==0xff){
					scen = FALSE;			/* �ȍ~�SCAN���~ */
				}

		/** �����ڲ��� **/
			}else if(tsts.act==ACT_BREAK){
				if(scen==FALSE || (scen==TRUE && rvc!=0xff)){
									/* ��ʊO����ݵݤ�܂��͉�ʊO����ݵ� */
					break;
				}else{
					rvc = np;				/* ���ق���̫�Ĉʒu */
				}

			}else{
				if(rvc==0xff){				/* ����޳����O�ꂽ�� */
					rvc = np;				/* ���ق���̫�Ĉʒu */
				}
			}
		}
	}
	return(rvc);
}


/*HEAD*/
/******************************************************************************
	[����]
		�I����޳ �����
	[����]
		int		x		: ����޳�\���J�n���W�iX�j
		int		y		: ����޳�\���J�n���W�iY�j
		byte	iy		: ���ڕ\���Ԋu�iY�j
		int		xs		: ����޳�\�����iX�j
		byte	ln		: �I����޳���s��
		SLW_TBL *ktb	: �I����޳�p�\�����߲���
		word	msk		: �\������Ͻ����

	[�������e]
		�I����޳���J�������޳���ɺ��ĕ\������
******************************************************************************/
static void LibSelWinOpen2(int x, int y, byte iy, int xs, byte ln, SLW_TBL *ktb, word msk)
/*TAIL*/
{
	word	i,yy;
	int		ys;

	ys = (ln+1)*iy+6+4;					/* ����޳�c������ */

	LibOpenWindow(x,y,xs,ys);			/* �I����ް����� */
	LibSelWinFlm(x,y,xs,ys);			/* �g���`�� */


#if 1	/* '99. 3.11  Y.Itoh */
	LibDotOff((xs+x-1)-2,y+1);	/* �E��p���� */
	LibDotOff((xs+x-1)-1,y+2);	/* �E��p���� */

	LibDotOff(x+1,(ys+y-1)-2);	/* �����p���� */
	LibDotOff(x+2,(ys+y-1)-1);	/* �����p���� */
#endif

	yy = y+4;

	LibPutMessageCenter(ktb->msg,x,x+xs-2,yy,IB_PFONT2);	/* ���ٕ\�� */
	yy += iy;

/*	LibLine(x+6,yy,xs-13,1,1);	/* ���ى��� */
	LibLine(x+3,yy,xs-7,1,1);	/* ���ى���(ZX486�V�޻޲݂ŉ���) '99. 3.11  Y.Itoh */

	yy += 3;

	ktb ++;
	for(i=0;;ktb++){
		if(!(msk & 0x0001)){
			LibPutMessage(ktb->msg,x+4,yy,IB_PFONT1);	/* ���ĕ\�� */
			yy += iy;
			i++;
			if(i>=ln)
				break;
		}
		msk = msk >> 1;
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�I����޳ ����

	[����]
		int		x	 : ����޳�\���J�n���W(X)
		int		y	 : ����޳�\���J�n���W(Y)
		int		xs	 : ����޳�\����(X)
		byte	ln	 : ����޳���\�����ڍs��(1,2,3,���)
		byte	np	 : ����޳�����]������̫�Ĉʒu(0,1,2,���)
							[ 0xff ����̫�Ĕ��]���� ]

		SLW_TBL *ktb : �I����޳�p�\���̐擪���ڽ

				{int msg, byte rtv},		1�s�ڕ\�����Ĕԍ�, 1�s�ڑI�����߂�l
				{int msg, byte rtv},		2�s�ڕ\�����Ĕԍ�, 2�s�ڑI�����߂�l
				{int msg, byte rtv},		3�s�ڕ\�����Ĕԍ�, 3�s�ڑI�����߂�l
						�E
						�E
						�E

	[�߂�l]
		�I����޳�p�\���̂Őݒ肳�ꂽ�߂�l
		 ( 0xff : ESCʰ�ޱ��݂�������ꂽ�� )

	[�������e]
		�I����޳���J��,�e�s�̑I�����p�ɐݒ肳�ꂽ�߂�l��Ԃ��
******************************************************************************/
byte LibSelWindow(int x, int y, int xs, byte ln, byte np, SLW_TBL *ktb)
/*TAIL*/
{
	byte	sl;
	byte	t_buf[128];
	int		i,o,t_size;

	LibSelWinTchSet();				/* ����ر�ݒ� */

	/*----- ����޳���ގZ�o   '98. 6.13 Y.Itoh -----*/
	for(xs=i=0;i<ln;i++){
	    LibReadMessage(ktb[i].msg,t_buf);	/* ү���ޓǂݍ��� */
		t_size = LibGetProStrSize(IB_PFONT1,t_buf);
		xs = max(t_size,xs);
	}

	xs += 8;

	/*** �ڷޭװ�΍� ***/

/*	o = 127 - (x+xs-1);		/* ���[�܂ł̗]�T */
	o = 159 - (x+xs-1);		/* ���[�܂ł̗]�T   '98.12.15 Y.Itoh �ύX */

	if(o < 0){				/* �Џo�Ă���     */
		x += o;
	/*	if(x<0)	x=0,xs=128;	*/
		if(x<0)	x=0,xs=160;		/* '98.12.15 Y.Itoh �ύX */
	}
	/*---------------------------------------------*/

	LibSelWinOpen(x,y,10,xs,ln,ktb);	/* �I����ް����� */
	sl = LibSelectWin(x,y,10,xs,ln,np);
									/* ����޳�ऍ��ڑI������ */
	LibCloseWindow();
	LibPutDisp();
	LibTchRelease();				/* �NULL��܂� POP */

	if(sl==0xff)					/* ESC ����� */
		return(0xff);
	return(ktb[sl].rtv);
}


/*HEAD*/
/******************************************************************************
	[����]
		�I����޳ ���� 2 (���ٕt��������\���ް�ޮ�)

	[����]
		int		y	 : ����޳�\���J�n���W(Y)
		byte	ln	 : no_mask�������޳���\�����ڍs��(1,2,3,���) �m���ق��܂ށn

		int		x_size:	����޳������	'00. 2.25  Y.Itoh

		SLW_TBL *ktb : �I����޳�p�\���̐擪���ڽ

				{int msg, byte rtv},		���ٕ\�����Ĕԍ�, �Ӗ������߂�l
				{int msg, byte rtv},		1�s�ڕ\�����Ĕԍ�, 1�s�ڑI�����߂�l
				{int msg, byte rtv},		2�s�ڕ\�����Ĕԍ�, 2�s�ڑI�����߂�l
						�E
						�E
						�E				��15 ���ڂ܂őΉ�

		word	msk	 : �\������Ͻ����
							�S���ڕ\���̎�		: 0x0000
							1�s�ڂ��\���̎�	: 0x0001 �� Bit �� ON
							2�s�ڂ��\���̎�	: 0x0002 �� Bit �� ON
							3�s�ڂ��\���̎�	: 0x0004 �� Bit �� ON
										�E
										�E
										�E
							15�s�ڂ��\���̎�	: 0x8000 �� Bit �� ON

	[�߂�l]
		�I����޳�p�\���̂Őݒ肳�ꂽ�߂�l
		 ( 0xff : ESCʰ�ޱ��݂�������ꂽ�� )

	[�������e]
		�I����޳���J��,�e�s�̑I�����p�ɐݒ肳�ꂽ�߂�l��Ԃ��
		�A����擪�s�����قƂ��ėp����̂őI��s�i�]���Ĥ�߂�l�͈Ӗ������j
******************************************************************************/
byte SpdSelWindow2(int y, byte ln, int x_size,SLW_TBL *ktb, word msk)
/*TAIL*/
{
	byte	sl,lc,fnt;
	byte	t_buf[128];
	int		i,t_size;
	int		x,xs;
	word	sft;

	LibSelWinTchSet();				/* ����ر�ݒ� */

	/*----- ����޳�����ގZ�o   -----*/
	sft = msk;
	sft = sft << 1;
	sft &= 0xfffe;						/* ���ق͕K���\�� */
	fnt = IB_PFONT2;					/* ���ق͑����� */
	for(xs=i=0,lc=0;i<=ln;i++){
		if(!(sft & 0x0001)){
			LibReadMessage(ktb[i].msg,t_buf);	/* ү���ޓǂݍ��� */
			t_size = LibGetProStrSize(fnt,t_buf);
			xs = max(t_size,xs);
			lc++;
			fnt = IB_PFONT1;			/* ���وȊO�͍ו��� */
		}
		sft = sft >> 1;
	}

	xs += 8;
/*	if(xs > 130){	/* �ڷޭװ�΍� */
	if(xs > 162){	/* �ڷޭװ�΍�  '98.12.15 Y.Itoh �ύX */
	/*	xs	= 130;	*/
		xs	= 162;	/*	'98.12.15 Y.Itoh �ύX */
	}
	/*------------------------------*/

#if 1	/* '00. 2.25  Y.Itoh */
	xs = max(x_size,xs);
#endif

/*	x = (128-xs)/2;		/* ����޳�J�n���W */
	x = (160-xs)/2;		/* ����޳�J�n���W '98.12.15 Y.Itoh �ύX */

	LibSelWinOpen2(x,y,9,xs,lc-1,ktb,msk);	/* �I����ް����� */

#if 0	/* '00. 2.25  Y.Itoh */
	sl = LibSelectWin(x,y+12,9,xs,lc-1,0);	/* ����޳�ऍ��ڑI������ */
#else	/* '00. 2.25  Y.Itoh */
	sl = LibSelectWin(x,y+12,9,xs,lc-1,0xff);	/* ����޳�ऍ��ڑI������ */
#endif

	LibCloseWindow();
	LibPutDisp();
	LibTchRelease();				/* �NULL��܂� POP */

	if(sl==0xff)					/* ESC ����� */
		return(0xff);

	lc = 0;							/* �I�����ꂽ���ڂ��Z�o */
	for(i=1;;i++){
		if(!(msk & 0x0001)){
			lc++;
			if(lc==sl+1)
				break;
		}
		msk = msk >> 1;
	}
	return(ktb[i].rtv);
}


/*HEAD*/
/******************************************************************************
	[����]
		�I����޳ �����

	[����]
		SLW2_ST	*slw 	: �I����޳�p�\����
		byte	ln		: �\���s��
		bool	opt		: ���ٗ]����߼��  (TRUE:�]���L�� / FALSE:�]������)

	[�������e]
		�I����޳���J�������޳���ɺ��ĕ\������
******************************************************************************/
static void LibSelWinOpenExt(SLW2_ST *slw, byte ln, bool opt)
/*TAIL*/
{
	word	i,yy;
	byte	*msg;
	byte	*mj;
	int		ys;

	ys = ln*slw->ity+6;			/* ����޳�c������ */
	if(opt==TRUE)
		ys += 11;

	ys++;	/* '99. 3.15  Y.Itoh */

	LibOpenWindow(slw->x,slw->y,slw->xs,ys);	/* �I����ް����� */
	LibSelWinFlm(slw->x,slw->y,slw->xs,ys);		/* �g���`�� */

	yy = slw->y+4;				/* ү���ޕ\���J�n�ʒu�w��(�c) */
	if(opt==TRUE)
		yy += 11;

	msg = slw->cmnt;
	for(i=0;i<ln;i++,yy+=slw->ity){
		LibStringDsp(msg,slw->x+slw->t_xs,yy,slw->x+slw->xs-5,IB_PFONT1);
												/* ������\�� */
		for(mj=msg;;mj++){
			if(*mj==0xfe || *mj==0){
				msg = mj+1;
				break;
			}
		}
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�I����޳ ����	�g���Łi�C��ү���ށj

	[����]
		SLW2_ST		*slw 		:in		�I����޳�p�\����

	[�߂�l]
		*rtv �Őݒ肳�ꂽ�߂�l
		 ( 0xff : ����޳�O��������ꂽ�� )

	[�������e]
		�I����޳���J��,�e�s�̑I�����p�ɐݒ肳�ꂽ�߂�l��Ԃ��
		�i�\�����Ă͌Œ�ү���ނł͂Ȃ���C�ӂ̕�����j
******************************************************************************/
byte LibSelWindowExt(SLW2_ST *slw)
/*TAIL*/
{
	byte	sl;
	byte	ln,i;
	byte	*aa;

	LibSelWinTchSet();				/* ����ر�ݒ� */

	aa = slw->rtv;
	for(i=0,ln=0;;i++){				/* ����޳�ऍs���擾 */
		if(aa[i]==0xff)
			break;
		ln++;
	}

	LibSelWinOpenExt(slw,ln,FALSE);	/* �I����ް����� */
	sl = LibSelectWin(slw->x,slw->y,slw->ity,slw->xs,ln,slw->np);
									/* ����޳�ऍ��ڑI������ */
	LibCloseWindow();
	LibPutDisp();

	LibTchRelease();				/* �NULL��܂� POP */

	if(sl==0xff)					/* ESC ����� */
		return(0xff);
	return(slw->rtv[sl]);
}


/***********************************************************************************/
/*    ү����ײ���؏����Q (SHIFT_NO�Ԃ��O�͋��ʏ���,�ȍ~�̎��͐�p�����֕���)     */
/***********************************************************************************/
/*HEAD*/
/******************************************************************************
	[����]
		�Œ�ү���ގ擾(�\�v�ZӰ�ޗp)

	[����]
		no				:in     ү����NO
		buf				:out	�ǂݏo���p�ޯ̧���ڽ

	[�߂�l]
		�Ȃ�

	[�������e]
		ү����NO�ɑΉ�����Œ�ү���ޕ�������擾����.
		�{�̂ɓ�������Ă��Ȃ�ү����(SHIFT_NO�Ԉȍ~)�̏ꍇ��,Ӱ�ޓ��ɒ�`����Ă���
		far�ް����g�p����.

******************************************************************************/
void LibReadMessage(word no,byte *buf)
/*TAIL*/
{
	byte	lang;

	if(no<SHIFT_NO){
		_LibReadMessage(no,buf);	/* ����ײ���؂����s */
	}
	else{
		lang = LibGetLang();
		far_strcpy(buf,MessageTable[(no-SHIFT_NO)*5+lang]);
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�Œ�ү���ޕ\��(�\�v�ZӰ�ޗp)

	[����]
		no				:in     ү����NO
		p_x				:in     �����W
		p_y				:in     �c���W
		type			:in     ̫�Ď��	IB_PFONT1	:�ް�����
											IB_PFONT2	:�w�i����
                                            IB_PFONT3	:���ٗp
                                            IB_CG57FONT	:5*7
	[�߂�l]
		�Ȃ�

	[�������e]
		ү����NO�ɑΉ�����Œ�ү���ނ�\������.
		�{�̂ɓ�������Ă��Ȃ�ү����(SHIFT_NO�Ԉȍ~)�̏ꍇ��,Ӱ�ޓ��ɒ�`����Ă���
		far�ް����g�p����.(LibReadMessage()�̌Ăяo��)

******************************************************************************/
void LibPutMessage(word no,int p_x,int p_y,byte type)
/*TAIL*/
{
	byte	buf[256];

	if(no<SHIFT_NO){
		_LibPutMessage(no,p_x,p_y,type);	/* ����ײ���؂����s */
	}
	else{
		LibReadMessage(no,buf);		/* SHIFT_NO�Ԉȍ~�ɑΉ�����ү���ޕ�������擾 */
		LibPutProStr(type,p_x,p_y,buf,160);
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�Œ�ү���ޕ\��	(����ݸގw��)(�\�v�ZӰ�ޗp)

	[����]
		no				:in     ү����NO
		p_x1			:in     ���[���W(�J�n)
		p_x2			:in     �E�[���W(�I��)
		p_y				:in     �c���W
		type			:in     ̫�Ď��	IB_PFONT1	:�ް�����
											IB_PFONT2	:�w�i����
                                            IB_PFONT3	:���ٗp
                                            IB_CG57FONT	:5*7
	[�߂�l]
		�Ȃ�

	[�������e]
		ү����NO�ɑΉ�����Œ�ү���ނ�,�w�肳�ꂽ�J�n�`�I���̗̈���ɾ���ݸޕ\������.
		�{�̂ɓ�������Ă��Ȃ�ү����(SHIFT_NO�Ԉȍ~)�̏ꍇ��,Ӱ�ޓ��ɒ�`����Ă���
		far�ް����g�p����.(LibReadMessage()�̌Ăяo��)

******************************************************************************/
void LibPutMessageCenter(word no,int p_x1,int p_x2,int p_y,byte type)
/*TAIL*/
{
	byte	buf[256];
	int		len,x;

	if(no<SHIFT_NO){
		_LibPutMessageCenter(no,p_x1,p_x2,p_y,type);	/* ����ײ���؂����s */
	}
	else{
		LibReadMessage(no,buf);		/* SHIFT_NO�Ԉȍ~�ɑΉ�����ү���ޕ�������擾 */
		len	= LibGetProStrSize(type,buf);
		x	= p_x1 + CENTER((p_x2-p_x1+1),len);
		LibPutProStr(type,x,p_y,buf,160);
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�Œ�ү���ޕ\��	(�E�񂹎w��)

	[����]
		no				:in     ү����NO
		p_x				:in     �E�[���W
		p_y				:in     �c���W
		type			:in     ̫�Ď��	IB_PFONT1	:�ް�����
											IB_PFONT2	:�w�i����
                                            IB_PFONT3	:���ٗp
                                            IB_CG57FONT	:5*7
	[�߂�l]
		�Ȃ�

	[�������e]
		�{�̂ɓ�������Ă��Ȃ�ү����(SHIFT_NO�Ԉȍ~)�̏ꍇ��,Ӱ�ޓ��ɒ�`����Ă���
		far�ް����g�p����.(LibReadMessage()�̌Ăяo��)

******************************************************************************/
void LibPutMessageRight(word no,int p_x,int p_y,byte type)
/*TAIL*/
{
	byte	buf[256];

	if(no<SHIFT_NO){
		_LibPutMessageRight(no,p_x,p_y,type);	/* ����ײ���؂����s */
	}
	else{
		LibReadMessage(no,buf);		/* SHIFT_NO�Ԉȍ~�ɑΉ�����ү���ޕ�������擾 */
		LibPutProStr(type,p_x-LibGetProStrSize(type,buf),p_y,buf,160);
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�޲�۸�ү���ލs���擾(�\�v�ZӰ�ޗp)

	[����]
		int		mes_no			:in		ү���ޔԍ�
		byte	w_pos			:in		����޳�\���ʒu
											0x00:			��ʉ�
											IX_MWIN_CENTER:	��ʒ���
		byte	b_cnt			:in		���ݐ�(0�`2)
		int		*y				:out	����޳�c���W
		int		*y_size			:out	����޳�c����

	[�߂�l]
		�s��-1 (0�`4)

	[�������e]
		�޲�۸�ү���ނ̍s��(�����񒆂�"@"��)���擾����
		�{�̂ɓ�������Ă��Ȃ�ү����(SHIFT_NO�Ԉȍ~)�̈�,Ӱ�ޓ��ɒ�`����Ă���
		far�ް����g�p����.

******************************************************************************/
static int SpdGetWinMessSize(int mes_no,byte w_pos,byte b_cnt,int *y,int *y_size)
/*TAIL*/
{
	int		i, lcnt;
	byte	buf[256];

	LibReadMessage(mes_no,buf);			/* SHIFT_NO�Ԉȍ~�ɑΉ�����ү���ޕ�������擾 */

	for(lcnt=0,i=0; i<256; i++){
		if(buf[i]==NULL){				/* �I�[���� */
			break;
		}else if(buf[i]=='@'){
			lcnt ++;					/* �s�� inc. */
		}
	}
	if(lcnt>4)
		lcnt = 4;						/* Max 5�s */

	*y = wim_yp[(b_cnt & 0x03)][lcnt];	/* �\��Y���W�擾 */
	*y_size = 161 - *y;					/* ����޳�c���擾 */

	if(w_pos==IX_MWIN_CENTER){			/* ��ʒ����w��̎� */
		*y = (*y)/2;
	}
	return(lcnt);
}


/*HEAD*/
/******************************************************************************
	[����]
		�޲�۸�ү���ޗp����޳���ގ擾(�\�v�ZӰ�ޗp)

	[����]
		int		mes_no			:in		ү���ޔԍ�
		byte	w_pos			:in		����޳�\���ʒu
											0x00:			��ʉ�
											IX_MWIN_CENTER:	��ʒ���
		byte	b_cnt			:in		���ݐ�(0�`2)
		int		*y				:out	����޳�c���W
		int		*y_size			:out	����޳�c����

	[�߂�l]
		�Ȃ�

	[�������e]
		�޲�۸�ү���ޗp�̳���޳�ʒu,���ނ��擾����.
		�{�̂ɓ�������Ă��Ȃ�ү����(SHIFT_NO�Ԉȍ~)�̏ꍇ��,Ӱ�ޓ��ɒ�`����Ă���
		far�ް����g�p����.

******************************************************************************/
void LibGetWinMessSize(int mes_no,byte w_pos,byte b_cnt,int *y,int *y_size)
/*TAIL*/
{
	if(mes_no<SHIFT_NO){
		_LibGetWinMessSize(mes_no,w_pos,b_cnt,y,y_size);	/* ����ײ���؂����s */

	}else{
		SpdGetWinMessSize(mes_no,w_pos,b_cnt,y,y_size);		/* �\�v�Z�p */
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�޲�۸�ү���ޗp�\��(�\�v�ZӰ�ޗp)

	[����]
		byte	g_no			:in		����(���̨��)�ԍ�
											IB_MWIN_NO_ICON �̎�,�Ȃ�
		int		mes_no			:in		ү���ޔԍ�
		byte	b_cnt			:in		���ݐ�(0�`2)
		byte	b_type			:in		���ݎ��
											IB_MWIN_NONE:		�Ȃ�
											IB_MWIN_YES_NO:		YES/NO(�{�^���Q��)
											IB_MWIN_SET_ESC:	SET/ESC(�{�^���Q��)
											IB_MWIN_OK:			OK(�{�^���P��)
											IB_MWIN_SET:		SET(�{�^���P��)
											IB_MWIN_ESC:		ESC(�{�^���P��)

											IX_MWIN_CENTER:		����޳�ʒu�����w��
	[�߂�l]
		�Ȃ�

	[�������e]
		�޲�۸�ү���ޗp�̕\�����s��.
		�{�̂ɓ�������Ă��Ȃ�ү����(SHIFT_NO�Ԉȍ~)�̏ꍇ��,Ӱ�ޓ��ɒ�`����Ă���
		far�ް����g�p����.

******************************************************************************/
void LibDspWinMessage(byte g_no,int mes_no,byte b_cnt,byte b_type)
/*TAIL*/
{
	int		lcnt, w_yp,w_ys;
	int		gdn, yof, yp, xp;
	byte	buf[256];
	int		gtp[5];
	int		i, j, hb;

	if(mes_no<SHIFT_NO){
		_LibDspWinMessage(g_no,mes_no,b_cnt,b_type);
											/* ����ײ���؂����s */
	}else{
		i = 0;
		if(b_type==IX_MWIN_CENTER)
			i = IX_MWIN_CENTER;
		lcnt = SpdGetWinMessSize(mes_no,i,b_cnt,&w_yp,&w_ys);
											/* ����޳���ޤ�\���J�n���W�擾 */
	  /*** ����޳���̨���\�� ***/
		if(w_yp==109 || w_yp==109/2){
			gdn = 107;
		}else if(w_yp==97 || w_yp==97/2){
			gdn = 108;
		}else{
			gdn = 109;
		}
		LibPutFarData(16, w_yp+1, gdn);

	  /*** ���ݕ\�� ***/
		if(g_no!=IB_MWIN_NO_ICON)
			LibPutFarData(24,w_yp+1+11,g_no);

	  /*** ���ݕ\�� ***/
		if((b_cnt & 0x03)>=1){				/* ���݂��P�ȏ�̎� */

			if(b_type<IB_MWIN_YES_NO || IB_MWIN_ESC<b_type)
				return;						/* ���͏����װ */

			yp = w_yp+w_ys-24;
			gdn = 113;
			if((b_cnt & 0x40)!=0)			/* �_���t��? */
				gdn = 114;
			LibPutFarData(106,yp,gdn);		/* �E���ݕ\�� */
			LibPutMessageCenter(bmsg[(b_type-IB_MWIN_YES_NO)][1],108,132,yp+4,IB_PFONT1);
											/* �E����ү���ޕ\�� */

			if((b_cnt & 0x03)>=2){			/* ���݂��Q�ȏ�̎� */
				gdn = 113;
				if((b_cnt & 0x80)!=0)		/* �_���t��? */
					gdn = 114;
				LibPutFarData(72,yp,gdn);	/* �����ݕ\�� */
				LibPutMessageCenter(bmsg[(b_type-IB_MWIN_YES_NO)][0],74,98,yp+4,IB_PFONT1);
											/* ������ү���ޕ\�� */
			}
		}

	  /*** ү���ޕ\�� ***/
		LibReadMessage(mes_no,buf);			/* ү���ޕ�������擾 */
		gtp[0] = 0;
		for(j=1,i=0;i<256;i++){
			if(buf[i]==NULL){
				break;
			}else if(buf[i]=='@'){
				buf[i] = NULL;				/* ���s���ނ�NULL�ɒu�� */
				gtp[j] = i+1;				/* �e�s�擪�ʒu�擾 */
				j ++;
			}
		}
		for(hb=0,i=0; i<=lcnt; i++){
			j = LibGetProStrSize(IB_PFONT1,&buf[gtp[i]]);	/* �e�s���擾 */
			if(hb < j)
				hb = j;						/* �ő�s���X�V */
		}

		i = 83;								/* ү���ލő�\����(���ݗL��̎�) */
		j = 50;								/* ү���ޕ\���ر���[(���ݗL��̎�) */
		if(g_no==IB_MWIN_NO_ICON){
			i = 107;						/* ү���ލő�\����(���ݖ����̎�) */
			j = 26;							/* ү���ޕ\���ر���[(���ݖ����̎�) */
		}
		if(hb>i)							/* ү���ޕ����ް */
			xp = j;	
		else
			xp = j+(i-hb)/2;				/* ү���ޕ\���J�nX���W */

		yof = wim_myof[(b_cnt&0x03)][lcnt];	/* ү���ޕ\���J�nY�̾�Ď擾 */
		yp = w_yp + 1 + yof;				/* ү���ޕ\���J�nY���W */

		for(i=0;i<=lcnt;i++){
			LibPutProStr(IB_PFONT1, xp, yp, &buf[gtp[i]],159);
			yp += 9;						/* ���s�c���W */
		}
	}
}


/*HEAD*/
/******************************************************************************
	[����]
		�e��ү���޳���ީ�\������(�\�v�ZӰ�ޗp)

	[����]
		byte icn ... �\�����ݸ��̨������
				ICON_NONE		: �Ȃ�
				ICON_OK			: OK
				ICON_BADTZ		: �~
				ICON_BIKKURI	: �I
				ICON_COFFEE		: ��˰����
				ICON_TRASH		: ���ݔ�
				ICON_SIGN		: ��
				ICON_SYNC		: �ʐM��

		word msg	: �\�����Ĕԍ�
			(���Ƃ���....)	323 : DATA_ITEM_NOT_FOUND!
							331 : OK_TO_DELETE@THE_DATA_ITEM?
							341 : DATA_STORED!

		byte wtyp	: ү��������
						0x00:�J�����ςȂ�...�(���ݖ���)	... ��ʒ���
						0x10:�J�����ςȂ�...�(���ݖ���)	... ��ʉ���
						0x01:1Sec�\��(���ݖ���)			... ��ʒ���
						0x11:1Sec�\��(���ݖ���)			... ��ʉ���
						0x02:�m�F(OK)���ݕt��			... ��ʉ���
						0x03:�m�F(ESC)���ݕt��			... ��ʉ���
						0x04:�m�F(SET)���ݕt��			... ��ʉ���
						0x05:�I��(Yes/No)���ݕt��		... ��ʉ���
						0x06:�I��(OK/ESC)���ݕt��		... ��ʉ���

	[�߂�l]
		bool jdg	: --- wtyp�� "5","6"�̎� ---
							TRUE	: Yes(OK)�I����
							FALSE	: No(ESC)�I����

					  --- wtyp�� "5","6"�ȊO�̎� ---
							TRUE

	[�������e]
		����޳ү���ނ�\������
		�{�̂ɓ�������Ă��Ȃ�ү����(SHIFT_NO�Ԉȍ~)�̏ꍇ��,Ӱ�ޓ��ɒ�`����Ă���
		far�ް����g�p����.

******************************************************************************/
bool LibWinIcnMsg(byte icn, word msg, byte wtyp)
/*TAIL*/
{
	word	win_ysz;
	word	ysp;
	byte	btyp;
	bool	jdg = TRUE;
	bool	loop = TRUE;
	TCHSTS	tsts;
	byte	btn;
	byte	w_pos = 0x00;	/* ��ʉ��w�� */
	byte	up_dwn = (wtyp & 0x10) >> 4;
	T_ICON far	*icon;

	wtyp &= 0x0f;

	if(icn>7)
		icn = 0;

	if(wtyp<2){					/* ���ݐ����� */
		btn = 0;
		w_pos = IX_MWIN_CENTER;			/* �Ƃ肠������ʒ����w�� �� */
		if(up_dwn == 1){
			w_pos = 0x00;				/* ��ʉ��w�� */
		}

	}else{
		LibTchStackPush( NULL );
		LibTchStackPush(TchHardIcon);	/* '98. 7.14 Y.Itoh */
		LibTchStackPush(TchBtnR);		/* �E���� ���ð��� */
		LibTchStackPush(TchActionKey);	/* ����ݷ�  ���ð��� */
		btn = 1;
	}
	if(wtyp>=5){
		btn = 2;
		LibTchStackPush(TchBtnL);		/* ������ ���ð��� */
	}

	LibGetWinMessSize(msg,w_pos,btn,&ysp,&win_ysz);	/* ����޳���ގ擾 */
/*	LibOpenWindow(0+16,ysp,128,win_ysz);		/* ����޳����� 	ZX485*/
	LibOpenWindow(0+16-1,ysp,128+2,win_ysz);	/* ����޳����� 	ZX485 '99. 1.22 Y.Itoh */

	btyp = wim_bt[wtyp];
	if(up_dwn == 1)
		btyp &= 0x0f;
	if(wtyp>=0x05)
		btn |= 0x80;
	else if(wtyp==0x02 || wtyp==0x04)
		btn |= 0x40;

	LibDspWinMessage(wim_ic[icn],msg,btn,btyp);	/* ����޳ү���ޕ\�� */


/******** '00.4.24  Y.Itoh *****************************************/
#if 0
	LibPutDisp();
#else
	if(wtyp==0){
		LibPutDispBox(0+16-1,ysp,128+2,win_ysz);
	}
	else{
		LibPutDisp();
	}
#endif
/*******************************************************************/


	while(loop==TRUE){
		switch(wtyp){
			case	0:				/** �J�����ςȂ� **/
				return(TRUE);

			case	1:				/** 1�bү���� **/
				LibWait(IB_1SWAIT);
				loop = FALSE;
				break;

			default:				/** �m�F���ݕt�� **/
			case	5:				/** ��ґ��� **/
			case	6:
				LibTchWait( &tsts );				/* ����҂� */
				if(tsts.obj==OBJ_BT_LFT){			/* ������ ����� */
					if(wtyp>=5){
						if(LibIconClick(&TicnBtnL,&tsts)==TRUE){
							jdg = TRUE;
							loop = FALSE;
						}
					}

				}else if(tsts.obj==OBJ_BT_RGT){		/* �E���� ����� */
					if(LibIconClick(&TicnBtnR,&tsts)==TRUE){
						if(wtyp>=5){
							jdg = FALSE;
						}else{
							jdg = TRUE;
						}
						loop = FALSE;
					}
				}else if(tsts.obj==OBJ_HIC_ESC){	/* �ESC�ʰ�ޱ�������̎� */
					if(wtyp>=5 || wtyp==3){
						jdg = FALSE;
						loop = FALSE;	/* '98. 7.16 Y.Itoh */
					}

				}else if(tsts.obj==OBJ_LPSW_PUSH){	/* ����ݷ� PUSH�� */
					if(wtyp>=2 || wtyp!=3){
						icon = &TicnBtnL;
						if(wtyp<0x05)
							icon = &TicnBtnR;
						if(LibIconClick(icon,&tsts)==TRUE){
							jdg = TRUE;
							loop = FALSE;
						}
					}
				}
				break;
		}
	}

	LibCloseWindow();			/* ����޳�۰�� */
	LibPutDisp();
	if(btn!=0){
		LibTchRelease();
	}
	return(jdg);
}
