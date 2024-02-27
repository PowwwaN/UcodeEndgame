#include "../inc/minilibmx.h"

#define HERO_SPEED 150

void setup() {
  hero.x = 500;      // positition of rectangle by x axis
  hero.y = 500;      // positition of rectangle by y axis
  hero.width = 100;  // width of rectangle
  hero.height = 100; // height of rectangle
  hero.xspeed = 0;
  hero.yspeed = 0;
  room_generator(&current_room_array, 0, 1); // generating the starting room array with no entry and exit up
}

void render() {
  draw_room(current_room_array); // drawing the room, block by block - walls, floor_tiles, entry/exit
  SDL_Rect hero_rect = {hero.x, hero.y, hero.width, hero.height};

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200); // color of a rectangle
  SDL_RenderFillRect(
      renderer,
      &hero_rect); // fills rectangle with predefined size and position

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

  // hero movement
  const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
        hero.yspeed = HERO_SPEED;
    else if (state[SDL_SCANCODE_S])
        hero.yspeed = -HERO_SPEED;
        else hero.yspeed = 0;

    if (state[SDL_SCANCODE_A])
        hero.xspeed = HERO_SPEED;
    else if (state[SDL_SCANCODE_D])
        hero.xspeed = -HERO_SPEED;
    else hero.xspeed = 0;

  int is_object = is_next_position_object(hero.width, hero.height, hero.x - hero.xspeed * delta_time, hero.y - hero.yspeed * delta_time, current_room_array);
  if (is_object == 9) {
    hero.xspeed = 0;
    hero.yspeed = 0;
  }
  else {
  hero.x -= hero.xspeed * delta_time;
  hero.y -= hero.yspeed * delta_time;
  }
}
