#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    float x, y;
} Vec2;

typedef struct {
    int x, y;
} Vec2i;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;

    Vec2i window_size;

    struct {
        Vec2 position;
    } ship;

    struct {
        int last_second;
        int last_frame;
        int delta_ns; // delta in nano seconds?
        float delta;
        int frames;
        int fps; // dont know if i should make it float
    } time;

    struct {
        bool left;
        bool right;
        bool shoot;
    } input;
} State;
