/* Wazp3D - Alain THELLIER - Paris - FRANCE 							*/
/* Adaptation to AROS from Matthias Rustler							*/
/* Code clean-up and library enhancements from Gunther Nikl					*/
/* LICENSE: GNU General Public License (GNU GPL) for this file				*/

/* This file contain the Wazp3d3D MorphOS library header					*/

/*======================================================================================*/
#ifdef WARP3DPPC
#warning Compiling PPC...
#define NAMETXT   "Warp3DPPC"
#else
#define NAMETXT   "Warp3D"
#endif
#define VERSION   53
#define REVISION  1
#define DATETXT    "24.07.2008"
#define VERSTXT    "53.1"
/*======================================================================================*/
/*#include <exec/memory.h>*/
#include <exec/resident.h>
/*#include <exec/initializers.h>
#include <exec/execbase.h>*/
//#include <exec/types.h>
#include <proto/exec.h>
#include <proto/dos.h>
//#include <stdarg.h> /* for varargs */
/*======================================================================================*/
BOOL WAZP3D_Init(void *exec);
void WAZP3D_Open();
void WAZP3D_Close();
void WAZP3D_Expunge();
/*======================================================================================*/
#define LIBNAME	 NAMETXT ".library"
#define IDSTRING NAMETXT " " VERSTXT " (" DATETXT ") PPC \r\n"
#define FULLNAME LIBNAME " " VERSTXT " (" DATETXT ")680 PPC"
/*======================================================================================*/
/*	library base private structure. The official one does not contain all the private fields! */
struct ExampleLibrary
	{
	struct Library LibNode;
	BPTR SegList;
	struct ExecBase *SysBase;
	};
#define DeleteLibrary(BASE) FreeMem(	(APTR)((char*)(BASE)-((BASE)->lib_NegSize)),(BASE)->lib_NegSize+(BASE)->lib_PosSize)
/*======================================================================================*/
/* First executable routine of this library; must return an error to the unsuspecting caller */
LONG ReturnError(void)
{
	return -1;
}
/*======================================================================================*/
extern const ULONG LibInitTable[4]; /* the prototype */
/* The library loader looks for this marker in the memory the library code
   and data will occupy. It is responsible setting up the Library base data structure.  */
/*======================================================================================*/
const struct Resident RomTag = {
	RTC_MATCHWORD,				/* Marker value. */
	(struct Resident *)&RomTag,		/* This points back to itself. */
	(struct Resident *)LibInitTable,	 /* This points somewhere behind this marker. */
	RTF_PPC | RTF_AUTOINIT,				/* The Library should be set up according to the given table. */
	VERSION,					/* The version of this Library. */
	NT_LIBRARY,					/* This defines this module as a Library. */
	0,						/* Initialization priority of this Library; unused. */
	LIBNAME,					/* Points to the name of the Library. */
	IDSTRING,					/* The identification string of this Library. */
	(APTR)&LibInitTable			/* This table is for initializing the Library. */
};
/*======================================================================================*/
/* The mandatory reserved library function */
ULONG LibReserved(void)
{
	return 0;
}
/*======================================================================================*/
/* Open the library, as called via OpenLibrary() */
struct Library *LibOpen(void)
{
	struct ExampleLibrary *libBase = (struct ExampleLibrary *)REG_A6;
	/* Prevent delayed expunge and increment opencnt */
	Forbid();
	libBase->LibNode.lib_Flags &= ~LIBF_DELEXP;
	libBase->LibNode.lib_OpenCnt++;
	Permit();
	WAZP3D_Open();
	return &libBase->LibNode;
}
/*======================================================================================*/
/* Expunge the library, remove it from memory */
BPTR LibExpunge2(struct ExampleLibrary *libBase)
{
	Forbid();

	if(!libBase->LibNode.lib_OpenCnt)
		{
		BPTR SegList;
		SegList = libBase->SegList;
		WAZP3D_Expunge();

		/* Remove the library from the public list */
		Remove((struct Node *) libBase);

		Permit();

		/* Free the vector table and the library data */
		DeleteLibrary(&libBase->LibNode);

		return SegList;
		}
	else
		libBase->LibNode.lib_Flags |= LIBF_DELEXP;

	Permit();

	/* Return the segment pointer, if any */
	return 0;
}
BPTR LibExpunge(void)
{
	struct ExampleLibrary *libBase = (struct ExampleLibrary *)REG_A6;

	return LibExpunge2(libBase);
}
/*======================================================================================*/
/* Close the library, as called by CloseLibrary() */
BPTR LibClose(void)
{
	struct ExampleLibrary *libBase = (struct ExampleLibrary *)REG_A6;
	WAZP3D_Close();
	Forbid();
	if(!(--libBase->LibNode.lib_OpenCnt))
		{
		if(libBase->LibNode.lib_Flags & LIBF_DELEXP)
			return LibExpunge2(libBase);
		}
	Permit();
	return 0;
}
/*======================================================================================*/
/* Initialize library */
#if 0
/* old style library init */
struct Library *LibInit(void)
{
	BPTR SegList = (BPTR)REG_A0;
	struct ExampleLibrary *libBase = (struct ExampleLibrary *)REG_D0;
	struct ExecBase *exec = (struct ExecBase *)REG_A6;
#else
/* RTF_PPC -> PPC SysV4 ABI for library init */
struct Library *LibInit(struct ExampleLibrary *libBase, BPTR SegList, struct ExecBase *exec)
{
#endif
	SysBase = exec;

	/* Remember stuff */
	libBase->SegList = SegList;
	libBase->SysBase = SysBase;

	if(WAZP3D_Init(exec))
		return &libBase->LibNode;

	/* Free the vector table and the library data */
	DeleteLibrary(&libBase->LibNode);
	return 0;
}
/*======================================================================================*/
/*	your own library's accessables functions	*/
#include "Wazp3D_functions_glue_mos.h"
/*======================================================================================*/
/* The following data structures and data are responsible for*/
/*	 setting up the Library base data structure and the library*/
/*	 function vector.*/
/*======================================================================================*/
const ULONG LibInitTable[4] = {
	(ULONG)sizeof(struct ExampleLibrary), /* Size of the base data structure */
	(ULONG)LibVectors,			 /* Points to the function vector */
	NULL,			 /* Library base data structure setup table */
	(ULONG)LibInit				 /* The address of the routine to do the setup */
};
/*======================================================================================*/

void exit(int i) { /*kprintf("Something called exit()! Painful death follows...\n");*/ for (;;) Wait(0); }
