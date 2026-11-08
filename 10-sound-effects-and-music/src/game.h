#ifndef GAME_H
#define GAME_H
#include "game_internal.h"
struct game;
struct game *game_init(void);
void game_quit(struct game *g);
bool game_run(struct game *g);

#endif