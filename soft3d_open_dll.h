/* Wazp3D - Alain THELLIER - Paris - FRANCE 							*/
/* Adaptation to AROS from Matthias Rustler							*/
/* Code clean-up and library enhancements from Gunther Nikl					*/
/* LICENSE: GNU General Public License (GNU GPL) for this file				*/

/* This file open/close the soft3d DLL								*/

#include "winuaenative.h"	/* winuaexxx functions*/
/*==================================================================================*/

#define SOFT3D_ClearImageBufferUAE 0
#define SOFT3D_ClearZBufferUAE 1
#define SOFT3D_CreateTextureUAE 2
#define SOFT3D_DoUpdateUAE 3
#define SOFT3D_DrawPrimitiveUAE 4
#define SOFT3D_EndUAE 5
#define SOFT3D_FreeTextureUAE 6
#define SOFT3D_ReadZSpanUAE 7
#define SOFT3D_AllocImageBufferUAE 8
#define SOFT3D_SetBitmapUAE 9
#define SOFT3D_SetClippingUAE 10
#define SOFT3D_SetDrawStateUAE 11
#define SOFT3D_AllocZbufferUAE 12
#define SOFT3D_StartUAE 13
#define SOFT3D_WriteZSpanUAE 14
#define SOFT3D_FlushUAE 15
#define SOFT3D_UpdateTextureUAE 16
#define SOFT3D_DebugUAE 17

UBYTE name0 [] = {"_SOFT3D_ClearImageBufferUAE"};
UBYTE name1 [] = {"_SOFT3D_ClearZBufferUAE"};
UBYTE name2 [] = {"_SOFT3D_CreateTextureUAE"};
UBYTE name3 [] = {"_SOFT3D_DoUpdateUAE"};
UBYTE name4 [] = {"_SOFT3D_DrawPrimitiveUAE"};
UBYTE name5 [] = {"_SOFT3D_EndUAE"};
UBYTE name6 [] = {"_SOFT3D_FreeTextureUAE"};
UBYTE name7 [] = {"_SOFT3D_ReadZSpanUAE"};
UBYTE name8 [] = {"_SOFT3D_AllocImageBufferUAE"};
UBYTE name9 [] = {"_SOFT3D_SetBitmapUAE"};
UBYTE name10[] = {"_SOFT3D_SetClippingUAE"};
UBYTE name11[] = {"_SOFT3D_SetDrawStateUAE"};
UBYTE name12[] = {"_SOFT3D_AllocZbufferUAE"};
UBYTE name13[] = {"_SOFT3D_StartUAE"};
UBYTE name14[] = {"_SOFT3D_WriteZSpanUAE"};
UBYTE name15[] = {"_SOFT3D_FlushUAE"};
UBYTE name16[] = {"_SOFT3D_UpdateTextureUAE"};
UBYTE name17[] = {"_SOFT3D_Debug"};

#define FUNCNB 18
APTR funcnames[FUNCNB]={name0,name1,name2,name3,name4,name5,name6,name7,name8,name9,name10,name11,name12,name13,name14,name15,name16,name17};
ULONG funcptrs[FUNCNB];
ULONG dllbase=0;

#define NLOOP(nbre) for(n=0;n<nbre;n++)
void Libprintf(UBYTE *string, ...);
extern BOOL LibDebug;
/*==================================================================================*/
void OpenSoft3DDLL()
{
BOOL DebugState=LibDebug;
int n;

LibDebug=TRUE;
	Libprintf("OpenSoft3DDLL\n");
	dllbase = winuae_opendll("soft3d.dll");
	if(dllbase == 0)
		{LibDebug=TRUE;LibAlert("Cant open WinUAE/soft3d.dll !"); LibDebug=DebugState; return;} 

	Libprintf("The DLL soft3d.dll is opened :-) (dllbase %ld)\n",dllbase);

	winuae_getnativeaddrall(dllbase,funcnames,funcptrs,FUNCNB);

	NLOOP(FUNCNB)
		if(funcptrs[n]!=0)
		{Libprintf("DLL's function%ld: %ld (from dllbase %ld)\n",n,funcptrs[n],funcptrs[n]-dllbase); }
		else
		{Libprintf("DLL's function%ld: not found ! \n",n); dllbase=0; } 

	if(dllbase!=0)
		{ Libprintf("DLL functions are here :-) \n"); }
	else
		{ Libprintf("DLL fail :-( \n"); dllbase=0; }

}
/*==================================================================================*/
void CloseSoft3DDLL()
{
	Libprintf("CloseSoft3DDLL\n");
	if(dllbase == 0) return;

	winuae_closedll(dllbase);
	Libprintf("The DLL soft3d.dll is closed\n");
}
/*==================================================================================*/


