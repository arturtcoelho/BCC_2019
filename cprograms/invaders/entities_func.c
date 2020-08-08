#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game_aux.h"
#include "linked_list.h"
#include "setup.h"
#include "print_func.h"
#include "game_aux.h"


/*move uma entidade em uma de 4 direcoes*/
void move_entity(entity_t *ent, int dir){
	switch(dir){
		case LEFT:
			ent->col--;
			return;
		case RIGHT:
			ent->col++;
			return;
		case UP:
			ent->lin--;
			return;
		case DOWN:
			ent->lin++;
			return;
		default: return;
	}
}


/*cria o tiro, se possivel*/
void create_shot(game_t* game, entity_t *cannon){
	if (game->num_shots > MAX_NUM_SHOTS)
		return;

	game->num_shots++;
	game->shot_id += 2;

	initialize_entity_inlist(&game->entities, game->shot_id, SHOT_TYPE, cannon->lin, cannon->col+CANNON_WIDTH/2, 1, 1, 1, 1);

	return;
}

/*compara a jogada e vove o canhao, ou atira*/
void atualize_cannon(game_t* game, play_t* play){
	if (game->last_shot < 4){
		game->last_shot++;
	}
	entity_t *cannon = bellong_list(ID_CANNON, &game->entities);
	if (cannon == NULL)
		fudeu_protocol(); /*caso o canhao por algum motivo nao exista*/

	/*esquerda*/
	if ((cannon->col > 1) && play->left_arrow){ 
		move_entity(cannon, LEFT);
		increment_version(cannon);
	}

	/*direita*/
	if ((cannon->col < GAME_WIDTH-CANNON_WIDTH) && play->right_arrow){
		move_entity(cannon, RIGHT);
		increment_version(cannon);
	}

	/*atira*/
	if (play->space_bar && game->last_shot > 3){
		create_shot(game, cannon);
		game->last_shot = 0;
	}

	return;
}

/*remove uma entidade baseada no seu id*/
void remove_entity(game_t* game, int id){
	if (id == 0)
		return;
	remove_id_list(id, &game->entities);
	return;
}

/*para cada elemento na lista, caso seja um tiro do canhao
eh feita a acao correspondente, seja apenas andar para frente
ou andar para frente*/
void atualize_shots(game_t* game){
	entity_t *shot;
	initialize_current_begin(&game->entities);
	while(game->entities.current != game->entities.end)
	{
		shot = consult_current(&game->entities);
		if(shot->type == SHOT_TYPE)
		{
			if (shot->lin-1 < 0) /*chegou no topo da tela*/
			{
				game->num_shots--;
				remove_entity(game, shot->id);
			} 
			else 
			{
				if (game->board[shot->lin-1][shot->col] == 0){
					move_entity(shot, UP);
				}
				else /*encontrou um alien ou barreira*/ 
				{
					if (game->board[shot->lin-1][shot->col] >= ID_ALIEN && game->board[shot->lin-1][shot->col] <= ID_MAX_ALIEN){ /*se acertou um alien*/
						game->num_aliens--;
						entity_t *alien = bellong_list(game->board[shot->lin-1][shot->col], &game->entities);
						if (alien != NULL){
							initialize_entity_inlist(&game->entities, ID_EXPLOSION, EXPLOSION_TYPE, alien->lin, alien->col, EXPLOSION_HIGHT, EXPLOSION_WIDTH, 1, 1); /*cria explosao no alien*/
							/*(list, id, type, lin, col, high, len, val, version)*/
						}
					}
					game->num_shots--;
					entity_t *alien_hit = bellong_list(game->board[shot->lin-1][shot->col], &game->entities);
					if (alien_hit != NULL)
						atualize_score(game, alien_hit);
					remove_entity(game, shot->id);
					remove_entity(game, game->board[shot->lin-1][shot->col]);
				}
			}
		}
		increment_current(&game->entities);
	}

	return;
}

/*move todos as entidades com tipo alien para a direcao indicada*/
void move_aliens(game_t *game, int dir){
	entity_t *alien;
	initialize_current_begin(&game->entities);
	while(!current_end(&game->entities)){
		alien = &game->entities.current->key;
		if (alien->type == ALIEN1_TYPE || alien->type == ALIEN2_TYPE || alien->type == ALIEN3_TYPE){
			move_entity(alien, dir);
			check_alien_colision(game, alien);
			increment_version(alien);
		}
		increment_current(&game->entities);
	}
	return;
}

/*adiciona uma bomba na lista, logo abaixo do alien correspondente, se possivel*/
void add_bomb(game_t *game, entity_t *alien){
	if (game->num_bombs > MAX_NUM_BOMBS)
		return;

	game->num_bombs++;
	game->bomb_id += 2;

	initialize_entity_inlist(&game->entities, game->bomb_id, BOMB_TYPE, alien->lin+ALIEN_HIGHT-2, alien->col+alien->width/2, 1, 1, 1, 1);

	return;
}

/*para cada alien, no caso de probabilidade positiva, cria uma bomba*/
void drop_bombs(game_t *game){
	entity_t *alien;
	initialize_current_begin(&game->entities);
	while(game->entities.current != game->entities.end){
		alien = &game->entities.current->key;
		if (alien->type == ALIEN1_TYPE || alien->type == ALIEN2_TYPE || alien->type == ALIEN3_TYPE){
			if ((rand() % 1000) < PROBABILITY_BOMB/game->num_aliens){
				add_bomb(game, alien);
			}
		}
		increment_current(&game->entities);
	}
	return;
}

/*faz o movimento dos aliens na lista, assim como os tiros*/
void atualize_aliens(game_t* game){
	if (game->direction == RIGHT){
		if ((alien_coloum(&game->entities, RIGHT)) < GAME_WIDTH){
			move_aliens(game, RIGHT);
		}
		else
		{
			game->direction = LEFT;
			game->alien_time -= 5;
			move_aliens(game, LEFT);
			move_aliens(game, DOWN);
		}
	}
	else
	{
		if (alien_coloum(&game->entities, LEFT) >= 1)
			move_aliens(game, LEFT);
		else
		{
			game->direction = RIGHT;
			game->alien_time -= 5;
			move_aliens(game, RIGHT);
			move_aliens(game, DOWN);
		}
	}
	drop_bombs(game);
	if (game->alien_time < 50){
		game->alien_time = 50;
	}
	return;

}

/*move as bombas e confere suas colisoes*/
void atualize_bombs(game_t *game){
	entity_t *bomb;
	int idbellow;
	initialize_current_begin(&game->entities);
	while(!current_end(&game->entities)){
		bomb = &game->entities.current->key;
		if (bomb->type == BOMB_TYPE){
			idbellow = game->board[bomb->lin+1][bomb->col];
			if (bomb->lin+1 >= GAME_HIGHT){
				remove_entity(game, bomb->id);
				game->num_bombs--;
			}
			else 
			{
				if (idbellow == 0 || (idbellow >= ID_ALIEN && idbellow <= ID_MAX_ALIEN)){/*nao acertou nada*/
					move_entity(bomb, DOWN);
					increment_version(bomb);
				}
				if (idbellow >= ID_BARRIER && idbellow <= ID_MAX_BARRIER){/*acertou barretira*/
					remove_entity(game, bomb->id);
					remove_entity(game, idbellow);
					game->num_bombs--;
				}
				if (idbellow == ID_CANNON){/*acertou o canhao*/
					remove_entity(game, bomb->id);
					game->lives--;
					game->num_bombs--;
				}
			}
		}
		increment_current(&game->entities);
	}
	return;
}

/*remove as explosoes apos certo periodo de tempo*/
void remove_explosions(game_t *game){
	entity_t *explosion;
	initialize_current_begin(&game->entities);

	while(!current_end(&game->entities)){
		explosion = consult_current(&game->entities);
		if (explosion->type == EXPLOSION_TYPE){
			explosion->version++;
			if (explosion->version > 4)
				remove_id_list(explosion->id, &game->entities);
		}
		increment_current(&game->entities);
	}

	return;
}

/*anda com a nave mae*/
void atualize_mother(game_t *game){
	entity_t *mother = bellong_list(ID_MOTHER, &game->entities);
	if (mother == NULL)
		return;
	mother->col++;
	mother->version++;
	
	if (mother->version >= 5)
		mother->version = 0;

	if (mother->col>GAME_WIDTH - MOTHER_WIDTH)
		mother->width--;

	if (mother->col>GAME_WIDTH)
		remove_id_list(mother->id, &game->entities);
}

/*inicializa a nave mae*/
void create_mother(game_t *game){
	initialize_entity_inlist(&game->entities, ID_MOTHER, MOTHER_TYPE, 2, 1, MOTHER_HIGHT, MOTHER_WIDTH, 1, 1);
	/*(list, id, type, lin, col, high, len, val, version)*/
	return;
}
