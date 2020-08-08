#ifndef __PRINTGAME__
#define __PRINTGAME__

#include "models.h"	

void print_game (game_t *game);
void choose_n_print (entity_t *entity);
void print_entity (entity_t* entity, char str[]);
void print_init(game_t *game);
void print_boarders();
void print_score(game_t *game);
void print_lives(game_t *game);
void print_level_turn(game_t *game);
void print_end (game_t *game);

#define OPENING1 "==================| SPACE INVADERS |=================="
#define OPENING2 "Artur T. Coelho"
#define OPENING3 "Pressione qualquer tecla para jogar "
#define LEVEL "Fase:  "
#define SCORE "Pontos: "
#define FIM1 "Obrigado por jogar"
#define FIM2 "Seus Pontos: "

#define WHITE 1
#define GREEN 2
#define RED 3

/*entities models*/
#define ALIEN11 " A ( )/ \\"
#define ALIEN12 " A ( )\\ /"
#define ALIEN21 "I:I:I<===>/   \\ " 
#define ALIEN22 ":I:I:<===> \\ / "
#define ALIEN31 "Y_-_Y| - |<! !>"
#define ALIEN32 "_Y-Y_| - |>! !<"
#define BARRIER " OOOOO OOOOOOOOOO OOO"
#define CANNON1 " _-^-_ (oOoOo)"
#define CANNON2 " _-^-_ (OoOoO)"
#define MOTHER1 " _______ (O=O=O=O) *******"
#define MOTHER2 " _______ (:.:.:.:) *******"
#define SHOT "|"
#define BOMB1 "("
#define BOMB2 ")"
#define BARRIER_CELL "O"
#define BARRIER_EXPLOSION "*"
#define EXPLOSION "\\|/-*-/|\\"

#endif