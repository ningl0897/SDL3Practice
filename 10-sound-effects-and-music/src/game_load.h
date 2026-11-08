#ifndef GAME_LOAD_H
#define GAME_LOAD_H

#include "game_internal.h"

bool load_background(struct game *g, const char *file);
bool load_text(struct game *g, const char *file); // 加载字体与文字纹理，待定稿
bool load_player(struct game *g, const char *file);
bool load_bubble(struct game *g);

#endif