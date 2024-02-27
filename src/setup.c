#include "../inc/minilibmx.h"

Enemy enemies[MAX_ENEMIES];
Enemy enemy;

int num_enemies = 0;

void setup() {

    hero.x = 500;      // positition of rectangle by x axis
    hero.y = 500;      // positition of rectangle by y axis
    hero.width = HERO_WIDTH;  // width of rectangle
    hero.height = HERO_HEIGHT; // height of rectangle
    hero.xspeed = 0;
    hero.yspeed = 0;
    hero.last_shoot_time = 0;
    hero.reload_time = 500;

    bullets_list = NULL;

    //    randomize enemies
    srand(time(NULL));

// initialize enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].width = ENEMY_WIDTH;
        enemies[i].height = ENEMY_HEIGHT;
        enemies[i].xspeed = ENEMY_SPEED;
        enemies[i].yspeed = ENEMY_SPEED;
        enemies[i].active = true;

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
        if (enemies[i].active){
            SDL_Rect enemy_rect = {enemies[i].x, enemies[i].y, enemies[i].width, enemies[i].height};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &enemy_rect);
        }
    }

    for (int i = 0; i < num_enemies; ++i) {
        if (enemies[i].active) {
            SDL_Rect hero_rect = {hero.x, hero.y, HERO_WIDTH, HERO_HEIGHT};
            SDL_Rect enemy_rect = {enemies[i].x, enemies[i].y, ENEMY_WIDTH, ENEMY_HEIGHT};
            if (SDL_HasIntersection(&hero_rect, &enemy_rect)) {
                // Обробка колізії тут
                enemies[i].active = false; // Ворог знищений
            }
        }
    }
    // rendering bullets

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200); // color of a rectangle
    struct s_bullet* bullet = bullets_list;
    for(;bullet!=NULL;){
        SDL_Rect bullet_rect = {bullet->x, bullet->y, bullet->width, bullet->height};
        SDL_RenderFillRect(
                renderer,
                &bullet_rect);
        bullet = bullet->next_bullet;
    }
    // Перевірка колізії куль із ворогами
    while (bullet != NULL) {
        if (bullet->active) {
            SDL_Rect bullet_rect = {bullet->x, bullet->y, bullet->width, bullet->height};
            for (int i = 0; i < num_enemies; ++i) {
                if (enemies[i].active) {
                    SDL_Rect enemy_rect = {enemies[i].x, enemies[i].y, ENEMY_WIDTH, ENEMY_HEIGHT};
                    if (SDL_HasIntersection(&bullet_rect, &enemy_rect)) {
                        // Обробка колізії кулі та ворога тут
                        enemies[i].active = false; // Ворог знищений
                        bullet->active = false; // Куля видалена
                        break; // Виходимо з циклу, якщо колізія вже виявлена
                    }
                }
            }
        }
        bullet = bullet->next_bullet;
    }

    SDL_RenderPresent(renderer); // shows renderer


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
    last_frame_time = SDL_GetTicks();


    // hero movement
    hero_movement();

    hero.x -= hero.xspeed * delta_time;
    hero.y -= hero.yspeed * delta_time;

    bullets();



    // Update the enemy position
    for (int i = 0; i < num_enemies; i++) {
//        update_enemy_position(&enemies[i], &hero);

        enemies[i].x += (calculate_dx(&enemies[i], &hero) * enemies[i].xspeed) * (delta_time / 15);
        enemies[i].y += (calculate_dy(&enemies[i], &hero) * enemies[i].yspeed) * (delta_time / 15);
    }
}