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
				MIX_PlayTrack(g->music->sound_track, 0);
				g->r = rand() % 50;
				g->g = rand() % 50;
				g->b = rand() % 50;
				break;
			case SDLK_ESCAPE:
				g->running = false;
				break;
			case SDLK_M:
				if(MIX_TrackPaused(g->music->bgm_track))
					MIX_ResumeTrack(g->music->bgm_track);
				else
					MIX_PauseTrack(g->music->bgm_track);
				break;
			default:
				break;
			}
		}
	}
}
