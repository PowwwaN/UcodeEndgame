#include <stdlib.h>
#include <time.h>
#include "../inc/minilibmx.h"
#include <math.h>

//i will do it later

// function to set random enemy position on map edge
//void set_enemy_random_position(Enemy *enemy) {
//    // randomize
//    srand(time(NULL));
//
//    // getting random edge
//    int edge = rand() % 4;
//
//    // getting random position
//    int x, y;
//    int map_width = WINDOW_WIDTH;
//    int map_height = WINDOW_HEIGHT;
//    int enemy_width = 30;
//    int enemy_height = 30;
//
//    switch (edge) {
//        case 0: // top edge
//            x = rand() % (map_width - enemy_width); // rand value x
//            y = -enemy_height; // Place above the top edge
//            break;
//        case 1: // bot edge
//            x = rand() % (map_width - enemy_width); // rand x
//            y = map_height; // Place below the bottom edge
//            break;
//        case 2: // left edge
//            x = -enemy_width; // Place to the left of the left edge
//            y = rand() % (map_height - enemy_height); // rand y
//            break;
//        case 3: // right edge
//            x = map_width; // Place to the right of the right edge
//            y = rand() % (map_height - enemy_height); // rand y
//            break;
//    }
//
//    // enemy position
//    enemy->x = x;
//    enemy->y = y;
//}

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
