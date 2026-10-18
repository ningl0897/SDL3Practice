#include "init_SDL.h"

bool game_init_SDL(struct game *g) {
	if (!SDL_Init(GAME_SDL_INIT_FLAGS)) {
		fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
		return false;
	}

	g->window=SDL_CreateWindow(GAME_SDL_WINDOW_TITLE, GAME_SDL_WINDOW_WIDTH, GAME_SDL_WINDOW_HEIGHT, GAME_SDL_WIN_DEFAULT_FLAGS);
	if(g->window == NULL ) {
		fprintf(stderr, "SDL create window error: %s\n", SDL_GetError());
		return false;
	}

	g->renderer = SDL_CreateRenderer(g->window, NULL);
	if(g->renderer == NULL ) {
		fprintf(stderr, "SDL create renderer error: %s\n", SDL_GetError());
		return false;
	}

	SDL_Surface *icon =IMG_Load("assets/icon.ico");
	if(icon == NULL ) {
		fprintf(stderr, "Error load img: %s\n", SDL_GetError());
		return false;
	}
	if(!SDL_SetWindowIcon(g->window, icon)){
		fprintf(stderr, "Error set icon: %s\n", SDL_GetError());
		SDL_DestroySurface(icon);
		return false;
	}
	SDL_DestroySurface(icon);

	return true;
}

void game_quit_SDL(struct game *g) {
	if(g->background != NULL) {
		SDL_DestroyTexture(g->background);
		g->background = NULL;
	}

	if(g->renderer != NULL) {
		SDL_DestroyRenderer(g->renderer);
		g->renderer = NULL;
	}

	if(g->window != NULL) {
		SDL_DestroyWindow(g->window);
		g->window = NULL;
	}

	SDL_Quit();
}
