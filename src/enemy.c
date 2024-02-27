#include "../inc/minilibmx.h"

void initEnemy(Enemy *enemy, int x, int y, int type) {
    enemy->position.x = x;
    enemy->position.y = y;
    enemy->position.w = ENEMY_WIDTH;
    enemy->position.h = ENEMY_HEIGHT;
    enemy->type = type;
}

void moveEnemy(Enemy *enemy, Player *player) {
    // Рух ворога у напрямку гравця
    int dx = player->position.x - enemy->position.x;
    int dy = player->position.y - enemy->position.y;
    double distance = sqrt(dx * dx + dy * dy);
    int speed = ENEMY_SPEED;

    if (distance > 0) {
        enemy->position.x += (int)(speed * dx / distance);
        enemy->position.y += (int)(speed * dy / distance);
    }
}

void renderEnemy(SDL_Renderer *renderer, Enemy *enemy, SDL_Texture *enemyTexture) {
    SDL_RenderCopy(renderer, enemyTexture, NULL, &enemy->position);
}
