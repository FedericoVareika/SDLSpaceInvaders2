#include <SDL2/SDL.h>
#include <stdbool.h>

#define SHIP_SPEED 100

typedef struct {
    float x, y;
} Vec2;

typedef struct {
    int x, y;
} Vec2i;

typedef struct {
    bool running;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    Vec2i window_size;
    Vec2i game_size;

    struct {
        Vec2 position;
    } ship;

    struct {
        Uint64 last_second;
        Uint64 last_frame;
        Uint64 delta_ms; // changed to ms
        double delta;
        Uint64 frames;
        Uint64 fps; // dont know if i should make it float
    } time;

    struct {
        bool left;
        bool right;
        bool shoot;
    } input;
} State;

void process_input(State *state);
void update(State *state);
void render(State *state);
