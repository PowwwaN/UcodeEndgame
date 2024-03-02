#include "../inc/minilibmx.h"

void clear_button_textures(t_menu_data *menu_data) {
    SDL_DestroyTexture(menu_data->startButton.active_texture);
    menu_data->startButton.active_texture = NULL;
    SDL_DestroyTexture(menu_data->startButton.active_texture);
    menu_data->startButton.active_texture = NULL;
    SDL_DestroyTexture(menu_data->settingsButton.active_texture);
    menu_data->settingsButton.active_texture = NULL;
    SDL_DestroyTexture(menu_data->settingsButton.inactive_texture);
    menu_data->settingsButton.inactive_texture = NULL;
    SDL_DestroyTexture(menu_data->exitButton.active_texture);
    menu_data->exitButton.active_texture = NULL;
    SDL_DestroyTexture(menu_data->exitButton.inactive_texture);
    menu_data->exitButton.inactive_texture = NULL;
}
SDL_Texture* menu_load_texture(const char* filepath) {
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(filepath);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", filepath, IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", filepath, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void handleMouseButtonDown(SDL_Event e, t_menu_data *menu_data, bool *menu_is_running) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (menu_data->menu_buttons_active) {
        if (SDL_PointInRect(&((SDL_Point) {x, y}), &menu_data->startButton.rect)) {
            menu_data->startButton.onClick();
            *menu_is_running = false;
            game_state = game_state_loading;
            next_game_state = game_state_playing;
            Mix_HaltMusic();
            Mix_FreeMusic(menu_data->menu_music);
            clear_button_textures(menu_data);
        } else if (SDL_PointInRect(&((SDL_Point) {x, y}), &menu_data->settingsButton.rect)) {
            menu_data->settingsButton.onClick();
        } else if (SDL_PointInRect(&((SDL_Point) {x, y}), &menu_data->exitButton.rect)) {
            menu_data->exitButton.onClick();
            Mix_HaltMusic();
            Mix_FreeMusic(menu_data->menu_music);
            *menu_is_running = false;
            game_is_running = false;
            clear_button_textures(menu_data);
        }
    }
}

void drawButton(t_menu_button button, int opacity) {
    if (opacity <= 240 && button.inactive_texture) {
        SDL_SetTextureBlendMode(button.inactive_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(button.inactive_texture, opacity);
        SDL_RenderCopy(renderer, button.inactive_texture, NULL, &button.rect);
    }
    else if (opacity == 255 && button.active_texture) {
        SDL_SetTextureBlendMode(button.active_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(button.active_texture, opacity);
        SDL_RenderCopy(renderer, button.active_texture, NULL, &button.rect);
    }
}

void increase_menu_buttons_opacity(t_menu_data menu_data) {
    if (menu_data.menu_button_opacity <= 220) {
        menu_data.menu_button_opacity += 2;
        menu_data.startButton.button_opacity += 1;
        menu_data.settingsButton.button_opacity += 1;
        menu_data.exitButton.button_opacity += 1;
    }
    else {
        menu_data.make_buttons_visible = false;
    }
}
void draw_all_buttons (t_menu_data *menu_data) {
    if (menu_data->make_buttons_visible == true) {
        increase_menu_buttons_opacity(*menu_data);
    }
    drawButton(menu_data->startButton, menu_data->startButton.button_opacity);
    drawButton(menu_data->settingsButton, menu_data->settingsButton.button_opacity);
    drawButton(menu_data->exitButton, menu_data->exitButton.button_opacity);
}
void render_menu_background(SDL_Texture* menu_bg_texture) {
    SDL_Rect render_menu_bg = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, menu_bg_texture, NULL, &render_menu_bg);
}

void reset_opacity_to_max() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
}

void draw_blinking_message(t_menu_data *menu_data) {
    if (menu_data->blinking_is_active) {
        if (menu_data->blinking_message.is_visible) {
            SDL_Color textColor = {230, 230, 230, 220}; // White color
            SDL_Surface *textSurface = TTF_RenderText_Solid(menu_data->blinking_message.font, "Press Enter to Start...",
                                                            textColor);
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            int text_width = textSurface->w;
            int text_height = textSurface->h;

            // Set rendering space and render to screen
            SDL_Rect renderQuad = {(WINDOW_WIDTH - text_width) / 2, WINDOW_HEIGHT - 100, text_width, text_height};
            SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

            // Get rid of old loaded surface and texture
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
    }
}