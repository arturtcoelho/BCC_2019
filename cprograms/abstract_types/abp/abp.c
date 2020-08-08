#include <stdio.h>
#include <stdlib.h>

#include "abp.h"

int initialize_tree(node_t *node){
	node->father = NULL;
	node->left_son = NULL;
	node->right_son = NULL;
	return 1;
}

int childless_tree(node_t *node){
	if (node->left_son == NULL && node->right_son == NULL)
		return 1;
	return 0;
}

int add_node(node_t *father, node_t *node, element_t key){
	node = malloc(sizeof(element_t));
	if (node == NULL){
		printf("cagou no pau\n");
		exit(1);
	}
	node->key = key;
	node->left_son = NULL;
	node->right_son = NULL;
	node->father = father;
	return 1;
}

int insert_tree(node_t *node, element_t key){
	if (childless_tree(node)){
		return add_node(node, node->left_son, key);
	}
	printf("a\n");
	return 1;
}

element_t remove_tree(node_t *node){
	return 1;
}

element_t* search_tree(node_t *node, element_t key){
	return NULL;
}