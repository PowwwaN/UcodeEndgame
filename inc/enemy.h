#ifndef ENEMY_H
#define ENEMY_H

#include "minilibmx.h"

ENEMY_HEIGHT = 5;
ENEMY_WIDTH = 5;
ENEMY_SPEED = 1;

typedef struct {
    SDL_Rect position;
    int type; // Використовуйте це, щоб визначити тип ворога (1, 2 або 3)
    // Додайте інші характеристики ворогів тут
} Enemy;

void initEnemy(Enemy *enemy, int type);
void moveEnemy(Enemy *enemy, Player *player);
void renderEnemy(SDL_Renderer *renderer, Enemy *enemy);
// Додайте додаткові функції, якщо необхідно

#endif /* ENEMY_H */
