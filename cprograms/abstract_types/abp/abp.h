#ifndef __BINARY_SEARCH_TREE___
#define __BINARY_SEARCH_TREE___

typedef int element_t;

typedef struct node_t{
	struct node_t *father, *left_son, *right_son;
	element_t key;
} node_t;

int initialize_tree(node_t *node);
int childless_tree(node_t *node);
int add_node(node_t *father, node_t *node, element_t key);
int insert_tree(node_t *node, element_t key);
element_t remove_tree(node_t *node);
element_t* search_tree(node_t *node, element_t key);

#endif