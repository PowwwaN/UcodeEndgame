#include "../inc/minilibmx.h"

void init_cursor(Cursor *cursor, SDL_Renderer *renderer) {
    cursor->texture = IMG_LoadTexture(renderer, "./resource/images/cursor.png");
    cursor->rect.h = 50;
    cursor->rect.w = 50;
    cursor->point.h = 1;
    cursor->point.w = 1;
    SDL_ShowCursor(SDL_DISABLE);
}

void update_cursor(Cursor *cursor) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    cursor->rect.x = x - 25;
    cursor->rect.y = y - 25;
    cursor->point.x = x;
    cursor->point.y = y;
}

void draw_cursor(Cursor *cursor, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, cursor->texture, NULL, &(cursor->rect));
}

