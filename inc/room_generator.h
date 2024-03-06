#pragma once

#include <stdbool.h>

#define TILE_SIZE 20

typedef struct s_array_represantation_of_the_room {
    int **array;
    int width;
    int height;
    short entry_direction;
    short exit_direction;
} t_array_represantation_of_the_room;
extern t_array_represantation_of_the_room current_room_array;

void room_generator(t_array_represantation_of_the_room *room_representation, short entry_direction, short exit_direction);
void room_render(t_array_represantation_of_the_room room_representation);
void draw_room(t_array_represantation_of_the_room room_representation);

extern SDL_Texture *wall_entry_texture;
extern SDL_Texture *wall_texture;
extern SDL_Texture *wall_exit_texture;
extern SDL_Texture *bg_texture;
