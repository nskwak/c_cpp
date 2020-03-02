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
// function: Linked list 
// https://www.geeksforgeeks.org/top-20-linked-list-interview-question/
// 1. Find the middle of a given linked list in C
// 
// 
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
}NODE;

void insert(NODE** head_ref, int dataIn)
{
	NODE* new_node = malloc(sizeof(NODE));
	new_node->data = dataIn;
	new_node->prev = NULL;
	new_node->next = *head_ref;
	if(*head_ref != NULL)
	{
		(*head_ref)->prev = new_node;
	}
	*head_ref = new_node;
}

void append(NODE** head_ref, int dataIn)
{
	NODE* new_node = malloc(sizeof(NODE));
	new_node->data = dataIn;
	if(*head_ref == NULL)
	{
		new_node->prev = NULL;
		new_node->next = *head_ref;
		*head_ref = new_node;
		return;
	}

	NODE* cur = *head_ref;
	new_node->next = NULL;
	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	new_node->prev = cur;
	cur->next = new_node;
}

void deleteNodeNthFromEnd(NODE** head_ref, int nthfromEnd)
{
	NODE* cur = *head_ref;
	NODE* prev;
	int count = 0;
	while(cur->next != NULL)
	{
		cur = cur->next;
		count++;
	}
	cur = *head_ref;
	if(nthfromEnd > count)
	{
		printf("no node to be deleted!\n");
		return;
	}
	count = count - nthfromEnd;
	while((cur->next != NULL) && (count >= 0))
	{
		prev = cur;
		cur = cur->next;
		count--;
	}
	cur->prev->next = cur->next;
	free(cur);
}

void deleteNode(NODE** head_ref, NODE* del) 
{ 
    if (*head_ref == NULL || del == NULL) 
        return; 
    if (*head_ref == del) 
        *head_ref = del->next; 
    if (del->next != NULL) 
        del->next->prev = del->prev; 
    if (del->prev != NULL) 
        del->prev->next = del->next; 
    free(del); 
    return; 
} 

void printlist(NODE* cur)
{
	while(cur != NULL)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

int main()
{
	NODE* head = NULL;
	append(&head, 11); 	printf("append: ");	printlist(head);
	insert(&head, 21); 	printf("insert: ");	printlist(head);
	append(&head, 12); 	printf("append: ");	printlist(head);
	insert(&head, 22); 	printf("insert: ");	printlist(head);
	append(&head, 13); 	printf("append: ");	printlist(head);
	append(&head, 14); 	printf("append: ");	printlist(head);
	append(&head, 15); 	printf("append: ");	printlist(head);
    deleteNode(&head, head); printf("delete 1st node: "); printlist(head);
    deleteNode(&head, head->next->next); printf("delete 3rd node: "); printlist(head);
	append(&head, 16); 	printf("append: ");	printlist(head);
	append(&head, 17); 	printf("append: ");	printlist(head);
    deleteNodeNthFromEnd(&head, 3); printf("delete 3rd node from End: "); printlist(head);
	append(&head, 18); 	printf("append: ");	printlist(head);
	append(&head, 19); 	printf("append: ");	printlist(head);
    deleteNodeNthFromEnd(&head, 3); printf("delete 3rd node from End: "); printlist(head);
	return 0;
}

#endif
