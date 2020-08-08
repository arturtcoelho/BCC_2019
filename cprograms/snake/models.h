// defines all start positions, times, etc
// define main structures

#ifndef __MODELS__ 
#define __MODELS__

#define GAME_HIGHT 25
#define GAME_WIDTH 60

// game timings
#define SLEEP_TIME 200

// tamanhos
#define TAM_INICIAL 5

// define directions
#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

// define cores
#define WHITE 1
#define GREEN 2
#define RED 3

#define SCORE "Pontos: "
#define SNAKE_CELL '0'

typedef struct {
	int left_arrow, right_arrow, up_arrow, down_arrow, none;
} play_t;

typedef struct entity {
	int lin;
	int col;
} entity_t;

struct node_t {
	entity_t key;
	struct node_t *next;
	struct node_t *prev;
};
typedef struct node_t node_t;

typedef struct list_t {
	node_t *beg;
	node_t *current;
	node_t *end;
	int size;
} list_t;

typedef struct game {
	list_t entities;
	int board[GAME_HIGHT][GAME_WIDTH];
	int validity;
	int score;
	int direction;
} game_t;

#endif
