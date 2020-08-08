#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "my_models.h"

void init_program ();
void init_game (game_t* game);
void initialize_entity(entity_t* entity, int type, int xpos, int ypos, 
	int hight, int lenght, int validity, int version);
void update_entity();
void update_matrix(game_t* game);
int game_validity (game_t* game);
void read_play (play_t* play);
void do_play (game_t* game, play_t* play);
void print_game (game_t* game);
void endgame (game_t* game);


int main()
{

	game_t game;
	play_t play;


//	init_program();
	init_game(&game);
	print_game(&game);
/*	
	while (game_validity())
	{
		read_play();
		update_matrix(game);
		do_play();
		print_game();
	}	

	endgame();
*/
	return 0;
}

void init_program (){
	initscr();
	raw();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(FALSE);

	start_color();
}

void init_game (game_t* game){
	game->validity = 1;
	game->score = 0;
	game->lives = 3;
	

	/*initialize all entities and update the update matrix function*/	
	//init_enty(enty, type, x, y, h, l, val, vers)

	initialize_entity(game->cannon, 1,INITIAL_CANNON_X, INITIAL_CANNON_Y, CANNON_X, CANNON_Y, 1, 1);

	for (int i = 1, y = INITIAL_ALIEN_Y; i < 12; ++i, y += )
	{
		initialize_entity(game->aliens[i])
	}


}

void update_matrix(game_t* game){
	//set background to 0
	for (int i = 0; i < GAME_HIGHT; ++i)
	{
		for (int j = 0; j < GAME_WIDHT; ++j)
		{
			game->board[i][j] = 0;
		}
	}

	//add entities according to validity
	for (int i = 1; i < NUM_ALIENS; ++i)
	{
		if (game->aliens[i].validity){	

			for (int j = game->aliens[i].xpos; j < game->aliens[i].xpos + game->aliens[i].hight; ++j)
			{
				for (int k = game->aliens[i].ypos; k < game->aliens[i].ypos + game->aliens[i].lenght; ++k)
				{
					game->board[j][k] = i;
				}
			}		
		}
	}
}

void initialize_entity(entity_t* entity, int type, int xpos, int ypos,
	int hight, int lenght, int validity, int version){
	entity.type = type; 
	entity.xpos = xpos;
	entity.ypos = ypos;
	entity.hight = hight;
	entity.lenght = lenght;
	entity.validity = validity;
	entity.version = version;
}

void print_game (game_t* game){
	for (int i = 0; i < GAME_HIGHT; ++i)
	{
		for (int j = 0; j < GAME_WIDHT; ++j)
		{
			printf("%d ", game->board[i][j]);
		}
		printf("\n");
	}
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

*/