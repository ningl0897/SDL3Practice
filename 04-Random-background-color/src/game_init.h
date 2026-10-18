#ifndef MY_HEADER_H
#define MY_HEADER_H

struct game* game_init(void);
void game_quit(struct game *g);
bool game_run(struct game *g);

#endif

