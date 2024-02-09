#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_video.h"
#include "State.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb_image.h"

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

    const char *filename = "sprites/sprites.png";
    int x, y, n, ok;
    ok = stbi_info(filename, &x, &y, &n);
    if (!ok) {
        printf("could not get png info\n");
        return 0;
    }
    stbi_set_flip_vertically_on_load(true);
    unsigned char *sprites = stbi_load(filename, &x, &y, &n, 0);

    SDL_Surface *sprite_surface = SDL_CreateRGBSurfaceWithFormatFrom(
        sprites, x, y, n, x * n, SDL_PIXELFORMAT_ARGB8888);
    state->sprites =
        SDL_CreateTextureFromSurface(state->renderer, sprite_surface);

    SDL_FreeSurface(sprite_surface); // Not sure if this is ok
    stbi_image_free(sprites);        // This either

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
