/******************************************************************************
	[TITLE]
		COMATIBILITY LIBRARY PROTOTYPE DEFINATIONS

	Copyright (C) 2001 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#ifndef LIBPROT_H
#define LIBPROT_H

#include	"define.h"  

/************************************************/
/*           LibraryPrototype		            */
/************************************************/
/***** Display *****/
// DD 
void LibPutDisp(void);
void LibPutDispBox(int x, int y, int xsize, int ysize);
// Dot Disp
void LibDotOn(int x, int y);
void LibGdsDotOn(int x,int y);
void LibDotOff(int x, int y);
void LibGdsDotOff(int x,int y);
void LibGdsDotCmp(int x,int y);
void LibPutDotSub(int x,int y,byte type);
// Line Disp
byte LibLine(int x, int y, int xsize, int ysize, byte bold);
void LibGdsLine(int x,int y,int x2,int y2);
void LibMeshLine(int x, int y, int xsize, int ysize);
void LibGdsLineMesh(int x,int y,int x2,int y2);
void LibLineClr(int x, int y, int xsize, int ysize);
void LibGdsLineClr(int x,int y,int x2,int y2);
void LibLineCplmnt(int x, int y, int xsize, int ysize);
void LibGdsLineCmp(int x,int y,int x2,int y2);
void LibPutLineSub(int x,int y,int x2,int y2,byte type);
// Box Control 
void LibClrDisp(void);
void LibReverse(int px, int py, int xsize, int ysize);
void LibGdsReverse(int x,int y,int x2,int y2);
void LibMesh(int px, int py, int xsize, int ysize);
void LibGdsMesh(int x,int y,int x2,int y2);
void LibGdsClr(int x,int y,int x2,int y2);
void LibClrBox(int x, int y, int xsize, int ysize);
void LibCngeBoxSub(int x,int y,int x2,int y2,byte type);
void LibGetGraph(int x, int y, int xsize, int ysize, byte *ubfptr);
void LibGrpUp(int x, int y, int xsize, int ysize, int up_size);
void LibGrpDwn(int x, int y, int xsize, int ysize, int dw_size);
// Box Disp
byte LibBox(int x, int y, int xsize, int ysize, byte type);
void LibGdsBox(int x,int y,int x2,int y2);
void LibGdsBoxMesh(int x,int y,int x2,int y2);
void LibGdsBoxClr(int x,int y,int x2,int y2);
void LibGdsBoxCmp(int x,int y,int x2,int y2);
void LibPutBoxSub(int x,int y,int x2,int y2,byte type);
// Graphic Disp Func
void LibPutGraph(int x, int y, const byte *graph);
void LibPutGraphO(int px, int py, byte *ptn, int mode);
void LibPutGraphM(int x, int y, byte *graph);
void LibGrphUpSideDown(byte *gw,byte *gs);
void LibPutFarData(int x, int y, int no);
void LibSKeyRevSub(int x, int y, int x2, int y2, byte rev,byte type);
// Font Disp Func
int LibPutProFont(byte type, byte code, int x_pos,int y_pos);
int LibGetProFontSize(byte type, byte code);
void LibPutProStr(byte type,int x,int y,byte *string,int x_size);
int LibGetProStrSize(byte type,byte *string);
void LibPut35Font(byte code,int x_pos,int y_pos);
void LibPut35Str(int x,int y,byte *string);
void LibStringDsp(byte *strg, word xps, word yps, word lmtx, byte font);
// Other                 
void LibSetDispMode(bool flag);
void LibInitDisp(void);
// Window Func
bool LibOpenWindow(int x, int y, int xsize, int ysize);
void LibOpenWindowS(byte flame, word px, word py, word xsize, word ysize);
void LibCloseWindow(void);
// 5Lang Message Func
void LibPutMessage(word no,int p_x,int p_y,byte type);
void LibPutMessageCenter(word no,int p_x1,int p_x2,int p_y,byte type);
void LibPutMessageCenter2(word no,int p_x,int p_y,byte type);
void LibPutMessageRight(word no,int p_x,int p_y,byte type);
void LibReadMessage(word no,byte *buf);
byte LibGetMessCnt(int mes_no);
void LibDspWinMessage(byte g_no,int mes_no,byte b_cnt,byte b_type);
void LibGetWinMessSize(int mes_no,byte w_pos,byte b_cnt,int *y,int *y_size);
//Hand Writing
void LibDrawInit(INIT_PACS draw_prm);
void LibDrawSetPtn(byte val);
void LibDrawSetClipArea(SETCLIPAREA_PACS draw_prm);
void LibDrawSetPoint(byte page,int x,int y,byte point,byte mode);
void LibDrawLine(DRAWLINE_PACS draw_prm,byte page)	;
void LibDrawBox(DRAWBOX_PACS draw_prm,byte page);
void LibDrawCircle(DRAWCIRCLE_PACS draw_prm,byte page)	;
void LibDrawFillArea(FillArea_PACS draw_prm,byte page);
void LibDrawTransDD(TransDD_PACS draw_prm,byte dd)	;
void LibDrawTransAll(byte val)	;
void LibDrawPutImage(PutImage_PACS draw_prm,byte page);
bool LibDrawGetImage(GetImage_PACS draw_prm,byte page);
bool LibDrawReductImage(ReductImage_PACS draw_prm);
int  LibDrawPrmCall(byte func_no,void *draw_prm,byte al);                        
bool LibScrShot(SHOT_INF *s_inf);

/***** Window Menu *****/
byte LibSelWindow(int x, int y, int xs, byte ln, byte np, SLW_TBL *ktb);
byte LibSelWindow2(int y, byte ln, SLW_TBL *ktb, word msk);
byte LibSelWindowExt(SLW2_ST *slw);
byte LibSelWinExt2A(SLW2_ST *slw);
byte LibSelWinExt2B(SLW2_ST *slw, byte ln);
bool LibWinIcnMsg(byte icn, word msg, byte wtyp);
word LibPullDown(void);
int LibPullDownInit(word *edt,word *sys,word *opt);
int LibPullDownAtrSet(int mode,word type,word item);
void LibEditPullDown(void);
void LibSelWinLckA(int x, int y, int ity, int xs, byte ln, SLW_TBL *ktb);
byte LibSelWinLckB(int x, int y, int ity, int xs, byte ln, byte np, SLW_TBL *ktb);
bool LibSelectFont(byte *font);

void LibSelWinOpen2(int x, int y, byte iy, int xs, byte ln, SLW_TBL *ktb, word msk);
byte LibSelectWin(int x, int y, byte iy, int xs,  byte ln, byte np);
void LibSelWinTchSet(void);

/***** Touch Event *****/
// Tpuch Event
void LibTchInit(void);
void LibTchStackClr(void);
TCHTBL *LibTchStackPop(void);
bool LibTchStackPush(TCHTBL *tbl);
bool LibTchHardIcon(TCHSTS *tsts, byte opt);
void LibTchWait(TCHSTS *tsts);
void LibRepOff(void);
void LibTchWaitSub(TCHSTS *tsts);
// Icon Touch Func
void LibIconPrint(const T_ICON *icon);
void LibIconPrintR(const T_ICON *icon);
void LibIconPrintM(const T_ICON *icon);
bool LibIconClick(const T_ICON *icon, const TCHSTS *tsts);
bool LibIconClick2(const T_ICON *icon, const TCHSTS *tsts);
void LibIconMoveDown(byte *inbuf, byte *workbuf, byte kind);
void LibIconMoveUp(byte *inbuf, byte *workbuf, byte kind);
bool LibBlockIconClick(const T_ICON *icon,TCHSTS *tsts,byte opt);
// Scroll Bar Func
void LibScrollPrint(T_SCR_POS scr);
void LibScrollArrowPrint(T_SCR_POS scr,byte mask);
int LibScrollClick(TCHSTS *tsts,T_SCR_POS *scr_pos);
int LibScrPosCheck(TCHSTS tsts,T_SCR_POS scr);
// Software KeyBoard Func
void LibKeyInit(void);
void LibDispKey(void);
byte LibGetKeyM(TCHSTS *tsts);
byte LibGetCale(byte *db, TCHSTS *tsts, int xsp, int ysp, int xep, word mes, byte type, byte type1, byte F_Type);
word LibInputTime(TCHSTS *tsts,LPTIMEKEYBCTRL lptbl,bool IsDispKeyb);
word LibInputTimeBar(TCHSTS *tsts,LPTIMEKEYBCTRL lpstbl,LPTIMEKEYBCTRL lpetbl);
word LibInputTerm(TCHSTS *tsts,LPTIMEKEYBCTRL lpstbl,LPTIMEKEYBCTRL lpetbl);
void LibSKeyRev(TCHTBL *sk_tbl,word obj_cd,byte sw);
bool LibSKeyIsCd(TCHTBL *sk_tbl,word obj_cd);
void LibCldKeyInit(TCHSTS *tsts, byte *db, int xsp, int ysp, byte type1, byte F_Type);
// Break Sampling Func
void LibBkSampleInit(BK_SMPL_TCH *t_tbl);
byte LibBkSampleCheck(bool *done);
void LibBkSampleInitSub(BK_SMPL_TCH *t_tbl, byte b_smp);

/***** Text Input, Drag Func ******/
// Text Input Func
void LibTxtInit(TXTP *tp);
void LibTxtTchSet(TXTP *tp);
void LibTxtInp(byte keycd, TCHSTS *tsts, TXTP *tp);
bool LibTxtDsp(TXTP *tp);
void LibTxtKeyWordSet(TXTP *tp);
// Data Disp Func
bool LibTxtDspC(TXTP *tp);
void LibTxtDspInit(TXTP *tp);
void LibTxtDspS(TXTP *tp, TCHSTS *tsts);
void LibTxtWrapSw(int Sw);
// Cursor 
bool LibGetCursor(int *c_xp, int *c_yp, int *c_xsize ,int *c_ysize);
void LibCurBlnkOn(int x, int y, int xsize, int ysize);
void LibCurBlnkOn2(int x, int y, int xsize, int ysize);
void LibCurBlnkOff(void);
void LibCurErase();

/***** String Func *****/
// KeyWord Func
void LibKeyWordInit(void);
void LibKeyWordSet(byte	*key_str);
bool LibKeyWordFSrch(byte *srch_str,byte *key_str);
bool LibKeyWordNSrch(byte *srch_str,byte *key_str);
void LibKeyWordSrchSub(byte sw,byte *srch_str,byte *key_str);
// String Control
bool LibCutTextRtn(byte *txbf);
void LibBCD2Ascii(byte bcd, byte *ascii);
byte LibAscii2BCD(char *ascii);
void LibNumToStr(byte *buff, word target, byte j);
void LibSToNum(byte *buff, word *res_num, byte j);
void LibLblAreaClr();
void LibLblAreaWrite(byte *fb, byte typ);
void LibLblAreaRead(byte *fb, byte typ);

/***** Date/Time *****/
// Date/Time Func
byte LibGetDateTimeM(byte *d_data);
byte LibGetDateTime(byte *yearh, byte *yearl, byte *month, byte *day,byte *hour, byte *minute, byte *second);
byte LibGetDateTime2(word *year2, byte *month2, byte *day2,byte *hour2, byte *minute2, byte *second2);
byte LibGetDate(byte *yearh, byte *yearl, byte *month, byte *day);
byte LibGetDate2(word *year2, byte *month2, byte *day2);
void LibGetTime(byte *hour, byte *minute, byte *second);
void LibGetTime2(byte *hour2, byte *minute2, byte *second2);
void LibAdjustTimeDeff2(int lag, word *year2, byte *month2, byte *day2, byte *dweek2,byte *hour2, byte *minute2, byte *second2);
byte LibChangeTotalDay(word *year2, byte *month2, byte *day2, dword tday);
dword LibGetTotalDay2(word year2, byte month2, byte day2);
void LibSetDateTime(byte yearh, byte yearl, byte month, byte day, byte hour, byte minute);
void LibSetDateTime2(word year2, byte month2, byte day2, byte hour2, byte minute2);
void LibSetDate2(word year2, byte month2, byte day2);
void LibSetTime2(byte hour2, byte minute2);
byte LibGetDow(byte *buff);
byte LibGetDays(word *buf);
byte LibChkFuture(byte *tgt, byte *now, byte ct);
void LibSummerTimeSet(void);

// Date/Time Disp Input
bool LibDateDisp(byte *buff, byte type, int xp, int yp, int xep, byte dmode, byte F_Type);
bool LibCheckDate(byte *dbuff);
bool LibChkTimeBuf(byte *buf);
void LibClkDispLine(LPTIMEKEYBCTRL lptbl);
void LibClkDispCursor(LPTIMEKEYBCTRL lptbl,int csrpos);
void LibConvRaw2Lib(byte *dest,byte *src,bool IsLarge);
void  LibConvRaw2Lib2(byte *dest,byte *src);
void LibConvLib2Raw(byte *dest,byte *src);
int LibGetCursorPos(int x,int y,LPTIMEKEYBCTRL lptbl);
bool LibJumpDate(byte *s_date);
void LibWait(byte time);

/***** Alarm *****/
void LibAlarm(void);
void LibNextAlmSet(void);
void LibChkSysAlarm(void);
void LibInitAlarmFlg(void);
bool LibInitAlarmFlgCheck(void);
int LibGetAlarmFlg(void);
bool LibGetAlarmInfo(FILE_BUF *afd, FILE_INFO *afi);
void LibInitAlarm(void);
void LibGetDailyAlarm(char *tbp);
int LibSetDailyAlarm(char *tbp);
bool LibNextAlarmSet(ALMAPL *almap, char type);
void LibGetNextAlm(ALMAPL *almap, byte ifdel);
byte LibAlarmBuzzSet(byte b_type);
void LibGetAlarmObj(TCHTBL *t_tbl);

/***** Flash ******/
bool LibFileFindNext(FILE_BUF *fb, FILE_INFO *finf, byte search);
bool LibLFileFindNext(LFILE_BUF *fb, FILE_INFO *finf, byte search);
bool LibFileFindPrev(FILE_BUF *fb, FILE_INFO *finf, byte search);
bool LibLFileFindPrev(LFILE_BUF *fb, FILE_INFO *finf, byte search);
bool LibFileFindNextExt(FILE_BUF *fb, FILE_INFO *finf, byte search);
bool LibLFileFindNextExt(LFILE_BUF *fb, FILE_INFO *finf, byte search);
bool LibNextSearchCld(FILE_BUF *fb, FILE_INFO *finf, byte search);
bool LibLNextSearchCld(LFILE_BUF *fb, FILE_INFO *finf, byte search);
bool LibFileRead(FILE_BUF *fb, FILE_INFO *finf);
bool LibLFileRead(LFILE_BUF *fb, FILE_INFO *finf);
bool LibFileWrite(FILE_BUF *fb, FILE_INFO *finf);
bool LibLFileWrite(LFILE_BUF *fb, FILE_INFO *finf);
bool LibFileCorect(FILE_BUF *fb, FILE_INFO *finf, byte type);
bool LibLFileCorect(LFILE_BUF *fb, FILE_INFO *finf, byte type);
bool LibFileRemove(FILE_BUF *fb, FILE_INFO *finf);
bool LibLFileRemove(LFILE_BUF *fb, FILE_INFO *finf);
bool LibFileRemoveAll(FILE_BUF *fb);
bool LibLFileRemoveAll(LFILE_BUF *fb);
void LibTodoFileRemove(FILE_BUF *fd);
void LibLTodoFileRemove(FILE_BUF *fd);
bool LibFileExch(FILE_BUF *fb, FILE_INFO *finf, word mvp);
bool LibLFileExch(LFILE_BUF *fb, FILE_INFO *finf, word mvp);
bool LibFileReadEx(FILE_BUF *fb, FILE_INFO *finf,int maxblock);
bool LibLFileReadEx(LFILE_BUF *fb, const FILE_INFO *finf,int maxblock);
void LibGetFileInfo(FILE_BUF *fd, FILE_INFO *fi);
void LibLGetFileInfo(LFILE_BUF *fd, FILE_INFO *fi);
word LibGetFileCnt(FILE_BUF *fd);
word LibLGetFileCnt(LFILE_BUF *fd);
dword LibGetFlash(void);
dword LibGetFreeBlock(void);
bool LibGetDataCond(void);
int	LibFileRemake(void);
word LibTelPtCnvrt(word fp);
void	LibErrorDisp(word err_code);

/***** Mode *****/
// Mode Move Func
void LibGetMode(word *m_code, word *m_sts, void **mode_info);
void LibGetLastMode(word *m_code, word *m_sts, void **mode_info);
bool LibModeJump(word m_code,byte m_sts);
void LibJumpMenu(void);
void LibMenuJump(word m_code);
void LibCallListMenu(void);
void LibCrdlOpnJmp(void);
void LibDataCom(void);
void LibModeRestart(void);
void *LibDualWin(word m_code, byte m_sts, void *ptr);
bool LibDualWinExit(void *ptr);
// Password Control
void LibScrtJmp(byte m_sts,word m_ofs);
void LibSecretCall(void    *info);
void LibScrtModeJmp(void);
void LibMoveArea(void);
void LibPassWordEdit(void);
bool LibPassWordCheck(void);
void LibFileCom(void);

/***** Addin *****/
// Program
word LibExeAddin(void);			// Dummy Nop Function
word LibGetDLAllNum(byte part);
void LibGetUserMode(word *mode_code, word *status, byte condition);
bool LibGetProgramName(byte *name_str, byte main_code, byte sub_code);
bool LibGetModeVer(byte *ver_str, byte main_code, byte sub_code);
bool LibGetLibVer(byte *ver_str, byte main_code, byte sub_code);
bool LibGetMenuIcon(byte **graph_addr, byte main_code, byte sub_code);
bool LibGetListIcon(byte **graph_addr, byte main_code, byte sub_code);
bool LibCheckPMode(byte main_code, byte sub_code, word status);
// Data
bool LibSubEntrySave(byte *name_str, byte *sub_entry);
bool LibSubEntryDel(byte *name_str, byte *sub_entry);
bool LibSubEntryRename(byte *old_name, byte *new_name, byte *sub_entry);
bool LibSubEntrySearch(byte *name_str, byte *sub_entry);
bool LibGetSubEntrySt(byte *name_str, byte sub_entry);
word LibGetSubEntNum(void);
bool LibGetAllEntry(byte *name_str, byte *mode_entry, byte *sub_entry);

/***** Serial *****/
word LibSrlPortOpen(SRL_STAT *po);
word LibSrlPortClose(void);
word LibSrlPortFClose(void);
word LibSrlRxBufClr(void);
word LibSrlTxBufClr(void);
word LibSrlGetDteStat(word *num, word *flag);
byte LibSrl232CStat(void);
word LibSrl232COpe(byte stat);
word LibSrlRateSet(byte speed);
word LibSrlGetRBufChar(void);
word LibSrlGetTBufSpace(void);
word LibSrlSendByte(byte tmode, byte data);
word LibSrlRecvByte(byte *data);
word LibSrlPreRead(word oft, byte *data);
word LibSrlSendBreak(byte time);
word LibSrlSendBlock(byte *data, word size);
word LibSrlRecvBlock(byte *data, word size, word *num);
word LibSrlGetOpenStat(void);

/*****  System Setting  *****/
// Function
void LibFuncDateTime(void);
void LibFuncSound(bool IsAlarmOnly);
void LibFuncFormat(void);
bool LibFuncLang(void);
void LibFuncCapa(void);
void LibFuncContrast(void);
void LibFuncDigitizer(void);
void LibFuncMemoryManagement(void);
bool LibFuncPtool(void);
void LibCalWin(byte tch_btn);
bool LibFuncUSB(void);
// System Status
word LibSaveSysRam(void);
word LibSaveSysRamB(void);
bool LibGetBLD(void);
void LibGetVersion(byte *ver_str);
void LibGetVer2(byte *ver_str);
void LibELHandle(byte mode);
byte LibGetEL(void);
byte LibGetLang(void);
void LibSetLang(byte lang);
byte LibSoundGet(void);
void LibSoundSet(byte opt);
bool LibContrastInit(void);
bool LibContrastUp(void);
bool LibContrastDown(void);
byte LibDigitizer(word *obj);
void LibPassClr(void);
void LibPassSet(byte  *pas_buf);
int LibPassGet(byte  *pass_buf);
bool LibPassChk(byte  *pass_buf);
word LibGetAPOTime(void);
void LibSetAPOTime(word msec);
void LibSetKeyKind(byte type);
byte LibGetKeyKind(void);
void LibBuzzerOff(void);
void LibBuzzerOn(byte b_type);
byte LibGetLangInf(void);
dword LibGetModelType(void);
byte LibGetCommDevice(void);
bool SysGetPONstat(void);
void SysSetPONstat(bool OnStat);
bool SysGetSUPstat(void);
void SysSetSUPstat(bool OnStat);
void SysSetELTime(byte elt);
byte SysGetELTime(void);

/***** Calculator *****/                            
// Calc Func 
void LibCalBaseData(byte *a_dat,const byte *n_dat1,const byte *n_dat2,byte kind);
void LibCalBase(CALWRAM *calram,byte kind);
bool LibCalBase2(byte *a_dat,const byte *n_dat1,const byte *n_dat2,byte kind);
void LibCalRoot(CALWRAM *calram);
// Calc Mode Func 
void LibCalKeyInit(CALWRAM *calram);
void LibCalKeyDsp(CALWRAM *calram);
void LibCalKeyTchWait(CALWRAM *calram,TCHSTS *tsts);
void LibCalBuf2Dat(byte *c_dat,const byte *c_buf);
void LibCalDat2Buf(byte *c_buf,const byte *c_dat);

/***** Debug *****/
void LibPutMsgDlg(byte *format, ...);
void LibPutMsgDlg2(byte *format, ...);
void LibPutMsgDlg3(byte *format, ...);
void LibPutMsgDlg4(byte *format, ...);                  

#endif
