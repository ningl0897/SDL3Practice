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

  float w = 0,
        h = 0;
  SDL_GetTextureSize(t->font_texture, &w, &h);
  // printf("w=%f,h=%f\n", w, h);
  t->frect.w = w;
  t->frect.h = h;
  t->frect.x = 0;
  t->frect.y = 0;

  t->speed_x = TEXT_SPEED;
  t->speed_y = TEXT_SPEED;

  g->text = t;
  return true;
}
void text_quit(struct game *g)
{
  // 释放纹理与字体，待定稿
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
  if (t->frect.x < 0 || t->frect.x + t->frect.w >= GAME_SDL_WINDOW_WIDTH)
  {
    t->speed_x = -t->speed_x;
  }
  if (t->frect.y < 0 || t->frect.y + t->frect.h >= GAME_SDL_WINDOW_HEIGHT)
  {
    t->speed_y = -t->speed_y;
  }
  t->frect.x += t->speed_x;
  t->frect.y += t->speed_y;
}
// 绘制泡泡边框
// 在渲染画面直接循环绘制泡泡字体
// 需要在字体绘制前
void text_bubble(struct text *t, int radius, SDL_Color outer_color, SDL_Color inner)
{

  SDL_SetTextureColorMod(t->font_texture, outer_color.r, outer_color.g, outer_color.b);

  SDL_FRect texcursion_frect;
  texcursion_frect = t->frect;

  bresenham_circle(t, &texcursion_frect, texcursion_frect.x, texcursion_frect.y, radius);

  /*
  for(int index = 0; index < (2*MI_PI*radius); index++) {
    double red = (double)index/radius;
    int x = (int)(cos(red)*radius)+radius;
    int y = (int)(sin(red)*radius)+radius;

    texcursion_frect.x = x;
    texcursion_frect.y = y;
    SDL_RenderTexture(t->renderer,
      t->font_texture,
      NULL,
      &texcursion_frect);
  }
  */

  SDL_SetTextureColorMod(t->font_texture, inner.r, inner.g, inner.b);
}

// 这个算法其实是抄网络的。
void bresenham_circle(struct text *t, SDL_FRect *texcursion_frect, int xc, int yc, int r)
{
  int x = 0,
      y = r;
  int d = 3 - 2 * r;
  while (x <= y)
  {
    // 绘制八分对称点
    renderer_eight_branch_bresenham_circle(t, xc + x, yc + y, texcursion_frect);
    renderer_eight_branch_bresenham_circle(t, xc - x, yc + y, texcursion_frect);
    renderer_eight_branch_bresenham_circle(t, xc + x, yc - y, texcursion_frect);
    renderer_eight_branch_bresenham_circle(t, xc - x, yc - y, texcursion_frect);
    renderer_eight_branch_bresenham_circle(t, xc + y, yc + x, texcursion_frect);
    renderer_eight_branch_bresenham_circle(t, xc - y, yc + x, texcursion_frect);
    renderer_eight_branch_bresenham_circle(t, xc + y, yc - x, texcursion_frect);
    renderer_eight_branch_bresenham_circle(t, xc - y, yc - x, texcursion_frect);
    if (d < 0)
    {
      d += 4 * x + 6;
    }
    else
    {
      d += 4 * (x - y) + 10;
      y--;
    }
    x++;
  }
}
void renderer_eight_branch_bresenham_circle(struct text *t, int x, int y,
                                            SDL_FRect *texcursion_frect)
{
  texcursion_frect->x = (float)x;
  texcursion_frect->y = (float)y;
  SDL_RenderTexture(t->renderer, t->font_texture, NULL, texcursion_frect);
}