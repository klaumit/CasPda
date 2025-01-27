/************************************************************************

   ADDITION LIBRARY DEFINATIONS & PROTOTYPES for New SH PocketViewer
 	Copyright (C) 2002 CASIO COMPUTER CO.,LTD. All rights reserved.

*************************************************************************/

#ifndef __ADDLIB_H_INCLUEDED__

#define __ADDLIB_H_INCLUEDED__

#include "define.h"

/******************* BINARY FILE ACCESS LIBRARY ************************/

/*** file open mode ***/
#define		_UBFOPEN_READ				0		/* read only */
#define		_UBFOPEN_READ_SHARE			1		/* read only (share) */
#define		_UBFOPEN_WRITE				2		/* write only */
#define		_UBFOPEN_READWRITE			3		/* read & write */
#define		_UBFOPEN_READWRITE_SHARE	4		/* read & write (share) */

/*** Error Code ***/
#define		_UBFERR_MEMORY				-12		/* memory full */
#define		_UBFERR_FILENAME			-11		/* illegal file name */
#define		_UBFERR_PARAMETER			-10		/* illegal parameter */
#define		_UBFERR_SYSTEM				-9		/* system error */
#define		_UBFERR_MAXFILES			-8		/* max. number of files */
#define		_UBFERR_ACCESS				-7		/* cannot access the file */
#define		_UBFERR_FILETYPE			-6		/* file type missmatch */
#define		_UBFERR_FILTER				-5		/*  */
#define		_UBFERR_NOTFIND				-4		/* file not found */
#define		_UBFERR_FINDHANDLE			-3		/*  */
#define		_UBFERR_SEEKPOS				-2		/* illegal seek position */
#define		_UBFERR_OTHER				-1		/* other type error */


typedef struct {
	int		size;						/* file size (BYTES) */
	byte	name[MAX_FILENAMELEN+1];	/* file name */
}ubf_t;


int LibUbfFindFirst(byte *bfnm, ubf_t *buf);
int LibUbfFindNext(int sh, ubf_t *buf);
int LibUbfFindClose(int sh);
int LibUbfOpen(byte *fnm, int opnmd);
int LibUbfWrite(int fd, void *buf, int sz);
int LibUbfRead(int fd, void *buf, int sz);
int LibUbfSeek(int fd, int pos);
int LibUbfClose(int fd);
int LibUbfRemove(byte *fnm);
int LibUbfRename(byte *oldfnm, byte *newfnm);
int LibUbfLength(int fd);
int LibUbfFlush(int fd);
int LibUbfGetFree(void);

/*********************** EXTENDED TOUCH LIBRARY ****************************/

bool LibTchWaitScan(TCHSTS *tsts);



#endif
