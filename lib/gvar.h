
extern int COLOR;
extern struct pointtype CurPoint;
extern struct arccoordstype CurArccoords;
#define PI 3.1415926
#define BOOL unsigned char
#define TRUE 0xff
#define FALSE 0
#define NULL 0

/*
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
};*/

#ifndef __VAR_DEF_
	
	#define __VAR_DEF_
	
	int COLOR;
	struct pointtype CurPoint;
	struct arccoordstype CurArccoords;
	
	//#define GET__CUR_POINT(ppoint)\
		//do{ (*(ppoint)).x=CurPoint.x; (*(ppoint)).y=CurPoint.y; }while(0)
	
	#define GET__CUR_ARCCOORDS(pparcc) \
		do{ 	(*(pparcc)).x=CurArccoords.x; (*(pparcc)).y=CurArccoords.y; \
			(*(pparcc)).xstart=CurArccoords.xstart; (*(pparcc)).ystart=CurArccoords.ystart;\
			(*(pparcc)).xend=CurArccoords.xend; (*(pparcc)).yend=CurArccoords.yend;\
		}while(0)
	
	#define SET_CUR_POINT(xc,yc) \
		do { CurPoint.x=(xc); CurPoint.y=(yc); }while(0)

	#define SET_CUR_ARCCOORDS(x0,y0,startx,starty,endx,endy) \
		do{\
		CurArccoords.x=(x0); CurArccoords.y=(y0); \
		CurArccoords.xstart=(startx); CurArccoords.ystart=(starty); \
		CurArccoords.xend=(endx); CurArccoords.yend=(endy); \
		}while(0)
#endif

//angle standardize
#define ANGLE_STANDARDIZE(stangle,endangle) \
do {\
	stangle%=360;\
	if(stangle<0)stangle+=360;\
	endangle%=360;\
	if(endangle<0)endangle+=360;\
}while(0)

#define ARC_CRITIC_POINT_DISPOSE(stangle, endangle, radius, rad, TipPointsLoc, direct, startx, starty, endx, endy) \
do{\
	if (stangle<endangle) direct=0xff;\
		else direct=0;\
	if (stangle<=180 && endangle<=180)TipPointsLoc=BothUp;\
		else if ( (stangle>180) && (endangle>180) )TipPointsLoc=BothDown;\
		else TipPointsLoc=Against;\
	/*map angle to coordinates*/\
	rad=stangle*PI/180;\
	startx=radius*cos(rad);\
	starty=radius*sin(rad);\
	rad=endangle*PI/180;\
    	endx=radius*cos(rad);\
	endy=radius*sin(rad);\
}while(0)

#define ELP_CRITIC_POINT_DISPOSE(stangle, endangle, radius, rad, TipPointsLoc, direct, startx, starty, endx, endy) \
do{\
	if (stangle<endangle) direct=0xff;\
		else direct=0;\
	if (stangle<=180 && endangle<=180)TipPointsLoc=BothUp;\
		else if ( (stangle>180) && (endangle>180) )TipPointsLoc=BothDown;\
		else TipPointsLoc=Against;\
	/*map angle to coordinates*/\
	rad=stangle*PI/180;\
    	radius=a*b/sqrt( b*b*cos(rad)*cos(rad) + a*a*sin(rad)*sin(rad) );\
    	startx=radius*cos(rad);\
    	starty=radius*sin(rad);\
	rad=endangle*PI/180;\
	radius=a*b/sqrt( b*b*cos(rad)*cos(rad) + a*a*sin(rad)*sin(rad) );\
    	endx=radius*cos(rad);\
	endy=radius*sin(rad);\
}while(0)

//static struct s{ char *listhead; char * next; int yvalue; } EThead;
