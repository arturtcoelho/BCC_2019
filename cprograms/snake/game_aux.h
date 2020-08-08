#ifndef __GAME_AUX__

void init_game(game_t* game);
int game_validity(game_t* game, play_t* play);
void read_play (play_t* play);
void update_matrix(game_t* game);
void do_play(game_t* game, play_t* play);
void endgame(game_t* game);
void init_program ();
void initialize_entity_inlist(list_t *l, int lin, int col);
void print_game (game_t* game);
void print_entity (entity_t* entity, char c);
void print_boarders();
void print_score(game_t *game);

#endif