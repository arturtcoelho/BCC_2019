
#ifndef __LISTA_LIB__
#define __LISTA_LIB__

#include "models.h"	

// struct node_t {
// 	entity_t key;
// 	struct node_t *next;
// 	struct node_t *prev;
// };
// typedef struct node_t node_t;

// typedef struct list_t {
// 	node_t *beg;
// 	node_t *current;
// 	node_t *end;
// 	int size;
// } list_t;


int initialize_list(list_t *l);
int empty_list(list_t *l);
void destroy_list(list_t *l);
int insert_begining_list(entity_t item, list_t *l);
int list_size(list_t *l);
int insert_end_list(entity_t item, list_t *l);
int remove_begining_list(list_t *l);
int remove_end_list(list_t *l);
// int remove_id_list(int id, list_t *l);
// entity_t* bellong_list(int id, list_t *l);
int initialize_current_begin(list_t *l);
int initialize_current_end(list_t *l);
int increment_current(list_t *l);
void decrement_current(list_t *l);
entity_t* consult_current(list_t *current);
int remove_current(list_t *l);
int current_end(list_t *l);

#endif