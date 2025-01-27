/******************************************************************************
	[TITLE]
	  OLD PV COMPATIBILITY LIBRARY PROTOTYPE DEFINATIONS
                                   REFERENCED ONLY SYSTEM VALIABLES
                                   REFERENCED ONLY SYSTEM GLOBAL VALIABLES
                                   REFERENCED ONLY SYSTEM TABLES

	Copyright (C) 2001 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#ifndef CLIBDEF
#define CLIBDEF

#include	"define.h"
#include	"LibProt.h"

/************************************************/
/*        Macro					                */
/************************************************/
#ifndef max
#define max(x, y) 				((x) >= (y) ? (x) : (y))
#endif

#ifndef min
#define min(x, y) 				((x) <= (y) ? (x) : (y))
#endif

#define GSIZE(x, y)				( ( word )x >> 8 ), ( ( word )x & 0x00ff ), ( ( word )y >> 8 ),	( ( word )y & 0x00ff )
#define CENTER(max, len)		(((int)(max)-(int)(len))>>1<0?0:((int)(max)-(int)(len))>>1)
/* for string operation */
#define LibChangeBcdVal( x )	( byte )( ( int )( x >> 4 ) * 10 + ( x & 0x0f ) )				/* library */
#define LibChangeValBcd( x )	( x == 0 ? 0 : ( byte )( ( ( x / 10 ) << 4 ) | ( x % 10 ) ) )	/* library */
/**/
#define LibTchRelease()			while(LibTchStackPop()!=NULL)
#define LibDateClr(d)			memset(d,0x00,8)
#define LibModeIconDsp()							\
{                                                   \
	LibPutFarData(130,  0, 44);						\
	LibPutMessageCenter( 89,131,157,2,IB_PFONT1);	\
}

/************************************************/
/*		GrobalArea								*/
/************************************************/
extern const TCHTBL 	TchAllDsp[];
extern const TCHTBL 	TchHardIcon[];
extern const TCHTBL 	TchActionKey[];
extern const TCHTBL 	TchModeIcon[];
extern volatile word			FlashStatus;		/* flash access status*/
extern volatile byte			SubEntryStat;		/* addin library execution status */
extern volatile byte			sb_ccategory[IM_NOTITLE_NUM][IM_MAX_BUF_CONTACTS];
extern volatile byte			sb_mcategory[IM_NOTITLE_NUM][IM_MAX_BUF_MEMO];
extern volatile unsigned int		Pen_Density;		/**/
extern volatile SETCLIPAREA_PACS	Effe_Area;			/**/
extern volatile unsigned int		BG_ID;				/**/
extern volatile INIT_PACS			vram_adr;			/**/
extern volatile byte			KeyWordBuf[IML_LIB_KW_BUF_SIZE];
extern volatile int				KeyWordTailPos;
extern volatile byte			Sys_LangInf;		/* Language Support (unique or 5lang) */
extern volatile byte			Sys_KeyBoardInf;
extern volatile byte 			Sys_SoundStat;		
extern volatile byte			Sys_PassWord[16];   /**/
extern volatile byte			Sys_USB;			/**/
extern volatile byte			Sys_EL_Time;		/**/
extern volatile byte			Sys_AlmBuzInfo;		/* alarm buzzer status */

/************************************************/
/*               SYSTEM AREA                    */
/************************************************/     
extern volatile word		SYS_KEY_FLG;			/* Keyboard flag                   */
extern volatile byte		SYS_KEY_KIND;			/* Keyboard type                   */
extern volatile word		SYS_CLD_DATE[3];		/* Calender date                   */
extern volatile byte		SYS_SCH_MODE;			/* Mode No.                        */
extern volatile byte		SYS_SCH_SBMODE;			/* SubMode No.                     */
extern volatile byte		SYS_SCH_SUBENTRY;		/* sub_entry                       */
extern volatile word		SYS_SCH_DTPOINT;		/* DataPointer                     */
extern volatile word		SYS_SCH_CTHD0;			/* Category0 Header                */
extern volatile byte		SYS_SCH_CTNM0[17];		/*           Name                  */
extern volatile word		SYS_SCH_CTHD1;			/* Category1 Header                */
extern volatile byte		SYS_SCH_CTNM1[17];		/*           Name                  */
extern volatile word		SYS_SCH_CTHD2;			/* Category2 Header                */
extern volatile byte		SYS_SCH_CTNM2[17];		/*           Name                  */
extern volatile byte		SYS_CALE_TYPE;			/* Calender Type                   */
extern volatile byte		SYS_SYNC_ID1[24];		/* Certification ID open           */
extern volatile byte		SYS_SYNC_ID2[24];		/*                  secret         */
extern volatile word		SYS_SYNC_MODE_INF;		/* CallingModeCode                 */
extern volatile byte		SYS_CAL_MEM[14];		/* Calculator Memory               */
extern volatile byte		SYS_TIME_FORMAT; 		/* Time display format             */
extern volatile byte		SYS_DATE_FORMAT; 		/* Date display format             */
extern volatile byte		SYS_DST[30];	 		/* DST according to the country    */
extern volatile byte		SYS_HOME_CITY;			/* HomeCity No.                    */
extern volatile byte		SYS_WORLD_CITY;  		/* WorldCity No.                   */
extern volatile byte		SYS_MENU_PTR;			/* ActionMenuPointer               */
extern volatile byte		SYS_TEL_CATEGORY;		/* CONTACTS CategoryType           */
extern volatile byte		SYS_MEMO_CATEGORY;		/* MEMO CategoryType               */
extern volatile byte		SYS_DELAY500;			/* */
extern volatile word		SYS_START_DATE[3];		/* ShedulerDueDate(start)          */
extern volatile word		SYS_END_DATE[3];		/* ShedulerDueDate(end)            */
extern volatile byte		SYS_INP_BUF[2049];		/* Copy/Paste Buffer               */
extern volatile byte		SYS_TIME_FLG;    		/* Home/World TimeFlag             */
extern volatile byte		SYS_MENU_MODE;			/* MenuDisplayType                 */
extern volatile byte		SYS_PAY_TYPE[10][14+1];	/* Payment Type Table              */
extern volatile byte 		SYS_EXP_TYPE[10][14+1];	/* Expense Type Table              */
extern volatile byte 		SYS_PAY_NO;				/* Payment Type Last Setting       */
extern volatile byte 		SYS_EXP_NO;				/* Expense Type Last Setting       */
extern volatile byte 		SYS_AMT_ITEM;			/* AmountListDisplayItem LastSetting */
extern volatile byte 		SYS_PTTL_ITEM;			/* Period TotalDisplayItem LastSetting */
extern volatile byte		SYS_SRCH_WORD[13];		/* SchedulerSearchKeyword          */
extern volatile byte 		SYS_SOL_LEVEL;			/* Game1 LevelInformation          */
extern volatile dword 		SYS_SOL_HI_SCORE[3];	/* Game1 HighScore                 */
extern volatile dword 		SYS_SOL_HI_TIME[3];		/* Game1 BestTime                  */
extern volatile byte 		SYS_PYR_LEVEL;			/* Game2 LevelInformation          */
extern volatile dword 		SYS_PYR_HI_SCORE[3];	/* Game2 HighScore                 */
extern volatile dword 		SYS_PYR_HI_TIME[3];		/* Game2 BestTime                  */
extern volatile byte		SYS_KEYBOAD_TYPE;		/* KeyboardLastValue               */
extern volatile word		SYS_TEL_INP_ITEM[7];	/* CONTACTS InputItem              */
extern volatile word		SYS_TEL_HIST_PTR[17];	/* CONTACTS HistoryPointer          */
extern volatile byte		SYS_TEL_FONT;			/* CONTACTS FontType               */
extern volatile word		SYS_TEL_SHIST_PTR[17];	/* CONTACTS HistoryPointer(for SECRET) */
extern volatile byte 		SYS_TEL_CENTER_POS[9];	/* CONTACTS CenterLinePosition     */
extern volatile byte 		SYS_TEL_RGT_KMK[7];		/* CONTACTS ListDisplayItem        */
extern volatile byte 		SYS_PASS_MATCH;			/* Password Match Flag             */
extern volatile byte 		SYS_PEN_INF;			/* Q-MEMO PenSize                  */
extern volatile byte 		SYS_ERA_INF;			/* Q-MEMO EraserSize               */
extern volatile byte		SYS_DAILY_ALM[4];		/* DailyAlarmTime				   */
extern volatile byte		SYS_CONV_MODE;			/* CONVERSION ModeFlag             */
extern volatile byte		SYS_DECI_CMODE;			/* CrossConversionDecimalPointModeFlag */
extern volatile byte		SYS_DECI_EMODE;			/* EuroConversionDecimalPointModeFlag   */
extern volatile byte		SYS_ECONV_DISP[3];		/* EuroConversionRateTable         */
extern volatile byte		SYS_EX_ECONV_RATE[16][7];		/* EuroConversionRateTable         */
extern volatile byte		SYS_EX_ECONV_NAME[16][5];		/* EuroConversionUintNameTable     */
extern volatile byte		SYS_EX_ECONV_SEIDO[16];			/* EuroConversionDecimalPointSettingTable */
extern volatile byte		SYS_CONV_RATE[3][13];	/* CrossConversionRateTable        */
extern volatile byte		SYS_CONV_NAME[3][5];	/* CrossConversionUnitNameTable    */
extern volatile byte		SYS_CONV_SEIDO[3];		/* CrossConversionDecimalPointSettingTable */
extern volatile byte		SYS_SCH_FONT;			/* SCHEDULER FontType              */
extern volatile byte		SYS_MEMO_FONT;			/* MEMO    FontType                */
extern volatile byte		SYS_EXP_FONT;			/* EXPENSE FontType                */
extern volatile byte		SYS_IMENU_PAGE;			/* Page                            */
extern volatile byte		SYS_IMENU_MAXPAGE;		/* MaximumPage                     */
extern volatile byte		SYS_IMENU_INFO;			/* SYS_IMENU_LINK Initial OK?      */
extern volatile MJMP_INFO	SYS_IMENU_LINK[IML_MJMP_INFO_MAX];	/* MenuLineInformation             */
extern volatile dword		SYS_SYNC_PARAM;			/* Syncronize Parameter            */


/* INCLUDE ADDITION LIBRARY */
#include "addlib.h"


#endif
