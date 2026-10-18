/*
 * c语言的sdl3练习，第一关，窗口篇。
 */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GAME_SDL_WINDOW_TITLE "hello SDL3, Open Window"
#define GAME_SDL_WINDOW_WIDTH (640)
#define GAME_SDL_WINDOW_HEIGHT (480)
#define GAME_SDL_INIT_FLAGS (SDL_INIT_VIDEO)

struct game {
	SDL_Window *window;
	SDL_Renderer *renderer;
};

bool game_init_SDL(struct game *g);
void game_scene_render(struct game *g);
void game_quit_SDL(struct game *g);


bool game_init_SDL(struct game *g) {
	if (!SDL_Init(GAME_SDL_INIT_FLAGS)) {
		fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
		return false;
	}

	g->window=SDL_CreateWindow(GAME_SDL_WINDOW_TITLE, GAME_SDL_WINDOW_WIDTH, GAME_SDL_WINDOW_HEIGHT, NULL);
	if(g->window == NULL ) {
		fprintf(stderr, "SDL create window error: %s\n", SDL_GetError());
		return false;
	}

	g->renderer = SDL_CreateRenderer(g->window, NULL);
	if(g->renderer == NULL ) {
		fprintf(stderr, "SDL create renderer error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void game_quit_SDL(struct game *g) {
	if(g->renderer != NULL) {
		SDL_DestroyRenderer(g->renderer);
	}

	if(g->window != NULL) {
		SDL_DestroyWindow(g->window);
	}

	SDL_Quit();
}

void game_scene_render(struct game *g) {
	SDL_SetRenderDrawColor(g->renderer, 173, 216, 230, 255);
	SDL_RenderClear(g->renderer);
	SDL_RenderPresent(g->renderer);
}

int main(void) {
	int game_status = EXIT_SUCCESS;

	struct game *game = calloc(1, sizeof(struct game));

	if(game == NULL)
	{
		game_status = EXIT_FAILURE;
		goto cleanup;
	}

	if(game_init_SDL(game)) {
		game_scene_render(game);
		SDL_Delay(3000);
	}
	else {
		game_status = EXIT_FAILURE;
		goto cleanup;
	}

cleanup:
	game_quit_SDL(game);
	free(game);

	return game_status;
}
