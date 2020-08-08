/*define all models, dimensions, initial positions, types*/

/*game total space*/
#define GAME_HIGHT 40
#define GAME_WIDHT 130

/*number of entities*/
#define NUM_MAX_ENTITIES 200

/*game timings*/
#define SLEEP_TIME 200
#define BASIC_TIME 100
#define ALIEN_TIME 500
#define MOTHER_TIME 10000
	
/*initial positions*/
#define INITIAL_CANNON_X 38
#define INITIAL_CANNON_Y 48
#define INITIAL_ALIEN_X 6
#define INITIAL_ALIEN_Y 21
#define INITIAL_BARRIER_X 32
#define INITIAL_BARRIER_Y 20

/*sizes*/
#define ALIEN_X 3
#define ALIEN_Y 5
#define CANNON_X 2
#define CANNON_Y 7
#define MOTHER_X 2
#define MOTHER_Y 9
#define Y_SPACING 3

/*define types*/ 
#define ALIEN1_TYPE 3 
#define ALIEN2_TYPE 4
#define ALIEN3_TYPE 5
#define CANNON_TYPE 1
#define MOTHER_TYPE 2
#define SHOT_TYPE 6
#define BOMB_TYPE 7
#define BARR_CELL_TYPE 8

/*entities models*/
#define ALIEN11 "I:I:I<===>/   \\"
#define ALIEN12 ":I:I:<===> \\ /"
#define ALIEN21 "WwWwWT___TV v V"
#define ALIEN22 "wWwWwT___Tv V v"
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

typedef struct {
	int left_arrow, right_arrow, force_stop, space_bar;
} play_t;

typedef struct {
	int type;
	int xpos, ypos;
	int hight, lenght;
	int validity;
	int version;
	int clearence;
} entity_t;

typedef struct {
	int board[GAME_HIGHT][GAME_WIDHT];
	entity_t entities[NUM_MAX_ENTITIES];
	int validity;
	int score;
	int lives;
	int direction;
	int descent;
	int alien_time;
} game_t;

void initialize_entity(game_t* game, int index,int type,int xpos,int ypos,int hight,int lenght,int validity, int version);
void initialize_aliens(game_t* game);
void initialize_barriers(game_t* game);
int game_validity (game_t* game, play_t* play);
void create_shot(game_t* game);
void remove_entity(game_t* game, int index);
int last_alien_coloum(game_t* game);
int first_alien_coloum(game_t* game);
void move_aliens(game_t* game, int direction);
void print_entity(entity_t* entity, char str[]);
void choose_n_print (game_t* game, int i);		
void move_aliens_down(game_t* game);