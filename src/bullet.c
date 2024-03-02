#include "../inc/minilibmx.h"
#include "../inc/bullet.h"


void process_bullets(float delta_time){


    int x, y;
    Uint32 mouse_state = SDL_GetMouseState(&x, &y);
    if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        create_bullet();
    }


    struct s_bullet* bullet = bullets_list;
    struct s_bullet* prev_bullet = NULL;
    while (bullet != NULL) {
    struct s_bullet* next_bullet = bullet->next_bullet;

    if (last_frame_time - bullet->create_time > bullet->lifetime) {
        bullet->active = false;
    }
    if (!bullet->active) {
        if (prev_bullet != NULL) {
            prev_bullet->next_bullet = next_bullet;
        } else {
            bullets_list = next_bullet;
        }
        if (next_bullet != NULL) {
            next_bullet->previous_bullet = prev_bullet;
        }
        free(bullet);
    } else {
        bullet->x += bullet->direction.x * (bullet->speed * delta_time);
        bullet->y += bullet->direction.y * (bullet->speed * delta_time);
        prev_bullet = bullet;
    }
    bullet = next_bullet;
}


}


void create_bullet(void){
   
  if(SDL_GetTicks() - hero.last_shoot_time < hero.reload_time){
    return;
  }
  hero.last_shoot_time = SDL_GetTicks();

    struct s_bullet* new_bullet_ptr = malloc(sizeof(struct s_bullet));
    if (new_bullet_ptr == NULL) {
        printf("Memory allocation error\n");
        return;
    }
    
    new_bullet_ptr->x = hero.x - 10;
    new_bullet_ptr->y = hero.y + 40;
    new_bullet_ptr->width = 20;
    new_bullet_ptr->height = 20;

    SDL_Point mouse_position;
    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    double angle = atan2f(mouse_position.y - (hero.y + 40), mouse_position.x - (hero.x - 10));

    new_bullet_ptr->direction.x = cosf(angle);
    new_bullet_ptr->direction.y = sinf(angle);
    new_bullet_ptr->speed = BULLET_SPEED;
    new_bullet_ptr->create_time = last_frame_time;
    new_bullet_ptr->lifetime = 2000;
    new_bullet_ptr->previous_bullet = NULL;
    new_bullet_ptr->active = true;

    // Adding a new bullet to the bullet list
    new_bullet_ptr->next_bullet = bullets_list;
    if (bullets_list != NULL) {
        bullets_list->previous_bullet = new_bullet_ptr;
    }
    bullets_list = new_bullet_ptr;
}



