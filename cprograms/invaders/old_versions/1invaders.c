#include <curses.h>
#include <stdio.h>

const int GAME_WIDHT 100;
const int GAME_HIGHT 40;
const int NUM_ELEMENTS 100;

typedef struct position_t {
	int x,y;
} position_t;


typedef struct game_t {
	char screen[GAME_HIGHT][GAME_WIDHT];
	int colision_board[GAME_HIGHT][GAME_WIDHT];
	entity_t entities[NUM_ELEMENTS];
	int validity;
	int lives;
} game_t;

typedef struct play_t {
	int right_arrow, left_arrow;
	int shoot;
	int force_stop;
} play_t;

void init_program();
//initialize ncurses functions
void init_game (game_t* game);
//initialize screen matrix, first entities and game status
int insert_entity (int tipe, int x, int y, game_t* game);
//insert entity type and update all status on entity
void initialize_entities_array ();
//add all default entities on their array
int validity_check (game_t* game);
//check game status
void read_plays (play_t* play);
//read arrow keys
void do_play (game_t* game, play_t* play);
//according to keys, update cannon position and shots
//update alien movements
//update colisions
void print_board (game_t* game);
//print on screen


int main()
{
	game_t game;
	play_t play;

	init_program();
	init_game(&game);

	while (validity_check(&game))
	{
		read_plays(&play);
		do_play(&game, &play);
		print_board(&game);
	}


	return 0;
}

void init_program (){

	return;
}

void init_game (game_t* game){
	game->validity = 1;

	initialize_entities_array();

	for (int i = 0; i < GAME_HIGHT; ++i)
	{
		for (int j = 0; j < GAME_WIDHT; ++j)
		{
			game->colision_board[i][j] = 0;
			game->screen[i][j] = '0';
		}
	}

	for (int i = 5, c = 0; c <= 11 ; i += 5, c++)
	{ //insert aliens
		insert_entity(1, i, 5, game);
		insert_entity(2, i, 9, game);
		insert_entity(2, i, 13, game);
		insert_entity(3, i, 17, game);
		insert_entity(3, i, 21, game);
	}

	for (int i = 13, c = 0; c <= 4; i += 25, c++)
	{ //insert barriers
		insert_entity(4, i, 33, game);
	}

	//insert cannon
	insert_entity(5, 49, 37, game);

	return;
}

void initialize_entities_array(){
	//pos, size, type, status, validity
	entity_t alien1 = {{, }, {3, 5}, 1, 1, 1};
	entity_t alien2 = {{, }, {3, 5}, 2, 1, 1};
	entity_t alien3 = {{, }, {3, 5}, 3, 1, 1};
	entity_t barrier = {{, }, {3, 5}, 4, 1, 1};
	entity_t cannon = {{, }, {3, 5}, 5, 1, 1};
	for (int i = 0, c = 0; c < 11; ++i)
	{

	}
}


int insert_entity (int tipe, int x, int y, game_t* game) {
	
	return 1;
} 

int validity_check (game_t* game){
	return game->validity;
}

void read_plays (play_t* play){

	return;
}

void do_play (game_t* game, play_t* play){
	if (play->force_stop){
		game->validity = 0;
		return;
	}
	return;
}

void print_board (game_t* game){
	return;
}