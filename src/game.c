#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "emulator.h"

#define WIDTH 224
#define HEIGHT 256

static SDL_Surface *surface = NULL;
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static uint8_t *memory;
static uint8_t *raster; // size is width * height @ 1bpp = 7168 bytes

static bool Init(void);
static void Update(EmulatorState *state);
static void Render(void);
static void Quit(void);

int main(int argc, char *argv[])
{
    FILE *file;
    char *filename = "bin/invaders.rom";
    int filesize;
    const int memsize = 1 << 16;

    if (!Init()) return 1;
    SDL_Event event;
    bool running = true;

    // Initialize memory from ROM file
    if ((file = fopen(filename, "rb")) == NULL) {
        printf("Failed to open file %s for reading. Exiting...", filename);
        return 1;
    }
    fseek(file, 0L, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);
    memory = malloc(memsize);
    raster = &memory[0x2400];
    fread(memory, filesize, 1, file);
    fclose(file);

    EmulatorState _state;
    EmulatorState *state = &_state;
    InitEmulator(state, memory, 1 << 16, NULL, NULL);

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        Update(state);
        Render();
        SDL_Delay(10);
    }

    Quit();
    return 0;
}

static bool Init(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    if ((window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) == NULL) {
        printf("SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }

    surface = SDL_GetWindowSurface(window);

    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        printf("SDL_CreateRenderer failed: %s", SDL_GetError());
        return false;
    }

    return true;
}

static void Update(EmulatorState *state) {
    static bool showedError = false;
    for (int i = 0; i < 5000; i++) {
        if (!EmulateInstruction(state) && !showedError) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error!", "Fatal error!", window);
            showedError = true;
        }
    }
}

static void Render(void)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            size_t pixelno = (j + 1) * HEIGHT - i;
            size_t byteno = pixelno / 8;
            size_t bitno = pixelno % 8;
            bool pixel_active = (raster[byteno] >> bitno) & 1;
            SDL_SetRenderDrawColor(renderer, 0, pixel_active ? 255 : 0, 0, 255);
            SDL_RenderDrawPoint(renderer, j, i);
        }
    }
    SDL_RenderPresent(renderer);
}

static void Quit(void)
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();
}
