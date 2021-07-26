
#include "graphics.h"
#include "gvar.h"

extern void LCDInit(void);
extern void LCDFini(void);
extern void LCDFillRect(int x0, int y0, int w, int h, int color);

//#define TIMES 10
#define J 3000000

//color definitions
#define BLACK 0
#define lBLUE 1
#define lGREEN 2
#define lCYAN 3
#define lRED 4
#define lPINK 5
#define lYELLOW 6
#define lGRAY 7
//dark color
#define GRAY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define PINK 13
#define YELLOW 14
#define WHITE 15
//	extern int LinuxConsoleFd;



#define OX 400
#define OY 300 

int main(void)
{     
	short m,l;
	unsigned int i=800;
	unsigned long j=J;
	//unsigned short timer=TIMES;
	int loop=0;
	int poly6[14]={400,100, 500,200, 500,300, 400,400, 300,300, 300,200, 400,100 };
	int poly4u[10]={ 400,200 , 500,350 ,420,280, 200,300, 400,200 };
	//int pwx[22]={ 0,20, 8,0, 20,0, 10,-10, 15,-22, 0,-20, -15,-22, -10,-10, -20,0, -9,0, 0,20 };
	int poly4d[10]={400,300, 480,150, 370,500, 300,100, 400,300};
	int rect[10]={100,200, 300,200, 300,400, 100,400, 100,200};
	//int *p=points;
	struct arccoordstype a={0,0, 0,0, 0,0};
	
	LinuxInit();
	LCDInit();
	COLOR=15;
	/*for (loop=0;loop<22;loop=loop+2)
		{
		pwx[loop]+=OX;
		pwx[loop+1]+=OY;
		}*/
	//draw something here;
	//line(300,300,500,300);
	//line(400,250,400,350);
	//LCDFillRect(0,0,800,20,1);
	//LCDFillRect(0,20,800,40,7);
	//LCDFillRect(0,60,800,500,15);
	//LCDFillRect(0,560,800,40,7);
	//arc(100,300,270,350,50); //arc(200,300,-90,-180,50);
	//arc(100,500,0,180,50); arc(200,500,180,0,50);
	//ellipse(100,100,0,-90,100,50); ellipse(200,100,90,0,100,50);
	//ellipse(400,100,180,0,100,50); ellipse(400,150,0,180,100,50); ellipse(400,500,0,0,100,50);
	//rectangle(500,250,700,350);
	//drawpoly(5,rect);
	//fillpoly(5,poly4u);
	//fillpoly(5,rect);
	arc(100,100,200,270,50);//pieslice(100,100,200,270,50);
	sector(400,300,215,270,100,50);//sector(400,300,100,170,100,50);sector(400,300,10,80,100,50);sector(400,300,280,350,100,50);
	//=======================================putpixel(500,250,5);
	//ellipse(500,500,90,360,100,50); 
	//getarccoords(&a); line(a.x, a.y, a.xstart, a.ystart); line(a.x, a.y, a.xend, a.yend);
	//floodfill(550,501,COLOR);
	COLOR=4;
	//delay time
	while(i>0) {
		while(j>0) j--;
		j=J;
		putpixel(800-i,580,COLOR);
		i--;
		} 
	LCDFini();
	LinuxFini();
	return 0;
}
