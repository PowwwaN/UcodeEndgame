#include "../inc/minilibmx.h"

void menu_start_game_button_action() {
    // TODO:
}

void menu_toggle_sound_button_action() {
    //TODO:
}

void menu_exit_game_button_action() {
    //TODO:
}

void setup_the_music(t_menu_data *menu_data) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        // Handle error
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        // Handle error
    }
    menu_data->menu_music = Mix_LoadMUS(menu_data->path_to_menu_music);
    if (menu_data->menu_music == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        // Handle error
    }

// Play music
    if (Mix_PlayMusic(menu_data->menu_music, -1) == -1) {
        printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
        // Handle error
    }
}
void clean_after_stoppng_menu(t_menu_data *menu_data) {
    SDL_DestroyTexture(menu_data->menu_bg_texture);
    menu_data->menu_bg_texture = NULL;
    TTF_Quit();
    Mix_HaltMusic();
    Mix_FreeMusic(menu_data->menu_music);
}
void make_button_active(t_menu_button *button) {
    button->button_opacity = 255;
}

void make_button_inactive(t_menu_button *button) {
    button->button_opacity = 150;
}

void action_if_mouse_inside_button(t_menu_data *menu_data) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Point mouse_position = {mouseX, mouseY};
    if (SDL_PointInRect(&mouse_position, &menu_data->startButton.rect)) {
        make_button_active(&menu_data->startButton);
    }
    else {
        make_button_inactive(&menu_data->startButton);
    }

    if (SDL_PointInRect(&mouse_position, &menu_data->settingsButton.rect)) {
        make_button_active(&menu_data->settingsButton);
    }
    else {
        make_button_inactive(&menu_data->settingsButton);
    }

    if (SDL_PointInRect(&mouse_position, &menu_data->exitButton.rect)) {
        make_button_active(&menu_data->exitButton);
    }
    else {
        make_button_inactive(&menu_data->exitButton);
    }
}

t_menu_data menu_setup() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        exit(-1);
    }

    t_menu_data menuState;

    menuState.menu_button_opacity = 0;
    menuState.make_buttons_visible = false;
    menuState.menu_buttons_active = false;
    menuState.menu_last_frame_time = 0;
    int button_width = 400;
    int button_height = 100;
    int menu_buttonx_start = (WINDOW_WIDTH / 2) - (button_width / 2);

    menuState.startButton = (t_menu_button){{menu_buttonx_start, 250, button_width, button_height}, 0, "Start", &menu_start_game_button_action};
    menuState.settingsButton = (t_menu_button){{menu_buttonx_start, 400, button_width, button_height}, 0, "Settings", &menu_toggle_sound_button_action};
    menuState.exitButton = (t_menu_button){{menu_buttonx_start, 550, button_width, button_height}, 0, "Exit", &menu_exit_game_button_action};
    menuState.background_texture_path = "./resource/sprites/menu_backgroundv1.jpg";
    menuState.menu_bg_texture = menu_load_texture(menuState.background_texture_path);
    menuState.blinking_message.font = TTF_OpenFont("./resource/fonts/dogica.ttf", 24);
    menuState.blinking_message.blink_duration = 540;
    menuState.blinking_message.last_blink_time = 0;
    menuState.blinking_message.is_visible = true;
    menuState.blinking_is_active = true;
    menuState.path_to_menu_music = "./resource/music_sets/menu_music_for_the_game.mp3";
    return menuState;
}

void menu_process_input(t_menu_data *menu_data, bool *menu_is_running) {
    SDL_Event event;
    int max_amount_of_events = 5;
    while (SDL_PollEvent(&event) && (max_amount_of_events > 0)) {
        switch (event.type) {
            case SDL_QUIT:
                *menu_is_running = false;
                clean_after_stoppng_menu(menu_data);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    clean_after_stoppng_menu(menu_data);
                    *menu_is_running = false;
                    reset_opacity_to_max();
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    menu_data->make_buttons_visible = true;
                    menu_data->menu_buttons_active = true;
                    menu_data->blinking_is_active = false;
                    menu_data->blinking_message.is_visible = false;

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseButtonDown(event, menu_data, menu_is_running);
                break;
        }
        max_amount_of_events--;
    }
}
void menu_update(t_menu_data *menu_data) {
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), menu_data->menu_last_frame_time + FRAME_TARGET_TIME));
    menu_data->menu_last_frame_time = SDL_GetTicks();
    if (menu_data->menu_last_frame_time  - menu_data->blinking_message.last_blink_time  > menu_data->blinking_message.blink_duration) {
        menu_data->blinking_message.is_visible = !menu_data->blinking_message.is_visible;
        menu_data->blinking_message.last_blink_time = menu_data->menu_last_frame_time;
    }
    if (menu_data->menu_buttons_active) {
        action_if_mouse_inside_button(menu_data);
    }
}

void menu_render(t_menu_data *menu_data) {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    render_menu_background(menu_data->menu_bg_texture);
    draw_all_buttons(menu_data);
    draw_blinking_message(menu_data);

    SDL_RenderPresent(renderer);
}