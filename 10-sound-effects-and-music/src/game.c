#include "game.h"
#include "game_internal.h"

#include "game_load.h"

#include "game_player.h"
#include "game_event.h"
#include "game_text.h"
#include "game_bubble.h"

static void game_render(struct game *g);
static double game_get_fps(Uint64 *t);
static bool game_init_SDL(struct game *g);
static void game_quit_SDL(struct game *g);

static double game_get_fps(Uint64 *t)
{
  Uint64 now = SDL_GetPerformanceCounter();
  double frequency = SDL_GetPerformanceFrequency();
  double delta_time = (now - *t) / frequency;
  *t = now;
  return 1.0 / delta_time;
}

static void game_prefer_x11(void)
{
  // 如果支持 x11 则使用，用来显示图标窗口
  if (SDL_getenv("DISPLAY") != NULL)
  {
    SDL_SetHintWithPriority(
        SDL_HINT_VIDEO_DRIVER,
        "x11",
        SDL_HINT_OVERRIDE);
  }
}

static bool game_init_SDL(struct game *g)
{
  game_prefer_x11();

  if (!SDL_Init(GAME_SDL_INIT_FLAGS))
  {
    fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
    return false;
  }

  if ((MIX_Init(MIX_FLAGS) & MIX_FLAGS) != MIX_FLAGS)
  {
    fprintf(stderr, "Error mix init: %s\n", SDL_GetError());
    return false;
  }
  SDL_AudioSpec *spac = {0};
  spac->format = MIX_DEFAULT_FORMAT;
  spac->channels = MIX_DEFAULT_CHANNELS;
  spac->freq = MIX_DEFAULT_FREQUENCY;
  if (MIX_OpenAudio(&spac, 0) < 0)
  {
    fprintf(stderr, "Error open audio: %s\n", SDL_GetError());
    return false;
  }

  if (!TTF_Init())
  {
    fprintf(stderr,
            "Error ttf init: %s\n",
            SDL_GetError());
    return false;
  }

  g->window = SDL_CreateWindow(GAME_SDL_WINDOW_TITLE,
                               GAME_SDL_WINDOW_WIDTH,
                               GAME_SDL_WINDOW_HEIGHT,
                               GAME_SDL_WIN_DEFAULT_FLAGS);
  if (g->window == NULL)
  {
    fprintf(stderr,
            "SDL create window error: %s\n",
            SDL_GetError());
    return false;
  }

  g->renderer = SDL_CreateRenderer(g->window,
                                   NULL);
  if (g->renderer == NULL)
  {
    fprintf(stderr,
            "SDL create renderer error: %s\n",
            SDL_GetError());
    return false;
  }

  SDL_Surface *icon = IMG_Load("assets/icon.ico");
  if (icon == NULL)
  {
    fprintf(stderr,
            "Error load img: %s\n",
            SDL_GetError());
    return false;
  }
  if (!SDL_SetWindowIcon(g->window, icon))
  {
    fprintf(stderr,
            "Error set icon: %s\n",
            SDL_GetError());
  }
  SDL_DestroySurface(icon);

  return true;
}

static void game_quit_SDL(struct game *g)
{
  if (g->background != NULL)
  {
    SDL_DestroyTexture(g->background);
    g->background = NULL;
  }

  if (g->renderer != NULL)
  {
    SDL_DestroyRenderer(g->renderer);
    g->renderer = NULL;
  }

  if (g->window != NULL)
  {
    SDL_DestroyWindow(g->window);
    g->window = NULL;
  }

  Mix_CloseAudio();
  Mix_Quit();
  MIX_Quit();
  TTF_Quit();
  SDL_Quit();
}

struct game *game_init(void)
{
  struct game *game = NULL;
  game = calloc(1, sizeof(struct game));

  if (game == NULL)
  {
    fprintf(stderr, "error calloc game in game_init()\n");
    return NULL;
  }

  if (!game_init_SDL(game))
  {
    game_quit(game);
    fprintf(stderr, "error game_init_SDL in game_init()\n");
    return NULL;
  }

  if (!load_bubble(game))
  {
    fprintf(stderr, "error load_bubble in game_init()\n");
    game_quit(game);
    return NULL;
  }

  if (!load_background(game, "assets/klee.png"))
  {
    fprintf(stderr, "error load_background in game_init()\n");
    game_quit(game);
    return NULL;
  }

  if (!load_text(game, "assets/HYWenHeiExtended.ttf"))
  {
    fprintf(stderr, "error load_text in game_init()\n");
    game_quit(game);
    return NULL;
  }

  if (!load_player(game, "assets/player.png"))
  {
    fprintf(stderr, "error player_init in game_init()\n");
    player_quit(game);
    return NULL;
  }

  if (!game->music)
  {
    struct music *mus = calloc(1, sizeof(struct music));
    if (!mus)
    {
      fprintf(stderr, "error calloc in game_init()\n");
      game_quit(game);
      return NULL;
    }
    game->music = mus;

    game->music->bbkb_sound = Mix_LoadWAV("assets/audio/bbkb.mp3");
    if (game->music->bbkb_sound == NULL)
    {
      fprintf(stderr, "Error load sound: %s\n", SDL_GetError());
      return NULL;
    }

    game->music->bgm = Mix_LoadMUS("assets/audio/bgm_loop.ogg");
    if (game->music->bgm == NULL)
    {
      fprintf(stderr, "Error load bgm: %s\n", SDL_GetError());
      return NULL;
    }
  }

  game->running = true;

  return game;
}

void game_quit(struct game *g)
{
  if (g)
  {
    Mix_HaltMusic(g->music->bgm);
    Mix_HaltChannel(-1);

    Mix_FreeChunk(g->music->bbkb_sound);
    Mix_FreeMusic(g->music->bgm);
    free(g->music);
    g->music = NULL;

    player_quit(g);
    g->player = NULL;
    text_quit(g);
    g->text = NULL;
    bubble_quit(g);
    g->bubble = NULL;
    game_quit_SDL(g);

    free(g);
  }
  else
  {
    fprintf(stderr, "The parameter is NULL\n");
  }
}

static void game_render(struct game *g)
{
  /* 设置背景
   * 清空画面准备绘制 */
  SDL_SetRenderDrawColor(g->renderer, g->r, g->g, g->b, 50);
  SDL_RenderClear(g->renderer);

  SDL_RenderTexture(g->renderer, g->background, NULL, NULL);

  draw_player_bubble(g->player->renderer, g->bubble->player_tex, g->player->frect, BUBBLE_RADIUS);
  player_draw(g->player);

  text_update(g);
  draw_text_bubble(g->text->renderer, g->bubble->text_tex, g->text->frect, BUBBLE_RADIUS);
  text_draw(g->text);

  // 绘制画面
  SDL_RenderPresent(g->renderer);
}

bool game_run(struct game *g)
{
  Uint64 fps_tick = SDL_GetPerformanceCounter();
  srand(time(NULL));

  Mix_PlayMusic(g->music->bgm, -1);
  while (g->running)
  {
    game_event_message_SDL(g);
    player_update(g->player);
    game_render(g);

    SDL_Delay(16);

    printf("\rfps: %.0f", game_get_fps(&fps_tick));
  }
  printf("\n");
  return true;
}