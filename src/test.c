#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Surface *surface = NULL;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool Init(void);
void Render(void);
void Quit(void);

int main(int argc, char *argv[])
{
    if (!Init()) return 1;
    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        Render();
        SDL_Delay(1);
    }

    Quit();
    return 0;
}

bool Init(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    if ((window = SDL_CreateWindow("My SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 480, SDL_WINDOW_SHOWN)) == NULL) {
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

void Render(void)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    static SDL_Rect rect = {100, 100, 50, 50};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    rect.x++;
}

void Quit(void)
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
