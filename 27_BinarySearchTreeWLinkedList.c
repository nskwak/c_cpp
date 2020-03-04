#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "string.h"
#include "malloc.h"
#include "unistd.h"
#include "math.h"
#include "time.h"
#include "signal.h"
#include "dirent.h"	
#include "stdarg.h"


#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: BST  
// Jon's BST/BT
// Look up (Non-recursive)
// Find number by Binary Search Tree for Linked List (No recursive, Recursive)
// 
typedef struct Node 
{
	int val;
	struct Node* left;
	struct Node* right;
}NODE;

void findnode(NODE* cur, int findVal)
{
	printf("[findnode] - Addr of cur: %p\n", cur);
	for(;;)
	{
		if(cur == NULL)	
		{
			printf("No cur\n");
			break;
		}
		else if(cur->val == findVal)	
		{
			printf("find %d !!\n", findVal);
			break;
		}
		else if(cur->val > findVal)		
		{
			printf("cur->val(%d) > findVal(%d)\n", cur->val, findVal);
			cur = cur->left;
		}			
		else 
		{
			printf("cur->val(%d) < findVal(%d)\n", cur->val, findVal);
			cur = cur->right;	
		}
	}
}

void findnodeWRecursive(NODE* cur, int findVal)
{
	printf("[findnodeWRecursive] - Addr of cur: %p\n", cur);
	for(;;)
	{
		if(cur == NULL)	
		{
			printf("No cur\n");
			break;
		}
		else if(cur->val > findVal)		
		{
			printf("cur->val(%d) > findVal(%d)\n", cur->val, findVal);
			findnodeWRecursive(cur->left, findVal);
		}			
		else if(cur->val < findVal)
		{
			printf("cur->val(%d) < findVal(%d)\n", cur->val, findVal);
			findnodeWRecursive(cur->right, findVal);	
		}
		else	
		{
			printf("find %d !!\n", findVal);
			break;
		}
	}
}

NODE* addNode(int dataIn)
{
	NODE* new_node = malloc(sizeof(NODE));
	new_node->val = dataIn;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

int main()
{
	int arrayInpit[] = {1,3,5,7,9,13,25,27,35};
	NODE* rootnode = NULL;
	printf("[main] - sizeof(NODE): %d, sizeof(int): %d\n", (int)(sizeof(NODE)), (int)(sizeof(int)));
	printf("[main] - 1. Addr of rootnode: %p\n", rootnode);

	rootnode = addNode(4);
	printf("[main] - 2. Addr of rootnode: %p, rootnode->val: %d\n", rootnode, rootnode->val);
	rootnode->left = addNode(2);
	printf("[main] - 3. Addr of rootnode: %p(%d), %p(%d)\n", rootnode, rootnode->val, rootnode->left, rootnode->left->val);
	rootnode->right = addNode(6);
	printf("[main] - 4. Addr of rootnode: %p(%d), %p(%d)\n", rootnode, rootnode->val, rootnode->right, rootnode->right->val);
	rootnode->left->left = addNode(1);
	printf("[main] - 5. Addr of rootnode: %p(%d), %p(%d)\n", rootnode, rootnode->val, rootnode->left->left, rootnode->left->left->val);
	rootnode->left->right = addNode(3);
	rootnode->right->left = addNode(5);
	rootnode->right->right = addNode(7);
	printf("[main] - 6. Addr of rootnode: %p\n", rootnode);
	findnode(rootnode, 4);
	findnodeWRecursive(rootnode, 4);
}
#endif