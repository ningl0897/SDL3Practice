#include "load_texture.h"

bool load_background(struct game *g, const char *file)
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
	return true;
}
bool load_text(struct game *g) // 加载字体与文字纹理，待定稿
{
	struct text *t = NULL;
	t = calloc(1, sizeof(struct text));
	if (t == NULL)
	{
		fprintf(stderr, "error calloc text in text_load()\n");
		return false;
	}

	t->renderer = g->renderer;
	if (!t->renderer)
	{
		fprintf(stderr, "error load texture: %s\n", SDL_GetError());
		return false;
	}

	t->font = TTF_OpenFont("assets/HYWenHeiExtended.ttf", TEXT_SIZE);
	if (t->font == NULL)
	{
		fprintf(stderr, "Font not found: %s\n", SDL_GetError());
		return false;
	}

	SDL_Surface *surf = TTF_RenderText_Blended(t->font, TEXT_STR, 0, TEXT_COLOR);
	if (!surf)
	{
		fprintf(stderr, "Font conversion texture error: %s\n", SDL_GetError());
		return false;
	}

	t->font_texture = SDL_CreateTextureFromSurface(g->renderer, surf);
	SDL_DestroySurface(surf);
	if (t->font_texture == NULL)
	{
		fprintf(stderr, "Font conversion texture error: %s\n", SDL_GetError());
		return false;
	}

	surf = NULL;

	float w = 0, h = 0;
	SDL_GetTextureSize(t->font_texture, &w, &h);
	printf("w=%f,h=%f\n", w, h);
	t->frect.w = w;
	t->frect.h = h;
	t->frect.x = 0;
	t->frect.y = 0;

	t->speed_x=TEXT_SPEED;
	t->speed_y=TEXT_SPEED;

	g->text = t;
	return true;
}
void text_quit(struct game *g)
{ // 释放纹理与字体，待定稿
	{
		if (g->text)
		{
			g->text->renderer = NULL;
			SDL_DestroyTexture(g->text->font_texture);
			g->text->font_texture = NULL;
			TTF_CloseFont(g->text->font);
			g->text->font = NULL;
			free(g->text);
			g->text = NULL;
		}
		else
		{
			fprintf(stderr, "The parameter is NULL\n");
		}
	}
}

void text_update(struct text *t) // 动画在此实现
{
	if(t->frect.x < 0 || t->frect.x+t->frect.w >= GAME_SDL_WINDOW_WIDTH)
	{
		t->speed_x = -t->speed_x;
	}
		if(t->frect.y < 0 || t->frect.y+t->frect.h >= GAME_SDL_WINDOW_HEIGHT)
	{
		t->speed_y = -t->speed_y;
	}
	t->frect.x += t->speed_x;
	t->frect.y += t->speed_y;
}