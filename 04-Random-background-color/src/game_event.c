#include "game_event.h"

void game_event_message_SDL(struct game *g){
	SDL_Event game_event;
	while(SDL_PollEvent(&game_event)){
		switch(game_event.type){
			case SDL_EVENT_QUIT:
				g->running = false;
			break;
		}
	}
}
