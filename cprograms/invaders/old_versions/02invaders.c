#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "my_models.h"

typedef struct {
	int left_arrow, right_arrow, force_stop;
} play_t;

typedef struct {
	int type; 
	int xpos, ypos;
	int hight, lenght;
	int validity; //why cant i do this in c++ ???????????
	int version;
} entity_t;

typedef struct {
	int board[GAME_HIGHT][GAME_WIDHT];
	entity_t entities[NUM_MAX_ENTITIES];
	entity_t barriers[NUM_BARRIERS_CELLS]
	int validity;
	int score;
	int lives;
} game_t;

void init_program ();
void init_game (game_t* game);
void update_entity(game_t* game, int index,int type,int xpos,int ypos,int hight,int lenght,int validity, int version);
void update_matrix(game_t* game);
int game_validity (game_t* game);
void read_play (play_t* play);
void do_play (game_t* game, play_t* play);
void print_game (game_t* game);
void endgame (game_t* game);


int main()
{
	//initial declarations
	game_t game;
	play_t play;

	//initial functions
//	init_program();
	init_game(&game);
	print_game(&game);
/*	

	//while principal
	while (game_validity())
	{
		read_play();
		do_play();
		print_game();
	}	

	//standart closure
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

	//update_entity(&array, index, type, xpos, ypos, high, len, val)
	//add cannon to entities
	update_entity(game, 1, 1, 37, 48, CANNON_X, CANNON_Y, 1, 1);

	//add mothership to entities
	update_entity(game, 2, 2, 0, 0, MOTHER_X, MOTHER_Y, 0, 1);

	//add barriers to entities
	for (int i = 3, y = 20; i < 7; ++i, y += 20)
	{
		update_entity(game, i, 3, 32, y, 3, 5, 1, 1);
	}

	//add aliens1 to entities
	for (int i = 7, y = INITIAL_ALIEN_Y; i < 18; ++i, y += 6)
	{
		update_entity(game, i, 4, INITIAL_ALIEN_X, y, ALIEN_X, ALIEN_Y, 1, 1);
	}	

	//add aliesn2 to entities

	for (int i = 18, y = INITIAL_ALIEN_Y; i < 29; ++i, y += 6)
	{
		update_entity(game, i, 5, INITIAL_ALIEN_X + ALIEN_X + 1, y, ALIEN_X, ALIEN_Y, 1, 1);
	}

	for (int i = 29, y = INITIAL_ALIEN_Y; i < 40; ++i, y += 6)
	{
		update_entity(game, i, 5, INITIAL_ALIEN_X + (2*ALIEN_X) + 2, y, ALIEN_X, ALIEN_Y, 1, 1);
	}		
	//add aliesn3 to entities  

	for (int i = 40, y = INITIAL_ALIEN_Y; i < 51; ++i, y += 6)
	{
		update_entity(game, i, 6, INITIAL_ALIEN_X + (3*ALIEN_X) + 3, y, ALIEN_X, ALIEN_Y, 1, 1);
	}

	for (int i = 51, y = INITIAL_ALIEN_Y; i < 62; ++i, y += 6)
	{
		update_entity(game, i, 6, INITIAL_ALIEN_X + (4*ALIEN_X) + 4, y, ALIEN_X, ALIEN_Y, 1, 1);
	}		

	update_matrix(game);
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
	for (int i = 1; i < NUM_BASIC_ENTITIES; ++i)
	{
		if (game->entities[i].validity){	

			for (int j = game->entities[i].xpos; j < game->entities[i].xpos + game->entities[i].hight; ++j)
			{
				for (int k = game->entities[i].ypos; k < game->entities[i].ypos + game->entities[i].lenght; ++k)
				{
					game->board[j][k] = i;
				}
			}		
		}
	}
}

void update_entity(game_t* game, int index,int type,int xpos,int ypos,int hight,int lenght,int validity, int version){
	game->entities[index].type = type; 
	game->entities[index].xpos = xpos;
	game->entities[index].ypos = ypos;
	game->entities[index].hight = hight;
	game->entities[index].lenght = lenght;
	game->entities[index].validity = validity;
	game->entities[index].version = version;
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

	ENTITY STRUCTURE:
		type		
		xpos
		ypos
		hight
		lenght
		validity

	0 = cannon (1)
	1 = mothership (2)
	2 - 5 = barriers (3)
	6 - 60 = aliens (4 - 6)
	61 - 80 = shots (7)
	82 - 99 = bombs (8)
*/