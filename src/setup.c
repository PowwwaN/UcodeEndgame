#include "../inc/minilibmx.h"

Enemy enemies[MAX_ENEMIES];
Enemy enemy;
SDL_Texture *texture;
int max_enemies = MAX_ENEMIES;
int num_enemies = 0;
time_t last_attack_time = 0;
bool hero_invincible = false;

bool timer_active = false;
bool was_attacked = false;

void setup() {

  hero.x = 500;      // positition of rectangle by x axis
  hero.y = 500;      // positition of rectangle by y axis
  hero.width = HERO_WIDTH;  // width of rectangle
  hero.height = HERO_HEIGHT; // height of rectangle
  hero.xspeed = 0;
  hero.yspeed = 0;
  hero.last_shoot_time = 0;
  hero.reload_time = 500;
  room_generator(&current_room_array, 0, 1); // generating the starting room array with no entry and exit up
  bullets_list = NULL;
  hero.hp = 5;
  hero.active = true;

  //    randomize enemies
    srand(time(NULL));

    // initialize enemies
    num_enemies = draw_enemy(enemies, num_enemies, max_enemies);

 
}


void render() {

  draw_room(current_room_array);

  SDL_Rect hero_rect = {hero.x, hero.y, hero.width, hero.height};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200); // color of a rectangle
  SDL_RenderFillRect(
      renderer,
      &hero_rect); // fills rectangle with predefined size and position


  ///////
   hero.texture = loadTexture("./resource/sprites/idle_player.png");
   blit(hero.texture, hero.x, hero.y);

    // draw enemies
    for (int i = 0; i < num_enemies; i++) {
        if (enemies[i].active && enemies[i].type == 0) {
            SDL_Rect enemy_rect = {enemies[i].x, enemies[i].y, enemies[i].width, enemies[i].height};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &enemy_rect);
        } else if (enemies[i].active && enemies[i].type == 1) {
            SDL_Rect enemy_rect = {enemies[i].x, enemies[i].y, enemies[i].width, enemies[i].height};
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &enemy_rect);
        } else if (enemies[i].active && enemies[i].type == 2) {
            SDL_Rect enemy_rect = {enemies[i].x, enemies[i].y, enemies[i].width, enemies[i].height};
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(renderer, &enemy_rect);
        }
    }

    for (int i = 0; i < num_enemies; ++i) {
        if (enemies[i].active && hero.active && hero.hp > 0) {
            if (!hero_invincible) {
                // Проверяем, не находится ли герой в состоянии невосприимчивости
                check_enemy_collision_and_repel(&hero, &enemies[i], hero.texture, &last_attack_time, &timer_active);
            }
        } else if (hero.hp <= 0) {
            hero.active = false;
        }
    }

    if (difftime(time(NULL), last_attack_time) < 1.0) {
        // Если прошло менее одной секунды с последней атаки, герой красный
        SDL_SetTextureColorMod(hero.texture, 255, 0, 0); // Устанавливаем красный цвет
    } else {
        // Возвращаем обычный цвет
        SDL_SetTextureColorMod(hero.texture, 255, 255, 255);
    }
    blit(hero.texture, hero.x, hero.y);

  // rendering bullets

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200); // color of a rectangle
  struct s_bullet* bullet = bullets_list;
  for(;bullet!=NULL;){
    SDL_Rect bullet_rect = {bullet->x, bullet->y, bullet->width, bullet->height};
    SDL_RenderFillRect(renderer, &bullet_rect);
    bullet = bullet->next_bullet;
  }

  // Перевірка колізії куль із ворогами
  bullet = bullets_list;
  while (bullet != NULL) {
      if (bullet->active) {
          SDL_Rect bullet_rect = {bullet->x, bullet->y, bullet->width, bullet->height};
          for (int i = 0; i < num_enemies; ++i) {
               if (enemies[i].active) {
                  SDL_Rect enemy_rect = {enemies[i].x, enemies[i].y, ENEMY_WIDTH, ENEMY_HEIGHT};
                  if (SDL_HasIntersection(&bullet_rect, &enemy_rect)) {
                      // Обробка колізії кулі та ворога тут
                      if (enemies[i].hp == 1) {
                          enemies[i].active = false; // Ворог знищений
                      }
                      enemies[i].hp--; // зменшення здоров'я ворога
                      bullet->active = false; // Куля видалена
                      break; // Виходимо з циклу, якщо колізія вже виявлена
                  }
               }
        }
      }
        bullet = bullet->next_bullet;

  }
  SDL_RenderPresent(renderer);
  // shows renderer
  SDL_RenderClear(renderer);
  SDL_DestroyTexture(hero.texture);
}

void update() {
  // sleep until reach the target frametime (required only if fps capping
  // needed)
 // int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

  //if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
  // SDL_Delay(time_to_wait);
  //}
  
  // Get a delta time time factor converted to seconds to be used to update my
  // objects later.
  float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
  last_frame_time = SDL_GetTicks();

  // hero movement
  hero_movement();

  int is_object = is_next_position_object(hero.width, hero.height, hero.x - hero.xspeed * delta_time, hero.y - hero.yspeed * delta_time, current_room_array);
  if (is_object == 9 || is_object == 1) {
    hero.xspeed = 0;
    hero.yspeed = 0;
  }
  else if (is_object == 3 || is_object == 2) {
    room_exit_transition(&hero, &current_room_array);
    max_enemies++;
    num_enemies = draw_enemy(enemies, num_enemies, max_enemies);
  }
  else {
  hero.x -= hero.xspeed * delta_time;
  hero.y -= hero.yspeed * delta_time;
  }

process_bullets(delta_time);

 

  // Update the enemy position
   for (int i = 0; i < num_enemies; i++) {
        update_enemy_position(&enemies[i], &hero, ENEMY_SPEED, delta_time, enemies, num_enemies);
    }
}
