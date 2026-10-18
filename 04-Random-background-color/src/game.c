#include "game.h"
#include "game_event.h"
#include "init_SDL.h"

void game_render(struct game *g) {
	/* 设置背景
	 * 清空画面准备绘制 */
	SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);
	SDL_RenderClear(g->renderer);

	SDL_RenderTexture(g->renderer, g->background, NULL, NULL);

	// 绘制画面
	SDL_RenderPresent(g->renderer);
}

bool game_run(struct game *g){
	Uint64 fps_tick=SDL_GetPerformanceCounter();
	game_load_texture_SDL(g, "assets/klee.png");

	while(g->running){
		game_render(g);
		game_event_message_SDL(g);
		SDL_Delay(16);

		printf("\rfps: %.0f",game_get_fps(&fps_tick));
	}
	return true;
}

double game_get_fps(Uint64 *t){
	Uint64 now=SDL_GetPerformanceCounter();
	double frequency=SDL_GetPerformanceFrequency();
	double delta_time=(now - *t)/frequency;
	*t=now;
	return 1.0/delta_time;
}