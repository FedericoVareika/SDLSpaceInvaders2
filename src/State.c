#include "State.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"

void process_input(State *state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            state->running = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                state->running = false;
                break;
            case SDLK_LEFT:
            case SDLK_a:
                state->input.left = true;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                state->input.right = true;
                break;
            case SDLK_SPACE:
                state->input.shoot = true;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_a:
                state->input.left = false;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                state->input.right = false;
                break;
            case SDLK_SPACE:
                state->input.shoot = false;
            }
        }
    }
}

static void update_time(State *state) {
    Uint64 now = SDL_GetPerformanceCounter();
    state->time.frames++;
    // printf("%i\n", (int)now);

    state->time.delta_ms = (now - state->time.last_frame) * 1000 /
                           ((double)SDL_GetPerformanceFrequency());
    state->time.delta = state->time.delta_ms * 0.001f;

    state->time.last_frame = now;

    if ((state->time.last_frame - state->time.last_second) /
            (double)SDL_GetPerformanceFrequency() >
        1) {
        state->time.fps = state->time.frames;
        state->time.frames = 0;
        state->time.last_second = state->time.last_frame;

        printf("FPS: [%lld]\n", (long long)state->time.fps);
    }
}

static void update_ship(State *state) {
    if (state->input.left) {
        state->ship.position.x -= SHIP_SPEED * state->time.delta;
    }
    if (state->input.right) {
        state->ship.position.x += SHIP_SPEED * state->time.delta;
    }
}

void update(State *state) {
    update_time(state);
    update_ship(state);
}

static void render_sprite(const State *state, Vec2i offset, Vec2 position) {
    const SDL_Rect *srcrect = &(SDL_Rect){
        offset.x * 16, offset.y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE};
    const SDL_Rect *dstrect =
        &(SDL_Rect){position.x, position.y, SPRITE_SIZE, SPRITE_SIZE};
    SDL_RenderCopy(state->renderer, state->sprites, srcrect, dstrect);
}

void render(const State *state) {
    // Set a greyish backround color
    SDL_SetRenderDrawColor(state->renderer, 20, 20, 20, 0xFF);
    SDL_RenderClear(state->renderer);

    // Draw texture
    SDL_SetRenderTarget(state->renderer, state->texture);
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(state->renderer);

    // Draw ship
    render_sprite(state, (Vec2i){0, 0}, state->ship.position);

    // Calculate game scale so that the game appears as a "window" inside of the
    // tab
    float game_scale = (float)state->window_size.y / (float)state->game_size.y;

    // Render texture on renderer
    SDL_SetRenderTarget(state->renderer, 0);
    SDL_RenderCopyEx(
        state->renderer,
        state->texture,
        &(SDL_Rect){0, 0, state->game_size.x, state->game_size.y},
        &(SDL_Rect){(state->window_size.x - (game_scale * state->game_size.x)) /
                        2,
                    0,
                    game_scale * state->game_size.x,
                    game_scale * state->game_size.y},
        0,
        0,
        SDL_FLIP_VERTICAL);
    SDL_RenderPresent(state->renderer);
}
