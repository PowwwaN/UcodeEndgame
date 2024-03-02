#include "../inc/minilibmx.h"

void renderTextureToSize(SDL_Texture *texture, int x, int y, int width, int height) {

    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}

void render_loading() {
    SDL_Texture *loading_bg_texture = loadTexture("resource/images/loading_screen(1)(1).jpg");
    if (loading_bg_texture == NULL) {
        printf("Failed to load loading_image_texture: %s\n", IMG_GetError());
        return;
    }
    int i = 0;
    while (game_state == game_state_loading) {
        SDL_RenderClear(renderer);
        SDL_Rect background_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderCopy(renderer, loading_bg_texture, NULL, &background_rect);
        SDL_RenderPresent(renderer);
        i++;
        if (i == 5000) {
            game_state = game_state_playing;
            SDL_DestroyTexture(loading_bg_texture);
            break;
        }
    }
}