#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "State.h"
#include <SDL2/SDL.h>
#include <stdio.h>

State state;

int main(void) {
    printf("hello world\n");

    state.window = SDL_CreateWindow("Space Shooting Sim",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    1600,
                                    900,
                                    0);
    if (!state.window) {
        fprintf(stderr, "Error creating window\n");
        return 1;
    }

    // state.renderer = SDL_GetRenderer(state.window);
    state.renderer = SDL_CreateRenderer(state.window, -1, 0);
    if (!state.renderer) {
        fprintf(stderr, "Error fetching renderer\n");
        return 1;
    }

    return 0;
}
