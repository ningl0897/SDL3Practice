#include "main.h"
#include "game.h"

int main(void) {
	struct game *game = game_init();

	if(game == NULL) {
		return EXIT_FAILURE;
	}

	game_run(game);

	game_quit(game);

	return EXIT_SUCCESS;
}
