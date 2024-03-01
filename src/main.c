#include "../inc/minilibmx.h"

struct s_hero hero;
int bullets_count;
struct s_bullet* bullets_list;
t_array_represantation_of_the_room current_room_array;
Cursor cursor;
int currentFrame;
int currentFrame_x;
SDL_Texture *hero_sheet;
SDL_Texture *idle_sheet;

int game_is_running = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int last_frame_time = 0;

int main(int argc, char *argv[]) {
  game_is_running = initialize_window();
  run_menu();
  
  SDL_Texture *bg_texture = loadTexture("./resource/sprites/bg.jpg"); // background texture
  

  ///////  ///////  ///////  /////// ///////
  /// loading hero
  ///  ///////  ///////  ///////  ///////  ///////
  hero_sheet = loadTexture(
      "./resource/sprites/Sprite-list.png"); // Set initial animation frame and
                                             // direction
  currentFrame = 0;
  ///////  ///////  ///////  /////// ///////
  /// loading hero
  ///  ///////  ///////  ///////  ///////  ///////

  ///////  ///////  ///////  /////// ///////
  /// loading hero
  ///  ///////  ///////  ///////  ///////  ///////
  idle_sheet = loadTexture("./resource/sprites/idle.png");

  currentFrame_x = 0;
  ///////  ///////  ///////  /////// ///////
  /// loading hero
  ///  ///////  ///////  ///////  ///////  ///////
  
  init_cursor(&cursor, renderer);

  setup();
  while (game_is_running) {
    update_cursor(&cursor);
    process_input();
    update();
    render();

    // Render background texture
    SDL_Rect background_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, bg_texture, NULL, &background_rect);

    // Render cursor texture
    draw_cursor(&cursor, renderer);
  }
  
  destroy_window();
  SDL_DestroyTexture(bg_texture);
  SDL_DestroyTexture(cursor.texture);
  SDL_DestroyTexture(hero.texture);
  return 0;
}
