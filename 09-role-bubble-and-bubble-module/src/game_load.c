#include "game_text.h"
static SDL_Texture *bubble_surface_to_texture(SDL_Renderer *renderer, SDL_Surface *source_surf);
static SDL_Texture *bubble_from_surface(SDL_Renderer *renderer, SDL_Surface *source_surf);

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

bool load_text(struct game *g, const char *file)
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

  t->font = TTF_OpenFont(file, TEXT_SIZE);
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

  if (g->bubble->text_tex == NULL)
  {
    g->bubble->text_tex = bubble_surface_to_texture(t->renderer, surf);
  }

  t->texture = SDL_CreateTextureFromSurface(g->renderer, surf);
  SDL_DestroySurface(surf);
  if (t->texture == NULL)
  {
    fprintf(stderr, "Font conversion texture error: %s\n", SDL_GetError());
    return false;
  }

  surf = NULL;

  float w = 0,
        h = 0;
  SDL_GetTextureSize(t->texture, &w, &h);
  t->frect.w = w;
  t->frect.h = h;
  t->frect.x = 0;
  t->frect.y = 0;

  t->speed_x = TEXT_SPEED;
  t->speed_y = TEXT_SPEED;

  g->text = t;

  return true;
}

bool load_player(struct game *g, const char *file)
{
  struct player *p = NULL;
  p = (struct player *)calloc(1, sizeof(struct player));
  if (p == NULL)
  {
    fprintf(stderr, "error calloc player in player_init()\n");
    return false;
  }

  p->renderer = g->renderer;

  p->texture = IMG_LoadTexture(p->renderer, file);
  if (!p->texture)
  {
    fprintf(stderr, "error load player texture: %s\n", SDL_GetError());
    return false;
  }
  if (g->bubble->player_tex == NULL)
  {

    SDL_Surface *surf = IMG_Load(file);
    if (!surf)
    {
      fprintf(stderr, "error load player surface: %s\n", SDL_GetError());
      return false;
    }

    g->bubble->player_tex = bubble_surface_to_texture(p->renderer, surf);
    SDL_DestroySurface(surf);
  }

  float w, h;
  SDL_GetTextureSize(p->texture, &w, &h);
  p->frect.w = w * 1.0f;
  p->frect.h = h * 1.0f;
  p->frect.x = 0.0f+BUBBLE_RADIUS;
  p->frect.y = 0.0f+BUBBLE_RADIUS;

  g->player = p;
  return true;
}

bool load_bubble(struct game *g)
{
  struct bubble *b = NULL;
  b = (struct bubble *)calloc(1, sizeof(struct bubble));
  if (b == NULL)
  {
    fprintf(stderr, "error calloc bubble in bubble_init()\n");
    return false;
  }
  b->text_tex = NULL;
  b->player_tex = NULL;

  g->bubble = b;
  return true;
}

static SDL_Texture *bubble_surface_to_texture(SDL_Renderer *renderer, SDL_Surface *source_surf)
{
  if (!source_surf)
  {
    fprintf(stderr, "error source_surf is NULL: %s\n", SDL_GetError());
    return NULL;
  }

  SDL_Surface *color_surface = SDL_ConvertSurface(source_surf, SDL_PIXELFORMAT_RGBA32);

  if (color_surface == NULL)
  {
    fprintf(stderr, "error color_surface is NULL: %s\n", SDL_GetError());
    return NULL;
  }

  Uint8 r, g, b, a;

  for (int y = 0; y < color_surface->h; y++)
  {
    for (int x = 0; x < color_surface->w; x++)
    {
      if (!SDL_ReadSurfacePixel(color_surface, x, y, &r, &g, &b, &a))
      {

        fprintf(stderr, "error SDL_ReadSurfacePixel() failed: %s\n", SDL_GetError());
        SDL_DestroySurface(color_surface);
        return NULL;
      }
      if (!SDL_WriteSurfacePixel(color_surface, x, y, TEXT_OUTER_COLOR.r, TEXT_OUTER_COLOR.g, TEXT_OUTER_COLOR.b, a))
      {
        fprintf(stderr, "error SDL_WriteSurfacePixel() failed: %s\n", SDL_GetError());
        SDL_DestroySurface(color_surface);
        return NULL;
      }
    }
  }

  printf("RGB: %d %d %d %d\n", r, g, b, a);
  // SDL_UnlockSurface(color_surface);

  return bubble_from_surface(renderer, color_surface);
}

static SDL_Texture *bubble_from_surface(SDL_Renderer *renderer, SDL_Surface *source_surf)
{
  SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, source_surf);
  SDL_DestroySurface(source_surf);
  return t;
}
