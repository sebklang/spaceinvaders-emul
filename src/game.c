#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "emulator.h"

#define WIDTH 256
#define HEIGHT 224

static SDL_Surface *surface = NULL;
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static uint8_t *memory;
static uint8_t *raster; // size is width * height (57344) bytes

static bool Init(void);
static void Update(EmulatorState *state);
static void Render(void);
static void Quit(void);

int main(int argc, char *argv[])
{
    if (!Init()) return 1;
    memory = malloc(1 << 16);
    raster = &memory[0x2400];
    SDL_Event event;
    bool running = true;

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
        SDL_Delay(1);
    }

    Quit();
    return 0;
}

static bool Init(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    if ((window = SDL_CreateWindow("My SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) == NULL) {
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
    for (int i = 0; i < 100000; i++) {
        if (!EmulateInstruction(state)) {
            printf("Fatal error!");
        }
    }
}

static void Render(void)
{
    /*
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    static SDL_Rect rect = {100, 100, 50, 50};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    rect.x++;
    */
    static Uint8 color_i = 0;
    SDL_RenderClear(renderer);
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            size_t pixelno = i * j;
            size_t byteno = pixelno / 8;
            size_t bitno = pixelno % 8;
            bool pixel_active = (raster[byteno] >> bitno) & 1;
            SDL_SetRenderDrawColor(renderer, 0, pixel_active ? 255 : 0, 0, 255);
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }
    color_i++;
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

