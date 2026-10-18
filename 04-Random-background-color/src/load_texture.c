#include "load_texture.h"

bool game_load_texture_SDL(struct ganme *g, const char *file){
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
