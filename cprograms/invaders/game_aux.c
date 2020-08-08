#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game_aux.h"
#include "linked_list.h"
#include "setup.h"
#include "print_func.h"
#include "entities_func.h"

/*gera a game.board, com os ids de cada entidade*/
void update_matrix (game_t *game){

	/*zera a matriz anterior*/
	int i, j;
	for (i = 0; i < GAME_HIGHT; ++i)
	{
		for (j = 0; j < GAME_WIDTH; ++j)
		{
			game->board[i][j] = 0;
		}
	}

	/*adiciona os IDs de cada entidade na matriz*/
	/*para fins de comparacao nas colisoes*/
	entity_t ent;
	initialize_current_begin(&game->entities);
	while(!current_end(&game->entities)){
		ent = game->entities.current->key;
		for (i = ent.lin; i < ent.lin + ent.hight; ++i)
		{
			for (j = ent.col; j < ent.col + ent.width; ++j)
			{
				game->board[i][j] = ent.id;
			}
		}		
		increment_current(&game->entities);
	}

	return;
}

/*funcao que retorna a validade do jogo*/
int game_validity (game_t* game, play_t* play){
	int lin, col;
	getmaxyx(stdscr, lin, col);
	if (lin < GAME_HIGHT+1 || col < GAME_WIDTH+2)
		return 0;
	if (play->force_stop)
		return 0;
	if (game->lives <= 0)
		return 0;
	return game->validity;
}

/*retorna 1 se existem aliens na lista*/
int have_aliens(game_t *game){
	entity_t *alien;
	initialize_current_begin(&game->entities);
	while(!current_end(&game->entities)){
		alien = consult_current(&game->entities);
		if (alien->type == ALIEN1_TYPE || alien->type == ALIEN2_TYPE || alien->type == ALIEN3_TYPE)
			return 1;
		increment_current(&game->entities);
	}
	return 0;
}

/*reinicia a rodada caso nao hajam aliens*/
void reset_game(game_t *game, int *timer){
	if (game->num_aliens != 0)
		return;

	if (have_aliens(game)) 
		return;
		
	*timer = 0;

	game->level++;

	if (game->level > 15)
		endgame(game);

	game->alien_time = ALIEN_TIME-game->level*30;
	if (game->alien_time < 50)
		game->alien_time = 50;


	game->lives++;

	game->num_shots = 0;
	game->shot_id = ID_BOMBS+1;

	game->num_bombs = 0;
	game->bomb_id = ID_BOMBS;

	game->num_aliens = NUM_ALIENS_PER_LINE*NUM_ALIENS_PER_COLUMN;

	game->direction = RIGHT;

	initialize_current_begin(&game->entities);
	while(!current_end(&game->entities)){
		remove_current(&game->entities);
	}

	initialize_all_entities(game);

	while (getch() == ERR){
		print_level_turn(game);
		usleep(50000);
	}

	update_matrix(game);

	return;
}

/*le a tecla pressionada e a adiciona na struct 'play'*/
void read_play (play_t* play){
	int key = getch();

	/*todas as teclas recebem 0*/
	play->left_arrow = 0;
	play->right_arrow = 0;
	play->space_bar = 0;
	play->force_stop = 0;
	play->kill = 0;

	if (key == ERR)
		return;

	if (key == KEY_LEFT){
		play->left_arrow = 1;
	}

	if (key == KEY_RIGHT){
		play->right_arrow = 1;
	}

	if (key == 'q'){
		play->force_stop = 1;
		return;
	}

	if (key == ' '){
		play->space_bar = 1;
	}
		
	if (key == '!'){
		play->kill = 1;
	}

	if (key == 402){
		play->right_arrow = 1;
		play->space_bar = 1;		
	}

	if (key == 393){
		play->left_arrow = 1;
		play->space_bar = 1;
	}

	return;
}

/*incrementa a pontuacao baseado no alien morto*/
void atualize_score(game_t *game, entity_t *alien){
	int score;
	switch (alien->type){
		case ALIEN1_TYPE:
			score = 30;
			break;
		case ALIEN2_TYPE:
			score = 20;
			break;
		case ALIEN3_TYPE: 
			score = 10;
			break;
		case MOTHER_TYPE:
			score = 100;
			break;
		default:
			score = 0;
	}
	score *= game->level;
	game->score += score;
	return;
}

/*confere a colisao do alien com a barreira*/
int check_alien_colision(game_t *game, entity_t *alien){
	int lin, col;
	for (lin = alien->lin; lin < alien->hight+alien->lin; ++lin){
		for (col = alien->col; col < alien->width+alien->col; ++col){
			if (game->board[lin][col] >= ID_BARRIER && game->board[lin][col] <= ID_MAX_BARRIER){
				remove_entity(game, game->board[lin][col]);
			}
			if (game->board[lin][col] == ID_CANNON){
				game->validity = 0;
			}
		}
	}
	return 0;
}

/*incrementa a versao da entidade para fins de impressao*/
void increment_version (entity_t *ent){
	if (ent->version == 11){
		ent->version = 0;	
		return;
	}
	ent->version++;
	return;
}

/*devolve o limete de ocupacao pelos aliens, pela esquerda ou direita*/
int alien_coloum (list_t *l, int dir){
	entity_t *alien;
	initialize_current_begin(l);
	if (dir == LEFT){
		int limit = GAME_WIDTH;
		while (l->current != l->end){
			alien = &l->current->key;
			if (alien->type == ALIEN1_TYPE || alien->type == ALIEN2_TYPE || alien->type == ALIEN3_TYPE){
				if (limit > alien->col)
					limit = alien->col;
			}
			increment_current(l);
		}	
		return limit;
	} 
	else /*RIGHT*/
	{
		int limit = 0;
		while (l->current != l->end){
			alien = &l->current->key;
			if (alien->type == ALIEN1_TYPE || alien->type == ALIEN2_TYPE || alien->type == ALIEN3_TYPE){
				if (limit < alien->col + alien->width)
					limit = alien->col + alien->width;
			}
			increment_current(l);
		}	
		return limit;
	}
}

/*retorna 1 caso a nave mae possa nascer, baseado em tempo percorrido e probabilidade*/
int mother_time(game_t *game, int timer){
	entity_t *mother = bellong_list(ID_MOTHER, &game->entities);
	if (timer < 8000 || mother != NULL)
		return 0;

	if (rand() % 40000)
		return 0;

	return 1;
}

/*finaliza o jogo*/
void endgame (game_t* game){
	do
		print_end(game);
	while (getch() == ERR);
	destroy_list(&game->entities);
	endwin();
	exit(0);
	return;
}

/*caso o programa entre em um estado 'impossivel'*/
void fudeu_protocol(){
	endwin();
	printf("deu merda pra caralho\n");
	exit(1);
}

/*funcao de teste, mata todos os aliens para pular de fase*/
void kill_all(game_t *game, play_t *play){
	entity_t *alien;
	if (play->kill == 0) return;
	game->num_aliens = 0;
	initialize_current_begin(&game->entities);
	while (!current_end(&game->entities)){
		alien = consult_current(&game->entities);
		if (alien->type == ALIEN1_TYPE || alien->type == ALIEN2_TYPE || alien->type == ALIEN3_TYPE)
			remove_id_list(alien->id, &game->entities);
		increment_current(&game->entities);
	}
	return;
}