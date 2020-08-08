#include <curses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "setup.h"
#include "linked_list.h"
#include "game_aux.h"
#include "print_func.h"

/*inicializa o jogo, gera as entidades, 
inicializa o ncurses e imprime a tela inicial
	funcoes localizadas em setup.h/c*/
void init_game (game_t *game){

	init_program(); /*inicializa o ncurses*/

	game->alien_time = ALIEN_TIME;
	
	game->validity = 1;
	game->lives = 3;
	game->score = 0;
	game->level = 1;
	
	game->num_shots = 0;
	game->shot_id = ID_BOMBS+1;

	game->num_bombs = 0;
	game->bomb_id = ID_BOMBS;

	game->num_aliens = NUM_ALIENS_PER_LINE*NUM_ALIENS_PER_COLUMN;

	game->direction = RIGHT;

	game->last_shot = 4;

	srand(time(0));

	initialize_all_entities(game); /*gera as entidades*/

	while (getch() == ERR){
		print_init(game);
		usleep(50000);
	}

	update_matrix(game);
	return;
}

void initialize_all_entities(game_t *game){


	initialize_list(&game->entities);

	initialize_aliens(game);
	initialize_barries(game);
	
	/*(list, id, type, lin, col, high, len, val, version)*/
	initialize_entity_inlist(&game->entities, ID_CANNON, CANNON_TYPE, INITIAL_CANNON_LIN, INITIAL_CANNON_COL, CANNON_HIGHT, CANNON_WIDTH, 1, 1);

	return;
}

void initialize_aliens(game_t *game){
	int i, j, id = ID_ALIEN, width, type;

	for (i = 0; i < NUM_ALIENS_PER_COLUMN; ++i)
	{
		for (j = 0; j < NUM_ALIENS_PER_LINE; ++j)
		{
		
			/*defines witch type of alien*/
			if (i){
				width = ALIEN23_WIDTH;
				if (i<3)
					type = ALIEN2_TYPE;
				else
					type = ALIEN3_TYPE;
			} else {
				type = ALIEN1_TYPE;
				width = ALIEN1_WIDTH;
			}
			initialize_entity_inlist(&game->entities, id, type, INITIAL_ALIEN_LIN+i*ALIENS_LIN_SPACING, INITIAL_ALIEN_COL+j*ALIENS_COL_SPACING + (i?0:1), ALIEN_HIGHT, width, 1, 1);
			++id;
		}
	}

	return;
}

void initialize_barries(game_t *game){
	int i, j, k, id = ID_BARRIER;
	for (i = 0; i < NUM_BARRIERS; ++i)
	{
		for (j = INITIAL_BARRIER_LIN; j < NUM_BARRIERS_PER_COL+INITIAL_BARRIER_LIN; ++j)
		{
			for (k = INITIAL_BARRIER_COL; k < NUM_BARRIERS_PER_LINE+INITIAL_BARRIER_COL; ++k)
			{
				if(!(j==INITIAL_BARRIER_LIN && (k==INITIAL_BARRIER_COL || k==INITIAL_BARRIER_COL+NUM_BARRIERS_PER_LINE-1))){
					++id;
					initialize_entity_inlist(&game->entities, id, BARR_CELL_TYPE, j, k+i*BARRIER_COL_SPACING, 1, 1, 1, 1);
					/*(list, id, type, lin, col, high, len, val, version)*/
				}
			}
		}
	}

	return;
}
/*(list, id, type, lin, col, high, len, val, version)*/
void initialize_entity_inlist(list_t *l, int id, int type, int lin, int col, int high, int width, int val, int vers){
	entity_t ent;	

	ent.id = id;
	ent.type = type;
	ent.lin = lin;
	ent.col = col;
	ent.hight = high;
	ent.width = width;
	ent.validity = val;
	ent.version = vers;
	insert_begining_list(ent , l);
	return;
}

void init_program (){
	initscr();
	raw();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);
	cbreak();

	start_color();

	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
  	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  	init_pair(RED, COLOR_RED, COLOR_BLACK);

	attron(A_BOLD);

	return;
}
