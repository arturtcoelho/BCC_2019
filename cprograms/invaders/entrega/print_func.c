#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>

#include "linked_list.h"
#include "print_func.h"
#include "models.h"

/*funcao de impressao para testes da matriz de colisao*/
/*void print_game (game_t *game){
	clear();
	int i;
	for (i = 0; i < GAME_HIGHT; ++i){
		move(i, 0);
		addch(i/10 + '0');
		addch(i%10 + '0');
	}
	move(0, 0);
	for (int i = 0; i < GAME_HIGHT; ++i)
	{
		for (int j = 0; j < GAME_WIDTH; ++j)
		{
			if (game->board[i][j])
				addch(game->board[i][j]%26+'0');
			else
				addch('.');
		}
		move(i+1, 0);
	}
	refresh();
	return;
}*/

/*imprime todas as entidades, as barreiras e informacoes extras*/
void print_game (game_t* game){
	erase();

	print_boarders();

	print_score(game);
	print_lives(game);

	initialize_current_begin(&game->entities);
	while(game->entities.current != game->entities.end)
	{
		if (game->entities.current->key.validity)
		choose_n_print(&game->entities.current->key);		
		increment_current(&game->entities);
	}
	refresh();
	return;
}

/*adiciona as barreiras a tela do ncurses*/
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

/*adiciona os coracoes (vidas)*/
void print_lives(game_t *game){
	wattron(stdscr, COLOR_PAIR(RED));
	int i;
	for (i = 1; i < game->lives+1; ++i)
	{
		move(GAME_HIGHT-1, i*2 -1);
		addch('<');
		addch('3');
	}
}

/*adiciona o score*/
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

/*dada a entidade recebida, a impreme*/
void choose_n_print (entity_t *entity){
	if (!entity->validity){
		print_entity(entity, EXPLOSION);
		return;
	}

	switch (entity->type)
	{
		/*cannon*/
		case CANNON_TYPE:
			wattron(stdscr, COLOR_PAIR(WHITE));
			if (entity->version >= 5)
			{
				print_entity(entity, CANNON1);
				break;				
			}
			print_entity(entity, CANNON2);
			break;

		/*alien 1*/
		case ALIEN1_TYPE:
			wattron(stdscr, COLOR_PAIR(GREEN));
			if (entity->version >= 5)
			{
				print_entity(entity, ALIEN11);
				break;				
			}
			print_entity(entity, ALIEN12);
			break;

		/*alien2*/
		case ALIEN2_TYPE:
			wattron(stdscr, COLOR_PAIR(GREEN));
			if (entity->version >= 5)
			{
				print_entity(entity, ALIEN21);
				break;				
			}
			print_entity(entity, ALIEN22);
			break;

		/*alien 3*/
		case ALIEN3_TYPE:
			wattron(stdscr, COLOR_PAIR(GREEN));
			if (entity->version >= 5)
			{
				print_entity(entity, ALIEN31);
				break;				
			}
			print_entity(entity, ALIEN32);
			break;

		/*mothership*/
		case MOTHER_TYPE:
			wattron(stdscr, COLOR_PAIR(RED));
			if (entity->version >= 5)
			{
				print_entity(entity, MOTHER1);
				break;				
			}
			print_entity(entity, MOTHER2);
			break;

		/*shot*/
		case SHOT_TYPE:
			wattron(stdscr, COLOR_PAIR(GREEN));
			print_entity(entity, SHOT);
			break;				

		/*shot*/
		case BARR_CELL_TYPE:
			wattron(stdscr, COLOR_PAIR(GREEN));
			print_entity(entity, BARRIER_CELL);
			break;				

		/*bomb*/
		case BOMB_TYPE:
			wattron(stdscr, COLOR_PAIR(WHITE));
			if (entity->version >= 5)
			{
				print_entity(entity, BOMB1);
				break;				
			}
			print_entity(entity, BOMB2);
			break;
		case EXPLOSION_TYPE:
			wattron(stdscr, COLOR_PAIR(RED));
			print_entity(entity, EXPLOSION);
			break;
	}

	return;
}

/*imprime uma entidade baseada em sua posicao e tamanho*/
void print_entity (entity_t* entity, char str[]){
	int i, j;
	move(entity->lin, entity->col);
	for (i = 0; i < entity->hight; ++i)
	{
		move(i+entity->lin, entity->col);
		for (j = 0; j < entity->width; ++j)
		{
			addch(str[i*entity->width+j]);
		}	
	}

	return;
}

/*imprime as mensagens de inicio*/
void print_init(game_t *game){

	clear();
	print_boarders();
	initialize_current_begin(&game->entities);
	while(game->entities.current != game->entities.end)
	{
		if (game->entities.current->key.validity)
		{
			choose_n_print(&game->entities.current->key);		
		}
		increment_current(&game->entities);
	}

	wattron(stdscr, COLOR_PAIR(RED));
	entity_t ent1, ent2;

	ent1.width = strlen(OPENING1)/3;
	ent1.hight = 3;
	ent1.lin = 3;
	ent1.col = 50;

	mvprintw(GAME_HIGHT-2, 1, OPENING2);

	ent2.width = strlen(OPENING3)/2;
	ent2.hight = 2;
	ent2.lin = 30;
	ent2.col = 50;
	print_entity(&ent1, OPENING1);	
	print_entity(&ent2, OPENING3);	

	refresh();
	return;
}

/*imprime as mensagens de troca de fase*/
void print_level_turn(game_t *game){
	clear();
	print_boarders();
	initialize_current_begin(&game->entities);
	while(game->entities.current != game->entities.end)
	{
		if (game->entities.current->key.validity)
		{
			choose_n_print(&game->entities.current->key);		
		}
		increment_current(&game->entities);
	}

	wattron(stdscr, COLOR_PAIR(RED));


	char level[3];
	sprintf(level, "%d", game->level);
	mvprintw(5, 50 + strlen(LEVEL) + 1, level);
	mvprintw(5, 50, LEVEL);
	mvprintw(GAME_HIGHT-2, 1, OPENING2);

	entity_t ent;

	ent.width = strlen(OPENING3)/2;
	ent.hight = 2;
	ent.lin = 30;
	ent.col = 50;

	print_entity(&ent, OPENING3);

	refresh();	
	return;
}

/*imprime a mensagem de fim e seu score*/
void print_end(game_t *game){
	wattron(stdscr, COLOR_PAIR(RED));
	
	mvprintw(30, 50, FIM1);
	mvprintw(32, GAME_WIDTH/2, FIM2);				
	unsigned int i;
	char score[12];
	sprintf(score, "%d", game->score);
	move(32, GAME_WIDTH/2+strlen(FIM2));
	for(i = 0; i < strlen(score); ++i){
		addch(score[i]);
	}	
	mvprintw(32, GAME_WIDTH/2-strlen(SCORE), SCORE);
	return;
}
