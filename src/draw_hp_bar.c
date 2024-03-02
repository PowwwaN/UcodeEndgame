#include "../inc/minilibmx.h"


TTF_Font *load_font_for_hp(char *filename) {
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    TTF_Font* font = TTF_OpenFont(filename, 48); // Font size 48
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }
    return font;
}

void render_hp_bar(int hero_hp) {
    int texW = 80;
    int texH = 80;
    SDL_QueryTexture(hp_bar.hud_texture, NULL, NULL, &texW, &texH);
    int bar_x = 22;
    int bar_y = 22;
    SDL_Rect dstrect = {bar_x, bar_y, texW, texH};

    SDL_RenderCopy(renderer, hp_bar.hud_texture, NULL, &dstrect);
    char amount_of_hp[2];
    SDL_Color amount_of_hp_color = {80, 80, 80};
    sprintf(amount_of_hp, "%d", hero_hp);
    SDL_Surface* textSurface = TTF_RenderText_Solid(hp_bar.font, amount_of_hp, amount_of_hp_color);
    if (textSurface == NULL) {
        printf("Unable to create text surface! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    int x = 112;
    int y = 34;
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};

    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
}