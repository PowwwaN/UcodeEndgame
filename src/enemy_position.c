#include <stdlib.h>
#include <time.h>
#include "../inc/minilibmx.h"
#include "../inc/enemy.h"
#include <math.h>


// function to set random enemy position on map edge
void set_enemy_random_position(float screen_width, float screen_height, Enemy *enemy) {

    // getting random edge
    int edge = rand() % 4;

    switch (edge) {
        case 0: // верхний край
            do {
                enemy->x = (float) (rand() % ((int) screen_width - (TILE_SIZE * 2)) + TILE_SIZE);
                enemy->y = 0 + ((ENEMY_HEIGHT / 2) + TILE_SIZE * 1.5);
            } while (enemy->x > hero.x - ENEMY_WIDTH * 1.5 && enemy->x < hero.x + HERO_WIDTH * 1.5 &&
                     enemy->y > hero.y - ENEMY_HEIGHT * 1.5 && enemy->y < hero.y + HERO_HEIGHT * 1.5);
            break;
        case 1: // правый край
            do {
                enemy->x = screen_width - (ENEMY_WIDTH + (ENEMY_WIDTH / 2) + TILE_SIZE * 1.5);
                enemy->y = (float) (rand() % ((int) screen_height - (TILE_SIZE * 2)) + TILE_SIZE);
            } while (enemy->x > hero.x - ENEMY_WIDTH * 1.5 && enemy->x < hero.x + HERO_WIDTH * 1.5 &&
                     enemy->y > hero.y - ENEMY_HEIGHT * 1.5 && enemy->y < hero.y + HERO_HEIGHT * 1.5);
            break;
        case 2: // нижний край
            do {
                enemy->x = (float) (rand() % ((int) screen_width - (TILE_SIZE * 2)) + TILE_SIZE);
                enemy->y = screen_height - (ENEMY_HEIGHT + (ENEMY_HEIGHT / 2) + TILE_SIZE * 1.5);
            } while (enemy->x > hero.x - ENEMY_WIDTH * 1.5 && enemy->x < hero.x + HERO_WIDTH * 1.5 &&
                     enemy->y > hero.y - ENEMY_HEIGHT * 1.5 && enemy->y < hero.y + HERO_HEIGHT * 1.5);
            break;
        case 3: // левый край
            do {
                enemy->x = 0 + ((ENEMY_WIDTH / 2) + TILE_SIZE * 1.5);
                enemy->y = (float) (rand() % ((int) screen_height - (TILE_SIZE * 2)) + TILE_SIZE);
            } while (enemy->x > hero.x - ENEMY_WIDTH * 1.5 && enemy->x < hero.x + HERO_WIDTH * 1.5 &&
                     enemy->y > hero.y - ENEMY_HEIGHT * 1.5 && enemy->y < hero.y + HERO_HEIGHT * 1.5);
            break;
    }
}

void normalize(float *dx, float *dy) {
    float length = sqrt((*dx) * (*dx) + (*dy) * (*dy));
    if (length != 0) {
        *dx /= length;
        *dy /= length;
    }
}

// update enemy position
void update_enemy_position(Enemy *enemy, Hero *hero, float speed, float delta_time, Enemy *other_enemies, int num_other_enemies) {
    float dx = (hero->x + (HERO_WIDTH / 2)) - (enemy->x + (ENEMY_WIDTH / 2));
    float dy = (hero->y + (HERO_HEIGHT / 2)) - (enemy->y + (ENEMY_HEIGHT / 2));
    normalize(&dx, &dy);

    bool collision_detected = false;

    // if there is a collision
    for (int i = 0; i < num_other_enemies; ++i) {
        if (&other_enemies[i] == enemy)
            continue;

        float other_dx = other_enemies[i].x - enemy->x;
        float other_dy = other_enemies[i].y - enemy->y;
        float distance_squared = other_dx * other_dx + other_dy * other_dy;
        float min_distance = (enemy->width + other_enemies[i].width) * 0.5f;

        if (distance_squared < min_distance * min_distance) {
            collision_detected = true;
            break;
        }
    }

    if (collision_detected) {
        // moving to hero
        float min_distance = FLT_MAX;
        float nearest_dx = 0.0f, nearest_dy = 0.0f;
        for (int i = 0; i < num_other_enemies; ++i) {
            if (&other_enemies[i] == enemy)
                continue;
            // calculate distance
            float other_dx = other_enemies[i].x - enemy->x;
            float other_dy = other_enemies[i].y - enemy->y;
            float distance_squared = other_dx * other_dx + other_dy * other_dy;
            if (distance_squared < min_distance) {
                min_distance = distance_squared;
                nearest_dx = other_dx;
                nearest_dy = other_dy;
            }
        }

        // normalize
        dx = -nearest_dx;
        dy = -nearest_dy;
        normalize(&dx, &dy);
    }

    if (collision_detected) {
        // moving away from another enemy
        enemy->x += dx * speed * delta_time;
        enemy->y += dy * speed * delta_time;
    } else {
        // moving to hero
        enemy->x += dx * speed * delta_time;
        enemy->y += dy * speed * delta_time;
    }
}

int draw_enemy(Enemy *enemies, int num_enemies, int max_enemies) {
    num_enemies = 0;
    counter = 0;
    for (int i = num_enemies; i < max_enemies; i++) {
        enemies[i].width = ENEMY_WIDTH;
        enemies[i].height = ENEMY_HEIGHT;
        enemies[i].xspeed = ENEMY_SPEED;
        enemies[i].yspeed = ENEMY_SPEED;
        enemies[i].active = true;
        enemies[i].type = rand() % 3;

        if (enemies[i].type == 0) {
            enemies[i].hp = 1;
            enemies[i].damage = 1;
        } else if (enemies[i].type == 1) {
            enemies[i].hp = 2;
            enemies[i].damage = 1;
        } else if (enemies[i].type == 2) {
            enemies[i].hp = 3;
            enemies[i].damage = 1;
        }

        set_enemy_random_position(WINDOW_WIDTH, WINDOW_HEIGHT, &enemies[i]);
        num_enemies++;
        counter++;
    }
    return num_enemies;
}
