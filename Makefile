SDL2Path = C:/SDL2-2.26.4/i686-w64-mingw32
SDL2Include = $(SDL2Path)/include
SDL2Lib = $(SDL2Path)/lib

disasm.exe:
	gcc src/disasm.c -o bin/disasm.exe

test.exe:
	gcc src/test.c -o bin/test.exe -I$(SDL2Include) -L$(SDL2Lib) -lmingw32 -lSDL2main -lSDL2 -mwindows
