/* Wazp3D - Alain THELLIER - Paris - FRANCE 							*/
/* Adaptation to AROS from Matthias Rustler							*/
/* Code clean-up and library enhancements from Gunther Nikl					*/
/* LICENSE: GNU General Public License (GNU GPL) for this file				*/

/* This file  contain print/memory functions usually in Wazp3d.c				*/

struct memory3D *firstME=NULL;		/* Tracked memory-allocation			*/

#ifdef WAZP3DDEBUG
void Libprintf(void *string,...);
void Libsprintf(void *buffer,void *string,...);

/*=================================================================*/
void PrintRGBA(UBYTE *RGBA)
{
	if (!Wazp3D->DebugVal.ON) return;
	Libprintf(" RGBA %ld %ld %ld %ld\n",RGBA[0],RGBA[1],RGBA[2],RGBA[3]);
}
/*==================================================================================*/
void pf(float x)		/* emulate printf() from a float %f */
{
LONG high,low,n,size;
UBYTE name[40];

	high=(LONG)(x);
	x=(x-(float)high);
	if(x<0.0) x=-x;
	low =(LONG)(1000000.0*x);
	Libsprintf(name,"%ld.%6ld ",high,low);
	size=strlen(name)-1;
	NLOOP(size)
		if(name[n]==' ') name[n]='0'; 
	Libprintf(name);
}
/*=================================================================*/
void PrintP(struct point3D *P)
{
	if (!Wazp3D->DebugPoint.ON) return;
/*	Libprintf(" P XYZW, %ld, %ld, %ld, %ld, UV, %ld, %ld,",(WORD)P->x,(WORD)P->y,(WORD)(1000.0*P->z),(WORD)(1000.0*P->w),(WORD)(P->u),(WORD)(P->v));*/

	Libprintf(" P XYZ W UV ");
	pf(P->x);
	pf(P->y);
	pf(P->z);
	pf(P->w);
	pf(P->u);
	pf(P->v);
	if (Wazp3D->DebugVal.ON)
		PrintRGBA((UBYTE *)&P->RGBA);
	else
		Libprintf("\n");
}
/*==================================================================================*/
#endif

#include "mymemory.h"
