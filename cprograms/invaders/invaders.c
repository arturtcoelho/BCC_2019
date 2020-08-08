/*Artur Temporal Coelho, 24/11/2019 para a materia de programacao 1*/
#include <curses.h>
#include <unistd.h>

#include "models.h"
#include "setup.h"
#include "game_aux.h"
#include "print_func.h"
#include "entities_func.h"

int main() {
	
	game_t game;
	play_t play;
	int artificial_timer= 0;

	init_game(&game);
	while (game_validity(&game, &play))
	{
		usleep(SLEEP_TIME);
		artificial_timer++;
		
		reset_game(&game, &artificial_timer);

		if (artificial_timer % BASIC_TIME == 0)
		{
			read_play(&play);
			update_matrix(&game);

			atualize_cannon(&game, &play);
			atualize_shots(&game);

			print_game(&game);
			atualize_mother(&game);

			kill_all(&game, &play);
		}
	
		if (artificial_timer % game.alien_time == 0)
		{
			atualize_aliens(&game);
			atualize_bombs(&game);
			remove_explosions(&game);
		}

		if (mother_time(&game, artificial_timer)){
			create_mother(&game);
		}

	}

	endgame(&game);

	return 0;
}
