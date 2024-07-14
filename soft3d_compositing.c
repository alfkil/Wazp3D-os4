#if defined(OS4COMPOSITING)
#include <graphics/composite.h>
#include <graphics/rpattr.h>
#include <libraries/Picasso96.h>
#include <proto/Picasso96API.h>
/*================================================================*/
#define TEXCOLSIZE 256				/* texture with vert colors	*/
#define WHITE32  ((255<<24)+(255<<16)+(255<<8)+(255)) 
#define CREM(message) if(Wazp3D->DebugBlendFunction.ON) printf(#message"\n");
/*================================================================*/
struct XYSTW_Vertex3D { 
float x, y; 
float s, t, w; 
}; 
/*================================================================*/
void COMP3D_DoUpdate(void *sc)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_DoUpdate);
	return; 			/* already done Soft3D side */
}
/*==================================================================*/
void COMP3D_Start(void *sc)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_Start);
	Wazp3D->DoMipMaps.ON=FALSE;			/* not possible via compositing */
	Wazp3D->UseAntiImage.ON=FALSE;

	if(!IP96)
	{
		printf("Could not open the Picasso96API library's main interface\n");
		SC->UseHard=FALSE;return;
	}

	SC->colorsbm =AllocBitMapTags(TEXCOLSIZE, TEXCOLSIZE, 32,
		BMATags_PixelFormat, PIXF_A8R8G8B8,
		BMATags_Displayable, TRUE,
		TAG_DONE, NULL);

	VAR(SC->colorsbm)
}
/*==================================================================*/
void COMP3D_ClearImageBuffer(void *sc,unsigned short x,unsigned short y,unsigned short large,unsigned short high,void *rgba)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_ClearImageBuffer);
	return; 			/* TODO: implement it with compositing */
}
/*==================================================================*/
void COMP3D_ClearZBuffer(void *sc,float fz)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_ClearZBuffer);
	return; 			/* not possible via compositing */
}
/*==================================================================*/
void UpdateBmTexture(struct SOFT3D_texture *ST)
{
register union rgba3D Color0;
register union rgba3D Color1;
register union rgba3D Color2;
register union rgba3D Color3;
register ULONG *ARGB32;		/* bm memory  */
register ULONG *RGBA32;		/* tex memory  */
register UBYTE *RGB;		/* tex memory  */
struct RenderInfo renderInfo;
LONG bmHandle;					/* to directly write to bm */
// APTR bmHandle;
ULONG size,n;
ULONG large;

	SFUNCTION(UpdateBmTexture);
	if(ST->bm==NULL) return;

	bmHandle=p96LockBitMap(ST->bm, (UBYTE*)&renderInfo, sizeof(renderInfo));

	// ULONG *tmp;
	// bmHandle = LockBitMapTags(ST->bm,
	// 	LBM_BaseAddress, &tmp,
	// 	LBM_BytesPerRow, &large, // this, apparently, doesn't work
	// 	TAG_DONE);
		
	if(bmHandle==0)
		return;

// DebugPrintF("LBM_BaseAddress : 0x%lx\n", tmp);
// DebugPrintF("LBM_BytesPerRow[gfx] : 0x%lx\n", large);

	ARGB32 = (ULONG*)renderInfo.Memory;
	// ARGB32 = tmp;
	// large /= 4;
	
	large = p96GetBitMapAttr(ST->bm, P96BMA_BYTESPERROW)/4;
// DebugPrintF("LBM_BytesPerRow[p96] : 0x%lx\n", large);

	RGB=ST->pt;
	RGBA32=(ULONG*)ST->pt;
	size=large*ST->high;

	size=size/4;
	Color0.B.RGBA[0]=255;
	Color1.B.RGBA[0]=255;
	Color2.B.RGBA[0]=255;
	Color3.B.RGBA[0]=255;

	if(ST->format==W3D_R8G8B8)
	NLOOP(size)
		{
		Color0.B.RGBA[1]=RGB[0];	
		Color0.B.RGBA[2]=RGB[1];	
		Color0.B.RGBA[3]=RGB[2];

		Color1.B.RGBA[1]=RGB[3];	
		Color1.B.RGBA[2]=RGB[4];	
		Color1.B.RGBA[3]=RGB[5];

		Color2.B.RGBA[1]=RGB[6];	
		Color2.B.RGBA[2]=RGB[7];	
		Color2.B.RGBA[3]=RGB[8];	

		Color3.B.RGBA[1]=RGB[9];	
		Color3.B.RGBA[2]=RGB[10];	
		Color3.B.RGBA[3]=RGB[11];

		ARGB32[0]=Color0.L.RGBA32;
		ARGB32[1]=Color1.L.RGBA32;
		ARGB32[2]=Color2.L.RGBA32;
		ARGB32[3]=Color3.L.RGBA32;
	
		ARGB32+=4;
		RGB+=12;
		}


	if(Wazp3D->TexMode.ON!=4)					/* If not set to "No blending" */
	if(ST->format==W3D_R8G8B8A8)
	NLOOP(size)
		{
		Color0.L.RGBA32=RGBA32[0];
		Color1.L.RGBA32=RGBA32[1];		
		Color2.L.RGBA32=RGBA32[2];
		Color3.L.RGBA32=RGBA32[3];
		Color0.L.RGBA32=((((ULONG)Color0.B.RGBA[3])<<24)+(Color0.L.RGBA32>>8));
		Color1.L.RGBA32=((((ULONG)Color1.B.RGBA[3])<<24)+(Color1.L.RGBA32>>8));
		Color2.L.RGBA32=((((ULONG)Color2.B.RGBA[3])<<24)+(Color2.L.RGBA32>>8));
		Color3.L.RGBA32=((((ULONG)Color3.B.RGBA[3])<<24)+(Color3.L.RGBA32>>8));
		ARGB32[0]=Color0.L.RGBA32;
		ARGB32[1]=Color1.L.RGBA32;
		ARGB32[2]=Color2.L.RGBA32;
		ARGB32[3]=Color3.L.RGBA32;
		RGBA32+=4;
		ARGB32+=4;
		}

	if(Wazp3D->TexMode.ON==4)					/* If set to "No blending" */
	if(ST->format==W3D_R8G8B8A8)
	NLOOP(size)
		{
		Color0.L.RGBA32=RGBA32[0];
		Color1.L.RGBA32=RGBA32[1];		
		Color2.L.RGBA32=RGBA32[2];
		Color3.L.RGBA32=RGBA32[3];
		Color0.L.RGBA32=((((ULONG)255)<<24)+(Color0.L.RGBA32>>8));
		Color1.L.RGBA32=((((ULONG)255)<<24)+(Color1.L.RGBA32>>8));
		Color2.L.RGBA32=((((ULONG)255)<<24)+(Color2.L.RGBA32>>8));
		Color3.L.RGBA32=((((ULONG)255)<<24)+(Color3.L.RGBA32>>8));
		ARGB32[0]=Color0.L.RGBA32;
		ARGB32[1]=Color1.L.RGBA32;
		ARGB32[2]=Color2.L.RGBA32;
		ARGB32[3]=Color3.L.RGBA32;
		RGBA32+=4;
		ARGB32+=4;
		}

	// p96UnlockBitMap(ST->bm,bmHandle);
	UnlockBitMap(bmHandle);
}
/*==================================================================*/
void COMP3D_CreateTexture(void *sc,void *st,unsigned char *pt,unsigned short large,unsigned short high,unsigned short format,unsigned char TexFlags)
{
struct SOFT3D_context *SC=sc;
struct SOFT3D_texture *ST=st;

	SFUNCTION(COMP3D_CreateTexture);

	ST->bm = AllocBitMapTags(large, high, 32,
		BMATags_Displayable, TRUE,
		BMATags_PixelFormat, PIXF_A8R8G8B8,
		TAG_DONE);

	if(!ST->bm) return;
	
VAR(ST->bm)
	UpdateBmTexture(ST);
}
/*==================================================================*/
void SetP(struct point3D *P,UBYTE r, UBYTE g, UBYTE b, UBYTE a)
{
	P->RGBA[0]=r;
	P->RGBA[1]=g;
	P->RGBA[2]=b;
	P->RGBA[3]=a;
}
/*==================================================================*/
void SetColor(struct SOFT3D_context *SC,UBYTE *ARGB, UBYTE  *RGBA)
{

		if(!SC->state.UseTex)
		{
		ARGB[0]=RGBA[3];
		ARGB[1]=RGBA[0];
		ARGB[2]=RGBA[1];
		ARGB[3]=RGBA[2];
		return;
		}

		ARGB[0]=255/3;
		ARGB[1]=RGBA[0];
		ARGB[2]=RGBA[1];
		ARGB[3]=RGBA[2];
		return;

}
/*==================================================================*/
void SrcColorToSrcAlpha(struct SOFT3D_texture *ST)
{
UBYTE *Image8;				/* bm memory  */
LONG bmHandle;					/* to directly write to bm */
ULONG xoffset,x,y;
UBYTE *ARGB;
struct RenderInfo renderInfo;

CREM(SrcColorToSrcAlpha)
	if(ST->bm==NULL) return;

	if(ST->format!=W3D_R8G8B8)
		return;

	if(ST->TexFlags & 4)
		return;

	SFUNCTION(SrcColorToSrcAlpha);
	bmHandle=p96LockBitMap(ST->bm, (UBYTE*)&renderInfo, sizeof(renderInfo));
	if(bmHandle==0)
		return;
	Image8=renderInfo.Memory;
	xoffset= p96GetBitMapAttr(ST->bm, P96BMA_BYTESPERROW) - (ST->large*ST->bits/8);
xoffset=0;
	ARGB=Image8;

	YLOOP(ST->high)
	{
	XLOOP(ST->large)
		{
		ARGB[0]=(ARGB[1]+ARGB[2]+ARGB[3])/3;  /* store color average level in alpha */
		ARGB+=4;
		}
	ARGB+=xoffset;
	}

	p96UnlockBitMap(ST->bm,bmHandle);
	ST->TexFlags=(ST->TexFlags | 4);
}
/*==================================================================*/
void OneMinusSrcColorToSrcAlpha(struct SOFT3D_texture *ST)
{
UBYTE *Image8;				/* bm memory  */
LONG bmHandle;					/* to directly write to bm */
ULONG xoffset,x,y;
UBYTE *ARGB;
struct RenderInfo renderInfo;

CREM(OneMinusSrcColorToSrcAlpha)
	if(ST->bm==NULL) return;

	if(ST->format!=W3D_R8G8B8)
		return;

	if(ST->TexFlags & 8)
		return;

	SFUNCTION(SrcColorToSrcAlpha);
	bmHandle=p96LockBitMap(ST->bm, (UBYTE*)&renderInfo, sizeof(renderInfo));
	if(bmHandle==0)
		return;
	Image8=renderInfo.Memory;
	xoffset= p96GetBitMapAttr(ST->bm, P96BMA_BYTESPERROW) - (ST->large*ST->bits/8);
xoffset=0;
	ARGB=Image8;

	YLOOP(ST->high)
	{
	XLOOP(ST->large)
		{
		ARGB[0]=255-(ARGB[1]+ARGB[2]+ARGB[3])/3;  /* store 1-color average level in alpha */
		ARGB+=4;
		}
	ARGB+=xoffset;
	}

	p96UnlockBitMap(ST->bm,bmHandle);
	ST->TexFlags=(ST->TexFlags | 8);
}
/*==================================================================*/
void COMP3D_DrawTriangles(void *sc,void *p,unsigned long Pnb)
{
struct SOFT3D_context *SC=sc;
struct SOFT3D_texture *ST=SC->state.ST;
struct RenderInfo renderInfo;
struct point3D *P=p;
UBYTE TrisHided[MAXPRIM/3];
struct XYSTW_Vertex3D *V;
ULONG i,j,TRInb,VisTRInb;
ULONG error;
ULONG BlendMode;
LONG x,y,high,large;
ULONG *ARGB32;
ULONG  ARGB[3];
UBYTE *Image8;				/* bm memory  */
LONG bmHandle;					/* to directly write to bm */
BOOL FaceCCW;
WORD s,t;
void *colorsbm;
ULONG bytelarge;
ULONG gouraud;
BOOL modulate;
UBYTE WhiteColored;
float PIXPOS1=2.52;
float PIXPOS2=3.52;
float uresize,vresize;
struct point3D PolyMin;
struct point3D PolyMax;
ULONG ColorsR=0;
ULONG ColorsG=0;
ULONG ColorsB=0;
ULONG ColorsA=0;
union rgba3D Color;
BOOL ColorChange;
UBYTE SrcFunc,DstFunc;
ULONG flags;
float  SrcA,DstA,ColorA;
ULONG  SrcAfix,DstAfix;
BOOL coloring;

	SFUNCTION(COMP3D_DrawTriangles);

	if(Pnb>MAXPRIM)
		{ REM(maxprim) ; return;}

	x=SC->ClipMin.x;
	y=SC->ClipMin.y;
	large=SC->ClipMax.x-SC->ClipMin.x+1;
 	high =SC->ClipMax.y-SC->ClipMin.y+1;
	TRInb=Pnb/3;

VAR(SC->bm)
VAR(x)
VAR(y)
VAR(high)
VAR(large)
VAR(Pnb)
VAR(TRInb)
VAR(ST)
if(ST!=NULL)
	VAR(ST->bm)
VAR(SC->state.BlendMode)
VAR(SC->yoffset)
	VAR(SC->colorsbm)






/* Pass0 do cullling = remove hidden triangles */
	V= (struct XYSTW_Vertex3D *) SC->HC.V;
	P=p;
	VisTRInb=0;
	JLOOP(TRInb)
		{
		TrisHided[j]=FALSE;
		FaceCCW= ((P[1].x - P[0].x)*(P[2].y - P[0].y)-(P[2].x - P[0].x)*(P[1].y - P[0].y) <  0.0); /* formula from TinyGL */

		if(SC->state.CullingMode==W3D_CCW)
		if(!FaceCCW)
			TrisHided[j]=TRUE;

		if(SC->state.CullingMode==W3D_CW)
		if(FaceCCW)
			TrisHided[j]=TRUE;

		if(TrisHided[j]==FALSE)
			VisTRInb++;
		P=P+3;
		}

VAR(VisTRInb)
	if(!SC->state.UseTex)
		{REM(no texturing) ; goto pass2;}

	if(ST->bm==NULL) return;

/* pass1 remove texture-repeat */
	P=p;
	JLOOP(TRInb)
	{
	PolyMin.u=PolyMax.u=P->u;
	PolyMin.v=PolyMax.v=P->v;

		ILOOP(3)
		{
		if (P[i].u < PolyMin.u)	PolyMin.u=P[i].u;
		if (P[i].v < PolyMin.v)	PolyMin.v=P[i].v;
		if (PolyMax.u < P[i].u)	PolyMax.u=P[i].u;
		if (PolyMax.v < P[i].v)	PolyMax.v=P[i].v;
		}

		PolyMin.u=FFLOOR(PolyMin.u);
		PolyMin.v=FFLOOR(PolyMin.v);
		PolyMax.u=PolyMax.u-PolyMin.u;
		PolyMax.v=PolyMax.v-PolyMin.v;

		ILOOP(3)
		{
		P[i].u=P[i].u - PolyMin.u;
		P[i].v=P[i].v - PolyMin.v;
		if(1.0 < PolyMax.u) P[i].u=P[i].u/PolyMax.u;
		if(1.0 < PolyMax.v) P[i].v=P[i].v/PolyMax.v;
		}
	P=P+3;
	}

/* Pass1 do texture: get vertices & compute average color */
	V= (struct XYSTW_Vertex3D *) SC->HC.V;
	P=p;
	uresize=(float)(ST->large-0.001);
	vresize=(float)(ST->high -0.001);
	ColorChange=FALSE;
	JLOOP(TRInb)
	{
	if(!TrisHided[j])
	{
		ILOOP(3)
		{
		V [i].x =P[i].x; 		
		V [i].y =P[i].y;

		V [i].s =P[i].u*uresize;
		V [i].t =P[i].v*vresize;
		V [i].w=1.0;

		if(SC->state.PerspMode!=0)	
		{
		V [i].w=P[i].w;
		V [i].s=V [i].s*V[i].w;
		V [i].t=V [i].t*V[i].w;
		}

		ColorsR=ColorsR+P[i].RGBA[0];
		ColorsG=ColorsG+P[i].RGBA[1];
		ColorsB=ColorsB+P[i].RGBA[2];
		ColorsA=ColorsA+P[i].RGBA[3];
		
		if(P->RGBA[0]!=P[i].RGBA[0])
			ColorChange=TRUE;
		if(P->RGBA[1]!=P[i].RGBA[1])
			ColorChange=TRUE;
		if(P->RGBA[2]!=P[i].RGBA[2])
			ColorChange=TRUE;
		if(P->RGBA[3]!=P[i].RGBA[3])
			ColorChange=TRUE;
		if (Wazp3D->DebugPoint.ON) 		printf("XY %f %f UVW %f %f %f\n",V [i].x,V [i].y,V [i].s,V [i].t,V [i].w);	
		}
	V=V+3;
	}
	P=P+3;
	}

	Color.B.RGBA[0]=ColorsA/(VisTRInb*3);
	Color.B.RGBA[1]=ColorsR/(VisTRInb*3);
	Color.B.RGBA[2]=ColorsG/(VisTRInb*3);
	Color.B.RGBA[3]=ColorsB/(VisTRInb*3);
	WhiteColored=( Color.L.RGBA32 == WHITE32 );

	BlendMode=9999;			/* default */

	if(SC->state.BlendMode==BLENDREPLACE)
		BlendMode=BLENDREPLACE;

	if(SC->state.BlendMode==BLENDALPHA)
		BlendMode=BLENDALPHA ;

/*  Replace specials blendmodes */
	if(SC->state.BlendMode==BLENDFASTALPHA)
		BlendMode=BLENDALPHA ;

	if(SC->state.BlendMode==BLENDNOALPHA)
		BlendMode=BLENDREPLACE;

	if(SC->state.BlendMode==BLENDCHROMA)
		BlendMode=(W3D_ONE*16 + W3D_ONE);		/* this is not a chromatest but looks nice too */

	if(SC->state.BlendMode==(W3D_SRC_ALPHA*16 + W3D_ONE))
		BlendMode=(W3D_ONE*16 + W3D_ONE);		/* this is not a chromatest but looks nice too */


	if(BlendMode==BLENDALPHA)
	if(ST->format==W3D_R8G8B8)					/* wants alpha with a solid tex ? */
		BlendMode=BLENDREPLACE;

	if(Wazp3D->UseFiltering.ON)
		flags=COMPFLAG_HardwareOnly | COMPFLAG_SrcFilter;
	else
		flags=COMPFLAG_HardwareOnly;

	modulate=(SC->state.TexEnvMode==W3D_MODULATE);

	if(WhiteColored)
		modulate=FALSE;

	SrcFunc=SC->state.BlendMode  /  16;
	DstFunc=SC->state.BlendMode % 16;

VAR(SrcFunc)
VAR(DstFunc)

	SrcA=DstA=1.0; 
/* if modulating then we put  average-color's  alpha to SrcA*/
	if(modulate)
		SrcA=((float)Color.B.RGBA[0])/255.0;
	if(SrcFunc== W3D_ONE_MINUS_SRC_ALPHA)
		SrcA=1.0 - SrcA;
	if(DstFunc== W3D_SRC_ALPHA)
		DstA=SrcA;
	if(DstFunc== W3D_ONE_MINUS_SRC_ALPHA)
		DstA=1.0 - SrcA;

	SrcAfix=(SrcA*65536.0);
	DstAfix=(DstA*65536.0);

CREM(CompositeTags pass 1)
	if(BlendMode==BLENDREPLACE)
	{
	if(Wazp3D->DebugBlendFunction.ON)
		printf("COMP3D:BlendMode: REPLAC Src%d Dst%d modulate%d WhiteColored%d ColorChange%d ARGB %d %d %d %d SrcA %2.2f DstA %2.2f\n",SrcFunc,DstFunc,modulate, WhiteColored, ColorChange,Color.B.RGBA[0],Color.B.RGBA[1],Color.B.RGBA[2],Color.B.RGBA[3],SrcA,DstA);	


		error = CompositeTags(COMPOSITE_Src, 
			ST->bm,SC->bm,
			COMPTAG_VertexArray, SC->HC.V, 
			COMPTAG_VertexFormat,COMPVF_STW0_Present,
		    	COMPTAG_NumTriangles,VisTRInb,
     			COMPTAG_DestX,x,
     			COMPTAG_DestY,y,
        		COMPTAG_DestWidth ,large,
     			COMPTAG_DestHeight,high,
			COMPTAG_OffsetY,SC->yoffset,
		    	COMPTAG_Flags,flags|COMPFLAG_IgnoreDestAlpha,
		    	TAG_DONE);
	}

	if(BlendMode==BLENDALPHA)
	{
	if(Wazp3D->DebugBlendFunction.ON)
		printf("COMP3D:BlendMode: ALPHA Src%d Dst%d modulate%d WhiteColored%d ColorChange%d ARGB %d %d %d %d SrcA %2.2f DstA %2.2f\n",SrcFunc,DstFunc,modulate, WhiteColored, ColorChange,Color.B.RGBA[0],Color.B.RGBA[1],Color.B.RGBA[2],Color.B.RGBA[3],SrcA,DstA);


		error = CompositeTags(COMPOSITE_Src_Over_Dest, 
			ST->bm,SC->bm,
			COMPTAG_VertexArray, SC->HC.V, 
			COMPTAG_VertexFormat,COMPVF_STW0_Present,
		    	COMPTAG_NumTriangles,VisTRInb,
     			COMPTAG_DestX,x,
      			COMPTAG_DestY,y,
        		COMPTAG_DestWidth ,large,
      			COMPTAG_DestHeight,high,
			COMPTAG_OffsetY,SC->yoffset,
			COMPTAG_SrcAlpha  ,SrcAfix,
	    		COMPTAG_DestAlpha,DstAfix,
		    	COMPTAG_Flags, flags|COMPFLAG_IgnoreDestAlpha ,
		    	TAG_DONE);
	}

	if(BlendMode==(W3D_ONE*16 + W3D_ONE))	
	{
	if(Wazp3D->DebugBlendFunction.ON)
		printf("COMP3D:BlendMode: ONEONE Src%d Dst%d modulate%d WhiteColored%d ColorChange%d ARGB %d %d %d %d SrcA %2.2f DstA %2.2f\n",SrcFunc,DstFunc,modulate, WhiteColored, ColorChange,Color.B.RGBA[0],Color.B.RGBA[1],Color.B.RGBA[2],Color.B.RGBA[3],SrcA,DstA);

		error = CompositeTags(COMPOSITE_Plus, 
			ST->bm,SC->bm,
			COMPTAG_VertexArray, SC->HC.V, 
			COMPTAG_VertexFormat,COMPVF_STW0_Present,
		    	COMPTAG_NumTriangles,VisTRInb,
     			COMPTAG_DestX,x,
      			COMPTAG_DestY,y,
        		COMPTAG_DestWidth ,large,
      			COMPTAG_DestHeight,high,
			COMPTAG_OffsetY,SC->yoffset,
			COMPTAG_SrcAlpha  ,SrcAfix,
	    		COMPTAG_DestAlpha,DstAfix,	
		    	COMPTAG_Flags, flags|COMPFLAG_IgnoreDestAlpha ,
		    	TAG_DONE);
	}

	
	if(BlendMode==9999)	
	{
		if(Wazp3D->DebugBlendFunction.ON)
		printf("COMP3D:BlendMode: OTHER Src%d Dst%d modulate%d WhiteColored%d ColorChange%d ARGB %d %d %d %d SrcA %2.2f DstA %2.2f\n",SrcFunc,DstFunc,modulate, WhiteColored, ColorChange,Color.B.RGBA[0],Color.B.RGBA[1],Color.B.RGBA[2],Color.B.RGBA[3],SrcA,DstA);	
	if(ST->format==W3D_R8G8B8)		/* src got no alpha */
	{
	if(SrcFunc== W3D_SRC_ALPHA)
		SrcFunc=W3D_SRC_COLOR;
	if(DstFunc== W3D_SRC_ALPHA)
		DstFunc=W3D_SRC_COLOR;

	if(SrcFunc== W3D_ONE_MINUS_SRC_ALPHA)
		SrcFunc=W3D_ONE_MINUS_SRC_COLOR;
	if(DstFunc== W3D_ONE_MINUS_SRC_ALPHA)
		DstFunc=W3D_ONE_MINUS_SRC_COLOR;
	}

	if(SrcFunc==W3D_SRC_COLOR)
		SrcColorToSrcAlpha(ST);

	if(DstFunc==W3D_ONE_MINUS_SRC_COLOR)
		SrcColorToSrcAlpha(ST);

	if(SrcFunc==W3D_ONE_MINUS_SRC_COLOR)
		OneMinusSrcColorToSrcAlpha(ST);

	if(DstFunc==W3D_SRC_COLOR)
		OneMinusSrcColorToSrcAlpha(ST);

		error = CompositeTags(COMPOSITE_Src_Over_Dest, 
			ST->bm,SC->bm,
			COMPTAG_VertexArray, SC->HC.V, 
			COMPTAG_VertexFormat,COMPVF_STW0_Present,
		    	COMPTAG_NumTriangles,VisTRInb,
     			COMPTAG_DestX,x,
     			COMPTAG_DestY,y,
        		COMPTAG_DestWidth ,large,
     			COMPTAG_DestHeight,high,
			COMPTAG_OffsetY,SC->yoffset,
			COMPTAG_SrcAlpha  ,SrcAfix,
	    		COMPTAG_DestAlpha,DstAfix,
		    	COMPTAG_Flags, flags|COMPFLAG_IgnoreDestAlpha ,
		    	COMPTAG_Flags, flags,
		    	TAG_DONE);
	}

		if(error != COMPERR_Success)
			REM(CompositeTags error);

	if(SC->state.TexEnvMode==W3D_REPLACE)
		return;

pass2:
	coloring=(!SC->state.UseTex);				/* If no tex then only draw colored triangles */

	if(coloring)
		{
		CREM(colors only)
		}

	if(modulate)
	if(SC->state.UseTex)					/* then mix drawn texture with colored triangles */
	if(BlendMode==BLENDREPLACE)				/* can draw the colors only upside a solid texture */
		{
		CREM(colorize solid texs)
		coloring=TRUE;
		}

	if(modulate)
	if(SC->state.UseTex)					/* then mix drawn texture with colored triangles */
	if(Wazp3D->DebugSepiaImage.ON)
		{
		CREM(colorize transp texs)
		coloring=TRUE;
		}


	if(!coloring) 
		return;

	if(SC->colorsbm==NULL) 
		return;

	CREM(do colors )	
	if(SC->state.UseGouraud)
		gouraud=COMPFLAG_SrcFilter;
	else
		gouraud=0;


	V= (struct XYSTW_Vertex3D *) SC->HC.V;
	P=p;
	colorsbm=SC->colorsbm;
	bmHandle=p96LockBitMap(colorsbm, (UBYTE*)&renderInfo, sizeof(renderInfo));
	if(bmHandle==0)
		return;
	Image8=renderInfo.Memory;
	bytelarge=p96GetBitMapAttr(colorsbm, P96BMA_BYTESPERROW);
	i=0;

	JLOOP(TRInb)
	{
	if(!TrisHided[j]) 
		{

		s=i % (TEXCOLSIZE/4);
		t=i / (TEXCOLSIZE/4);
		s=s*4;
		t=t*4;

		SetColor(SC,(UBYTE*)&ARGB[0], P[0].RGBA);
		SetColor(SC,(UBYTE*)&ARGB[1], P[1].RGBA);
		SetColor(SC,(UBYTE*)&ARGB[2], P[2].RGBA);

		ARGB32=(ULONG*)(Image8+bytelarge*t+s*4);		/* pixel at 0 0 */
		ARGB32[0]=ARGB[0];
		ARGB32[1]=ARGB[0];
		ARGB32[2]=ARGB[0];
		ARGB32[3]=ARGB[1];
		ARGB32[4]=ARGB[1];
		ARGB32[5]=ARGB[1];
		ARGB32+=bytelarge/4;

		ARGB32[0]=ARGB[0];
		ARGB32[1]=ARGB[0];
		ARGB32[2]=ARGB[0];
		ARGB32[3]=ARGB[1];
		ARGB32[4]=ARGB[1];
		ARGB32[5]=ARGB[1];
		ARGB32+=bytelarge/4;

		ARGB32[0]=ARGB[0];
		ARGB32[1]=ARGB[0];
		ARGB32[2]=ARGB[0];
		ARGB32[3]=ARGB[1];
		ARGB32[4]=ARGB[1];
		ARGB32[5]=ARGB[1];
		ARGB32+=bytelarge/4;

		ARGB32[0]=ARGB[2];
		ARGB32[1]=ARGB[2];
		ARGB32[2]=ARGB[2];
		ARGB32[3]=ARGB[2];
		ARGB32[4]=ARGB[2];
		ARGB32[5]=ARGB[2];
		ARGB32+=bytelarge/4;

		ARGB32[0]=ARGB[2];
		ARGB32[1]=ARGB[2];
		ARGB32[2]=ARGB[2];
		ARGB32[3]=ARGB[2];
		ARGB32[4]=ARGB[2];
		ARGB32[5]=ARGB[2];
		ARGB32+=bytelarge/4;

		ARGB32[0]=ARGB[2];
		ARGB32[1]=ARGB[2];
		ARGB32[2]=ARGB[2];
		ARGB32[3]=ARGB[2];
		ARGB32[4]=ARGB[2];
		ARGB32[5]=ARGB[2];

		V[0].s=s+PIXPOS1;   	V[0].t=t+PIXPOS1; 	
		V[1].s=s+PIXPOS2;		V[1].t=t+PIXPOS1; 	
		V[2].s=s+PIXPOS1;   	V[2].t=t+PIXPOS2; 

		V[0].x=P[0].x; 	V[0].y=P[0].y; 	V[0].w=1.0;
		V[1].x=P[1].x; 	V[1].y=P[1].y;	V[1].w=1.0;		
		V[2].x=P[2].x; 	V[2].y=P[2].y;	V[2].w=1.0;	

		i++;
		V=V+3;
		}

	P=P+3;
	}
	p96UnlockBitMap(colorsbm,bmHandle);

CREM(CompositeTags pass 2)
		error = CompositeTags(COMPOSITE_Src_Over_Dest,  
		colorsbm,SC->bm,
		COMPTAG_VertexArray, SC->HC.V, 
		COMPTAG_VertexFormat,COMPVF_STW0_Present,
		COMPTAG_NumTriangles,VisTRInb,
       	 	COMPTAG_DestX,x,
       	 	COMPTAG_DestY,y,
        	COMPTAG_DestWidth ,large,
       	 	COMPTAG_DestHeight,high,
		COMPTAG_OffsetY,SC->yoffset,
		COMPTAG_Flags,COMPFLAG_HardwareOnly|gouraud,
		TAG_DONE);

	if(error != COMPERR_Success)
		REM(CompositeTags error);
}
/*================================================================*/
void DrawTri(void *sc,void *p,ULONG a,ULONG b,ULONG c)
{
struct point3D TRI[3];
struct point3D *P=p;

CREM(DrawTri)
	COPYP( &TRI[0] , &P[a] );
	COPYP( &TRI[1] , &P[b] );
	COPYP( &TRI[2] , &P[c] );
	COMP3D_DrawTriangles(sc,TRI,3);
}
/*================================================================*/
void DrawQuad(void *sc,void *p)
{
struct point3D TRI[3*2];
struct point3D *P=p;

CREM(DrawQuad)
	COPYP( &TRI[0] , &P[0] );
	COPYP( &TRI[1] , &P[1] );
	COPYP( &TRI[2] , &P[2] );
	COPYP( &TRI[3] , &P[0] );
	COPYP( &TRI[4] , &P[2] );
	COPYP( &TRI[5] , &P[3] );
	COMP3D_DrawTriangles(sc,TRI,6);
}
/*================================================================*/
void DrawPoints(void *sc,struct point3D *P,ULONG nb)
{
struct SOFT3D_context *SC=sc;
ULONG RGB32;				/* bm memory  */
ULONG n;

CREM(DrawPoints)
	if(SC->bm==NULL) return;

	NLOOP(nb)
	{
		RGB32  = (P[n].RGBA[0] <<16) + (P[n].RGBA[1] <<8) + (P[n].RGBA[2]);
		SetRPAttrs(&SC->rastport, RPTAG_APenColor,RGB32,TAG_DONE);
 		WritePixel(&SC->rastport, P[n].x, P[n].y);
	}

}
/*================================================================*/
void DrawLine(void *sc,void *p,ULONG a,ULONG b)
{
struct SOFT3D_context *SC=sc;
struct point3D *P=p;
ULONG RGB32;
LONG bmHandle;					/* to directly write to bm */
ULONG offset;
struct RenderInfo renderInfo;
struct SOFT3D_texture *ST=SC->state.ST;
ULONG x,y;
UWORD large;
UBYTE *ARGB;
float uresize,vresize;

CREM(DrawLine)
	RGB32  = (P[a].RGBA[0] <<16) + (P[a].RGBA[1] <<8) + (P[a].RGBA[2]);	/* get line color from point a */
	if(SC->state.UseTex)
	{
		bmHandle=p96LockBitMap(ST->bm, (UBYTE*)&renderInfo, sizeof(renderInfo));
		if(bmHandle!=0)
		{
		large=p96GetBitMapAttr(ST->bm, P96BMA_BYTESPERROW)/4;
		ARGB=renderInfo.Memory;
		uresize=(float)(ST->large-0.001);
		vresize=(float)(ST->high -0.001);
		x= (ULONG) (uresize * P[a].u);
		y= (ULONG) (vresize * P[a].v);
		offset = large*y*4 + x*4;
		ARGB+=offset;
		RGB32  = (ARGB[1] <<16) + (ARGB[2] <<8) + (ARGB[3]);			/* get line color from tex */
		p96UnlockBitMap(ST->bm,bmHandle);
		}
	}

	SetRPAttrs(&SC->rastport, RPTAG_APenColor,RGB32,TAG_DONE);
	SetDrMd(&SC->rastport, JAM1);
	Move(&SC->rastport, P[a].x, P[a].y);
	Draw(&SC->rastport, P[b].x, P[b].y);
}
/*================================================================*/
void COMP3D_DrawPrimitive(void *sc,void *p,unsigned long Pnb,unsigned long primitive)
{
ULONG n;
ULONG nb=Pnb;

	if(Pnb>MAXPRIM)
		{ REM(maxprim) ; return;}

	if(primitive==W3D_PRIMITIVE_TRIANGLES)
	{
		COMP3D_DrawTriangles(sc,p,Pnb);
	return;
	}

	if(nb==4)
	if(primitive==W3D_PRIMITIVE_TRIFAN)
	{
		DrawQuad(sc,p);
	return;
	}

	if(primitive==W3D_PRIMITIVE_TRIFAN)
	{
	for (n=2;n<nb;n++)
		DrawTri(sc,p,0,n-1,n);
	return;
	}

	if(primitive==W3D_PRIMITIVE_TRISTRIP)
	{
	for (n=2;n<nb;n++)
	{
		if (n&1)	 						 /* reverse vertex order */
			DrawTri(sc,p,n-1,n-2,n-0);
		else
			DrawTri(sc,p,n-2,n-1,n-0);
	}
	return;
	}

	if(primitive==W3D_PRIMITIVE_POINTS)
	{
		DrawPoints(sc,p,nb);
	}

	if(primitive==W3D_PRIMITIVE_LINES)
	{
	nb=nb/2;
	NLOOP(nb)
		DrawLine(sc,p,2*n,2*n+1);
	return;
	}

	if(primitive==W3D_PRIMITIVE_LINELOOP)
	{
	nb=nb-1;
	NLOOP(nb)
		DrawLine(sc,p,n,n+1);

	DrawLine(sc,p,nb,0);
	return;
	}

	if(primitive==W3D_PRIMITIVE_LINESTRIP)
	{
	nb=nb-1;
	NLOOP(nb)
		DrawLine(sc,p,n,n+1);
	return;
	}
}
/*==================================================================*/
void COMP3D_End(void *sc)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_End);
	if(SC->colorsbm)
	{
      	// p96FreeBitMap(SC->colorsbm);
      	FreeBitMap(SC->colorsbm);
      	SC->colorsbm = NULL;
    	}

}
/*==================================================================*/
void COMP3D_Flush(void *sc)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_Flush);
	return; 			/* not needed for compositing */
}
/*==================================================================*/
void ChangeHardFog(void *sc,unsigned char FogMode,float FogZmin,float FogZmax,float FogDensity,unsigned char *FogRGBA)
{
struct SOFT3D_context *SC=sc;

	return; 			/* not possible this way via compositing : need a tex for fog */
}
/*==================================================================*/
void COMP3D_FreeTexture(void *sc,void *st)
{
struct SOFT3D_context *SC=sc;
struct SOFT3D_texture *ST=st;

	SFUNCTION(COMP3D_FreeTexture);
	if(ST->bm)
	{
      	FreeBitMap(ST->bm);
      	// p96FreeBitMap(ST->bm);
      	ST->bm = NULL;
    	}
}
/*==================================================================*/
void COMP3D_ReadZSpan(void *sc, unsigned short x, unsigned short y,unsigned long n, double *dz)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_ReadZSpan);
	return; 			/* not possible via compositing */
}
/*==================================================================*/
void COMP3D_WriteZSpan(void *sc, unsigned short x, unsigned short y,unsigned long n, double *dz, unsigned char *mask)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_WriteZSpan);
	return; 			/* not possible via compositing */
}
/*==================================================================*/
void COMP3D_AllocImageBuffer(void *sc,unsigned short large,unsigned short high)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_AllocImageBuffer);
	return; 			/* not possible via compositing */
}
/*==================================================================*/
void COMP3D_SetBitmap(void *sc,void *bm,unsigned char *ARGB,unsigned long format,unsigned short x,unsigned short y,unsigned short large,unsigned short high)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_SetBitmap);
	return; 			/* already done Soft3D side */
}
/*==================================================================*/
void COMP3D_SetClipping(void *sc,unsigned short xmin,unsigned short xmax,unsigned short ymin,unsigned short ymax)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_SetClipping);
	return; 			/* already done Soft3D side */
}
/*==================================================================*/
void COMP3D_SetDrawFunctions(void *sc)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_SetDrawFunctions);
	return; 			/* not possible this way via compositing */
}
/*==================================================================*/
void COMP3D_AllocZbuffer(void *sc,unsigned short large,unsigned short high)
{
struct SOFT3D_context *SC=sc;

	SFUNCTION(COMP3D_AllocZbuffer);
	return; 			/* not possible via compositing */
}
/*==================================================================*/
void COMP3D_UpdateTexture(void *sc,void *st,unsigned char *pt,unsigned short large,unsigned short high,unsigned char bits)
{
struct SOFT3D_context *SC=sc;
struct SOFT3D_texture *ST=st;

	SFUNCTION(COMP3D_UpdateTexture);
	UpdateBmTexture(ST);
}
/*==================================================================*/
#endif
