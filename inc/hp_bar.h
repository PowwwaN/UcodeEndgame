#pragma once

typedef struct s_hp_bar {
    SDL_Texture *hud_texture;
    TTF_Font  *font;
} t_hp_bar;
extern t_hp_bar hp_bar;

TTF_Font *load_font_for_hp(char *filename);