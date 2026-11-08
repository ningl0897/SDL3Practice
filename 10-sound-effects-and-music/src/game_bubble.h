#ifndef GAME_BUBBLE_H
#define GAME_BUBBLE_H

#include "game_internal.h"

void bubble_quit(struct game *g);

void draw_player_bubble(SDL_Renderer *renderer, SDL_Texture *texture, SDL_FRect texcursion_frect, int radius);
void draw_text_bubble(SDL_Renderer *renderer, SDL_Texture *texture, SDL_FRect texcursion_frect, int radius);

#endif