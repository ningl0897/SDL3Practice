/*
 * c语言的sdl3练习，第二，事件篇。
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
	bool game_status;
};

bool game_init_SDL(struct game *g);
void game_scene_render(struct game *g);
void game_quit_SDL(struct game *g);
struct game* game_init(void);
void game_quit(struct game *g);
void game_event_message_SDL(struct game *g);
bool game_run(struct game *g);
double game_get_fps(Uint64 *t);

bool game_init_SDL(struct game *g) {
	if (!SDL_Init(GAME_SDL_INIT_FLAGS)) {
		fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
		return false;
	}

	g->window=SDL_CreateWindow(GAME_SDL_WINDOW_TITLE, GAME_SDL_WINDOW_WIDTH, GAME_SDL_WINDOW_HEIGHT, SDL_WINDOW_TRANSPARENT);
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
	SDL_SetRenderDrawColor(g->renderer, 23, 66, 80, 99);
	SDL_RenderClear(g->renderer);
	SDL_RenderPresent(g->renderer);
}

struct game* game_init(void) {
	struct game *game=NULL;
	game = calloc(1, sizeof(struct game));

	if(game == NULL)
	{
		fprintf(stderr, "error calloc game in game_init()\n");
		return NULL;
	}
	if(!game_init_SDL(game)){
		game_quit(game);
		return NULL;
	}

	game->game_status = true;

	return game;
}

void game_quit(struct game *g){
	if(g){
		game_quit_SDL(g);
		free(g);
	}else{
		fprintf(stderr, "The parameter is NULL\n");
	}
}

void game_event_message_SDL(struct game *g){
	SDL_Event game_event;
	while(SDL_PollEvent(&game_event)){
		switch(game_event.type){
			case SDL_EVENT_QUIT:
				g->game_status = false;
			break;
		}
	}
}

bool game_run(struct game *g){
	Uint64 fps_tick=SDL_GetPerformanceCounter();

	while(g->game_status){
		game_scene_render(g);
		game_event_message_SDL(g);
		SDL_Delay(4);

		printf("\rfps: %.0f",game_get_fps(&fps_tick));
	}
	return true;
}

double game_get_fps(Uint64 *t){
	Uint64 now=SDL_GetPerformanceCounter();
	double frequency=SDL_GetPerformanceFrequency();
	double delta_time=(now - *t)/frequency;
	*t=now;
	return 1.0/delta_time;
}

int main(void) {
	struct game *game = game_init();
	if(game == NULL) {
		return EXIT_FAILURE;
	}

	game_run(game);

	game_quit(game);

	return EXIT_SUCCESS;
}
