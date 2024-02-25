#include "../inc/minilibmx.h"


void initPlayer(Player *player, int x, int y) {
    player->position.x = x;
    player->position.y = y;
    player->position.w = PLAYER_WIDTH; 
    player->position.h = PLAYER_HEIGHT; 
}

void movePlayer(Player *player, int dx, int dy) {
    player->position.x += dx;
    player->position.y += dy;
}

void renderPlayer(SDL_Renderer *renderer, Player *player, SDL_Texture *playerTexture) {
    SDL_RenderCopy(renderer, playerTexture, NULL, &player->position);
}

void attack(Player *player) {
    // Логіка атаки гравця
}
