#include "../inc/minilibmx.h"
#include "../inc/hero.h"

struct s_hero {
  float x;
  float y;
  float width;
  float height;
  float speed;
} hero;

void setup(){
  hero.x = 500; //positition of rectangle by x axis
  hero.y = 500; //positition of rectangle by y axis
  hero.width = 100; // width of rectangle
  hero.height = 100; //height of rectangle
  hero.speed = 20; 
}

void render() {
                                  //RGB and opacity
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Background
  SDL_RenderClear(renderer);

  SDL_Rect hero_rect = {hero.x, hero.y, hero.width,
                             hero.height};

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200); //color of a rectangle
  SDL_RenderFillRect(renderer, &hero_rect); //fills rectangle with predefined size and position

  SDL_RenderPresent(renderer); // shows renderer
}

void update() {
  //sleep until reach the target frametime (required only if fps capping needed)
//  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

/*   if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
    SDL_Delay(time_to_wait);
  } */
  
  //Get a delta time time factor converted to seconds to be used to update my objects later.
  float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

  //logic to keep a fixed timestep
  last_frame_time = SDL_GetTicks();

  hero.x -= hero.speed * delta_time; 
  hero.y -= hero.speed * delta_time;
}
