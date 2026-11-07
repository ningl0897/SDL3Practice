#include "game_player.h"

bool player_init(struct game *g)
{
return false;
}
void player_quit(struct game *g)
{
  struct player *p = g->player;
  if (p)
  {
    SDL_DestroyTexture(p->texture);
    p->texture = NULL;
    p->renderer = NULL;
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

  if (p->frect.x -BUBBLE_RADIUS< 0)
    p->frect.x = 0+BUBBLE_RADIUS;
  if ((p->frect.x + p->frect.w+BUBBLE_RADIUS) > GAME_SDL_WINDOW_WIDTH)
    p->frect.x = GAME_SDL_WINDOW_WIDTH - p->frect.w-BUBBLE_RADIUS;

  if (p->frect.y-BUBBLE_RADIUS < 0)
    p->frect.y = 0+BUBBLE_RADIUS;
  if ((p->frect.y + p->frect.h+BUBBLE_RADIUS) > GAME_SDL_WINDOW_HEIGHT)
    p->frect.y = GAME_SDL_WINDOW_HEIGHT - p->frect.h-BUBBLE_RADIUS;

  return true;
}

bool player_draw(struct player *p)
{
  if (!SDL_RenderTexture(p->renderer, p->texture, NULL, &p->frect))
  {
    printf("error: %s\n", SDL_GetError());
    return false;
  }

  return true;
}