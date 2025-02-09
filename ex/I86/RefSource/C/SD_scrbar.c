/******************************************************************************
	[����]
        �g���Ž�۰��ް�����pͯ��

	[�@��]
		ZX400 Referencer

	[�T�v]
		�g���Ž�۰��ް�֘Aײ����

	Copyright (C) 2000 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#include	<stdrom.h>
#include	"define.h"
#include	"libc.h"
#include    "l_define.h"
#include    "l_libc.h"
#include	"SD_scrbar.h"

/************************************************/
/*             �������ߐ錾                     */
/************************************************/
void DLibScrollPrintSub(XT_SCR_POS scr,bool arrow);
int DLibGetScrBoxSize(XT_SCR_POS scr,int *box_pos);

/* long DLibGetScrDspPos(XT_SCR_POS scr,int diff,TCHSTS *tsts);	/* @@SS 00.10.05 */
long DLibGetScrDspPos(XT_SCR_POS scr,int diff,TCHSTS *tsts);	/* @@SS 00.10.05 */

bool DLibScrPrmCheck(XT_SCR_POS scr);


/*HEAD*/
/******************************************************************************
	[����]
		��۰��ް�\��

	[����]
		XT_SCR_POS scr				:in		��۰��ް�ʒu���

	[�߂�l]
		�Ȃ�

	[�������e]
		��۰��ް��\������.

******************************************************************************/
void DLibScrollPrint(XT_SCR_POS scr)
/*TAIL*/
{
	DLibScrollPrintSub(scr,TRUE);
}


/*HEAD*/
/******************************************************************************
	[����]
		��۰��ް��������Ǘ�

	[����]
		const TCHSTS	*tsts			:in		����ð�����
		XT_SCR_POS		*scr_pos		:in/out	��۰��ް�ʒu���

	[�߂�l]
		����ʒu			0	����
						1	�����
						2	���Ԉ�	(�\���ύX����)
						4	�ړ���
						-1	�װ

	[�������e]
		��۰��ް������Ǘ����s��.
		�㉺���������ꂽ�ꍇ,(0,1)�̕ԋp�݂̂��s��.
		���Ԉ�(�\���߲��/��\���߲��)��������ꂽ�ꍇ,��۰�BOX�̈ړ��\�����s��,
		�����,�Ώ�ؽĒ��̘_���I�Ȉړ����scr_pos->pos�ɏo�͂���.

******************************************************************************/
int DLibScrollClick(TCHSTS *tsts,XT_SCR_POS *scr_pos)
/*TAIL*/
{
	int		diff;
	int		box_size,box_pos;
	int		y1, y2, tx, ty;
	int		ret;
/*	int		lastpos;	/* @@SS 00.10.05 */
	long	lastpos;	/* @@SS 00.10.05 */

	if(DLibScrPrmCheck(*scr_pos)==FALSE){	/* �����װ */
		return(-1);
	}

	if(scr_pos->vol == 0){					/* �����װ */
		return(-1);
	}

	tx = tsts->x;
	ty = tsts->y;
	y1 = scr_pos->y;
	y2 = scr_pos->y+scr_pos->size-1;

	if		(ty < y1+ARW_SIZE && scr_ret_bak != 2){		/* ���� */
		ret = 0;
	}
	else if (ty > y2-ARW_SIZE && scr_ret_bak != 2){		/* ����� */
		ret = 1;
	}
	else{												/* �\���߲��/��\���߲�� */
		if((scr_ret_bak==0 || scr_ret_bak==1) && tsts->act != ACT_MAKE){
			if(scr_ret_bak == 0){
				LibSKeyRevSub(scr_pos->x-1,scr_pos->y-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+ARW_SIZE-1+2,IB_GDS_KEYREV,IB_GDS_KREVP1);
			}
			else if(scr_ret_bak == 1){
				LibSKeyRevSub(scr_pos->x-1,scr_pos->y+scr_pos->size-ARW_SIZE-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+scr_pos->size-1+2,IB_GDS_KEYREV, IB_GDS_KREVP1);
			}
			LibTchInit();	/* ������ر */
			scr_ret_bak	= -1;
			ret			= -1;
		}
		else{
			if(scr_pos->vol <= scr_pos->dsp){

#if 1			/* '98. 8.17 �Ԋ|����Ԃ��ް��������ꂽ�疳�� */
				LibTchInit();	/* ������ر */
				scr_ret_bak	= -1;
				ret			= -1;
#endif

			}
			else{
				ret = 2;
			}
		}
	}

	switch(tsts->act){

		case ACT_MAKE:
			if		(ret == 0){
				if(scr_ret_bak != 0){
					LibSKeyRevSub(scr_pos->x-1,scr_pos->y-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+ARW_SIZE-1+2,IB_GDS_KEYREV,IB_GDS_KREVP1);
				}
				LibWait(IB_125MWAIT);	/* �ҋ@ */
			}
			else if	(ret == 1){
				if(scr_ret_bak != 1){
					LibSKeyRevSub(scr_pos->x-1,scr_pos->y+scr_pos->size-ARW_SIZE-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+scr_pos->size-1+2,IB_GDS_KEYREV, IB_GDS_KREVP1);
				}
				LibWait(IB_125MWAIT);	/* �ҋ@ */
			}
			else if	(ret == 2){

				box_size = DLibGetScrBoxSize(*scr_pos,&box_pos);
				if		(ty >= box_pos && ty <= box_pos+box_size-1){
					scr_sts = 1;			/* ��۰�BOX      */
				}
				else if	(ty < box_pos && ty > scr_pos->y+ARW_AREA-1){
					scr_sts = 2;			/* ��\���߲�ď� */
					scr_pos->pos -= scr_pos->dsp;
					if(scr_pos->pos < 0){
						scr_pos->pos = 0;
					}
					DLibScrollPrintSub(*scr_pos,FALSE);
				}
				else if	(ty > box_pos+box_size-1 && ty <= scr_pos->y+scr_pos->size-ARW_AREA-1){
					scr_sts = 3;			/* ��\���߲�ĉ� */
					scr_pos->pos += scr_pos->dsp;

					/* �ŏI�Ŕ��f */
					if(scr_pos->pos+scr_pos->dsp > scr_pos->vol){
						scr_pos->pos = scr_pos->vol-scr_pos->dsp;
					}

					DLibScrollPrintSub(*scr_pos,FALSE);
				}
				else{
					scr_sts = 0;
				}
				scr_tch_bak	= *tsts;
			}

			scr_ret_bak = ret;

			break;

		case ACT_MOVE_IN:
			if(ret==0||ret==1){
			/*	goto ARROW_IN;	*/
			}
			break;

		case ACT_DOWN_IN:

			if(scr_sts == 1){	/* BOX���� */
				diff = ty - scr_tch_bak.y;

				if(diff){
					scr_pos->pos = DLibGetScrDspPos(*scr_pos,diff,tsts);
					DLibScrollPrintSub(*scr_pos,FALSE);
					scr_tch_bak = *tsts;
				}
				ret = 4;	/* ���� */
				break;
			}

			box_size = DLibGetScrBoxSize(*scr_pos,&box_pos);

			if		(scr_sts == 2 && 
						ty >= y1+ARW_SIZE+2){	/* '98. 7. 6 �����ǉ� */

				if(ty < box_pos){
					scr_pos->pos -= scr_pos->dsp;
					if(scr_pos->pos < 0){
						scr_pos->pos = 0;
					}
					DLibScrollPrintSub(*scr_pos,FALSE);
				}
			}
			else if	(scr_sts == 3){
				if(ty > box_pos+box_size-1 && 
						ty <= y2-ARW_SIZE-2){	/* '98. 7. 6 �����ǉ� */

					scr_pos->pos += scr_pos->dsp;	/* ���ŕ��ݸ���� */

					/* �ŏI�ł̔��� */
					if(scr_pos->vol <= scr_pos->dsp){
						lastpos = 0;
					}
					else{
						lastpos = scr_pos->vol-scr_pos->dsp;
					}

					if(scr_pos->pos > lastpos){
						scr_pos->pos = lastpos;
					}

					DLibScrollPrintSub(*scr_pos,FALSE);
				}
			}
			break;

		ARROW_OUT:
		case ACT_MOVE_OUT:

#if 1	/* '98. 8.17 ������̱װш�v */
			if(tx == 0x8000 && ty == 0x8000){
				if		(scr_ret_bak == 0){
					LibSKeyRevSub(scr_pos->x-1,scr_pos->y-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+ARW_SIZE-1+2,IB_GDS_KEYREV,IB_GDS_KREVP1);
				}
				else if	(scr_ret_bak == 1){
					LibSKeyRevSub(scr_pos->x-1,scr_pos->y+scr_pos->size-ARW_SIZE-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+scr_pos->size-1+2,IB_GDS_KEYREV, IB_GDS_KREVP1);
				}
				LibPutDisp();
				LibTchInit();	/* ������ر */
				scr_ret_bak = -1;
				break;
			}
#endif

			if(ret == 2){
				DLibScrollPrintSub(*scr_pos,FALSE);
			}
			else if(ret == 4){
				DLibScrollPrintSub(*scr_pos,FALSE);
				ret = 2;
			}
			else if(ret == 0){
				LibSKeyRevSub(scr_pos->x-1,scr_pos->y-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+ARW_SIZE-1+2,IB_GDS_KEYREV,IB_GDS_KREVP1);
			}
			else if(ret == 1){
				LibSKeyRevSub(scr_pos->x-1,scr_pos->y+scr_pos->size-ARW_SIZE-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+scr_pos->size-1+2,IB_GDS_KEYREV, IB_GDS_KREVP1);
			}
			else{	/* �ر����O�ꂽ�ꍇ */
				LibPutDispBox(scr_pos->x-1,scr_pos->y-2,SCR_XSIZE+2,scr_pos->size+4);
			}
			scr_sts		= 0;
			scr_ret_bak = -1;
			LibTchInit();	/* ������ر */
			break;

		case ACT_BREAK_IN:
			if(ret==0||ret==1)	goto ARROW_OUT;
			scr_sts = 0;
			scr_ret_bak = -1;
			break;

		default:
			break;
	}

	if(ret == 0 || ret == 1){
		if(tsts->act != ACT_BREAK_IN){
			ret = -1;
		}
	}

	return(ret);
}


/*HEAD*/
/******************************************************************************
	[����]
		��۰��ް����ʒu����

	[����]
		TCHSTS		tsts			:in		����ð�����
		XT_SCR_POS	scr				:in		��۰��ް�ʒu���

	[�߂�l]
		int			����ʒu

	[�������e]
		��۰��ް������ʒu�������s��.

******************************************************************************/
int DLibScrPosCheck(TCHSTS tsts,XT_SCR_POS scr)
/*TAIL*/
{
	int		ret;
	int		y1, y2, ty;

	ty = tsts.y;
	y1 = scr.y;
	y2 = scr.y+scr.size-1;

	if	(ty < y1+ARW_SIZE && scr_ret_bak != 2){			/* ���� */
		ret = 0;
	}
	else if (ty > y2-ARW_SIZE && scr_ret_bak != 2){		/* ����� */
		ret = 1;
	}
	else{												/* BOX    */
		ret = 2;
	}

	return(ret);
}


/*HEAD*/
/******************************************************************************
	[����]
		��۰��ް�\��	<����>

	[����]
		XT_SCR_POS	scr				:in		��۰��ް�ʒu���
		bool		arrow			:in		��󕔕��`��L��

	[�߂�l]
		�Ȃ�

	[�������e]
		��۰��ް��\������.

	[����]
		�{�֐���,��ʱ��؂̉�ʏ�ԂɊւ�炸,��Έʒu�ɕ\������K�v�������,
		�\���n�֐���,����޳����݂ɂ����W��ڂ̔������Ȃ����̂��g�p���邱��.

******************************************************************************/
void DLibScrollPrintSub(XT_SCR_POS scr,bool arrow)
/*TAIL*/
{
	int		box_size,box_pos,
			dif_pos;

	if(DLibScrPrmCheck(scr)==FALSE){
		return;
	}

	if(arrow==TRUE){
		/* �S�̂����� */
		LibGdsClr(scr.x,scr.y,scr.x+SCR_XSIZE-1,scr.y+scr.size-1);
	}
	else{
		/* ��۰ٴر���̂ݏ��� */
		LibGdsClr(scr.x,scr.y+ARW_AREA,scr.x+SCR_XSIZE-1,scr.y+scr.size-1-ARW_AREA);
	}

	if(scr.dsp < scr.vol){

		box_size = DLibGetScrBoxSize(scr,&box_pos);

		/* ��۰ٴر���ɖԊ|�� */
		LibCngeBoxSub(scr.x,scr.y+ARW_AREA,scr.x+SCR_XSIZE-1,scr.y+scr.size-1-ARW_AREA,IB_GDS_REV);
		LibCngeBoxSub(scr.x,scr.y+ARW_AREA,scr.x+SCR_XSIZE-1,scr.y+scr.size-1-ARW_AREA,IB_GDS_MESH);

		if(arrow==TRUE){
			/* �㉺���`�� */
			DLibScrollArrowPrint(scr,SCR_NO_MASK);
		}

		dif_pos = box_pos;
		dif_pos = (dif_pos<scr.y+ARW_AREA)?scr.y+ARW_AREA:dif_pos;
		dif_pos = (dif_pos>scr.y+scr.size-ARW_AREA-box_size)?scr.y+scr.size-ARW_AREA-box_size:dif_pos;

		LibGdsClr(scr.x, dif_pos, scr.x+SCR_XSIZE-1,dif_pos+box_size-1);
		LibPutBoxSub( scr.x, dif_pos, scr.x+SCR_XSIZE-1,dif_pos+box_size-1,IB_GDS_OVER);

	}
	else{
		LibGdsBox(scr.x,scr.y+ARW_AREA,scr.x+SCR_XSIZE-1,scr.y+scr.size-1-ARW_AREA);
		LibCngeBoxSub(scr.x,scr.y,scr.x+SCR_XSIZE-1,scr.y+scr.size-1,IB_GDS_MESH);
		DLibScrollArrowPrint(scr,SCR_NO_MASK);
		DLibScrollArrowPrint(scr,SCR_ALL_MASK);
	}

/*	LibPutDisp();	*/
	LibPutDispBox(scr.x-1,scr.y-2,SCR_XSIZE+2,scr.size+4);
}


/*HEAD*/
/******************************************************************************
	[����]
		��۰�BOX ����/�ʒu�̎擾

	[����]
		XT_SCR_POS	scr				:in		��۰��ް�ʒu���
		int			*box_pos		:out	��۰�BOX �ʒu

	[�߂�l]
		box_size	��۰�BOX ����

	[�������e]
		��۰�BOX�̻��ނƈʒu���擾����.

******************************************************************************/
int DLibGetScrBoxSize(XT_SCR_POS scr,int *box_pos)
/*TAIL*/
{

/************************/
/*     '98. 8.27        */
/*	int		ratio,pos;	*/
	long	ratio,pos;
/************************/

	int		box_size;

	if(scr.vol == 0)	return(SCR_BOX_MIN);	/* �ی� ����̑Ώ� */

	/* ��۰�BOX ���ގZ�o */
	ratio = scr.dsp * DATA_MAX / scr.vol;					/* '98. 8.27 100��DATA_MAX */
	box_size = ((scr.size-ARW_AREA*2) * ratio) / DATA_MAX;	/* '98. 8.27 100��DATA_MAX */
	box_size++;	/* �␳ */
	box_size = (box_size<SCR_BOX_MIN)?SCR_BOX_MIN:box_size;

	/* ��۰�BOX �ʒu�Z�o */
	if(scr.pos==0){							/* 0�ԖڂȂ疳�����ōŏ�� */
		*box_pos = scr.y+ARW_AREA;
		return(box_size);
	}
	else if(scr.dsp >= scr.vol-scr.pos){	/* �c�茏������ʂɓ���Ȃ疳�����ōŉ��� */
		*box_pos = scr.y+scr.size-ARW_AREA-box_size;
		return(box_size);
	}
	else{									/* size����,1����������ޯĻ��ނ��Z�o */
		pos = (scr.size-ARW_AREA*2)*DATA_MAX /scr.vol;		/* '98. 8.27 100��DATA_MAX */
		pos = pos * scr.pos / DATA_MAX;					/* '98. 8.27 100��DATA_MAX */
		*box_pos = scr.y + ARW_AREA + pos;
		*box_pos = (*box_pos<scr.y+ARW_AREA)?scr.y+ARW_AREA:*box_pos;
		*box_pos = (*box_pos>scr.y+scr.size-ARW_AREA-box_size)?scr.y+scr.size-ARW_AREA-box_size:*box_pos;
	}

	return(box_size);
}


/*HEAD*/
/******************************************************************************
	[����]
		��۰��ްؽĈʒu�̎擾

	[����]
		XT_SCR_POS	scr				:in		��۰��ް�ʒu���
		int			diff			:in		�O��ʒu�Ƃ��ޯč�
		TCHSTS		*tsts			:in		����ð�����

	[�߂�l]
		dsp_pos		��۰��ްؽĕ\���ʒu

	[�������e]
		�ړ�������������۰�BOX�̑O��ʒu�Ƃ��ޯč�����,ؽď�̘_���I��
		�ʒu��ԋp����.

******************************************************************************/
long DLibGetScrDspPos(XT_SCR_POS scr,int diff,TCHSTS *tsts)
/*TAIL*/
{
/*	int		box_size,box_pos,dsp_pos,lastpos;	/* @@SS 00.10.05 */
/*	long	ratio,pos,t_nul;					/* @@SS 00.10.05 */
	int		box_size,box_pos;					/* @@SS 00.10.05 */
	long	pos, t_nul, lastpos, dsp_pos;		/* @@SS 00.10.05 */


	if(scr.vol == 0)	return(scr.pos);	/* �ی� ����̑Ώ� */

	lastpos = scr.vol-scr.dsp;	/* �ŏI��(�ى��)�̈ʒu */

	if(diff>0 && scr.pos>=lastpos){		/* ���ɍŏI��ʂ����� */
		return(scr.pos);
	}

	box_size = DLibGetScrBoxSize(scr,&box_pos);

	if(tsts->y < scr.y+ARW_AREA){				/* �ŏ�ʉ�ʂ���Ɉړ����ꂽ */
		return(0);
	}
	if(box_pos+diff-1 >= 						/* �ŉ��ʉ�ʂ�艺�Ɉړ����ꂽ */
			scr.y+scr.size-(box_size+ARW_AREA)){
		return(lastpos);
	}

	pos = tsts->y - (scr.y+ARW_AREA);

/*@@SS ******************************************************************/
/*@@SS 	ratio = pos*DATA_MAX / (scr.size-ARW_AREA*2);	/* '98. 8.27 100��DATA_MAX */
/*@@SS 	if(ratio>=DATA_MAX)	return(lastpos);		/* '98. 8.27 100��DATA_MAX */
/*@@SS 	t_nul = scr.vol * ratio / DATA_MAX;			/* '98. 8.27 100��DATA_MAX */
	if(pos>=(scr.size-ARW_AREA*2))					/*@SS 00.10.05 */
		return(lastpos);							/*@SS 00.10.05 */
	t_nul = scr.vol * pos / (scr.size-ARW_AREA*2);	/*@SS 00.10.05 */
/*@@SS ******************************************************************/

	dsp_pos = t_nul;
	dsp_pos -= scr.dsp / 2;
	dsp_pos++;	/* �␳ */
	dsp_pos = (dsp_pos<0)?0:dsp_pos;
	dsp_pos = (dsp_pos>scr.vol-scr.dsp)?lastpos:dsp_pos;

	return(dsp_pos);

}


/*HEAD*/
/******************************************************************************
	[����]
		��۰��ް��������

	[����]
		XT_SCR_POS	scr				:in		��۰��ް�ʒu���

	[�߂�l]
		bool		��������		TRUE:	����
									FALSE:	�װ
	[�������e]
		��۰��ް�̈����������s��.

******************************************************************************/
bool DLibScrPrmCheck(XT_SCR_POS scr)
/*TAIL*/
{
	/* ���ނ��s��(����������) */
	if(scr.size < ARW_AREA*2 + SCR_BOX_MIN + 2){
		return(FALSE);
	}

	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[����]
		��۰��ް�\��	<�㉺���>

	[����]
		XT_SCR_POS	scr				:in		��۰��ް�ʒu���
		byte		mask			:in		�Ԋ|���w��
												SCR_NO_MASK:	�Ԋ|���Ȃ�
												SCR_UP_MASK:	��Ԋ|��
												SCR_DWN_MASK:	���Ԋ|��
												SCR_ALL_MASK:	�㉺�Ԋ|��
	[�߂�l]
		�Ȃ�

	[�������e]
		��۰��ް�̏㉺����\������.

******************************************************************************/
void DLibScrollArrowPrint(XT_SCR_POS scr,byte mask)
/*TAIL*/
{

	if(mask == SCR_NO_MASK){

		/* �܂�,���]�̈���܂߂ď��� */
		LibGdsClr(scr.x-1,scr.y-2,scr.x+SCR_XSIZE-1+1,scr.y+ARW_SIZE-1+2);
		LibGdsClr(scr.x-1,scr.y+scr.size-ARW_SIZE-2,scr.x+SCR_XSIZE-1+1,scr.y+scr.size-1+2);

		/* �����ď㉺�̖���`��   */
		LibPutFarData(scr.x,scr.y,					260);	/* 9 * 5 */	/* �� */
		LibPutFarData(scr.x,scr.y+scr.size-ARW_SIZE,187);	/* 9 * 5 */	/* �� */
	}

	if(mask & SCR_UP_MASK){		/* �����Ͻ��\�� */
		LibPutFarData(scr.x,scr.y,174);						/* 9 * 5 */	/* �� */
	}

	if(mask & SCR_DWN_MASK){	/* ������Ͻ��\�� */
		LibPutFarData(scr.x,scr.y+scr.size-ARW_SIZE,173);	/* 9 * 5 */	/* �� */
	}
}


