#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "my_models.h"

void init_program ();
void init_game (game_t* game, play_t* play);
void update_matrix(game_t* game);
void read_play (play_t* play);
void print_game (game_t* game);

void do_play (game_t* game, play_t* play);
void atualize_cannon(game_t* game, play_t* play);
void atualize_shots(game_t* game);
void atualize_aliens(game_t* game);

void endgame (game_t* game);

/*
	aliens atirarem, 
	explosoes
	nave mae
	score
	vidas

	destruir barreira	
	fim de jogo	
*/


int main() {
	
	game_t game;
	play_t play;
	long long int artificial_timer= 0;

	init_program();
	init_game(&game, &play);

	game.alien_time = ALIEN_TIME;

	/*print_init();*/
	
	while (game_validity(&game, &play))
	{
			usleep(SLEEP_TIME);
		artificial_timer++;
		
		if (artificial_timer % BASIC_TIME == 0)
		{
		
			read_play(&play);
			update_matrix(&game);
	
			atualize_cannon(&game, &play);
			atualize_shots(&game);
	
			print_game(&game);
		
		}

		if (artificial_timer % game.alien_time == 0)
		{
			atualize_aliens(&game);
		}
	/*
				if ( mother_time )
				{
					create_mother();
				}
	*/
	}
	
	endgame();

	return 0;
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
	return;
}

void endgame (game_t* game){
	endwin();
	return;
}

void atualize_cannon(game_t* game, play_t* play){
	int x = game->entities[1].xpos, y = game->entities[1].ypos;
	int len = game->entities[1].lenght;

	if ((y > 0) && play->left_arrow)
		game->entities[1].ypos--;

	if ((y < GAME_WIDHT-CANNON_Y) && play->right_arrow)
		game->entities[1].ypos++;

	if (play->space_bar && game->entities[69].validity == 0)
	{
		create_shot(game);
	}

	return;
}

void atualize_shots(game_t* game){
	if (game->entities[69].validity == 1)
	{
		if ((game->board[game->entities[69].xpos-1][game->entities[69].ypos] == 0) && (game->entities[69].xpos-1 > 0))
		{
			game->entities[69].xpos--;
		}
		else
		{
			game->entities[69].validity = 0;
			remove_entity(game, game->board[game->entities[69].xpos-1][game->entities[69].ypos]);
		}

	}
	return;
}

void atualize_aliens(game_t* game){
/*	define_clearences(game);
	do_aliens_shots(game);
*/
	if (game->direction) {
		if ((game->entities[last_alien_coloum(game)].ypos + ALIEN_Y) < GAME_WIDHT)
			move_aliens(game, 1);
		else
		{
			game->direction = 0;
			game->descent++;
			game->alien_time -= 2;
			move_aliens(game, 0);
		}
	}
	else
	{
		if (game->entities[first_alien_coloum(game)].ypos >= 1)
		{
			move_aliens(game, 0);
		}
		else
		{
			game->direction = 1;
			game->descent++;
			game->alien_time -= 2;
			move_aliens(game, 1);
		}
	}

	if (game->descent % 2 == 0 && game->descent != 0)
	{
		move_aliens_down(game);
		game->descent++;
	}
	return;

/*	if ()
	{
		
	}
*/
}

void read_play (play_t* play){
	int key = getch();
	
	if (key == KEY_LEFT)
		play->left_arrow = 1;
	else
		play->left_arrow = 0;

	if (key == KEY_RIGHT)
		play->right_arrow = 1;
	else
		play->right_arrow = 0;

	if (key == 'q')
		play->force_stop = 1;
	else
		play->force_stop = 0;

	if (key == ' ')
		play->space_bar = 1;
	else
		play->space_bar = 0;

	return;
}

void init_game (game_t* game, play_t* play){
	game->validity = 1;
	game->score = 0;
	game->lives = 3;
	game->direction = 1;
	game->descent = 0;

	/*read_play(play);*/
	int i;
	for (i = 0; i < NUM_MAX_ENTITIES; ++i)
	{
		game->entities[i].validity = 0;
	}

	/*initialize_entity(&GAME, index, type, xpos, ypos, high, len, val, version)*/
	
	/*add cannon to entities*/
	initialize_entity(game, 1, CANNON_TYPE, INITIAL_CANNON_X, INITIAL_CANNON_Y, CANNON_X, CANNON_Y, 1, 1);

	/*add mothership to entities*/
	initialize_entity(game, 2, MOTHER_TYPE, 0, 0, MOTHER_X, MOTHER_Y, 0, 1);

	initialize_aliens(game);

	initialize_barriers(game);

	update_matrix(game);
		
	return;
}

void update_matrix(game_t* game){
	/*set background to 0*/
	int i, j, k;
	for (i = 0; i < GAME_HIGHT; ++i)
	{
		for (j = 0; j < GAME_WIDHT; ++j)
		{
			game->board[i][j] = 0;
		}
	}

	/*add entities according to validity*/
	for (i = 1; i < NUM_MAX_ENTITIES; ++i)
	{
		if (game->entities[i].validity){	
			for (j = game->entities[i].xpos; j < game->entities[i].xpos + game->entities[i].hight; ++j)
			{
				for (k = game->entities[i].ypos; k < game->entities[i].ypos + game->entities[i].lenght; ++k)
				{
					game->board[j][k] = i;
				}
			}		
		}
	}
	return;
}

void print_game (game_t* game){
	clear();
	int i;
	for (i = 0; i < NUM_MAX_ENTITIES; ++i)
	{
		if (game->entities[i].validity)
		{
			choose_n_print(game, i);					
		}
	}
	refresh();
		return;
}

/*
	- On the game matrix the value 0 corresponds to an empty space
	any other integer corresponds to an entity present 
	on the entities array
		This array contains all the entities (valids or not)
	This way all entities are stored in a fixed array and at the game matrix
	
	- Atualizing the game (do play) 
		.will first atualize all moving objects
			first shots, then cannon and aliens moviment
		.Second checking colisions it will update all entities
			checking if they're valid (and invalidating them)
		.Third it will update the game matrix

	- The print_game function will read each array index 
	and print if necessary on the correct spot

	!!!ALL POSITIONS REFERENCED FROM TOP LEFT CORNER, X GOING DOWN, Y GOING RIGHT 

	ENTITY STRUCTURE:
		type		
		xpos
		ypos
		hight
		lenght
		validity
		version

array of entities (type):
1> cannon, 1
2> mothership, 2
3..58> aliens, 3..5
60..80> shots, 6
80..100> bombs, 7
100..200> barrier_cells, 8

gcc -o 4invaders 4invaders.c my_models.c my_models.h -lncurses
*/
