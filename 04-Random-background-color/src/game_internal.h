#ifndef GAME_INTERNAL_H
#define GAME_INTERNAL_H

#include "game.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GAME_SDL_WINDOW_TITLE "Change the color."
#define GAME_SDL_WINDOW_WIDTH (640)
#define GAME_SDL_WINDOW_HEIGHT (480)
#define GAME_SDL_INIT_FLAGS (SDL_INIT_VIDEO)
#define GAME_SDL_WIN_DEFAULT_FLAGS (SDL_WINDOW_TRANSPARENT | SDL_WINDOW_RESIZABLE)

struct game {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
	bool running;
	Uint8 r;
	Uint8 g;
	Uint8 b;
};

#endif
