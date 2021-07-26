#include "gvar.h"
#include "graphics.h"

typedef struct { //seed point 
	int x;
	int y;
	}
s_seed;

struct StackItem {s_seed seed ; struct StackItem * next;};

static struct StackItem * stackPointer =NULL ;

static void push(s_seed s)
{
	struct StackItem  * p;
	if (   (   p= (struct StackItem  *) malloc( sizeof(struct StackItem) )   )!=NULL   )
		{
		(*p).seed.x=s.x;
		(*p).seed.y=s.y;
		(*p).next=stackPointer;
		stackPointer = p;
		}
}

static s_seed pop()
{
	struct StackItem  *  temp;
	s_seed tempseed;
	temp=(*stackPointer).next;
	tempseed=(*stackPointer).seed;
	free(stackPointer);
	stackPointer=temp;
	return (tempseed);
}

static void FreeStack()
{
	struct StackItem  *  temp;
	while(stackPointer!=NULL)
		{
		temp=(*stackPointer).next;
		free(stackPointer);
		stackPointer=temp;
		}
}


void floodfill(int x0, int y0, int bordercolor)
{ 
	int m=0;
	int xl,xr,i;
	int x,y;
	BOOL spanNeedFill = FALSE;
	s_seed pt; //seed point
	//setstackempty();
	pt.x=x0; 
	pt.y=y0;
	push(pt);
	//if(x0==500)circle(0,0,100);
	//if(y0==549)circle(0,0,100);
	while (	stackPointer!=NULL )
		{//circle(0,0,100);		 
		pt = pop();		//pop seed point out of stack
		y=pt.y;
		x=pt.x;			//fill on right
		//if(y==125 && x==99)circle(0,0,100);
		while( getpixel(x,y)!=bordercolor ) 
			{
			//circle(0,50*m,20); 
			//
			putpixel(x,y,bordercolor);
			x++;
			if (x>801) { goto FINAL; } //avoid die error
			}
		xr = x-1;		// most right end of the filled scan line 

		x = pt.x-1;		//fill on left
		while( getpixel(x,y)!=bordercolor )
			{ 
			//m++;circle(0,50*m,20); 
			putpixel( x,y,bordercolor );
			x--;
			if (x<-1) {  goto FINAL; } //avoid die error
			}
		xl = x+1;		// most left end of the filled scan line
//=========================scan upper line to find a seed==========================================
		y = y+1;	//scan upper line
		x = xl;
		//if(xr-x>1)circle(0,300,20); 
		while(x<xr)
			{ 
			//m++;circle(0,50*m,20); 
			while( getpixel(x,y)!=bordercolor )
				{ 
				spanNeedFill=0xff;
				x++;
				if (x>801) {goto FINAL; } //avoid die error
				}
				
			if(spanNeedFill)
				{ 
				pt.x=x-1; 
				pt.y=y;
				push(pt); 	//push seed point
				spanNeedFill=0;
				}
			while( getpixel(x,y)== bordercolor && x<xr) {x++;}
			}//End of while( i<xr )
//===========================scan lower line to find a seed==================================
		y = y-2;
		x = xl;
		while(x<xr)
			{
			while( getpixel(x,y)!=bordercolor )
				{ 
				spanNeedFill=0xff;
				x++;
				if (x>801) {goto FINAL;  } //avoid die error
				}
			if( spanNeedFill )
				{ 
				pt.x=x-1; 
				pt.y=y;
				push(pt);	//push seed point
				spanNeedFill=0;
				}
			while( getpixel(x,y) == bordercolor && x<xr) x++; //m++;circle(20,50*m,20); }
			}//End of while( i<xr )
		}//End of while( ! isstackempty())
	FINAL: FreeStack();
}
