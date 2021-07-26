#include "graphics.h" 
#include "gvar.h"

enum e{ BothUp, BothDown, Against };

//scan precise start point and end point
#define SCAN_TERM_POINR(i) \
do{\
	for( x=startx,i=0; x<startx+10; i++ )\
		for (y=starty-10; y<starty+10; y++)\
			{\
			if ( getpixel(x+i,y)==COLOR ) {startx=x+i; starty=y; return; }\
			if ( getpixel(x-i,y)==COLOR ) {startx=x-i; starty=y; return; }\
			}\
	for( x=endx,i=0; x<endx+10; i++ )\
		for (y=endy-10; y<endy+10; y++)\
			{\
			if ( getpixel(x+i,y)==COLOR ) {endx=x+i; endy=y; return; }\
			if ( getpixel(x-i,y)==COLOR ) {endx=x-i; endy=y; return; }\
			}\
}while(0);	


static void __put_circle_points( int x0, int y0, int x, int y, int c )
{
	putpixel(x0+x, y0+y, c);
	putpixel(x0+x, y0-y, c);
	putpixel(x0-x, y0+y, c);
	putpixel(x0-x, y0-y, c);
	putpixel(x0+y, y0+x, c);
	putpixel(x0+y, y0-x, c);
	putpixel(x0-y, y0+x, c);
	putpixel(x0-y, y0-x, c);
}

static void __cond_put_circle_points( int x0, int y0, int x, int y, int c, int startx, int endx, enum e TipPointsLoc, BOOL direct )
{	
	if (TipPointsLoc==BothUp)
		{
		//endx=_endx-2; startx=_startx+2;
		if(direct){// angle for fill is less than 180 //draw (x,y) (-x,y) (-y,x) (y,x)
			y=-y; 	//correct the screen reference frame
			//p->startx=-
			if ( (endx<=x) &&(x<=startx) )		{putpixel(x0+x, y0+y, c);}
			if ( (endx<=-x) &&(-x<=startx) )	{putpixel(x0-x, y0+y, c);}
			x=-x;	//correct the screen reference frame
			if ( (endx<=y) &&(y<=startx) )		{putpixel(x0+y, y0+x, c);}
			if ( (endx<=-y) &&(-y<=startx) )	{putpixel(x0-y, y0+x, c);}
			}
		else{//draw (x,y) (-x,y) (-y,x) (y,x)  and (-x,-y) (x,-y)  (-y,-x) (y,-x) 
			y=-y; 	//correct the screen reference frame
			if ( x<=startx || x>=endx)		{putpixel(x0+x, y0+y, c);}
			if ( -x<=startx || -x>=endx)		{putpixel(x0-x, y0+y, c);}
			putpixel(x0-x, y0-y, c);
			putpixel(x0+x, y0-y, c);
			x=-x;	//correct the screen reference frame
			if ( y<=startx || y>=endx )		{putpixel(x0+y, y0+x, c);}
			if ( -y<=startx || -y>=endx )		{putpixel(x0-y, y0+x, c);}
			putpixel(x0-y, y0-x, c);
			putpixel(x0+y, y0-x, c);			
			}
		}
		
	else if(TipPointsLoc==BothDown)
    		{//draw (-x,-y) (x,-y) (-y,-x) (y,-x)
		//endx=_endx+2; startx=_startx-2;
		if(direct){
			y=-y; 	//correct the screen reference frame
			if ( (startx<=-x) &&(-x<=endx) )	putpixel(x0-x, y0-y, c);
			if ( (startx<=x) &&(x<=endx) )		putpixel(x0+x, y0-y, c);
			x=-x;	//correct the screen reference frame		
			if ( (startx<=-y) &&(-y<=endx) )	putpixel(x0-y, y0-x, c);
			if ( (startx<=y) &&(y<=endx) )		putpixel(x0+y, y0-x, c);
			}
		else{//draw (x,y) (-x,y) (-y,x) (y,x)  and (-x,-y) (x,-y)  (-y,-x) (y,-x) 
			y=-y; 	//correct the screen reference frame
			if ( (startx<=-x) || (-x<=endx) )	putpixel(x0-x, y0-y, c);
			if ( (startx<=x) || (x<=endx) )		putpixel(x0+x, y0-y, c);
			putpixel(x0+x, y0+y, c);
			putpixel(x0-x, y0+y, c);
			x=-x;	//correct the screen reference frame		
			if ( (startx<=-y) || (-y<=endx) )	putpixel(x0-y, y0-x, c);
			if ( (startx<=y)  || (y<=endx) )	putpixel(x0+y, y0-x, c);
			putpixel(x0+y, y0+x, c);
			putpixel(x0-y, y0+x, c);	
			}
		}
	else
		{
		if (direct){// start ege is on  up
			//endx=_endx+2; startx=_startx+2;
			y=-y; 	//correct the screen reference frame
			if ( x<=startx )	{putpixel(x0+x, y0+y, c);}
			if ( -x<=startx )	putpixel(x0-x, y0+y, c);
			if (x<=endx ) 	putpixel(x0+x, y0-y, c);
			if (-x<=endx)	putpixel(x0-x, y0-y, c);
			x=-x;	//correct the screen reference frame		
			if ( y<=startx )	{putpixel(x0+y, y0+x, c);}
			if ( -y<=startx )	putpixel(x0-y, y0+x, c);
			if (y<=endx ) 	putpixel(x0+y, y0-x, c);
			if (-y<=endx)	putpixel(x0-y, y0-x, c);	
			}
		else{
			//endx=_endx-2; startx=_startx-2;
			y=-y; 	//correct the screen reference frame
			if ( x>=startx )	{putpixel(x0+x, y0-y, c);}
			if ( -x>=startx )	putpixel(x0-x, y0-y, c);
			if (x>=endx ) 	putpixel(x0+x, y0+y, c);
			if (-x>=endx)	putpixel(x0-x, y0+y, c);
			x=-x;	//correct the screen reference frame		
			if ( y>=startx )	{putpixel(x0+y, y0-x, c);}
			if ( -y>=startx )	putpixel(x0-y, y0-x, c);
			if (y>=endx ) 	putpixel(x0+y, y0+x, c);
			if (-y>=endx)	putpixel(x0-y, y0+x, c);			
			}
		}	
}

static void __cond_put_ellipse_points(int x0, int y0, int x, int y, int c,int startx, int endx, enum e TipPointsLoc, BOOL direct)
{
	y=-y;	//correct the screen reference frame
	if (TipPointsLoc==BothUp)
		{//draw (x,y) (-x,y) (x,-y) (-x,-y)
		if (direct){
			if ( (endx<=x) &&(x<=startx) )		putpixel(x0+x, y0+y, c);
			if ( (endx<=-x) &&(-x<=startx) )	putpixel(x0-x, y0+y, c);
			}
		else{
			if ( (endx<=x) || (x<=startx) )		putpixel(x0+x, y0+y, c);
			if ( (endx<=-x) || (-x<=startx) )	putpixel(x0-x, y0+y, c);
			putpixel(x0+x, y0-y, c);
			putpixel(x0-x, y0-y, c);
			}
		}
	else if(TipPointsLoc==BothDown)
    		{//draw (x,y) (-x,y) (x,-y) (-x,-y)
		if(direct){
			if ( (startx<=x) &&(x<=endx) )		putpixel(x0+x, y0-y, c);
			if ( (startx<=-x) &&(-x<=endx) )	putpixel(x0-x, y0-y, c);
			}
		else{
			if ( (startx<=x) || (x<=endx) )		putpixel(x0+x, y0-y, c);
			if ( (startx<=-x) || (-x<=endx) )	putpixel(x0-x, y0-y, c);
			putpixel(x0+x, y0+y, c);
			putpixel(x0-x, y0+y, c);
			}	
		}
	else
		{//draw (x,y) (-x,y) (x,-y) (-x,-y)
		if(direct){
			if ( x<=startx )	putpixel(x0+x, y0+y, c);
			if ( -x<=startx )	putpixel(x0-x, y0+y, c);
			if ( x<=endx )	putpixel(x0+x, y0-y, c);
			if ( -x<=endx )	putpixel(x0-x, y0-y, c);
			}
		else{
			if ( x>=startx )	putpixel(x0+x, y0+y, c);
			if ( -x>=startx )	putpixel(x0-x, y0+y, c);
			if ( x>=endx )	putpixel(x0+x, y0-y, c);
			if ( -x>=endx )	putpixel(x0-x, y0-y, c);			
			}
		}
} 

//-------------------------------------------------------------------------------------------------------------------------------------
//Draw a circle
void circle (int x0, int y0, int r)
{
	int x, y, p;
	x=0;
	y=r;
	p=3-2*r;
	while (x<y){
        	__put_circle_points(x0, y0, x, y, COLOR);
        	if (p<0) p=p+4*x+6;
        	else
			{
                  	p=p+4*(x-y)+10;
                  	y--;
                	}
        	x++;
               	}
	if (x==y)
        __put_circle_points(x0, y0, x, y, COLOR);
}

//Draw arc on a circle
void arc(int x0, int y0, int stangle, int endangle, int radius)
{
	int x, y, p;
	enum e TipPointsLoc;//the relative locations of start and end point 
	int startx,starty,endx,endy;//x coordinate of start point and end point
	float rad;
	BOOL direct;
	int mm;
	//angle standardize
	ANGLE_STANDARDIZE(stangle,endangle);
	//if (stangle==180)circle(100,100,100);
	//////////////////
	ARC_CRITIC_POINT_DISPOSE(stangle, endangle, radius, rad, TipPointsLoc, direct, startx, starty, endx, endy);

	//	
	x=0;
	y=radius;
	p=3-2*radius;
	while (x<y){
        	__cond_put_circle_points(x0, y0, x, y, COLOR, startx, endx, TipPointsLoc,direct);
        	if (p<0) p=p+4*x+6;
        	else
			{
                  	p=p+4*(x-y)+10;
                  	y--;
                	}
        	x++;
               	}
	if (x==y)
        	__cond_put_circle_points(x0, y0, x, y, COLOR, startx, endx, TipPointsLoc,direct);
	//correct screen coordinates and put down some points
	starty=-starty;
	endy=-endy;
	//move
	startx+=x0;
	starty+=y0;
	endx+=x0;
	endy+=y0;
	int i;
	SCAN_TERM_POINR(i)
	SET_CUR_POINT(endx,endy);
	SET_CUR_ARCCOORDS(x0,y0, startx,starty, endx,endy);
}


//Draw ellipse
void ellipse(int x0 , int y0 , int stangle, int endangle, int a , int b)
{
	int x,y;  
	float p;
	float radius;
	enum e TipPointsLoc;		//the relative locations of start and end point 
	int startx,starty,endx,endy;		//x coordinate of start point and end point
	float rad;
	BOOL direct;
	//angle standardize
	ANGLE_STANDARDIZE(stangle,endangle);
	//////////////////////////////
	ELP_CRITIC_POINT_DISPOSE(stangle, endangle, radius, rad, TipPointsLoc, direct, startx, starty, endx, endy);
	
	x = 0; 
	y = b;		
	p = b*b +a*a*(0.25-b);
	__cond_put_ellipse_points(x0,y0,x,y,COLOR,startx,endx,TipPointsLoc,direct);
	while( b*b*(x+1) < a*a*(y-0.5))  //upper part  
		{
		x++;  
		if (p<0){
			p += b*b*(2*x+3); 
			}
		else{  
			p += b*b*(2*x+3) + a*a*(-2*y+2); 
			y--;
			} 
		__cond_put_ellipse_points(x0,y0,x,y,COLOR,startx,endx,TipPointsLoc,direct);
		}	
	p = b*b*(x+0.5)*(x+0.5) + a*a*(y-1)*(y-1) - a*a*b*b;
	while(y >0)	//lower part
		{ 
		y--;
		if (p <0) 
			{ 
			p +=a*a*(-2*y+3)+b*b*(2*x+2);
			x++;	
			}
		else{
			p +=a*a*(-2*y+3);	 
			}
		__cond_put_ellipse_points(x0,y0,x,y,COLOR,startx,endx,TipPointsLoc,direct);
		}
	//correct screen coordinates
	starty=-starty;
	endy=-endy;
	//move
	startx+=x0;
	starty+=y0;
	endx+=x0;
	endy+=y0;
	int i;
	SCAN_TERM_POINR(i)
	//put down some points
	SET_CUR_POINT(endx,endy);
	SET_CUR_ARCCOORDS(x0,y0, startx,starty, endx,endy);	
}
