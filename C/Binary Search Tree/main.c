// ====== this is a sample main program
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_LEN 80

#include <stdio.h>
#include "bst.h"
#include "data.h"

int main(void) {

	//BStree bs;
	//bs = bstree_ini(1000);
	//bstree_insert(bs, key_construct("Once", 1), 11);
	//bstree_insert(bs, key_construct("Upon", 22), 2);
	//bstree_insert(bs, key_construct("a", 3), 33);
	//bstree_insert(bs, key_construct("Time", 4), 44);
	//bstree_insert(bs, key_construct("is", 5), 55);
	//bstree_insert(bs, key_construct("filmed", 6), 66);
	//bstree_insert(bs, key_construct("in", 7), 77);
	//bstree_insert(bs, key_construct("Vancouver", 8), 88);
	//bstree_insert(bs, key_construct("!", 99), 9);
	//bstree_insert(bs, key_construct("Once", 5), 50);
	//bstree_insert(bs, key_construct("Once", 1), 10);
	//bstree_traversal(bs);
	//bstree_free(bs);

	BStree bst;
	int bst_size;
	char key_name[MAX_STRING_LEN];
	char key_id;
	int data;
	int counter;
	
	printf("Welcome to the binary tree insertion and print program!!");

	printf("\nEnter an integer number of the size of the binary tree: ");
	scanf("%d", &bst_size);
	bst = bstree_ini(bst_size);
	printf("Binary search tree of size %d is initialized!\n", bst_size);

	printf("\nHow many items would you like to insert into the tree: ");
	scanf("%d", &counter);

	while (counter >= bst_size)
	{
		printf("\nThe number of insertions cannot be bigger than the size of your tree (Re-enter a smaller number): ");
		scanf("%d", &counter);
	}

	int i;

	for (i = 0; i < counter; i++)
	{
		printf("\nPlease enter a key name: ");
		scanf("%s", key_name);

		printf("Please enter a key id (This is a number): ");
		scanf("%d", &key_id);

		printf("Please enter the ID (This is a number): ");
		scanf("%d", &data);

		bstree_insert(bst, key_construct(key_name, key_id), data);
		printf("Your item was inserted into the tree!\n");
	}

	printf("\nHere is the traversal of the tree you created: \n\n");

	bstree_traversal(bst);
	bstree_free(bst);

	return 0;
}
