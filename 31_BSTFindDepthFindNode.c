#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: BFS (Breadth-First Search), Bina  
// Jon's BFS BT, DFS BT
// BST - find_height, find_depth
typedef struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
}NODE;

int max(int a, int b);
int min(int a, int b);
NODE* AddNode(int dataIn);
NODE* FindNode(NODE* cur, int key);
int FindDepth(NODE* cur);

int main()
{
	NODE* root = NULL;

	root = AddNode(4);
	root->left = AddNode(2);
	root->right = AddNode(6);
	root->left->left = AddNode(1);
	root->left->right = AddNode(3);
	root->right->left = AddNode(5);
	root->right->right = AddNode(7);
	//printf("%d ", root->left->data);
	FindNode(root, 3);
	printf("=============================================\n");
	int dePth = FindDepth(root);
	printf("findDepth = %d\n", dePth);

	dePth = FindDepth(root->right);
	printf("findDepth = %d\n", dePth);

	printf("[main] - max = %d\n", max(4,3));

	return 0;
}

NODE* AddNode(int dataIn)
{
	NODE* new_node = malloc(sizeof(NODE));
	new_node->data = dataIn;
	new_node->left = NULL;
	new_node->right = NULL;
}

int max(int a, int b)
{
	printf("max %d, %d \n", a, b);
	return (a > b) ? a : b;
}

int min(int a, int b)
{
	printf("max %d, %d \n", a, b);
	return (a > b) ? b : a;
}

NODE* FindNode(NODE* cur, int key)
{
	for(;;)
	{
		if(cur == NULL)			break;
		else if(cur->data == key)	
		{
			printf("found!! %d\n", key);	
			break;
		}
		else if(cur->data > key) cur = cur->left;
		else cur = cur->right;
	}
	return cur;
}

int FindDepth(NODE* cur)
{
	int left_h, right_h;
	if(cur == NULL) return 0;
	if(cur->left)
	{
		printf("cur->left:  %d \n", cur->left->data);
		left_h = FindDepth(cur->left);
		printf("cur->left: left_h %d \n", left_h);
	}
	if(cur->right)
	{
		printf("cur->right: %d \n", cur->right->data);
		right_h = FindDepth(cur->right);
		printf("cur->right: right_h %d \n", right_h);
	}
	return (max(left_h, right_h) + 1);
}


#endif