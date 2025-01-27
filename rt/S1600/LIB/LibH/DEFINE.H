/******************************************************************************
	[TITLE]
  	  COMPATIBILITY LIBRARY HEADER  FOR GENERIC USERS

      if you use BIOS CALL HEADER, please include 'bios.h' before 'define.h'
      and 'define.h'.

  	  Copyright (C) 2002 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/
#ifndef DEFINEDEF
#define DEFINEDEF

/************************************************/
/*               tyepdef & enum                 */
/************************************************/
/* Variable */

#ifndef _BIOS_H_

typedef	int	bool;
typedef	int	BOOL;

#define	FALSE	0
#define	TRUE	1
#define	HALF	2		//for old pv comatibility

typedef	unsigned char	byte;			/* 1 Byte */
typedef	unsigned short	word;			/* 2 Byte */
typedef	unsigned long	dword;			/* 4 Byte */

#endif

/* SuspectedKeyCode for TimeKeyBoard(It allocates for 0x80 since then.)*/
enum {CLKKEY_OTHER=0,
	  CLKKEY_CLKBOARD=0x80, CLKKEY_AM,CLKKEY_PM,CLKKEY_TIMEBAR,
	  CLKKEY_NUMBER, CLKKEY_DEL,CLKKEY_NEXT,CLKKEY_LEFT,CLKKEY_RIGHT,
	  CLKKEY_TIMEKEYB,CLKKEY_DRAGBAR,CLKKEY_TOUCHBAR,CLKKEY_LSHIFT,
	  CLKKEY_RSHIFT,CLKKEY_CSRMOVE,
	  CLKKEY_ILLEGAL };

/************************************************/
/*                 Literal                      */
/************************************************/     

/* Judgment */
#define ON      		1
#define OFF     		0

/************************************************/
/*               define type                    */
/************************************************/    
/************************
 *   New Definations    *
 ************************/
/* Keyword register library defination */
#define IML_LIB_KW_BUF_SIZE			1024

/* Calender Keyboard Object */
#define IM_OBJ_CALE_NEXT			0x8665		/* [NEXT] key */

/* Touch Object(for generic key input/data output) */
#define IML_OBJ_TXTTCH				0x9002
#define IML_OBJ_SCR_BAR				0xc011

/* Flash Memory Access Definations */
#define IMB_FILE_KIND_BIN			0x01		/* Binary File */
#define IMB_FILE_KIND_TEXT			0x00		/* Text File */
#define IMB_FILE_OPEN_MODE 			0x80		/* open mode */
#define IMB_FILE_SECRET_MODE	 	0x00		/* secret mode */
#define IML_FILE_BLOCK_SIZE 		64			/* 1block size */

/* Flash Bios Path defination */
#define MAX_PATHLEN       127
#define MAX_FILENAMELEN   62
#define MAX_DEVICENAMELEN 16
#define MAX_EXTNAMELEN    3

/* FlashDataBuffer */
#define IMB_ITEM_TOP				0xFE
#define IMB_TEXT_END				0x00

/* FLASH error code */
#define IML_NORMALCY				0x0000		/* No problem                                */
#define IML_NUL_BUFF				0x0001		/* No data to register. */
#define IML_WRITE_ERR				0x0002		/* x（used inside）                          */
#define IML_FORMAT_ERR				0x0003		/* Fatal error                               */
#define IML_MAX_CHAR_ERR			0x0004		/* The number of characters to be registered exceed the limit. */
#define IML_TME_DATE_ERR			0x0005		/* The data other than numeric number exists. (Date/Time) */
#define IML_OUT_PNTA_ERR			0x0006		/* The setting pointer has an illegal value (out of range). */
#define IML_TWIN_DAT_ERR			0x0007		/* When deleting data in TEL<COMPANY> mode,
													there is no 4-byte data to be paired.	*/
#define IML_MEMORY_OVER				0x0008		/* Unable to register because of the insufficient memory capacity. */
#define IML_ARM_TOTL_ERR			0x0010		/* The number of registered alarms exceed the maximum. */
#define IML_ARM_SAMV_ERR			0x0011		/* The same alarm value already exists. */
#define IML_ARM_NULL_ERR			0x0012		/* Alarm is empty. */
#define IML_CRADLE_ERR				0x0020		/* The cradle ID of the write destination is not FFFFh. */
#define IML_PARAMET_ERR				0xFFFE		/* Illegal value is set: Debug purpose only.  */
#define IML_NO_DATA_ERR				0xFFFF		/* No data exists for search. */
#define IML_ARM_OLDV_ERR			0xB000		/* Alarm is the past date. */
#define IML_SCRT_ACS_ERR			0xA000		/* Access a SecretData in OpenMode */
#define IML_ENUM_RATEEND			0x0040		/* end of enumrating files	*/
#define IML_DEVICECHANGED_ERR		0x0041		/* changed device state */
#define IML_RECORD_NOTFOUND_ERR		0x0042		/* selected record not found */
#define IML_NOT_ALMZSUPPORT_ERR		0x0050		/* not alarm support file */
#define IML_ALMFILE_REGIST_ERR		0x0051		/* cannot register a alarm file for alarm format */
#define IML_ESCKEY_BREAK			0x0060		/* stopped by break key	*/
#define IML_SEARCH_NEARDATA			0x0061		/* near data search	*/
#define IML_INTERNAL_ERR			0x0100		/* internal error(font conversion) */
//#define IML_RECORD_MAX_ERR		IW_MEMORY_OVER		/* too many number of records(see blow.) */

// if not inclueded BIOS.H :)
#ifndef _BIOS_H_

/****************************************************************************/
/*				CODES														*/
/****************************************************************************/
#define	FONTCHARACTER	unsigned short		
#define	PV_CHAR			unsigned char		/* PV CHARACTER */
#define	PV_EOS			(PV_CHAR)(0x00)		/* PV End Of String */
#define	CP_CHAR			unsigned char		/* CP CHARACTER */
#define	CP_EOS			(CP_CHAR)(0x00)		/* CP End Of String */

/****************************************************************************/
/*				STRUCTURE													*/
/****************************************************************************/
/* SYSTEM TIME */
typedef struct TimeSys{
		byte	year_high;		/* YEAR(High):BCD  */
		byte	year_low;		/* YEAR(Low):BCD   */
		byte	month;			/* MONTH:BCD       */
		byte	day;			/* DAY:BCD         */
		byte	hour;			/* HOUR:BCD        */
		byte	min;			/* MINUTE:BCD      */
		byte	sec;			/* SECOND:BCD      */
		byte	dummy;			/* ﾀﾞﾐｰ            */
}TIMESYS;

/****************************************************************************/
/*				BIOS DEFINATIONS FOR APPLICATIONS  							*/
/****************************************************************************/

// OBJECT CODES
//------------------------------------------------------------------------------------------
#define	OBJ_BASE_SYSTEM    0x0000      // system object base number

#define	OBJ_END            0x0000      // Object array end mark

#define	OBJ_SYS_BLD1       0x0001      // BLD1 Detect
#define	OBJ_SYS_BLD1CLOSE  0x0002      // BLD1 Disp fin
#define	OBJ_SYS_APO        0x0003      // APO(AutoPowerOFF)
#define	OBJ_SYS_1SEC       0x0004      // RTC 1sec update
#define	OBJ_SYS_500MSEC    0x0005      // System Clock 500msec
#define	OBJ_SYS_STACOM     0x0006      // Remote On
#define	OBJ_SYS_CONNECTKEY 0x0007      // Ext. keyboard connected
#define	OBJ_SYS_CUTOFFKEY  0x0008      // Ext. Keyboard dis-connected
#define	OBJ_SYS_TMR        0x0009      // timer just arrived(normal or system)
#define	OBJ_SYS_DATAERR    0x000A      // Data Error Detect		@2002.04.25
#define	OBJ_SYS_PWON       0x000F      // ON

#define	OBJ_ESC            0x0010      // Break key sample ESC
#define	OBJ_SYS_CRDLKEY    0x0011      // Sync Key
#define	OBJ_LPSW_PUSH      0x0012      // Action key : PUSH 
#define	OBJ_LPSW_UP        0x0013      // Action key : Up   
#define	OBJ_LPSW_DOWN      0x0014      // Action key : Down 
#define	OBJ_LPSW_LEFT      0x0015      // Action key : LEFT 
#define	OBJ_LPSW_RIGHT     0x0016      // Action key : RIGHT
#define	OBJ_ALL_KEY        0x0017      // Hard key(All)
#define	OBJ_CODE_KEY       0x0018      // Hard Key(00h-7Fh)
#define	OBJ_CTRL_KEY       0x0019      // Hard Key(80h-FFh)
#define	OBJ_SYS_TESTKEY    0x001A      // TEST Key

#define	OBJ_NONE           0x0FFF      // NO EVENT

#define	OBJ_CMD_SCHE       0x3007      // SCHEDULE
#define	OBJ_CMD_EL         0x3008      // EL
#define	OBJ_CMD_ESC        0x3009      // ESC
#define	OBJ_CMD_MBAR       0x300A      // MENU BAR

// Action Codes  2001.8.6
//------------------------------------------------------------------------------------------
#define IMUL_ACT_MK		0x00000001	/* MaKe	    (PEN/KEY) */
#define IMUL_ACT_MV		0x00000002	/* MoVe	    (PEN    ) */
#define IMUL_ACT_MV_OUT	0x00000004	/* MoVe OUT (PEN    ) */
#define IMUL_ACT_MV_IN	0x00000008	/* MoVe IN  (PEN    ) */
#define IMUL_ACT_DW		0x00000010	/* DoWn	    (PEN    ) */
#define IMUL_ACT_DW_IN	0x00000020	/* DoWn IN  (PEN    ) */
#define IMUL_ACT_BK		0x00000040	/* BreaK    (PEN    ) */
#define IMUL_ACT_BK_IN	0x00000080	/* Break IN (PEN    ) */
#define IMUL_ACT_REP	0x00000100	/* REPeat   (PEN/KEY) */
#define IMUL_ACT_500M	0x00000200	/* 500Msec  (PEN/KEY) */
#define IMUL_ACT_ALM	0x00000400	/* ALarM    (PEN/KEY) */
#define IMUL_ACT_INPUT	0x80000000	/* INPUT    (PEN/KEY) */
#define IMUL_ACT_NONE	0x00000000	/* NONE	    (PEN/KEY) */
#define	IMUL_ACT_TMR	0x00000800	/* TiMeR    (PEN/KEY) */
#define	IMUL_ACT_1SEC	0x00001000	/* 1SEC     (PEN/KEY) */
#define	IMUL_ACT_APO	0x00002000	/* APO      (PEN/KEY) */
#define	IMUL_ACT_CMD	0x00010000	/* CMD      (PEN/KEY) */
#define IMUL_ACT_SYSWINCLS	0x00020000	/* SYStemWindowCLoSe */

//	Break Key Sample
//----------------------------------------------------------------------------------------
/* Registered Break factors */
#define	FG_BRK_BLD1			0x00000001	// BLD Detect
#define	FG_BRK_ESC			0x00000002	// ESC Touch
#define	FG_BRK_HDICESC		0x00000004	// Hardicon Esc touch
#define	FG_BRK_CRADLE		0x00000008	// Cladle key pushed
/* Generated Break factors */
#define	IM_BRK_NOEVT		0			// No Factor
#define	IM_BRK_BLD1			1			// BLD Message Level
#define	IM_BRK_ESC			2			// ESC Touch
#define	IM_BRK_HDICESC		3			// HardIcon ESC touch
#define	IM_BRK_CRADLE		4			// Cladle key pushed

//	EVENTSTS extended info defination    unsigned short ext;	/* for 500msec event */
//----------------------------------------------------------------------------------------
#define IM_EXT_NULL			0		// normal
#define IM_EXT_500M			1		// 500msec event

//	keycode
//----------------------------------------------------------------------------------------
/*----------------------------------------------------------------------------------------
	key code definations
----------------------------------------------------------------------------------------*/
#define IMU_KC_NULL 	0x00		// NULL
#define IMU_KC_TAB		0x09		// TAB
#define IMU_KC_EXP		0x1D		// Exp
#define IMU_KC_STORE 	0x1E		// ->
#define IMU_KC_PMINUS	0x1F		// (-)
#define IMU_KC_SPACE	0x20		// space
#define IMU_KC_EXCLAM 	0x21		// ! exclamation mark			2002.03.12
#define IMU_KC_SHARP 	0x22		// # sharp						2002.03.12
#define IMU_KC_DOLLAR 	0x23		// $ dollar						2002.03.12
#define IMU_KC_AND	 	0x24		// & and						2002.03.12
#define IMU_KC_LPAR 	0x28		// (  left paren
#define IMU_KC_RPAR		0x29		// ) right paren
#define IMU_KC_ASTRSK	0x2A		// * asterisk ×
#define IMU_KC_PLUS 	0x2B		// +
#define IMU_KC_COMMA	0x2C		// , 
#define IMU_KC_MINUS	0x2D		// -
#define IMU_KC_DP 		0x2E		// . DP
#define IMU_KC_SLASH	0x2F		// / ÷
#define IMU_KC_0		0x30		// 0
#define IMU_KC_1		0x31		// 1
#define IMU_KC_2		0x32		// 2
#define IMU_KC_3		0x33		// 3
#define IMU_KC_4		0x34		// 4
#define IMU_KC_5		0x35		// 5
#define IMU_KC_6		0x36		// 6
#define IMU_KC_7		0x37		// 7
#define IMU_KC_8		0x38		// 8
#define IMU_KC_9		0x39		// 9
#define IMU_KC_PERCENT 	0x3B		// % percent					2002.03.12
#define IMU_KC_ROOT	 	0x3C		//   root						2002.03.12
#define IMU_KC_EQ	 	0x3D		// = equal
#define IMU_KC_CALAC	0x3E		// AC							2002.03.12
#define IMU_KC_CALC 	0x3F		// C							2002.03.12
#define IMU_KC_ATMARK	0x40		// @ atmark						2002.03.12
#define IMU_KC_COLON 	0x41		// : colon						2002.03.12
#define IMU_KC_APOSTROP	0x42		// ' apostrophe					2002.03.12
#define IMU_KC_QUEST 	0x43		// ? question mark				2002.03.12
#define IMU_KC_UNDERSC 	0x44		// _ underscore					2002.03.12
#define IMU_KC_ACUTE 	0x50		// ACC1 acute              		2002.03.12
#define IMU_KC_GRAVE 	0x51		// ACC2 grave                	2002.03.12
#define IMU_KC_CIRC	 	0x52		// ACC3 circ                  	2002.03.12
#define IMU_KC_UML	 	0x53		// ACC4 uml                		2002.03.12
#define IMU_KC_TILDE 	0x54		// ACC5 tilde            		2002.03.12
#define IMU_KC_UPARW 	0x5E		// ^ upper arrow
#define IMU_KC_A	 	0x61		// a
#define IMU_KC_B	 	0x62		// b
#define IMU_KC_C	 	0x63		// c
#define IMU_KC_D	 	0x64		// d
#define IMU_KC_E	 	0x65		// e
#define IMU_KC_F	 	0x66		// f
#define IMU_KC_G	 	0x67		// g
#define IMU_KC_H	 	0x68		// h
#define IMU_KC_I		0x69		// i
#define IMU_KC_J	 	0x6A		// j
#define IMU_KC_K	 	0x6B		// k
#define IMU_KC_L	 	0x6C		// l
#define IMU_KC_M	 	0x6D		// m
#define IMU_KC_N	 	0x6E		// n
#define IMU_KC_O	 	0x6F		// o
#define IMU_KC_P	 	0x70		// p
#define IMU_KC_Q	 	0x71		// q
#define IMU_KC_R	 	0x72		// r
#define IMU_KC_S	 	0x73		// s
#define IMU_KC_T	 	0x74		// t
#define IMU_KC_U	 	0x75		// u
#define IMU_KC_V	 	0x76		// v
#define IMU_KC_W	 	0x77		// w
#define IMU_KC_X	 	0x78		// x
#define IMU_KC_Y		0x79		// y
#define IMU_KC_Z	 	0x7A		// z
#define IMU_KC_CEDIL 	0x7C		// cedil               			2002.03.12
#define IMU_KC_BETA	 	0x7D		// β							2002.03.12
#define IMU_KC_ON	 	0x80		// ON
#define IMU_KC_OFF 		0x81		// OFF
#define IMU_KC_EL	 	0x82		// EL
#define IMU_KC_F1	 	0x84		// F1
#define IMU_KC_F2	 	0x85		// F2
#define IMU_KC_F3	 	0x86		// F3
#define IMU_KC_F4	 	0x87		// F4
#define IMU_KC_F5	 	0x88		// F5
#define IMU_KC_F6		0x89		// F6
#define IMU_KC_F7	 	0x8A		// F7
#define IMU_KC_F8	 	0x8B		// F8
#define IMU_KC_F9	 	0x8C		// F9
#define IMU_KC_F10	 	0x8D		// F10
#define IMU_KC_F11	 	0x8E		// F11
#define IMU_KC_F12	 	0x8F		// F12
#define IMU_KC_UP	 	0x90		// UP
#define IMU_KC_DOWN 	0x91		// DOWN
#define IMU_KC_LEFT 	0x92		// LEFT
#define IMU_KC_RIGHT 	0x93		// RIGHT
#define IMU_KC_OK		0x94		// OK PUSH
#define IMU_KC_ESC		0x95		// escape
#define IMU_KC_DEL		0x96		// delete
#define IMU_KC_BS		0x97		// back space
#define IMU_KC_CLR		0x98		// clear
#define IMU_KC_RTN		0x99		// return
#define IMU_KC_EXE	 	0x9A		// EXE
#define IMU_KC_SHIFT 	0xA0		// shift
#define IMU_KC_CAPS 	0xA1		// caps
#define IMU_KC_SYMBOL	0xA2		// symbol
#define IMU_KC_ACC 		0xA3		// acc (code)
#define IMU_KC_COMMAND	0xA4		// command
#define IMU_KC_NUMLOCK	0xA5		// NumLock
#define IMU_KC_NEXT	 	0xA6		// Next
#define IMU_KC_AMPM	 	0xA7		// AM/PM						2002.03.12
#define IMU_KC_MENU 	0xB0		// menu
#define IMU_KC_TOOLS 	0xB1		// tools
#define IMU_KC_SECRET	0xB2		// secret
#define IMU_KC_KEY 		0xB3		// keyboad
#define IMU_KC_SCREEN	0xFC		// print screen
#define IMU_KC_SYNC 	0xFD		// sync
#define IMU_KC_TEST 	0xFE		// test
#define IMU_KC_NOP 		0xFF		// nop

/*----------------------------------------------------------------------------------------
	structures for applications
----------------------------------------------------------------------------------------*/
typedef struct key_kiko{
	unsigned char ki;
	unsigned char ko;
}KEY_KIKO;

typedef struct ad_value{		// @2001.10.17
	unsigned short adval_x;		/* A/D Value bit:000000**********			*/
	unsigned short adval_y;		/*  (LOW 10bit is valid. other bit always zero	*/
}AD_VALUE;

typedef struct pen_lcd {
    int	lcd_x;				/* X coordinate (LCD) */
    int	lcd_y;				/* Y coordinate (LCD) */
	AD_VALUE ad;			/* A/D value @2001.10.17 */
} PEN_LCD;

typedef struct key_dat {
    unsigned short kcode;	/* key code(command code) */
    unsigned short ccode;	/* character code */
} KEY_DAT;

// application launch struct
typedef struct application_launch {
    int mode;
    FONTCHARACTER *pathname;/* application path  */
    void *option;			/* application options */
    int optsize;			/* option size */
    void *result;			/* result buffer */
    int ressize;			/* result buffersize */
} APL_LAUNCH;

typedef struct application_hardicon {
    PEN_LCD pen;
} APL_HARDICON;

typedef struct application_command {
    union {
        APL_LAUNCH launch;
        APL_HARDICON hardicon;
    } dat;
} APL_CMD;

typedef struct tchtbl{
	int	x1;		//object area (X1)	
	int	y1;		//object area (Y1)
	int	x2;		//object area (X2)
	int	y2;		//object area (Y1)
	unsigned long	act;		//Action code
	unsigned short	obj;		//Object Code
	unsigned short	ext;		//extended information
}TCHTBL;

typedef struct eventsts {
    unsigned short	obj;		/* event object */
    unsigned long	act;		/* event action */
    union {
	PEN_LCD pen;					// Touch information
	KEY_DAT key;					// key information
	TIMESYS time;					// alarm information
	APL_CMD command;				// application control message
    } data;
    unsigned short ext;			/* event addition information */
    unsigned char istr[4];		/* for extended (NULL) */
	unsigned char pwon;			// power on information
} EVENTSTS;

/*----------------------------------------------------------------------------------------
	PROCCTRL.H
----------------------------------------------------------------------------------------*/

/*PROGRAM INFORMATION procctrl.h */
typedef struct _programinfo {
  unsigned short APPNAME[32];          // Application Name
  unsigned int LOCALE;       		   // Locale Info
  unsigned int APPVERSION;   		   // Program Version
  unsigned int STACK_SIZE;   		   // Stack Size
  unsigned int MIN_STACK_SIZE;   	   // Min. Stack Size
  unsigned int MAX_STACK_SIZE;   	   // Max. Stack Size
  unsigned int HEAP_SIZE;   		   // Heap Size
  unsigned int MIN_HEAP_SIZE;   	   // Min. Heap Size
  unsigned int MAX_HEAP_SIZE;   	   // Max. Heap Size
  unsigned char *icon;       		   // <dummy> (0)
} TPROGRAMINFO;

/*----------------------------------------------------------------------------------------
   DISPBIOS.H
----------------------------------------------------------------------------------------*/
#define	IM_FONTSTYLE_NORMAL	0		// PV:NORMAL
#define	IM_FONTSTYLE_BOLD	1		// PV:BOLD
#define	IM_FONTSTYLE_NO2	2		// PV:TITLE
#define	IM_FONTSTYLE_NO3	3		// PV:5*7Font

#define	IMB_WRITEKIND_OVER		0x01	//OVERWRITE
#define	IMB_WRITEKIND_OR		0x02	//OR
#define	IMB_WRITEKIND_AND		0x03	//AND
#define	IMB_WRITEKIND_XOR		0x04	//XOR

#define	IMB_AREAKIND_OVER		0x01	// OVERRITE
#define	IMB_AREAKIND_MESH		0x02	// MESH
#define	IMB_AREAKIND_CLR		0x03	// CLEAR
#define	IMB_AREAKIND_REVERSE	0x04	// REVERSE

// for Drawing Bios
#define		IMB_DOTSIZE_1	0x01
#define		IMB_DOTSIZE_2	0x02
#define		IMB_DOTSIZE_3	0x03

/*----------------------------------------------------------------------------------------
   SERIAL.H
----------------------------------------------------------------------------------------*/
typedef struct SRL_STAT {
	byte	port;			/* Port No.			*/
	byte	speed;			/* Bouadrate		*/
	byte	parit;			/* Parity bit		*/
	byte	datab;			/* DataBitLength	*/
	byte	stopb;			/* StopBitLength	*/
	byte	fctrl;			/* FlowControl		*/
} SRL_STAT;

/*Port property*/
#define	IMB_SRL_3PIN				0x00
#define	IMB_SRL_9PIN				0x01
/*Speed property*/
#define	IMB_SRL_300BPS				0x00
#define	IMB_SRL_600BPS				0x01
#define	IMB_SRL_1200BPS				0x02
#define	IMB_SRL_2400BPS				0x03
#define	IMB_SRL_4800BPS				0x04
#define	IMB_SRL_9600BPS				0x05
#define	IMB_SRL_19200BPS			0x06
#define	IMB_SRL_38400BPS			0x07
#define	IMB_SRL_57600BPS			0x08
#define	IMB_SRL_115200BPS			0x09
/*Parity bit property*/
#define	IMB_SRL_NONE				0x00
#define	IMB_SRL_ODD					0x01
#define	IMB_SRL_EVEN				0x02
/*Char length property*/
#define	IMB_SRL_7DATA				0x01
#define	IMB_SRL_8DATA				0x00
/*Stop bit property*/
#define	IMB_SRL_1STOP				0x00
#define	IMB_SRL_2STOP				0x01
/*Flow control property*/
#define	IMB_SRL_NOFLOW				0x00
#define	IMB_SRL_RSCS				0x01
#define	IMB_SRL_XONOFF				0x02
#define	IMB_SRL_BOTHFLOW			(IMB_SRL_RSCS|IMB_SRL_XONOFF)
/*-----------------------------------------------------------------*/
/*SIGNAL STATUS                                                    */
/*-----------------------------------------------------------------*/
#define	FG_SRL_RS					0x0001
#define	FG_SRL_ER					0x0002
#define	FG_SRL_CD					0x0004
#define	FG_SRL_CS					0x0008
#define	FG_SRL_DR					0x0010
/*-----------------------------------------------------------------*/
/*FOR SIGNAL CONTROL                                               */
/*-----------------------------------------------------------------*/
#define	FG_SRL_ER_ON				0x0100
#define	FG_SRL_ER_OFF				0x0200
#define	FG_SRL_RS_ON				0x0400
#define	FG_SRL_RS_OFF				0x0800
/*-----------------------------------------------------------------*/
/*SERIAL ERRORS                                                    */
/*-----------------------------------------------------------------*/
#define	IMW_SRL_NOERR		0x0000
#define	IMW_SRL_NODATA		0x0001
#define	IMW_SRL_TXERR		0x0002
#define	IMW_SRL_NOOPEN		0x0003
#define	IMW_SRL_PRMERR		0x0004
#define	IMW_SRL_CLSERR		0x0005
#define	IMW_SRL_RXERR		0x0006
#define	IMW_SRL_TOUT		0x0007
#define	IMW_SRL_OPEN		0x0008
/*-----------------------------------------------------------------*/
/*PORT STATUS                                                      */
/*-----------------------------------------------------------------*/
#define	IMB_SRL_3PIN_OPEN	0x01
#define	IMB_SRL_9PIN_OPEN	0x10
/*-----------------------------------------------------------------*/
/*COMMUNICATION STATUS                                             */
/*-----------------------------------------------------------------*/
#define	FG_SRL_RX_OVER		0x0001
#define	FG_SRL_PER			0x0002
#define	FG_SRL_FER			0x0004
#define	FG_SRL_BREAK		0x0008
#define	FG_SRL_DCE_BUSY		0x0010
#define	FG_SRL_DTE_BUSY		0x0020
#define	FG_SRL_OVER_RUN		0x0040
#define	FG_SRL_3PIN			0x1000
#define	FG_SRL_9PIN			0x2000
/*-----------------------------------------------------------------*/
/*SERIAL EVENTS                                                    */
/*-----------------------------------------------------------------*/
#define	FG_SRL_EV_BRK		0x00000001
#define	FG_SRL_EV_ERR		0x00000002
#define	FG_SRL_EV_RX		0x00000004
#define	FG_SRL_EV_TX		0x00000008
/*-----------------------------------------------------------------*/
/*PORT CLOSE TYPE                                                  */
/*-----------------------------------------------------------------*/
#define	IMW_SRL_NORMAL		0x0000
#define	IMW_SRL_FORCED		0x0001

/*----------------------------------------------------------------------------
   COMMDRIVER.H
-----------------------------------------------------------------------------*/

/* COMMUNICATION API ERROR MESSAGE*/
#define	IMW_COMM_NOERR		0x0000
#define	IMW_COMM_NODATA		0x0001
#define	IMW_COMM_TXERR		0x0002
#define	IMW_COMM_NOOPEN		0x0003
#define	IMW_COMM_PRMERR		0x0004
#define	IMW_COMM_CLSERR		0x0005
#define	IMW_COMM_RXERR		0x0006
#define	IMW_COMM_TOUT		0x0007
#define	IMW_COMM_OPEN		0x0008

/* COMMUNICATION API FUNCTION PROPERTY */
#define	IMB_COMM_300BPS		0x00
#define	IMB_COMM_600BPS		0x01
#define	IMB_COMM_1200BPS	0x02
#define	IMB_COMM_2400BPS	0x03
#define	IMB_COMM_4800BPS	0x04
#define	IMB_COMM_9600BPS	0x05
#define	IMB_COMM_19200BPS	0x06
#define	IMB_COMM_38400BPS	0x07
#define	IMB_COMM_57600BPS	0x08
#define	IMB_COMM_115200BPS	0x09
/*Parity bit property*/
#define	IMB_COMM_NONE				0x00
#define	IMB_COMM_ODD				0x01
#define	IMB_COMM_EVEN				0x02
/*Char length property*/
#define	IMB_COMM_7DATA				0x01
#define	IMB_COMM_8DATA				0x00
/*Stop bit property*/
#define	IMB_COMM_1STOP				0x00
#define	IMB_COMM_2STOP				0x01
/*Flow control property*/
#define	IMB_COMM_NOFLOW				0x00
#define	IMB_COMM_RSCS				0x01
#define	IMB_COMM_XONOFF				0x02
#define	IMB_COMM_BOTHFLOW			(IMB_COMM_RSCS|IMB_COMM_XONOFF)
/*Close type*/
#define	IMW_COMM_NORMAL		0x0000
#define	IMW_COMM_FORCED		0x0001
/*Signal flag*/
#define	FG_COMM_RS			0x0001
#define	FG_COMM_ER			0x0002
#define	FG_COMM_CD			0x0004
#define	FG_COMM_CS			0x0008
#define	FG_COMM_DR			0x0010
/*Communication status*/
#define	FG_COMM_OV			0x0001
#define	FG_COMM_PE			0x0002
#define	FG_COMM_FE			0x0004
#define	FG_COMM_BK			0x0008
#define	FG_COMM_CB			0x0010
#define	FG_COMM_TB			0x0020
#define	FG_COMM_OVR			0x0040
#define	FG_COMM_USBERR		0x0080
#define	FG_COMM_SRL3PIN		0x1000
#define	FG_COMM_SRL9PIN		0x2000
#define	FG_COMM_USB			0x4000
#define	FG_COMM_SRL9PINOP	0x8000
/*Contorl signal flag*/
#define	FG_COMM_ER_ON		0x0100
#define	FG_COMM_ER_OFF		0x0200
#define	FG_COMM_RS_ON		0x0400
#define	FG_COMM_RS_OFF		0x0800
/*Event flag*/
#define	FG_COMM_EV_BRK		0x00000001
#define	FG_COMM_EV_ERR		0x00000002
#define	FG_COMM_EV_RX		0x00000004
#define	FG_COMM_EV_TX		0x00000008

#endif

//　NULL code
#undef NULL
#define NULL			0x0000		//NULL
                              
#define WDOT			1			// light
#define CDOT			1			// no light

/********************************************
 *	 definations for old PV Compatilbility  *
 ********************************************/
/* Language */
#define IB_DEUTSCH		0x00
#define IB_ENGLISH		0x01
#define IB_ESPANOL		0x02
#define IB_FRANCAIS		0x03
#define IB_ITALIANO		0x04
#define IB_LANG_ENGLISH	0x01

/* Proportional font */
#define IB_PFONT1		IM_FONTSTYLE_NORMAL		/* Proportional NORMAL		*/
#define IB_PFONT2		IM_FONTSTYLE_BOLD		/* Proportional BOLD		*/
#define IB_PFONT3		IM_FONTSTYLE_NO2		/* Proportional for TITLE	*/
#define IB_CG57FONT		IM_FONTSTYLE_NO3		/* Fixed Pitch 5*7			*/

/* Touch action code */
#define ACT_MAKE		IMUL_ACT_MK				/* MaKe	    (PEN/KEY) */
#define ACT_MOVE		IMUL_ACT_MV				/* MoVe	    (PEN    ) */
#define ACT_MOVE_OUT	IMUL_ACT_MV_OUT			/* MoVe OUT (PEN    ) */
#define ACT_MOVE_IN		IMUL_ACT_MV_IN			/* MoVe IN  (PEN    ) */
#define ACT_DOWN		IMUL_ACT_DW				/* DoWn	    (PEN    ) */
#define ACT_DOWN_IN		IMUL_ACT_DW_IN			/* DoWn IN  (PEN    ) */
#define ACT_BREAK		IMUL_ACT_BK				/* BreaK    (PEN    ) */
#define ACT_BREAK_IN	IMUL_ACT_BK_IN			/* Break IN (PEN    ) */
#define ACT_REPEAT		IMUL_ACT_REP			/* REPeat   (PEN/KEY) */
#define ACT_500MSEC		IMUL_ACT_500M			/* 500Msec  (PEN/KEY) */
#define ACT_ALM			IMUL_ACT_ALM			/* ALarM    (PEN/KEY) */
#define ACT_NONE		IMUL_ACT_NONE			/* NONE	    (PEN/KEY) */

#define ACT_ICON		(ACT_MAKE | ACT_MOVE_IN |ACT_MOVE_OUT | ACT_BREAK_IN)
#define ACT_SCR_BAR		(ACT_MAKE | ACT_MOVE_IN | ACT_MOVE_OUT | ACT_DOWN_IN | ACT_BREAK_IN)
#define ACT_TXTAREA		(ACT_MAKE|ACT_MOVE_OUT|ACT_BREAK|ACT_DOWN_IN|ACT_DOWN)

/* Touch reserve object code(for hardicon)  */
#define OBJ_HIC_MBAR	OBJ_CMD_MBAR  			/* MenuBar */
#define OBJ_HIC_ESC 	OBJ_CMD_ESC				/* ESC     */
#define OBJ_HIC_SCD		OBJ_CMD_SCHE			/* Schdule */
#define OBJ_HIC_EL	 	OBJ_CMD_EL				/* EL      */

/* Touch reserve obejct code (SYSTEM) */
#define OBJ_500MSEC		OBJ_SYS_500MSEC			/* Over500msec              */

/* Touch reserve object code (for mode icon) */
#define OBJ_MD_ICON		0x8900

/* all displayarea Object code */
#define OBJ_ALLTCH		0x9fff					/* all touch area  */

/* CalculatorKeyboardRelationObjectCode */
#define OBJ_CAL_NEXT	0xc947					/* [NEXT] Key   */
#define OBJ_CAL_EQUAL	0xc948					/* [=] Key      */

/* CalenderKeyboardRelationObjectCode */
#define OBJ_CALE_NEXT	IM_OBJ_CALE_NEXT		/* [NEXT] Key   */

/* TouchObjectCode(GeneralCharacterInputting/for data display) */
#define OBJ_TXTTCH		IML_OBJ_TXTTCH
#define OBJ_SCR_BAR		IML_OBJ_SCR_BAR

/* extended code */
#define EXT_CODE_500MS	0x0001

/* FACTOR */
#define IX_BLD1MSG		FG_BRK_BLD1
#define IX_CRADLE		FG_BRK_CRADLE
#define IX_ESCBRK		FG_BRK_ESC

/* City list count */
#define	CITYLIST_NUM		219

/* GDS BIOS Software Keybord Embellishment */
#define IB_GDS_KREVP1	1					/* PATTERN1 Normal      */
#define IB_GDS_KREVP2	2					/* PATTERN2 Right shadow*/
#define IB_GDS_KREVP3	3					/* PATTERN3 around right shadow */
#define IB_GDS_KREVP4	4					/* PATTERN4 around      */

/* GDS BIOS Software Keybord Embellishment */
#define IB_GDS_KEYREV	0						/* REVERSE        */
#define IB_GDS_KEYREVR	1						/* REVERSE Return */

/* GDS BIOS Window Message :Button Type */
#define IB_MWIN_NONE	0x00					/* NONE                 */
#define IB_MWIN_YES_NO	0x01					/* YES/NO  (2 Button)   */
#define IB_MWIN_SET_ESC	0x02					/* SET/ESC (2 Button)   */
#define IB_MWIN_OK		0x03					/* OK  (1 Button)       */
#define IB_MWIN_SET		0x04					/* SET (1 Button)       */
#define IB_MWIN_ESC		0x05					/* ESC (1 Button)       */
#define IX_MWIN_CENTER	0x80					/* CENTER               */
#define IB_MWIN_NO_ICON	0xFF					/* NO ICON              */ 

#define IX_DAYLY_ALM	0x01					/* DAY ALARM      */
#define IX_DATA_ALM		0x02					/* SCHEDULE       */
#define IX_KEY_SOUND	0x80					/* KEY TONE       */

/* KEYWORD REGISTRATION OPTION */
#define IB_KEYWD_FSRCH	0x00					/* FIRST SEARCH   */
#define IB_KEYWD_NSRCH	0x01					/* NEXT SEARCH    */

/* message window icon classification */
#define ICON_NONE		0   			 		/* none          */
#define ICON_OK			1   			 		/* OK            */
#define ICON_BADTZ		2    					/* X             */
#define ICON_BIKKURI	3    					/* !             */
#define ICON_COFFEE		4    					/* Coffee cup    */
#define ICON_TRASH		5    					/* Trash box     */
#define ICON_SIGN		6    					/* Hand          */
#define ICON_SYNC		7    					/* communicating */

/* KeyBoardRequest */
#define SKEY_COM1_S		0x0000					/* NormalKeyBoard(SmallCharacterBorad)      */
#define SKEY_COM2_S		0x0001					/* NormalKeyBoard(SmallCharacterBoard with SHIFT)*/
#define SKEY_COM1_L		0x0002					/* NormalKeyBoard(LargeCharacterBoard)        */
#define SKEY_COM2_L		0x0003					/* NormalKeyBoard(LargeCharacterBoard with SHIFT)  */
#define SKEY_COM3_L		0x0012					/* NormalKeyBoard(LargeCharacterBoard at ItemTop)  */
#define SKEY_CODE		0x0004					/* NormalKeyBoard(AccentSymbolBoard)        */
#define SKEY_SMBL		0x0005					/* NormalKeyBoard(SymbolBoard)              */

/* Keycode */
#define KEY_RTN			0xf0					/* Return     */
#define KEY_DEL			0xf1					/* Del        */
#define KEY_SHIFT		0xf2					/* ↑         */
#define KEY_CAPS		0xf3					/* Caps       */
#define KEY_SPC			0xf4					/* Space      */
#define KEY_SMBL		0xf5					/* Symbol     */
#define KEY_CODE		0xf6					/* Accent     */
#define KEY_NEXT		0xf7					/* Next       */
#define KEY_BACK		0xf8					/* Back       */
#define KEY_ALLCODE		0xf9					/* All Code   */
#define KEY_CHANGE		0xfa					/* SynbolChange */
#define KEY_NOP			0xfe					/* CalenderNOP */
#define KEY_NONE		0xff					/* OtheTouchArea */

/* ScrollBarSizeInformation */
#define SCR_XSIZE		9						/* X dot size       */
#define ARW_SIZE		5						/* Arrow size       */
#define ARW_AREA		7						/* Arrow area size  */

/* ScrollBarArrowHatchingInformation */
#define SCR_NO_MASK		0x00					/* Arrow No hatching */
#define SCR_UP_MASK		0x01					/* UpArrow hatching     */
#define SCR_DWN_MASK	0x02					/* DownArrow hatching   */
#define SCR_ALL_MASK	(SCR_UP_MASK | SCR_DWN_MASK)

/* LibDateDisp() input condition */
#define IN_MODE			0					/* for input    */
#define DISP_MODE		1					/* for display  */
#define DISP_YM			2					/* year / month */
#define DISP_MY			3					/* month / year */
#define DISP_MYS		5					/* month / year (2 digits below) */
#define IN_YM			4					/* input year and month */

#define WEEK_ON			1					/* day of the week ON  */
#define WEEK_OFF		0					/* day of the week OFF */

/* GeneralCharacterInput/DataDisplay */
#define		TXTNOP		0x00		/* NOP                               */
#define		TXTCUT		0x0B		/* CUT                               */
#define		TXTCOPY		0x0C		/* COPY                              */
#define		TXTPASTE	0x0D		/* PASTE                             */
#define		TXTDYTIM	0x0F		/* Paste of date&time                */
#define		TXTMJKEY	0x01
#define		TXTCSMV		0x02
#define		TXTCSUP		0x03
#define		TXTCSDWN	0x04
#define		TXTBS		0x05
#define		TXTDEL		0x06
#define		TXTDRG		0x07
#define		TXTDGDN		0x08
#define		TXTDGUP		0x09
#define		TXTSBAR		0x0A
#define		TXTREDSP	0x0E

/*== ipdpst(InputStatusFlag) ==*/
#define		NOCHG		0x00		/* It is not in the re-display.      */
#define		CSRMOV		0x10		/* The re-display only about the cursor. */
#define		CSRPOS		0x20		/* It rewrites a letter on the cursor.   */
#define		UPSCRL		0x30		/* Up scroll                         */
#define		DNSCRL		0x40		/* Down scroll                       */
#define		CSRAFT		0x50		/* It rewrites since the cursor.     */
#define		CSRAFT2		0x60		/* It rewrites since the cursor.(The cursor position fixation) */
#define		UPSCWRT		0x70		/* Up scrolled above,it rewrites since the cursor. */
#define		PRECSL		0x80		/* It rewrites since the line in front of the cursor. */
#define		ALLTXT		0x90		/* It rewrites all texts.            */
#define		ALLTXT2		0xA0		/* It rewrites all texts.(with the cursor revision) */
#define		fntx_min	2			/* The minimum font width            */

/* PullDown (index attribute specification) */
#define PULLDOWN_NONDSP			0x01	/* makes a non-display */
#define PULLDOWN_HTNDSP			0x02	/* makes a hatching display  */
#define	PDNTBLEND				0xFFFF	/* PullDown Table END code */

/* PullDown (index item specification) */
#define PULLDOWN_EDIT  			0x8000	/* [Edit]            */
#define PULLDOWN_SYSTEM			0x4000	/* [System]          */
#define PULLDOWN_OPTION			0x2000	/* [Option]          */
#define PULLDOWN_RESERV			0x1000	/* [Reserve]         */
#define PULLDOWN_IDX_MASK		0xF000	/* index item mask   */

/* WAIT BIOS */
#define IB_125MWAIT			5						/* 125mSec      */
#define IB_250MWAIT			10						/* 250mSec      */
#define IB_500MWAIT			20						/* 500mSec      */
#define IB_1SWAIT			40						/* 1Sec	        */

/* BlockTypeIconFunctoin Arguments */
#define B_ICON_LEFT			1
#define B_ICON_CENTER		0
#define B_ICON_RIGHT		2

/* Calculator size information */
#define CAL_EZSIZE			11						/* Maximum figure   */
#define CAL_BUFSIZE			14						/* buffer size for the calculation value */
#define CAL_MBUFSIZE		14						/* buffer size for the memory calculation value */
#define CAL_SISUUKIJUN		100						/* index standard value */

/* SerialCommunicationLibrary */
/* PortNo.	*/
#define IB_SRL_COM1			0x00					/* COM1( 3PIN RS-232C)		*/
#define IB_SRL_COM2			0x01					/* COM2( 9PIN RS-232C)		*/
#define IB_SRL_COM3			0x02					/* COM3( USB ) 				*/

/* CommunicationPortInitial */
#define IB_SRL_300BPS			IMB_COMM_300BPS		/* 300bps		*/
#define IB_SRL_600BPS			IMB_COMM_600BPS		/* 600bps		*/
#define IB_SRL_1200BPS			IMB_COMM_1200BPS	/* 1200bps		*/
#define IB_SRL_2400BPS			IMB_COMM_2400BPS	/* 2400bps		*/
#define IB_SRL_4800BPS			IMB_COMM_4800BPS	/* 4800bps		*/
#define IB_SRL_9600BPS			IMB_COMM_9600BPS	/* 9600bps		*/
#define IB_SRL_19200BPS			IMB_COMM_19200BPS	/* 19200bps		*/
#define IB_SRL_38400BPS			IMB_COMM_38400BPS	/* 38400bps		*/
#define IB_SRL_57600BPS			IMB_COMM_57600BPS	/* 57600bps		*/
#define IB_SRL_115200BPS		IMB_COMM_115200BPS	/* 115200bps	*/

#define IX_SRL_NOFLOW			IMB_COMM_NOFLOW		/* 00000000 ;Not flow control		*/
#define IX_SRL_RSCS				IMB_COMM_RSCS		/* 00000010 ;RS/CS flow control		*/
#define IX_SRL_XONOFF			IMB_COMM_XONOFF		/* 00000011 ;XON/XOFF+RS/CS flow control */
#define IX_SRL_XONOFFONLY		IMB_COMM_BOTHFLOW	/* 00000001 ;XON/XOFF flow control	*/

#define IX_SRL_7DATA			IMB_COMM_7DATA		/* 00001000 ;data 7 bit	*/
#define IX_SRL_8DATA			IMB_COMM_8DATA		/* 00001100 ;data 8 bit	*/

#define IX_SRL_NONE				IMB_COMM_NONE		/* 00000000 ;None parity	*/
#define IX_SRL_ODD				IMB_COMM_ODD		/* 00010000 ;Odd parity		*/
#define IX_SRL_EVEN				IMB_COMM_EVEN		/* 00110000 ;Even parity	*/

#define IX_SRL_1STOP			IMB_COMM_1STOP		/* 01000000 ;stop 1bit	*/
#define IX_SRL_2STOP			IMB_COMM_2STOP		/* 11000000 ;stop 2bit	*/

/* ErrorCode */
#define IW_SRL_NOERR			IMW_COMM_NOERR		/* No error				*/
#define IW_SRL_PRMERR			IMW_COMM_PRMERR		/* Input parameter error	*/
#define IW_SRL_TRSERR			IMW_COMM_TXERR		/* Can not data sendind	*/
#define IW_SRL_NODATA			IMW_COMM_NODATA		/* No receive data		*/
#define IW_SRL_RCVERR			IMW_COMM_RXERR		/* Receive status error	*/
#define IW_SRL_CLSERR			IMW_COMM_CLSERR		/* Can not close		*/
#define IW_SRL_TMOERR			IMW_COMM_TOUT		/* time out error		*/
#define IW_SRL_NOOPEN			IMW_COMM_NOOPEN		/* Not Open error		*/
#define IW_SRL_NODEVOPEN		0x1000				/* Not Device Open		*/
#define IW_SRL_CNCTERR			0x1001				/* Conect error			*/
#define IW_SRL_OVFERR			0x1002				/* Receive buffer over flow	*/
#define IW_SRL_RCHGERR			0x1003				/* Can not change baudrate	*/
//#define	IW_SRL_FUNCERR		0xFFFF	/* */
              
/* SerialSignalLineStatus */
#define IX_SRL_ER				0x01					/*	00000001	*/
#define IX_SRL_RS				0x02					/*	00000010	*/
#define IX_SRL_CS				0x20					/*	00100000	*/
#define IX_SRL_CD				0x40					/*	01000000	*/
#define IX_SRL_DR				0x80					/*	10000000	*/
               
#define IX_SRL_FE				FG_COMM_FE			/* 0x0004 ;flaming error		*/
#define IX_SRL_PE				FG_COMM_PE			/* 0x0002 ;parity error		*/
#define IX_SRL_OE				FG_COMM_OVR			/* 0x0040 ;over run error	*/
#define IX_SRL_CB				FG_COMM_CB			/* 0x0010 ;DCE busy			*/
#define IX_SRL_TB				FG_COMM_TB			/* 0x0020 ;DTE busy			*/
#define IX_SRL_OV				FG_COMM_OV			/* 0x0001 ;receive buffer over flow error*/
#define IX_SRL_USBERR			FG_COMM_USBERR		/* 0x0080 ;USB communication error */
#define IX_SRL_RXRDY			FG_COMM_EV_RX		/* 0x00000004 ;receive data ready	*/
#define IX_SRL_TXEMP			FG_COMM_EV_TX		/* 0x00000008 ;sending register empty*/

#define IB_FOLLOW_BUSY			0x00				/* follows a flow control	*/
#define IB_IGNORE_BUSY			0x01				/* ignores a flow control   */
                                        	
/* Open Status */
#define IB_NO_OPEN				0x00				/* NOT OPEN PORT	*/
#define IB_COM1_OPEN			0x01				/* 3PIN PORT OPEN	*/
#define IB_COM2_OPEN			0x41				/* 9PIN PORT OPEN	*/
#define IB_COM3_OPEN			0x81				/* USB PORT OPEN	*/

/* TimeSettingKeyboard RetuenValue(Upper8bit) */
#define CLKKEYB_RSLT_NONE		0				/* NO EVENT                            */
#define CLKKEYB_RSLT_NEXTITEM	0x0f				/* After setting in the minute         */
#define CLKKEYB_RSLT_PREVITEM	0x0e				/* It pushed the left key when the cursor was in 0. */
#define CLKKEYB_RSLT_OUTOFKEYB	0x0d				/* Invalid area                        */
#define CLKKEYB_RSLT_KEYBSWAP	0x0c				/* It is a touch in the time bar switching button. */
#define CLKKEYB_RSLT_DISPGUIDE	0x0b				/* It became a guidance display condition. */

/***** Backup Buffer *****/
#define IM_MAX_BUF_CONTACTS		184
#define IM_MAX_BUF_MEMO     	15	
#define IM_NOTITLE_NUM 	 		5
#define IM_NOTITLE_NUM_NAME		13

/* Drawing BIOS DrawMode */
#define DRW_REPLACE				IMB_WRITEKIND_OVER
#define DRW_AND					IMB_WRITEKIND_AND
#define DRW_OR					IMB_WRITEKIND_OR
#define DRW_XOR					IMB_WRITEKIND_XOR                  

/* GDS BIOS Pattern */
#define IB_GPOVER   			IMB_WRITEKIND_OVER		/* OVER Write           */
#define IB_GPOR     			IMB_WRITEKIND_OR		/* OR Write             */
#define IB_GPAND    			IMB_WRITEKIND_AND		/* AND Write            */
//#define IB_GPREV    			IMB_WRITEKIND_REVERSE	/* REVERSE Write (deleted)  */
//#define IB_GPMESH   			IMB_WRITEKIND_MESH		/* MESH Write    (deleted)  */

/* GDS BIOS Transfer Type l_define */
#define IB_GDS_OVER				IMB_AREAKIND_OVER		/* OVER                 */
#define IB_GDS_OR				IMB_WRITEKIND_OR		/* OR                   */
#define IB_GDS_AND				IMB_WRITEKIND_AND		/* AND                  */
#define IB_GDS_REV				IMB_AREAKIND_REVERSE	/* REVERSE              */
#define IB_GDS_MESH				IMB_AREAKIND_MESH		/* MESH                 */
#define IB_GDS_XOR				IMB_WRITEKIND_XOR		/* XOR                  */

/* TOUCH PANEL ALIGNMENT */
#define IB_ERR_END				0xFF						/* OUTPUT: ERROR END */
#define IB_NOERR_END			0x00						/* OUTPUT:NO ERROR END      */
#define IB_ESC_END				0x01						/* OUTPUT:ESC END OR OFF KEY	*/
#define IB_PON_END				0x03						/* OUTPUT:POWER ON              */

/* for Quick Memo Library */
#define QME_PEN_TIN				IMB_DOTSIZE_1
#define QME_PEN_STD				IMB_DOTSIZE_2
#define QME_PEN_FAT				IMB_DOTSIZE_3

/* Flash Memory Access Library Definations */
#define FILE_KIND_BIN			IMB_FILE_KIND_BIN			/* Binary File */
#define FILE_KIND_TEXT 			IMB_FILE_KIND_TEXT			/* Text File */
#define FILE_OPEN_MODE 			IMB_FILE_SECRET_MODE		/* open mode */
#define FILE_SECRET_MODE 		IMB_FILE_SECRET_MODE		/* secret mode */
#define FILE_BLOCK_SIZE 		IML_FILE_BLOCK_SIZE			/* 1block size */

/* FlashDataBuffer */
#define ITEM_TOP				IMB_ITEM_TOP
#define TEXT_END				IMB_TEXT_END

/* FlashErrorCode */
#define IW_NORMALCY				IML_NORMALCY			/* No problem          			              */
#define IW_NUL_BUFF				IML_NUL_BUFF			/* No data to register. 					  */
#define IW_WRITE_ERR			IML_WRITE_ERR			/* x（used inside）                           */
#define IW_FORMAT_ERR			IML_FORMAT_ERR			/* Fatal error                                */
#define IW_MAX_CHAR_ERR			IML_MAX_CHAR_ERR		/* The number of characters to be registered exceed the limit. */
#define IW_TME_DATE_ERR			IML_TME_DATE_ERR		/* The data other than numeric number exists. (Date/Time) */
#define IW_OUT_PNTA_ERR			IML_OUT_PNTA_ERR		/* The setting pointer has an illegal value (out of range). */
#define IW_TWIN_DAT_ERR			IML_TWIN_DAT_ERR		/* The setting pointer has an illegal value (out of range). */
														/* there is no 4-byte data to be paired.	*/
#define IW_MEMORY_OVER			IML_MEMORY_OVER			/* Unable to register because of the insufficient memory capacity. */
/**/
#define IML_RECORD_MAX_ERR		IW_MEMORY_OVER			/* too many number of records(see above.)	*/
/**/

#define IW_ARM_TOTL_ERR			IML_ARM_TOTL_ERR		/* The number of registered alarms exceed the maximum. */
#define IW_ARM_SAMV_ERR			IML_ARM_SAMV_ERR		/* The same alarm value already exists. */
#define IW_ARM_NULL_ERR			IML_ARM_NULL_ERR		/* The same alarm value already exists. */
#define IW_CRADLE_ERR			IML_CRADLE_ERR			/* The cradle ID of the write destination is not FFFFh. */
#define IW_PARAMET_ERR			IML_PARAMET_ERR			/* Illegal value is set: Debug purpose only.  */
#define IW_NO_DATA_ERR			IML_NO_DATA_ERR			/* No data exists for search. */
#define IW_ARM_OLDV_ERR			IML_ARM_OLDV_ERR		/* Alarm is the past date. */
#define IW_SCRT_ACS_ERR			IML_SCRT_ACS_ERR		/* Access a SecretData in OpenMode */
#define IW_ENUM_RATEEND			IML_ENUM_RATEEND		/* End of enumrating files	*/
#define IW_DEVICECHANGED_ERR	IML_DEVICECHANGED_ERR	/* Changed device state */
#define IW_RECORD_NOTFOUND_ERR	IML_RECORD_NOTFOUND_ERR	/* Selected record not found */
#define IW_NOT_ALMZSUPPORT_ERR	IML_NOT_ALMZSUPPORT_ERR	/* Not alarm support file */
#define IW_ALMFILE_REGIST_ERR	IML_ALMFILE_REGIST_ERR	/* Cannot register alarm file format */
#define IW_ESCKEY_BREAK			IML_ESCKEY_BREAK		/* Break by BREAK-KEY */
#define IW_SEARCH_NEARDATA		IML_SEARCH_NEARDATA		/* Search with near data	*/
#define IW_INTERNAL_ERR			IML_INTERNAL_ERR		/* internal error (font conversion)	*/
#define IW_RECORD_MAX_ERR		IML_RECORD_MAX_ERR		/* over record count in a single mode */

/* Menu Information */
#define	IML_MJMP_INFO_MAX		90			/* Menu link information maximum count */

/* MAIN MODE CODE */
#define IB_MSYS					0x00			/* SYSTEM           */
#define IB_MTEL					0x01			/* TELEPHONE        */
#define IB_MMEMO				0x02			/* MEMO             */
#define IB_MSCHD				0x03			/* SCHEDULE         */
#define IB_MCLOCK				0x04			/* CLOCK            */
#define IB_MESHEET				0x06			/* SPREADSHEET      */
#define IB_MCOM					0x07			/* COMMUNICATION    */
#define IB_MADDIN				0x08			/* ADDIN            */
#define IB_MQFORM				0x09			/* QUICK FORM       */
#define IB_MGAME				0x0A			/* GAME             */
#define IB_MMAIL				0x0B			/* DICTIONARY		*/
#define IB_MEXPEN				0x0C			/* EXPENSE          */
#define IB_MCONV				0x0D			/* Conversion       */
#define IB_MMENUMD				0x0E			/* MENU             */
#define IB_MSECRET				0x80			/* <SECRET ON>      */

#define IW_MSYS					0x0000		/* SYSTEM           */
#define IW_MTEL					0x0100		/* TELEPHONE        */
#define IW_MMEMO				0x0200		/* MEMO             */
#define IW_MSCHD				0x0300		/* SCHEDULE         */
#define IW_MCLOCK				0x0400		/* CLOCK            */
#define IW_MESHEET				0x0600		/* SPREADSHEET      */
#define IW_MCOM					0x0700		/* COMMUNICATION    */
#define IW_MADDIN				0x0800		/* ADDIN            */
#define IW_MQFORM				0x0900		/* QUICK FORM       */
#define IW_MGAME				0x0A00		/* GAME             */
#define IW_MMAIL				0x0B00		/* DICTIONARY		*/
#define IW_MEXPEN				0x0C00		/* EXPENSE          */
#define IW_MCONV				0x0D00		/* TOOL             */
#define IW_MMENUMD				0x0E00		/* MENU             */
#define IW_MSECRET				0x8000		/* <SECRET ON>      */

/* SUB MODE CODE */
/* SYSTEM */
#define IB_SMNORMAL				0x00		/* NORMAL			*/
#define IB_SMTEST				0x01		/* TEST PROGRAM		*/
#define IB_SMSERVICE			0x02		/* SERVICE TRANSFER	*/

#define IB_SMLIBINT				0x80		/* C LibINT	 */
#define IB_SMFUNCINT			0x81		/* C FuncINT */
#define IB_SMSYSDAT1			0x90		/* SystemData1(Message&Font)	*/
#define IB_SMSYSDAT2			0xB0		/* SystemData2(Graphic)		*/

// System（新規）
#define IB_SMSYSALMDRV			(IB_SMLIBINT+2)		/* Alarm Driver */
#define IB_SMSYSFONT_00			(IB_SMSYSDAT1)		/* FONT00	*/
#define IB_SMSYSFONT_01			(IB_SMSYSDAT1+1)	/* FONT01	*/
#define IB_SMSYSFONT_02			(IB_SMSYSDAT1+2)	/* FONT02	*/
#define IB_SMSYSFONT_03			(IB_SMSYSDAT1+3)	/* FONT5*7	*/

#define IB_SMSYSMESS_DT			(IB_SMSYSDAT1+16)	/*　DEU */
#define IB_SMSYSMESS_EN			(IB_SMSYSDAT1+17)	/*　ENU */
#define IB_SMSYSMESS_ES			(IB_SMSYSDAT1+18)	/*　ESN */
#define IB_SMSYSMESS_FR			(IB_SMSYSDAT1+19)	/*　FRA */
#define IB_SMSYSMESS_IT			(IB_SMSYSDAT1+20)	/*　ITA */

#define IB_SMALL				0x00			/* COMMON			*/
/* TELEPHONE */
#define IB_SMTELPAR				0x01			/* PERSONAL         */
#define IB_SMTELBIS				0x02			/* BUSINESS         */
#define IB_SMTELETC				0x04			/* ETC	            */
/* SCHEDULE */
#define IB_SMSCHD				0x01			/* SCHEDULE         */
#define IB_SMSCHDK				0x02			/* TERM             */
#define IB_SMTODO				0x03			/* TODO             */
#define IB_SMREMI				0x04			/* REMINDER         */
#define IB_SMCALE				0x05			/* CALENDER         */
#define IB_SMSCHD_DAY			0x06			/* DAY              */
#define IB_SMSCHD_WEEK			0x07			/* WEEK             */
#define IB_SMSCHD_MONTH			0x08			/* MONTH            */
#define IB_SMSCHD_YEAR			0x09			/* YEAR             */
#define IB_SMSCHD_HALF			0x0A			/* HALF YEAR        */

#define IB_SMPCLINK				0x03			/* PCLINK			*/

/* INSIDE ADDIN SUBMODE CODE 0x80~ */
#define IB_INADDIN_REFENC		0x81			/* P.Referencer Mode */

/* COMMUNICATION */
#define IB_SMMAIL				0x01			/* MAIL             */
#define IB_SMFAX				0x02			/* FAX              */
#define IB_SMPCLINK				0x03			/* PCLINK           */
#define IB_SMCRAIDL				IB_SMPCLINK		/* CRAIDLE          */
#define IB_SMONLINE				0x05			/* ONLINE           */
#define IB_SMCOM_FILE			0x06 			/* FTM              */

#define IB_SMCLIP				0x02			/* CLIP(DualWindow) */

/* SYSTEM INFO */
#define IB_MDWINDOW				0x80			/* DUAL WINDOW      */
#define IW_MDWINDOW				0x8000

/* APPLICATION INFO */
#define IB_MINDEXDSP			0x01			/* INDEX/LIST       */
#define IW_MINDEXDSP			0x0001
#define IB_MDATADSP				0x02			/* DATA DISPLAY     */
#define IW_MDATADSP				0x0002
#define IB_MDATANEW				0x04			/* DATA NEW         */
#define IW_MDATANEW				0x0004
#define IB_MDATAREPR			0x08			/* DATA EDIT        */
#define IW_MDATAREPR			0x0008
#define IB_MDATASET				0x10			/* DATA REGISTRATION */
#define IW_MDATASET				0x0010
#define IB_MDATADEL				0x20			/* DATA DELETE      */
#define IW_MDATADEL				0x0020
#define IB_MSCRT_MOVE			0x80			/* DATA MOVE        */
#define IW_MSCRT_MOVE			0x0080

/* ADDIN SYNCRONIZE BIOS  */
#define IX_ADIN_COMMERR			0xffff			/* TIMEOUT or FAIL 			*/
#define IX_ADIN_DETECTBLD		0xfffe			/* DETECT BLD1				*/
#define IX_ADIN_DATAFULL		0xfffd			/* MEMORY FULL				*/

#define IB_DLFIRST_SRCH			0x00			/* FIRST SEARCH 			*/
#define IB_DLNEXT_SRCH			0x01			/* NEXT SEARCH				*/

/* flash BIOS Sub entry */
/* SubEntryStat output code */
#define	IB_SERR_RNEW	0x00	/* New registration					*/
#define	IB_SERR_RALDY	0x01	/* It has registered already.		*/
#define	IB_SERR_FOPEN	0xFF	/* Pointer for the input doesn't have a specification file name. */
#define	IB_SERR_NOSUBC	0xFE	/* SubEntry FULL					*/
#define	IB_SERR_NGSUBC	0xFD	/* SubEntryNo. outside of the range*/
#define	IB_SERR_ALDYFL	0xFC	/* already used file name*/
#define	IB_SERR_NOFILE	0xFB	/* no exist file name*/
#define	IB_SERR_INJUST	0xF0	/* input condition error(Illegal function No.)	*/
/* Used LibGetDLAllNum() */
#define IB_DLPROG_COUNT	0x01	/* Program Only					*/
#define IB_DLDATA_COUNT	0x02	/* Data Only						*/
#define IB_DLALL_COUNT	(IB_DLPROG_COUNT|IB_DLDATA_COUNT)	/* Program AND Data		*/

/* ALARM */
#define	IB_ALMOFF		0x00	/* ALARM OFF set          		*/
#define	IB_ALMON_DATA	0x01	/* ALARM ON  set(SCHEDULE)		*/
#define	IB_ALMON_DILY	0x02	/* ALARM ON  set(DAY) 			*/
#define	IB_ALMBZZ_NOW	0x03	/* ALARM STATE get              */
#define	IB_ALMPUSHWORK	0x04	/* Saves event management work    */
#define	IB_ALMPOPWORK 	0x05	/* Restores event management work */
#define	IB_ALMPUSHOBJ	0x06	

#define IML_FLASHLIB_TEXT_MAX		(32*1024)	// Flash Interface Text Buffer Size
#define IML_FLASHLIB_BIN_MAX		(32*1024)	// Flash Interface Binary Buffer Size

#define IML_LIB_MENU_ICON_MAX		256			// Application Icon Read Area 256 Byte

/************************************************************/
/*		COMPATIBLE DEFINATIONS FROM L_DEFINE.H				*/
/************************************************************/
#define	IB_BEEP0_SET			0					/* THROUGH OUT    */
#define	IB_BEEP1_SET			1					/* 1TIMES/SEC     */
#define	IB_BEEP2_SET			2					/* 2TIMES/SEC     */
#define	IB_BEEP3_SET			3					/* 3TIMES/SEC     */

/* EL */
#define	IB_ELP_OFF			0x00					/* EL PANEL OFF              */
#define	IB_ELP_ON			0x01					/* EL PANEL ON(15 SECOND)    */
#define	IB_ELP_SON			0x02					/* EL PANEL ON(CONTINUATION) */
#define	IB_ELP_ERR			0xFF					/* EL PANEL NOT EXIST or PARAM ERR */

/* KEYBOARD TYPE */
#define	IB_QWERTY			0x00					/* QWERTY */
#define	IB_AZERTY			0x01					/* AZERTY */
#define	IB_QWERTZ			0x02					/* QWERTZ */

/*******************************************************************************
							STRUCTURES
*******************************************************************************/
/* TouchStatusInformation(TouchEventBIOS OutputCondition) */
typedef struct TCHSTS {
	word	obj;			/* ObjectCode */
	dword	act;			/* ActionCode */
	int		x;				/* TouchPosition X */
	int		y;				/* TouchPosition Y */
	word	ext;			/* END Code(for the extension) */
	byte	istr[4];		/* <not used> */
	unsigned char pwon;		/* Power On Information		*/
} TCHSTS;

typedef struct T_ICON{
	TCHTBL	*tch;			/* TouchTableInformation       */
	byte	*ngp;			/* IconGraphicPattern(Normal)  */
	byte	*rgp;			/* IconGraphicPattern(Reverse) */
	byte	kind;			/* ReverseType                 */
} T_ICON;

/* ｽｸﾛｰﾙﾊﾞｰ */
typedef struct T_SCR_POS{
	int		x;				/* ScrollBarDisplayStartPosition X */
	int		y;				/* ScrollBarDisplayStartPosition Y */
	int		size;			/* ScrollBarHeight */
	int		vol;			/* TotalCount      */
	int		dsp;			/* DisplayCount    */
	int		pos;			/* DisplayStartDataPosition */
} T_SCR_POS;                               

/* Message Information Structure */
typedef struct {
	byte	**m_tbl;
	int		st_no;
	int		m_cnt;
} MES_INF;

/* SelectWindowPositionInformation */
typedef struct SLW_TBL{
	int		msg;					/* DisplayMessageNo. */
	byte	rtv;						/* The return value in choice */
} SLW_TBL;

/* SelectWindowPositionInformation */
typedef struct SLW2_ST{
	int		x;							/* WindowDisplayStartPosition X */
	int		y;							/* WindowDisplayStartPosition Y */
	int		xs;							/* WindowDisplyWhith (X size)    */
	int		ity;						/* CommentsLinePitch             */
	byte 	np;							/* ReverseCursorDefaultPosition */
	byte 	*cmnt;						/* DisplayCommentsBufferPointer  */
	byte	*rtv;						/* Buffer pointer for return value in choice */
	byte	t_xs;						/* StringDisplayStartPosition */
}SLW2_ST;

/* FLASH data buffer (32KB)*/
typedef struct FILE_BUF {
	byte	fsb_main_entry_;			/* MainEntryNo. */
	byte	fsb_sub_entry_;				/* SubEntryNo.  */

	byte	fsb_scrt_info_;				/* SecretInformation */
	byte	fsb_ararm_chk_;				/* AlarmCheckInformation */

	byte	fsb_todo_chek_;				/* TODO CheckInformation */
	byte	fsb_todo_rank_;				/* TODO RankInformation  */

	byte	fsb_date1_buf_[8];			/* Date/DueDate */
	byte	fsb_date2_buf_[8];			/* CheckDate     */
	byte	fsb_date_aram_[8];			/* AlarmDate     */
	byte	fsb_time1_buf_[4];			/* Time/DueTime(From)    */
	byte	fsb_time2_buf_[4];			/* Time/DueTime(To)      */
	byte	fsb_time3_buf_[4];			/* CheckTime             */
	byte	fsb_time_aram_[4];			/* AlarmTime             */

	byte	fsb_date_srch_[8];			/* SearchBuffer Date      */
	byte	fsb_time_srch_[4];			/* SearchBuffer Time      */
	byte	fsb_text_srch_[33];			/* SearchBuffer RealData(text) */

	union{
		struct{
								/* Buffer to store real data (TEXT) 32KB   */
			byte	fsb_text_buf_[IML_FLASHLIB_TEXT_MAX];
		}text;

		struct{
			byte	dummy_16by[22];	/* MemoryManagementWork      */
			word	char_num;		/* BinaryDataCapacity        */
								/* Buffer to store real data (BINARY) 32KB */
			byte	bin_buf[IML_FLASHLIB_BIN_MAX];
		}bin;

	}fbuf;
} FILE_BUF;
                                                          
/* FLASH data buffer [compatibility definition] */
#define LFILE_BUF	FILE_BUF


/* FLASH data buffer(for Calender Keyboard Internal Process) */
typedef struct FILE_BUF_CALE {
	byte	fsb_main_entry_;			/* MainEntryNo. */
	byte	fsb_sub_entry_;				/* SubEntryNo.  */

	byte	fsb_scrt_info_;				/* SecretInformation */
	byte	fsb_ararm_chk_;				/* AlarmCheckInformation */

	byte	fsb_todo_chek_;				/* TODO CheckInformation  */
	byte	fsb_todo_rank_;				/* TODO RankInformation   */

	byte	fsb_date1_buf_[8];			/* Date/DueDate           */
	byte	fsb_date2_buf_[8];			/* CheckDate              */
	byte	fsb_date_aram_[8];			/* AlarmDate              */
	byte	fsb_time1_buf_[4];			/* Time/DueTime(From)     */
	byte	fsb_time2_buf_[4];			/* Time/DueTime(To)       */
	byte	fsb_time3_buf_[4];			/* CheckTime              */
	byte	fsb_time_aram_[4];			/* AlarmTime              */

	byte	fsb_date_srch_[8];			/* SearchBuffer	Date      */
	byte	fsb_time_srch_[4];			/* SearchBuffer Time      */
	byte	fsb_text_srch_[33];			/* SearchBuffer RealData(TEXT) */

	union{
		struct{
			byte	fsb_text_buf_[128];/* Buffer to store real data (TEXT) */
		}text;

		struct{
			byte	dummy_16by[22];	/* MemoryManagemantWork   */
			word	char_num;		/* BinaryDataCapacity     */
			byte	bin_buf[100];		/* Buffer to store real data (BINARY) */
		}bin;

	}fbuf;
} FILE_BUF_CALE;

/* FLASH data information */
typedef struct FILE_INFO {
	word	fp;						/*	file pointer	*/
	byte	kind;						/*	TEXT/BINARY identification */
} FILE_INFO;

/* GeneralCharacterInput/DataDisplay ParameterInformation */
typedef struct  TXTP {

	/* TextInputLibrary InputCondition */
	word		st_x;				/* TextArea Left X position */
	int			ed_x;				/* TextArea Right X position */
	word		st_y;				/* TextArea Up Y position    */
	int			it_y;				/* TextAreaLinePitch         */
	int			MAXGYO;				/* TextDisplayMaximumLineNumber */
	word		maxmj;				/* MaximumInputCharacterNumber  */
	byte		font;				/* FontSizeSpecification */
	bool		csen;				/* Cursor DisplayPermission */
	byte		rtnen;				/* LineFeedMark DisplayPermission */
	byte		*txbf;				/* TextBufferPointer     */
	word		*gdcmt;				/* GuidanceCommentsTablePointer */
	byte		*gdcmt2;			/* GuidanceCommentsBufferPointer */
	word		txtobj;				/* TextAreaTouchObject   */
	word		sbrobj;				/* ScrollBarTouchObject  */
	byte		*kwb_0;				/* KeywordBuffer0 Pointer */
	byte		*kwb_1;				/* KeywordBuffer1 Pointer */
	byte		*kwb_2;				/* KeywordBuffer2 Pointer */
	byte		*kw_dbk;			/* KeywordScreenShelterPointer */
	TCHTBL		*tchtb;				/* TouchTablePointer */
	T_SCR_POS	*s_pos;				/* ScrollBarPositionInformationPointer */

	/* TextInputLibraryWorkRAM */
	word		cp;					/* CursorPointer         */
	word		xp;					/* Display X position    */
	word		yp;					/* Display Y position    */
	word		c_xp;				/* Display Cursor X position */
	word		c_yp;				/* Display Cursor Y position */
	word		dlmp[22];			/* Line top character pointer */
	byte		ditp[22];			/* Line top character pointer */
	word		csln;				/* Cursor display line position */
	word		mjln;				/* Character draw start position */
	word		mjcnt;				/* Character Capacity in Text buffer */
	byte		ipdpst;				/* Input Display Status Flag */
	byte		txtst;				/* TextInput Status Flag */
	word		sr_sp;				/* Reverse start position pointer */
	word		sr_ep;				/* Reverse end position pointer */
	word		sr_xp;				/* Reverse end position pointer X */
	word		sr_yp;				/* Reverse end position pointer Y */
	word		srln;				/* Reverse line number            */
	bool		selrv;				/* Select reverse flag   */
	word		ktyp;				/* For keyboard type shelter */
	byte		citm;				/* Now cursor item       */
	byte		wdcnt;				/* Input string length   */
	byte		kwnmt;				/* Candidate display flag */
	byte		kwsln;				/* Candidate display select line */

} TXTP;

/* Drawing InitialInformation */
typedef struct {
	byte	*RawAdr;					/* RealData VRAM  */
	byte	*BakAdr;					/* Background VRAM   */
} INIT_PACS;


/* DrawingAreaInformation */
typedef struct SETCLIPAREA_PACS{
	int		Sx;					/* Start X position */
	int		Sy;					/* Start Y position */
	int		Ex;					/* End X position */
	int		Ey;					/* End Y position */
} SETCLIPAREA_PACS;

/* LineDrawingInformation */
typedef struct DRAWLINE_PACS{
	int		x1;					/* Start X position */
	int		y1;					/* Start Y position */
	int		x2;					/* End X position */
	int		y2;					/* End Y position */
	int		Mode;				/* Drawing mode   */
	int		Size;				/* Pen size       */
	int		Style;				/* Line style     */
} DRAWLINE_PACS;

/* Drawing BOX DrawingInformation */
#define DRAWBOX_PACS		DRAWLINE_PACS

/* Drawing CircleDrawingInformation */
typedef struct DRAWCIRCLE_PACS{
	int		x;					/* Center X position */
	int		y;					/* Center Y position */
	int		r;					/* Radius */
	int		Dummy;				/* <Dummy>               */
	int		Mode;				/* Drawing mode          */
	int		Size;				/* Pen size              */
} DRAWCIRCLE_PACS;

/* Drawing FillInformation */
#define FillArea_PACS	SETCLIPAREA_PACS

/* Drawing VRAM SendingInformation */
#define TransDD_PACS	SETCLIPAREA_PACS

/* Drawing VRAM ImageWritingInformation */
typedef struct {
	int		x;				/* ImageOutputPosition X */
	int		y;				/* ImageOutputPosition Y */
	int		Width;			/* ImageWidth            */
	int		Height;			/* ImageHeight           */
	int		Mode;			/* WritingMode           */
	byte	*adr;			/* Background VRAM       */
} PutImage_PACS;

/* Drawing VRAM GetImageInformation */
typedef struct {
	int		sx;				/* GetImageAreaLeftTopPosition X */
	int		sy;				/* GetImageAreaLeftTopPosition Y */
	int		width;			/* GetImageWidth          */
	int		height;			/* GetImageHeight         */
	int		dummy;			/* <Dummy>                */
	byte	*adr;			/* ImageWritingAddress    */
} GetImage_PACS;


/* Drawing ImageCompressionInformation */
typedef struct {
	byte	*sadr;				/* Compression SourceImageAddress */
	int		sseg;				/* Compression SourceImageSegment */
	int		swidth;				/* Compression SourceImageWidth    */
	int		sheight;			/* Compression SourceImageHeight   */
	byte	*dadr;				/* Compression DestinationImageAddress */
	int		dwidth;				/* Compression DestinationImageWidth */
	int		dheight;			/* Compression DestinationImageHeight */
} ReductImage_PACS;

/* ScreenShotImageInformation */
typedef struct SHOT_INF{
	int		x;					/* ImageAreaLeftTopPosition X */
	int		y;					/* ImageAreaLeftTopPosition Y */
	int		x_size;				/* ImageWidth                 */
	int		y_size;				/* ImageHeight                */
	int		p_x;				/* WritingPosition X          */
	int		p_y;				/* WritingPosition Y          */
	byte	g_buf[3072];		/* ImageDataBuffer            */

} SHOT_INF;

/* TimeKeyboardTable */
typedef struct tTIMEKEYBCTRL {
	int		xsp,ysp;			/* SquareLeftTopPosition */
	int		xep,yep;			/* SquareRightTopPosition */
	int		font;				/* FontType */
	int		csrpos;				/* NowCursorPosition */
	char	barpos;				/* for internal process */
	char	barshift;			/* for internal process */
	bool	enabletimebar; 		/* It sets 'TRUE' when permitting TimBarbutton */ 
	bool	existnextitem; 		/* It sets 'TRUE' when there is NextItem */
	bool	existprevitem; 		/* It sets 'TRUE' when there is PreItem */
	byte	*timbuf;			/* Store buffer ('HHMMA'+00h) */
	byte	*guide;				/* Guidance strings(equal or to less than 31 bytes) */
} TIMEKEYBCTRL,*PTIMEKEYBCTRL,*LPTIMEKEYBCTRL;
 
/* BreakKeySample ESC IconTouchTable */
typedef struct BK_SMPL_TCH{
	int		x1;					/* LeftTopPosition X */
	int		y1;					/* LeftTopPosition Y */
	int		x2;					/* RightDownPosition X */
	int		y2;					/* RightDownPosition Y */
} BK_SMPL_TCH;

/* Calculator data buffer */
typedef struct caldata{
	byte	calkey;						/* Input key        */
	byte	calichi;					/* Status           */
	byte	calerror;					/* Error flag       */
	byte	calkonkai;					/* Input status (now value) */
	byte	calzenkai;					/* Input status (last value) */
	byte	calenzanf;					/* Calculation flag  */
	byte	caltisuk;					/* Placed number flag */
	byte	calperprs;					/* +% control flag */
	byte	calnoover;					/* +% overflow flag */
	byte    dummy1[7];              	/*Adjusting dummy*/      //16
    byte    calxbuf[CAL_BUFSIZE];		/* Calculation X Buffer */
    byte    dummy2[2];            		/*Adjusting dummy*/      //16
    byte    calybuf[CAL_BUFSIZE];		/* Calculation Y Buffer */
    byte    dummy3[2];            		/*Adjusting dummy*/      //16
    byte    calzbuf[CAL_BUFSIZE];		/* Fixed number buffer */
    byte    dummy4[2];            		/*Adjusting dummy*/      //16
    byte    calmbufcp[CAL_BUFSIZE];		/* Memory Value shelter buffer */
    byte    dummy5[2];            		/*Adjusting dummy*/      //16
    byte    calycpbuf[CAL_BUFSIZE];		/* Calculation shelter buffer  */
    byte    dummy6[2];            		/*Adjusting dummy*/      //16
	byte	calxdata[CAL_EZSIZE];		/* Calculation X value buffer */
	byte    dummy7[6];            		/*Adjusting dummy*/      //16
	byte	calydata[CAL_EZSIZE];		/* Calculation Y value buffer */
	byte    dummy8[6];            		/*Adjusting dummy*/      //16
	
} CALWRAM;

/* Menu Mode  Infomation */
typedef struct MJMP_INFO{			/* MENU JUMP INFORMATION TABLE */
	byte	kind;					/* 0x00=Internal Program 0x01=addin 0xff=not registered,0xfe=deleted */
	word	mode;					/* Mode (main/sub) */
	word	status;					/* status  upper byte: Internal Program、01h=UserProgram		 */
									/*		   lower byte: 01h=program,02h=data (MSB=1 then Secret ) */
} MJMP_INFO;

typedef struct {
    byte *name;
    int lag;
	int offset;
	int vol;
	int idx;
	int pos;
} CITY;

#define ALM_DMY_FUNC_ON
#ifdef	ALM_DMY_FUNC_ON
// for old pv compatiblity
/* ALARM (APPLICATION) */
typedef struct ALARM_APL {
		int		ptr;			/* POINTER                 */
		byte	date[9];		/* YEAR MONTH DAY:ASCII    */
		byte	time[4];		/* HOUR MINUTE:ASCII       */
		byte	mode;			/* MODE                    */
		byte	submode;		/* SUB MODE                */
		byte	regisdata;		/* REGIST DATA FORM        */
		byte	reserve;		/* RESERVE                 */
} ALMAPL;
#endif

#endif                

