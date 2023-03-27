SDL2Path = C:/SDL2-2.26.4/i686-w64-mingw32
SDL2Include = $(SDL2Path)/include
SDL2Lib = $(SDL2Path)/lib

emulator.exe:
	gcc -ggdb src/main.c src/macros.c src/disasm.c src/emulator.c src/datatransfer.c src/arithmetic.c src/logic.c src/branch.c src/stack.c src/misc.c -o main.exe

disasm.exe:
	gcc src/disasm.c src/disasm_to_file.c -o disasm.exe

test.exe:
	gcc src/test.c -o bin/test.exe -I$(SDL2Include) -L$(SDL2Lib) -lmingw32 -lSDL2main -lSDL2 -mwindows
