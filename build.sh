    echo "Compiling..."
If EXISTS SYS:AROS.boot

echo "Compiling CoW3D with a static Wazp3D-54 with Mesa support..."
gcc -c -D STATWAZP3D Wazp3D55.c soft3d_opengl.c CoW3D-5.c
echo "Linking to GL (Mesa support)..."
gcc -o Cow3D-Aros-static Wazp3D55.o soft3d_opengl.o CoW3D-5.o -lgl
echo "Done..."

echo "CoW3D-5.c ..."
gcc -O3 -c CoW3D-5.c
gcc -O3 -o CoW3D-5-Aros CoW3D-5.o -lgl
echo "CoW3D-5-Aros also done..."

Else
    Version VERSION 46
    If WARN


echo "Building Wazp3D for 68020-40 ..."
echo "Wazp3D_lib.c ..."
gcc -D WAZP3DDEBUG -D MOTOROLAORDER -m68020-40 -m68881 -noixemul -O0 -nostartfiles -c Wazp3D_lib.c  
echo "Wazp3D55.c ..."
gcc -D WAZP3DDEBUG -D MOTOROLAORDER -m68020-40 -m68881 -noixemul -O2 -nostartfiles -c Wazp3D55.c
echo "linking ..."
gcc -noixemul -nostartfiles -o Warp3D.library-full Wazp3D_lib.o Wazp3D55.o   
echo "Warp3D.library-full done..."

echo "Wazp3D_lib.c ..."
gcc -D WAZP3DDEBUG -D MOTOROLAORDER -D SOFT3DLIB  -m68020-40 -m68881 -noixemul -O0 -nostartfiles -c Wazp3D_lib.c   
echo "Wazp3D55.c ..."
gcc -D WAZP3DDEBUG -D MOTOROLAORDER -D SOFT3DLIB  -m68020-40 -m68881 -noixemul -O2 -nostartfiles -c Wazp3D55.c
echo "linking ..."
gcc -noixemul -nostartfiles -o Warp3D.library-winuae Wazp3D_lib.o Wazp3D55.o 
gcc -noixemul -nostartfiles -o LIBS:Warp3D.library Wazp3D_lib.o Wazp3D55.o 
echo "Warp3D.library-winuae done..."

echo "soft3d_lib.c ..."
gcc -D WAZP3DDEBUG -D MOTOROLAORDER -D SOFT3DLIB -D SOFT3DDLL  -m68020-40 -m68881 -noixemul -O0 -nostartfiles -c soft3d_lib.c  
echo "soft3d55.c ..."
gcc -D WAZP3DDEBUG -D MOTOROLAORDER -D SOFT3DLIB -D SOFT3DDLL  -m68020-40 -m68881 -noixemul -O2 -nostartfiles -c soft3d55.c
echo "linking ..."
gcc -noixemul -nostartfiles -o soft3d.library soft3d_lib.o soft3d55.o   
gcc -noixemul -nostartfiles -o LIBS:soft3d.library soft3d_lib.o soft3d55.o         
echo "soft3d.library done..."

echo "All libraries done..."

echo "Wazp3D-Prefs.c ..."
gcc -noixemul -c Wazp3D-Prefs.c  Wazp3D-Prefs.o
gcc -noixemul -o Wazp3D-Prefs Wazp3D-Prefs.o  
echo "Wazp3D-Prefs also done..."

echo "CoW3D-5.c ..."
gcc -noixemul -O3 -c CoW3D-5.c
gcc -noixemul -O3 -o CoW3D-5 CoW3D-5.o
echo "CoW3D-5 also done..."

    Else

echo "Building Wazp3D for PPC ..."
echo "Wazp3D_lib_ppc.c ..."
gcc -D WAZP3DDEBUG -D MOTOROLAORDER -noixemul -O0 -nostartfiles -c Wazp3D_lib_ppc.c  
echo "Wazp3D55.c ..."
gcc -D WAZP3DDEBUG -D MOTOROLAORDER -noixemul -O2 -nostartfiles -c Wazp3D55.c    
echo "linking ..."
gcc -noixemul -nostartfiles -o Warp3D.library-ppc Wazp3D_lib_ppc.o Wazp3D55.o   
echo "Warp3D.library-ppc done..."

echo "Wazp3D-Prefs.c ..."
gcc -noixemul -c Wazp3D-Prefs.c  
gcc -noixemul -o Wazp3D-Prefs-ppc Wazp3D-Prefs.o  
echo "Wazp3D-Prefs-ppc also done..."

echo "CoW3D-5.c ..."
gcc -noixemul -O3 -c CoW3D-5.c
gcc -noixemul -O3 -o CoW3D-5-ppc CoW3D-5.o
echo "CoW3D-2-ppc also done..."

echo "Building Wazp3D for Altivec ..."
echo "Wazp3D_lib_ppc.c ..."
gcc -D WAZP3DDEBUG -D MOTOROLAORDER -noixemul -O0 -nostartfiles -c Wazp3D_lib_ppc.c  
echo "Wazp3D55.c ..."
gcc -D WAZP3DDEBUG -D MOTOROLAORDER -noixemul -O2 -maltivec -ftree-vectorize  -ffast-math  -nostartfiles -c Wazp3D55.c    
echo "linking ..."
gcc -noixemul -nostartfiles -o Warp3D.library-altivec Wazp3D_lib_ppc.o Wazp3D55.o   
echo "Warp3D.library-altivec done..."


    EndIf
EndIf
delete #?.o > NIL:
echo "Compilation done"
wait 600
