#include "../inc/minilibmx.h"
#include "../inc/enemy_position.h"
#define HERO_SPEED 150

Enemy enemies[MAX_ENEMIES];
Enemy enemy;

int num_enemies = 0;

void setup() {
    hero.x = 500;      // positition of rectangle by x axis
    hero.y = 500;      // positition of rectangle by y axis
    hero.width = 100;  // width of rectangle
    hero.height = 100; // height of rectangle
    hero.xspeed = 0;
    hero.yspeed = 0;

//    randomize enemies
    srand(time(NULL));

// initialize enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].width = 30;
        enemies[i].height = 30;
        enemies[i].xspeed = 5;
        enemies[i].yspeed = 5;

        set_enemy_random_position(WINDOW_WIDTH, WINDOW_HEIGHT, &enemies[i]);
        num_enemies++;
    }

}

void render() {
    // RGB and opacity
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Background
    SDL_RenderClear(renderer);

    SDL_Rect hero_rect = {hero.x, hero.y, hero.width, hero.height};

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200); // color of a rectangle
    SDL_RenderFillRect(
            renderer,
            &hero_rect); // fills rectangle with predefined size and position

// draw enemies
    for (int i = 0; i < num_enemies; i++) {
        SDL_Rect enemy_rect = {enemies[i].x, enemies[i].y, enemies[i].width, enemies[i].height};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &enemy_rect);
    }

    SDL_RenderPresent(renderer); // shows renderer

    SDL_Delay(100);

}

void update() {
    // sleep until reach the target frametime (required only if fps capping
    // needed)
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    // Get a delta time time factor converted to seconds to be used to update my
    // objects later.
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    // logic to keep a fixed timestep
    last_frame_time = SDL_GetTicks();

    // hero movement
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
        hero.yspeed = HERO_SPEED;
    else if (state[SDL_SCANCODE_S])
        hero.yspeed = -HERO_SPEED;
    else hero.yspeed = 0;

    if (state[SDL_SCANCODE_A])
        hero.xspeed = HERO_SPEED;
    else if (state[SDL_SCANCODE_D])
        hero.xspeed = -HERO_SPEED;
    else hero.xspeed = 0;

    hero.x -= hero.xspeed * delta_time;
    hero.y -= hero.yspeed * delta_time;

    // Update the enemy position
    for (int i = 0; i < num_enemies; i++) {
//        update_enemy_position(&enemies[i], &hero);

        enemies[i].x += (calculate_dx(&enemies[i], &hero) * enemies[i].xspeed) * (delta_time / 15);
        enemies[i].y += (calculate_dy(&enemies[i], &hero) * enemies[i].yspeed) * (delta_time / 15);
    }
}