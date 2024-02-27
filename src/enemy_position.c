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

float distance_between_points(int x1, int y1, int x2, int y2) {  // distance between enemy and hero
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void update_enemy_position(Enemy *enemy, Hero *hero) {  // func to enemy follow hero
    float dx = hero->x - enemy->x;
    float dy = hero->y - enemy->y;

    // Calculate the distance between enemy and hero
    float distance = sqrt(dx * dx + dy * dy);

    // Normalize the direction vector
    if (distance != 0) {
        dx /= distance;
        dy /= distance;
    }

    // Set the speed
    float speed = 5;

    // Move the enemy towards the hero
    enemy->x += dx * speed;
    enemy->y += dy * speed;
}
