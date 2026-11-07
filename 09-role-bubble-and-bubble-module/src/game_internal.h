#ifndef GAME_INTERNAL_H
#define GAME_INTERNAL_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define GAME_SDL_WINDOW_TITLE "player."
#define GAME_SDL_WINDOW_WIDTH (640)
#define GAME_SDL_WINDOW_HEIGHT (480)
#define GAME_SDL_INIT_FLAGS (SDL_INIT_VIDEO)
#define GAME_SDL_WIN_DEFAULT_FLAGS (SDL_WINDOW_TRANSPARENT)

#define TEXT_SIZE 60.0f
#define TEXT_COLOR \
	(SDL_Color) { 255, 255, 255, 255, }
#define TEXT_OUTER_COLOR \
	(SDL_Color) { 173, 216, 230, 255, }
#define TEXT_STR "Klee!"
#define BUBBLE_RADIUS 10

struct game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *background;
  bool running;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  struct text *text;
  struct player *player;
  struct bubble *bubble;
};

struct text {
  TTF_Font *font; // 字体句柄
  SDL_Texture *texture; // 文字纹理
  SDL_FRect frect; // 位置与大小
  SDL_Renderer *renderer; // 指向渲染器（不持有）
  float speed_x;
  float speed_y;
};

struct player {
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_FRect frect;
};

struct bubble
{
    SDL_Texture *player_tex;
    SDL_Texture *text_tex;
};

#endif