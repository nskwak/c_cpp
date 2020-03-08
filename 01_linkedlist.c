#if 1
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
///////////////////////////////////////////////////////////////////////////////////
// function: Linked list Restudy #2
// insert(at begin), append(at end), insertafter(after nth), delete(nth or value)
//

typedef struct Node{
    int data;
    struct Node* next;
}NODE;

void deletenthFrEnd(NODE** head_ref, int nth)
{
    NODE* new_node = malloc(sizeof(NODE));
    NODE* prev;
    NODE* cur = *head_ref;

    int totalNode = 0;
    while(cur != NULL)
    {
        cur = cur->next;
        totalNode++;
    }
    cur = *head_ref;
    totalNode = totalNode - nth - 1;
    while(totalNode >= 0)
    {
        prev = cur;
        cur = cur->next;
        totalNode--;
    }

    prev->next = cur->next;
    free(cur);
}


void deleteVal(NODE** head_ref, int val)
{
    NODE* prev;
    NODE* cur = *head_ref;

    while((cur != NULL) && (cur->data!=val))
    {
        prev = cur;
        cur = cur->next;
    }
    if(cur == NULL)
    {
        printf("No data can be deteted!!\n");
        return;
    }
    prev->next = cur->next;
    free(cur);
}

void deletenth(NODE** head_ref, int nth)
{
    NODE* prev;
    NODE* cur = *head_ref;

    while((cur != NULL) && (nth >0))
    {
        prev = cur;
        cur = cur->next;
        nth--;
    }
    if(cur == NULL)
    {
        printf("No data can be deteted!!\n");
        return;
    }
    prev->next = cur->next;
    free(cur);
}

void insertafter(NODE** head_ref, int nth, int dataIn)
{
    NODE* new_node = malloc(sizeof(NODE));
    NODE* prev;
    NODE* cur = *head_ref;

    while((cur != NULL) && (nth >=0))
    {
        prev = cur;
        cur = cur->next;
        nth--;
    }
    new_node->data = dataIn;
    new_node->next = cur;
    prev->next = new_node;
}

void insert(NODE** head_ref, int dataIn)
{
    NODE* new_node = malloc(sizeof(NODE));
    new_node->data = dataIn;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void append(NODE** head_ref, int dataIn)
{
    NODE* new_node = malloc(sizeof(NODE));
    NODE* cur = *head_ref;
    new_node->data = dataIn;
    new_node->next = NULL;

    if(cur == NULL)
    {
        *head_ref = new_node;
        return;
    }
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new_node;
}

void printlist(NODE* head_ref)
{
    while(head_ref != NULL)
    {
        printf("%d ", head_ref->data);
        head_ref = head_ref->next;
    }
    printf("\n");
}

int main()
{
    NODE* head=NULL;
    int invar, invar1;
    append(&head, 111);
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    printlist(head);
    deletenth(&head, 2);
    printf("delete 2nd val: ");         printlist(head);
    append(&head, 6);
    append(&head, 7);
    append(&head, 8);
    append(&head, 9);
    printlist(head);
    deleteVal(&head, 7);
    printf("delete val=7 : ");            printlist(head);
    insertafter(&head, 2, 88);
    printlist(head);
    invar = 2;
    deletenthFrEnd(&head, invar);
    printf("delete %dth node from the end : ", invar);            printlist(head);
    return 0;
}

#endif