#include "../inc/minilibmx.h"
#include "../inc/hero.h"

void process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);
  hero_movement();
  switch (event.type) {
  case SDL_MOUSEBUTTONDOWN:
    if(event.button.button == SDL_BUTTON_LEFT){
      create_bullet();
    }
    break;
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
void create_bullet(void){
   
    // Виправлення проблеми з ініціалізацією структури hero
  if(SDL_GetTicks() - hero.last_shoot_time < hero.reload_time){
    return;
  }
  hero.last_shoot_time = SDL_GetTicks();

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

    SDL_Point mouse_position;
    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    double angle = atan2f(mouse_position.y - hero.y, mouse_position.x - hero.x);

    new_bullet_ptr->direction.x = cosf(angle);
    new_bullet_ptr->direction.y = sinf(angle);
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