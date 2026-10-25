#include "load_texture.h"
// #include "game_internal.h"

bool game_load_texture_SDL(struct game *g, const char *file){
	
	return true;
}
bool text_load(struct const game *g ,const char *file);   // 加载字体与文字纹理，待定稿
{
if(file == NULL){
		fprintf(stderr, "Filename error: %s\n", SDL_GetError());
		return false;
	}
	
struct text *t=NULL;
	t = calloc(1, sizeof(struct text));

	if(t == NULL){
		fprintf(stderr, "error calloc text in text_load()\n");
		return NULL;
	}
	t->background=g->background;

	t->background=IMG_LoadTexture(t->renderer,file);
	if(!t->background){
		fprintf(stderr, "error load texture: %s\n", SDL_GetError());
		return false;
	}

	t->font = TTF_OpenFont("assets/\"HYWenHei Extended.ttf\"", TEXT_SIZE,);
	if(!t->font ==NULL){
		fprintf(stderr, "Font not found: %s\n", SDL_GetError());
		return false;
	}

	SDL_Surface *surf=TTF_RenderText_Blended(t->font, TEXT_STR, 0, TEXT_COLOR);
	if(!surf){
		fprintf(stderr, "Font conversion texture error: %s\n", SDL_GetError());
		return false;
	}

	t->frect.w=(float)surf->W;
	t->frect.h=(float)surf->h;

	t->font_texture=SDL_CreateTextureFromSurface(t->renderer, surf);
	SDL_DestroySurface(surf);
	surf=NULL;
	if(!t->font_texture ){
		fprintf(stderr, "Font conversion texture error: %s\n", SDL_GetError());
		return false;
	return true;
}
void text_quit(struct text *t);   // 释放纹理与字体，待定稿
{
if(t){
		t->background=NULL;
		free(t);
		g->text=NULL;
	}else{
		fprintf(stderr, "The parameter is NULL\n");
	}
}
}

static void text_update(struct text *t)  // 动画在此实现
{
float speed=0.0f;
if(t->frect.w>GAME_SDL_WINDOW_WIDTH)
{
speed=-TEXT_SPEED
}
if(t->frect.w>GAME_SDL_WINDOW_HEIGHT)
{
speed=-TEXT_SPEED
}
t->frect.w+=speed;
t->frect.h+=speed;

}