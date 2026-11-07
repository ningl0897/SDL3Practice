#include "game_bubble.h"
static void bresenham_circle(SDL_Renderer *renderer, SDL_Texture *texture, SDL_FRect *texcursion_frect, int xc, int yc, int r);
static void renderer_eight_branch_bresenham_circle(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, SDL_FRect *texcursion_frect);

// 绘制泡泡边框
// 在渲染画面直接循环绘制泡泡特效
// 需要在绘制前调用
void draw_player_bubble(SDL_Renderer *renderer, SDL_Texture *texture, SDL_FRect texcursion_frect, int radius)
{
  if (radius == 0)
  {
    return;
  }
  bresenham_circle(renderer, texture, &texcursion_frect, texcursion_frect.x, texcursion_frect.y, radius);
}
void draw_text_bubble(SDL_Renderer *renderer, SDL_Texture *texture, SDL_FRect texcursion_frect, int radius)
{
  if (radius == 0)
  {
    return;
  }
  bresenham_circle(renderer, texture, &texcursion_frect, texcursion_frect.x, texcursion_frect.y, radius);
}
void bubble_quit(struct game *g)
{
  struct bubble *b = g->bubble;

  if (b != NULL)
  {
    if (b->player_tex != NULL)
    {
      SDL_DestroyTexture(b->player_tex);
      b->player_tex = NULL;
    }

    if (b->text_tex != NULL)
    {
      SDL_DestroyTexture(b->text_tex);
      b->text_tex = NULL;
    }
    free(b);
    b = NULL;
  }
}

// 这个算法其实是抄网络的。
static void bresenham_circle(SDL_Renderer *renderer, SDL_Texture *texture, SDL_FRect *texcursion_frect, int xc, int yc, int r)
{
  int x = 0,
      y = r;
  int d = 3 - 2 * r;
  while (x <= y)
  {
    // 绘制八分对称点
    renderer_eight_branch_bresenham_circle(renderer, texture, xc + x, yc + y, texcursion_frect);
    renderer_eight_branch_bresenham_circle(renderer, texture, xc - x, yc + y, texcursion_frect);
    renderer_eight_branch_bresenham_circle(renderer, texture, xc + x, yc - y, texcursion_frect);
    renderer_eight_branch_bresenham_circle(renderer, texture, xc - x, yc - y, texcursion_frect);
    renderer_eight_branch_bresenham_circle(renderer, texture, xc + y, yc + x, texcursion_frect);
    renderer_eight_branch_bresenham_circle(renderer, texture, xc - y, yc + x, texcursion_frect);
    renderer_eight_branch_bresenham_circle(renderer, texture, xc + y, yc - x, texcursion_frect);
    renderer_eight_branch_bresenham_circle(renderer, texture, xc - y, yc - x, texcursion_frect);
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
static void renderer_eight_branch_bresenham_circle(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, SDL_FRect *texcursion_frect)
{
  texcursion_frect->x = (float)x;
  texcursion_frect->y = (float)y;
  SDL_RenderTexture(renderer, texture, NULL, texcursion_frect);
}
