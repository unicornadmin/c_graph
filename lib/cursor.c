#include "gvar.h"
#include "graphics.h"
int getx( void) 
{
	return CurPoint.x;
}


int gety( void)
{
	return CurPoint.y;
}


void moveto(int x, int y)
{
	SET_CUR_POINT(x,y);
}


void moverel(int dx, int dy)
{
	SET_CUR_POINT(CurPoint.x+dx,CurPoint.y+dy);
}


