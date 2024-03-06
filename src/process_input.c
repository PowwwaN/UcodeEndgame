#include "../inc/minilibmx.h"

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game_state = game_state_gameover;
                }
            break;
    }
}

void hero_movement(void) {

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W]) {
        hero.yspeed = HERO_SPEED;
    } else if (state[SDL_SCANCODE_S]) {
        hero.yspeed = -HERO_SPEED;
    } else {
        hero.yspeed = 0;
    }
    if (state[SDL_SCANCODE_A]) {
        hero.xspeed = HERO_SPEED;
    } else if (state[SDL_SCANCODE_D]) {
        hero.xspeed = -HERO_SPEED;
    } else {
        hero.xspeed = 0;
    }
}