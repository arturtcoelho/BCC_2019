#ifndef __GAMEAUX__
#define __GAMEAUX__

#include "models.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

void update_matrix(game_t* game);
void increment_version (entity_t *ent);
int alien_coloum (list_t *l, int limit);
int game_validity (game_t* game, play_t* play);
int check_alien_colision(game_t *game, entity_t *alien);
int have_aliens(game_t *game);
void reset_game(game_t *game, int *timer);
void read_play (play_t* play);
void atualize_score(game_t *game, entity_t *alien);
int mother_time(game_t *game, int timer);
void endgame (game_t* game);
void fudeu_protocol();
void kill_all(game_t *game, play_t *play);

#endif
