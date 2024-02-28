#include "../inc/minilibmx.h"

struct s_hero hero;
int bullets_count;
struct s_bullet* bullets_list;
t_array_represantation_of_the_room current_room_array;

int game_is_running = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int last_frame_time = 0;

int main(int argc, char *argv[]) {
  game_is_running = initialize_window();

  setup();
    SDL_Delay(500);
  while (game_is_running) {
    process_input();
    update();
    render();

  }
  destroy_window();

  return 0;
}
