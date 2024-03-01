#include "../inc/minilibmx.h"

struct s_hero hero;
int bullets_count;
struct s_bullet *bullets_list;
t_array_represantation_of_the_room current_room_array;
Cursor cursor;
int currentFrame;
SDL_Texture *hero_sheet;

int game_is_running = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int last_frame_time = 0;

int main(int argc, char *argv[]) {
  game_is_running = initialize_window();

  SDL_Texture *bg_texture =
      loadTexture("./resource/sprites/bg.jpg"); // background texture
  init_cursor(&cursor, renderer);

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

  setup();
  while (game_is_running) {
    process_input();
    update();
    load_hero();
    render();
    SDL_Rect background_rect = {0, 0, WINDOW_WIDTH,
                                WINDOW_HEIGHT}; // background texture
    SDL_RenderCopy(renderer, bg_texture, NULL,
                   &background_rect); // background texture
    update_cursor(&cursor);
    draw_cursor(&cursor, renderer);
  }

  destroy_window();
  SDL_DestroyTexture(bg_texture);
  SDL_DestroyTexture(cursor.texture);
  SDL_DestroyTexture(hero.texture);
  return 0;
}
