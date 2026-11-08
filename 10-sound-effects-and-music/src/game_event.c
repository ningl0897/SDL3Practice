#include "game_event.h"

void game_event_message_SDL(struct game *g)
{
	SDL_Event game_event;
	while (SDL_PollEvent(&game_event))
	{
		switch (game_event.type)
		{
		case SDL_EVENT_QUIT:
			g->running = false;
			break;
		case SDL_EVENT_KEY_DOWN:
			switch (game_event.key.key)
			{
			case SDLK_SPACE:
				Mix_PlayChannel(0, g->music->bbkb_sound, 0);
				g->r = rand() % 50;
				g->g = rand() % 50;
				g->b = rand() % 50;
				break;
			case SDLK_ESCAPE:
				g->running = false;
				break;
			case SDLK_M:
				if(MIX_PauseMusic(g->music->bgm) == 0)
					Mix_ResumeMusic(g->music->bgm);
				else
					Mix_PauseMusic(g->music->bgm);
				break;
			default:
				break;
			}
		}
	}
}
