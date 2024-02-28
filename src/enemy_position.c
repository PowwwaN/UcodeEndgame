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
        case 0: // top edge
            enemy->x = (float) (rand() % (int) screen_width);
            enemy->y = 0;
            break;
        case 1: // right edge
            enemy->x = screen_width;
            enemy->y = (float) (rand() % (int) screen_height);
            break;
        case 2: // bot edge
            enemy->x = (float) (rand() % (int) screen_width);
            enemy->y = screen_height;
            break;
        case 3: // left edge
            enemy->x = 0;
            enemy->y = (float) (rand() % (int) screen_height);
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
void update_enemy_position(Enemy *enemy, Hero *hero, float speed, float delta_time) {
    float dx = hero->x - enemy->x;
    float dy = hero->y - enemy->y;

    normalize(&dx, &dy);

    enemy->x += dx * speed * delta_time;
    enemy->y += dy * speed * delta_time;
}
