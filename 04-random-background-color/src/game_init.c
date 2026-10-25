#include "game_init.h"
#include "game_internal.h"
#include "init_SDL.h"

struct game* game_init(void) {
	struct game *game=NULL;
	game = calloc(1, sizeof(struct game));

	if(game == NULL){
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
