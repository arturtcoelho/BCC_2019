#include <curses.h>
#include <unistd.h>
#include <string.h>
#include "my_models.h"


void initialize_aliens(game_t* game){
	int i, y;
	/*add aliens1 to entities*/
	for (i = 3, y = INITIAL_ALIEN_Y; i < 14; ++i, y += ALIEN_Y+Y_SPACING)
	{
		initialize_entity(game, i, ALIEN1_TYPE, INITIAL_ALIEN_X, y, ALIEN_X, ALIEN_Y, 1, 1);
	}	

	/*add aliesn2 to entities*/

	for (i = 14, y = INITIAL_ALIEN_Y; i < 25; ++i, y += ALIEN_Y+Y_SPACING)
	{
		initialize_entity(game, i, ALIEN2_TYPE, INITIAL_ALIEN_X + ALIEN_X+1, y, ALIEN_X, ALIEN_Y, 1, 1);
	}

	for (i = 25, y = INITIAL_ALIEN_Y; i < 36; ++i, y += ALIEN_Y+Y_SPACING)
	{
		initialize_entity(game, i, ALIEN2_TYPE, INITIAL_ALIEN_X + (2*(ALIEN_X+1)), y, ALIEN_X, ALIEN_Y, 1, 1);
	}		
	/*add aliesn3 to entities*/

	for (i = 36, y = INITIAL_ALIEN_Y; i < 47; ++i, y += ALIEN_Y+Y_SPACING)
	{
		initialize_entity(game, i, ALIEN3_TYPE, INITIAL_ALIEN_X + (3*(ALIEN_X+1)), y, ALIEN_X, ALIEN_Y, 1, 1);
	}

	for (i = 47, y = INITIAL_ALIEN_Y; i < 58; ++i, y += ALIEN_Y+Y_SPACING)
	{
		initialize_entity(game, i, ALIEN3_TYPE, INITIAL_ALIEN_X + (4*(ALIEN_X+1)), y, ALIEN_X, ALIEN_Y, 1, 1);
	}		
	
	return;

}

void initialize_barriers(game_t* game){
	/*lines of 5*/
	int i, y;
	for (i = 100, y=GAME_WIDHT/5 ; i < 105; ++i, ++y)
	{
		initialize_entity(game, i, BARR_CELL_TYPE, INITIAL_CANNON_X-4, y, 1, 1, 1, 1);
	}
	for (i = 105, y = 2*GAME_WIDHT/5; i < 110; ++i, ++y)
	{
		initialize_entity(game, i, BARR_CELL_TYPE, INITIAL_CANNON_X-4, y, 1, 1, 1, 1);
	}
	for (i = 110, y = 3*GAME_WIDHT/5; i < 115; ++i, ++y)
	{
		initialize_entity(game, i, BARR_CELL_TYPE, INITIAL_CANNON_X-4, y, 1, 1, 1, 1);
	}
	for (i = 115, y = (4*GAME_WIDHT)/5; i < 120; ++i, ++y)
	{
		initialize_entity(game, i, BARR_CELL_TYPE, INITIAL_CANNON_X-4, y, 1, 1, 1, 1);
	}
	/*lines of 7*/
	for (i = 120, y = GAME_WIDHT/5-1; i < 134; i+=2, ++y)
	{
		initialize_entity(game, i, BARR_CELL_TYPE, INITIAL_CANNON_X-3, y, 1, 1, 1, 1);
		initialize_entity(game, i+1, BARR_CELL_TYPE, INITIAL_CANNON_X-2, y, 1, 1, 1, 1);

	}
	for (i = 134, y = 2*GAME_WIDHT/5-1; i < 148; i+=2, ++y)
	{
		initialize_entity(game, i, BARR_CELL_TYPE, INITIAL_CANNON_X-3, y, 1, 1, 1, 1);
		initialize_entity(game, i+1, BARR_CELL_TYPE, INITIAL_CANNON_X-2, y, 1, 1, 1, 1);

	}
	for (i = 148, y = 3*GAME_WIDHT/5-1; i < 162; i+=2, ++y)
	{
		initialize_entity(game, i, BARR_CELL_TYPE, INITIAL_CANNON_X-3, y, 1, 1, 1, 1);
		initialize_entity(game, i+1, BARR_CELL_TYPE, INITIAL_CANNON_X-2, y, 1, 1, 1, 1);

	}
	for (i = 162, y = 4*GAME_WIDHT/5-1; i < 176; i+=2, ++y)
	{
		initialize_entity(game, i, BARR_CELL_TYPE, INITIAL_CANNON_X-3, y, 1, 1, 1, 1);
		initialize_entity(game, i+1, BARR_CELL_TYPE,  INITIAL_CANNON_X-2, y, 1, 1, 1, 1);

	}

	return;
}

void initialize_entity(game_t* game, int index,int type,int xpos,int ypos,int hight,int lenght,int validity, int version){
	game->entities[index].type = type; 
	game->entities[index].xpos = xpos;
	game->entities[index].ypos = ypos;
	game->entities[index].hight = hight;
	game->entities[index].lenght = lenght;
	game->entities[index].validity = validity;
	game->entities[index].version = version;
	return;
}


int game_validity (game_t* game, play_t* play){
	if (play->force_stop)
		return 0;
	if (game->lives <= 0)
		return 0;
	return game->validity;
}



void choose_n_print (game_t* game, int i){		
	switch (game->entities[i].type) 
	{
		case 1:
		if (game->entities[i].version)
		{
			print_entity(&game->entities[i], CANNON1);
			break;				
		}
		print_entity(&game->entities[i], CANNON2);
		break;
		case 2:
		if (game->entities[i].version)
		{
			print_entity(&game->entities[i], MOTHER1);
			break;				
		}
		print_entity(&game->entities[i], MOTHER2);
		break;
		case 3:
		if (game->entities[i].version)
		{
			print_entity(&game->entities[i], ALIEN11);
			break;				
		}
		print_entity(&game->entities[i], ALIEN12);
		break;
		case 4:
		if (game->entities[i].version)
		{
			print_entity(&game->entities[i], ALIEN21);
			break;				
		}
		print_entity(&game->entities[i], ALIEN22);
		break;
		case 5:
		if (game->entities[i].version)
		{
			print_entity(&game->entities[i], ALIEN31);
			break;				
		}
		print_entity(&game->entities[i], ALIEN32);

		break;
		case 6:
		print_entity(&game->entities[i], SHOT);
		break;				
		case 7:
		if (game->entities[i].version)
		{
			print_entity(&game->entities[i], BOMB1);
			break;				
		}
		print_entity(&game->entities[i], BOMB2);
		break;
		case 8:
		print_entity(&game->entities[i], BARRIER_CELL);
		break;				
		default:;
	}
	return;
}

void print_entity (entity_t* entity, char str[]){
	int type = entity->type, version = entity->version;
	int lenght = entity->lenght, hight = entity->hight;
	int x = entity->xpos - hight, y = entity->ypos + lenght;
	unsigned int i;
	for (i = 0; i < strlen(str); ++i)
	{
		if (i%lenght == 0){
			x++;
			y-=lenght;
		}
		move(x, y+i);
		addch(str[i]);
	}
	return;
}

void create_shot(game_t* game){
	initialize_entity(game, 69, SHOT_TYPE, game->entities[1].xpos-1, game->entities[1].ypos + game->entities[1].lenght/2, 1, 1, 1, 1);
	return;
}

void remove_entity(game_t* game, int index){
	game->entities[index].validity = 0;
}

int last_alien_coloum(game_t* game){
	int last = 0, result = -1, i;

	for (i = 3; i < 58; ++i)
	{
		if (game->entities[i].validity)
		{
			if (game->entities[i].ypos > last){
				last = game->entities[i].ypos;
				result = i;
			}

		}
	}
	if (result == -1)
		return 0;
	return result;
}

int first_alien_coloum(game_t* game){
	int first = GAME_WIDHT, result = -1, i;
	for (i = 3; i < 58; ++i)
	{
		if (game->entities[i].validity)
		{
			if (game->entities[i].ypos < first){
				first = game->entities[i].ypos;
				result = i;
			}
		}

	}
	if (result == -1)
		return 0;
	return result;	
}

void move_aliens(game_t* game, int direction){
	int i;

	if (direction)
	{
		for (i = 3; i < 59; ++i)
		{
			game->entities[i].ypos++;
			game->entities[i].version = !game->entities[i].version;
		}
	}
	else
	{
		for (i = 3; i < 59; ++i)
		{
			game->entities[i].ypos--;
			game->entities[i].version = !game->entities[i].version;
		}	
	}
}

void move_aliens_down(game_t* game){
	int i;
	for (i = 3; i < 59; ++i)
	{
		if (game->entities[i].xpos + ALIEN_X < GAME_HIGHT)
		{
			game->entities[i].xpos++;
		}
	}
	return;
}