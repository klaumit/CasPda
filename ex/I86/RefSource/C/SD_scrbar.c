/******************************************************************************
	[ﾀｲﾄﾙ]
        拡張版ｽｸﾛｰﾙﾊﾞｰ処理用ﾍｯﾀﾞ

	[機種]
		ZX400 Referencer

	[概要]
		拡張版ｽｸﾛｰﾙﾊﾞｰ関連ﾗｲﾌﾞﾗﾘ

	Copyright (C) 2000 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#include	<stdrom.h>
#include	"define.h"
#include	"libc.h"
#include    "l_define.h"
#include    "l_libc.h"
#include	"SD_scrbar.h"

/************************************************/
/*             ﾌﾟﾛﾄﾀｲﾌﾟ宣言                     */
/************************************************/
void DLibScrollPrintSub(XT_SCR_POS scr,bool arrow);
int DLibGetScrBoxSize(XT_SCR_POS scr,int *box_pos);

/* long DLibGetScrDspPos(XT_SCR_POS scr,int diff,TCHSTS *tsts);	/* @@SS 00.10.05 */
long DLibGetScrDspPos(XT_SCR_POS scr,int diff,TCHSTS *tsts);	/* @@SS 00.10.05 */

bool DLibScrPrmCheck(XT_SCR_POS scr);


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｽｸﾛｰﾙﾊﾞｰ表示

	[引数]
		XT_SCR_POS scr				:in		ｽｸﾛｰﾙﾊﾞｰ位置情報

	[戻り値]
		なし

	[処理内容]
		ｽｸﾛｰﾙﾊﾞｰを表示する.

******************************************************************************/
void DLibScrollPrint(XT_SCR_POS scr)
/*TAIL*/
{
	DLibScrollPrintSub(scr,TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｽｸﾛｰﾙﾊﾞｰﾀｯﾁ総合管理

	[引数]
		const TCHSTS	*tsts			:in		ﾀｯﾁｽﾃｰﾀｽ情報
		XT_SCR_POS		*scr_pos		:in/out	ｽｸﾛｰﾙﾊﾞｰ位置情報

	[戻り値]
		ﾀｯﾁ位置			0	上矢印
						1	下矢印
						2	中間域	(表示変更あり)
						4	移動中
						-1	ｴﾗｰ

	[処理内容]
		ｽｸﾛｰﾙﾊﾞｰのﾀｯﾁ管理を行う.
		上下矢印がﾀｯﾁされた場合,(0,1)の返却のみを行う.
		中間域(表示ﾎﾟｲﾝﾄ/非表示ﾎﾟｲﾝﾄ)がﾀｯﾁされた場合,ｽｸﾛｰﾙBOXの移動表示を行い,
		さらに,対象ﾘｽﾄ中の論理的な移動先をscr_pos->posに出力する.

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

	if(DLibScrPrmCheck(*scr_pos)==FALSE){	/* 引数ｴﾗｰ */
		return(-1);
	}

	if(scr_pos->vol == 0){					/* 引数ｴﾗｰ */
		return(-1);
	}

	tx = tsts->x;
	ty = tsts->y;
	y1 = scr_pos->y;
	y2 = scr_pos->y+scr_pos->size-1;

	if		(ty < y1+ARW_SIZE && scr_ret_bak != 2){		/* 上矢印 */
		ret = 0;
	}
	else if (ty > y2-ARW_SIZE && scr_ret_bak != 2){		/* 下矢印 */
		ret = 1;
	}
	else{												/* 表示ﾎﾟｲﾝﾄ/非表示ﾎﾟｲﾝﾄ */
		if((scr_ret_bak==0 || scr_ret_bak==1) && tsts->act != ACT_MAKE){
			if(scr_ret_bak == 0){
				LibSKeyRevSub(scr_pos->x-1,scr_pos->y-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+ARW_SIZE-1+2,IB_GDS_KEYREV,IB_GDS_KREVP1);
			}
			else if(scr_ret_bak == 1){
				LibSKeyRevSub(scr_pos->x-1,scr_pos->y+scr_pos->size-ARW_SIZE-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+scr_pos->size-1+2,IB_GDS_KEYREV, IB_GDS_KREVP1);
			}
			LibTchInit();	/* ﾀｯﾁ情報ｸﾘｱ */
			scr_ret_bak	= -1;
			ret			= -1;
		}
		else{
			if(scr_pos->vol <= scr_pos->dsp){

#if 1			/* '98. 8.17 網掛け状態のﾊﾞｰにﾀｯﾁされたら無効 */
				LibTchInit();	/* ﾀｯﾁ情報ｸﾘｱ */
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
				LibWait(IB_125MWAIT);	/* 待機 */
			}
			else if	(ret == 1){
				if(scr_ret_bak != 1){
					LibSKeyRevSub(scr_pos->x-1,scr_pos->y+scr_pos->size-ARW_SIZE-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+scr_pos->size-1+2,IB_GDS_KEYREV, IB_GDS_KREVP1);
				}
				LibWait(IB_125MWAIT);	/* 待機 */
			}
			else if	(ret == 2){

				box_size = DLibGetScrBoxSize(*scr_pos,&box_pos);
				if		(ty >= box_pos && ty <= box_pos+box_size-1){
					scr_sts = 1;			/* ｽｸﾛｰﾙBOX      */
				}
				else if	(ty < box_pos && ty > scr_pos->y+ARW_AREA-1){
					scr_sts = 2;			/* 非表示ﾎﾟｲﾝﾄ上 */
					scr_pos->pos -= scr_pos->dsp;
					if(scr_pos->pos < 0){
						scr_pos->pos = 0;
					}
					DLibScrollPrintSub(*scr_pos,FALSE);
				}
				else if	(ty > box_pos+box_size-1 && ty <= scr_pos->y+scr_pos->size-ARW_AREA-1){
					scr_sts = 3;			/* 非表示ﾎﾟｲﾝﾄ下 */
					scr_pos->pos += scr_pos->dsp;

					/* 最終頁判断 */
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

			if(scr_sts == 1){	/* BOX操作 */
				diff = ty - scr_tch_bak.y;

				if(diff){
					scr_pos->pos = DLibGetScrDspPos(*scr_pos,diff,tsts);
					DLibScrollPrintSub(*scr_pos,FALSE);
					scr_tch_bak = *tsts;
				}
				ret = 4;	/* 実験 */
				break;
			}

			box_size = DLibGetScrBoxSize(*scr_pos,&box_pos);

			if		(scr_sts == 2 && 
						ty >= y1+ARW_SIZE+2){	/* '98. 7. 6 条件追加 */

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
						ty <= y2-ARW_SIZE-2){	/* '98. 7. 6 条件追加 */

					scr_pos->pos += scr_pos->dsp;	/* 改頁分ｲﾝｸﾘﾒﾝﾄ */

					/* 最終頁の判定 */
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

#if 1	/* '98. 8.17 ﾀｯﾁ中のｱﾗｰﾑ一致 */
			if(tx == 0x8000 && ty == 0x8000){
				if		(scr_ret_bak == 0){
					LibSKeyRevSub(scr_pos->x-1,scr_pos->y-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+ARW_SIZE-1+2,IB_GDS_KEYREV,IB_GDS_KREVP1);
				}
				else if	(scr_ret_bak == 1){
					LibSKeyRevSub(scr_pos->x-1,scr_pos->y+scr_pos->size-ARW_SIZE-2,scr_pos->x+SCR_XSIZE-1+1,scr_pos->y+scr_pos->size-1+2,IB_GDS_KEYREV, IB_GDS_KREVP1);
				}
				LibPutDisp();
				LibTchInit();	/* ﾀｯﾁ情報ｸﾘｱ */
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
			else{	/* ｴﾘｱから外れた場合 */
				LibPutDispBox(scr_pos->x-1,scr_pos->y-2,SCR_XSIZE+2,scr_pos->size+4);
			}
			scr_sts		= 0;
			scr_ret_bak = -1;
			LibTchInit();	/* ﾀｯﾁ情報ｸﾘｱ */
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
	[ﾀｲﾄﾙ]
		ｽｸﾛｰﾙﾊﾞｰﾀｯﾁ位置ﾁｪｯｸ

	[引数]
		TCHSTS		tsts			:in		ﾀｯﾁｽﾃｰﾀｽ情報
		XT_SCR_POS	scr				:in		ｽｸﾛｰﾙﾊﾞｰ位置情報

	[戻り値]
		int			ﾀｯﾁ位置

	[処理内容]
		ｽｸﾛｰﾙﾊﾞｰのﾀｯﾁ位置ﾁｪｯｸを行う.

******************************************************************************/
int DLibScrPosCheck(TCHSTS tsts,XT_SCR_POS scr)
/*TAIL*/
{
	int		ret;
	int		y1, y2, ty;

	ty = tsts.y;
	y1 = scr.y;
	y2 = scr.y+scr.size-1;

	if	(ty < y1+ARW_SIZE && scr_ret_bak != 2){			/* 上矢印 */
		ret = 0;
	}
	else if (ty > y2-ARW_SIZE && scr_ret_bak != 2){		/* 下矢印 */
		ret = 1;
	}
	else{												/* BOX    */
		ret = 2;
	}

	return(ret);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｽｸﾛｰﾙﾊﾞｰ表示	<実体>

	[引数]
		XT_SCR_POS	scr				:in		ｽｸﾛｰﾙﾊﾞｰ位置情報
		bool		arrow			:in		矢印部分描画有無

	[戻り値]
		なし

	[処理内容]
		ｽｸﾛｰﾙﾊﾞｰを表示する.

	[注意]
		本関数は,上位ｱﾌﾟﾘの画面状態に関わらず,絶対位置に表示する必要がある為,
		表示系関数は,ｳｨﾝﾄﾞｳｵｰﾌﾟﾝによる座標ｽﾞﾚの発生しないものを使用すること.

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
		/* 全体を消去 */
		LibGdsClr(scr.x,scr.y,scr.x+SCR_XSIZE-1,scr.y+scr.size-1);
	}
	else{
		/* ｽｸﾛｰﾙｴﾘｱ内のみ消去 */
		LibGdsClr(scr.x,scr.y+ARW_AREA,scr.x+SCR_XSIZE-1,scr.y+scr.size-1-ARW_AREA);
	}

	if(scr.dsp < scr.vol){

		box_size = DLibGetScrBoxSize(scr,&box_pos);

		/* ｽｸﾛｰﾙｴﾘｱ内に網掛け */
		LibCngeBoxSub(scr.x,scr.y+ARW_AREA,scr.x+SCR_XSIZE-1,scr.y+scr.size-1-ARW_AREA,IB_GDS_REV);
		LibCngeBoxSub(scr.x,scr.y+ARW_AREA,scr.x+SCR_XSIZE-1,scr.y+scr.size-1-ARW_AREA,IB_GDS_MESH);

		if(arrow==TRUE){
			/* 上下矢印描画 */
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
	[ﾀｲﾄﾙ]
		ｽｸﾛｰﾙBOX ｻｲｽﾞ/位置の取得

	[引数]
		XT_SCR_POS	scr				:in		ｽｸﾛｰﾙﾊﾞｰ位置情報
		int			*box_pos		:out	ｽｸﾛｰﾙBOX 位置

	[戻り値]
		box_size	ｽｸﾛｰﾙBOX ｻｲｽﾞ

	[処理内容]
		ｽｸﾛｰﾙBOXのｻｲｽﾞと位置を取得する.

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

	if(scr.vol == 0)	return(SCR_BOX_MIN);	/* 保険 万一の対処 */

	/* ｽｸﾛｰﾙBOX ｻｲｽﾞ算出 */
	ratio = scr.dsp * DATA_MAX / scr.vol;					/* '98. 8.27 100→DATA_MAX */
	box_size = ((scr.size-ARW_AREA*2) * ratio) / DATA_MAX;	/* '98. 8.27 100→DATA_MAX */
	box_size++;	/* 補正 */
	box_size = (box_size<SCR_BOX_MIN)?SCR_BOX_MIN:box_size;

	/* ｽｸﾛｰﾙBOX 位置算出 */
	if(scr.pos==0){							/* 0番目なら無条件で最上位 */
		*box_pos = scr.y+ARW_AREA;
		return(box_size);
	}
	else if(scr.dsp >= scr.vol-scr.pos){	/* 残り件数が画面に入るなら無条件で最下位 */
		*box_pos = scr.y+scr.size-ARW_AREA-box_size;
		return(box_size);
	}
	else{									/* sizeから,1件あたりのﾄﾞｯﾄｻｲｽﾞを算出 */
		pos = (scr.size-ARW_AREA*2)*DATA_MAX /scr.vol;		/* '98. 8.27 100→DATA_MAX */
		pos = pos * scr.pos / DATA_MAX;					/* '98. 8.27 100→DATA_MAX */
		*box_pos = scr.y + ARW_AREA + pos;
		*box_pos = (*box_pos<scr.y+ARW_AREA)?scr.y+ARW_AREA:*box_pos;
		*box_pos = (*box_pos>scr.y+scr.size-ARW_AREA-box_size)?scr.y+scr.size-ARW_AREA-box_size:*box_pos;
	}

	return(box_size);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｽｸﾛｰﾙﾊﾞｰﾘｽﾄ位置の取得

	[引数]
		XT_SCR_POS	scr				:in		ｽｸﾛｰﾙﾊﾞｰ位置情報
		int			diff			:in		前回位置とのﾄﾞｯﾄ差
		TCHSTS		*tsts			:in		ﾀｯﾁｽﾃｰﾀｽ情報

	[戻り値]
		dsp_pos		ｽｸﾛｰﾙﾊﾞｰﾘｽﾄ表示位置

	[処理内容]
		移動が発生したｽｸﾛｰﾙBOXの前回位置とのﾄﾞｯﾄ差から,ﾘｽﾄ上の論理的な
		位置を返却する.

******************************************************************************/
long DLibGetScrDspPos(XT_SCR_POS scr,int diff,TCHSTS *tsts)
/*TAIL*/
{
/*	int		box_size,box_pos,dsp_pos,lastpos;	/* @@SS 00.10.05 */
/*	long	ratio,pos,t_nul;					/* @@SS 00.10.05 */
	int		box_size,box_pos;					/* @@SS 00.10.05 */
	long	pos, t_nul, lastpos, dsp_pos;		/* @@SS 00.10.05 */


	if(scr.vol == 0)	return(scr.pos);	/* 保険 万一の対処 */

	lastpos = scr.vol-scr.dsp;	/* 最終頁(ﾌﾙ画面)の位置 */

	if(diff>0 && scr.pos>=lastpos){		/* 既に最終画面だった */
		return(scr.pos);
	}

	box_size = DLibGetScrBoxSize(scr,&box_pos);

	if(tsts->y < scr.y+ARW_AREA){				/* 最上位画面より上に移動された */
		return(0);
	}
	if(box_pos+diff-1 >= 						/* 最下位画面より下に移動された */
			scr.y+scr.size-(box_size+ARW_AREA)){
		return(lastpos);
	}

	pos = tsts->y - (scr.y+ARW_AREA);

/*@@SS ******************************************************************/
/*@@SS 	ratio = pos*DATA_MAX / (scr.size-ARW_AREA*2);	/* '98. 8.27 100→DATA_MAX */
/*@@SS 	if(ratio>=DATA_MAX)	return(lastpos);		/* '98. 8.27 100→DATA_MAX */
/*@@SS 	t_nul = scr.vol * ratio / DATA_MAX;			/* '98. 8.27 100→DATA_MAX */
	if(pos>=(scr.size-ARW_AREA*2))					/*@SS 00.10.05 */
		return(lastpos);							/*@SS 00.10.05 */
	t_nul = scr.vol * pos / (scr.size-ARW_AREA*2);	/*@SS 00.10.05 */
/*@@SS ******************************************************************/

	dsp_pos = t_nul;
	dsp_pos -= scr.dsp / 2;
	dsp_pos++;	/* 補正 */
	dsp_pos = (dsp_pos<0)?0:dsp_pos;
	dsp_pos = (dsp_pos>scr.vol-scr.dsp)?lastpos:dsp_pos;

	return(dsp_pos);

}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｽｸﾛｰﾙﾊﾞｰ引数ﾁｪｯｸ

	[引数]
		XT_SCR_POS	scr				:in		ｽｸﾛｰﾙﾊﾞｰ位置情報

	[戻り値]
		bool		検査結果		TRUE:	正常
									FALSE:	ｴﾗｰ
	[処理内容]
		ｽｸﾛｰﾙﾊﾞｰの引数ﾁｪｯｸを行う.

******************************************************************************/
bool DLibScrPrmCheck(XT_SCR_POS scr)
/*TAIL*/
{
	/* ｻｲｽﾞが不正(小さすぎる) */
	if(scr.size < ARW_AREA*2 + SCR_BOX_MIN + 2){
		return(FALSE);
	}

	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｽｸﾛｰﾙﾊﾞｰ表示	<上下矢印>

	[引数]
		XT_SCR_POS	scr				:in		ｽｸﾛｰﾙﾊﾞｰ位置情報
		byte		mask			:in		網掛け指定
												SCR_NO_MASK:	網掛けなし
												SCR_UP_MASK:	上網掛け
												SCR_DWN_MASK:	下網掛け
												SCR_ALL_MASK:	上下網掛け
	[戻り値]
		なし

	[処理内容]
		ｽｸﾛｰﾙﾊﾞｰの上下矢印を表示する.

******************************************************************************/
void DLibScrollArrowPrint(XT_SCR_POS scr,byte mask)
/*TAIL*/
{

	if(mask == SCR_NO_MASK){

		/* まず,反転領域を含めて消去 */
		LibGdsClr(scr.x-1,scr.y-2,scr.x+SCR_XSIZE-1+1,scr.y+ARW_SIZE-1+2);
		LibGdsClr(scr.x-1,scr.y+scr.size-ARW_SIZE-2,scr.x+SCR_XSIZE-1+1,scr.y+scr.size-1+2);

		/* 続いて上下の矢印を描画   */
		LibPutFarData(scr.x,scr.y,					260);	/* 9 * 5 */	/* ▲ */
		LibPutFarData(scr.x,scr.y+scr.size-ARW_SIZE,187);	/* 9 * 5 */	/* ▼ */
	}

	if(mask & SCR_UP_MASK){		/* 上矢印をﾏｽｸ表現 */
		LibPutFarData(scr.x,scr.y,174);						/* 9 * 5 */	/* △ */
	}

	if(mask & SCR_DWN_MASK){	/* 下矢印をﾏｽｸ表現 */
		LibPutFarData(scr.x,scr.y+scr.size-ARW_SIZE,173);	/* 9 * 5 */	/* ▽ */
	}
}


