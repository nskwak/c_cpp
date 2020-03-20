#include <malloc.h>
#include <unistd.h>
///////////////////////////////////////////////////////////////////////////////////
// function: 141. Linked List Cycle 
// determine if it has a cycle in it. 
// 

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
        printf("[append] start addr=%p,     end addr=%p data=%d\n", *head_ref, new_node, dataIn);
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
    int i = 0;
    printf("======================== printlist =========================\n");
    while(cur != NULL)
    {
        i++;
        prev = cur;
        printf("%p => %d \n", cur, cur->data);
        cur = cur->next;
        if(i == 8)  break;
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

void appendAttach(NODE** head_ref, int nth, int dataIn) //KK_ add data at the end and attach nth pos
{
    NODE* new_node = malloc(sizeof(NODE));
    NODE* cur = *head_ref;
    NODE* nthnode;
    new_node->data = dataIn;
    new_node->next = NULL;
    if(cur == NULL)
    {
        //printf("haha\n");
        printf("[appendAttach] start addr=%p, end addr=%p data=%d\n", *head_ref, new_node, dataIn);
        *head_ref = new_node;
        return;
    }
    int count = 0;
    if(cur->next == NULL)
    {
        nthnode = cur;
    }

    while(cur->next != NULL)
    {
        //printf("***cur = %p\n", cur);
        if(count == nth)
        {
            nthnode = cur;
        }
        cur = cur->next;
        count++;
    }
    cur->next = new_node;
    new_node->next = nthnode;
    printf("[appendAttach] start addr=%p, end addr=%p data=%d, new_node->next=%p\n"
        , *head_ref, new_node, dataIn, new_node->next);
}

int hasCycleOn(NODE* head)
{
    NODE* prev;
    while(head)
    {
        if(head->next == NULL)   return -1;
        head = head->next;
    }
}

int hasCycleO1(NODE* head)
{
    NODE* slow = head;
    NODE* fast = head;
    while(fast)
    {
        //printf("1. slow %d is same as fast %d?\n", slow->data, fast->data);
        if(fast->next == NULL)   return -1;
        //printf("ggaggung1 %d, %d\n", slow->data, fast->data);
        fast = fast->next->next;
        //printf("ggaggung2 %d, %d\n", slow->data, fast->data);
        slow = slow->next;
        //printf("ggaggung3 %d, %d\n", slow->data, fast->data);
        printf("2. slow %d is same as fast %d?\n", slow->data, fast->data);
        if(fast == slow)         return 0;
    }
    return -1;
}

int main()
{
    NODE* head = NULL;
    NODE* last_node;
    NODE* rootnode = NULL;

    #if 1
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);
    append(&head, 6);
    appendAttach(&head, 1, 7);
    #else
    append(&head, 1);
    appendAttach(&head, 0, 2);
    #endif

    printlist(head);

    int result = hasCycleO1(head);
    if(result==0)   printf("Has Cycle\n");
    else            printf("No Cycle\n");

    return 0;
}
