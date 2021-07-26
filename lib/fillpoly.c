//#include <stdlib.h> 
#include "gvar.h"
#include "graphics.h"

struct sNODE{
	int y_up;
	float x_dn;
	float dx;
	struct sNODE *pnext;
	};

struct sBLOCK{
	struct sNODE *pnode;
	int y_dn;
	struct sBLOCK *pnext;
	};

#define NULL 0
#define sNODE_NULL { y_up : 0 , x_dn : 0.0 , dx : 0.0 ,  pnext : NULL }
#define sBLOCK_NULL { pnode : NULL , y_dn : 0 , pnext : NULL }

#define EDGE_NODE_LEN ( sizeof (struct sNODE) )
#define BLOCK_LEN ( sizeof (struct sBLOCK) )

//operations on node of edge list
//p : struct sNODE * p
#define NODE_Y(p) 	( (*(p)) . y_up)
#define NODE_X(p) 	( (*(p)) . x_dn )
#define NODE_DX(p) 	( (*(p)) . dx )
#define NODE_NEXT(p) 	( (*(p)) . pnext )

//operations on block of ET
//p : struct sBLOCK * p
#define BLCK_FRST_NODE(p) 	( (*(p)). pnode )
#define BLCK_Y(p)     		( (*(p)). y_dn )
#define BLCK_NEXT(p)  		( (*(p)). pnext )

//struct sBLOCK * globalET=NULL; //debug in function create_ET() and insert_edge_list()

static void insert_edge_list( struct sBLOCK *plisthead, struct sNODE *newNode);
static void free_edge_list ( struct sBLOCK *plisthead);
static struct sBLOCK * create_ET (int EdgeNum, int *points);

static void __scanET_fillpoly(struct sBLOCK *pET);
static void free_ET(struct sBLOCK *pET);

void 	fillpoly(int num, int *points)
{
	int i,EdgeNum;
	struct sBLOCK *p;
	
	EdgeNum=num-1;
	if( ( p=create_ET(EdgeNum,points) ) == NULL ) return;
	__scanET_fillpoly(p);
	free_ET(p);
}

//insert and sort
//plisthead is a pointer to a list head ,which is a element of a block of ET
static void insert_edge_list( struct sBLOCK *plisthead, struct sNODE *newNode)
{
	struct sNODE *ppre,*pnxt;
	struct sNODE tempListHead=sNODE_NULL; //
	//static int cl, rw=-1; 
	//cl=plisthead-globalET-1;rw++;

	NODE_NEXT(&tempListHead)=BLCK_FRST_NODE(plisthead); // temp list head points to real  list
	ppre=&tempListHead;					//point to the temp list head
	pnxt=NODE_NEXT(ppre);				//point to the first node of  edge list
	////////////////////if the list is empty ,add first node //////////////////////////////////////////////////////////////////////////////////////
	if( pnxt==NULL )	
		{
		NODE_NEXT( newNode )=NULL;
		NODE_NEXT(&tempListHead)=newNode;
		//circle(20+50*rw,20+50*cl,20);
		BLCK_FRST_NODE(plisthead)=NODE_NEXT(&tempListHead); //the list is pointed by real list head 
		return;
		}	
	/////////////////////insert other nodes////////////////////////////////////////////////////////////////////////////////////////////////////////
	while(pnxt!=NULL)
		{
		if ( NODE_X(newNode) < NODE_X(pnxt) )
			{
			//circle(20+50*rw,20+50*cl,20);
			NODE_NEXT(newNode)=pnxt;
			NODE_NEXT(ppre)=newNode;//insert a new node before pnxt
			break;
			}
		else if ( NODE_X(newNode) == NODE_X(pnxt) )
			{
			if ( NODE_DX(newNode) < NODE_DX(pnxt) )
				{
				NODE_NEXT(newNode)=pnxt;
				NODE_NEXT(ppre)=newNode;//insert a new node before pnxt
				//circle(20+50*rw,20+50*cl,20);
				break;
				}
			}
		ppre=pnxt;
		pnxt=NODE_NEXT(pnxt);		
		}
	///////////////////////////////append a node in the last location of the list///////////////////////////////////////////////
	if (pnxt==NULL){
		NODE_NEXT(newNode)=NULL;
		NODE_NEXT(ppre)=newNode;
		//circle(20+50*rw,20+50*cl,20);
		}
		
	BLCK_FRST_NODE(plisthead)=NODE_NEXT(&tempListHead); //the list is pointed by real list head 
}


#define 	INI_EDGE_NODE(x1,y1,x2,y2,p) \
do{\
		/*init the edge node	*/\
		if ( y1 < y2 ){\
			NODE_Y(p)=y2;\
			NODE_X(p)=x1;\
			NODE_DX(p)=(float)(x2-x1)/(float)(y2-y1);\
			}\
		else{\
			NODE_Y(p)=y1;\
			NODE_X(p)=x2;\
			NODE_DX(p)=(float)(x1-x2)/(float)(y1-y2);\
			y1=y2; /*the minimal value*/\
			}	\
}while(0)

// ET is acctrualy an array, which block contains 3 integer. AND it's block also is a node of linked list
//every block of ET contains 1 pointer to edges list, 1 pointer to next and 1 value of x which length is 1 int 

static struct sBLOCK * create_ET(int EdgeNum, int *points)
{
	struct sBLOCK *ET=NULL  ;
	struct sBLOCK *ppre,*pnxt;	//point to the block of ET
	struct sBLOCK * pTop;	//point to the highest used block  of ET
	
	int i;
	int x1,x2,y1,y2;		//two neigbour points of the poly
	struct sNODE *pnode=NULL ;  	
	
	//int rw=-1,cl=0;
	
	ET=( struct sBLOCK* ) malloc( (EdgeNum+1) * BLOCK_LEN ); 	
	if( ET==NULL )return NULL;
	
	//init the ET list
	for(i=0; i< ( EdgeNum + 1 ) ; i++)
		{
		BLCK_FRST_NODE(ET+i)=NULL;
		BLCK_NEXT(ET+i)=NULL;
		BLCK_Y(ET+i)=0;
		}
	//init the head of ET
	pTop=ET;
	//sertch all edges ,and fill the content of ET
	for (i=0; i<EdgeNum; i++)			
		{
		//rw++;
		x1=*( points + i * 2 + 0 );	//x1,x2 are coordinates of two neibour points
		y1=*( points + i * 2 + 1 );	//y1,y2 are coordinates of two neibour points
		x2=*( points + i * 2 + 2 );
		y2=*( points + i * 2 + 3 );
		if (y1==y2)continue;

		//generate one edge node
		pnode=(struct sNODE*)malloc( EDGE_NODE_LEN );
		//malloc node of every edge
		if (pnode==NULL)
			{
			free_ET(ET);
			return NULL;
			}
		INI_EDGE_NODE(x1,y1,x2,y2,pnode);
		
		
		//insert a block into ET and insert the node of edge into edge list headed by the block
		ppre=ET; 			//point to the first block of ET
		pnxt=BLCK_NEXT(ppre);	//point to the second block of ET
		//if(ppre!=NULL && pnxt ==NULL  )circle(20+50*rw,20+50*cl,20);
		while( pnxt!=NULL )
			{
			if( BLCK_Y(pnxt)==y1 ){
							//cl=(pnxt-ET-1); circle(20+50*rw,20+50*cl,20); 				
				insert_edge_list(  pnxt, pnode);	
				break;
				}
			else if ( BLCK_Y(pnxt)>y1 ){
				//////////////////insert a block in ET on pnxt
				pTop++;//"malloc 1 block of ET"
				BLCK_Y(pTop)=y1;
				BLCK_NEXT(ppre)=pTop;
				BLCK_NEXT(pTop)=pnxt; 	//cl=(pTop-ET-1); circle(20+50*rw,20+50*cl,20); 
				insert_edge_list(  pTop, pnode);
				break;	
				}
			ppre=pnxt;
			pnxt=BLCK_NEXT(pnxt);
			}
		if( pnxt==NULL){
			////////////////////////insert a block in ET on pnxt
			pTop++;//"malloc 1 block of ET"
			BLCK_Y(pTop)=y1;
			BLCK_NEXT(ppre)=pTop;
			BLCK_NEXT(pTop)=NULL; 		//cl=(pTop-ET-1); circle(20+50*rw,20+50*cl,20);
			insert_edge_list( pTop , pnode);
			}
		
		}
		
	return (ET);

}





static void free_ET(struct sBLOCK *pET)
{
	struct sBLOCK *p;
	p=BLCK_NEXT(pET);
	while(p!=NULL)
		{
		free_edge_list( p );	
		p=BLCK_NEXT(p);
		}
	free(pET);
}


static void free_edge_list ( struct sBLOCK *plisthead)
{	
	struct sNODE  *ppre,*pnxt;
	if ( BLCK_FRST_NODE(plisthead)==NULL )return; 	//edge list is empty
	ppre=BLCK_FRST_NODE(plisthead);
	pnxt=NODE_NEXT(ppre);
	while(pnxt!=NULL)
		{
		free(ppre);
		ppre=pnxt;
		pnxt=NODE_NEXT(pnxt);
		}
	free(ppre);//free the last one
}


//this is for debugging
/*
static void __scanET_fillpoly(struct sBLOCK *pET)
{
	int i=0,col=0;
	struct sNODE * pLstNod; 	//point to node of edge list
	struct sBLOCK * pBlck; 	//point to block of ET
	
	pBlck=BLCK_NEXT(pET);
	//pLstNod=BLCK_FRST_NODE(pBlck);
	while(pBlck!=NULL)
		{
		pLstNod=BLCK_FRST_NODE(pBlck);	
		while(pLstNod!=NULL)
			{
			circle( 20+50*i, 20+50*col, 20);
			i++;
			pLstNod=NODE_NEXT(pLstNod);
			}
		i=0;
		col++;
		pBlck=BLCK_NEXT(pBlck);
		}
}*/

//delete all edges which field Y equals y
#define FREE_NODES(pAEThead, y, pr, pn)\
do{\
	pr=(char*)&pAEThead;\
	if ( *(int*)pr !=NULL )\
		{ \
		pn= (char*)(*pr);\
		while(pn!=NULL){\
		if( NODE_Y(pn)==y ){\
			NODE_NEXT(pr)=NODE_NEXT(pn);\
			free( pn);\
			}\
		else{\
			pr=pn;\
			pn=(char*)NODE_NEXT(pn); \
			}\
		}\
}while(0)\

static void __scanET_fillpoly(struct sBLOCK *pET)
{
	struct sBLOCK AET=sBLOCK_NULL;
	struct sNODE TmpListHead=sNODE_NULL;
	struct sBLOCK * BlockIndex;		//point to a block of ET ,which is edge list head
	struct sNODE  * pr , *pn ; 		//point to nodes to be deleted from AET
	struct sNODE * p;			//point to nodes ( in edge list ) to be inserted into AET
	int y; 
	int x1,x2;
	//int ydisp=-1, xdisp=0, a=0;
	
	BlockIndex=BLCK_NEXT(pET); 	//point to the second block of ET , that is the first edge list in ET 
	y=BLCK_Y(BlockIndex);		// ymin is the minimal value
	//if(y==100)circle(100,200,30);
	//scan 
	for(;y<=600;y++)
		{
		if (BlockIndex==NULL && BLCK_FRST_NODE(&AET)==NULL )break;
		//delete all edges in AET which field y_up value equals y
		if ( BLCK_FRST_NODE(&AET)!=NULL )
			{
			NODE_NEXT(&TmpListHead)=BLCK_FRST_NODE(&AET);//make TmpListHead to be the head of edge list
			pr=&TmpListHead; 		  
			pn=NODE_NEXT(pr);
			while(pn!=NULL){
				if( NODE_Y(pn)==y ){
					NODE_NEXT(pr)=NODE_NEXT(pn);
					free( pn);
					pn=NODE_NEXT(pn);
					continue;
					}
				pr=pn;
				pn=NODE_NEXT(pn);
				}
			BLCK_FRST_NODE(&AET)=NODE_NEXT(&TmpListHead);
			}	
		//insert edge nodes in ET into AET
		if (BlockIndex!=NULL && y==BLCK_Y(BlockIndex) )
			{
			//ydisp+=1;	xdisp=0;	
			//seartch edge list , insert elements of ET into AET
			pr=BLCK_FRST_NODE(BlockIndex);
			pn=NODE_NEXT(pr);
			BLCK_FRST_NODE(BlockIndex)=NULL;	//delete all edges of some list in ET	
			while( pn!=NULL ){
				insert_edge_list(&AET,pr);
				pr=pn;
				pn=NODE_NEXT(pn);
				//circle(20+50*xdisp,20+50*ydisp,20); xdisp++;
				}
			insert_edge_list(&AET,pr);				
			BlockIndex=BLCK_NEXT(BlockIndex);
			}
		//seartch AET, fill with the color
		p=BLCK_FRST_NODE(&AET);
		while( p!= NULL)
			{
			//if(y==100)circle(100,200,30);
			x1=NODE_X(p); //make int from float
			p=NODE_NEXT(p);
			x2=NODE_X(p);
			while( x1<=x2 )
				{
				putpixel(x1,y,COLOR);
				x1++;
				}
			p=NODE_NEXT(p);
			}
		//seartch AET , calculate concurrent point of next san line
		p=BLCK_FRST_NODE(&AET);
		while( p!= NULL)
			{
			NODE_X(p)+=NODE_DX(p);
			p=NODE_NEXT(p);
			}
		}
}
