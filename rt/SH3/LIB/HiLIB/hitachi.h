#ifndef	__HITACHI_H
#define	__HITACHI_H

#include <stddef.h>
#include <ctype.h>

#if 0	/* @ttake */
#include <string.h>
#include <setjmp.h>
#include <machine.h>
#include <math.h>
#endif	/* @ttake */

#define	PI	3.1415926535897932

#if 0	/* @ttake */
#include <float.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#endif	/* @ttake */

extern char		*itoa(int, char *, int);				
extern char		*ltoa(long, char *, int);				
extern char		*ultoa(unsigned long, char *, int);		
extern char		*_itoa(int, char *, int);				
extern char		*_ltoa(long, char *, int);				
extern char		*_ultoa(unsigned long, char *, int);	

#if 0	/* @ttake */
extern int	int86(long into, union REGS * in, union REGS *out);
extern int	int86x(long into, union REGS * in, union REGS *out, struct SREGS * seg);
extern int	int86y(long into, union REGS * in, union REGS *out);
#endif	/* @ttake */

extern int max(int x,int y);
extern char *strrev(char *str);

/*    excerpt from dos.h    */
#define	FP_SEG(p)	((unsigned short)((unsigned long)((void *)(p)) >> 16))
#define	FP_OFF(p)	(unsigned short)(p)
#define	MK_FP(s, o)	((void *)(((unsigned long)(s) << 16)|(unsigned short)(o)))

#if 0	/* @ttake */

#ifndef	__REGS_DEFINED
#define	__REGS_DEFINED
union REGS	{
	struct XREGS	{
		unsigned short	ax, bx, cx, dx, si, di, bp, ds, es, flags, cflag;
	}	x;
	struct HREGS	{
		unsigned char	al, ah, bl, bh, cl, ch, dl, dh;
	}	h;
};

struct SREGS	{
	unsigned short	es, cs, ss, ds;
};
#endif

#endif	/* @ttake */

#endif	/* __HITACHI_H */
