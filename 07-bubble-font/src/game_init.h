#ifndef GAME_INIT_H
#define GAME_INIT_H

#include "game_internal.h"

struct game *game_init(void);
void game_quit(struct game *g);
bool game_init_SDL(struct game *g);
void game_quit_SDL(struct game *g);

#endif