/******************************************************************************
	[ﾀｲﾄﾙ]
		Referencer ﾓｰﾄﾞ  ﾒｯｾｰｼﾞ処理群

	[機種]
		ZX400 Referencer

	[概要]
		5カ国語言語ﾒｯｾｰｼﾞ処理に関する処理群.
		本体に内蔵していないﾒｯｾｰｼﾞも同じﾗｲﾌﾞﾗﾘｲﾝﾀｰﾌｪｰｽで表示できるように,
		ここの処理で吸収する.

	[作成者]
		鈴木茂人

	[備考]
		ZX481表計算ﾓｰﾄﾞより流用､改造

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
/*               共通ﾗｲﾌﾞﾗﾘ処理群 (関数名を変更してそのまま移植)              */
/******************************************************************************/
/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		固定ﾒｯｾｰｼﾞ取得

	[引数]
		no				:in     ﾒｯｾｰｼﾞNO
		buf				:out	読み出し用ﾊﾞｯﾌｧｱﾄﾞﾚｽ

	[戻り値]
		なし

	[処理内容]
		ﾒｯｾｰｼﾞNOに対応する固定ﾒｯｾｰｼﾞ文字列を取得する.
		内容は,設定されている｢国｣の情報に応じて自動的に変化する.

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
	[ﾀｲﾄﾙ]
		固定ﾒｯｾｰｼﾞ表示

	[引数]
		no				:in     ﾒｯｾｰｼﾞNO
		p_x				:in     横座標
		p_y				:in     縦座標
		type			:in     ﾌｫﾝﾄ種別	IB_PFONT1	:ﾃﾞｰﾀﾀｲﾌﾟ
											IB_PFONT2	:背景ﾀｲﾌﾟ
                                            IB_PFONT3	:ﾀｲﾄﾙ用
                                            IB_CG57FONT	:5*7
	[戻り値]
		なし

	[処理内容]
		ﾒｯｾｰｼﾞNOに対応する固定ﾒｯｾｰｼﾞを表示する.表示される内容は,設定されている｢国｣の情報
		に応じて自動的に変化する.

	[補足]
		5つの修飾ﾊﾟﾀｰﾝが用意されているが,ここでは上書きﾓｰﾄﾞのみとする.

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
	[ﾀｲﾄﾙ]
		固定ﾒｯｾｰｼﾞ表示	(ｾﾝﾀﾘﾝｸﾞ指定)

	[引数]
		no				:in     ﾒｯｾｰｼﾞNO
		p_x1			:in     左端座標(開始)
		p_x2			:in     右端座標(終了)
		p_y				:in     縦座標
		type			:in     ﾌｫﾝﾄ種別	IB_PFONT1	:ﾃﾞｰﾀﾀｲﾌﾟ
											IB_PFONT2	:背景ﾀｲﾌﾟ
                                            IB_PFONT3	:ﾀｲﾄﾙ用
                                            IB_CG57FONT	:5*7
	[戻り値]
		なし

	[処理内容]
		ﾒｯｾｰｼﾞNOに対応する固定ﾒｯｾｰｼﾞを,指定された開始～終了の領域内にｾﾝﾀﾘﾝｸﾞ表示する.
		表示される内容は,設定されている｢国｣の情報に応じて自動的に変化する.

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
	[ﾀｲﾄﾙ]
		固定ﾒｯｾｰｼﾞ表示	(右寄せ指定)

	[引数]
		no				:in     ﾒｯｾｰｼﾞNO
		p_x				:in     右端座標
		p_y				:in     縦座標
		type			:in     ﾌｫﾝﾄ種別	IB_PFONT1	:ﾃﾞｰﾀﾀｲﾌﾟ
											IB_PFONT2	:背景ﾀｲﾌﾟ
                                            IB_PFONT3	:ﾀｲﾄﾙ用
                                            IB_CG57FONT	:5*7
	[戻り値]
		なし

	[処理内容]
		ﾒｯｾｰｼﾞNOに対応する固定ﾒｯｾｰｼﾞを,指定された右端座標に合わせて右寄せ表示する.
		表示される内容は,設定されている｢国｣の情報に応じて自動的に変化する.

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
	[ﾀｲﾄﾙ]
		ﾀﾞｲｱﾛｸﾞﾒｯｾｰｼﾞ用ｳｨﾝﾄﾞｳｻｲｽﾞ取得

	[引数]
		int		mes_no			:in		ﾒｯｾｰｼﾞ番号
		byte	w_pos			:in		ｳｨﾝﾄﾞｳ表示位置
											0x00:			画面下
											IX_MWIN_CENTER:	画面中央
		byte	b_cnt			:in		ﾎﾞﾀﾝ数(0～2)
		int		*y				:out	ｳｨﾝﾄﾞｳ縦座標
		int		*y_size			:out	ｳｨﾝﾄﾞｳ縦ｻｲｽﾞ

	[戻り値]
		なし

	[処理内容]
		ﾀﾞｲｱﾛｸﾞﾒｯｾｰｼﾞ用のｳｨﾝﾄﾞｳ位置,ｻｲｽﾞを取得する.

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
	[ﾀｲﾄﾙ]
		ﾀﾞｲｱﾛｸﾞﾒｯｾｰｼﾞ用表示

	[引数]
		byte	g_no			:in		ｱｲｺﾝ(ｸﾞﾗﾌｨｯｸ)番号
											IB_MWIN_NO_ICON の時,なし
		int		mes_no			:in		ﾒｯｾｰｼﾞ番号
		byte	b_cnt			:in		ﾎﾞﾀﾝ数(0～2)
		byte	b_type			:in		ﾎﾞﾀﾝ種別
											IB_MWIN_NONE:		なし
											IB_MWIN_YES_NO:		YES/NO(ボタン２つ)
											IB_MWIN_SET_ESC:	SET/ESC(ボタン２つ)
											IB_MWIN_OK:			OK(ボタン１つ)
											IB_MWIN_SET:		SET(ボタン１つ)
											IB_MWIN_ESC:		ESC(ボタン１つ)

											IX_MWIN_CENTER:		ｳｨﾝﾄﾞｳ位置中央指定
	[戻り値]
		なし

	[処理内容]
		ﾀﾞｲｱﾛｸﾞﾒｯｾｰｼﾞ用の表示を行う.

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
	[ﾀｲﾄﾙ]
		選択ｳｲﾝﾄﾞｳ ﾀｯﾁｴﾘｱ定義

	[処理内容]
******************************************************************************/
static void LibSelWinTchSet(void)
/*TAIL*/
{
	LibTchStackPush( NULL );
	LibTchStackPush(TchAllDsp);		/* 全画面ﾀｯﾁｴﾘｱ */
	LibTchStackPush(TchHardIcon);	/* ﾊｰﾄﾞｱｲｺﾝ ﾀｯﾁﾃｰﾌﾞﾙ */
	LibTchStackPush(TchActionKey);	/* ｱｸｼｮﾝｷｰ  ﾀｯﾁﾃｰﾌﾞﾙ */
	LibTchInit();
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		選択ｳｲﾝﾄﾞｳ枠描画
	[引数]
	[処理内容]
******************************************************************************/
static void LibSelWinFlm(int x, int y, int xs, int ys)
/*TAIL*/
{
	LibLine(x+2,y+1,xs-4,1,1);			/* 枠(上) */
	LibLine(x+1,y+2,1,ys-4,1);			/* 枠(左) */
	LibLine(x+2,y+ys-3,xs-4,1,2);		/* 枠(下) */
	LibLine(x+xs-3,y+2,1,ys-4,2);		/* 枠(右) */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		選択ｳｲﾝﾄﾞｳ ｵｰﾌﾟﾝ
	[引数]
		word *tbl	: ｺﾒﾝﾄﾃｰﾌﾞﾙ
	[処理内容]
		選択ｳｲﾝﾄﾞｳを開き､ｳｲﾝﾄﾞｳ内にｺﾒﾝﾄ表示する
******************************************************************************/
static void LibSelWinOpen(int x, int y, int ity, int xs, byte ln, SLW_TBL *ktb)
/*TAIL*/
{
	word	i,yy;
	int		ys;

	ys = ln*ity+6;					/* ｳｲﾝﾄﾞｳ縦幅決定 */
	if(ity==9)
		ys ++;

	LibOpenWindow(x,y,xs,ys);		/* 選択ｳｨﾝﾄﾞｰｵｰﾌﾟﾝ */
	LibSelWinFlm(x,y,xs,ys);		/* 枠線描画 */

	yy = y+4;
	for(i=0;i<ln;i++,yy+=ity,ktb++){
		LibPutMessage(ktb->msg,x+4,yy,IB_PFONT1);	/* ｺﾒﾝﾄ表示 */
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		選択ｳｨﾝﾄﾞｳ表示中、ﾀｯﾁ時行算出
	[引数]
		TCHSTS	*tsts	: ﾀｯﾁｽﾃｰﾀｽ
		int		xp		: ｳｲﾝﾄﾞｳ表示開始座標（X）
		int		yp		: ｳｲﾝﾄﾞｳ表示開始座標（Y）
		byte	iy		: 項目表示間隔（Y）
		int		xs		: ｳｲﾝﾄﾞｳ表示幅（X）
		byte	ln		: 選択ｳｲﾝﾄﾞｳ内行数

	[戻り値]
		ﾀｯﾁ該当行位置(0,1,2,3,...,)    0xff : ｳｨﾝﾄﾞｳ外 
	[処理内容]
		ﾀｯﾁされた箇所が､選択ｳｲﾝﾄﾞｳ上で何行目であるか算出する
******************************************************************************/
static byte LibSelWinTchLn(TCHSTS *tsts, int xp, int yp, byte iy, int xs, byte ln)
/*TAIL*/
{
	word	i,ly;

	if((tsts->x < xp) || (xp+xs-1 < tsts->x))		/* 横に外れている時 */
		return(0xff);

	if((tsts->y < yp+2) || (yp+ln*iy+2 < tsts->y))	/* 縦に外れている時 */
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
	[ﾀｲﾄﾙ]
		ｳｲﾝﾄﾞｳ内､項目選択処理

	[引数]
		int		x		: ｳｲﾝﾄﾞｳ表示開始座標（X）
		int		y		: ｳｲﾝﾄﾞｳ表示開始座標（Y）
		byte	iy		: 項目表示間隔（Y）
		int		xs		: ｳｲﾝﾄﾞｳ表示幅（X）
		byte	ln		: 選択ｳｲﾝﾄﾞｳ内行数
		byte np			: ﾃﾞﾌｫﾙﾄ反転位置(ﾃﾞﾌｫﾙﾄ反転が無い時は0xff)

	[処理内容]
		ﾀｯﾁ待ち､及び反転ｶｰｿﾙ表示
******************************************************************************/
static byte LibSelectWin(int x, int y, byte iy, int xs,  byte ln, byte np)
/*TAIL*/
{
	TCHSTS	tsts;
	byte	rvc;
	bool	scen;

	rvc = np;				/* とりあえず選択位置は､ﾃﾞﾌｫﾙﾄ位置 */
/*	dfp = rvc;	*/

	for(scen=TRUE;;){
		if(rvc!=0xff){
			LibReverse(x+3,y+rvc*iy+3,xs-7,9);	/* 反転ｶｰｿﾙ表示 */

#if 0	/* '00. 2.15  Y.Itoh */
			LibPutDisp();						/* 表示更新 */
#endif
		}
#if 1	/* '00. 2.15  Y.Itoh */
		LibPutDisp();						/* 表示更新 */
#endif

		LibTchWait(&tsts);						/* ﾀｯﾁ待ち */
		if(rvc!=0xff)
			LibReverse(x+3,y+rvc*iy+3,xs-7,9);	/* 反転ｶｰｿﾙ戻し */

	/** ｱｸｼｮﾝｷｰ ﾀｯﾁ時 **/
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

	/*** ｢ESC｣ﾊｰﾄﾞｱｲｺﾝﾀｯﾁ時 ***/
		}else if(tsts.obj==OBJ_HIC_ESC){
			return(0xff);

	/*** 画面(ｳｲﾝﾄﾞｳ内外)ﾀｯﾁ時 ***/
		}else if(tsts.obj==OBJ_ALLTCH){
			rvc = 0xff;
			if(scen==TRUE){
				rvc = LibSelWinTchLn(&tsts,x,y,iy,xs,ln);
											/* ｳｲﾝﾄﾞｳ内ﾀｯﾁ行算出 */
		/*		if(rvc!=0xff)
		/*			dfp = rvc;				/* 最終位置更新 */
			}

		/** ﾍﾟﾝｵﾝ時 **/
			if(tsts.act==ACT_MAKE){
				if(rvc==0xff){
					scen = FALSE;			/* 以降､SCAN中止 */
				}

		/** ﾍﾟﾝﾌﾞﾚｲｸ時 **/
			}else if(tsts.act==ACT_BREAK){
				if(scen==FALSE || (scen==TRUE && rvc!=0xff)){
									/* 画面外でﾍﾟﾝｵﾝ､または画面外でﾍﾟﾝｵﾌ */
					break;
				}else{
					rvc = np;				/* ｶｰｿﾙはﾃﾞﾌｫﾙﾄ位置 */
				}

			}else{
				if(rvc==0xff){				/* ｳｲﾝﾄﾞｳから外れた時 */
					rvc = np;				/* ｶｰｿﾙはﾃﾞﾌｫﾙﾄ位置 */
				}
			}
		}
	}
	return(rvc);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		選択ｳｲﾝﾄﾞｳ ｵｰﾌﾟﾝ
	[引数]
		int		x		: ｳｲﾝﾄﾞｳ表示開始座標（X）
		int		y		: ｳｲﾝﾄﾞｳ表示開始座標（Y）
		byte	iy		: 項目表示間隔（Y）
		int		xs		: ｳｲﾝﾄﾞｳ表示幅（X）
		byte	ln		: 選択ｳｲﾝﾄﾞｳ内行数
		SLW_TBL *ktb	: 選択ｳｲﾝﾄﾞｳ用構造体ﾎﾟｲﾝﾀｰ
		word	msk		: 表示項目ﾏｽｸ情報

	[処理内容]
		選択ｳｲﾝﾄﾞｳを開き､ｳｲﾝﾄﾞｳ内にｺﾒﾝﾄ表示する
******************************************************************************/
static void LibSelWinOpen2(int x, int y, byte iy, int xs, byte ln, SLW_TBL *ktb, word msk)
/*TAIL*/
{
	word	i,yy;
	int		ys;

	ys = (ln+1)*iy+6+4;					/* ｳｲﾝﾄﾞｳ縦幅決定 */

	LibOpenWindow(x,y,xs,ys);			/* 選択ｳｨﾝﾄﾞｰｵｰﾌﾟﾝ */
	LibSelWinFlm(x,y,xs,ys);			/* 枠線描画 */


#if 1	/* '99. 3.11  Y.Itoh */
	LibDotOff((xs+x-1)-2,y+1);	/* 右上角消去 */
	LibDotOff((xs+x-1)-1,y+2);	/* 右上角消去 */

	LibDotOff(x+1,(ys+y-1)-2);	/* 左下角消去 */
	LibDotOff(x+2,(ys+y-1)-1);	/* 左下角消去 */
#endif

	yy = y+4;

	LibPutMessageCenter(ktb->msg,x,x+xs-2,yy,IB_PFONT2);	/* ﾀｲﾄﾙ表示 */
	yy += iy;

/*	LibLine(x+6,yy,xs-13,1,1);	/* ﾀｲﾄﾙ下線 */
	LibLine(x+3,yy,xs-7,1,1);	/* ﾀｲﾄﾙ下線(ZX486新ﾃﾞｻﾞｲﾝで延長) '99. 3.11  Y.Itoh */

	yy += 3;

	ktb ++;
	for(i=0;;ktb++){
		if(!(msk & 0x0001)){
			LibPutMessage(ktb->msg,x+4,yy,IB_PFONT1);	/* ｺﾒﾝﾄ表示 */
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
	[ﾀｲﾄﾙ]
		選択ｳｲﾝﾄﾞｳ 処理

	[引数]
		int		x	 : ｳｲﾝﾄﾞｳ表示開始座標(X)
		int		y	 : ｳｲﾝﾄﾞｳ表示開始座標(Y)
		int		xs	 : ｳｲﾝﾄﾞｳ表示幅(X)
		byte	ln	 : ｳｲﾝﾄﾞｳ内表示項目行数(1,2,3,･･･)
		byte	np	 : ｳｲﾝﾄﾞｳ内反転ｶｰｿﾙﾃﾞﾌｫﾙﾄ位置(0,1,2,･･･)
							[ 0xff でﾃﾞﾌｫﾙﾄ反転無し ]

		SLW_TBL *ktb : 選択ｳｲﾝﾄﾞｳ用構造体先頭ｱﾄﾞﾚｽ

				{int msg, byte rtv},		1行目表示ｺﾒﾝﾄ番号, 1行目選択時戻り値
				{int msg, byte rtv},		2行目表示ｺﾒﾝﾄ番号, 2行目選択時戻り値
				{int msg, byte rtv},		3行目表示ｺﾒﾝﾄ番号, 3行目選択時戻り値
						・
						・
						・

	[戻り値]
		選択ｳｲﾝﾄﾞｳ用構造体で設定された戻り値
		 ( 0xff : ESCﾊｰﾄﾞｱｲｺﾝがﾀｯﾁされた時 )

	[処理内容]
		選択ｳｲﾝﾄﾞｳを開き,各行の選択時用に設定された戻り値を返す｡
******************************************************************************/
byte LibSelWindow(int x, int y, int xs, byte ln, byte np, SLW_TBL *ktb)
/*TAIL*/
{
	byte	sl;
	byte	t_buf[128];
	int		i,o,t_size;

	LibSelWinTchSet();				/* ﾀｯﾁｴﾘｱ設定 */

	/*----- ｳｨﾝﾄﾞｳｻｲｽﾞ算出   '98. 6.13 Y.Itoh -----*/
	for(xs=i=0;i<ln;i++){
	    LibReadMessage(ktb[i].msg,t_buf);	/* ﾒｯｾｰｼﾞ読み込み */
		t_size = LibGetProStrSize(IB_PFONT1,t_buf);
		xs = max(t_size,xs);
	}

	xs += 8;

	/*** ｲﾚｷﾞｭﾗｰ対策 ***/

/*	o = 127 - (x+xs-1);		/* 左端までの余裕 */
	o = 159 - (x+xs-1);		/* 左端までの余裕   '98.12.15 Y.Itoh 変更 */

	if(o < 0){				/* ﾊﾐ出ている     */
		x += o;
	/*	if(x<0)	x=0,xs=128;	*/
		if(x<0)	x=0,xs=160;		/* '98.12.15 Y.Itoh 変更 */
	}
	/*---------------------------------------------*/

	LibSelWinOpen(x,y,10,xs,ln,ktb);	/* 選択ｳｨﾝﾄﾞｰｵｰﾌﾟﾝ */
	sl = LibSelectWin(x,y,10,xs,ln,np);
									/* ｳｲﾝﾄﾞｳ内､項目選択処理 */
	LibCloseWindow();
	LibPutDisp();
	LibTchRelease();				/* ｢NULL｣まで POP */

	if(sl==0xff)					/* ESC ﾀｯﾁ時 */
		return(0xff);
	return(ktb[sl].rtv);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		選択ｳｲﾝﾄﾞｳ 処理 2 (ﾀｲﾄﾙ付き､中央表示ﾊﾞｰｼﾞｮﾝ)

	[引数]
		int		y	 : ｳｲﾝﾄﾞｳ表示開始座標(Y)
		byte	ln	 : no_mask時､ｳｲﾝﾄﾞｳ内表示項目行数(1,2,3,･･･) ［ﾀｲﾄﾙも含む］

		int		x_size:	ｳｨﾝﾄﾞｳ横ｻｲｽﾞ	'00. 2.25  Y.Itoh

		SLW_TBL *ktb : 選択ｳｲﾝﾄﾞｳ用構造体先頭ｱﾄﾞﾚｽ

				{int msg, byte rtv},		ﾀｲﾄﾙ表示ｺﾒﾝﾄ番号, 意味無し戻り値
				{int msg, byte rtv},		1行目表示ｺﾒﾝﾄ番号, 1行目選択時戻り値
				{int msg, byte rtv},		2行目表示ｺﾒﾝﾄ番号, 2行目選択時戻り値
						・
						・
						・				※15 項目まで対応

		word	msk	 : 表示項目ﾏｽｸ情報
							全項目表示の時		: 0x0000
							1行目を非表示の時	: 0x0001 の Bit を ON
							2行目を非表示の時	: 0x0002 の Bit を ON
							3行目を非表示の時	: 0x0004 の Bit を ON
										・
										・
										・
							15行目を非表示の時	: 0x8000 の Bit を ON

	[戻り値]
		選択ｳｲﾝﾄﾞｳ用構造体で設定された戻り値
		 ( 0xff : ESCﾊｰﾄﾞｱｲｺﾝがﾀｯﾁされた時 )

	[処理内容]
		選択ｳｲﾝﾄﾞｳを開き,各行の選択時用に設定された戻り値を返す｡
		但し､先頭行はﾀｲﾄﾙとして用いるので選択不可（従って､戻り値は意味無し）
******************************************************************************/
byte SpdSelWindow2(int y, byte ln, int x_size,SLW_TBL *ktb, word msk)
/*TAIL*/
{
	byte	sl,lc,fnt;
	byte	t_buf[128];
	int		i,t_size;
	int		x,xs;
	word	sft;

	LibSelWinTchSet();				/* ﾀｯﾁｴﾘｱ設定 */

	/*----- ｳｨﾝﾄﾞｳ横ｻｲｽﾞ算出   -----*/
	sft = msk;
	sft = sft << 1;
	sft &= 0xfffe;						/* ﾀｲﾄﾙは必ず表示 */
	fnt = IB_PFONT2;					/* ﾀｲﾄﾙは太文字 */
	for(xs=i=0,lc=0;i<=ln;i++){
		if(!(sft & 0x0001)){
			LibReadMessage(ktb[i].msg,t_buf);	/* ﾒｯｾｰｼﾞ読み込み */
			t_size = LibGetProStrSize(fnt,t_buf);
			xs = max(t_size,xs);
			lc++;
			fnt = IB_PFONT1;			/* ﾀｲﾄﾙ以外は細文字 */
		}
		sft = sft >> 1;
	}

	xs += 8;
/*	if(xs > 130){	/* ｲﾚｷﾞｭﾗｰ対策 */
	if(xs > 162){	/* ｲﾚｷﾞｭﾗｰ対策  '98.12.15 Y.Itoh 変更 */
	/*	xs	= 130;	*/
		xs	= 162;	/*	'98.12.15 Y.Itoh 変更 */
	}
	/*------------------------------*/

#if 1	/* '00. 2.25  Y.Itoh */
	xs = max(x_size,xs);
#endif

/*	x = (128-xs)/2;		/* ｳｲﾝﾄﾞｳ開始座標 */
	x = (160-xs)/2;		/* ｳｲﾝﾄﾞｳ開始座標 '98.12.15 Y.Itoh 変更 */

	LibSelWinOpen2(x,y,9,xs,lc-1,ktb,msk);	/* 選択ｳｨﾝﾄﾞｰｵｰﾌﾟﾝ */

#if 0	/* '00. 2.25  Y.Itoh */
	sl = LibSelectWin(x,y+12,9,xs,lc-1,0);	/* ｳｲﾝﾄﾞｳ内､項目選択処理 */
#else	/* '00. 2.25  Y.Itoh */
	sl = LibSelectWin(x,y+12,9,xs,lc-1,0xff);	/* ｳｲﾝﾄﾞｳ内､項目選択処理 */
#endif

	LibCloseWindow();
	LibPutDisp();
	LibTchRelease();				/* ｢NULL｣まで POP */

	if(sl==0xff)					/* ESC ﾀｯﾁ時 */
		return(0xff);

	lc = 0;							/* 選択された項目を算出 */
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
	[ﾀｲﾄﾙ]
		選択ｳｲﾝﾄﾞｳ ｵｰﾌﾟﾝ

	[引数]
		SLW2_ST	*slw 	: 選択ｳｲﾝﾄﾞｳ用構造体
		byte	ln		: 表示行数
		bool	opt		: ﾀｲﾄﾙ余白ｵﾌﾟｼｮﾝ  (TRUE:余白有り / FALSE:余白無し)

	[処理内容]
		選択ｳｲﾝﾄﾞｳを開き､ｳｲﾝﾄﾞｳ内にｺﾒﾝﾄ表示する
******************************************************************************/
static void LibSelWinOpenExt(SLW2_ST *slw, byte ln, bool opt)
/*TAIL*/
{
	word	i,yy;
	byte	*msg;
	byte	*mj;
	int		ys;

	ys = ln*slw->ity+6;			/* ｳｲﾝﾄﾞｳ縦幅決定 */
	if(opt==TRUE)
		ys += 11;

	ys++;	/* '99. 3.15  Y.Itoh */

	LibOpenWindow(slw->x,slw->y,slw->xs,ys);	/* 選択ｳｨﾝﾄﾞｰｵｰﾌﾟﾝ */
	LibSelWinFlm(slw->x,slw->y,slw->xs,ys);		/* 枠線描画 */

	yy = slw->y+4;				/* ﾒｯｾｰｼﾞ表示開始位置指定(縦) */
	if(opt==TRUE)
		yy += 11;

	msg = slw->cmnt;
	for(i=0;i<ln;i++,yy+=slw->ity){
		LibStringDsp(msg,slw->x+slw->t_xs,yy,slw->x+slw->xs-5,IB_PFONT1);
												/* 文字列表示 */
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
	[ﾀｲﾄﾙ]
		選択ｳｲﾝﾄﾞｳ 処理	拡張版（任意ﾒｯｾｰｼﾞ）

	[引数]
		SLW2_ST		*slw 		:in		選択ｳｲﾝﾄﾞｳ用構造体

	[戻り値]
		*rtv で設定された戻り値
		 ( 0xff : ｳｨﾝﾄﾞｳ外がﾀｯﾁされた時 )

	[処理内容]
		選択ｳｲﾝﾄﾞｳを開き,各行の選択時用に設定された戻り値を返す｡
		（表示ｺﾒﾝﾄは固定ﾒｯｾｰｼﾞではなく､任意の文字列）
******************************************************************************/
byte LibSelWindowExt(SLW2_ST *slw)
/*TAIL*/
{
	byte	sl;
	byte	ln,i;
	byte	*aa;

	LibSelWinTchSet();				/* ﾀｯﾁｴﾘｱ設定 */

	aa = slw->rtv;
	for(i=0,ln=0;;i++){				/* ｳｲﾝﾄﾞｳ内､行数取得 */
		if(aa[i]==0xff)
			break;
		ln++;
	}

	LibSelWinOpenExt(slw,ln,FALSE);	/* 選択ｳｨﾝﾄﾞｰｵｰﾌﾟﾝ */
	sl = LibSelectWin(slw->x,slw->y,slw->ity,slw->xs,ln,slw->np);
									/* ｳｲﾝﾄﾞｳ内､項目選択処理 */
	LibCloseWindow();
	LibPutDisp();

	LibTchRelease();				/* ｢NULL｣まで POP */

	if(sl==0xff)					/* ESC ﾀｯﾁ時 */
		return(0xff);
	return(slw->rtv[sl]);
}


/***********************************************************************************/
/*    ﾒｯｾｰｼﾞﾗｲﾌﾞﾗﾘ処理群 (SHIFT_NO番より前は共通処理,以降の時は専用処理へ分岐)     */
/***********************************************************************************/
/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		固定ﾒｯｾｰｼﾞ取得(表計算ﾓｰﾄﾞ用)

	[引数]
		no				:in     ﾒｯｾｰｼﾞNO
		buf				:out	読み出し用ﾊﾞｯﾌｧｱﾄﾞﾚｽ

	[戻り値]
		なし

	[処理内容]
		ﾒｯｾｰｼﾞNOに対応する固定ﾒｯｾｰｼﾞ文字列を取得する.
		本体に内蔵されていないﾒｯｾｰｼﾞ(SHIFT_NO番以降)の場合は,ﾓｰﾄﾞ内に定義されている
		farﾃﾞｰﾀを使用する.

******************************************************************************/
void LibReadMessage(word no,byte *buf)
/*TAIL*/
{
	byte	lang;

	if(no<SHIFT_NO){
		_LibReadMessage(no,buf);	/* 共通ﾗｲﾌﾞﾗﾘを実行 */
	}
	else{
		lang = LibGetLang();
		far_strcpy(buf,MessageTable[(no-SHIFT_NO)*5+lang]);
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		固定ﾒｯｾｰｼﾞ表示(表計算ﾓｰﾄﾞ用)

	[引数]
		no				:in     ﾒｯｾｰｼﾞNO
		p_x				:in     横座標
		p_y				:in     縦座標
		type			:in     ﾌｫﾝﾄ種別	IB_PFONT1	:ﾃﾞｰﾀﾀｲﾌﾟ
											IB_PFONT2	:背景ﾀｲﾌﾟ
                                            IB_PFONT3	:ﾀｲﾄﾙ用
                                            IB_CG57FONT	:5*7
	[戻り値]
		なし

	[処理内容]
		ﾒｯｾｰｼﾞNOに対応する固定ﾒｯｾｰｼﾞを表示する.
		本体に内蔵されていないﾒｯｾｰｼﾞ(SHIFT_NO番以降)の場合は,ﾓｰﾄﾞ内に定義されている
		farﾃﾞｰﾀを使用する.(LibReadMessage()の呼び出し)

******************************************************************************/
void LibPutMessage(word no,int p_x,int p_y,byte type)
/*TAIL*/
{
	byte	buf[256];

	if(no<SHIFT_NO){
		_LibPutMessage(no,p_x,p_y,type);	/* 共通ﾗｲﾌﾞﾗﾘを実行 */
	}
	else{
		LibReadMessage(no,buf);		/* SHIFT_NO番以降に対応したﾒｯｾｰｼﾞ文字列を取得 */
		LibPutProStr(type,p_x,p_y,buf,160);
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		固定ﾒｯｾｰｼﾞ表示	(ｾﾝﾀﾘﾝｸﾞ指定)(表計算ﾓｰﾄﾞ用)

	[引数]
		no				:in     ﾒｯｾｰｼﾞNO
		p_x1			:in     左端座標(開始)
		p_x2			:in     右端座標(終了)
		p_y				:in     縦座標
		type			:in     ﾌｫﾝﾄ種別	IB_PFONT1	:ﾃﾞｰﾀﾀｲﾌﾟ
											IB_PFONT2	:背景ﾀｲﾌﾟ
                                            IB_PFONT3	:ﾀｲﾄﾙ用
                                            IB_CG57FONT	:5*7
	[戻り値]
		なし

	[処理内容]
		ﾒｯｾｰｼﾞNOに対応する固定ﾒｯｾｰｼﾞを,指定された開始～終了の領域内にｾﾝﾀﾘﾝｸﾞ表示する.
		本体に内蔵されていないﾒｯｾｰｼﾞ(SHIFT_NO番以降)の場合は,ﾓｰﾄﾞ内に定義されている
		farﾃﾞｰﾀを使用する.(LibReadMessage()の呼び出し)

******************************************************************************/
void LibPutMessageCenter(word no,int p_x1,int p_x2,int p_y,byte type)
/*TAIL*/
{
	byte	buf[256];
	int		len,x;

	if(no<SHIFT_NO){
		_LibPutMessageCenter(no,p_x1,p_x2,p_y,type);	/* 共通ﾗｲﾌﾞﾗﾘを実行 */
	}
	else{
		LibReadMessage(no,buf);		/* SHIFT_NO番以降に対応したﾒｯｾｰｼﾞ文字列を取得 */
		len	= LibGetProStrSize(type,buf);
		x	= p_x1 + CENTER((p_x2-p_x1+1),len);
		LibPutProStr(type,x,p_y,buf,160);
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		固定ﾒｯｾｰｼﾞ表示	(右寄せ指定)

	[引数]
		no				:in     ﾒｯｾｰｼﾞNO
		p_x				:in     右端座標
		p_y				:in     縦座標
		type			:in     ﾌｫﾝﾄ種別	IB_PFONT1	:ﾃﾞｰﾀﾀｲﾌﾟ
											IB_PFONT2	:背景ﾀｲﾌﾟ
                                            IB_PFONT3	:ﾀｲﾄﾙ用
                                            IB_CG57FONT	:5*7
	[戻り値]
		なし

	[処理内容]
		本体に内蔵されていないﾒｯｾｰｼﾞ(SHIFT_NO番以降)の場合は,ﾓｰﾄﾞ内に定義されている
		farﾃﾞｰﾀを使用する.(LibReadMessage()の呼び出し)

******************************************************************************/
void LibPutMessageRight(word no,int p_x,int p_y,byte type)
/*TAIL*/
{
	byte	buf[256];

	if(no<SHIFT_NO){
		_LibPutMessageRight(no,p_x,p_y,type);	/* 共通ﾗｲﾌﾞﾗﾘを実行 */
	}
	else{
		LibReadMessage(no,buf);		/* SHIFT_NO番以降に対応したﾒｯｾｰｼﾞ文字列を取得 */
		LibPutProStr(type,p_x-LibGetProStrSize(type,buf),p_y,buf,160);
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾀﾞｲｱﾛｸﾞﾒｯｾｰｼﾞ行数取得(表計算ﾓｰﾄﾞ用)

	[引数]
		int		mes_no			:in		ﾒｯｾｰｼﾞ番号
		byte	w_pos			:in		ｳｨﾝﾄﾞｳ表示位置
											0x00:			画面下
											IX_MWIN_CENTER:	画面中央
		byte	b_cnt			:in		ﾎﾞﾀﾝ数(0～2)
		int		*y				:out	ｳｨﾝﾄﾞｳ縦座標
		int		*y_size			:out	ｳｨﾝﾄﾞｳ縦ｻｲｽﾞ

	[戻り値]
		行数-1 (0～4)

	[処理内容]
		ﾀﾞｲｱﾛｸﾞﾒｯｾｰｼﾞの行数(文字列中の"@"個数)を取得する
		本体に内蔵されていないﾒｯｾｰｼﾞ(SHIFT_NO番以降)の為,ﾓｰﾄﾞ内に定義されている
		farﾃﾞｰﾀを使用する.

******************************************************************************/
static int SpdGetWinMessSize(int mes_no,byte w_pos,byte b_cnt,int *y,int *y_size)
/*TAIL*/
{
	int		i, lcnt;
	byte	buf[256];

	LibReadMessage(mes_no,buf);			/* SHIFT_NO番以降に対応したﾒｯｾｰｼﾞ文字列を取得 */

	for(lcnt=0,i=0; i<256; i++){
		if(buf[i]==NULL){				/* 終端発見 */
			break;
		}else if(buf[i]=='@'){
			lcnt ++;					/* 行数 inc. */
		}
	}
	if(lcnt>4)
		lcnt = 4;						/* Max 5行 */

	*y = wim_yp[(b_cnt & 0x03)][lcnt];	/* 表示Y座標取得 */
	*y_size = 161 - *y;					/* ｳｨﾝﾄﾞｳ縦幅取得 */

	if(w_pos==IX_MWIN_CENTER){			/* 画面中央指定の時 */
		*y = (*y)/2;
	}
	return(lcnt);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾀﾞｲｱﾛｸﾞﾒｯｾｰｼﾞ用ｳｨﾝﾄﾞｳｻｲｽﾞ取得(表計算ﾓｰﾄﾞ用)

	[引数]
		int		mes_no			:in		ﾒｯｾｰｼﾞ番号
		byte	w_pos			:in		ｳｨﾝﾄﾞｳ表示位置
											0x00:			画面下
											IX_MWIN_CENTER:	画面中央
		byte	b_cnt			:in		ﾎﾞﾀﾝ数(0～2)
		int		*y				:out	ｳｨﾝﾄﾞｳ縦座標
		int		*y_size			:out	ｳｨﾝﾄﾞｳ縦ｻｲｽﾞ

	[戻り値]
		なし

	[処理内容]
		ﾀﾞｲｱﾛｸﾞﾒｯｾｰｼﾞ用のｳｨﾝﾄﾞｳ位置,ｻｲｽﾞを取得する.
		本体に内蔵されていないﾒｯｾｰｼﾞ(SHIFT_NO番以降)の場合は,ﾓｰﾄﾞ内に定義されている
		farﾃﾞｰﾀを使用する.

******************************************************************************/
void LibGetWinMessSize(int mes_no,byte w_pos,byte b_cnt,int *y,int *y_size)
/*TAIL*/
{
	if(mes_no<SHIFT_NO){
		_LibGetWinMessSize(mes_no,w_pos,b_cnt,y,y_size);	/* 共通ﾗｲﾌﾞﾗﾘを実行 */

	}else{
		SpdGetWinMessSize(mes_no,w_pos,b_cnt,y,y_size);		/* 表計算用 */
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾀﾞｲｱﾛｸﾞﾒｯｾｰｼﾞ用表示(表計算ﾓｰﾄﾞ用)

	[引数]
		byte	g_no			:in		ｱｲｺﾝ(ｸﾞﾗﾌｨｯｸ)番号
											IB_MWIN_NO_ICON の時,なし
		int		mes_no			:in		ﾒｯｾｰｼﾞ番号
		byte	b_cnt			:in		ﾎﾞﾀﾝ数(0～2)
		byte	b_type			:in		ﾎﾞﾀﾝ種別
											IB_MWIN_NONE:		なし
											IB_MWIN_YES_NO:		YES/NO(ボタン２つ)
											IB_MWIN_SET_ESC:	SET/ESC(ボタン２つ)
											IB_MWIN_OK:			OK(ボタン１つ)
											IB_MWIN_SET:		SET(ボタン１つ)
											IB_MWIN_ESC:		ESC(ボタン１つ)

											IX_MWIN_CENTER:		ｳｨﾝﾄﾞｳ位置中央指定
	[戻り値]
		なし

	[処理内容]
		ﾀﾞｲｱﾛｸﾞﾒｯｾｰｼﾞ用の表示を行う.
		本体に内蔵されていないﾒｯｾｰｼﾞ(SHIFT_NO番以降)の場合は,ﾓｰﾄﾞ内に定義されている
		farﾃﾞｰﾀを使用する.

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
											/* 共通ﾗｲﾌﾞﾗﾘを実行 */
	}else{
		i = 0;
		if(b_type==IX_MWIN_CENTER)
			i = IX_MWIN_CENTER;
		lcnt = SpdGetWinMessSize(mes_no,i,b_cnt,&w_yp,&w_ys);
											/* ｳｨﾝﾄﾞｳｻｲｽﾞ､表示開始座標取得 */
	  /*** ｳｨﾝﾄﾞｳｸﾞﾗﾌｨｯｸ表示 ***/
		if(w_yp==109 || w_yp==109/2){
			gdn = 107;
		}else if(w_yp==97 || w_yp==97/2){
			gdn = 108;
		}else{
			gdn = 109;
		}
		LibPutFarData(16, w_yp+1, gdn);

	  /*** ｱｲｺﾝ表示 ***/
		if(g_no!=IB_MWIN_NO_ICON)
			LibPutFarData(24,w_yp+1+11,g_no);

	  /*** ﾎﾞﾀﾝ表示 ***/
		if((b_cnt & 0x03)>=1){				/* ﾎﾞﾀﾝが１つ以上の時 */

			if(b_type<IB_MWIN_YES_NO || IB_MWIN_ESC<b_type)
				return;						/* 入力条件ｴﾗｰ */

			yp = w_yp+w_ys-24;
			gdn = 113;
			if((b_cnt & 0x40)!=0)			/* 点線付き? */
				gdn = 114;
			LibPutFarData(106,yp,gdn);		/* 右ﾎﾞﾀﾝ表示 */
			LibPutMessageCenter(bmsg[(b_type-IB_MWIN_YES_NO)][1],108,132,yp+4,IB_PFONT1);
											/* 右ﾎﾞﾀﾝﾒｯｾｰｼﾞ表示 */

			if((b_cnt & 0x03)>=2){			/* ﾎﾞﾀﾝが２つ以上の時 */
				gdn = 113;
				if((b_cnt & 0x80)!=0)		/* 点線付き? */
					gdn = 114;
				LibPutFarData(72,yp,gdn);	/* 左ﾎﾞﾀﾝ表示 */
				LibPutMessageCenter(bmsg[(b_type-IB_MWIN_YES_NO)][0],74,98,yp+4,IB_PFONT1);
											/* 左ﾎﾞﾀﾝﾒｯｾｰｼﾞ表示 */
			}
		}

	  /*** ﾒｯｾｰｼﾞ表示 ***/
		LibReadMessage(mes_no,buf);			/* ﾒｯｾｰｼﾞ文字列を取得 */
		gtp[0] = 0;
		for(j=1,i=0;i<256;i++){
			if(buf[i]==NULL){
				break;
			}else if(buf[i]=='@'){
				buf[i] = NULL;				/* 改行ｺｰﾄﾞをNULLに置換 */
				gtp[j] = i+1;				/* 各行先頭位置取得 */
				j ++;
			}
		}
		for(hb=0,i=0; i<=lcnt; i++){
			j = LibGetProStrSize(IB_PFONT1,&buf[gtp[i]]);	/* 各行幅取得 */
			if(hb < j)
				hb = j;						/* 最大行幅更新 */
		}

		i = 83;								/* ﾒｯｾｰｼﾞ最大表示幅(ｱｲｺﾝ有りの時) */
		j = 50;								/* ﾒｯｾｰｼﾞ表示ｴﾘｱ左端(ｱｲｺﾝ有りの時) */
		if(g_no==IB_MWIN_NO_ICON){
			i = 107;						/* ﾒｯｾｰｼﾞ最大表示幅(ｱｲｺﾝ無しの時) */
			j = 26;							/* ﾒｯｾｰｼﾞ表示ｴﾘｱ左端(ｱｲｺﾝ無しの時) */
		}
		if(hb>i)							/* ﾒｯｾｰｼﾞ幅ｵｰﾊﾞｰ */
			xp = j;	
		else
			xp = j+(i-hb)/2;				/* ﾒｯｾｰｼﾞ表示開始X座標 */

		yof = wim_myof[(b_cnt&0x03)][lcnt];	/* ﾒｯｾｰｼﾞ表示開始Yｵﾌｾｯﾄ取得 */
		yp = w_yp + 1 + yof;				/* ﾒｯｾｰｼﾞ表示開始Y座標 */

		for(i=0;i<=lcnt;i++){
			LibPutProStr(IB_PFONT1, xp, yp, &buf[gtp[i]],159);
			yp += 9;						/* 次行縦座標 */
		}
	}
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		各種ﾒｯｾｰｼﾞｳｲﾝﾄﾞｩ表示処理(表計算ﾓｰﾄﾞ用)

	[引数]
		byte icn ... 表示ｱｲｺﾝｸﾞﾗﾌｨｯｸﾀｲﾌﾟ
				ICON_NONE		: なし
				ICON_OK			: OK
				ICON_BADTZ		: ×
				ICON_BIKKURI	: ！
				ICON_COFFEE		: ｺｰﾋｰｶｯﾌﾟ
				ICON_TRASH		: ごみ箱
				ICON_SIGN		: 手
				ICON_SYNC		: 通信中

		word msg	: 表示ｺﾒﾝﾄ番号
			(たとえば....)	323 : DATA_ITEM_NOT_FOUND!
							331 : OK_TO_DELETE@THE_DATA_ITEM?
							341 : DATA_STORED!

		byte wtyp	: ﾒｯｾｰｼﾞﾀｲﾌﾟ
						0x00:開きっぱなし...｡(ﾎﾞﾀﾝ無し)	... 画面中央
						0x10:開きっぱなし...｡(ﾎﾞﾀﾝ無し)	... 画面下部
						0x01:1Sec表示(ﾎﾞﾀﾝ無し)			... 画面中央
						0x11:1Sec表示(ﾎﾞﾀﾝ無し)			... 画面下部
						0x02:確認(OK)ﾎﾞﾀﾝ付き			... 画面下部
						0x03:確認(ESC)ﾎﾞﾀﾝ付き			... 画面下部
						0x04:確認(SET)ﾎﾞﾀﾝ付き			... 画面下部
						0x05:選択(Yes/No)ﾎﾞﾀﾝ付き		... 画面下部
						0x06:選択(OK/ESC)ﾎﾞﾀﾝ付き		... 画面下部

	[戻り値]
		bool jdg	: --- wtypが "5","6"の時 ---
							TRUE	: Yes(OK)選択時
							FALSE	: No(ESC)選択時

					  --- wtypが "5","6"以外の時 ---
							TRUE

	[処理内容]
		ｳｨﾝﾄﾞｳﾒｯｾｰｼﾞを表示する｡
		本体に内蔵されていないﾒｯｾｰｼﾞ(SHIFT_NO番以降)の場合は,ﾓｰﾄﾞ内に定義されている
		farﾃﾞｰﾀを使用する.

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
	byte	w_pos = 0x00;	/* 画面下指定 */
	byte	up_dwn = (wtyp & 0x10) >> 4;
	T_ICON far	*icon;

	wtyp &= 0x0f;

	if(icn>7)
		icn = 0;

	if(wtyp<2){					/* ﾎﾞﾀﾝ数決定 */
		btn = 0;
		w_pos = IX_MWIN_CENTER;			/* とりあえず画面中央指定 ※ */
		if(up_dwn == 1){
			w_pos = 0x00;				/* 画面下指定 */
		}

	}else{
		LibTchStackPush( NULL );
		LibTchStackPush(TchHardIcon);	/* '98. 7.14 Y.Itoh */
		LibTchStackPush(TchBtnR);		/* 右ﾎﾞﾀﾝ ﾀｯﾁﾃｰﾌﾞﾙ */
		LibTchStackPush(TchActionKey);	/* ｱｸｼｮﾝｷｰ  ﾀｯﾁﾃｰﾌﾞﾙ */
		btn = 1;
	}
	if(wtyp>=5){
		btn = 2;
		LibTchStackPush(TchBtnL);		/* 左ﾎﾞﾀﾝ ﾀｯﾁﾃｰﾌﾞﾙ */
	}

	LibGetWinMessSize(msg,w_pos,btn,&ysp,&win_ysz);	/* ｳｲﾝﾄﾞｳｻｲｽﾞ取得 */
/*	LibOpenWindow(0+16,ysp,128,win_ysz);		/* ｳｲﾝﾄﾞｳｵｰﾌﾟﾝ 	ZX485*/
	LibOpenWindow(0+16-1,ysp,128+2,win_ysz);	/* ｳｲﾝﾄﾞｳｵｰﾌﾟﾝ 	ZX485 '99. 1.22 Y.Itoh */

	btyp = wim_bt[wtyp];
	if(up_dwn == 1)
		btyp &= 0x0f;
	if(wtyp>=0x05)
		btn |= 0x80;
	else if(wtyp==0x02 || wtyp==0x04)
		btn |= 0x40;

	LibDspWinMessage(wim_ic[icn],msg,btn,btyp);	/* ｳｲﾝﾄﾞｳﾒｯｾｰｼﾞ表示 */


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
			case	0:				/** 開きっぱなし **/
				return(TRUE);

			case	1:				/** 1秒ﾒｯｾｰｼﾞ **/
				LibWait(IB_1SWAIT);
				loop = FALSE;
				break;

			default:				/** 確認ﾎﾞﾀﾝ付き **/
			case	5:				/** 二者択一 **/
			case	6:
				LibTchWait( &tsts );				/* ﾀｯﾁ待ち */
				if(tsts.obj==OBJ_BT_LFT){			/* 左ﾎﾞﾀﾝ ﾀｯﾁ時 */
					if(wtyp>=5){
						if(LibIconClick(&TicnBtnL,&tsts)==TRUE){
							jdg = TRUE;
							loop = FALSE;
						}
					}

				}else if(tsts.obj==OBJ_BT_RGT){		/* 右ﾎﾞﾀﾝ ﾀｯﾁ時 */
					if(LibIconClick(&TicnBtnR,&tsts)==TRUE){
						if(wtyp>=5){
							jdg = FALSE;
						}else{
							jdg = TRUE;
						}
						loop = FALSE;
					}
				}else if(tsts.obj==OBJ_HIC_ESC){	/* ｢ESC｣ﾊｰﾄﾞｱｲｺﾝﾀｯﾁの時 */
					if(wtyp>=5 || wtyp==3){
						jdg = FALSE;
						loop = FALSE;	/* '98. 7.16 Y.Itoh */
					}

				}else if(tsts.obj==OBJ_LPSW_PUSH){	/* ｱｸｼｮﾝｷｰ PUSH時 */
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

	LibCloseWindow();			/* ｳｲﾝﾄﾞｳｸﾛｰｽﾞ */
	LibPutDisp();
	if(btn!=0){
		LibTchRelease();
	}
	return(jdg);
}
