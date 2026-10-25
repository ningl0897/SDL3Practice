#include "load_texture.h"
#include "game_internal.h"

bool game_load_texture_SDL(struct game *g, const char *file)
{
	if (file == NULL)
	{
		fprintf(stderr, "Filename error: %s\n", SDL_GetError());
		return false;
	}
	g->background = IMG_LoadTexture(g->renderer, file);
	if (!g->background)
	{
		fprintf(stderr, "error load texture: %s\n", SDL_GetError());
		return false;
	}

	g->game_font = TTF_OpenFont("assets/HYWenHeiExtended.ttf", TEXT_SIZE);
	if (g->game_font == NULL)
	{
		fprintf(stderr, "Font not found: %s\n", SDL_GetError());
		return false;
	}

	SDL_Surface *surf = TTF_RenderText_Blended(g->game_font, TEXT_STR, 0, TEXT_COLOR);
	if (!surf)
	{
		fprintf(stderr, "Font conversion texture error: %s\n", SDL_GetError());
		return false;
	}

	g->game_font_texture = SDL_CreateTextureFromSurface(g->renderer, surf);
	SDL_DestroySurface(surf);
	float w = 0, h = 0;
	SDL_GetTextureSize(g->game_font_texture, &w, &h);
	printf("w=%f,h=%f\n", w, h);
	g->game_frect.w = w;
	g->game_frect.h = h;
	g->game_frect.x = 0;
	g->game_frect.y = 0;

	surf = NULL;
	if (!g->game_font_texture)
	{
		fprintf(stderr, "Font conversion texture error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}
