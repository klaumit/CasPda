/******************************************************************************
*	[Title]		Binary Editor
*	[Model] 	PocketViewer
*	[Version]	Ver1.00
*
*	Copyright (C) 2002 CASIO COMPUTER CO.,LTD. All rights reserved.
******************************************************************************/

//#include	"LibUbf.h"


/*** Edit Phase ***/
#define	_ST_X		2			/* screen start point (x) */
#define	_ST_Y		15			/* screen start point (y) */
#define	_ED_X		146			/* screen end point (x) */
#define	_IT_Y		9			/* screen end point (y) */
#define	_MAXG		8			/* number of display lines */
#define	_MAXMJ		(_SCTSZ*8)	/* number of max input character */

/*** Name Input Phase ***/
#define	_FS_ST_X	5			/* screen start point (x) */
#define	_FS_ST_Y	55			/* screen start point (x) */
#define	_FS_ED_X	155			/* screen end point (x) */
#define	_FS_IT_Y	9			/* screen end point (x) */
#define	_FS_MAXG	1			/* number of display lines */
#define	_FS_MAXMJ	20			/* number of max input character */
#define	_SCTSZ		512			/* file read size unit */

/*** FileList Phase ***/
#define	_LIST_MAX	14			/* number of display lines */

/*** Touch Object ***/
#define	OBJ_IC_NEW			0xEA00
#define	OBJ_AR_LIST			0xEA01
#define	OBJ_IC_SAVE			0xEA02

/*** Pull Down Menu ***/
#define PDWN_EDT_CUT	PULLDOWN_EDIT | 0x0001		/* Cut					*/
#define PDWN_EDT_COPY	PULLDOWN_EDIT | 0x0002		/* Copy					*/
#define PDWN_EDT_PASTE	PULLDOWN_EDIT | 0x0004		/* Paste				*/
#define PDWN_EDT_DELT	PULLDOWN_EDIT | 0x0008		/* Delete				*/
#define PDWN_SYS_DTTM	PULLDOWN_SYSTEM | 0x0001	/* Set_date/time		*/
#define PDWN_SYS_SOUND	PULLDOWN_SYSTEM | 0x0002	/* Sound				*/
#define PDWN_SYS_FORMT	PULLDOWN_SYSTEM | 0x0004	/* Format				*/
#define PDWN_SYS_CAPCT	PULLDOWN_SYSTEM | 0x0008	/* Capacity				*/
#define PDWN_SYS_MMANE	PULLDOWN_SYSTEM | 0x0010	/* Memory_management	*/
#define PDWN_SYS_CNTRS	PULLDOWN_SYSTEM | 0x0020	/* Contrast				*/
#define PDWN_SYS_TPA	PULLDOWN_SYSTEM | 0x0040	/* Touch_Panel_Alignment*/

extern byte const Fname[];
extern byte const TEicn[];
extern TCHTBL const TchNewIcon[];
extern T_ICON const TiconNew;
extern TCHTBL const TchList[];
extern TCHTBL const  TchScrBar[];
extern TCHTBL const TchSaveIcon[];
extern T_ICON const TiconSave;
