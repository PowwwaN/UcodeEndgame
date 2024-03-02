#ifndef ENEMY_H
#define ENEMY_H

#include "hero.h"
#include "minilibmx.h"

typedef struct s_enemy {
    float x;
    float y;
    float width;
    float height;
    float xspeed;
    float yspeed;
    bool active;
    int type;
    int hp;
    bool avoid;
    int damage;
} Enemy;
extern  Enemy enemy;

extern SDL_Texture *enemy_sheet1;
extern SDL_Texture *enemy_sheet2;
extern SDL_Texture *enemy_sheet3;
void load_enemy(int action, int numFrames, int x, int y);

void set_enemy_random_position(float screen_width, float screen_height,Enemy *enemy);
float distance_between_points(int x1, int y1, int x2, int y2);
void update_enemy_position(Enemy *enemy, Hero *hero, float speed, float delta_time, Enemy *other_enemies, int num_other_enemies);
void render_enemy(SDL_Renderer *renderer, Enemy *enemy);
void normalize(float *dx, float *dy);
void check_enemy_collision_and_repel(Hero *hero, const Enemy *enemy, time_t *last_attack_time, bool *timer_active);
int draw_enemy(Enemy *enemies, int num_enemies, int max_enemies);
#define MAX_ENEMIES 5
#define ENEMY_WIDTH 60
#define ENEMY_HEIGHT 60
#define ENEMY_SPEED 200

#endif // ENEMY_H
