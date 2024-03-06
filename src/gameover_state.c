#include "../inc/minilibmx.h"

void render_gameover( ) {
    SDL_Surface* tempSurface = IMG_Load("resource/images/game_over_screen.jpg");
    SDL_Texture* game_over_screen_texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    SDL_SetTextureBlendMode(game_over_screen_texture, SDL_BLENDMODE_BLEND);

    if (!game_over_screen_texture) {
        printf("Failed to load texture: %s\n", SDL_GetError());
        // Handle error appropriately
    }

    TTF_Font *gameover_font = TTF_OpenFont("resource/fonts/dogica.ttf", 24); // 24 is the font size
    if (gameover_font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return;
    }
    // making game over screen visible
    for (int alpha = 0; alpha <= 255; alpha += 5) {
        SDL_SetTextureAlphaMod(game_over_screen_texture, alpha);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        int size_of_game_over_screen = 600;
        SDL_Rect gameover_rect = {(WINDOW_WIDTH / 2 - size_of_game_over_screen / 2), (WINDOW_HEIGHT / 2 - size_of_game_over_screen / 2),
                                  size_of_game_over_screen, size_of_game_over_screen};
        SDL_RenderCopy(renderer, game_over_screen_texture, NULL, &gameover_rect);

        // Update the screen
        SDL_RenderPresent(renderer);

        // Wait a bit before changing the opacity again
        SDL_Delay(10); // Adjust delay for faster or slower fade
    }
    SDL_Delay(3000);
}

void game_over_screen() {
    render_gameover();
}