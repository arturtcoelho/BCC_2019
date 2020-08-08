#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>

#include "linked_list.h"
#include "models.h"

/*struct node_t {
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
*/

int initialize_list(list_t *l){
	l->size = 0;
	l->beg = (node_t*) malloc(sizeof(node_t));
	l->end = (node_t*) malloc(sizeof(node_t));
	l->current = NULL;

	if (l->beg == NULL || l->end == NULL)
		return 0;

	l->beg->next = l->end;
	l->beg->prev = NULL;
	l->end->next = NULL;
	l->end->prev= l->beg;

	return 1;
}

int empty_list(list_t *l){
	return !l->size;
}

void destroy_list(list_t *l){
	if(!empty_list(l)){
		initialize_current_begin(l);
		while(remove_current(l));
	}

	free(l->beg);
	free(l->end);
	l->size = 0;
	return;
}

int insert_begining_list(entity_t item, list_t *l){
	node_t *old = l->current;
	l->current = (node_t*) malloc(sizeof(node_t));

	if (l->current == NULL)
		return 0;

	l->current->key = item;
	l->current->prev = l->beg;
	l->current->next = l->beg->next;

	l->beg->next->prev = l->current;
	l->beg->next = l->current;

	l->size++;
	l->current = old;
	return 1;
}

int list_size(list_t *l){
	return l->size;
}

int insert_end_list(entity_t item, list_t *l){
	node_t *old = l->current;
	l->current = (node_t*) malloc(sizeof(node_t));

	if (l->current == NULL)
		return 0;

	l->current->key = item;
	l->current->next = l->end;
	l->current->prev = l->end->prev;

	l->end->prev->next = l->current;
	l->end->prev = l->current;

	l->size++;
	l->current = old;
	return 1;
}

int remove_begin_list(list_t *l){
	if (empty_list(l))
		return 0; 
	initialize_current_begin(l);
	return remove_current(l);  
}

int remove_end_list(list_t *l){
	if (empty_list(l))
		return 0; 
	initialize_current_end(l);
	return remove_current(l);
}

// int remove_id_list(int id, list_t *l){
// 	if (empty_list(l))
// 		return 0;
	
// 	node_t *node = l->beg->next;
// 	while((node != l->end) && (node->key.id != id)){
// 		node = node->next;
// 	}

// 	if (node == l->end)
// 		return 0;

// 	node->next->prev = node->prev;
// 	node->prev->next = node->next;

// 	free(node);

// 	return 1;
// }

// entity_t* bellong_list(int id, list_t *l){
// 	if (empty_list(l))
// 		return NULL;

// 	node_t *node = l->beg->next;

// 	l->end->key.id = id;

// 	while((node != l->end) && (node->key.id != id))
// 		node = node->next;

// 	if (node == l->end)
// 		return NULL;

// 	return &(node->key);
// }

int initialize_current_begin(list_t *l){
	if (l->beg->next == l->end)
		return 0;
	l->current = l->beg->next;
	return 1;
}

int initialize_current_end(list_t *l){
	if (l->end->prev == l->beg)
		return 0;
	l->current = l->end->prev;
	return 1;
}

int increment_current(list_t *l){
	if (l->current->next == NULL)
		return 0;
	l->current = l->current->next;
	return 1;
}

void decrement_current(list_t *l){
	l->current = l->current->prev;
	return;
}

entity_t* consult_current(list_t *l){
	return &(l->current->key);
}

int remove_current(list_t *l){
	if (l->current == l->end)
		return 0;
	
	node_t *p = l->current;

	l->current->prev->next = l->current->next;
	l->current->next->prev = l->current->prev;

	l->current = l->current->next;

	l->size--;
	free(p);
	return 1;
}

int current_end(list_t *l){
	return (l->current == l->end);
}