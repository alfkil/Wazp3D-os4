#ifndef _INLINE_SOFT3D_H
#define _INLINE_SOFT3D_H

#ifndef __INLINE_MACROS_H
#include <inline/macros.h>
#endif

#ifndef SOFT3D_BASE_NAME
#define SOFT3D_BASE_NAME Soft3DBase
#endif

#define SOFT3D_Start(PrefsWazp3D)						LP1  (30,APTR,SOFT3D_Start,APTR,PrefsWazp3D,a1, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_ClearImageBuffer(sc,x,y,large,high,RGBA)		LP6NR(36,SOFT3D_ClearImageBuffer,APTR,sc,a1,UWORD,x,d1,UWORD,y,d2,UWORD,large,d3,UWORD,high,d4,APTR,RGBA,a2, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_ClearZBuffer(sc,fz)						LP2NR(42,SOFT3D_ClearZBuffer,APTR,sc,a1,float,fz,d1, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_CreateTexture(sc,pt,large,high,format,TexFlags)	LP6  (48,APTR,SOFT3D_CreateTexture,APTR,sc,a1,APTR,pt,a2,UWORD,large,d1,UWORD,high,d2,UWORD,format,d3,UBYTE,TexFlags,d4, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_DoUpdate(sc)							LP1  (54,UBYTE,SOFT3D_DoUpdate,APTR,sc,a1, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_DrawPrimitive(sc,p,Pnb,primitive)			LP4NR(60,SOFT3D_DrawPrimitive,APTR,sc,a1,APTR,p,a2,ULONG,Pnb,d1,ULONG,primitive,d2, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_End(sc)								LP1NR(66,SOFT3D_End,APTR,sc,a1, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_FreeTexture(sc,st)						LP2NR(72,SOFT3D_FreeTexture,APTR,sc,a1,APTR,st,a2, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_ReadZSpan(sc,x,y,n,dz)					LP5NR(78,SOFT3D_ReadZSpan,APTR,sc,a1,UWORD,x,d1,UWORD,y,d2,ULONG,n,d3,APTR,dz,a2, ,SOFT3D_BASE_NAME)	  
#define SOFT3D_AllocImageBuffer(sc,large,high)				LP3NR(84,SOFT3D_AllocImageBuffer,APTR,sc,a1,UWORD,large,d1,UWORD,high,d2, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_SetBitmap(sc,bm,bmdata,bmformat,x,y,large,high)	LP8NR(90,SOFT3D_SetBitmap,APTR,sc,a1,APTR,bm,a2,APTR,bmdata,a3,ULONG,bmformat,d1,UWORD,x,d2,UWORD,y,d3,UWORD,large,d4,UWORD,high,d5, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_SetClipping(sc,xmin,xmax,ymin,ymax)			LP5NR(96,SOFT3D_SetClipping,APTR,sc,a1,UWORD,xmin,d1,UWORD,xmax,d2,UWORD,ymin,d3,UWORD,ymax,d4, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_SetDrawState(sc,sta)						LP2NR(102,SOFT3D_SetDrawState,APTR,sc,a1,APTR,sta,a2, ,SOFT3D_BASE_NAME);
#define SOFT3D_AllocZbuffer(sc,large,high)				LP3  (108,APTR,SOFT3D_AllocZbuffer,APTR,sc,a1,UWORD,large,d1,UWORD,high,d2, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_WriteZSpan(sc,x,y,n,dz,mask)				LP6NR(114,SOFT3D_WriteZSpan,APTR,sc,a1,UWORD,x,d1,UWORD,y,d2,ULONG,n,d3,APTR,dz,a2,APTR,mask,a3, ,SOFT3D_BASE_NAME) 
#define SOFT3D_Flush(sc)							LP1NR(120,SOFT3D_Flush,APTR,sc,a1, ,SOFT3D_BASE_NAME)
#define SOFT3D_UpdateTexture(sc,st,pt)					LP3NR(126,SOFT3D_UpdateTexture,APTR,sc,a1,APTR,st,a2,APTR,pt,a3, ,SOFT3D_BASE_NAME)	 
#define SOFT3D_Debug(txt)							LP1NR(132,SOFT3D_Debug,APTR,txt,a1, ,SOFT3D_BASE_NAME)	 


#endif /*  _INLINE_SOFT3D_H  */
