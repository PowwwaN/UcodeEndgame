#ifndef BULLET_H
#define BULLET_H

#include "minilibmx.h"

void create_bullet(void);
void process_bullets(float delta_time);


struct s_bullet {
  float x;
  float y;
  float width;
  float height;
  SDL_FPoint direction;
  float speed;
  unsigned int lifetime;
  unsigned int create_time;
  struct s_bullet* next_bullet;
  struct s_bullet* previous_bullet;
  bool active;
};
extern struct s_bullet* bullets_list;


#endif
