#include "../inc/minilibmx.h"
#include "../inc/room_generator.h"

void drawWall(int x, int y) {
    SDL_Rect wall_rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderFillRect(
            renderer,
            &wall_rect);
}
void drawFloor(int x, int y) {
    SDL_Rect floor_rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 0, 50, 50, 200);
    SDL_RenderFillRect(
            renderer,
            &floor_rect);
}
void drawEntry(int x, int y) {
    SDL_Rect entry_rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 0, 0, 30, 200);
    SDL_RenderFillRect(
            renderer,
            &entry_rect);
}

void drawExit(int x, int y) {
    SDL_Rect entry_rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 50, 0, 100, 200);
    SDL_RenderFillRect(
            renderer,
            &entry_rect);
}



void draw_room(t_array_represantation_of_the_room room_representation) {
    int height = room_representation.height;
    int width = room_representation.width;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (room_representation.array[y][x]) {
                case 0: // Floor
 //                   drawFloor(x, y);
                    break;
                case 3: // Floor
 //                   drawFloor(x, y);
                    break;
                case 9: // Wall
                    drawWall(x, y);
                    break;
                case 1: // Entry
                    drawEntry(x, y);
                    break;
                case 2: // Exit
                    drawExit(x, y);
                    break;
            }
        }
    }
}

