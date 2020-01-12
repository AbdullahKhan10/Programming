// ====== this is in bst.c
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


// Input: ’size’: size of an array
// Output: a pointer of type BStree,
// i.e. a pointer to an allocated memory of BStree_struct type
// Effect: dynamically allocate memory of type BStree_struct
// allocate memory for a Node array of size+1 for member tree_nodes
// allocate memory for an unsigned char array of size+1 for member is_free
// set all entries of is_free to 1
// set member size to ’size’;
BStree bstree_ini(int size) 
{
	BStree b = (BStree_struct*)malloc(sizeof(BStree_struct));
	b->tree_nodes = (Node*)malloc(sizeof(Node)*(size+1));
	b->is_free = (unsigned char*)malloc(sizeof(unsigned char)*(size + 1));

	int i; 

	for (i = 0; i < size + 1; i++)
	{
		b->is_free[i] = '1';
	}

	b->size = size;

	return b;
}
// Input: ’bst’: a binary search tree
// ’key’: a pointer to Key
// ’data’: an integer
// Effect: ’data’ with ’key’ is inserted into ’bst’
// if ’key’ is already in ’bst’, do nothing
void bstree_insert(BStree bst, Key *key, int data) 
{
	bstree_insertion(bst, key, data, 1);
}

// Input: ’bst’: a binary search tree
// ’key’: a pointer to Key
// ’data’: an integer
// 'startindex': the index of which the recursion starts
// Effect: ’data’ with ’key’ is inserted into ’bst’
// if ’key’ is already in ’bst’, do nothing
void bstree_insertion(BStree bst, Key *key, int data, int startindex)
{
	if (bst->is_free[1] == '1')
	{
		bst->tree_nodes[1].key = key;
		bst->tree_nodes[1].data = data;
		bst->is_free[1] = '0';
	}
	else
	{
		if (bst->is_free[startindex] == '0' && key_comp(*bst->tree_nodes[startindex].key, *key) == 0)
		{
			//Duplicate keys 
			return;
		}
		else if (key_comp(*bst->tree_nodes[startindex].key, *key) > 0) 
		{
			if (bst->is_free[startindex*2] == '1')
			{
				bst->tree_nodes[startindex*2].key = key;
				bst->tree_nodes[startindex*2].data = data;
				bst->is_free[startindex*2] = '0';
			}
			else
			{
				bstree_insertion(bst, key, data, startindex*2);
			}
		}
		else if (key_comp(*bst->tree_nodes[startindex].key, *key) < 0)
		{
			if (bst->is_free[(startindex*2)+1] == '1')
			{
				bst->tree_nodes[(startindex*2)+1].key = key;
				bst->tree_nodes[(startindex*2)+1].data = data;
				bst->is_free[(startindex*2)+1] = '0';
			}
			else
			{
				bstree_insertion(bst, key, data, (startindex*2)+1);
			}
		}
	}
}


// Input: ’bst’: a binary search tree
// Effect: print all the nodes in bst using in order traversal
void bstree_traversal(BStree bst) 
{
	inorder_traversal(bst, 1); 
}

// Input: ’bst’: a binary search tree
// 'startindex': an index variable to help find the left and right child of bst
// Effect: print all the nodes in bst using in order traversal
void inorder_traversal(BStree bst, int startindex)
{
	if (bst->is_free[startindex] == '0')
	{
		inorder_traversal(bst, startindex * 2);
		print_node(bst->tree_nodes[startindex]);
		inorder_traversal(bst, ((startindex * 2) + 1));
	}
}

// Input: ’bst’: a binary search tree
// Effect: all memory used by bst are freed
void bstree_free(BStree bst) 
{
	free(bst->is_free);
	free(bst->tree_nodes);
	free(bst);
}