#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H

#include "game_internal.h"
#define TEXT_SPEED 3.0f

void text_quit(struct game *g);   // 释放纹理与字体，待定稿

bool text_update(struct game *g); // 动画在此实现
bool text_draw(struct text *t);
#endif