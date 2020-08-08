#include <stdio.h>

#include "abp.h"

int main()
{
	node_t tree;
	initialize_tree(&tree);
	printf("%d\n", childless_tree(&tree));
	insert_tree(&tree, 1);
	printf("%d\n", childless_tree(&tree));
	return 0;
}