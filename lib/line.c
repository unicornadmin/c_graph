#include "graphics.h" 

#include "gvar.h"
//struct arccoordstype CurArccoords;
//Draw a line
//point(x0,y0) may not be the start point
void line(int x0,int y0, int x1,int y1)
{
	int x,y;//start point's coordinate
	int dx,dy;
	int p; //decition para
	int ksign; //the sign of k
	int tempy,temp,i;
	char AxisChngFlag=0x0;
	//
	SET_CUR_POINT(x1,y1);
    	dy=abs(y1-y0);
    	dx=abs(x1-x0);	
	//Assumed that |k|<=1; decide which point is on the left and decide the sign of k     	
	if (x0<=x1) // point 0 is on the left 
		{
		x=x0;
		y=y0;
		if (y1>=y0) ksign=1; else ksign=-1;	//dy=y1-y0
		}
	else	// point 1 is on the left
		{
		x=x1;
		y=y1;
		if (y0>=y1) ksign=1; else ksign=-1;	//dy=y0-y1
		}	 
	//When |k|>1 , exchange x,y axis, after this , |k|>=1 is  the same as |k|<1.
	//contain the case of dx=0, when dx=0 ,deciding where is the start is diffrence!
   	if(dy>dx) 
		{
		//make the symmetrical line of the line to be show on the screen about lint y=x
		AxisChngFlag=0xf;
		temp=y; y=x; x=temp;
		temp=dx; dx=dy; dy=temp;
		//decide the start of the line after transimission
		if (x>y0) { x=y0; y=x0; }
		if (x>y1) { x=y1; y=x1; }
		}		
	//now |k|<1 ! if k<0 ,then make the symmetrical point of the start ploint(x,y) about the X axis, so 0<k<1
	y=y*ksign;
	tempy=y;
	// draw the line	
	p= 2*dy-dx; 
	for( i=0; i<=dx; i++){
		//trun the reference line with 0<k<1 into real line on the sreen 
		y=tempy*ksign;					//if k<0, make the symmetric line about the X axis			
		if (AxisChngFlag) {temp=x;x=y;y=temp;}			//when |k|>=1 ,the coordinate(x,y) is correct in regular  reference frame
		putpixel(x,y,COLOR);					//draw;
		//trun back the real line into the reference line with 0<k<1	
		if (AxisChngFlag) {temp=x;x=y;y=temp;}			//x
		y=tempy*ksign;					//if k<0, make the symmetric line about the X axis
		//compute the line in the condition of 0<k<1
		x++; 
		if (p<0)
                 	p=p+2*dy; 	//y need not be changed
                else
                	{
			tempy++;		//when 0<k<1 ,temp is the the correct coordinate on y axis  in regular  reference frame
			p=p+2*dy-2*dx;
                	}
						
	} 
	putpixel(x1,y1,COLOR);      
}

void	   lineto(int x, int y)
{
	line(getx(),gety(),x,y);

}



void	linerel(int dx, int dy)
{
	int xs,ys;
	xs=getx();
	ys=gety();
	line(xs,ys,xs+dx,ys+dy);
}

void  rectangle(int x0, int y0, int x1, int y1)
{
	int i;
	if(x0>x1)return;
	if(y0>y1)return;
	for(i=x0;i<x1+1;i++)
		{
		putpixel(i,y0,COLOR);
	        putpixel(i,y1,COLOR);
		}
	for(i=y0;i<y1+1;i++)
		{
		putpixel(x0,i,COLOR);
	        putpixel(x1,i,COLOR);		
		
		}
	SET_CUR_POINT(x1,y1);

}

void drawpoly(int pnum,int *p)
{
	int i;
	if (pnum%2!=0 && pnum<2) return;
	for(i=0;i<pnum-1;i++)
		{
		line(*(p+i*2),*(p+i*2+1),*(p+i*2+2),*(p+i*2+3));
		}


}

void getarccoords(struct arccoordstype *arccoords)
{
	GET__CUR_ARCCOORDS(arccoords);

}  

