Intel 8080 emulator for Space Invaders (1978).

Build/run instructions:

1. Install GCC or, alternatively, replace all occurrences of `gcc` in the Makefile with your preferred compiler.
2. [Download an SDL2 release](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5).
3. Open the Makefile and replace the value of SDL2Path to the SDL2 path on your system.
4. Go to the root folder and type `make game` or, on Windows with MINGW installed, `mingw32-make game`.
5. Run the emulation by typing `bin/game.exe`.

This has only been tested on Windows 10.

The controls are not yet implemented, but you can press the G and H buttons on your keyboard to trigger what I believe to be the timer hardware and display the menu symbol by symbol.

More functionality to come (maybe).
