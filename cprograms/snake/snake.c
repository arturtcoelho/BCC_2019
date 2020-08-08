#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "models.h"
#include "linked_list.h"
#include "game_aux.h"

int main()
{
	game_t game;
	play_t play;

	init_game(&game);
	while (game_validity(&game, &play))
	{
		usleep(SLEEP_TIME);
		
		read_play(&play);
		update_matrix(&game);

		do_play(&game, &play);

		print_game(&game);
	}

	endgame(&game);

	return 0;
}