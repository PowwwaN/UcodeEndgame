#include "../inc/minilibmx.h"

t_position_in_room get_the_position_in_array(t_position_in_room position_of_dot) {
    int x = position_of_dot.x;
    int y = position_of_dot.y;
    t_position_in_room result;
    result.x = x / 20;
    result.y = y / 20;
    return result;
}

int is_player_in_the_obstacle(int x, int y, int hero_width, int hero_height, t_array_represantation_of_the_room current_room_array) {
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
    }
    return 0;
}
int is_next_position_object(int hero_width, int hero_height, int x, int y, t_array_represantation_of_the_room current_room_array) {
    if (is_player_in_the_obstacle(x, y, hero_width, hero_height, current_room_array)){
        return 9;
    }
    return 0;
}