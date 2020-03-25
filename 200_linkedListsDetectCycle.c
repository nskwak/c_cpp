#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
///////////////////////////////////////////////////////////////////////////////////
// Hackerrank.com: Linked Lists: Detect a Cycle
//  
/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.
A Node is defined as: 
    struct Node {
        int data;
        struct Node* next;
    }
*/

struct Node {
    int data;
    struct Node* next;
};

bool has_cycle(struct Node* head) {
    // Complete this function
    // Do not write the main method
    struct Node* slow = head;
    struct Node* fast = head;
    while(fast)
    {
        if(fast->next == NULL)   return 0;
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)         return 1;
    }
    return 0;
}