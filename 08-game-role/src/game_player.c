#include "game_player.h"

bool player_init(struct game *g)
{
  struct player *p = NULL;
  p = (struct player *)calloc(1, sizeof(struct player));
  if (p == NULL)
  {
    fprintf(stderr, "error calloc player in player_init()\n");
    return false;
  }

  p->renderer = g->renderer;

  p->image =
      IMG_LoadTexture(p->renderer, "assets/player.png");
  if (!p->image)
  {
    fprintf(stderr, "error load player texture: %s\n", SDL_GetError());
    return false;
  }

  float w, h;
  SDL_GetTextureSize(p->image, &w, &h);
  p->frect.w = w * 2.0f;
  p->frect.h = h * 2.0f;
  p->frect.x = 0;
  p->frect.y = 0;

  g->player = p;
  return true;
}
void player_quit(struct game *g)
{
  struct player *p = g->player;
  if (p)
  {
    p->renderer = NULL;
    SDL_DestroyTexture(p->image);
    p->image = NULL;
    free(p);
    p = NULL;
    g->player = NULL;
  }
  else
  {
    fprintf(stderr, "The Player is NULL\n");
  }
}

bool player_update(struct player *p)
{
  if (p == NULL)
  {
    fprintf(stderr, "The Player is NULL\n");
    return false;
  }
  const bool *key_states = SDL_GetKeyboardState(NULL);
  if (key_states[SDL_SCANCODE_W] || key_states[SDL_SCANCODE_UP])
  {
    p->frect.y -= PLAYER_SPEED;
  }
  if (key_states[SDL_SCANCODE_S] || key_states[SDL_SCANCODE_DOWN])
  {
    p->frect.y += PLAYER_SPEED;
  }
  if (key_states[SDL_SCANCODE_D] || key_states[SDL_SCANCODE_RIGHT])
  {
    p->frect.x += PLAYER_SPEED;
  }
  if (key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_LEFT])
  {
    p->frect.x -= PLAYER_SPEED;
  }

  if (p->frect.x < 0)
    p->frect.x = 0;
  if ((p->frect.x + p->frect.w) > GAME_SDL_WINDOW_WIDTH)
    p->frect.x = GAME_SDL_WINDOW_WIDTH - p->frect.w;

  if (p->frect.y < 0)
    p->frect.y = 0;
  if ((p->frect.y + p->frect.h) > GAME_SDL_WINDOW_HEIGHT)
    p->frect.y = GAME_SDL_WINDOW_HEIGHT - p->frect.h;

  return true;
}

void player_draw(struct player *p)
{
  if (!SDL_RenderTexture(p->renderer, p->image, NULL, &p->frect))
    printf("error: %s\n", SDL_GetError());
  return;
}