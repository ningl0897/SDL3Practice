#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GAME_SDL_WINDOW_TITLE "Change the color."
#define GAME_SDL_WINDOW_WIDTH (640)
#define GAME_SDL_WINDOW_HEIGHT (480)
#define GAME_SDL_INIT_FLAGS (SDL_INIT_VIDEO)
#define GAME_SDL_WIN_DEFAULT_FLAGS (SDL_WINDOW_TRANSPARENT | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS | SDL_WINDOW_CENTERED)

struct game {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
	bool running;
};

void game_render(struct game *g);
bool game_run(struct game *g)
double game_get_fps(Uint64 *t);

#endif