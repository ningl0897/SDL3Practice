#include "load_texture.h"
#include "game_internal.h"

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
