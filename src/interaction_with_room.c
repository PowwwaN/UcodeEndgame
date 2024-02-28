#include "../inc/minilibmx.h"

t_position_in_room get_the_position_in_array(t_position_in_room position_of_dot) {
    int x = position_of_dot.x;
    int y = position_of_dot.y;
    t_position_in_room result;
    result.x = x / 20;
    result.y = y / 20;
    return result;
}

int what_object_is_next(int x, int y, int hero_width, int hero_height, t_array_represantation_of_the_room current_room_array) {
    t_position_in_room array_of_positions[AMOUNT_OF_PLAYERS_EDGES];
    t_position_in_room player_left_upper_dot;
    t_position_in_room player_right_upper_dot;
    t_position_in_room player_right_lower_dot;
    t_position_in_room player_left_lower_dot;
    player_left_upper_dot.x = x; player_left_upper_dot.y = y;
    array_of_positions[0] = player_left_upper_dot;
    player_right_upper_dot.x = x + hero_width; player_right_upper_dot.y = y;
    array_of_positions[1] = player_right_upper_dot;
    player_right_lower_dot.x = x + hero_width; player_right_lower_dot.y = y + hero_height;
    array_of_positions[2] = player_right_lower_dot;
    player_left_lower_dot.x = x; player_left_lower_dot.y = y + hero_height;
    array_of_positions[3] = player_left_lower_dot;
    for (int iterator_through_positions = 0; iterator_through_positions < AMOUNT_OF_PLAYERS_EDGES; ++iterator_through_positions) {
        int array_x, array_y;
        t_position_in_room position_in_the_array = get_the_position_in_array(array_of_positions[iterator_through_positions]);
        array_x = position_in_the_array.x;
        array_y = position_in_the_array.y;
        if (current_room_array.array[array_y][array_x] == 9) {
            return 9;
        }
        if (current_room_array.array[array_y][array_x] == 2) {
            return 2;
        }
        if (current_room_array.array[array_y][array_x] == 1) {
            return 1;
        }
    }
    return 0;
}

int is_next_position_object(int hero_width, int hero_height, int x, int y, t_array_represantation_of_the_room current_room_array) {
    return (what_object_is_next(x, y, hero_width, hero_height, current_room_array));
}

void hero_room_transition(struct s_hero *hero, int exit_direction) {
    switch(exit_direction) {
        case 1: {
            hero->y = WINDOW_HEIGHT - 150;
            break;
        }
        case 2:
            hero->x = 80;
            break;
        case 3:
            hero->y = 80;
            break;
        case 4:
            hero->x = WINDOW_WIDTH - 80;
            break;
    }
}

short sync_room_exit_and_entry(int exit_direction) {
    switch(exit_direction) {
        case 1: {
            return 3;
        }
        case 2:
            return 4;
        case 3:
            return 1;
        case 4:
            return 2;
    }
    return 0;
}

short generate_exit_direction(int entry_direction) {
    short new_exit_direction = entry_direction;
    while (new_exit_direction == entry_direction) {
        srand(time(NULL));
        new_exit_direction = (rand() % 4) + 1;
    }
    return new_exit_direction;
}

void next_room_transition(t_array_represantation_of_the_room **current_room) {
    t_array_represantation_of_the_room *new_room = malloc(sizeof(t_array_represantation_of_the_room));
    short new_room_entry_direction = sync_room_exit_and_entry((*current_room)->exit_direction);
    short new_room_exit_direction = generate_exit_direction(new_room_entry_direction);
    room_generator(new_room, new_room_entry_direction, new_room_exit_direction);
    **current_room = *new_room;
}

void room_exit_transition(struct s_hero *hero, t_array_represantation_of_the_room *current_room) {
    hero_room_transition(hero, current_room->exit_direction);
    next_room_transition(&current_room);
}