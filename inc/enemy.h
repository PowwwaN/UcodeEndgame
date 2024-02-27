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
    bool active;
} Enemy;
extern  Enemy enemy;

void set_enemy_random_position(float screen_width, float screen_height,Enemy *enemy);
float distance_between_points(int x1, int y1, int x2, int y2);
void update_enemy_position(Enemy *enemy, Hero *hero);
void render_enemy(SDL_Renderer *renderer, Enemy *enemy);
float calculate_dx(Enemy *enemy, Hero *hero);
float calculate_dy(Enemy *enemy, Hero *hero);
#define MAX_ENEMIES 5
#define ENEMY_WIDTH 60
#define ENEMY_HEIGHT 60
#define ENEMY_SPEED 2

#endif