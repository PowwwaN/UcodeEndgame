#ifndef PLAYER_H
#define PLAYER_H

#include "minilibmx.h"

PLAYER_WIDTH = 10;
PLAYER_HEIGHT = 10;

typedef struct {
    SDL_Rect position;
    // Додайте інші характеристики гравця тут
} Player;

void initPlayer(Player *player);
void movePlayer(Player *player, int dx, int dy);
void renderPlayer(SDL_Renderer *renderer, Player *player);
void attack(Player *player);
// Додайте додаткові функції, якщо необхідно

#endif /* PLAYER_H */
