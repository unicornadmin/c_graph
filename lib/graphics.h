/*	graphics.h

	Definitions for Graphics Package.

	Copyright (c) Borland International 1987,1988
	All Rights Reserved.
*/


#if __STDC__
	#define _Cdecl
#else
	#define _Cdecl	cdecl
#endif

#if     !defined(__GRAPHX_DEF_)
	#define __GRAPHX_DEF_

enum graphics_errors {		/* graphresult error return codes */
	grOk		=   0,
	grNoInitGraph	=  -1,
	grNotDetected	=  -2,
	grFileNotFound	=  -3,
	grInvalidDriver    	=  -4,
	grNoLoadMem	=  -5,
	grNoScanMem	=  -6,
	grNoFloodMem	=  -7,
	grFontNotFound	=  -8,
	grNoFontMem	=  -9,
	grInvalidMode	= -10,
	grError 	   	= -11,   /* generic error */
	grIOerror	   	= -12,
	grInvalidFont	= -13,
	grInvalidFontNum  	= -14,
	grInvalidVersion   	= -18
};

enum graphics_drivers { 	/* define graphics drivers */
	DETECT, 		/* requests autodetection */
	CGA, MCGA, EGA, EGA64, EGAMONO, IBM8514,	/* 1 - 6 */
	HERCMONO, ATT400, VGA, PC3270,			/* 7 - 10 */
	CURRENT_DRIVER = -1
};

enum graphics_modes {		/* graphics modes for each driver */
    CGAC0      = 0,  /* 320x200 palette 0; 1 page	*/
    CGAC1      = 1,  /* 320x200 palette 1; 1 page	*/
    CGAC2      = 2,  /* 320x200 palette 2: 1 page	*/
    CGAC3      = 3,  /* 320x200 palette 3; 1 page	*/
    CGAHI      = 4,  /* 640x200 1 page			*/
    MCGAC0     = 0,  /* 320x200 palette 0; 1 page	*/
    MCGAC1     = 1,  /* 320x200 palette 1; 1 page	*/
    MCGAC2     = 2,  /* 320x200 palette 2; 1 page	*/
    MCGAC3     = 3,  /* 320x200 palette 3; 1 page	*/
    MCGAMED    = 4,  /* 640x200 1 page			*/
    MCGAHI     = 5,  /* 640x480 1 page			*/
    EGALO      = 0,  /* 640x200 16 color 4 pages	*/
    EGAHI      = 1,  /* 640x350 16 color 2 pages	*/
    EGA64LO    = 0,  /* 640x200 16 color 1 page 	*/
    EGA64HI    = 1,  /* 640x350 4 color  1 page 	*/
    EGAMONOHI  = 0,  /* 640x350 64K on card, 1 page - 256K on card, 4 pages */
    HERCMONOHI = 0,  /* 720x348 2 pages 		*/
    ATT400C0   = 0,  /* 320x200 palette 0; 1 page	*/
    ATT400C1   = 1,  /* 320x200 palette 1; 1 page	*/
    ATT400C2   = 2,  /* 320x200 palette 2; 1 page	*/
    ATT400C3   = 3,  /* 320x200 palette 3; 1 page	*/
    ATT400MED  = 4,  /* 640x200 1 page			*/
    ATT400HI   = 5,  /* 640x400 1 page			*/
    VGALO      = 0,  /* 640x200 16 color 4 pages	*/
    VGAMED     = 1,  /* 640x350 16 color 2 pages	*/
    VGAHI      = 2,  /* 640x480 16 color 1 page 	*/
    PC3270HI   = 0,  /* 720x350 1 page			*/
    IBM8514LO  = 0,  /* 640x480 256 colors		*/
    IBM8514HI  = 1   /*1024x768 256 colors		*/
};

/* Colors for setpalette and setallpalette */

	#if	!defined(__COLORS)
		#define __COLORS

enum COLORS {
    BLACK,		    /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,		    /* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};
	#endif

enum CGA_COLORS {
    CGA_LIGHTGREEN     = 1,		/* Palette C0 Color Names	*/
    CGA_LIGHTRED       = 2,
    CGA_YELLOW	       = 3,

    CGA_LIGHTCYAN      = 1,		/* Palette C1 Color Names	*/
    CGA_LIGHTMAGENTA   = 2,
    CGA_WHITE	       = 3,

    CGA_GREEN	       = 1,		/* Palette C2 Color Names	*/
    CGA_RED	       = 2,
    CGA_BROWN	       = 3,

    CGA_CYAN	       = 1,		/* Palette C3 Color Names	*/
    CGA_MAGENTA        = 2,
    CGA_LIGHTGRAY      = 3
};


enum EGA_COLORS {
    EGA_BLACK		 =  0,	    /* dark colors */
    EGA_BLUE		 =  1,
    EGA_GREEN		 =  2,
    EGA_CYAN		 =  3,
    EGA_RED		 =  4,
    EGA_MAGENTA 	 =  5,
    EGA_BROWN		 =  20,
    EGA_LIGHTGRAY	 =  7,
    EGA_DARKGRAY	 =  56,     /* light colors */
    EGA_LIGHTBLUE	 =  57,
    EGA_LIGHTGREEN	 =  58,
    EGA_LIGHTCYAN	 =  59,
    EGA_LIGHTRED	 =  60,
    EGA_LIGHTMAGENTA	 =  61,
    EGA_YELLOW		 =  62,
    EGA_WHITE		 =  63
};

enum line_styles {		/* Line styles for get/setlinestyle */
	SOLID_LINE   = 0,
	DOTTED_LINE  = 1,
	CENTER_LINE  = 2,
	DASHED_LINE  = 3,
	USERBIT_LINE = 4,	/* User defined line style */
};

enum line_widths {		/* Line widths for get/setlinestyle */
	NORM_WIDTH  = 1,
	THICK_WIDTH = 3,
};

enum font_names {
	DEFAULT_FONT	= 0,	/* 8x8 bit mapped font */
	TRIPLEX_FONT	= 1,	/* "Stroked" fonts */
	SMALL_FONT	= 2,
	SANS_SERIF_FONT = 3,
	GOTHIC_FONT	= 4
};

	#define HORIZ_DIR	0	/* left to right */
	#define VERT_DIR	1	/* bottom to top */

	#define USER_CHAR_SIZE	0	/* user-defined char size */

enum fill_patterns {		/* Fill patterns for get/setfillstyle */
	EMPTY_FILL,		/* fills area in background color */
	SOLID_FILL,		/* fills area in solid fill color */
	LINE_FILL,		/* --- fill */
	LTSLASH_FILL,		/* /// fill */
	SLASH_FILL,		/* /// fill with thick lines */
	BKSLASH_FILL,		/* \\\ fill with thick lines */
	LTBKSLASH_FILL, 	/* \\\ fill */
	HATCH_FILL,		/* light hatch fill */
	XHATCH_FILL,		/* heavy cross hatch fill */
	INTERLEAVE_FILL,	/* interleaving line fill */
	WIDE_DOT_FILL,		/* Widely spaced dot fill */
	CLOSE_DOT_FILL, 	/* Closely spaced dot fill */
	USER_FILL		/* user defined fill */
};

enum putimage_ops {		/* BitBlt operators for putimage */
	COPY_PUT,		/* MOV */
	XOR_PUT,		/* XOR */
	OR_PUT, 		/* OR  */
	AND_PUT,		/* AND */
	NOT_PUT 		/* NOT */
};

enum text_just {		/* Horizontal and vertical justification
				   for settextjustify */
	LEFT_TEXT	= 0,
	CENTER_TEXT	= 1,
	RIGHT_TEXT	= 2,

	BOTTOM_TEXT	= 0,
     /* CENTER_TEXT	= 1,  already defined above */
	TOP_TEXT	= 2
};


	#define MAXCOLORS 15

struct palettetype {
	unsigned char size;
	signed char colors[MAXCOLORS+1];
};

struct linesettingstype {
	int linestyle;
	unsigned upattern;
	int thickness;
};

struct textsettingstype {
	int font;
	int direction;
	int charsize;
	int horiz;
	int vert;
};

struct fillsettingstype {
	int pattern;
	int color;
};

struct pointtype {
	int x, y;
};

struct viewporttype {
	int left, top, right, bottom;
	int clip;
};

struct arccoordstype {
	int x, y;
	int xstart, ystart, xend, yend;
};

extern void 	   arc(int x, int y, int stangle, int endangle,int radius);
//extern void	   bar(int left, int top, int right, int bottom);
//extern void	   bar3d(int left, int top, int right, int bottom,int depth, int topflag);
extern void	   circle(int x, int y, int radius);
//extern void	   cleardevice( void);
//extern void	   clearviewport( void);
//extern void	   closegraph(void);
///extern void	   detectgraph(int *graphdriver,int *graphmode);
//extern void	   drawpoly(int numpoints, int *polypoints);
extern void	   ellipse(int x, int y, int stangle, int endangle,int xradius, int yradius);
extern void	   fillellipse( int x, int y, int xradius, int yradius );
extern void	   fillpoly(int numpoints, int *polypoints);
extern void	   floodfill(int x, int y, int border);
extern void	   getarccoords(struct arccoordstype *arccoords);
//extern void	   getaspectratio(int *xasp, int *yasp);
//extern int	   getbkcolor(void);
//extern int	   getcolor( void);
//struct palettetype 	   * getdefaultpalette(  void );
//extern char 	   * getdrivername(  void );
//extern void	   getfillpattern(char *pattern);
//extern void	   getfillsettings(struct fillsettingstype *fillinfo);
//extern int	   getgraphmode( void);
//extern void	   getimage(int left, int top, int right, int bottom,void *bitmap);
//extern void	   getlinesettings(struct linesettingstype *lineinfo);
//extern int	   getmaxcolor( void);
//extern int	   getmaxmode( void);
//extern int	   getmaxx( void);
//extern int	   getmaxy( void);
//extern char 	   * getmodename( int mode_number );
//extern void	   getmoderange(int graphdriver, int *lomode, int *himode);
extern unsigned       getpixel(int x, int y);
//extern void	   getpalette(struct palettetype *palette);
//extern int	   getpalettesize(  void );
//extern void	   gettextsettings(struct textsettingstype *texttypeinfo);
//extern void	   getviewsettings(struct viewporttype *viewport);
extern int	           getx( void);
extern int	           gety( void);
//extern void	   graphdefaults( void);
//extern char         *grapherrormsg(int errorcode);
//extern void	   _graphfreemem( void *ptr, unsigned size);
//extern void         *_graphgetmem(unsigned size);
//extern int	   graphresult( void);
//extern unsigned      imagesize(int left, int top, int right, int bottom);
//extern void	   initgraph(int  *graphdriver,int  *graphmode,char *pathtodriver);
//extern int	   installuserdriver( char *name, int (*detect)( void) );
//extern int	   installuserfont( char *name );
extern void	   line(int x1, int y1, int x2, int y2);
extern void	   linerel(int dx, int dy);
extern void	   lineto(int x, int y);
extern void	   moverel(int dx, int dy);
extern void	   moveto(int x, int y);
//extern void	   outtext(char *textstring);
//extern void	   outtextxy(int x, int y, char *textstring);
extern void	   pieslice(int x, int y, int stangle, int endangle,int radius);
extern void	   putimage(int left, int top, void *bitmap, int op);
extern void	   putpixel(int x, int y, int color);
extern void	   rectangle(int left, int top, int right, int bottom);
//extern void	   restorecrtmode(void);
extern void	   sector( int X, int Y, int StAngle, int EndAngle,int XRadius, int YRadius );
//extern void	   setactivepage(int page);
//extern void	   setallpalette(struct palettetype *palette);
//extern void	   setaspectratio( int xasp, int yasp );
//extern void	   setbkcolor(int color);
//extern void	   setcolor(int color);
//extern void	   setfillpattern(char *upattern, int color);
//extern void	   setfillstyle(int pattern, int color);
//extern unsigned      setgraphbufsize(unsigned bufsize);
//extern void	   setgraphmode(int mode);
//extern void	   setlinestyle(int linestyle, unsigned upattern,int thickness);
//extern void	   setpalette(int colornum, int color);
//extern void	   setrgbpalette(int colornum,int red, int green, int blue);
//extern void	   settextjustify(int horiz, int vert);
//extern void	   settextstyle(int font, int direction, int charsize);
//extern void	   setusercharsize(int multx, int divx,int multy, int divy);
//extern void	   setviewport(int left, int top, int right, int bottom,int clip);
//extern void	   setvisualpage(int page);
//extern void	   setwritemode( int mode );
//extern int	   textheight(char *textstring);
//extern int	   textwidth(char *textstring);

/***** graphics drivers *****/



/***** graphics fonts *****/
/*
int	       _Cdecl registerbgifont(void (*font)(void));
int	   registerfarbgifont(void *font);

/* !!	These "functions" are NOT user-callable,   !! */
/* !! they are there just so you can link in fonts !! */
/*
void	       _Cdecl	triplex_font(void);
void	       _Cdecl	  small_font(void);
void	       _Cdecl sansserif_font(void);
void	       _Cdecl	 gothic_font(void);

extern int far _Cdecl	triplex_font_far[];
extern int far _Cdecl	  small_font_far[];
extern int sansserif_font_far[];
extern int far _Cdecl	 gothic_font_far[];*/


#endif
