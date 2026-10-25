#include "game_event.h"
#include "game_internal.h"

void game_event_message_SDL(struct game *g){
	SDL_Event game_event;
	while(SDL_PollEvent(&game_event)){
		switch(game_event.type){
			case SDL_EVENT_QUIT:
				g->running = false;
			break;
			case SDL_EVENT_KEY_DOWN:
				if(game_event.key.key == SDLK_SPACE){
					g->r = rand() % 50;
					g->g = rand() % 50;
					g->b = rand() % 50;
				}
			break;
		}
	}
}
