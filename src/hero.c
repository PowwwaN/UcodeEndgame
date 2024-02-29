#include "../inc/minilibmx.h"
#include "../inc/hero.h"
#include "../inc/enemy.h"

// function for pushing the hero
void check_enemy_collision_and_repel(Hero *hero, const Enemy *enemy, SDL_Texture *texture) {
    // check if hero and enemy collide
    if ((hero->x + (HERO_WIDTH / 2)) < (enemy->x + (ENEMY_WIDTH / 2)) + ENEMY_WIDTH && (hero->x + (HERO_WIDTH / 2)) + HERO_WIDTH > (enemy->x + (ENEMY_WIDTH / 2)) &&
        (hero->y + (HERO_HEIGHT / 2)) < (enemy->y + (ENEMY_HEIGHT / 2)) + ENEMY_HEIGHT && (hero->y + (HERO_HEIGHT / 2)) + HERO_HEIGHT > (enemy->y + (ENEMY_HEIGHT / 2))) {
        // taking the angle between hero and enemy
        float dx = (hero->x + (HERO_WIDTH / 2)) - (enemy->x + (ENEMY_WIDTH / 2));
        float dy = (hero->y + (HERO_HEIGHT / 2)) - (enemy->y + (ENEMY_HEIGHT / 2));
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