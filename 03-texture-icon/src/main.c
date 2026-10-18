/*
 * c语言的sdl3练习，第三，纹理篇。
 */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GAME_SDL_WINDOW_TITLE "Texture background and icons."
#define GAME_SDL_WINDOW_WIDTH (640)
#define GAME_SDL_WINDOW_HEIGHT (480)
#define GAME_SDL_INIT_FLAGS (SDL_INIT_VIDEO)

struct game {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
	bool running;
};

struct game* game_init(void);
void game_quit(struct game *g);
bool game_run(struct game *g);

bool game_init_SDL(struct game *g);
void game_render(struct game *g);
void game_quit_SDL(struct game *g);
void game_event_message_SDL(struct game *g);
double game_get_fps(Uint64 *t);
bool game_load_texture_SDL(struct game *g, const char *file);
static void game_prefer_x11(void);


bool game_init_SDL(struct game *g) {
	game_prefer_x11();

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

	SDL_Surface *icon =IMG_Load("icon.ico");
	if(icon == NULL ) {
		fprintf(stderr, "Error load img: %s\n", SDL_GetError());
		return false;
	}
	if(!SDL_SetWindowIcon(g->window, icon)){
		fprintf(stderr, "Error set icon: %s\n", SDL_GetError());
		SDL_DestroySurface(icon);
		return true;
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

void game_render(struct game *g) {
	SDL_SetRenderDrawColor(g->renderer, 23, 66, 80, 255);
	SDL_RenderClear(g->renderer);

	SDL_RenderTexture(g->renderer, g->background, NULL, NULL);

	SDL_RenderPresent(g->renderer);
}

static void game_prefer_x11(void)
{
	// 如果支持 x11 则使用，用来显示图标窗口
	if (SDL_getenv("DISPLAY") != NULL)
	{
		SDL_SetHintWithPriority(
			SDL_HINT_VIDEO_DRIVER, "x11", SDL_HINT_OVERRIDE);
	}
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

	game->running = true;

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
				g->running = false;
			break;
		}
	}
}

double game_get_fps(Uint64 *t){
	Uint64 now=SDL_GetPerformanceCounter();
	double frequency=SDL_GetPerformanceFrequency();
	double delta_time=(now - *t)/frequency;
	*t=now;
	return 1.0/delta_time;
}

bool game_load_texture_SDL(struct game *g, const char *file){
	if(file == NULL){
		fprintf(stderr, "Filename error: %s\n", SDL_GetError());
		return false;
	}
	g->background=IMG_LoadTexture(g->renderer,file);
	if(!g->background){
		fprintf(stderr, "error load texture: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool game_run(struct game *g){
	Uint64 fps_tick=SDL_GetPerformanceCounter();
	game_load_texture_SDL(g, "scenery.png");

	while(g->running){
		game_event_message_SDL(g);
		game_render(g);
		SDL_Delay(16);

		printf("\rfps: %.0f",game_get_fps(&fps_tick));
	}
	return true;
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
