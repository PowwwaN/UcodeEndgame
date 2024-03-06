#include "../inc/minilibmx.h"
#include "../inc/hero.h"
#include "../inc/enemy.h"

// function for pushing the hero
void check_enemy_collision_and_repel(Hero *hero, const Enemy *enemy, time_t *last_attack_time, bool *timer_active) {
    float distance_from_tile = sqrt(pow(hero->x - TILE_SIZE, 2) + pow(hero->y - TILE_SIZE, 2));
    float distance_to_screen_edge = fminf(hero->x, WINDOW_WIDTH - hero->x);
    distance_to_screen_edge = fminf(distance_to_screen_edge, fminf(hero->y, WINDOW_HEIGHT - hero->y));

    if (distance_from_tile > 50 && distance_to_screen_edge > 100 &&
        (distance_from_tile > REPULSION_DISTANCE ||
         ((hero->x - TILE_SIZE) > REPULSION_DISTANCE) || ((hero->y - TILE_SIZE) > REPULSION_DISTANCE) ||
         ((TILE_SIZE - hero->x) > REPULSION_DISTANCE) || ((TILE_SIZE - hero->y) > REPULSION_DISTANCE))) {
        if (difftime(time(NULL), *last_attack_time) >= 1.0 && !(*timer_active)) {
            *timer_active = true;

            // Check if hero and enemy collide
            if (SDL_HasIntersection(&(SDL_Rect){hero->x, hero->y, HERO_WIDTH, HERO_HEIGHT},
                                    &(SDL_Rect){enemy->x, enemy->y, ENEMY_WIDTH, ENEMY_HEIGHT})) {
                // Taking the angle between hero and enemy
                float dx = (hero->x + (HERO_WIDTH / 2)) - (enemy->x + (ENEMY_WIDTH / 2));
                float dy = (hero->y + (HERO_HEIGHT / 2)) - (enemy->y + (ENEMY_HEIGHT / 2));
                float angle = atan2(dy, dx);

                // Calculate the repulsion vector
                float repulsion_x = cos(angle) * REPULSION_DISTANCE;
                float repulsion_y = sin(angle) * REPULSION_DISTANCE;

                // Apply repulsion to hero position
                hero->x += repulsion_x;
                hero->y += repulsion_y;

                hero->hp -= enemy->damage;

                // Update last attack time
                *last_attack_time = time(NULL);

                hero->attacked = true;
            }
        } else {
            *timer_active = false;
        }
    }
}


void update_hero_animation() {
    if (hero.xspeed == 0 && hero.yspeed > 0) {
        hero.direction = 4; // up
        load_hero(1, 6);
    } else if (hero.yspeed < 0 && hero.xspeed == 0) {
        hero.direction = 0; // down
        load_hero(1, 6);
    }
    if (hero.yspeed == 0 && hero.xspeed > 0) {
        hero.direction = 6; // right
        load_hero(1, 6);
    } else if (hero.yspeed == 0 && hero.xspeed < 0) {
        hero.direction = 2; // left
        load_hero(1, 6);
    }
    if (hero.yspeed > 0 && hero.xspeed > 0) {
        hero.direction = 5; // up-left
        load_hero(1, 6);
    } else if (hero.yspeed < 0 && hero.xspeed > 0) {
        hero.direction = 7; // down-left
        load_hero(1, 6);
    }
    if (hero.yspeed < 0 && hero.xspeed < 0) {
        hero.direction = 1; // down-right
        load_hero(1, 6);
    } else if (hero.yspeed > 0 && hero.xspeed < 0) {
        hero.direction = 3; // up-right
        load_hero(1, 6);
    }
    if (hero.yspeed == 0 && hero.xspeed == 0) {
        load_hero(0, 4);
    }
}
