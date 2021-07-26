#include "graphics.h"
#include "gvar.h"

//Based on the agrorithm of function "arc"
//Draw arc on a circle
void pieslice(int x0, int y0, int stangle, int endangle, int radius)
{
	BOOL seedValid=FALSE;
	/*for(;radius>0; radius--)
		{
		arc( x0, y0, stangle, endangle, radius );
		}*/
	int x=x0, y=0;
	struct arccoordstype ac={0,0, 0,0, 0,0};
	BOOL cross=FALSE;	//scan line X=i first concurs with the edge of the graph 
	BOOL mayinto=FALSE;	//scan line X=i may be really  cross the internal  of the graph 
	BOOL find=FALSE;		//find the seed

	//build enclose graph
	arc(x0, y0, stangle, endangle, radius);
	getarccoords(&ac); 
	if (ac.x==100 && )
	line(ac.x, ac.y, ac.xstart, ac.ystart);
	line(ac.x, ac.y, ac.xend, ac.yend);
	
	//find the seed point	
	for (x=x0; x<x0+radius; x++)
		{
		//circle(700,x,50);
		cross=FALSE;
		mayinto=FALSE;
		for (y=0;y<599;y++)
			{
			if (! cross && getpixel(x,y)==COLOR ) cross=TRUE;
			if (cross )
				{
				if (!mayinto && getpixel(x,y)!=COLOR) mayinto =TRUE;
				else if (mayinto && getpixel(x,y)==COLOR) { y--; find=TRUE; break;}
				}
			}
		if (find) break;
		if (!cross) break;//exchange scan direction
		}
		
	if (!find)
		for (x=x0; x>x0-radius; x--)
			{
			cross=FALSE;
			mayinto=FALSE;
			for (y=0;y<599;y++)
				{
				if (! cross && getpixel(x,y)==COLOR ) cross=TRUE;
				if (cross )
					{
					if (!mayinto && getpixel(x,y)!=COLOR) mayinto =TRUE;
					else if (mayinto && getpixel(x,y)==COLOR) {y--; find=TRUE; break;}
					}
				}
			if (find) break;
			//if (!cross) break;//exchange scan direction
			}
	if(find) {floodfill(x,y,COLOR);}
}


//Draw ellipse
void sector(int x0 , int y0 , int stangle, int endangle,int a , int b)
{
	/*for(; b>0; b--)
		{
		ellipse(x0 , y0 , stangle, endangle, a , b);
		b--;
		a--;
		}*/
	int m=0;
	int x=x0, y=0;
	struct arccoordstype ac={0,0, 0,0, 0,0};
	BOOL cross=FALSE; 	//scan line X=i first concurs with the edge of the graph 
	BOOL mayinto=FALSE;	//scan line X=i may be really  cross the internal  of the graph 
	BOOL find=FALSE;		//find the seed
	//build enclose graph
	ellipse(x0, y0, stangle, endangle, a, b);
	getarccoords(&ac); 
	line(ac.x, ac.y, ac.xstart, ac.ystart);
	line(ac.x, ac.y, ac.xend, ac.yend);
	//find the seed point	
	for (x=x0; x<x0+a; x++)
		{
		cross=FALSE;
		mayinto=FALSE;
		for (y=0;y<600;y++)
			{
			if (! cross && getpixel(x,y)==COLOR ) cross=TRUE;
			if (cross )
				{
				if (!mayinto && getpixel(x,y)!=COLOR) mayinto =TRUE;
				else if (mayinto && getpixel(x,y)==COLOR) {y--; find=TRUE; break;}
				}
			}
		if (find) break;
		if (!cross) break;//exchange scan direction
		}
		
	if (!find)
		for (x=x0; x>x0-a; x--)
			{
			cross=FALSE;
			mayinto=FALSE;			
			for (y=0;y<600;y++)
				{
				if (! cross && getpixel(x,y)==COLOR ) cross=TRUE;
				if (cross )
					{
					if (!mayinto && getpixel(x,y)!=COLOR) mayinto =TRUE;
					else if (mayinto && getpixel(x,y)==COLOR) {y--; find=TRUE; break;}
					}
				}
			if (find) break;
			//if (!cross) break;//exchange scan direction
			}
	//if (x!=x0-1 && y >250) {m++,circle(0,50+m*100,50);}
	if(find) {floodfill(x,y,COLOR);}
}

