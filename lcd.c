#include <linux/fb.h> 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static int fb;

//unit : pixel
#define WIDTH 800
#define HEIGHT 600

static struct fb_var_screeninfo var;
static int fb_w, fb_h, bpp;

static unsigned char c0=0, c1=1,c2=2,c3=3,c4=4,c5=5,c6=6,c7=7,c8=8,c9=9,c10=10,c11=11,c12=12,c13=13,c14=14,c15=15;
static unsigned short sblack=0xffff,swhite=0x01;

extern void LCDFillRect(int x0, int y0, int w, int h, int color);
extern void LCDGetGeometry(void);

#define FILL_BUFFER_BYTE(color) \
 do {\
	switch(color) \
		{\
		case 0:write(fb, &c0, 1);break;\
		case 1:write(fb, &c1, 1);break;/*1*/\
		case 2:write(fb, &c2, 1);break;/*2*/\
		case 3:write(fb, &c3, 1);break;/*3*/\
		case 4:write(fb, &c4, 1);break;/*4*/\
		case 5:write(fb, &c5, 1);break;/*5*/\
		case 6:write(fb, &c6, 1);break;/*8*/\
		case 7:write(fb, &c7, 1);break;/*9*/\
		case 8:write(fb, &c8, 1);break;/*8*/\
		case 9:write(fb, &c9, 1);break;/*9*/\
		case 10:write(fb, &c10, 1);break;/*9*/\
		case 11:write(fb, &c11, 1);break;/*9*/\
		case 12:write(fb, &c12, 1);break;/*9*/\
		case 13:write(fb, &c13, 1);break;/*9*/\
		case 14:write(fb, &c14, 1);break;/*9*/\
		case 15:write(fb, &c15, 1);break;/*9*/\
		} \
}while(0) 

void LCDInit(void)
{
    if ((fb = open("/dev/fb0", O_RDWR)) == -1) { // not O_WRONLY
	printf("open error!\n");
	exit(-1);
    }
    if (ioctl(fb, FBIOGET_VSCREENINFO, &var)){//get lcd parameters
	exit(-1);
    }
    fb_w = var.xres;//row pixes
    fb_h = var.yres;//column pixes
    bpp = (var.bits_per_pixel + 7) >> 3;//bytes per pix
	
    LCDGetGeometry();
//    LCDFillRect(0, 0, WIDTH, HEIGHT, 0);
}

void LCDFini(void)
{
    close(fb);
}



//fuction :Every byte or two byte of framebuffer stand one pixel.
//int x,y :The pixel's location, their base is zero
//int c: the pixel is white while it is true;
 
void putpixel(int x, int y, int c)
{
    if ( x < 0 || x >= WIDTH) return;
    if ( y < 0 || y >= HEIGHT) return;
    //move to the buffer of pixel(x,y);  fb_w*bpp=bytes per row
    lseek(fb, (y) * fb_w * bpp  + x * bpp  ,SEEK_SET);
    //write the buffer of pixel(x,y)
    FILL_BUFFER_BYTE(c); 
    /*if (bpp == 2) {
	if (c)
	    write(fb, &swhite, 2);	//ssize_t write(int fd£¬ const void *buffer£¬size_t count)£»
	else
	    write(fb, &sblack, 2);
    } else { 	
	if (c)
	    write(fb, &white, 1);
	else
	    write(fb, &black, 1);
    }*/
}

unsigned int  getpixel(int x, int y)
{
	char color=0;
	//char *p
	lseek(fb, (y) * fb_w * bpp  + x * bpp  ,SEEK_SET);
	if ( read( fb, &color, bpp ) != -1 )
		return color;
	else 
		return -1;
	
}



void LCDFillRect(int x0, int y0, int w, int h, int color)//unit of w,h is 8 pixel
{
    int i, j;
    for (i=0;i<w ; i++)
	for (j=0;j<h ; j++)
	    putpixel(x0+ i, y0  + j, color);
}

void LCDPutImage(int x0, int y0, int w, int h, char *buf)//unit of x0,y0 is pixel ;           unit of w,h is 8 pixel
{
    int i, j, k;// unit : pixel
    char abyte;
    for (i=0;i<w * 8;i++)
	for (j=0;j<h * 8;j++) {
	    abyte = buf [(i + w * 8 * j) / 8];//every bit of buf is used to draw one pixel
	    if (abyte & (0x80 >> (i % 8)))
		putpixel(x0 * 8 + i, y0 * 8 + j, 1);
	    else
		putpixel(x0 * 8 + i, y0 * 8 + j, 0);
	}
}

void LCDPutImageRev(int x0, int y0, int w, int h, char *buf)
{
    int i, j, k;
    char abyte;
    for (i=0;i<w * 8;i++)
	for (j=0;j<h * 8;j++) {
	    abyte = buf [(i + w * 8 * j) / 8];
	    if (abyte & (0x80 >> (i % 8)))
		putpixel(x0 * 8 + i, y0 * 8 + j, 0);
	    else
		putpixel(x0 * 8 + i, y0 * 8 + j, 1);
	}
}

unsigned int LCDWidth;
unsigned int LCDHeight;

void LCDGetGeometry(void)
{
    LCDWidth  = WIDTH / 8;
    LCDHeight = HEIGHT / 8;
}



