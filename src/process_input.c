#include "../inc/minilibmx.h"

void process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    game_is_running = 0;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
      game_is_running = 0;
    break;
  }
}

void hero_movement(void) {

const Uint8 *state = SDL_GetKeyboardState(NULL);

if (state[SDL_SCANCODE_W]){
    hero.yspeed = HERO_SPEED; 
    hero.lastDirection.y = -1;
}
else if (state[SDL_SCANCODE_S]){
    hero.yspeed = -HERO_SPEED; 
    hero.lastDirection.y = 1;
} else {
  hero.yspeed = 0;
  hero.lastDirection.y = 0;
}
if (state[SDL_SCANCODE_A]){
    hero.xspeed = HERO_SPEED; 
    hero.lastDirection.x = -1;
}
else if (state[SDL_SCANCODE_D]){
    hero.xspeed = -HERO_SPEED; 
    hero.lastDirection.x = 1;
} else {
hero.xspeed = 0;
hero.lastDirection.x = 0;
}
}

void bullets(void){
   //bullets
const Uint8 *state = SDL_GetKeyboardState(NULL);
if (state[SDL_SCANCODE_SPACE]){
    // Виправлення проблеми з ініціалізацією структури hero
    printf(""); // Видалено зайвий printf

    struct s_bullet* new_bullet_ptr = malloc(sizeof(struct s_bullet));
    if (new_bullet_ptr == NULL) {
        // Обробка помилки виділення пам'яті
        printf("Memory allocation error\n");
        return;
    }
    
    new_bullet_ptr->x = hero.x;
    new_bullet_ptr->y = hero.y;
    new_bullet_ptr->width = 20;
    new_bullet_ptr->height = 20;
    new_bullet_ptr->direction = hero.lastDirection;
    new_bullet_ptr->speed = 5;
    new_bullet_ptr->create_time = last_frame_time;
    new_bullet_ptr->lifetime = 2000;
    new_bullet_ptr->previous_bullet = NULL;
    new_bullet_ptr->active = true;

    // Додавання нової кулі до списку куль
    new_bullet_ptr->next_bullet = bullets_list;
    if (bullets_list != NULL) {
        bullets_list->previous_bullet = new_bullet_ptr;
    }
    bullets_list = new_bullet_ptr;
}

  struct s_bullet* bullet = bullets_list;
  for(;bullet!=NULL;)
  {
    if(last_frame_time - bullet->create_time > bullet->lifetime)
    {
     // printf("%u - %u", last_frame_time, bullet->create_time);
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