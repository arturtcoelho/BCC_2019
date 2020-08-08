#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HIGHT 10
#define WIDHT 10

typedef struct game_t {
	int board[HIGHT+2][WIDHT+2];
	int shown[HIGHT+2][WIDHT+2];
	int num_plays;
	int dificulty;
	int validity;
	int bomb_number;
} game_t;

typedef struct play_t {
	int x, y;
	int type;
} play_t;

//  game_t *game
void mount_board (game_t *game);
int surround (int x, int y, int n, game_t *game);
int rand_piece (game_t *game);
int valid_game (game_t *game);
void print_board (game_t *game);
void read_play (play_t *play);
void do_play (play_t play, game_t *game);
void expansion (int x, int y, game_t *game);
void print_result (game_t *game);


int main() {
	game_t game;
	play_t play;

	mount_board(&game);
	printf("%d\n", game.bomb_number);
	while (valid_game(&game)) { 
		print_board(&game);
		read_play(&play); 
		do_play(play, &game);
	}
	print_result(&game);
	
	return 0;
}

void mount_board ( game_t *game) {

	srand(time(0));

	printf("Type in dificulty:\n");
	scanf("%d", &game->dificulty);

	game->bomb_number = 0;
	game->validity = 1;
	game->num_plays = 0;

	for (int i = 0; i < HIGHT+2; ++i) {
		game->shown[i][0] = 9;
		game->board[i][0] = 9;
	}

	for (int i = 0; i < HIGHT+2; ++i){
		game->shown[i][WIDHT+1] = 9;
		game->board[i][WIDHT+1] = 9;
	}

	for (int i = 0; i < WIDHT+2; ++i) {
		game->shown[0][i] = 9;
		game->board[0][i] = 9;
	}

	for (int i = 0; i < WIDHT+2; ++i){
		game->shown[HIGHT+1][i] = 9;
		game->board[HIGHT+1][i] = 9;
	}

	for (int i = 1; i < HIGHT+1; ++i) {
		for (int j = 1; j < WIDHT+1; ++j) {
			if (rand_piece(game)) {
				game->bomb_number ++;
				game->board[i][j] = -1; 
			}
		}
	}

	for (int i = 1; i < HIGHT+1; ++i) {
		for (int j = 1; j < WIDHT+1; ++j) {
			game->board[i][j] = surround(i, j, game->board[i][j], game);
		}
	}

	for (int i = 1; i < HIGHT+1; ++i) {
		for (int j = 1; j < WIDHT+1; ++j) {
			game->shown[i][j] = 0;
		}
	}
}

int surround (int x, int y, int n,  game_t *game){
	if (game->board[x][y] != -1){
		int cont = 0;

		for (int i = y-1; i <= y+1; ++i)
			if (game->board[x-1][i]==-1)
				cont++;		
		if (game->board[x][y-1]==-1) 
			cont++;
		if (game->board[x][y+1]==-1)
			cont++;
		for (int i = y-1; i <= y+1; ++i) 
			if (game->board[x+1][i]==-1) 
				cont++;
		return cont;
	}
	return -1;
}

int rand_piece ( game_t *game) {
	int n = game->dificulty / 10;
	switch (n) {
		case 0: if (rand() % 10 == 0) return -1;
			return 0;
		case 1: if (rand() % 10 <= 1) return -1;
			return 0;
		case 2: if (rand() % 10 <= 2) return -1;
			return 0;
		case 3: if (rand() % 10 <= 3) return -1;
			return 0;
		case 4: if (rand() % 10 <= 4) return -1;
			return 0;
		case 5: if (rand() % 10 <= 5) return -1;
			return 0;
		case 6: if (rand() % 10 <= 6) return -1;
			return 0;
		case 7: if (rand() % 10 <= 7) return -1;
			return 0;
		case 8: if (rand() % 10 <= 8) return -1;
			return 0;
		case 9: if (rand() % 10 <= 9) return -1;
			return 0;
		default: return 0;
	}
}

int valid_game (game_t *game) {
	if (!game->validity)
		return 0;
	int counter = 0;
	int total = HIGHT*WIDHT;
	int num = total - game->bomb_number;
	for (int i = 1; i <= HIGHT; ++i) {
		for (int j = 1; j <= WIDHT; ++j) {
			if (game->shown[i][j] == 1 && game->board[i][j] != -1)
				num--;
		}
	}
	if (num)
		return 1;
	printf("GANHOW!!!!\n");
	return 0;
}

void print_board ( game_t *game) {
	printf("\n");	
	
	for (int i = 1; i < HIGHT+1; ++i) {
		for (int j = 1; j < WIDHT+1; ++j) {
			if (game->shown[i][j] == 1) {
				if (game->board[i][j] == -1) {
					printf("* ");
				} else printf("%d ", game->board[i][j]);
			} else if (game->shown[i][j] == 2)
				printf("! ");
			else
				printf(". "); 
		}
		printf("\n");		
	}
	/*
	for (int i = 1; i < HIGHT+1; ++i)
	{
		for (int j = 1; j < WIDHT+1; ++j)
		{
			if (game->board[i][j] == -1)
				printf("* ");
			else 
				printf("%d ", game->board[i][j]);
		}
		printf("\n");
	}*/
}

void read_play ( play_t *play) {
	//testa se a jogada esta nos limites do tabuleiro
		printf("Type in coordinates of play:\n");
		scanf("%d%d%d",&play->type, &play->x, &play->y);
}


void do_play (play_t play, game_t *game){
	game->num_plays++;
	if (play.type == 0){
		if (game->board[play.x][play.y] == -1){
			game->validity = 0;
			return;
		}
		expansion(play.x, play.y, game);
		return;
	}
	game->shown[play.x][play.y] = 2;
}

void expansion (int x, int y, game_t *game) {
//checks x and y on borders
	if (game->board[x][y] == 9)
		return;
	if (game->board[x][y] != 0) {
		game->shown[x][y] = 1;
		return;
	}
	if (game->shown[x][y] == 1) 
		return;
	game->shown[x][y] = 1;
	expansion(x-1, y-1, game);
	expansion(x-1, y, game);
	expansion(x-1, y+1, game);
	expansion(x, y-1, game);
	expansion(x, y+1, game);
	expansion(x+1, y-1, game);
	expansion(x+1, y, game);
	expansion(x+1, y+1, game);
	return;
}

void print_result (game_t *game) {
	printf("Fim de jogo\n");
	printf("Jogadas: %d\n", game->num_plays);
	printf("\n");	
	for (int i = 1; i < HIGHT+1; ++i) {
		for (int j = 1; j < WIDHT+1; ++j) {
			if (game->board[i][j] == -1)
				printf("* ");
			else 
				printf("%d ", game->board[i][j]);
		}
		printf("\n");		
	}
}