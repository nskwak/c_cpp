#include <malloc.h>
#include <unistd.h>
///////////////////////////////////////////////////////////////////////////////////
// function: Singly Linked list Restudy 
// append, insert, 
// add node using rootnode = addnode()

typedef struct Node{
    int data;
    struct Node* next;
}NODE;

void insert(NODE** head_ref, int dataIn)        //KK_ add at the begin
{
    NODE* new_node = malloc(sizeof(NODE));
    new_node->data = dataIn;
    new_node->next = *head_ref;
    *head_ref = new_node;
    printf("[insert] start addr=%p, next addr=%p data=%d\n", *head_ref, new_node->next, dataIn);
}

void append(NODE** head_ref, int dataIn)        //KK_ add at the end
{
    NODE* new_node = malloc(sizeof(NODE));
    NODE* cur = *head_ref;
    new_node->data = dataIn;
    new_node->next = NULL;
    if(cur == NULL)
    {
        //printf("haha\n");
        *head_ref = new_node;
        return;
    }
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new_node;
    printf("[append] start addr=%p, end addr=%p data=%d\n", *head_ref, new_node, dataIn);
}

void printlist(NODE* cur)
{
    NODE* prev;
    printf("======================== printlist =========================\n");
    while(cur != NULL)
    {
        prev = cur;
        printf("%p => %d \n", cur, cur->data);
        cur = cur->next;
    }
    printf("=printlist end prev=%p \n", prev);
}

NODE* addnode(int dataIn)
{
    NODE* new_node = malloc(sizeof(NODE));
    new_node->data = dataIn;
    new_node->next = NULL;
    return new_node;
}

NODE* findendnode(NODE* cur)
{
    NODE* prev;
    while(cur != NULL)
    {
        prev = cur;
        cur = cur->next;
    }
    return prev;
}

int main()
{
    NODE* head = NULL;
    NODE* last_node;
    NODE* rootnode = NULL;

    insert(&head, 10);
    append(&head, 1);
    append(&head, 2);
    insert(&head, 11);
    append(&head, 3);
    append(&head, 4);
    printlist(head);
    last_node = findendnode(head);
    printf("last_node=%p \n", last_node);

    rootnode = addnode(55);
    printf("rootnode=%p => %d \n", rootnode, rootnode->data);
    rootnode->next = addnode(56);
    printf("rootnode=%p => %d \n", rootnode->next, rootnode->next->data);

    last_node->next = rootnode;     //connect two linked list....
    printlist(head);

    append(&head, 7);
    append(&head, 8);
    printlist(head);

    return 0;
}
