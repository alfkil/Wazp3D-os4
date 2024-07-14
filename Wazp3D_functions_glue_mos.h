/* Wazp3D PPC  need Warp3D v5 functions */
#define WARP3DV5 1

#include <Warp3D/Warp3D.h>        /* définitions de WORD ,UBYTE, etc... */

#include <emul/emulinterface.h>
#include <emul/emulregs.h>
#include <utility/tagitem.h>
#include <stdarg.h>

W3D_Context *LibW3D_CreateContext(void)
{
	ULONG *error = (ULONG *)REG_A0;
	struct TagItem *CCTags = (struct TagItem *)REG_A1;
	return (W3D_Context *)W3D_CreateContext(error, CCTags);
}

void LibW3D_DestroyContext(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_DestroyContext(context);
}

ULONG LibW3D_GetState(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG state = (ULONG)REG_D1;
	return W3D_GetState(context, state);
}

ULONG LibW3D_SetState(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG state = (ULONG)REG_D0;
	ULONG action = (ULONG)REG_D1;
	return W3D_SetState(context, state, action);
}

ULONG LibW3D_CheckDriver(void)
{
	return W3D_CheckDriver();
}

ULONG LibW3D_LockHardware(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	return W3D_LockHardware(context);
}

void LibW3D_UnLockHardware(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_UnLockHardware(context);
}

void LibW3D_WaitIdle(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_WaitIdle(context);
}

ULONG LibW3D_CheckIdle(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	return W3D_CheckIdle(context);
}

ULONG LibW3D_Query(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG query = (ULONG)REG_D0;
	ULONG destfmt = (ULONG)REG_D1;
	return W3D_Query(context, query, destfmt);
}

ULONG LibW3D_GetTexFmtInfo(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG texfmt = (ULONG)REG_D0;
	ULONG destfmt = (ULONG)REG_D1;
	return W3D_GetTexFmtInfo(context, texfmt, destfmt);
}

W3D_Texture *LibW3D_AllocTexObj(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG *error = (ULONG *)REG_A1;
	struct TagItem *ATOTags = (struct TagItem *)REG_A2;
	return (W3D_Texture *)W3D_AllocTexObj(context, error, ATOTags);
}

void LibW3D_FreeTexObj(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	W3D_FreeTexObj(context, texture);
}

void LibW3D_ReleaseTexture(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	W3D_ReleaseTexture(context, texture);
}

void LibW3D_FlushTextures(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_FlushTextures(context);
}

ULONG LibW3D_SetFilter(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	ULONG MinFilter = (ULONG)REG_D0;
	ULONG MagFilter = (ULONG)REG_D1;
	return W3D_SetFilter(context, texture, MinFilter, MagFilter);
}

ULONG LibW3D_SetTexEnv(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	ULONG envparam = (ULONG)REG_D0;
	W3D_Color *envcolor = (W3D_Color *)REG_A2;
	return W3D_SetTexEnv(context, texture, envparam, envcolor);
}

ULONG LibW3D_SetWrapMode(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	ULONG s_mode = (ULONG)REG_D0;
	ULONG t_mode = (ULONG)REG_D1;
	W3D_Color *bordercolor = (W3D_Color *)REG_A2;
	return W3D_SetWrapMode(context, texture, s_mode, t_mode, bordercolor);
}

ULONG LibW3D_UpdateTexImage(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	void *teximage = (void *)REG_A2;
	int level = (int)REG_D1;
	ULONG *palette = (ULONG *)REG_A3;
	return W3D_UpdateTexImage(context, texture, teximage, level, palette);
}

ULONG LibW3D_UploadTexture(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	return W3D_UploadTexture(context, texture);
}

ULONG LibW3D_DrawLine(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Line *line = (W3D_Line *)REG_A1;
	return W3D_DrawLine(context, line);
}

ULONG LibW3D_DrawPoint(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Point *point = (W3D_Point *)REG_A1;
	return W3D_DrawPoint(context, point);
}

ULONG LibW3D_DrawTriangle(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Triangle *triangle = (W3D_Triangle *)REG_A1;
	return W3D_DrawTriangle(context, triangle);
}

ULONG LibW3D_DrawTriFan(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Triangles *triangles = (W3D_Triangles *)REG_A1;
	return W3D_DrawTriFan(context, triangles);
}

ULONG LibW3D_DrawTriStrip(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Triangles *triangles = (W3D_Triangles *)REG_A1;
	return W3D_DrawTriStrip(context, triangles);
}

ULONG LibW3D_SetAlphaMode(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG mode = (ULONG)REG_D1;
	W3D_Float *refval = (W3D_Float *)REG_A1;
	return W3D_SetAlphaMode(context, mode, refval);
}

ULONG LibW3D_SetBlendMode(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG srcfunc = (ULONG)REG_D0;
	ULONG dstfunc = (ULONG)REG_D1;
	return W3D_SetBlendMode(context, srcfunc, dstfunc);
}

ULONG LibW3D_SetDrawRegion(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	struct BitMap *bm = (struct BitMap *)REG_A1;
	int yoffset = (int)REG_D1;
	W3D_Scissor *scissor = (W3D_Scissor *)REG_A2;
	return W3D_SetDrawRegion(context, bm, yoffset, scissor);
}

ULONG LibW3D_SetFogParams(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Fog *fogparams = (W3D_Fog *)REG_A1;
	ULONG fogmode = (ULONG)REG_D1;
	return W3D_SetFogParams(context, fogparams, fogmode);
}

ULONG LibW3D_SetColorMask(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Bool red = (W3D_Bool)REG_D0;
	W3D_Bool green = (W3D_Bool)REG_D1;
	W3D_Bool blue = (W3D_Bool)REG_D2;
	W3D_Bool alpha = (W3D_Bool)REG_D3;
	return W3D_SetColorMask(context, red, green, blue, alpha);
}

ULONG LibW3D_SetStencilFunc(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG func = (ULONG)REG_D0;
	ULONG refvalue = (ULONG)REG_D1;
	ULONG mask = (ULONG)REG_D2;
	return W3D_SetStencilFunc(context, func, refvalue, mask);
}

ULONG LibW3D_AllocZBuffer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	return W3D_AllocZBuffer(context);
}

ULONG LibW3D_FreeZBuffer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	return W3D_FreeZBuffer(context);
}

ULONG LibW3D_ClearZBuffer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Double *clearvalue = (W3D_Double *)REG_A1;
	return W3D_ClearZBuffer(context, clearvalue);
}

ULONG LibW3D_ReadZPixel(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG x = (ULONG)REG_D0;
	ULONG y = (ULONG)REG_D1;
	W3D_Double *z = (W3D_Double *)REG_A1;
	return W3D_ReadZPixel(context, x, y, z);
}

ULONG LibW3D_ReadZSpan(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG x = (ULONG)REG_D0;
	ULONG y = (ULONG)REG_D1;
	ULONG n = (ULONG)REG_D2;
	W3D_Double *z = (W3D_Double *)REG_A1;
	return W3D_ReadZSpan(context, x, y, n, z);
}

ULONG LibW3D_SetZCompareMode(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG mode = (ULONG)REG_D1;
	return W3D_SetZCompareMode(context, mode);
}

ULONG LibW3D_AllocStencilBuffer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	return W3D_AllocStencilBuffer(context);
}

ULONG LibW3D_ClearStencilBuffer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG *clearvalue = (ULONG *)REG_A1;
	return W3D_ClearStencilBuffer(context, clearvalue);
}

ULONG LibW3D_FillStencilBuffer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG x = (ULONG)REG_D0;
	ULONG y = (ULONG)REG_D1;
	ULONG width = (ULONG)REG_D2;
	ULONG height = (ULONG)REG_D3;
	ULONG depth = (ULONG)REG_D4;
	void *data = (void *)REG_A1;
	return W3D_FillStencilBuffer(context, x, y, width, height, depth, data);
}

ULONG LibW3D_FreeStencilBuffer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	return W3D_FreeStencilBuffer(context);
}

ULONG LibW3D_ReadStencilPixel(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG x = (ULONG)REG_D0;
	ULONG y = (ULONG)REG_D1;
	ULONG *st = (ULONG *)REG_A1;
	return W3D_ReadStencilPixel(context, x, y, st);
}

ULONG LibW3D_ReadStencilSpan(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG x = (ULONG)REG_D0;
	ULONG y = (ULONG)REG_D1;
	ULONG n = (ULONG)REG_D2;
	ULONG *st = (ULONG *)REG_A1;
	return W3D_ReadStencilSpan(context, x, y, n, st);
}

ULONG LibW3D_SetLogicOp(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG operation = (ULONG)REG_D1;
	return W3D_SetLogicOp(context, operation);
}

ULONG LibW3D_Hint(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG mode = (ULONG)REG_D0;
	ULONG quality = (ULONG)REG_D1;
	return W3D_Hint(context, mode, quality);
}

ULONG LibW3D_SetDrawRegionWBM(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Bitmap *bm = (W3D_Bitmap *)REG_A1;
	W3D_Scissor *scissor = (W3D_Scissor *)REG_A1;
	return W3D_SetDrawRegionWBM(context, bm, scissor);
}

ULONG LibW3D_GetDriverState(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	return W3D_GetDriverState(context);
}

ULONG LibW3D_Flush(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	return W3D_Flush(context);
}

ULONG LibW3D_SetPenMask(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG pen = (ULONG)REG_D0;
	return W3D_SetPenMask(context,pen);
}

ULONG LibW3D_SetStencilOp(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG sfail = (ULONG)REG_D0;
	ULONG dpfail = (ULONG)REG_D1;
	ULONG dppass = (ULONG)REG_D2;
	return W3D_SetStencilOp(context, sfail, dpfail, dppass);
}

ULONG LibW3D_SetWriteMask(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG mask = (ULONG)REG_D0;
	return W3D_SetWriteMask(context, mask);
}

ULONG LibW3D_WriteStencilPixel(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG x = (ULONG)REG_D0;
	ULONG y = (ULONG)REG_D1;
	ULONG st = (ULONG)REG_D2;
	return W3D_WriteStencilPixel(context, x, y, st);
}

ULONG LibW3D_WriteStencilSpan(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG x = (ULONG)REG_D0;
	ULONG y = (ULONG)REG_D1;
	ULONG n = (ULONG)REG_D2;
	ULONG *st = (ULONG *)REG_A1;
	UBYTE *mask = (UBYTE *)REG_A2;
	return W3D_WriteStencilSpan(context, x, y, n, st, mask);
}

void LibW3D_WriteZPixel(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG x = (ULONG)REG_D0;
	ULONG y = (ULONG)REG_D1;
	W3D_Double *z = (W3D_Double *)REG_A1;
	W3D_WriteZPixel(context, x, y, z);
}

void LibW3D_WriteZSpan(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG x = (ULONG)REG_D0;
	ULONG y = (ULONG)REG_D1;
	ULONG n = (ULONG)REG_D2;
	W3D_Double *z = (W3D_Double *)REG_A1;
	UBYTE *mask = (UBYTE *)REG_A2;
	W3D_WriteZSpan(context, x, y, n, z, mask);
}

ULONG LibW3D_SetCurrentColor(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Color *color = (W3D_Color *)REG_A1;
	return W3D_SetCurrentColor(context, color);
}

ULONG LibW3D_SetCurrentPen(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG pen = (ULONG)REG_D1;
	return W3D_SetCurrentPen(context,pen);
}

ULONG LibW3D_UpdateTexSubImage(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	void *teximage = (void *)REG_A2;
	ULONG level = (ULONG)REG_D1;
	ULONG *palette = (ULONG *)REG_A4;
	W3D_Scissor *scissor = (W3D_Scissor *)REG_A4;
	ULONG srcbpr = (ULONG)REG_D0;
	return W3D_UpdateTexSubImage(context, texture, teximage, level, palette, scissor, srcbpr);
}

ULONG LibW3D_FreeAllTexObj(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	return W3D_FreeAllTexObj(context);
}

ULONG LibW3D_GetDestFmt(void)
{
	return W3D_GetDestFmt();
}

ULONG LibW3D_DrawLineStrip(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Lines *lines = (W3D_Lines *)REG_A1;
	return W3D_DrawLineStrip(context, lines);
}

ULONG LibW3D_DrawLineLoop(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Lines *lines = (W3D_Lines *)REG_A1;
	return W3D_DrawLineLoop(context,lines);
}

W3D_Driver **LibW3D_GetDrivers(void)
{
	return (W3D_Driver**)W3D_GetDrivers();
}

ULONG LibW3D_QueryDriver(void)
{
	W3D_Driver *driver = (W3D_Driver *)REG_A0;
	ULONG query = (ULONG)REG_D0;
	ULONG destfmt = (ULONG)REG_D1;
	return W3D_QueryDriver(driver, query, destfmt);
}

ULONG LibW3D_GetDriverTexFmtInfo(void)
{
	W3D_Driver *driver = (W3D_Driver *)REG_A0;
	ULONG query = (ULONG)REG_D0;
	ULONG destfmt = (ULONG)REG_D1;
	return W3D_GetDriverTexFmtInfo(driver, query, destfmt);
}

ULONG LibW3D_RequestMode(void)
{
	struct TagItem *taglist = (struct TagItem *)REG_A0;
	return W3D_RequestMode(taglist);
}

void LibW3D_SetScissor(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Scissor *scissor = (W3D_Scissor *)REG_A1;
	W3D_SetScissor(context, scissor);
}

void LibW3D_FlushFrame(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_FlushFrame(context);
}

W3D_Driver *LibW3D_TestMode(void)
{
	ULONG ModeID = (ULONG)REG_D0;
	return (W3D_Driver*) W3D_TestMode(ModeID);
}

ULONG LibW3D_SetChromaTestBounds(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	ULONG rgba_lower = (ULONG)REG_D0;
	ULONG rgba_upper = (ULONG)REG_D1;
	ULONG mode = (ULONG)REG_D2;
	return W3D_SetChromaTestBounds(context, texture, rgba_lower, rgba_upper, mode);
}

ULONG LibW3D_ClearDrawRegion(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG color = (ULONG)REG_D0;
	return W3D_ClearDrawRegion(context, color);
}

ULONG LibW3D_DrawTriangleV(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_TriangleV *triangle = (W3D_TriangleV *)REG_A1;
	return W3D_DrawTriangleV(context, triangle);
}

ULONG LibW3D_DrawTriFanV(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_TrianglesV *triangles = (W3D_TrianglesV *)REG_A1;
	return W3D_DrawTriFanV(context,triangles);
}

ULONG LibW3D_DrawTriStripV(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_TrianglesV *triangles = (W3D_TrianglesV *)REG_A1;
	return W3D_DrawTriStripV(context, triangles);
}

W3D_ScreenMode *LibW3D_GetScreenmodeList(void)
{
	return (W3D_ScreenMode*) W3D_GetScreenmodeList();
}

void LibW3D_FreeScreenmodeList(void)
{
	W3D_ScreenMode *list = (W3D_ScreenMode *)REG_A0;
	W3D_FreeScreenmodeList(list);
}

ULONG LibW3D_BestModeID(void)
{
	struct TagItem *tags = (struct TagItem *)REG_A0;
	return W3D_BestModeID(tags);
}

ULONG LibW3D_VertexPointer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	void *pointer = (void *)REG_A1;
	int stride = (int)REG_D0;
	ULONG mode = (ULONG)REG_D1;
	ULONG flags = (ULONG)REG_D2;
	return W3D_VertexPointer(context, pointer, stride, mode, flags);
}

ULONG LibW3D_TexCoordPointer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	void *pointer = (void *)REG_A1;
	int stride = (int)REG_D0;
	int unit = (int)REG_D1;
	int off_v = (int)REG_D2;
	int off_w = (int)REG_D3;
	ULONG flags = (ULONG)REG_D4;
	return W3D_TexCoordPointer(context, pointer, stride, unit, off_v, off_w, flags);
}

ULONG LibW3D_ColorPointer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	void *pointer = (void *)REG_A1;
	int stride = (int)REG_D0;
	ULONG format = (ULONG)REG_D1;
	ULONG mode = (ULONG)REG_D2;
	ULONG flags = (ULONG)REG_D3;
	return W3D_ColorPointer(context, pointer, stride, format, mode, flags);
}

ULONG LibW3D_BindTexture(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG tmu = (ULONG)REG_D0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	return W3D_BindTexture(context, tmu, texture);
}

ULONG LibW3D_DrawArray(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG primitive = (ULONG)REG_D0;
	ULONG base = (ULONG)REG_D1;
	ULONG count = (ULONG)REG_D2;
	return W3D_DrawArray(context, primitive, base, count);
}

ULONG LibW3D_DrawElements(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG primitive = (ULONG)REG_D0;
	ULONG type = (ULONG)REG_D1;
	ULONG count = (ULONG)REG_D2;
	void *indices = (void *)REG_A1;
	return W3D_DrawElements(context, primitive, type, count, indices);
}

void LibW3D_SetFrontFace(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG direction = (ULONG)REG_D0;
	W3D_SetFrontFace(context, direction);
}


#ifdef WARP3DV5
ULONG LibW3D_SetTextureBlend(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	struct TagItem *tagList = (struct TagItem *)REG_A1;
	return(W3D_SetTextureBlend(context, tagList));
}


ULONG LibW3D_SecondaryColorPointer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	void *pointer = (void *)REG_A1;
	int stride = (int)REG_D0;
	ULONG format = (ULONG)REG_D1;
	ULONG mode = (ULONG)REG_D2;
	ULONG flags = (ULONG)REG_D3;
	return(W3D_SecondaryColorPointer(context,pointer,stride,format,mode,flags));
}

ULONG LibW3D_FogCoordPointer(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	void *pointer = (void *)REG_A1;
	int stride = (int)REG_D0;
	ULONG mode = (ULONG)REG_D1;
	ULONG flags = (ULONG)REG_D2;
	return(W3D_FogCoordPointer(context,pointer,stride,mode,flags));
}

ULONG LibW3D_InterleavedArray(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	void *pointer = (void *)REG_A1;
	int stride = (int)REG_D0;
	ULONG format = (ULONG)REG_D1;
	ULONG flags = (ULONG)REG_D2;
	return(W3D_InterleavedArray(context,pointer,stride,format,flags));
}

ULONG LibW3D_ClearBuffers(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Color * color  = (W3D_Color *)REG_A1;
	W3D_Double * depth = (W3D_Double *)REG_A2;
	ULONG * stencil    = (ULONG *)REG_A3;
	return(W3D_ClearBuffers(context,color,depth,stencil));
}

ULONG LibW3D_SetParameter(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	ULONG target = (ULONG)REG_D0;
	void * pattern = (void *)REG_A0;
	return(W3D_SetParameter(context,target,pattern));
}

ULONG LibW3D_PinTexture(void)
{
	W3D_Context *context = (W3D_Context *)REG_A0;
	W3D_Texture *texture = (W3D_Texture *)REG_A1;
	BOOL pinning = (BOOL)REG_D0;
	return(W3D_PinTexture(context,texture,pinning));
}

ULONG LibW3D_SetDrawRegionTexture(void)
{
	W3D_Context *context  = (W3D_Context *)REG_A0;
	W3D_Texture * texture = (W3D_Texture *)REG_A1;
	W3D_Scissor *scissor  = (W3D_Scissor *)REG_A2;
	return(W3D_SetDrawRegionTexture(context,texture,scissor));
}

#endif



static const APTR LibVectors[] =
{
	FUNCARRAY_32BIT_NATIVE,
	(APTR) LibOpen,
	(APTR) LibClose,
	(APTR) LibExpunge,
	(APTR) LibReserved,

	(APTR) LibW3D_CreateContext,
	(APTR) LibW3D_DestroyContext,
	(APTR) LibW3D_GetState,
	(APTR) LibW3D_SetState,

	(APTR) LibW3D_CheckDriver,
	(APTR) LibW3D_LockHardware,
	(APTR) LibW3D_UnLockHardware,
	(APTR) LibW3D_WaitIdle,
	(APTR) LibW3D_CheckIdle,
	(APTR) LibW3D_Query,
	(APTR) LibW3D_GetTexFmtInfo,

	(APTR) LibW3D_AllocTexObj,
	(APTR) LibW3D_FreeTexObj,
	(APTR) LibW3D_ReleaseTexture,
	(APTR) LibW3D_FlushTextures,
	(APTR) LibW3D_SetFilter,
	(APTR) LibW3D_SetTexEnv,
	(APTR) LibW3D_SetWrapMode,
	(APTR) LibW3D_UpdateTexImage,
	(APTR) LibW3D_UploadTexture,

	(APTR) LibW3D_DrawLine,
	(APTR) LibW3D_DrawPoint,
	(APTR) LibW3D_DrawTriangle,
	(APTR) LibW3D_DrawTriFan,
	(APTR) LibW3D_DrawTriStrip,

	(APTR) LibW3D_SetAlphaMode,
	(APTR) LibW3D_SetBlendMode,
	(APTR) LibW3D_SetDrawRegion,
	(APTR) LibW3D_SetFogParams,
	(APTR) LibW3D_SetColorMask,
	(APTR) LibW3D_SetStencilFunc,

	(APTR) LibW3D_AllocZBuffer,
	(APTR) LibW3D_FreeZBuffer,
	(APTR) LibW3D_ClearZBuffer,
	(APTR) LibW3D_ReadZPixel,
	(APTR) LibW3D_ReadZSpan,
	(APTR) LibW3D_SetZCompareMode,

	(APTR) LibW3D_AllocStencilBuffer,
	(APTR) LibW3D_ClearStencilBuffer,
	(APTR) LibW3D_FillStencilBuffer,
	(APTR) LibW3D_FreeStencilBuffer,
	(APTR) LibW3D_ReadStencilPixel,
	(APTR) LibW3D_ReadStencilSpan,

	(APTR) LibW3D_SetLogicOp,
	(APTR) LibW3D_Hint,
	(APTR) LibW3D_SetDrawRegionWBM,
	(APTR) LibW3D_GetDriverState,
	(APTR) LibW3D_Flush,
	(APTR) LibW3D_SetPenMask,
	(APTR) LibW3D_SetStencilOp,
	(APTR) LibW3D_SetWriteMask,
	(APTR) LibW3D_WriteStencilPixel,
	(APTR) LibW3D_WriteStencilSpan,
	(APTR) LibW3D_WriteZPixel,
	(APTR) LibW3D_WriteZSpan,
	(APTR) LibW3D_SetCurrentColor,
	(APTR) LibW3D_SetCurrentPen,
	(APTR) LibW3D_UpdateTexSubImage,
	(APTR) LibW3D_FreeAllTexObj,
	(APTR) LibW3D_GetDestFmt,

	(APTR) LibW3D_DrawLineStrip,
	(APTR) LibW3D_DrawLineLoop,
	(APTR) LibW3D_GetDrivers,
	(APTR) LibW3D_QueryDriver,
	(APTR) LibW3D_GetDriverTexFmtInfo,
	(APTR) LibW3D_RequestMode,
	(APTR) LibW3D_SetScissor,
	(APTR) LibW3D_FlushFrame,
	(APTR) LibW3D_TestMode,
	(APTR) LibW3D_SetChromaTestBounds,
	(APTR) LibW3D_ClearDrawRegion,

	(APTR) LibW3D_DrawTriangleV,
	(APTR) LibW3D_DrawTriFanV,
	(APTR) LibW3D_DrawTriStripV,
	(APTR) LibW3D_GetScreenmodeList,
	(APTR) LibW3D_FreeScreenmodeList,
	(APTR) LibW3D_BestModeID,

	(APTR) LibW3D_VertexPointer,
	(APTR) LibW3D_TexCoordPointer,
	(APTR) LibW3D_ColorPointer,
	(APTR) LibW3D_BindTexture,
	(APTR) LibW3D_DrawArray,
	(APTR) LibW3D_DrawElements,
	(APTR) LibW3D_SetFrontFace,

#ifdef WARP3DV5
	(APTR) LibW3D_SetTextureBlend,
 	(APTR) LibW3D_SecondaryColorPointer,
 	(APTR) LibW3D_FogCoordPointer,
 	(APTR) LibW3D_InterleavedArray,
 	(APTR) LibW3D_ClearBuffers,
  	(APTR) LibW3D_SetParameter,
	(APTR) LibW3D_PinTexture,
	(APTR) LibW3D_SetDrawRegionTexture,
#endif

	(APTR) -1
};
