#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "State.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int init_state(State *state) {
    state->running = true;

    state->window_size = (Vec2i){1280, 720};
    state->game_size = (Vec2i){224, 256};

    // Create window
    state->window = SDL_CreateWindow("Space Shooting Sim",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     state->window_size.x,
                                     state->window_size.y,
                                     0);
    if (!state->window) {
        fprintf(stderr, "Error creating window\n");
        return 0;
    }

    // Create renderer
    state->renderer = SDL_CreateRenderer(state->window,
                                         -1,
                                         SDL_RENDERER_ACCELERATED |
                                             SDL_RENDERER_PRESENTVSYNC |
                                             SDL_RENDERER_TARGETTEXTURE);
    if (!state->renderer) {
        fprintf(stderr, "Error fetching renderer\n");
        return 0;
    }

    // Create backbuffer
    state->texture = SDL_CreateTexture(state->renderer,
                                       SDL_PIXELFORMAT_ABGR8888,
                                       SDL_TEXTUREACCESS_TARGET,
                                       state->game_size.x,
                                       state->game_size.y);
    if (!state->texture) {
        fprintf(stderr, "Error creating texture backbuffer\n");
        return 0;
    }

    state->ship.position = (Vec2){0, 5};
    printf(
        "Ship pos: (%f, %f)\n", state->ship.position.x, state->ship.position.y);

    return 1;
}

int main(void) {
    State *state = malloc(sizeof(State));
    if (!init_state(state)) {
        return 1;
    }

    while (state->running) {
        process_input(state);
        update(state);
        render(state);
    }

    SDL_DestroyTexture(state->texture);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    free(state);
    return 0;
}
