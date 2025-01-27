/*****************************************************************************
*	[Title]		LibTchWaitScan SAMPLE PROGRAM Main File
*	[Model] 	PV Unit
*	[Version]	Ver1.00
******************************************************************************/
#include	<hitachi.h>
#include	"define.h"
#include	"libc.h"

#define LBOX_X1		0
#define LBOX_Y1		110
#define LBOX_X2		79
#define LBOX_Y2		134

#define RBOX_X1		80
#define RBOX_Y1		110
#define RBOX_X2		159
#define RBOX_Y2		134

#define UBOX_X1		0
#define UBOX_Y1		85
#define UBOX_X2		159
#define UBOX_Y2		109

#define DBOX_X1		0
#define DBOX_Y1		135
#define DBOX_X2		159
#define DBOX_Y2		159

#define TAREA_X1	0
#define TAREA_Y1	85
#define TAREA_X2	159
#define TAREA_Y2	159

#define AREA_INVALID	0
#define AREA_LBOX		1
#define AREA_RBOX		2
#define AREA_UBOX		3
#define AREA_DBOX		4

#define OBJ_AREA_L		0x9001
#define OBJ_AREA_R		0x9002
#define OBJ_AREA_U		0x9003
#define OBJ_AREA_D		0x9004

#define BALL_SIZEX	8
#define BALL_SIZEY	8
const byte GraphBall1[] = {
	GSIZE(8, 8),
	0x18,
	0x7E,
	0x7E,
	0xFF,
	0xFF,
	0x7E,
	0x7E,
	0x18,
};
const byte GraphBall2[] = {
	GSIZE(8, 8),
	0x00,
	0x18,
	0x3C,
	0x7E,
	0x7E,
	0x3C,
	0x18,
	0x00,
};
const byte GraphL[] = {
	GSIZE(15, 15),
	0x00, 0x07,
	0x00, 0x19,
	0x00, 0x61,
	0x01, 0x81,
	0x06, 0x01,
	0x18, 0x01,
	0x60, 0x01,
	0x80, 0x01,
	0x60, 0x01,
	0x18, 0x01,
	0x06, 0x01,
	0x01, 0x81,
	0x00, 0x61,
	0x00, 0x19,
	0x00, 0x07,
};
const byte GraphR[] = {
	GSIZE(15, 15),
	0xC0, 0x01,
	0x30, 0x01,
	0x0C, 0x01,
	0x03, 0x01,
	0x00, 0xC1,
	0x00, 0x31,
	0x00, 0x0D,
	0x00, 0x03,
	0x00, 0x0D,
	0x00, 0x31,
	0x00, 0xC1,
	0x03, 0x01,
	0x0C, 0x01,
	0x30, 0x01,
	0xC0, 0x01,
};
const byte GraphU[] = {
	GSIZE(15, 15),
	0x01, 0x01,
	0x02, 0x81,
	0x02, 0x81,
	0x04, 0x41,
	0x04, 0x41,
	0x08, 0x21,
	0x08, 0x21,
	0x10, 0x11,
	0x10, 0x11,
	0x20, 0x09,
	0x20, 0x09,
	0x40, 0x05,
	0x40, 0x05,
	0x80, 0x03,
	0x80, 0x03,
};
const byte GraphD[] = {
	GSIZE(15, 15),
	0x80, 0x03,
	0x80, 0x03,
	0x40, 0x05,
	0x40, 0x05,
	0x20, 0x09,
	0x20, 0x09,
	0x10, 0x11,
	0x10, 0x11,
	0x08, 0x21,
	0x08, 0x21,
	0x04, 0x41,
	0x04, 0x41,
	0x02, 0x81,
	0x02, 0x81,
	0x01, 0x01,
};
const TCHTBL TchTblAreaAll[] =
{
	LBOX_X1, LBOX_Y1, LBOX_X2, LBOX_Y2,
	ACT_MAKE | ACT_BREAK | ACT_DOWN,
	OBJ_AREA_L,
	0x0000,

	RBOX_X1, RBOX_Y1, RBOX_X2, RBOX_Y2,
	ACT_MAKE | ACT_BREAK | ACT_DOWN,
	OBJ_AREA_R,
	0x0000,

	UBOX_X1, UBOX_Y1, UBOX_X2, UBOX_Y2,
	ACT_MAKE | ACT_BREAK | ACT_DOWN,
	OBJ_AREA_U,
	0x0000,

	DBOX_X1, DBOX_Y1, DBOX_X2, DBOX_Y2,
	ACT_MAKE | ACT_BREAK | ACT_DOWN,
	OBJ_AREA_D,
	0x0000,

	0, 0, 0, 0,	ACT_NONE, OBJ_END, 0x0000
};

void BoxDisp(void)
{
	LibGdsBox(LBOX_X1, LBOX_Y1, LBOX_X2, LBOX_Y2);
	LibGdsBox(RBOX_X1, RBOX_Y1, RBOX_X2, RBOX_Y2);
	LibGdsBox(UBOX_X1, UBOX_Y1, UBOX_X2, UBOX_Y2);
	LibGdsBox(DBOX_X1, DBOX_Y1, DBOX_X2, DBOX_Y2);
	LibPutGraph(LBOX_X1+33, LBOX_Y1+5, GraphL);
	LibPutGraph(RBOX_X1+33, RBOX_Y1+5, GraphR);
	LibPutGraph(UBOX_X1+73, UBOX_Y1+5, GraphU);
	LibPutGraph(DBOX_X1+73, DBOX_Y1+5, GraphD);
}

int JudgeTouchArea(TCHSTS *tsts)
{
	int area;
	int x, y;

	x = tsts->x; y = tsts->y; 

	if ((LBOX_X1 <= x)&&(x<= LBOX_X2)&&(LBOX_Y1 <= y)&&(y <= LBOX_Y2)) {
		area = AREA_LBOX;
	}
	else if ((RBOX_X1 <= x)&&(x <= RBOX_X2)&&(RBOX_Y1 <= y)&&(y <= RBOX_Y2)) {
		area = AREA_RBOX;
	}
	else if ((UBOX_X1 <= x)&&(x <= UBOX_X2)&&(UBOX_Y1 <= y)&&(y <= UBOX_Y2)) {
		area = AREA_UBOX;
	}
	else if ((DBOX_X1 <= x)&&(x <= DBOX_X2)&&(DBOX_Y1 <= y)&&(y <= DBOX_Y2)) {
		area = AREA_DBOX;
	}
	else {
		area = AREA_INVALID;
	}

	return (area);
}

void GraphicDisp(int x, int y)
{
	LibPutGraph(x, y, GraphBall1);
}

void GraphicClr(int x, int y)
{
	LibClrBox(x, y, BALL_SIZEX, BALL_SIZEY);
}

void GraphicReverse(int x, int y, bool *b1)
{
	*b1 = !(*b1);

	if (*b1) {
		LibPutGraph(x, y, GraphBall1);
	}
	else {
		LibPutGraph(x, y, GraphBall2);
	}
}

void GraphicMove(int area, int *x, int *y)
{
#define GMOV_DOTX	1
#define GMOV_DOTY	1

	GraphicClr(*x, *y);

	switch(area) {
	case AREA_INVALID :
		break;

	case AREA_LBOX :
		*x -= GMOV_DOTX;
		if (*x < 1) *x = 1;
		break;

	case AREA_RBOX :
		*x += GMOV_DOTX;
		if (*x > (159 - BALL_SIZEX)) *x = (159 - BALL_SIZEX);
		break;

	case AREA_UBOX :
		*y -= GMOV_DOTY;
		if (*y < 0) *y = 0;
		break;

	case AREA_DBOX :
		*y += GMOV_DOTY;
		if (*y > (UBOX_Y1 - BALL_SIZEX)) *y = (UBOX_Y1 - BALL_SIZEX);
		break;

	default	:
		break;
	}

	GraphicDisp(*x, *y);
}

/******************************************************************************
*  [Title]			main
*  [Arguments]		None
*  [ReturnVAL]		None
*******************************************************************************/
void main(void)
{
#define STATE_NONE	0
#define STATE_IDOL	1
#define STATE_MOVE	2

	bool exist;
	TCHSTS tsts;
	bool b1=TRUE;
	int	state, area, act;
	int gx=75, gy=10;

	LibClrDisp();
	BoxDisp();
	GraphicDisp(gx, gy);
	LibPutDisp();

	state = STATE_IDOL;
	LibTchInit();
	LibTchStackClr();
	LibTchStackPush(0);
	LibTchStackPush(TchHardIcon);
	LibTchStackPush(TchTblAreaAll);

	while(1){
		exist = LibTchWaitScan(&tsts);
		if (exist) {							// The input occurred.
			switch (tsts.act) {
			case ACT_MAKE :
			case ACT_DOWN :
				state = STATE_MOVE;
				area = JudgeTouchArea(&tsts);
				GraphicMove(area, &gx, &gy);
				b1 = TRUE;
				LibPutDispBox(0, 0, UBOX_X2, UBOX_Y2);
				break;

			case ACT_BREAK :
				state = STATE_IDOL;
				break;
			}
		}
		else {
			// The process which is not related with an input is described here.
			// Even under an input, it may come here. so a state is judged.
			if (state==STATE_IDOL) {
				LibWait(IB_250MWAIT);
				GraphicReverse(gx, gy, &b1);
				LibPutDispBox(0, 0, UBOX_X2, UBOX_Y2);
			}
		}
	}
}

