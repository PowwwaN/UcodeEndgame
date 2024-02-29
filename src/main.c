#include "../inc/minilibmx.h"

struct s_hero hero;
int bullets_count;
struct s_bullet* bullets_list;
t_array_represantation_of_the_room current_room_array;
Cursor cursor;

int game_is_running = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int last_frame_time = 0;

int main(int argc, char *argv[]) {
  game_is_running = initialize_window();

  
  SDL_Texture *bg_texture = loadTexture("./resource/sprites/bg.jpg"); // background texture
  init_cursor(&cursor, renderer);

  setup();
  while (game_is_running) {
    process_input();
    update();
    render();
    SDL_Rect background_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};// background texture
    SDL_RenderCopy(renderer, bg_texture, NULL, &background_rect);     // background texture
    update_cursor(&cursor);
    draw_cursor(&cursor, renderer);
  }
  
  destroy_window();
  SDL_DestroyTexture(bg_texture);
  SDL_DestroyTexture(cursor.texture);
  return 0;
}
