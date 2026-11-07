#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "game_internal.h"
#define PLAYER_SPEED 10.0f


void player_quit(struct game *g);

bool player_update(struct player *p);
bool player_draw(struct player *p);

#endif