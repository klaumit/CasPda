/******************************************************************************
	[ﾀｲﾄﾙ]
        拡張版ｽｸﾛｰﾙﾊﾞｰ処理用ﾍｯﾀﾞ

    [機種]
		ZX400 Referencer

	[作成者]
		鈴木茂人

	Copyright (C) 2000 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#ifndef SCR_BAR_DEF
#define SCR_BAR_DEF
#include    "define.h"

/************************************************/
/*                ﾘﾃﾗﾘ                          */
/************************************************/

/*@@SS #define DATA_MAX		60000	/* ﾃﾞｰﾀMAX件数 */
#define DATA_MAX		1000000	/*@@SS ﾃﾞｰﾀMAX件数 */

#define SCR_BOX_MIN		7		/* ｽｸﾛｰﾙBOX最小値(define.hからは削除する予定) */


/** @@SS 00.10.05 **/
/** ScrollBarPositionInformation */
/** typedef struct XT_SCR_POS{
/** 	int		x;				/* ScrollBarDisplayStartPosition X */
/** 	int		y;				/* ScrollBarDisplayStartPosition Y */
/** 	int		size;			/* ScrollBarHeight */
/** 	long	vol;			/* TotalCount      */
/** 	long	dsp;			/* DisplayCount    */
/** 	long	pos;			/* DisplayStartDataPosition */
/** } XT_SCR_POS;
*/

/*** ScrollBarPositionInformation @@SS 00.10.05 ***/
typedef struct XT_SCR_POS{
	int		x;				/* ScrollBarDisplayStartPosition X */
	int		y;				/* ScrollBarDisplayStartPosition Y */
	int		size;			/* ScrollBarHeight */
	long	vol;			/* TotalCount      */
	long	dsp;			/* DisplayCount    */
	long	pos;			/* DisplayStartDataPosition */
} XT_SCR_POS;
/**************************************************/


/************************************************/
/*             ﾌﾟﾛﾄﾀｲﾌﾟ宣言                     */
/************************************************/
void DLibScrollPrint(XT_SCR_POS scr);
void DLibScrollArrowPrint(XT_SCR_POS scr,byte mask);
int DLibScrollClick(TCHSTS *tsts,XT_SCR_POS *scr_pos);
int DLibScrPosCheck(TCHSTS tsts,XT_SCR_POS scr);


/************************************************/
/*              ｴﾘｱ定義                         */
/************************************************/
extern XT_SCR_POS		XTScr;


/************************************************/
/*                farﾃﾞｰﾀ                       */
/************************************************/

#endif
