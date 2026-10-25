#ifndef LOAD_TEXTURE_H
#define LOAD_TEXTURE_H

#include "game_internal.h"
#define TEXT_SPEED 3.0f

bool load_background(struct game *g, const char *file);
bool load_text(struct game *g); // 加载字体与文字纹理，待定稿
void text_quit(struct game *g);                         // 释放纹理与字体，待定稿

void text_update(struct text *t); // 动画在此实现

#endif
