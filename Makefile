all: Warp3D.library

Warp3D.library: Wazp3D55.o Wazp3D_lib_ppc.o makefile
	gcc -nostartfiles -o Warp3D.library Wazp3D_lib_ppc.o Wazp3D55.o

Wazp3D_lib_ppc.o: Wazp3D_lib_ppc.c Warp3D_protos.h Wazp3D_68k_to_ppc.h Wazp3D_functions_glue_ppc.h makefile
	gcc -DMOTOROLAORDER -O0 -nostartfiles -c Wazp3D_lib_ppc.c -DOS4_V54 -DWARP3DV5 ;-DWAZP3DDEBUG 

Wazp3D55.o: Wazp3D55.c Wazp3D.h soft3d55.c soft3d_protos.h soft3d_opengl.h soft3d_compositing.c mymemory.h makefile
	gcc -DMOTOROLAORDER -O2 -nostartfiles -c Wazp3D55.c -DWARP3DV5 ;-DWAZP3DDEBUG

install: Warp3D.library
	delete libs:Warp3D.library
	copy Warp3D.library libs:
