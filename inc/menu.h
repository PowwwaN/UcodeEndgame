#pragma once

#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL_mixer.h>

typedef struct s_menu_button{
    SDL_Rect rect;
    int button_opacity;
    SDL_Texture* inactive_texture;
    SDL_Texture* active_texture;
    char* label;
    void (*onClick)(void); // Function for the click event
} t_menu_button;

typedef struct s_menu_color {
    int red;
    int green;
    int blue;
} t_menu_color;

typedef struct s_blinking_message {
    TTF_Font *font;
    int blink_duration;
    int last_blink_time;
    bool is_visible;
} t_blinking_message;

typedef struct s_menu_data{
    int menu_last_frame_time;

    int menu_button_opacity;
    bool make_buttons_visible;
    bool menu_buttons_active;
    t_menu_button startButton;
    t_menu_button settingsButton;
    t_menu_button exitButton;

    char *background_texture_path;
    SDL_Texture *menu_bg_texture;
    t_blinking_message blinking_message;
    bool blinking_is_active;

    Mix_Music *menu_music;
    char *path_to_menu_music;
} t_menu_data;

void run_menu();
t_menu_data menu_setup();
void setup_the_music(t_menu_data *menu_data);
void menu_process_input(t_menu_data *menu_data, bool *menu_is_running);
void handleMouseButtonDown(SDL_Event e, t_menu_data *menu_data, bool *menu_is_running);
void menu_start_game_button_action();
void menu_update(t_menu_data *menu_data);

void menu_render(t_menu_data *menu_data);
SDL_Texture* menu_load_texture(const char* filepath);
void drawButton(t_menu_button button, int opacity);
void draw_all_buttons (t_menu_data *menu_data);
void draw_blinking_message(t_menu_data *menu_data);
void render_menu_background(SDL_Texture* menu_bg_texture);
void reset_opacity_to_max();