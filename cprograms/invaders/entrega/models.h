/*defines all start positions, times, etc*/
/*define main structures*/

#ifndef __MODELS__ 
#define __MODELS__

#define GAME_HIGHT 40
#define GAME_WIDTH 130

/*game timings*/
#define SLEEP_TIME 200
#define BASIC_TIME 100
#define ALIEN_TIME 400
/*#define MOTHER_TIME 10000*/
	
#define PROBABILITY_BOMB 1000

#define ID_CANNON 1
#define ID_MOTHER 2
#define ID_ALIEN 3
#define ID_MAX_ALIEN 58
#define ID_BARRIER 58 
#define ID_MAX_BARRIER 158
#define ID_BOMBS 159
#define ID_EXPLOSION 0
#define NUM_ALIENS_PER_LINE 11
#define NUM_ALIENS_PER_COLUMN 5
#define NUM_BARRIERS_PER_LINE 9
#define NUM_BARRIERS_PER_COL 3
#define NUM_BARRIERS 4
#define MAX_NUM_SHOTS 5
#define MAX_NUM_BOMBS 3

/*initial positions*/
#define INITIAL_CANNON_LIN 38
#define INITIAL_CANNON_COL 48
#define INITIAL_ALIEN_LIN 2
#define INITIAL_ALIEN_COL 21
#define INITIAL_BARRIER_LIN 34
#define INITIAL_BARRIER_COL 25
#define INITIAL_MOTHER_LIN 0
#define INITIAL_MOTHER_COL 0 

/*sizes*/
#define ALIEN_HIGHT 3
#define ALIEN1_WIDTH 3
#define ALIEN23_WIDTH 5
#define CANNON_HIGHT 2
#define CANNON_WIDTH 7
#define MOTHER_HIGHT 2
#define MOTHER_WIDTH 9
#define EXPLOSION_HIGHT 3
#define EXPLOSION_WIDTH 3
#define LINE_SPACING 4
#define ALIENS_COL_SPACING 7
#define ALIENS_LIN_SPACING 4
#define BARRIER_COL_SPACING 24


/*define types*/ 
#define ALIEN1_TYPE 3 
#define ALIEN2_TYPE 4
#define ALIEN3_TYPE 5
#define CANNON_TYPE 1
#define MOTHER_TYPE 2
#define SHOT_TYPE 6
#define BOMB_TYPE 7
#define BARR_CELL_TYPE 8
#define EXPLOSION_TYPE 9

typedef struct {
	int left_arrow, right_arrow, force_stop, space_bar, kill;
} play_t;

typedef struct entity {
	int id;
	int type;
	int lin;
	int col;
	int hight;
	int width;
	int validity;
	int version;
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
	int lives;
	int alien_time;
	int score;
	int num_shots;
	int shot_id;
	int num_bombs;
	int bomb_id;
	int num_aliens;
	int direction;
	int level;
	int last_shot;
} game_t;

#endif
