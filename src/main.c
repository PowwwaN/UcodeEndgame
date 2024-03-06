#include "../inc/minilibmx.h"
#include "../inc/bullet.h"

struct s_hero hero;
int bullets_count;
struct s_bullet *bullets_list;
SDL_Texture **bullet_textures;
t_array_represantation_of_the_room current_room_array;
Cursor cursor;
int current_frame;
int currentFrame_x;


SDL_Texture *hero_sheet;
SDL_Texture *idle_sheet;
SDL_Texture *enemy_sheet1;
SDL_Texture *enemy_sheet2;
SDL_Texture *enemy_sheet3;
SDL_Texture *wall_texture;
SDL_Texture *wall_exit_texture;
SDL_Texture *bg_texture;
SDL_Texture *wall_entry_texture;
t_hp_bar hp_bar;

int game_is_running = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int last_frame_time = 0;
t_game_state game_state = game_state_menu;
t_game_state next_game_state = game_state_loading;

int main(int argc, char *argv[]) {
    game_is_running = initialize_window();


    bg_texture = loadTexture("./resource/sprites/bg.jpg"); // background texture

    ///////  ///////  ///////  /////// ///////
    /// loading hero
    ///  ///////  ///////  ///////  ///////  ///////
    hero_sheet = loadTexture(
            "./resource/sprites/Sprite-list.png"); // Set initial animation frame and
    // direction
    current_frame = 0;
    ///////  ///////  ///////  /////// ///////
    /// loading hero
    ///  ///////  ///////  ///////  ///////  ///////

    ///////  ///////  ///////  /////// ///////
    /// loading hero
    ///  ///////  ///////  ///////  ///////  ///////
    idle_sheet = loadTexture("./resource/sprites/idle.png");

    current_frame = 0;
    ///////  ///////  ///////  /////// ///////
    /// loading hero
    ///  ///////  ///////  ///////  /////////

    ///////  ///////  ///////  /////// ///////
    /// loading enemy
    ///  ///////  ///////  ///////  /////////
    enemy_sheet1 = loadTexture("./resource/enemies/White-sprite.png");
    current_frame = 0;
    enemy_sheet2 = loadTexture("./resource/enemies/Blue-sprite.png");
    current_frame = 0;
    enemy_sheet3 = loadTexture("./resource/enemies/Red-sprite.png");
    current_frame = 0;
    ///////  ///////  ///////  /////// ///////
    /// loading enemy
    ///  ///////  ///////  ///////  /////////
    ///////  ///////  ///////  /////// ///////
    /// loading bullet
    ///  ///////  ///////  ///////  /////////

    //for (int i = 0; i < 8; i++) {
    // char filename[35];
    //sprintf(filename, "./resource/bullets/%d.png", i + 1);
    //  bullet_textures = loadTexture("./resource/bullets/1.png");

    //}

    ///////  ///////  ///////  /////// ///////
    /// loading bullet
    ///  ///////  ///////  ///////  /////////
    wall_texture = loadTexture("./resource/sprites/wall_image_v3.png");
    wall_exit_texture = loadTexture("./resource/sprites/wall_exit_image.jpg");
    wall_entry_texture = loadTexture("./resource/sprites/wall_image_v2.jpg");

    while (game_is_running) {
        switch (game_state) {
            case game_state_menu:
                SDL_ShowCursor(SDL_ENABLE);
                next_game_state = game_state_loading;
                run_menu();
                break;
            case game_state_playing: {
                next_game_state = game_state_gameover;
                init_cursor(&cursor, renderer);

                load_game_music();
                setup();
                while (game_state == game_state_playing) {
                    process_input();
                    update();
                    render();
                    // // Render background texture
                    // SDL_Rect background_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
                    // SDL_RenderCopy(renderer, bg_texture, NULL, &background_rect);

                    // // Render cursor texture
                    // draw_cursor(&cursor, renderer);
                    // update_cursor(&cursor);
                }
                case game_state_gameover: {
                    game_over_screen();
                    next_game_state = game_state_menu;
                    game_state = game_state_loading;
                }
                case game_state_loading: {
                    render_loading();
                }
            }
        }
    }

    destroy_window();
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(hero.texture);
    SDL_DestroyTexture(wall_texture);
    SDL_DestroyTexture(wall_exit_texture);
    SDL_DestroyTexture(wall_entry_texture);
    SDL_DestroyTexture(cursor.texture);
    return 0;
}
