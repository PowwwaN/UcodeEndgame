#include "../inc/minilibmx.h"

void renderTextureToSize(SDL_Texture *texture, int x, int y, int width, int height) {

    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}

char *print_loading_text(int phase_of_loading) {
    switch (phase_of_loading) {
        case 0:
            return "|";
            break;
        case 1:
            return "L|";
            break;
        case 2:
            return "Lo|";
            break;
        case 3:
            return "Loa|";
            break;
        case 4:
            return "Load|";
            break;
        case 5:
            return "Loadi|";
            break;
        case 6:
            return "Loadin|";
            break;
        case 7:
            return "Loading|";
            break;
        case 8:
            return "Loading.";
            break;
        case 9:
            return "Loading..";
            break;
        case 10:
            return "Loading...";
            break;

    }
    return NULL;
}

void render_loading() {
    SDL_Texture *loading_bg_texture = loadTexture("resource/images/loading_screen(1)(1).jpg");
    if (loading_bg_texture == NULL) {
        printf("Failed to load loading_image_texture: %s\n", IMG_GetError());
        return;
    }

    TTF_Font *loading_font = TTF_OpenFont("resource/fonts/dogica.ttf", 24); // 24 is the font size
    if (loading_font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return;
    }
    int i = 0;
    int phase_of_loading = 0;
    srand(time(NULL));
    int loading_duration = (rand() % 5) + 14;
    while (game_state == game_state_loading) {
        SDL_RenderClear(renderer);
        SDL_Rect background_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderCopy(renderer, loading_bg_texture, NULL, &background_rect);
        SDL_Color textColor = {255, 255, 255};  // White color

        SDL_Surface* textSurface = TTF_RenderText_Solid(loading_font, print_loading_text(phase_of_loading), textColor);
        phase_of_loading++;
        if (phase_of_loading == 11) {
            phase_of_loading = 8;
        }
        if (textSurface == NULL) {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            return;
        }
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            return;
        }

        int x = WINDOW_WIDTH - 400;
        int y = WINDOW_HEIGHT - 50;

        SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};

        SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

        SDL_FreeSurface(textSurface);
        SDL_RenderPresent(renderer);
        i++;
        SDL_Delay(200);
        if (i == loading_duration) {
            game_state = next_game_state;
            SDL_DestroyTexture(loading_bg_texture);
            SDL_DestroyTexture(textTexture);
            break;
        }
    }
}