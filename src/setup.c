#include "minilibmx.h"
#include <SDL2/SDL_timer.h>
#include <time.h>

struct s_rectangle {
  float x;
  float y;
  float width;
  float height;
} t_rectangle;

void setup(){
  t_rectangle.x = 500; //positition of rectangle by x axis
  t_rectangle.y = 500; //positition of rectangle by y axis
  t_rectangle.width = 100; // width of rectangle
  t_rectangle.height = 100; //height of rectangle
}

void render() {
                                  //RGB and opacity
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Background
  SDL_RenderClear(renderer);

  SDL_Rect rectangle_rect = {t_rectangle.x, t_rectangle.y, t_rectangle.width,
                             t_rectangle.height};

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 200); //color of a rectangle
  SDL_RenderFillRect(renderer, &rectangle_rect); //fills rectangle with predefined size and position

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

  t_rectangle.x -= 20 * delta_time; 
  t_rectangle.y -= 10 * delta_time;
}
