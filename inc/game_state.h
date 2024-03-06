#pragma once

typedef enum {
    game_state_menu,
    game_state_playing,
    game_state_gameover,
    game_state_loading
} t_game_state;

extern t_game_state next_game_state;
extern t_game_state game_state;

void render_loading();
void game_over_screen();