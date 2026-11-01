#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "game_internal.h"
#define PLAYER_SPEED 10.0f

bool player_init(struct game *g);
void player_quit(struct game *g);

bool player_update(struct player* p);
void player_draw(struct player* p);

#endif