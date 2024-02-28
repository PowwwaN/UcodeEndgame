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

void hero_movement(void) {

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W]) {
        hero.yspeed = HERO_SPEED;
        hero.shoot_direction.y = -1;
    } else if (state[SDL_SCANCODE_S]) {
        hero.yspeed = -HERO_SPEED;
        hero.shoot_direction.y = 1;
    } else {
        hero.yspeed = 0;
        hero.shoot_direction.y = 0;
    }
    if (state[SDL_SCANCODE_A]) {
        hero.xspeed = HERO_SPEED;
        hero.shoot_direction.x = -1;
    } else if (state[SDL_SCANCODE_D]) {
        hero.xspeed = -HERO_SPEED;
        hero.shoot_direction.x = 1;
    } else {
        hero.xspeed = 0;
        hero.shoot_direction.x = 0;
    }
}