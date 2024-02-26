#include "minilibmx.h"

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
  // todo
}
