#pragma once
#include "../inc/minilibmx.h"

#define AMOUNT_OF_PLAYERS_EDGES 4

typedef struct s_position_in_room{
    int x;
    int y;
} t_position_in_room;

int is_next_position_object(int hero_width, int hero_height, int x, int y, t_array_represantation_of_the_room current_room_array);