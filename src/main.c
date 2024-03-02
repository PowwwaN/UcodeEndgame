#include "../inc/minilibmx.h"
#include "../inc/bullet.h"

struct s_hero hero;
int bullets_count;
struct s_bullet *bullets_list;
t_array_represantation_of_the_room current_room_array;
Cursor cursor;
int current_frame;
int currentFrame_x;


SDL_Texture *hero_sheet;
SDL_Texture *idle_sheet;
SDL_Texture *enemy_sheet1;
SDL_Texture *enemy_sheet2;
SDL_Texture *enemy_sheet3;

t_hp_bar hp_bar;

int game_is_running = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int last_frame_time = 0;
t_game_state game_state = game_state_menu;

int main(int argc, char *argv[]) {
    game_is_running = initialize_window();


    SDL_Texture *bg_texture = loadTexture("./resource/sprites/bg.jpg"); // background texture

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


    while (game_is_running) {
        switch (game_state) {
            case game_state_menu:
                SDL_ShowCursor(SDL_ENABLE);
                run_menu();
                break;
            case game_state_playing: {
                init_cursor(&cursor, renderer);

//                load_game_music();
                setup();
                while (game_state == game_state_playing) {
                    update_cursor(&cursor);
                    process_input();
                    update();
                    render();
                    // Render background texture
                    SDL_Rect background_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
                    SDL_RenderCopy(renderer, bg_texture, NULL, &background_rect);

                    // Render cursor texture
                    draw_cursor(&cursor, renderer);
                }
                case game_state_gameover: {
                    game_state = game_state_menu;
                }
                case game_state_loading: {
//                    render_loading();
                        game_state = game_state_playing;
                }
            }
        }
    }

    destroy_window();
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(cursor.texture);
    SDL_DestroyTexture(hero.texture);
    return 0;
}
