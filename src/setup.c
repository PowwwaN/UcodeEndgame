#include "../inc/minilibmx.h"




void setup() {
  hero.x = 500;      // positition of rectangle by x axis
  hero.y = 500;      // positition of rectangle by y axis
  hero.width = 100;  // width of rectangle
  hero.height = 100; // height of rectangle
  hero.xspeed = 0;
  hero.yspeed = 0;
  hero.last_shoot_time =0;
  hero.reload_time = 500;

  bullets_list = NULL;
  
}

void render() {
  // RGB and opacity
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Background
  SDL_RenderClear(renderer);

  SDL_Rect hero_rect = {hero.x, hero.y, hero.width, hero.height};

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200); // color of a rectangle
  SDL_RenderFillRect(
      renderer,
      &hero_rect); // fills rectangle with predefined size and position

  // rendering bullets

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200); // color of a rectangle
  struct s_bullet* bullet = bullets_list;
  for(;bullet!=NULL;){
    SDL_Rect bullet_rect = {bullet->x, bullet->y, bullet->width, bullet->height};
    SDL_RenderFillRect(
        renderer,
        &bullet_rect);
    bullet = bullet->next_bullet;
  }
  SDL_RenderPresent(renderer); // shows renderer
}

void update() {
  // sleep until reach the target frametime (required only if fps capping
  // needed)
  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    SDL_Delay(time_to_wait);
  }

  // Get a delta time time factor converted to seconds to be used to update my
  // objects later.
  float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

  // logic to keep a fixed timestep
  last_frame_time = SDL_GetTicks();

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_w:
        hero.yspeed = 300;
        hero.lastDirection.y = -1;
        break;
      case SDLK_s:
        hero.yspeed = -300;
        hero.lastDirection.y = 1;
        break;
      case SDLK_a:
        hero.xspeed = 300;
        hero.lastDirection.x = -1;
        break;
      case SDLK_d:
        hero.xspeed = -300;
        hero.lastDirection.x = 1;
        break;
      case SDLK_e:
        //!!! i printf here, because othervise compiler complains about initializing structure !!!
        if(hero.last_shoot_time - last_frame_time < hero.reload_time){
          break;
        }
        printf("");
        struct s_bullet* new_bullet_ptr = malloc(sizeof(struct s_bullet));
        new_bullet_ptr->x = hero.x;
        new_bullet_ptr->y = hero.y;
        new_bullet_ptr->width = 20;
        new_bullet_ptr->height = 20;
        new_bullet_ptr->direction = hero.lastDirection;
        new_bullet_ptr->speed = 5;
        new_bullet_ptr->create_time = last_frame_time;
        new_bullet_ptr->lifetime = 2000;
        new_bullet_ptr->previous_bullet = NULL;
        
        new_bullet_ptr->next_bullet = bullets_list;
        if(bullets_list!= NULL){
          bullets_list->previous_bullet = new_bullet_ptr;
        }
        bullets_list = new_bullet_ptr;
        break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_w:
      case SDLK_s:
        hero.yspeed = 0;
        break;
      case SDLK_a:
      case SDLK_d:
        hero.xspeed = 0;
        break;
      }
      break;
    }
  }

  hero.x -= hero.xspeed * delta_time;
  hero.y -= hero.yspeed * delta_time;

  struct s_bullet* bullet = bullets_list;
  for(;bullet!=NULL;)
  {
    if(last_frame_time - bullet->create_time > bullet->lifetime)
    {
      printf("%u - %u", last_frame_time, bullet->create_time);
      if(bullet->next_bullet != NULL){
        bullet->next_bullet->previous_bullet = bullet->previous_bullet;
      }
      if(bullet->previous_bullet != NULL){
        bullet->previous_bullet->next_bullet = bullet->next_bullet;
      }
      struct s_bullet* next_bullet = bullet->next_bullet;
      if(bullet == bullets_list){
        if(bullet->next_bullet != NULL){
          bullets_list = bullet->next_bullet;
        } 
        else{
          bullets_list = NULL;
        }
      }
      free(bullet);
      bullet = next_bullet;
      continue;
    }
    bullet->x += bullet->direction.x * bullet->speed;
    bullet->y += bullet->direction.y * bullet->speed;
    bullet = bullet->next_bullet;
  }
}