#include "../inc/minilibmx.h"
#include "../inc/hero.h"
#include "../inc/enemy.h"

// function for pushing the hero
void check_enemy_collision_and_repel(Hero *hero, const Enemy *enemy, time_t *last_attack_time, bool *timer_active) {
    // Проверяем, прошло ли достаточно времени с момента последнего удара и таймер не активен
    if (difftime(time(NULL), *last_attack_time) >= 1.0 && !(*timer_active)) {
        // Активируем таймер
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

            // Damage hero
            hero->hp -= enemy->damage;

            // Update last attack time
            *last_attack_time = time(NULL);
        }
    } else {
        // Если таймер уже активен и время не прошло, сбрасываем таймер
        *timer_active = false;
    }
}