#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include "minilibmx.h"

typedef struct s_enemy {
    float x;
    float y;
    float width;
    float height;
    float xspeed;
    float yspeed;
} Enemy;
extern  Enemy enemy;

void set_enemy_random_position(float screen_width, float screen_height,Enemy *enemy);
float distance_between_points(int x1, int y1, int x2, int y2);
void update_enemy_position(Enemy *enemy, Hero *hero);
void render_enemy(SDL_Renderer *renderer, Enemy *enemy);

#define MAX_ENEMIES 5

#endif