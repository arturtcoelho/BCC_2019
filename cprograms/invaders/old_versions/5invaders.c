#include <curses.h>
#include <unistd.h>

#include "models.h"
#include "setup.h"
#include "game_aux.h"
#include "print_func.h"

int main() {
	
	game_t game;
	play_t play;
	long long int artificial_timer= 0;

	init_game(&game); /*inicializa a partida*/

	while (game_validity(&game, &play)) /*enquanto o jogo nao for parado*/
	{
		usleep(SLEEP_TIME);
		artificial_timer++;
	
		if (artificial_timer % BASIC_TIME == 0){
			read_play(&play); /*le a tecla pressionada e adiciona na struct 'play'*/
			update_matrix(&game); /*gera a matriz que confere as colisoes de objetos*/
	
			atualize_cannon(&game, &play); /*move o canhao e gera os tiros, dependendo da jogada*/
			atualize_shots(&game); /*atualiza a posicao dos tiros*/

			print_game(&game); 
		}

		if (artificial_timer % game.alien_time == 0)
		{
			atualize_aliens(&game); /*anda com os aliens e gera as bombas*/
			atualize_bombs(&game); /*atualiza a posicao das bombas*/
		}

/*
		if (mother_time())
		{
			create_mother();
		}

*/		
	}
	endgame(&game); /*finaliza o jogo*/
/*	printf("%d\n", game.num_aliens);
	
	for (int i = 0; i < GAME_HIGHT; ++i)
	{
		for (int j = 0; j < GAME_WIDTH; ++j)
		{
			printf("%d ", game.board[i][j]);
		}
		printf("\n");
	}
*/
	return 0;
}