#include "../inc/minilibmx.h"
#include "../inc/hero.h"
#include "../inc/enemy.h"

// function for pushing the hero
void check_enemy_collision_and_repel(Hero *hero, const Enemy *enemy) {
    // check if hero and enemy collide
    if (hero->x < enemy->x + ENEMY_WIDTH && hero->x + HERO_WIDTH > enemy->x &&
        hero->y < enemy->y + ENEMY_HEIGHT && hero->y + HERO_HEIGHT > enemy->y) {
        // taking the angle between hero and enemy
        float dx = hero->x - enemy->x;
        float dy = hero->y - enemy->y;
        float angle = atan2(dy, dx) * (180 / M_PI);

        // pushing the hero in the direction of the enemy by 30px
        if (angle >= -45 && angle < 45) {
            hero->x += 30;
        } else if (angle >= 45 && angle < 135) {
            hero->y += 30;
        } else if (angle >= -135 && angle < -45) {
            hero->y -= 30;
        } else {
            hero->x -= 30;
        }
    }
}