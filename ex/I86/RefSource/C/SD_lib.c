/******************************************************************************
	[ﾀｲﾄﾙ]
		Referencer

	[機種]
		通信電子手帳(海外)

	[概要]
		Referencer ﾃｷｽﾄ表示ﾗｲﾌﾞﾗﾘｰ

	[作成者]
		鈴木茂人

	Copyright (C) 2000 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#include	<stdrom.h>

#include	"define.h"
#include	"libc.h"
#include	"L_define.h"
#include	"L_libc.h"

#include	"SD_main.h"

/*	byte far	*wdtpp;			/* 単語先頭ﾎﾟｲﾝﾀｰ */
/*	int			wdtpx;			/* 単語先頭X座標 */
/*	byte		wdtpf;			/* 単語先頭文字ﾌｫﾝﾄ */
DSPCT	wtct;				/* 単語先頭情報 */

SHWIDX	dltp[D_LNC+2];
byte	graphtmp[3200+4];

/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		１行表示処理

	[引数]
		bool	den		: in 表示許可

	[戻り値]
		TRUE	: 一行正常終了(改行処理発生時)
		FALSE	: 行途中で終了ｺｰﾄﾞ発見時、またはｴﾗｰによる強制終了時
	[処理内容]
******************************************************************************/
bool DicDsp1L(DSPCT *dct, bool den)
/*TAIL*/
{
	bool	ret = TRUE;
	byte	ccd;

	/* 行先頭設定 */
	wtct = *dct;			/* 単語先頭情報として退避 */

	while(ret==TRUE){
		ret = DicDsp1C(dct,den,&ccd);	/* 一文字表示処理 */
	}
	if(ret==HALF)
		return(TRUE);
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		１文字表示処理

	[引数]
		bool	den		: in	表示許可 ･･	TRUE  :表示許可
											FALSE :非表示
											HALF  :文字反転のみ
		byte	ccd		: out	ｺｰﾄﾞ種別

	[戻り値]
		TRUE	: 通常処理終了時
		HALF	: 改行処理発生時
		FALSE	: 終了ｺｰﾄﾞ発見時、またはｴﾗｰ発生時
	[処理内容]
******************************************************************************/
bool DicDsp1C(DSPCT *dct, bool den, byte *ccd)
/*TAIL*/
{
	bool	ret = TRUE;

	dct->code = *(dct->pot);		/* 1ｺｰﾄﾞ読み込み */
	*ccd = JdgContCode(&dct->pot);	/* 制御ｺｰﾄﾞ判断 */

	switch(*ccd){

		case CD_CHA:			/* 文字ｺｰﾄﾞ「00h～7Fh」 */
		case CD_OVCHA:			/* 1ﾊﾞｲﾄｺｰﾄﾞ指定(0x80以上)「80h～FFh」 */
			if(Dsp1Cha(dct,den)==FALSE)
				ret = HALF;		/* 自然改行 */
			break;

		case CD_RTN:			/* 改行ｺｰﾄﾞ「0Dh」 */
	/*		dct->pot ++;	*/
			if(dct->st!=0){		/* 見出し､小見出し､ﾘﾝｸ見出しの時 */
				dct->fnt = FNT_BASE;
				dct->st = 0;
			}
			NextLine(dct);
			ret = HALF;
			break;

		case CD_TITLE:			/* 見出し「@\T」 */
			dct->fnt = FNT_TITLE;
			dct->x = dct->sx - D_SFTX*2;
			dct->st = 2;
			break;

		case CD_LINK:			/* ﾘﾝｸ見出し「@\L+文字列長(1byte)」 */
			dct->fnt = FNT_LINKT;
			dct->x = dct->sx - D_SFTX*2;
			dct->st = 2;
			break;

		case CD_SUBT:			/* 小見出し「@\C」 */
			dct->fnt = FNT_SUBT;
			dct->x = dct->sx - D_SFTX;
			dct->st = 1;
			break;

		case CD_GPDEF:			/* 画像指定「@\g????」 */
			DspGraph(dct,den);
			break;

		case CD_END:			/* 終了ｺｰﾄﾞ(次見出し)「@\T」「@\L」 */
			ret = FALSE;
			break;

		case CD_FNT57:			/* 5x7ﾌｫﾝﾄ指定        「@\fNM」 */
			dct->fnt = IB_CG57FONT;
			break;

		case CD_FNTPN:			/* ﾌﾟﾛﾎﾟｰｼｮﾅﾙﾌｫﾝﾄ指定 「@\fPN」 */
			dct->fnt = IB_PFONT1;
			break;

		case CD_FNTPB:			/* 太文字ﾌｫﾝﾄ指定     「@\fPB」 */
			dct->fnt = IB_PFONT2;
			break;

		case CD_LKDEF:			/* ﾘﾝｸ指定「@\l+文字列長(1byte)」 */
			if(LinkSet(dct,den,FALSE)==FALSE){
				ret = FALSE;
			}
			break;

		case CD_JPDEF:			/* ｼﾞｬﾝﾌﾟ指定「@\j+文字列長(1byte)」 */
			if(LinkSet(dct,den,TRUE)==FALSE){
				ret = FALSE;
			}
			break;
	}
	return(ret);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		制御ｺｰﾄﾞ判断

	[引数]
		byte	far **tgt	: in/out	ﾀｰｹﾞｯﾄｺｰﾄﾞｱﾄﾞﾚｽ
										(制御ｺｰﾄﾞ時はｽｷｯﾌﾟ後のｱﾄﾞﾚｽを返す)


	[戻り値]
		CD_CHA		文字ｺｰﾄﾞ「00h～7Fh(09h,0Dh以外)」
		CD_RTN		改行ｺｰﾄﾞ「0Dh」
		CD_OVCHA	1ﾊﾞｲﾄｺｰﾄﾞ指定(0x80以上)「@\x??」
		CD_TITLE	見出し「@\T」
		CD_SUBT		小見出し「@\C」
		CD_GPDEF	画像指定「@\g????」
		CD_END		終了ｺｰﾄﾞ(次見出し)「@\T」,「@\L」
		CD_FNT57	5x7ﾌｫﾝﾄ指定「@\fNM」
		CD_FNTPN	ﾌﾟﾛﾎﾟｰｼｮﾅﾙﾌｫﾝﾄ指定「@\fPN」
		CD_FNTPB	太文字ﾌｫﾝﾄ指定「@\fPB」
		CD_JPDEF	ｼﾞｬﾝﾌﾟ指定「@\j文字列長」
		CD_LKDEF	ﾘﾝｸ指定「@\l文字列長」
		CD_LINK		ﾘﾝｸ見出し「@\L文字列長」

	[処理内容]
******************************************************************************/
byte JdgContCode(byte far **tgt)
/*TAIL*/
{
	byte	ccd;
	byte	skip = 3;

	ccd = CD_CHA;					/* とりあえず */

	if(**tgt==0x0d){
		ccd = CD_RTN;				/* 改行ｺｰﾄﾞ */
		skip = 1;

	}else if(**tgt==0x40){			/* 「@」の時 */

		if(*(*tgt+1)==0x5c){		/* 2文字目が「\」の時 */

			if(*(*tgt+2)=='T'){		/* 3文字目が「T」の時 */
				if(*tgt==dttop){
					ccd = CD_TITLE;			/* 見出しｺｰﾄﾞ */
				}else{
					ccd = CD_END;			/* 終了ｺｰﾄﾞ */
				}

			}else if(*(*tgt+2)=='L'){	/* 3文字目が「L」の時 */
				if(*tgt==dttop){
					ccd = CD_LINK;			/* ﾘﾝｸ見出しｺｰﾄﾞ */
					skip = 4;
				}else{
					ccd = CD_END;			/* 終了ｺｰﾄﾞ */
				}

			}else if(*(*tgt+2)=='C'){	/* 3文字目が「C」の時 */
				if(*(*tgt-1)==0x0d){		/* 0文字目が改行ｺｰﾄﾞの時 */
					ccd = CD_SUBT;			/* 小見出し */
				}

			}else if(*(*tgt+2)=='g'){	/* 3文字目が「g」の時 */
				ccd = CD_GPDEF;				/* 画像指定 */

			}else if(*(*tgt+2)=='j'){	/* 3文字目が「j」の時 */
				ccd = CD_JPDEF;				/* ｼﾞｬﾝﾌﾟ指定 */

			}else if(*(*tgt+2)=='l'){	/* 3文字目が「l」の時 */
				ccd = CD_LKDEF;				/* ﾘﾝｸ指定 */

			}else if(CmpStr(*tgt+2,"fNM",3)==TRUE){
				ccd = CD_FNT57;				/* 5x7ﾌｫﾝﾄ指定 */
				skip = 5;
			}else if(CmpStr(*tgt+2,"fPN",3)==TRUE){
				ccd = CD_FNTPN;				/* ﾌﾟﾛﾎﾟｰｼｮﾅﾙﾌｫﾝﾄ指定 */
				skip = 5;
			}else if(CmpStr(*tgt+2,"fPB",3)==TRUE){
				ccd = CD_FNTPB;				/* 太文字ﾌｫﾝﾄ指定 */
				skip = 5;
			}
		}

	}else if(**tgt >= 0x80){
		ccd = CD_OVCHA;				/* 1ﾊﾞｲﾄｺｰﾄﾞ指定(0x80以上) */
		skip = 0;
	}

	if(ccd==CD_CHA || ccd==CD_END)
		skip = 0;

	(*tgt) += skip;
	return(ccd);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		1文字表示

	[引数]
		bool	den		: in 表示許可	TRUE  : 表示
										FALSE : 非表示
										HALF  : 文字反転のみ
	[戻り値]
		TRUE	: 正常終了
		FALSE	: 改行処理の為、表示せず。

	[処理内容]
******************************************************************************/
bool Dsp1Cha(DSPCT *dct, bool den)
/*TAIL*/
{
	int		xp;
	word	pt;

	if(dct->y < dct->sy)			/* 表示許可でも範囲外には表示しない */
		den = FALSE;

	xp = LibGetProFontSize(dct->fnt,dct->code);	/* 文字横幅取得 */

	if(dct->x + xp >= dct->ex){			/* 行あふれ時 */
		/*** ﾜｰﾄﾞﾗｯﾌﾟ処理 ***/
		if(wtct.x > wtct.sx){		/* 行先頭からの単語でなければ... */
			if((den==TRUE)||(den==HALF)){		/* 行末まで画面消去 */
				if((wtct.x<wtct.ex)&&(wtct.y<wtct.ey))
					LibClrBox(wtct.x, wtct.y, wtct.ex-wtct.x, D_ITY);
			}
			*dct = wtct;
			wtct.x = wtct.sx;
		}
		NextLine(dct);							/* 改行処理 */
		return(FALSE);
	}

	if(den==TRUE){
		LibPutProFont(dct->fnt,dct->code,dct->x,dct->y);
												/* 一文字表示 */
		if(dct->pot < dct->lkpt){				/* ﾘﾝｸ有効時 */
			if(dct->jpf==TRUE)					/* ｼﾞｬﾝﾌﾟの時 */
				LibLine(dct->x,(dct->y)+D_ITY-1,xp,1,1);	/* 下線 */
			else								/* ﾘﾝｸの時 */
				LibMeshLine(dct->x,(dct->y)+D_ITY-1,xp,1);	/* 下点線 */
		}

	}else if(den==HALF){				/* 文字反転時 */
		if((rsp!=0xffff)&&(rep!=0xffff)){
			pt = (word)(dct->pot-dttop);
			if((rsp<=pt)&&(pt<rep)){
				LibGdsReverse(dct->x,dct->y,dct->x+xp-1,dct->y+D_ITY-1);
			}
		}
	}

	dct->x += xp;
	dct->pot ++;

	/******* ﾜｰﾄﾞﾗｯﾌﾟ処理対応 ********/
	/*  ｽﾍﾟｰｽ表示後の表示情報を退避  */
	/*********************************/
	if(dct->code==0x20 && (*(dct->pot)!=0x20) && (*(dct->pot)!=0x0d)){
								/* ｽﾍﾟｰｽで、次がｽﾍﾟｰｽでも改行でもない時 */
		wtct = *dct;			/* 単語先頭情報退避 */
	}

	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｸﾞﾗﾌｨｯｸ表示

	[引数]
	[戻り値]
		TRUE	: 正常終了
		FALSE	: 改行処理の為、表示せず。

	[処理内容]
******************************************************************************/
bool DspGraph(DSPCT *dct, bool den)
/*TAIL*/
{
	byte far	*gdt;
	int			xs, ys;
	LSTIDX		lwk; 

	if(dct->x>=dct->ex){			/* 表示開始が右にあふれたら... */
		NextLine(dct);				/* 画像表示後に改行 */
		return(FALSE);
	}

/*	dct->pot += 3;	*/

	lwk.num = GetGraphNum(dct->pot);	/* 画像番号取得 */
	DicGraphRead(&lwk);					/* 画像ｲﾝﾃﾞｯｸｽから画像ｱﾄﾞﾚｽ取得 */
	gdt = &Gbuf.bin_buf[0]+lwk.ofs;

	if(den==TRUE){
		PutGraphE(dct, gdt);	/* ｸﾞﾗﾌｨｯｸ表示 */
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
	wtct = *dct;			/* 単語先頭情報として退避 */

	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｸﾞﾗﾌｨｯｸﾃﾞｰﾀｻｲｽﾞ取得

	[引数]
	[戻り値]
	[処理内容]
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
	[ﾀｲﾄﾙ]
		ｽｸﾛｰﾙ用ｸﾞﾗﾌｨｯｸ表示

	[引数]
		int		x				: in ｸﾞﾗﾌｨｯｸ表示開始座標（X）
		int		y				: in ｸﾞﾗﾌｨｯｸ表示開始座標（Y）
		const byte far *graph	: in ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ

	[戻り値]
		FALSE	: 表示は全て画面外、又はｸﾞﾗﾌｨｯｸｻｲｽﾞｴﾗｰ
		TRUE	: ｸﾞﾗﾌｨｯｸを画面内に全て表示
		HALF	: ｸﾞﾗﾌｨｯｸを一部表示

	[処理内容]
******************************************************************************/
bool PutGraphE(DSPCT *dct, const byte far *graph)
/*TAIL*/
{
	int		xs, ys;					/* 画像ｻｲｽﾞ */
	int		gx, gy;					/* 切り出し開始座標 */
	int		gxs, gys;				/* 切り出しｻｲｽﾞ(貼り付けｻｲｽﾞ) */
	int		xx, yy;					/* 貼り付け座標 */

	if(GetGraphSize(graph, &xs, &ys)!=TRUE)
		return(FALSE);					/* 画像ｻｲｽﾞｴﾗｰ */


	/* 画面内に収まる場合 */
	if((dct->sx<=dct->x && dct->x+xs<dct->ex)
			 && (dct->sy<=dct->y && dct->y+ys<dct->ey)){
		LibPutGraph(dct->x,dct->y, graph );			/* そのままｸﾞﾗﾌｨｯｸ表示 */
		return(TRUE);
	}
	/* 全て画面外の場合 */
	else if((dct->x+xs<=dct->sx || dct->ex<=dct->x)
				 || (dct->y+ys<=dct->sy || dct->ey<=dct->y)){
		return(FALSE);
	}

	/*** とりあえず ***/
	gx = gy = 0;
	gxs = xs;
	gys = ys;
	xx = dct->x;
	yy = dct->y;

	/*** 左右へのはみだし ***/
	if(dct->x<dct->sx && dct->sx < dct->x+xs){				/* 画面左部にはみ出る場合 */
		gx = dct->sx-dct->x;
		gxs = xs-gx;
		xx = dct->sx;
	}
	else if((dct->sx<=dct->x && dct->x<dct->ex)
				&&(dct->ex <= dct->x+xs)){	/* 画面右部にはみ出る場合 */
		gx = 0;
		gxs = dct->ex-dct->x;
	}

	/*** 上下へのはみだし ***/
	if(dct->y < dct->sy){				/* 上部にはみ出る場合 */
		gy = dct->sy-dct->y;
		yy = dct->sy;
		gys = ys-gy;
		if(gys>dct->ey-dct->sy)		/* 上下部共にはみ出る場合 */
			gys = dct->ey-dct->sy;
	}
	else if(dct->ey < dct->y+ys){		/* 下部にのみはみ出る場合 */
		gy = 0;
		gys = dct->ey-dct->y;
	}

	/** BIOSﾊﾞｸﾞ対策 **/
	if(xs < 9)
		xs = 9;
	if(gxs < 9)
		gxs = 9;

	LibOpenWindow(0,0,xs,ys);					/* ｸﾞﾗﾌｨｯｸ切り出し用Window */
	LibPutGraph(0, 0, graph );					/* ｸﾞﾗﾌｨｯｸ表示 */
	LibGetGraph(gx,gy,gxs,gys,&graphtmp[4]);	/* 画像切り出し */
	LibCloseWindow();

	graphtmp[0] = gxs & 0xff;				/* 貼り付けｻｲｽﾞ付加 */
	graphtmp[1] = gxs >> 8;
	graphtmp[2] = gys & 0xff;
	graphtmp[3] = gys >> 8;
	LibPutGraph(xx, yy, graphtmp );			/* ｸﾞﾗﾌｨｯｸ表示 */
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		画像ｻｲｽﾞ取得

	[引数]
		const byte far *graph	: in	ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ
		int		*xs				: out	ｸﾞﾗﾌｨｯｸ表示ｻｲｽﾞ（X）
		int		*ys				: out	ｸﾞﾗﾌｨｯｸ表示ｻｲｽﾞ（Y）

	[戻り値]
		TRUE	: 正常値
		FALSE	: 画像ｻｲｽﾞｵｰﾊﾞｰ(160x160ﾄﾞｯﾄより大きい)

	[処理内容]
******************************************************************************/
bool GetGraphSize(const byte far *graph, int *xs, int *ys)
/*TAIL*/
{
	*xs = graph[0] + ((int)graph[1]<<8);	/* ｸﾞﾗﾌｨｯｸ横ｻｲｽﾞ取得 */
	*ys = graph[2] + ((int)graph[3]<<8);	/* ｸﾞﾗﾌｨｯｸ縦ｻｲｽﾞ取得 */
	if(*xs>160 || *ys>160)
		return(FALSE);
/*	if(*xs<=8)
/*		return(FALSE);
*/
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		改行処理

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void NextLine(DSPCT *dct)
/*TAIL*/
{
	dct->x		= dct->sx;
	if(dct->st==1 || dct->st==2)	/* 見出し､又は小見出しの時 */
		dct->x -= D_SFTX*dct->st;	/* 表示開始位置を左にｼﾌﾄ */
	dct->y		+= dct->ity;
	dct->ity	= D_ITY;
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		見出しｺｰﾄﾞｻｰﾁ

	[引数]
		byte far	**tgt		: in/out	検索開始(発見)ﾎﾟｲﾝﾀ

	[戻り値]
		TRUE		: 正常終了（指定ｺｰﾄﾞ発見）
		FALSE		: 未発見

******************************************************************************/
bool TitleCodeSrc(byte far **tgt)
/*TAIL*/
{
	while(*tgt < (&Dbuf.bin_buf[10240])){

		if(CodeSrc(tgt,0x40)==FALSE)	/* 「@」ｺｰﾄﾞｻｰﾁ */
			return(FALSE);
		(*tgt) ++;

		if(**tgt==0x5c){
			(*tgt) ++;

			if(**tgt=='T'){		/* 「@\T」発見! */
				(*tgt) -= 2;
				return(TRUE);
			}
		}
	}
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｺｰﾄﾞｻｰﾁ

	[引数]
		byte far	**tgt		: in/out	検索開始(発見)ﾎﾟｲﾝﾀ
		byte		cd			: in		検索対象ｺｰﾄﾞ

	[戻り値]
		TRUE		: 正常終了（指定ｺｰﾄﾞ発見）
		FALSE		: 未発見
	[処理内容]
******************************************************************************/
bool CodeSrc(byte far **tgt, byte cd)
/*TAIL*/
{
/*	for(;(*tgt)<BUFEND;(*tgt)++){	*/
	for(;;(*tgt)++){				/* for TEST */

		if(**tgt==cd){
			return(TRUE);			/* ｺｰﾄﾞ発見時 */
		}

	}
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｸﾞﾗﾌｨｯｸﾃﾞｰﾀﾌｧｲﾙ読み込み

	[引数]
		word	flp		: in	ﾌｧｲﾙﾎﾟｲﾝﾀｰ(0～)

	[戻り値]
		TRUE	: 正常終了
		FALSE	: 読み出しｴﾗｰ

	[処理内容]
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
	[ﾀｲﾄﾙ]
		実ﾃﾞｰﾀﾌｧｲﾙ読み込み

	[引数]
		word	flp		: in	ﾌｧｲﾙﾎﾟｲﾝﾀｰ(0～)

	[戻り値]
		TRUE	: 正常終了
		FALSE	: 読み出しｴﾗｰ

	[処理内容]
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
	[ﾀｲﾄﾙ]
		ｲﾝﾃﾞｯｸｽﾌｧｲﾙ読み込み

	[引数]
		word	flp		: in	ﾌｧｲﾙﾎﾟｲﾝﾀｰ(0～)

	[戻り値]
		TRUE	: 正常終了
		FALSE	: 読み出しｴﾗｰ

	[処理内容]
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
	[ﾀｲﾄﾙ]
		DBﾌｧｲﾙ読み込み

	[引数]

	[戻り値]
		TRUE	: 正常終了
		FALSE	: 読み出しｴﾗｰ

	[処理内容]
		10KByteのﾊﾞｲﾅﾘｰﾌｧｲﾙを読み込む。
		ﾀﾞﾐｰﾃﾞｰﾀ24Byteを考慮し、（160+1）ﾌﾞﾛｯｸ読み込む事！
******************************************************************************/
bool DicFileRead(LFBUF far *buf, FILE_INFO *inf)
/*TAIL*/
{
	bool	jdg;

	jdg = LibLFileReadEx((LFILE_BUF far *)buf,inf,161);
									/* 先頭(10K+64)Byteのみ読み込み */
	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		1ﾃﾞｰﾀ読み込み

	[引数]

		LSTIDX	*lidx		: ﾘｽﾄｲﾝﾃﾞｯｸｽ構造体
			lidx.num			  in	取得ｲﾝﾃﾞｯｸｽ番号
			lidx.flp			  in	該当ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰの含まれるﾌｧｲﾙﾎﾟｲﾝﾀｰ
			lidx.ofs			  in	該当ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰのｵﾌｾｯﾄ

		byte far **tgt		: out	ﾃﾞｰﾀ開始ｱﾄﾞﾚｽ(「@\*」の次)

	[戻り値]

		TRUE	: 正常終了
		FALSE	: 読み出しｴﾗｰ

	[処理内容]
******************************************************************************/
bool DicDataRead(LSTIDX	*lidx, byte far **tgt)
/*TAIL*/
{
	word	flp, ofs;

	if(lidx->num==0xffffffff)
		return(FALSE);

	if(DicIndexFileRead(lidx->flp)==TRUE){	/* ｲﾝﾃﾞｯｸｽﾎﾟｲﾝﾀｰ該当ﾌﾞﾛｯｸ読み込み */
		flp = *(word far *)(&Ibuf.bin_buf[0] + lidx->ofs + 4 ) + topfp;
		ofs = *(word far *)(&Ibuf.bin_buf[0] + lidx->ofs + 6 );

		if(DicDataFileRead(flp)==TRUE){		/* 実ﾃﾞｰﾀ読み込み */
			*tgt = &Dbuf.bin_buf[0] + ofs;
			*tgt += 3;					/* ｢@\T｣ｽｷｯﾌﾟ */
			return(TRUE);
		}
	}
	return(FALSE);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｸﾞﾗﾌｨｯｸ 1 ﾃﾞｰﾀ読み込み

	[引数]
		LSTIDX	*lidx		: in/out	ｲﾝﾃﾞｯｸｽ構造体

	[戻り値]
		TRUE	: 正常終了
		FALSE	: 読み出しｴﾗｰ

	[処理内容]
******************************************************************************/
bool DicGraphRead(LSTIDX *lidx)
/*TAIL*/
{
	bool		jdg;
	word		ofs, flp, i;
	long		bict,num;
	byte far	*tgt;

	num = lidx->num;
	flp = topfp + gtopbk;		/* ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ先頭が含まれるﾌｧｲﾙ */
	ofs = gtopof;

	bict = (SZ_BLOCK-gtopof)/8;

	DicGraphFileRead(flp);			/* ｸﾞﾗﾌｨｯｸindexﾃﾞｰﾀ読み込み */

	for(i=0;i<gidxc;i++){

		jdg = JdgGraphIndex(ofs,num);		/* ﾀｰｹﾞｯﾄﾃﾞｰﾀのindexか判断 */
		if(jdg!=HALF){
			break;
		}else{
			ofs += 8;
			if(ofs>=SZ_BLOCK){
				flp ++;
				ofs = 0;
				if(DicGraphFileRead(flp)==FALSE){	/* ｸﾞﾗﾌｨｯｸindexﾃﾞｰﾀ読み込み */
					jdg = FALSE;
					break;
				}
			}
		}
	}

	if(jdg==TRUE){
		tgt = &Gbuf.bin_buf[0] + ofs;
		flp = topfp + *(word far *)(tgt+4);
		ofs = *(word far *)(tgt+6);			/* 実ﾃﾞｰﾀ開始ｵﾌｾｯﾄ */
		if(DicGraphFileRead(flp)==FALSE)	/* ｸﾞﾗﾌｨｯｸ実ﾃﾞｰﾀ読み込み */
			return(FALSE);
		lidx->flp = flp;
		lidx->ofs = ofs;
	}

	return(jdg);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ ｻｰﾁ

	[引数]
	[戻り値]
		TRUE	: 該当ｲﾝﾃﾞｯｸｽ発見
		HAFF	: 該当ｲﾝﾃﾞｯｸｽではない
		FALSE	: ｸﾞﾗﾌｨｯｸｲﾝﾃﾞｯｸｽ終了

	[処理内容]
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
	[ﾀｲﾄﾙ]
		ｸﾞﾗﾌｨｯｸ表示

	[引数]
	[戻り値]
	[処理内容]
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
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示総行数取得

	[引数]
		byte far	*tgt	: in	ﾃﾞｰﾀ開始ﾎﾟｲﾝﾀｰ

	[戻り値]
		
	[処理内容]
		ﾃｷｽﾄ縦幅(D_ITY)を一行分として、一件のﾃﾞｰﾀが何行分なのかを調べる
		但し､Bufには該当ﾃﾞｰﾀを含むﾌﾞﾛｯｸを読み込んでおく事｡
******************************************************************************/
long GetDicDspL(byte far *tgt, DSPCT *dctwk)
/*TAIL*/
{
	int		lc = 0;
	bool	loop = TRUE;
	int		i;

	dctwk->fnt	= IB_PFONT1;
/*	dctemp.pot	= tgt;			/* ﾃﾞｰﾀ開始ｱﾄﾞﾚｽ*/
	dctwk->pot	= dttop;
	dctwk->lkpt	= dctwk->pot;
	dctwk->jpf	= FALSE;

	while(loop){
		dctwk->y = dctwk->sy;				/* 行先頭は左端 */
		if(DicDsp1L(dctwk,FALSE)==FALSE)	/* 一行分処理 */
			loop = FALSE;
		i = (dctwk->y - dctwk->sy)/dctwk->ity;
		lc += i;
	}
/*	return(lc+1);	*/
	return(lc);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		文字列比較

	[引数]
		byte far	*stra	: 比較対象文字列Ａ
		byte far	*strb	: 比較対象文字列Ｂ
		int			len		: 比較文字列長

	[戻り値]
		TRUE	: 一致
		FALSE	: 不一致

	[処理内容]
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
	[ﾀｲﾄﾙ]
		ﾘﾝｸ処理

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
bool LinkSet(DSPCT *dct, bool den, bool jpf)
/*TAIL*/
{
	byte		ct;
	byte		j,ccd;
	byte far	*tgt;

	ct = *dct->pot;					/* ﾘﾝｸ指定文字数取得 */
	if(ct>TT_LEN)
		return(FALSE);

	dct->pot ++;

	/*** ﾘﾝｸ指定終了位置取得 ***/
	tgt = dct->pot;
	for(j=0;j<ct;){
		ccd = JdgContCode(&tgt);	/* 制御ｺｰﾄﾞ判断 */

		switch(ccd){

			case CD_CHA:		/* 文字ｺｰﾄﾞ「00h～7Fh」 */
			case CD_OVCHA:		/* 1ﾊﾞｲﾄｺｰﾄﾞ指定(0x80以上)「@\x??」 */
				tgt ++;
				j ++;
				break;

			case CD_FNT57:		/* 5x7ﾌｫﾝﾄ指定        「@\fNM」 */
			case CD_FNTPN:		/* ﾌﾟﾛﾎﾟｰｼｮﾅﾙﾌｫﾝﾄ指定 「@\fPN」 */
			case CD_FNTPB:		/* 太文字ﾌｫﾝﾄ指定     「@\fPB」 */
				break;

		/*	case CD_RTN:		/* 改行ｺｰﾄﾞ「0Dh」 */
			default:			/* Fail Safe */
				return(FALSE);
		}
	}
	dct->lkpt = tgt;
	dct->jpf  = jpf;

/*	if(lkpsp<LKPSCT){			/* 一画面内最大ﾘﾝｸ設定数以下の時 */
/*		lkps[lkpsp].smp = dct->pot - dttop;		/* ﾘﾝｸ設定ｴﾘｱ退避 */
/*		lkps[lkpsp].emp = lkps[lkpsp].smp + i;
/*		lkpsp ++;
/*	}
*/
	return(TRUE);
}


/*HEAD*/
/******************************************************************************
    [ﾀｲﾄﾙ]
    	ESCｽｷｬﾝ検査

    [引数]
    	なし

    [戻り値]
    	bool			検査結果	TRUE:	ESCｱｲｺﾝにﾀｯﾁあり
    								FALSE:	            なし
    [処理内容]
    	ESCﾊｰﾄﾞｱｲｺﾝにﾀｯﾁされているか検査する.
    	連続型の処理のﾌﾞﾚｰｸ時に用いる.

    [備考]
		SpredSheet(ZX481)より流用･･･「SpdTchEscScan()」
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
    [ﾀｲﾄﾙ]
    	「Please Wait...」ﾒｯｾｰｼﾞ表示

    [備考]
		SpredSheet(ZX481)より流用･･･「SpdWaitingMes()」
******************************************************************************/
void DicWaitingMes(void)
/*TAIL*/
{
	if(MesDone == FALSE)
		return;

	LibWinIcnMsg(ICON_COFFEE,381,0);
	LibCloseWindow();					/* LibWinIcnMsg(0)分 */
	MesDone = TRUE;
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾘｽﾄ表示中､ｽｸﾛｰﾙﾊﾞｰ Up/Downﾎﾞﾀﾝ ﾏｽｸ指定
	[引数]
	[戻り値]
		byte   mask : マスク情報
						SCR_NO_MASK:    網掛けなしで上下とも表示
						SCR_UP_MASK:    上矢印を網掛けにする
						SCR_DWN_MASK:   下矢印を網掛けにする
						SCR_ALL_MASK:   上下とも網掛け
	[処理内容]
******************************************************************************/
byte LstArrowMask(XT_SCR_POS *scr)
/*TAIL*/
{
	byte	mask;

	mask = SCR_NO_MASK;			/* とりあえず上下とも網掛けなし */

	if(lcp==0 && scr->pos==0){
		mask |= SCR_UP_MASK;		/* 上ｷｰ ﾏｽｸ */
	}

	if(lcp==L_LNC-1 && scr->pos==scr->vol - scr->dsp){
		mask |= SCR_DWN_MASK;		/* 下ｷｰ ﾏｽｸ */

	}else if(lcp<L_LNC-1 && lip[lcp+1].num==0xffffffff){
		mask |= SCR_DWN_MASK;		/* 下ｷｰ ﾏｽｸ */
	}
	return(mask);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾃﾞｰﾀ表示中､ｽｸﾛｰﾙﾊﾞｰ Up/Downﾎﾞﾀﾝ ﾏｽｸ指定
	[引数]
	[戻り値]
		byte   mask : マスク情報
						SCR_NO_MASK:    網掛けなしで上下とも表示
						SCR_UP_MASK:    上矢印を網掛けにする
						SCR_DWN_MASK:   下矢印を網掛けにする
						SCR_ALL_MASK:   上下とも網掛け
	[処理内容]
******************************************************************************/
byte DataArrowMask(XT_SCR_POS *scr)
/*TAIL*/
{
	byte	mask;

	mask = SCR_NO_MASK;			/* とりあえず上下とも網掛けなし */

	if(scr->pos==0){
		mask |= SCR_UP_MASK;		/* 上ｷｰ ﾏｽｸ */
	}

	if(scr->pos>=scr->vol - scr->dsp){
		mask |= SCR_DWN_MASK;		/* 下ｷｰ ﾏｽｸ */
	}
	return(mask);
}


/*HEAD*/
/******************************************************************************
	[ﾀｲﾄﾙ]
		ﾌｧｲﾙﾎﾟｲﾝﾀｰ初期化

	[引数]
	[戻り値]
	[処理内容]
******************************************************************************/
void FilePointerInit()
/*TAIL*/
{
	Ginf.fp = Dinf.fp = Iinf.fp = 0xffff;		/* 先頭ﾌｧｲﾙ */
	Ginf.kind = Dinf.kind = Iinf.kind = 1;		/* ﾊﾞｲﾅﾘ識別 */
}
