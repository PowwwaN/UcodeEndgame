#include "../inc/minilibmx.h"

void run_menu() {
    bool menu_is_running = true;
    t_menu_data menu_data = menu_setup();
    setup_the_music(&menu_data);
    while (menu_is_running) {
        menu_process_input(&menu_data, &menu_is_running);
        menu_update(&menu_data);
        menu_render(&menu_data);
    }
}
