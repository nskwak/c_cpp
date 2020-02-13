#if 1
///////////////////////////////////////////////////////////////////////////////////
// singly linked list 
// insert data at the beginning of node
// append data at the end of node
// update data 
// insertAfter data
// search data
///////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <malloc.h>

struct Node {
    int data;
    struct Node* pointer;
};

// insert, append, delete, update, insertAfter, select(search)

void insert(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->pointer = *head_ref;
    (*head_ref) = new_node;
    printf("insert - new_node=%p, data=%d\n", new_node, new_data);
}

void insertAfter(struct Node* pre_node, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->pointer = pre_node->pointer;
    pre_node->pointer = new_node;
    printf("insertAfter - new_node=%p, data=%d\n", new_node, new_data);
}

void append(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    struct Node* cur = *head_ref;

    new_node->data = new_data;
    new_node->pointer = NULL;

    if(*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    while(cur->pointer != NULL)
    {
        cur = cur->pointer;
    }
    cur->pointer = new_node;
    printf("append - new_node=%p, data=%d\n", new_node, new_data);
}

void delete(struct Node** head_ref, int delete_data)
{
    struct Node* cur = *head_ref;
    struct Node* prev;
    //check if first node has detelet_data or not
    if(cur != NULL && cur->data == delete_data)
    {
        *head_ref = cur->pointer;
        free(cur);
        return;
    }
    //check following node
    while (cur != NULL && cur->data != delete_data)
    {
        prev = cur;
        cur = cur->pointer; 
    }
    //if cur=NULL, there is no matched data to delete
    if (cur == NULL)
        printf("there is no %d to delete!!!!!\n", delete_data);
        return;
    //copy curr->pointer to pre->pointer and delete cur node.
    prev->pointer = cur->pointer;
    free(cur);
    return;
}

void update(struct Node** head_ref, int datatobeupdata, int updatedata)
{
    struct Node* cur = *head_ref;
    struct Node* prev;
    if(cur != NULL && cur->data == datatobeupdata)
    {
        cur->data = updatedata;
        return;
    }
    while (cur != NULL && cur->data != datatobeupdata)
    {
        prev = cur;
        cur = cur->pointer;
    }
    if(cur == NULL)
    {
        printf("there is no %d to update to %d!!!!!\n", datatobeupdata, updatedata);
        return;
    }
    printf("updated %d to %d\n", datatobeupdata, updatedata);
    cur->data = updatedata;
    return;
}
void printlist(struct Node* cur)
{
    while(cur != NULL)
    {
        printf(" %d ", cur->data);
        cur = cur->pointer;
    }
    printf("\n");
}

int main()
{
    struct Node* head = NULL;
    insert(&head, 1);
    append(&head, 33);
    append(&head, 44);
    insert(&head, 2);
    insertAfter(head, 100);
    printlist(head);
    delete(&head, 100);
    printlist(head);
    delete(&head, 2);
    printlist(head);
    delete(&head, 44);
    printlist(head);
    delete(&head, 4);
    printlist(head);
    update(&head, 33, 22);
    printlist(head);

    return(0);
}
///////////////////////////////////////////////////////////////////////////////////
#endif






#if 0
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// 2020/02/11 
// linked list #1
// https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/

// A complete working C program to demonstrate all insertion methods 
// on Linked List 
#include <stdio.h> 
#include <stdlib.h> 

// A linked list node 
struct Node 
{ 
  int data; 
  struct Node *pointer; 
}; 


// Given a reference (pointer to pointer) to the head of a list and  
//   an int, inserts a new node on the front of the list. 
void insert(struct Node** head_ref, int new_data) 
{ 
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
    /* 2. put in the data  */
    new_node->data  = new_data; 
    /* 3. Make pointr of new node as head */
    new_node->pointer = (*head_ref); 
    /* 4. move the head to point to the new node */
    (*head_ref)    = new_node; 
    printf("insert - new_node:%p\n", new_node);
} 

// Given a node prev_node, insert a new node after the given  
//   prev_node 
void insertAfter(struct Node* prev_node, int new_data) 
{ 
    printf("insertAfter - prev_node:%p\n", prev_node);

    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL) 
    { 
      printf("the given previous node cannot be NULL"); 
      return; 
    } 
    /* 2. allocate new node */
    struct Node* new_node =(struct Node*) malloc(sizeof(struct Node)); 
    /* 3. put in the data  */
    new_node->data  = new_data; 
    /* 4. Make pointer of new node as pointer of prev_node */
    new_node->pointer = prev_node->pointer; 
    /* 5. move the pointer of prev_node as new_node */
    prev_node->pointer = new_node; 
} 

// This function prints contents of linked list starting from head 
void printList(struct Node *node) 
{ 
  while (node != NULL) 
  { 
     printf(" %d ", node->data); 
     node = node->pointer; 
  } 
  printf("\n");
} 

// Given a reference (pointer to pointer) to the head 
//   of a list and an int, appends a new node at the end 
void append(struct Node** head_ref, int new_data) 
{ 
    // 1. allocate node
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
    struct Node *cur = *head_ref;  // used in step 5
    // 2. put in the data  
    new_node->data  = new_data; 
    // 3. This new node is going to be the cur node, so make pointer of it as NULL
    new_node->pointer = NULL; 
    // 4. If the Linked List is empty, then make the new node as head 
    if (*head_ref == NULL) 
    { 
       *head_ref = new_node; 
       return; 
    } 
    // 5. Else traverse till the cur node
    while (cur->pointer != NULL) 
        cur = cur->pointer; 
    /* 6. Change the pointer of cur node */
    cur->pointer = new_node; 
    printf("append - new_node:%p\n", new_node);
    return; 
} 

/* Driver program to test above functions*/
int main() 
{ 
  /* Start with the empty list */
  struct Node* head = NULL; 

  // Insert 6.  So linked list becomes 6->NULL 
  append(&head, 6); 
  
  // Insert 7 at the beginning. So linked list becomes 7->6->NULL 
  insert(&head, 7); 
  
  // Insert 1 at the beginning. So linked list becomes 1->7->6->NULL 
  insert(&head, 1); 
  
  // Insert 4 at the end. So linked list becomes 1->7->6->4->NULL 
  append(&head, 4); 
  
  // Insert 8, after 7. So linked list becomes 1->7->8->6->4->NULL 
  //insertAfter(head->pointer, 8);  //1->7->8->6->4->NULL
  insertAfter(head, 8);             //1->8->7->6->4->NULL
  
  printf("\n Created Linked list is: "); 
  printList(head); 
  
  return 0; 
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
#endif