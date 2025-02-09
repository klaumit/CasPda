/******************************************************************************
	[����]
		Referencer

	[�@��]
		�ʐM�d�q�蒠(�C�O)

	[�T�v]
		Referencer ÷�ĕ\��ײ���ذ

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

/*	byte far	*wdtpp;			/* �P��擪�߲��� */
/*	int			wdtpx;			/* �P��擪X���W */
/*	byte		wdtpf;			/* �P��擪����̫�� */
DSPCT	wtct;				/* �P��擪��� */

SHWIDX	dltp[D_LNC+2];
byte	graphtmp[3200+4];

/*HEAD*/
/******************************************************************************
	[����]
		�P�s�\������

	[����]
		bool	den		: in �\������

	[�߂�l]
		TRUE	: ��s����I��(���s����������)
		FALSE	: �s�r���ŏI�����ޔ������A�܂��ʹװ�ɂ�鋭���I����
	[�������e]
******************************************************************************/
bool DicDsp1L(DSPCT *dct, bool den)
/*TAIL*/
{
	bool	ret = TRUE;
	byte	ccd;

	/* �s�擪�ݒ� */
	wtct = *dct;			/* �P��擪���Ƃ��đޔ� */

	while(ret==TRUE){
		ret = DicDsp1C(dct,den,&ccd);	/* �ꕶ���\������ */
	}
	if(ret==HALF)
		return(TRUE);
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[����]
		�P�����\������

	[����]
		bool	den		: in	�\������ ��	TRUE  :�\������
											FALSE :��\��
											HALF  :�������]�̂�
		byte	ccd		: out	���ގ��

	[�߂�l]
		TRUE	: �ʏ폈���I����
		HALF	: ���s����������
		FALSE	: �I�����ޔ������A�܂��ʹװ������
	[�������e]
******************************************************************************/
bool DicDsp1C(DSPCT *dct, bool den, byte *ccd)
/*TAIL*/
{
	bool	ret = TRUE;

	dct->code = *(dct->pot);		/* 1���ޓǂݍ��� */
	*ccd = JdgContCode(&dct->pot);	/* ���亰�ޔ��f */

	switch(*ccd){

		case CD_CHA:			/* �������ށu00h�`7Fh�v */
		case CD_OVCHA:			/* 1�޲ĺ��ގw��(0x80�ȏ�)�u80h�`FFh�v */
			if(Dsp1Cha(dct,den)==FALSE)
				ret = HALF;		/* ���R���s */
			break;

		case CD_RTN:			/* ���s���ށu0Dh�v */
	/*		dct->pot ++;	*/
			if(dct->st!=0){		/* ���o��������o����ݸ���o���̎� */
				dct->fnt = FNT_BASE;
				dct->st = 0;
			}
			NextLine(dct);
			ret = HALF;
			break;

		case CD_TITLE:			/* ���o���u@\T�v */
			dct->fnt = FNT_TITLE;
			dct->x = dct->sx - D_SFTX*2;
			dct->st = 2;
			break;

		case CD_LINK:			/* �ݸ���o���u@\L+������(1byte)�v */
			dct->fnt = FNT_LINKT;
			dct->x = dct->sx - D_SFTX*2;
			dct->st = 2;
			break;

		case CD_SUBT:			/* �����o���u@\C�v */
			dct->fnt = FNT_SUBT;
			dct->x = dct->sx - D_SFTX;
			dct->st = 1;
			break;

		case CD_GPDEF:			/* �摜�w��u@\g????�v */
			DspGraph(dct,den);
			break;

		case CD_END:			/* �I������(�����o��)�u@\T�v�u@\L�v */
			ret = FALSE;
			break;

		case CD_FNT57:			/* 5x7̫�Ďw��        �u@\fNM�v */
			dct->fnt = IB_CG57FONT;
			break;

		case CD_FNTPN:			/* ����߰����̫�Ďw�� �u@\fPN�v */
			dct->fnt = IB_PFONT1;
			break;

		case CD_FNTPB:			/* ������̫�Ďw��     �u@\fPB�v */
			dct->fnt = IB_PFONT2;
			break;

		case CD_LKDEF:			/* �ݸ�w��u@\l+������(1byte)�v */
			if(LinkSet(dct,den,FALSE)==FALSE){
				ret = FALSE;
			}
			break;

		case CD_JPDEF:			/* �ެ��ߎw��u@\j+������(1byte)�v */
			if(LinkSet(dct,den,TRUE)==FALSE){
				ret = FALSE;
			}
			break;
	}
	return(ret);
}


/*HEAD*/
/******************************************************************************
	[����]
		���亰�ޔ��f

	[����]
		byte	far **tgt	: in/out	���ޯĺ��ޱ��ڽ
										(���亰�ގ��ͽ���ߌ�̱��ڽ��Ԃ�)


	[�߂�l]
		CD_CHA		�������ށu00h�`7Fh(09h,0Dh�ȊO)�v
		CD_RTN		���s���ށu0Dh�v
		CD_OVCHA	1�޲ĺ��ގw��(0x80�ȏ�)�u@\x??�v
		CD_TITLE	���o���u@\T�v
		CD_SUBT		�����o���u@\C�v
		CD_GPDEF	�摜�w��u@\g????�v
		CD_END		�I������(�����o��)�u@\T�v,�u@\L�v
		CD_FNT57	5x7̫�Ďw��u@\fNM�v
		CD_FNTPN	����߰����̫�Ďw��u@\fPN�v
		CD_FNTPB	������̫�Ďw��u@\fPB�v
		CD_JPDEF	�ެ��ߎw��u@\j�����񒷁v
		CD_LKDEF	�ݸ�w��u@\l�����񒷁v
		CD_LINK		�ݸ���o���u@\L�����񒷁v

	[�������e]
******************************************************************************/
byte JdgContCode(byte far **tgt)
/*TAIL*/
{
	byte	ccd;
	byte	skip = 3;

	ccd = CD_CHA;					/* �Ƃ肠���� */

	if(**tgt==0x0d){
		ccd = CD_RTN;				/* ���s���� */
		skip = 1;

	}else if(**tgt==0x40){			/* �u@�v�̎� */

		if(*(*tgt+1)==0x5c){		/* 2�����ڂ��u\�v�̎� */

			if(*(*tgt+2)=='T'){		/* 3�����ڂ��uT�v�̎� */
				if(*tgt==dttop){
					ccd = CD_TITLE;			/* ���o������ */
				}else{
					ccd = CD_END;			/* �I������ */
				}

			}else if(*(*tgt+2)=='L'){	/* 3�����ڂ��uL�v�̎� */
				if(*tgt==dttop){
					ccd = CD_LINK;			/* �ݸ���o������ */
					skip = 4;
				}else{
					ccd = CD_END;			/* �I������ */
				}

			}else if(*(*tgt+2)=='C'){	/* 3�����ڂ��uC�v�̎� */
				if(*(*tgt-1)==0x0d){		/* 0�����ڂ����s���ނ̎� */
					ccd = CD_SUBT;			/* �����o�� */
				}

			}else if(*(*tgt+2)=='g'){	/* 3�����ڂ��ug�v�̎� */
				ccd = CD_GPDEF;				/* �摜�w�� */

			}else if(*(*tgt+2)=='j'){	/* 3�����ڂ��uj�v�̎� */
				ccd = CD_JPDEF;				/* �ެ��ߎw�� */

			}else if(*(*tgt+2)=='l'){	/* 3�����ڂ��ul�v�̎� */
				ccd = CD_LKDEF;				/* �ݸ�w�� */

			}else if(CmpStr(*tgt+2,"fNM",3)==TRUE){
				ccd = CD_FNT57;				/* 5x7̫�Ďw�� */
				skip = 5;
			}else if(CmpStr(*tgt+2,"fPN",3)==TRUE){
				ccd = CD_FNTPN;				/* ����߰����̫�Ďw�� */
				skip = 5;
			}else if(CmpStr(*tgt+2,"fPB",3)==TRUE){
				ccd = CD_FNTPB;				/* ������̫�Ďw�� */
				skip = 5;
			}
		}

	}else if(**tgt >= 0x80){
		ccd = CD_OVCHA;				/* 1�޲ĺ��ގw��(0x80�ȏ�) */
		skip = 0;
	}

	if(ccd==CD_CHA || ccd==CD_END)
		skip = 0;

	(*tgt) += skip;
	return(ccd);
}


/*HEAD*/
/******************************************************************************
	[����]
		1�����\��

	[����]
		bool	den		: in �\������	TRUE  : �\��
										FALSE : ��\��
										HALF  : �������]�̂�
	[�߂�l]
		TRUE	: ����I��
		FALSE	: ���s�����ׁ̈A�\�������B

	[�������e]
******************************************************************************/
bool Dsp1Cha(DSPCT *dct, bool den)
/*TAIL*/
{
	int		xp;
	word	pt;

	if(dct->y < dct->sy)			/* �\�����ł��͈͊O�ɂ͕\�����Ȃ� */
		den = FALSE;

	xp = LibGetProFontSize(dct->fnt,dct->code);	/* ���������擾 */

	if(dct->x + xp >= dct->ex){			/* �s���ӂꎞ */
		/*** ܰ��ׯ�ߏ��� ***/
		if(wtct.x > wtct.sx){		/* �s�擪����̒P��łȂ����... */
			if((den==TRUE)||(den==HALF)){		/* �s���܂ŉ�ʏ��� */
				if((wtct.x<wtct.ex)&&(wtct.y<wtct.ey))
					LibClrBox(wtct.x, wtct.y, wtct.ex-wtct.x, D_ITY);
			}
			*dct = wtct;
			wtct.x = wtct.sx;
		}
		NextLine(dct);							/* ���s���� */
		return(FALSE);
	}

	if(den==TRUE){
		LibPutProFont(dct->fnt,dct->code,dct->x,dct->y);
												/* �ꕶ���\�� */
		if(dct->pot < dct->lkpt){				/* �ݸ�L���� */
			if(dct->jpf==TRUE)					/* �ެ��߂̎� */
				LibLine(dct->x,(dct->y)+D_ITY-1,xp,1,1);	/* ���� */
			else								/* �ݸ�̎� */
				LibMeshLine(dct->x,(dct->y)+D_ITY-1,xp,1);	/* ���_�� */
		}

	}else if(den==HALF){				/* �������]�� */
		if((rsp!=0xffff)&&(rep!=0xffff)){
			pt = (word)(dct->pot-dttop);
			if((rsp<=pt)&&(pt<rep)){
				LibGdsReverse(dct->x,dct->y,dct->x+xp-1,dct->y+D_ITY-1);
			}
		}
	}

	dct->x += xp;
	dct->pot ++;

	/******* ܰ��ׯ�ߏ����Ή� ********/
	/*  ��߰��\����̕\������ޔ�  */
	/*********************************/
	if(dct->code==0x20 && (*(dct->pot)!=0x20) && (*(dct->pot)!=0x0d)){
								/* ��߰��ŁA������߰��ł����s�ł��Ȃ��� */
		wtct = *dct;			/* �P��擪���ޔ� */
	}

	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[����]
		���̨���\��

	[����]
	[�߂�l]
		TRUE	: ����I��
		FALSE	: ���s�����ׁ̈A�\�������B

	[�������e]
******************************************************************************/
bool DspGraph(DSPCT *dct, bool den)
/*TAIL*/
{
	byte far	*gdt;
	int			xs, ys;
	LSTIDX		lwk; 

	if(dct->x>=dct->ex){			/* �\���J�n���E�ɂ��ӂꂽ��... */
		NextLine(dct);				/* �摜�\����ɉ��s */
		return(FALSE);
	}

/*	dct->pot += 3;	*/

	lwk.num = GetGraphNum(dct->pot);	/* �摜�ԍ��擾 */
	DicGraphRead(&lwk);					/* �摜���ޯ������摜���ڽ�擾 */
	gdt = &Gbuf.bin_buf[0]+lwk.ofs;

	if(den==TRUE){
		PutGraphE(dct, gdt);	/* ���̨���\�� */
	}

	GetGraphSize(gdt, &xs, &ys);
	if(ys > dct->ity){
		if(ys%D_ITY >0){
			dct->ity = D_ITY * (ys/D_ITY +1);
		}else{
			dct->ity = ys;
		}
	}
	dct->x += xs;
	if(dct->x>=dct->ex)
		NextLine(dct);

	dct->pot += GL_LEN;
	wtct = *dct;			/* �P��擪���Ƃ��đޔ� */

	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[����]
		���̨���ް����ގ擾

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
long GraphDataSize(byte far *gdt)
/*TAIL*/
{
	int		xs,ys;
	int		cr=0;

	xs = (0xff & gdt[0]) + (gdt[1]<<8);
	ys = (0xff & gdt[2]) + (gdt[3]<<8);
	if((xs%8)>0)
		cr = 1;
	return(( xs/8 + cr ) * ys);
}


/*HEAD*/
/******************************************************************************
	[����]
		��۰ٗp���̨���\��

	[����]
		int		x				: in ���̨���\���J�n���W�iX�j
		int		y				: in ���̨���\���J�n���W�iY�j
		const byte far *graph	: in ���̨���ް�

	[�߂�l]
		FALSE	: �\���͑S�ĉ�ʊO�A���͸��̨�����޴װ
		TRUE	: ���̨������ʓ��ɑS�ĕ\��
		HALF	: ���̨�����ꕔ�\��

	[�������e]
******************************************************************************/
bool PutGraphE(DSPCT *dct, const byte far *graph)
/*TAIL*/
{
	int		xs, ys;					/* �摜���� */
	int		gx, gy;					/* �؂�o���J�n���W */
	int		gxs, gys;				/* �؂�o������(�\��t������) */
	int		xx, yy;					/* �\��t�����W */

	if(GetGraphSize(graph, &xs, &ys)!=TRUE)
		return(FALSE);					/* �摜���޴װ */


	/* ��ʓ��Ɏ��܂�ꍇ */
	if((dct->sx<=dct->x && dct->x+xs<dct->ex)
			 && (dct->sy<=dct->y && dct->y+ys<dct->ey)){
		LibPutGraph(dct->x,dct->y, graph );			/* ���̂܂ܸ��̨���\�� */
		return(TRUE);
	}
	/* �S�ĉ�ʊO�̏ꍇ */
	else if((dct->x+xs<=dct->sx || dct->ex<=dct->x)
				 || (dct->y+ys<=dct->sy || dct->ey<=dct->y)){
		return(FALSE);
	}

	/*** �Ƃ肠���� ***/
	gx = gy = 0;
	gxs = xs;
	gys = ys;
	xx = dct->x;
	yy = dct->y;

	/*** ���E�ւ݂̂͂��� ***/
	if(dct->x<dct->sx && dct->sx < dct->x+xs){				/* ��ʍ����ɂ͂ݏo��ꍇ */
		gx = dct->sx-dct->x;
		gxs = xs-gx;
		xx = dct->sx;
	}
	else if((dct->sx<=dct->x && dct->x<dct->ex)
				&&(dct->ex <= dct->x+xs)){	/* ��ʉE���ɂ͂ݏo��ꍇ */
		gx = 0;
		gxs = dct->ex-dct->x;
	}

	/*** �㉺�ւ݂̂͂��� ***/
	if(dct->y < dct->sy){				/* �㕔�ɂ͂ݏo��ꍇ */
		gy = dct->sy-dct->y;
		yy = dct->sy;
		gys = ys-gy;
		if(gys>dct->ey-dct->sy)		/* �㉺�����ɂ͂ݏo��ꍇ */
			gys = dct->ey-dct->sy;
	}
	else if(dct->ey < dct->y+ys){		/* �����ɂ݂̂͂ݏo��ꍇ */
		gy = 0;
		gys = dct->ey-dct->y;
	}

	/** BIOS�޸ޑ΍� **/
	if(xs < 9)
		xs = 9;
	if(gxs < 9)
		gxs = 9;

	LibOpenWindow(0,0,xs,ys);					/* ���̨���؂�o���pWindow */
	LibPutGraph(0, 0, graph );					/* ���̨���\�� */
	LibGetGraph(gx,gy,gxs,gys,&graphtmp[4]);	/* �摜�؂�o�� */
	LibCloseWindow();

	graphtmp[0] = gxs & 0xff;				/* �\��t�����ޕt�� */
	graphtmp[1] = gxs >> 8;
	graphtmp[2] = gys & 0xff;
	graphtmp[3] = gys >> 8;
	LibPutGraph(xx, yy, graphtmp );			/* ���̨���\�� */
}


/*HEAD*/
/******************************************************************************
	[����]
		�摜���ގ擾

	[����]
		const byte far *graph	: in	���̨���ް�
		int		*xs				: out	���̨���\�����ށiX�j
		int		*ys				: out	���̨���\�����ށiY�j

	[�߂�l]
		TRUE	: ����l
		FALSE	: �摜���޵��ް(160x160�ޯĂ��傫��)

	[�������e]
******************************************************************************/
bool GetGraphSize(const byte far *graph, int *xs, int *ys)
/*TAIL*/
{
	*xs = graph[0] + ((int)graph[1]<<8);	/* ���̨�������ގ擾 */
	*ys = graph[2] + ((int)graph[3]<<8);	/* ���̨���c���ގ擾 */
	if(*xs>160 || *ys>160)
		return(FALSE);
/*	if(*xs<=8)
/*		return(FALSE);
*/
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[����]
		���s����

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void NextLine(DSPCT *dct)
/*TAIL*/
{
	dct->x		= dct->sx;
	if(dct->st==1 || dct->st==2)	/* ���o������͏����o���̎� */
		dct->x -= D_SFTX*dct->st;	/* �\���J�n�ʒu�����ɼ�� */
	dct->y		+= dct->ity;
	dct->ity	= D_ITY;
}


/*HEAD*/
/******************************************************************************
	[����]
		���o�����޻��

	[����]
		byte far	**tgt		: in/out	�����J�n(����)�߲��

	[�߂�l]
		TRUE		: ����I���i�w�躰�ޔ����j
		FALSE		: ������

******************************************************************************/
bool TitleCodeSrc(byte far **tgt)
/*TAIL*/
{
	while(*tgt < (&Dbuf.bin_buf[10240])){

		if(CodeSrc(tgt,0x40)==FALSE)	/* �u@�v���޻�� */
			return(FALSE);
		(*tgt) ++;

		if(**tgt==0x5c){
			(*tgt) ++;

			if(**tgt=='T'){		/* �u@\T�v����! */
				(*tgt) -= 2;
				return(TRUE);
			}
		}
	}
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[����]
		���޻��

	[����]
		byte far	**tgt		: in/out	�����J�n(����)�߲��
		byte		cd			: in		�����Ώۺ���

	[�߂�l]
		TRUE		: ����I���i�w�躰�ޔ����j
		FALSE		: ������
	[�������e]
******************************************************************************/
bool CodeSrc(byte far **tgt, byte cd)
/*TAIL*/
{
/*	for(;(*tgt)<BUFEND;(*tgt)++){	*/
	for(;;(*tgt)++){				/* for TEST */

		if(**tgt==cd){
			return(TRUE);			/* ���ޔ����� */
		}

	}
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[����]
		���̨���ް�̧�ٓǂݍ���

	[����]
		word	flp		: in	̧���߲���(0�`)

	[�߂�l]
		TRUE	: ����I��
		FALSE	: �ǂݏo���װ

	[�������e]
******************************************************************************/
bool DicGraphFileRead(word flp)
/*TAIL*/
{
	if(Ginf.fp==flp)
		return(TRUE);
	Ginf.fp = flp;
	return(DicFileRead(&Gbuf,&Ginf));
}


/*HEAD*/
/******************************************************************************
	[����]
		���ް�̧�ٓǂݍ���

	[����]
		word	flp		: in	̧���߲���(0�`)

	[�߂�l]
		TRUE	: ����I��
		FALSE	: �ǂݏo���װ

	[�������e]
******************************************************************************/
bool DicDataFileRead(word flp)
/*TAIL*/
{
	if(Dinf.fp==flp)
		return(TRUE);
	Dinf.fp = flp;
	return(DicFileRead(&Dbuf,&Dinf));
}


/*HEAD*/
/******************************************************************************
	[����]
		���ޯ��̧�ٓǂݍ���

	[����]
		word	flp		: in	̧���߲���(0�`)

	[�߂�l]
		TRUE	: ����I��
		FALSE	: �ǂݏo���װ

	[�������e]
******************************************************************************/
bool DicIndexFileRead(word flp)
/*TAIL*/
{
	if(Iinf.fp==flp)
		return(TRUE);
	Iinf.fp = flp;
	return(DicFileRead(&Ibuf,&Iinf));
}


/*HEAD*/
/******************************************************************************
	[����]
		DB̧�ٓǂݍ���

	[����]

	[�߂�l]
		TRUE	: ����I��
		FALSE	: �ǂݏo���װ

	[�������e]
		10KByte���޲�ذ̧�ق�ǂݍ��ށB
		��а�ް�24Byte���l�����A�i160+1�j��ۯ��ǂݍ��ގ��I
******************************************************************************/
bool DicFileRead(LFBUF far *buf, FILE_INFO *inf)
/*TAIL*/
{
	bool	jdg;

	jdg = LibLFileReadEx((LFILE_BUF far *)buf,inf,161);
									/* �擪(10K+64)Byte�̂ݓǂݍ��� */
	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[����]
		1�ް��ǂݍ���

	[����]

		LSTIDX	*lidx		: ؽĲ��ޯ���\����
			lidx.num			  in	�擾���ޯ���ԍ�
			lidx.flp			  in	�Y�����ޯ���߲����̊܂܂��̧���߲���
			lidx.ofs			  in	�Y�����ޯ���߲����̵̾��

		byte far **tgt		: out	�ް��J�n���ڽ(�u@\*�v�̎�)

	[�߂�l]

		TRUE	: ����I��
		FALSE	: �ǂݏo���װ

	[�������e]
******************************************************************************/
bool DicDataRead(LSTIDX	*lidx, byte far **tgt)
/*TAIL*/
{
	word	flp, ofs;

	if(lidx->num==0xffffffff)
		return(FALSE);

	if(DicIndexFileRead(lidx->flp)==TRUE){	/* ���ޯ���߲����Y����ۯ��ǂݍ��� */
		flp = *(word far *)(&Ibuf.bin_buf[0] + lidx->ofs + 4 ) + topfp;
		ofs = *(word far *)(&Ibuf.bin_buf[0] + lidx->ofs + 6 );

		if(DicDataFileRead(flp)==TRUE){		/* ���ް��ǂݍ��� */
			*tgt = &Dbuf.bin_buf[0] + ofs;
			*tgt += 3;					/* �@\T������ */
			return(TRUE);
		}
	}
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[����]
		���̨�� 1 �ް��ǂݍ���

	[����]
		LSTIDX	*lidx		: in/out	���ޯ���\����

	[�߂�l]
		TRUE	: ����I��
		FALSE	: �ǂݏo���װ

	[�������e]
******************************************************************************/
bool DicGraphRead(LSTIDX *lidx)
/*TAIL*/
{
	bool		jdg;
	word		ofs, flp, i;
	long		bict,num;
	byte far	*tgt;

	num = lidx->num;
	flp = topfp + gtopbk;		/* ���̨�����ޯ���擪���܂܂��̧�� */
	ofs = gtopof;

	bict = (SZ_BLOCK-gtopof)/8;

	DicGraphFileRead(flp);			/* ���̨��index�ް��ǂݍ��� */

	for(i=0;i<gidxc;i++){

		jdg = JdgGraphIndex(ofs,num);		/* ���ޯ��ް���index�����f */
		if(jdg!=HALF){
			break;
		}else{
			ofs += 8;
			if(ofs>=SZ_BLOCK){
				flp ++;
				ofs = 0;
				if(DicGraphFileRead(flp)==FALSE){	/* ���̨��index�ް��ǂݍ��� */
					jdg = FALSE;
					break;
				}
			}
		}
	}

	if(jdg==TRUE){
		tgt = &Gbuf.bin_buf[0] + ofs;
		flp = topfp + *(word far *)(tgt+4);
		ofs = *(word far *)(tgt+6);			/* ���ް��J�n�̾�� */
		if(DicGraphFileRead(flp)==FALSE)	/* ���̨�����ް��ǂݍ��� */
			return(FALSE);
		lidx->flp = flp;
		lidx->ofs = ofs;
	}

	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[����]
		���̨�����ޯ�� ���

	[����]
	[�߂�l]
		TRUE	: �Y�����ޯ������
		HAFF	: �Y�����ޯ���ł͂Ȃ�
		FALSE	: ���̨�����ޯ���I��

	[�������e]
******************************************************************************/
bool JdgGraphIndex(word ofs, word gnum)
/*TAIL*/
{
	byte far	*tgt;

	tgt = &Gbuf.bin_buf[0] + ofs;
	if(*tgt!=0x05)
		return(FALSE);
	tgt += 2;

	if(gnum==*(word far *)(tgt))
		return(TRUE);
	return(HALF);
}


/*HEAD*/
/******************************************************************************
	[����]
		���̨���\��

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
/*	long GetGraphNum(byte far *tgt)	*/
word GetGraphNum(byte far *tgt)
/*TAIL*/
{
#if 0
	long	gnum;

	gnum = 		(	(long)(*tgt)     <<	24	)
			+	(	(long)(*(tgt+1)) <<	16	)
		 	+	(	(long)(*(tgt+2)) <<	8	)
		 	+	(	(long)(*(tgt+3))		);
	return(gnum);

#else
	return(*(word far *)(tgt));
#endif
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\�����s���擾

	[����]
		byte far	*tgt	: in	�ް��J�n�߲���

	[�߂�l]
		
	[�������e]
		÷�ďc��(D_ITY)����s���Ƃ��āA�ꌏ���ް������s���Ȃ̂��𒲂ׂ�
		�A���Buf�ɂ͊Y���ް����܂���ۯ���ǂݍ���ł������
******************************************************************************/
long GetDicDspL(byte far *tgt, DSPCT *dctwk)
/*TAIL*/
{
	int		lc = 0;
	bool	loop = TRUE;
	int		i;

	dctwk->fnt	= IB_PFONT1;
/*	dctemp.pot	= tgt;			/* �ް��J�n���ڽ*/
	dctwk->pot	= dttop;
	dctwk->lkpt	= dctwk->pot;
	dctwk->jpf	= FALSE;

	while(loop){
		dctwk->y = dctwk->sy;				/* �s�擪�͍��[ */
		if(DicDsp1L(dctwk,FALSE)==FALSE)	/* ��s������ */
			loop = FALSE;
		i = (dctwk->y - dctwk->sy)/dctwk->ity;
		lc += i;
	}
/*	return(lc+1);	*/
	return(lc);
}


/*HEAD*/
/******************************************************************************
	[����]
		�������r

	[����]
		byte far	*stra	: ��r�Ώە�����`
		byte far	*strb	: ��r�Ώە�����a
		int			len		: ��r������

	[�߂�l]
		TRUE	: ��v
		FALSE	: �s��v

	[�������e]
******************************************************************************/
bool CmpStr(byte far *stra, byte far *strb, int len)
/*TAIL*/
{
	int		i;

	for(i=0;i<len;i++){
		if(*stra!=*strb)
			return(FALSE);
		stra ++;
		strb ++;
	}
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[����]
		�ݸ����

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
bool LinkSet(DSPCT *dct, bool den, bool jpf)
/*TAIL*/
{
	byte		ct;
	byte		j,ccd;
	byte far	*tgt;

	ct = *dct->pot;					/* �ݸ�w�蕶�����擾 */
	if(ct>TT_LEN)
		return(FALSE);

	dct->pot ++;

	/*** �ݸ�w��I���ʒu�擾 ***/
	tgt = dct->pot;
	for(j=0;j<ct;){
		ccd = JdgContCode(&tgt);	/* ���亰�ޔ��f */

		switch(ccd){

			case CD_CHA:		/* �������ށu00h�`7Fh�v */
			case CD_OVCHA:		/* 1�޲ĺ��ގw��(0x80�ȏ�)�u@\x??�v */
				tgt ++;
				j ++;
				break;

			case CD_FNT57:		/* 5x7̫�Ďw��        �u@\fNM�v */
			case CD_FNTPN:		/* ����߰����̫�Ďw�� �u@\fPN�v */
			case CD_FNTPB:		/* ������̫�Ďw��     �u@\fPB�v */
				break;

		/*	case CD_RTN:		/* ���s���ށu0Dh�v */
			default:			/* Fail Safe */
				return(FALSE);
		}
	}
	dct->lkpt = tgt;
	dct->jpf  = jpf;

/*	if(lkpsp<LKPSCT){			/* ���ʓ��ő��ݸ�ݒ萔�ȉ��̎� */
/*		lkps[lkpsp].smp = dct->pot - dttop;		/* �ݸ�ݒ�ر�ޔ� */
/*		lkps[lkpsp].emp = lkps[lkpsp].smp + i;
/*		lkpsp ++;
/*	}
*/
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
    [����]
    	ESC���݌���

    [����]
    	�Ȃ�

    [�߂�l]
    	bool			��������	TRUE:	ESC���݂��������
    								FALSE:	            �Ȃ�
    [�������e]
    	ESCʰ�ޱ��݂��������Ă��邩��������.
    	�A���^�̏�������ڰ����ɗp����.

    [���l]
		SpredSheet(ZX481)��藬�p����uSpdTchEscScan()�v
******************************************************************************/
bool DicTchEscScan(void)
/*TAIL*/
{

#if 0

	extern TCHTBL far	*TchStack[];
	extern int			TchStackPointer;

	#define IB_EVTSCAN	0x02
	#define IX_TCHPANEL	0x01
    union   REGS    ireg, oreg;
	struct	SREGS	sreg;
	TCHSTS			tsts;

    ireg.h.ah	= IB_EVTSCAN;
    ireg.h.al	= IX_TCHPANEL;
	sreg.ds		= FP_SEG(TchStack[TchStackPointer]);
	ireg.x.si	= FP_OFF(TchStack[TchStackPointer]);
	sreg.es		= FP_SEG(&tsts);
	ireg.x.di	= FP_OFF(&tsts);
	int86x(EVTLIB, &ireg, &oreg, &sreg);

	return(	tsts.x >= TchHardIcon[7].x1	&&
			tsts.x <= TchHardIcon[7].x2	&&
			tsts.y >= TchHardIcon[7].y1	&&
			tsts.y <= TchHardIcon[7].y2
	);
	#undef IB_EVTSCAN
	#undef IX_TCHPANEL

#endif
}


/*HEAD*/
/******************************************************************************
    [����]
    	�uPlease Wait...�vү���ޕ\��

    [���l]
		SpredSheet(ZX481)��藬�p����uSpdWaitingMes()�v
******************************************************************************/
void DicWaitingMes(void)
/*TAIL*/
{
	if(MesDone == FALSE)
		return;

	LibWinIcnMsg(ICON_COFFEE,381,0);
	LibCloseWindow();					/* LibWinIcnMsg(0)�� */
	MesDone = TRUE;
}


/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\�������۰��ް Up/Down���� Ͻ��w��
	[����]
	[�߂�l]
		byte   mask : �}�X�N���
						SCR_NO_MASK:    �Ԋ|���Ȃ��ŏ㉺�Ƃ��\��
						SCR_UP_MASK:    �����Ԋ|���ɂ���
						SCR_DWN_MASK:   ������Ԋ|���ɂ���
						SCR_ALL_MASK:   �㉺�Ƃ��Ԋ|��
	[�������e]
******************************************************************************/
byte LstArrowMask(XT_SCR_POS *scr)
/*TAIL*/
{
	byte	mask;

	mask = SCR_NO_MASK;			/* �Ƃ肠�����㉺�Ƃ��Ԋ|���Ȃ� */

	if(lcp==0 && scr->pos==0){
		mask |= SCR_UP_MASK;		/* �㷰 Ͻ� */
	}

	if(lcp==L_LNC-1 && scr->pos==scr->vol - scr->dsp){
		mask |= SCR_DWN_MASK;		/* ���� Ͻ� */

	}else if(lcp<L_LNC-1 && lip[lcp+1].num==0xffffffff){
		mask |= SCR_DWN_MASK;		/* ���� Ͻ� */
	}
	return(mask);
}


/*HEAD*/
/******************************************************************************
	[����]
		�ް��\�������۰��ް Up/Down���� Ͻ��w��
	[����]
	[�߂�l]
		byte   mask : �}�X�N���
						SCR_NO_MASK:    �Ԋ|���Ȃ��ŏ㉺�Ƃ��\��
						SCR_UP_MASK:    �����Ԋ|���ɂ���
						SCR_DWN_MASK:   ������Ԋ|���ɂ���
						SCR_ALL_MASK:   �㉺�Ƃ��Ԋ|��
	[�������e]
******************************************************************************/
byte DataArrowMask(XT_SCR_POS *scr)
/*TAIL*/
{
	byte	mask;

	mask = SCR_NO_MASK;			/* �Ƃ肠�����㉺�Ƃ��Ԋ|���Ȃ� */

	if(scr->pos==0){
		mask |= SCR_UP_MASK;		/* �㷰 Ͻ� */
	}

	if(scr->pos>=scr->vol - scr->dsp){
		mask |= SCR_DWN_MASK;		/* ���� Ͻ� */
	}
	return(mask);
}


/*HEAD*/
/******************************************************************************
	[����]
		̧���߲���������

	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void FilePointerInit()
/*TAIL*/
{
	Ginf.fp = Dinf.fp = Iinf.fp = 0xffff;		/* �擪̧�� */
	Ginf.kind = Dinf.kind = Iinf.kind = 1;		/* �޲�؎��� */
}
