#ifndef __SETUP__
#define __SETUP____

#include "models.h"

void init_game (game_t* game);
void initialize_all_entities(game_t *game);
void initialize_aliens(game_t *game);
void initialize_barries(game_t *game);
void initialize_entity_inlist(list_t *l, int id, int type, int lin, int col, int high, int widht, int val, int vers);
void init_program ();

#endif

