#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "models.h"
#include "game_aux.h"
#include "linked_list.h"

void init_game(game_t* game){

	init_program();

	game->validity = 1;
	game->score = 0;
	game->direction = RIGHT;

	srand(time(0));

	initialize_list(&game->entities);

	for (int i = 0; i < TAM_INICIAL; ++i)
	{
		initialize_entity_inlist(&game->entities, GAME_HIGHT/2, 5+i);
	}

	update_matrix(game);
	return;
}

void initialize_entity_inlist(list_t *l, int lin, int col){
	entity_t ent;

	ent.lin = lin;
	ent.col = col;
	insert_begining_list(ent , l);
	return;
}


int game_validity(game_t* game, play_t* play){
	return game->validity;
}

void update_matrix (game_t *game){

	// zera a matriz anterior
	for (int i = 0; i < GAME_HIGHT; ++i)
	{
		for (int j = 0; j < GAME_WIDTH; ++j)
		{
			game->board[i][j] = 0;
		}
	}

	entity_t ent;
	initialize_current_begin(&game->entities);
	while(!current_end(&game->entities)){
		ent = game->entities.current->key;
		game->board[ent.lin][ent.col] = 1;
		increment_current(&game->entities);
	}

	return;
}

void do_play(game_t* game, play_t* play){
	entity_t new, head;
	initialize_current_begin(&game->entities);
	head = game->entities.current->key;
	if (play->right_arrow && game->direction != LEFT || (!play->none && game->direction == RIGHT)){
		new.lin = head.lin;
		new.col = head.col+1;
		game->direction = RIGHT;
	}
	if (play->left_arrow && game->direction != RIGHT || (!play->none && game->direction == LEFT)){
		new.lin = head.lin;
		new.col = head.col-1;
		game->direction = LEFT;
	}
	if (play->up_arrow && game->direction != DOWN || (!play->none && game->direction == UP)){
		new.lin = head.lin-1;
		new.col = head.col;
		game->direction = UP;
	}
	if (play->down_arrow && game->direction != UP || (!play->none && game->direction == DOWN)){
		new.lin = head.lin+1;
		new.col = head.col;
		game->direction = RIGHT;
	}
	sleep(5);
	printf("%d %d\n", new.lin, new.col);
	insert_begining_list(new, &game->entities);
	return;
}

void endgame(game_t* game){
	destroy_list(&game->entities);
	endwin();
	exit(0);
	return;
}

// imprime todas as entidades, as barreiras e informacoes extras
void print_game (game_t* game){
	erase();

	print_boarders();

	print_score(game);

	initialize_current_begin(&game->entities);
	
	wattron(stdscr, COLOR_PAIR(GREEN));
	while(game->entities.current != game->entities.end)
	{
		move(game->entities.current->key.lin, game->entities.current->key.col);
		addch(SNAKE_CELL);
		increment_current(&game->entities);
	}
	refresh();
	return;
}

// adiciona o score
void print_score(game_t *game){
	unsigned int i;
	char score[12];
	sprintf(score, "%d", game->score);
	move(1, GAME_WIDTH/2);
	for(i = 0; i < strlen(score); ++i){
		addch(score[i]);
	}	
	mvprintw(1, GAME_WIDTH/2-strlen(SCORE), SCORE);
	return;
}

// adiciona as barreiras a tela do ncurses
void print_boarders(){
	wattron(stdscr, COLOR_PAIR(WHITE));
	int i;
	for (i = 0; i < GAME_HIGHT+1; ++i)
	{
		move(i, 0);
		addch('#');
		move(i, GAME_WIDTH+1);
		addch('#');
	}
	for (i = 0; i < GAME_WIDTH+2; ++i)
	{
		move(0, i);
		addch('#');
		move(GAME_HIGHT, i);
		addch('#');
	}
}

// le a tecla pressionada e a adiciona na struct 'play'
void read_play (play_t* play){
	int key = getch();

	/*todas as teclas recebem 0*/
	play->none = 0;
	play->left_arrow = 0;
	play->right_arrow = 0;
	play->up_arrow = 0;
	play->down_arrow = 0;

	if (key == ERR){
		play->none = 1;
		return;
	}

	if (key == KEY_LEFT){
		play->left_arrow = 1;
		return;
	}

	if (key == KEY_RIGHT){
		play->right_arrow = 1;
		return;
	}

	if (key == KEY_UP){
		play->up_arrow = 1;
		return;
	}

	if (key == KEY_DOWN){
		play->down_arrow = 1;
		return;
	}

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