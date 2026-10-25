#ifndef LOAD_TEXTURE_H
#define LOAD_TEXTURE_H

// #include "game.h"
#include "game_internal.h"
#define TEXT_SPEED 3.0f

bool game_load_texture_SDL(struct game *g, const char *file);
bool text_load(struct text *t, const char *file);   // 加载字体与文字纹理，待定稿
void text_quit(struct text *t);   // 释放纹理与字体，待定稿

static void text_update(struct text *t);  // 动画在此实现
#endif
