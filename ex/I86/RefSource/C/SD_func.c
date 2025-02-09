/******************************************************************************
	[����]
		Referencer

	[�@��]
		�ʐM�d�q�蒠(�C�O)

	[�T�v]
		Referencer �e��@�\����

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

SHOT_INF		Screen;			/* ��ذݼ��ėp */

/*HEAD*/
/******************************************************************************
	[����]
		ؽĕ\���������޳��ƭ��\���ݒ�
	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void DicPdwnSet(void)
/*TAIL*/
{
	word	p_set;

	LibPullDownInit(PdEdt,PdSys,PdOpt);		/* PullDown ������ */

	/*== [Edit]�Ԋ|���w�� ==*/
	p_set = 0;
	if((DicStatus==ST_LTCHIDLE)||(DicStatus==ST_STCHIDLE)){
											/* ؽĕ\��������ް��\���� */
	 	p_set |=  PDWN_EDT_CUT
 				| PDWN_EDT_COPY
 				| PDWN_EDT_PASTE;

 	}else{									/* ������͒� */
	 	p_set |=  PDWN_EDT_SRCH;
 	}
	LibPullDownAtrSet( PULLDOWN_HTNDSP, PULLDOWN_EDIT, p_set);


	/*== [System]�Ԋ|���w�� ==*/
	p_set = 0;
	if(DicStatus==ST_ILOOP){				/* ������͒� */
	 	p_set |=  PDWN_SYS_DTTM	
 				| PDWN_SYS_FORMT
 				| PDWN_SYS_MMANE
 				| PDWN_SYS_LANG;
	}
	LibPullDownAtrSet( PULLDOWN_HTNDSP, PULLDOWN_SYSTEM, p_set);



	/*== [Option]�Ԋ|���w�� ==*/
	p_set = 0;
	if(DicStatus==ST_ILOOP){			/* ������͒� */
		p_set |= PDWN_OPT_SCPY;
	}
	LibPullDownAtrSet( PULLDOWN_HTNDSP, PULLDOWN_OPTION, p_set);
}


/*HEAD*/
/******************************************************************************
	[����]
		����޳��ƭ���e��@�\����
	[����]
	[�߂�l]
		FALSE	: �ʏ�I��
		TRUE	: ��ʍĕ`��̕K�v����
	[�������e]
******************************************************************************/
bool DicPdwnFnc(TXTP *tp)
/*TAIL*/
{
	word	sel;
	bool	jdg = FALSE;

	sel = LibPullDown();		/* ����޳��ƭ� */

	if(sel & PULLDOWN_EDIT){	/* �Edit��I���̎� */
		jdg = PdwnFncEdt(sel,tp);

	}else if(sel & PULLDOWN_SYSTEM){
		jdg = PdwnFncSys(sel);

	}else if(sel & PULLDOWN_OPTION){
		jdg = PdwnFncOpt(sel);
	}
	return(jdg);
}



/*HEAD*/
/******************************************************************************
	[����]
		����޳��ƭ���e��@�\����(Edit�n)
	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
bool PdwnFncEdt(word sel, TXTP *tp)
/*TAIL*/
{
	bool	jdg = FALSE;

	switch(sel){

	/*** Copy ***/
		case PDWN_EDT_COPY:
			tp->txtst = TXTCOPY;
			break;

	/*** Cut ***/
		case PDWN_EDT_CUT:
			tp->txtst = TXTCUT;
			break;

	/*** Paste ***/
		case PDWN_EDT_PASTE:
			tp->txtst = TXTPASTE;
			break;

	/*** Search ***/
		case PDWN_EDT_SRCH:
			DicStatus = ST_IINI;		/* ��������͂� */
			jdg = TRUE;
			break;
	}
	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[����]
		����޳��ƭ���e��@�\����(System�n)
	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
bool PdwnFncSys(word sel)
/*TAIL*/
{
	bool	jdg = FALSE;
	switch(sel){

		case PDWN_SYS_DTTM:		/* Set_date/time		*/
			LibFuncDateTime();
			break;

		case PDWN_SYS_SOUND:	/* Sound				*/
			LibFuncSound(0);
			break;

		case PDWN_SYS_FORMT:	/* Format				*/
			LibFuncFormat();
			break;

		case PDWN_SYS_CAPCT:	/* Capacity				*/
			LibFuncCapa();
			break;

		case PDWN_SYS_MMANE:	/* Memory_management	*/
			LibFuncMemoryManagement();
			break;

		case PDWN_SYS_LANG:		/* Language				*/
			jdg = LibFuncLang();
			if(jdg==TRUE){
				if(DicStatus==ST_LTCHIDLE)		/* ���ݤؽĕ\�����Ȃ�... */
					DicStatus = ST_LDATADSP;	/* ؽĉ�ʏ������� */
				else if(DicStatus==ST_STCHIDLE)	/* ���ݤ�ް��\�����Ȃ�... */
					DicStatus = ST_SBKDSP;		/* �ް��ĕ\�� */
			}
			break;

		case PDWN_SYS_CNTRS:	/* Contrast				*/
			LibFuncContrast();
			break;

		case PDWN_SYS_TPA:		/* Touch_Panel_Alignment*/
			LibFuncDigitizer();
			break;

	/*	case PDWN_SYS_DTCOM:	/* Data_communication	*/
	/*		LibDataCom();
	/*		break;
	*/
	}
	return(jdg);
}

/*HEAD*/
/******************************************************************************
	[����]
		����޳��ƭ���e��@�\����(Option�n)
	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
bool PdwnFncOpt(word sel)
/*TAIL*/
{
	switch(sel){

	 /*** Screen Copy ***/
		case PDWN_OPT_SCPY:
			DicScrnShot();			/* ��ذݼ��� */
			break;
	}
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[����]
		Screen Shot �@�\����
	[����]
	[�߂�l]
	[�������e]
******************************************************************************/
void DicScrnShot(void)
/*TAIL*/
{
	Screen.x		= 0;				/* ���㉡ */
	Screen.y		= 13;				/* ����c */
	Screen.x_size	= 147-Screen.x+1;	/* ������ */
	Screen.y_size	= 140-Screen.y+1;	/* �c���� */
	Screen.p_x		= 6;				/* �\��t���ʒu �� */
	Screen.p_y		= 29;				/* �\��t���ʒu �c */

	LibScrShot(&Screen);				/* ��ذݼ��� */
}
