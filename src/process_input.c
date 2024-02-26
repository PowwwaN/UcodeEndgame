#include "../inc/minilibmx.h"

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = 0;
            break;
    }
}

void hero_movement() {
    SDL_Event event;
    SDL_PollEvent(&event);
    // in progress
}