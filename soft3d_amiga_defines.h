/* Wazp3D - Alain THELLIER - Paris - FRANCE 							*/
/* Adaptation to AROS from Matthias Rustler							*/
/* Code clean-up and library enhancements from Gunther Nikl					*/
/* LICENSE: GNU General Public License (GNU GPL) for this file				*/

/* For the PC DLL we define the Amiga types here so it dont need any Amiga includes */

typedef   signed char	BYTE;
typedef unsigned char	UBYTE;
typedef   signed long	LONG;
typedef unsigned long	ULONG;
typedef   signed short	WORD;
typedef unsigned short	UWORD;
typedef short		BOOL;
typedef void 		*APTR;
#define NULL		(APTR)0
#define TRUE		1
#define FALSE		0

/* For the PC DLL we define the Warp3D types here so it dont need any Amiga includes */

typedef double W3D_Double;
#define W3D_REPLACE             1
#define W3D_DECAL               2
#define W3D_MODULATE            3
#define W3D_BLEND               4
#define W3D_ADD			  5
#define W3D_SUB			  6
#define W3D_Z_NEVER             1
#define W3D_Z_LESS              2
#define W3D_Z_GEQUAL            3
#define W3D_Z_LEQUAL            4
#define W3D_Z_GREATER           5
#define W3D_Z_NOTEQUAL          6
#define W3D_Z_EQUAL             7
#define W3D_Z_ALWAYS            8
#define W3D_ZERO                1       /* source + dest */
#define W3D_ONE                 2       /* source + dest */
#define W3D_SRC_COLOR           3       /* dest only */
#define W3D_DST_COLOR           4       /* source only */
#define W3D_ONE_MINUS_SRC_COLOR 5       /* dest only */
#define W3D_ONE_MINUS_DST_COLOR 6       /* source only */
#define W3D_SRC_ALPHA           7       /* source + dest */
#define W3D_ONE_MINUS_SRC_ALPHA 8       /* source + dest */
#define W3D_DST_ALPHA           9       /* source + dest */
#define W3D_ONE_MINUS_DST_ALPHA 10      /* source + dest */
#define W3D_SRC_ALPHA_SATURATE  11      /* source only */
#define W3D_CONSTANT_COLOR      12
#define W3D_ONE_MINUS_CONSTANT_COLOR 13
#define W3D_CONSTANT_ALPHA      14
#define W3D_ONE_MINUS_CONSTANT_ALPHA 15
#define W3D_CW                  0                       /* Front face is clockwise */
#define W3D_CCW                 1                       /* Front face is counter clockwise */
#define W3D_PRIMITIVE_TRIANGLES         0
#define W3D_PRIMITIVE_TRIFAN            1
#define W3D_PRIMITIVE_TRISTRIP          2
#define W3D_PRIMITIVE_POINTS            3
#define W3D_PRIMITIVE_LINES             4
#define W3D_PRIMITIVE_LINELOOP          5
#define W3D_PRIMITIVE_LINESTRIP         6
#define BLENDCHROMA    (W3D_SRC_COLOR*16 + W3D_DST_COLOR)       /* This is an unused BlendMode		*/

/* For the PC DLL we define the CyberGraphics types here so it dont need any Amiga includes */

#define PIXFMT_LUT8     0
#define PIXFMT_RGB15    1
#define PIXFMT_BGR15    2
#define PIXFMT_RGB15PC  3
#define PIXFMT_BGR15PC  4
#define PIXFMT_RGB16    5
#define PIXFMT_BGR16    6
#define PIXFMT_RGB16PC  7
#define PIXFMT_BGR16PC  8
#define PIXFMT_RGB24    9
#define PIXFMT_BGR24   10
#define PIXFMT_ARGB32  11
#define PIXFMT_BGRA32  12
#define PIXFMT_RGBA32  13

#define W3D_CHUNKY              1
#define W3D_A1R5G5B5            2
#define W3D_R5G6B5              3
#define W3D_R8G8B8              4
#define W3D_A4R4G4B4            5
#define W3D_A8R8G8B8            6
#define W3D_A8                  7
#define W3D_L8                  8
#define W3D_L8A8                9
#define W3D_I8                 10
#define W3D_R8G8B8A8           11




