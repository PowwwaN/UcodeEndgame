#ifndef CURSOR_H
#define CURSOR_H

#include "minilibmx.h"

typedef struct cursor {
  SDL_Texture *texture;
  SDL_Rect rect;
  SDL_Rect point;

} Cursor;
extern Cursor cursor;

void init_cursor(Cursor *cursor, SDL_Renderer *renderer);
void update_cursor(Cursor *cursor);
void draw_cursor(Cursor *cursor, SDL_Renderer *renderer);

#endif
