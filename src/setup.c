#include "../inc/minilibmx.h"
#include "../inc/bullet.h"

Enemy enemies[MAX_ENEMIES];
Enemy enemy;
SDL_Texture *texture;
int max_enemies = MAX_ENEMIES;
int num_enemies = 0;
time_t last_attack_time = 0;
bool hero_invincible = false;
bool timer_active = false;
bool was_attacked = false;

bool exit_delay_active = false;
int exit_delay_duration = 1000;
int exit_delay_start_time = 0;

bool open_door = false;

void setup() {

    hero.x = WINDOW_WIDTH / 2;      // positition of rectangle by x axis
    hero.y = WINDOW_HEIGHT / 2;     // positition of rectangle by y axis
    hero.width = HERO_WIDTH;  // width of rectangle
    hero.height = HERO_HEIGHT; // height of rectangle
    hero.xspeed = 0;
    hero.yspeed = 0;
    hero.last_shoot_time = 0;
    hero.reload_time = 500;
    room_generator(&current_room_array, 0, 1); // generating the starting room array with no entry and exit up
    bullets_list = NULL;
    hero.hp = 5;
    hero.active = true;
    hp_bar.hud_texture = loadTexture("resource/sprites/HUD _cropped_v2.png");
    hp_bar.font = load_font_for_hp("resource/fonts/dos_vga_hp_font.ttf");

    //    randomize enemies
    srand(time(NULL));


}


void render() {

    draw_room(current_room_array);


    // draw enemies
    for (int i = 0; i < num_enemies; i++) {
        if (enemies[i].active && enemies[i].type == 0) {
            load_enemy(2, 8, enemies[i].x, enemies[i].y);
        } else if (enemies[i].active && enemies[i].type == 1) {
            load_enemy(3, 8, enemies[i].x, enemies[i].y);
        } else if (enemies[i].active && enemies[i].type == 2) {
            load_enemy(4, 8, enemies[i].x, enemies[i].y);
        }
    }

    time_t current_time = time(NULL);

    for (int i = 0; i < num_enemies; ++i) {
        if (enemies[i].active && hero.active && hero.hp > 0) {
            // checking collision
            if (SDL_HasIntersection(&(SDL_Rect){hero.x, hero.y, HERO_WIDTH, HERO_HEIGHT},
                                    &(SDL_Rect){enemies[i].x, enemies[i].y, ENEMY_WIDTH, ENEMY_HEIGHT})) {
                // checking attack time
                if (difftime(current_time, last_attack_time) >= 1.0) {
                    if (hero.hp > 0) {
                        // pushing hero
                        check_enemy_collision_and_repel(&hero, &enemies[i], &last_attack_time, &timer_active);

                        // changing time
                        last_attack_time = current_time;
                    }
                }
            }
        } else if (hero.hp <= 0) {
            hero.active = false;
        }
    }
    if (difftime(time(NULL), last_attack_time) < 1.0) {
        SDL_SetTextureColorMod(idle_sheet, 255, 0, 0);
        SDL_SetTextureColorMod(hero_sheet, 255, 0, 0);
    } else {
        SDL_SetTextureColorMod(idle_sheet, 255, 255, 255);
        SDL_SetTextureColorMod(hero_sheet, 255, 255, 255);
    }
    blit(hero.texture, hero.x, hero.y);

    // rendering bullets


    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200); // color of a rectangle
    struct s_bullet *bullet = bullets_list;
    for (; bullet != NULL;) {
        SDL_Rect bullet_rect = {bullet->x, bullet->y, bullet->width, bullet->height};
        SDL_RenderFillRect(renderer, &bullet_rect);
        bullet = bullet->next_bullet;
    }




    // Перевірка колізії куль із ворогами





    bullet = bullets_list;
    while (bullet != NULL) {
        if (bullet->active) {
            SDL_Rect bullet_rect = {bullet->x, bullet->y, bullet->width, bullet->height};
            for (int i = 0; i < num_enemies; ++i) {
                if (enemies[i].active) {
                    SDL_Rect enemy_rect = {enemies[i].x, enemies[i].y, ENEMY_WIDTH, ENEMY_HEIGHT};
                    if (SDL_HasIntersection(&bullet_rect, &enemy_rect)) {
                        // Обробка колізії кулі та ворога тут
                        if (enemies[i].hp == 1) {
                            enemies[i].active = false;// Ворог знищений
                        }
                        enemies[i].hp--; // зменшення здоров'я ворога
                        bullet->active = false; // Куля видалена
                        break; // Виходимо з циклу, якщо колізія вже виявлена
                    }
                }
            }
        }
        bullet = bullet->next_bullet;

    }
    render_hp_bar(hero.hp);

    if (exit_delay_active) {
        int current_time = SDL_GetTicks();
        // check if delay is over
        if (current_time - exit_delay_start_time >= exit_delay_duration) {
            num_enemies = draw_enemy(enemies, num_enemies, max_enemies);
            max_enemies++;
            exit_delay_active = false;
            printf("num_enemies: %d\n", num_enemies);
        }
    }
    // shows renderer
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void update() {
    // sleep until reach the target frametime (required only if fps capping
    // needed)
    // int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    //if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    // SDL_Delay(time_to_wait);
    //}

    // Get a delta time time factor converted to seconds to be used to update my
    // objects later.
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    // hero movement
    hero_movement();
    int is_object = is_next_position_object(hero.width, hero.height, hero.x - hero.xspeed * delta_time,
                                            hero.y - hero.yspeed * delta_time, current_room_array);
    if (is_object == 9 || is_object == 1) {
        if (is_horizontal_wall(hero.x - hero.xspeed * delta_time, hero.y - hero.yspeed * delta_time)) {
            hero.yspeed = 0;
            hero.x -= hero.xspeed * delta_time;
        } else if (is_horizontal_wall(hero.x - hero.xspeed * delta_time, hero.y - hero.yspeed * delta_time)) {
            hero.xspeed = 0;
            hero.y -= hero.yspeed * delta_time;
        } else {
            hero.xspeed = 0;
            hero.yspeed = 0;
        }
    } else if ((is_object == 3 || is_object == 2) && open_door == true) {
        room_exit_transition(&hero, &current_room_array);
        num_enemies = 0;
        exit_delay_active = true;
        exit_delay_start_time = SDL_GetTicks();
        // deleting all bullets after transition
        struct s_bullet *bullet = bullets_list;
        while (bullet != NULL) {
            if (bullet->active) {
                bullet->active = false;
            }
            bullet = bullet->next_bullet;
        }
    } else {
        if (hero.xspeed == 0 && hero.yspeed != 0) {
            hero.y -= hero.yspeed * delta_time * sqrt(2);
        } else if (hero.yspeed == 0 && hero.xspeed != 0) {
            hero.x -= hero.xspeed * delta_time * sqrt(2);
        } else {
            hero.x -= hero.xspeed * delta_time;
            hero.y -= hero.yspeed * delta_time;
        }
    }
    if (hero.xspeed == 0 && hero.yspeed > 0) {
        hero.direction = 4; // up
        load_hero(1, 6);
    } else if (hero.yspeed < 0 && hero.xspeed == 0) {
        hero.direction = 0; // down
        load_hero(1, 6);
    }
    if (hero.yspeed == 0 && hero.xspeed > 0) {
        hero.direction = 6; // right
        load_hero(1, 6);
    } else if (hero.yspeed == 0 && hero.xspeed < 0) {
        hero.direction = 2; // left
        load_hero(1, 6);
    }
    if (hero.yspeed > 0 && hero.xspeed > 0) {
        hero.direction = 5; // up-left
        load_hero(1, 6);
    } else if (hero.yspeed < 0 && hero.xspeed > 0) {
        hero.direction = 7; // down-left
        load_hero(1, 6);
    }
    if (hero.yspeed < 0 && hero.xspeed < 0) {
        hero.direction = 1; // down-right
        load_hero(1, 6);
    } else if (hero.yspeed > 0 && hero.xspeed < 0) {
        hero.direction = 3; // up-right
        load_hero(1, 6);
    }
    if (hero.yspeed == 0 && hero.xspeed == 0) {
        load_hero(0, 4);
    }
    process_bullets(delta_time);



    // Update the enemy position
    for (int i = 0; i < num_enemies; i++) {
        update_enemy_position(&enemies[i], &hero, ENEMY_SPEED, delta_time, enemies, num_enemies);
    }
}

void load_game_music() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        // Handle error
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        // Handle error
    }
    Mix_Music *game_main_music = Mix_LoadMUS("resource/music_sets/game_music.mp3");
    if (game_main_music == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        // Handle error
    }

// Play music
    if (Mix_PlayMusic(game_main_music, -1) == -1) {
        printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
        // Handle error
    }
}