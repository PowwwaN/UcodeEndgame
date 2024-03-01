#include "../inc/minilibmx.h"

int min(int a, int b) {
    return a < b ? a : b;
}

bool is_floor(int x, int y, int width, int height) {
    x++;
    y++;
    return x > 1 && x < width && y > 1 && y < height;
}

bool is_entry(int x, int y, short entry_direction, int width, int height) {
    int entry_size = min(width, height) / 4;
    x++;
    y++;
    int distance_between_edge_and_entry;
    if (entry_direction == 0) {
        return false;
    }
    if (entry_direction == 1) { // up direction
        distance_between_edge_and_entry = (width - entry_size) / 2;
        if (y == 1 && (x >= distance_between_edge_and_entry && x < distance_between_edge_and_entry + entry_size)) {
            return true;
        }
        return false;
    }
    if (entry_direction == 2) { // right direction
        distance_between_edge_and_entry = (height - entry_size) / 2;
        if (x == width && (y >= distance_between_edge_and_entry && y < distance_between_edge_and_entry + entry_size)) {
            return true;
        }
        return false;
    }
    if (entry_direction == 3) { // down direction
        distance_between_edge_and_entry = (width - entry_size) / 2;
        if (y == height && (x >= distance_between_edge_and_entry && x < distance_between_edge_and_entry + entry_size)) {
            return true;
        }
        return false;
    }
    if (entry_direction == 4) { // left direction
        distance_between_edge_and_entry = (height - entry_size) / 2;
        if (x == 1 && (y >= distance_between_edge_and_entry && y < distance_between_edge_and_entry + entry_size)) {
            return true;
        }
        return false;
    }
    return false;
}

bool is_exit(int x, int y, short exit_direction, int width, int height) {
    int exit_size = min(width, height) / 4;
    x++;
    y++;
    int distance_between_edge_and_entry;
    if (exit_direction == 0) {
        return false;
    }
    if (exit_direction == 1) { // up direction
        distance_between_edge_and_entry = (width - exit_size) / 2;
        if (y == 1 && (x >= distance_between_edge_and_entry && x < distance_between_edge_and_entry + exit_size)) {
            return true;
        }
        return false;
    }
    if (exit_direction == 2) { // right direction
        distance_between_edge_and_entry = (height - exit_size) / 2;
        if (x == width && (y >= distance_between_edge_and_entry && y < distance_between_edge_and_entry + exit_size)) {
            return true;
        }
        return false;
    }
    if (exit_direction == 3) { // down direction
        distance_between_edge_and_entry = (width - exit_size) / 2;
        if (y == height && (x >= distance_between_edge_and_entry && x < distance_between_edge_and_entry + exit_size)) {
            return true;
        }
        return false;
    }
    if (exit_direction == 4) { // left direction
        distance_between_edge_and_entry = (height - exit_size) / 2;
        if (x == 1 && (y >= distance_between_edge_and_entry && y < distance_between_edge_and_entry + exit_size)) {
            return true;
        }
        return false;
    }
    return false;
}

bool is_ghost_exit(int x, int y, short exit_direction, int width, int height) {
    int exit_size = min(width, height) / 4;
    x++;
    y++;
    int distance_between_edge_and_entry;
    if (exit_direction == 0) {
        return false;
    }
    if (exit_direction == 1) { // up direction
        distance_between_edge_and_entry = (width - exit_size) / 2;
        if (y == 2 && (x >= distance_between_edge_and_entry && x < distance_between_edge_and_entry + exit_size)) {
            return true;
        }
        return false;
    }
    if (exit_direction == 2) { // right direction
        distance_between_edge_and_entry = (height - exit_size) / 2;
        if (x == width - 1 && (y >= distance_between_edge_and_entry && y < distance_between_edge_and_entry + exit_size)) {
            return true;
        }
        return false;
    }
    if (exit_direction == 3) { // down direction
        distance_between_edge_and_entry = (width - exit_size) / 2;
        if (y == height - 1 && (x >= distance_between_edge_and_entry && x < distance_between_edge_and_entry + exit_size)) {
            return true;
        }
        return false;
    }
    if (exit_direction == 4) { // left direction
        distance_between_edge_and_entry = (height - exit_size) / 2;
        if (x == 2 && (y >= distance_between_edge_and_entry && y < distance_between_edge_and_entry + exit_size)) {
            return true;
        }
        return false;
    }
    return false;
}

void filling_the_room_array(t_array_represantation_of_the_room *room_representation) {
    room_representation->width = WINDOW_WIDTH / 20;
    room_representation->height = WINDOW_HEIGHT / 20;
    room_representation->array = malloc(room_representation->height * sizeof(int*));
    for (int i = 0; i < room_representation->height; i++) {
        room_representation->array[i] = malloc(room_representation->width * sizeof(int));
    }

    for (int y = 0; y < room_representation->height; y++) {
        for (int x = 0; x < room_representation->width; x++) {
            if (is_ghost_exit(x, y, room_representation->exit_direction, room_representation->width, room_representation->height)) {
                room_representation->array[y][x] = 3;
            }
            else if (is_floor(x, y, room_representation->width, room_representation->height)) {
                room_representation->array[y][x] = 0; // int representation of the floor/empty space
            }
            else if (is_entry(x, y, room_representation->entry_direction, room_representation->width, room_representation->height)) {
                room_representation->array[y][x] = 1;
            }
            else if (is_exit(x, y, room_representation->exit_direction, room_representation->width, room_representation->height)) {
                room_representation->array[y][x] = 2;
            }
            else {
                room_representation->array[y][x] = 9; // wall
            }
        }
    }
}

void room_generator(t_array_represantation_of_the_room *room_representation, short entry_direction, short exit_direction) {
    room_representation->entry_direction = entry_direction;
    room_representation->exit_direction = exit_direction;
    filling_the_room_array(room_representation);
}
