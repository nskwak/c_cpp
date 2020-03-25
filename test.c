#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

typedef struct SinglyLinkedListNode SinglyLinkedListNode;
typedef struct SinglyLinkedList SinglyLinkedList;

struct SinglyLinkedListNode {
    int data;
    SinglyLinkedListNode* next;
};

struct SinglyLinkedList {
    SinglyLinkedListNode* head;
    SinglyLinkedListNode* tail;
};

void print_singly_linked_list(SinglyLinkedListNode* node, char* sep, FILE* fptr) {
    int i = 0;  //KK_
    printf("KK_ print_singly_linked_list: node:%p\n", node);
    while (node) {
        printf("KK_ %d => %p  \n", node->data, node);
        fprintf(fptr, "%d", node->data);

        node = node->next;

        if (node) {
            fprintf(fptr, "%s", sep);
        }
        i++;    //KK_
        if(i > 6)   break;  //KK_
    }
    printf("END!!\n");
}

void free_singly_linked_list(SinglyLinkedListNode* node) {
    printf("KK_free_singly_linked_list \n");
    while (node) {
        SinglyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

SinglyLinkedListNode* create_singly_linked_list_node(int node_data) {
    SinglyLinkedListNode* node = malloc(sizeof(SinglyLinkedListNode));

    node->data = node_data;
    node->next = NULL;
    printf("create_singly_linked_list_node:%p, data:%d \n", node, node_data);
    return node;
}

void insert_node_into_singly_linked_list(SinglyLinkedList** singly_linked_list, int node_data) {
    SinglyLinkedListNode* node = create_singly_linked_list_node(node_data);

    if (!(*singly_linked_list)->head) {
        (*singly_linked_list)->head = node;
    } else {
        (*singly_linked_list)->tail->next = node;
    }
    printf("KK_insert_node_into_singly_linked_list => node_data:%d => addnoder:%p ", node_data, node);
    printf("(*singly_linked_list)->head:%p (*singly_linked_list)->tail:%p \n", (*singly_linked_list)->head, (*singly_linked_list)->tail);
    (*singly_linked_list)->tail = node;
}

SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* head, int data, int position) {
    //KK_
    SinglyLinkedListNode* new_node = malloc(sizeof(SinglyLinkedListNode));
    SinglyLinkedListNode* cur = head;
    SinglyLinkedListNode* nthnode;
    new_node->data = data;
    new_node->next = NULL;
    if(cur == NULL)
    {
        head = new_node;
        return head;
    }
    int count = 0;
    if(cur->next == NULL)
    {
        nthnode = cur;
    }
    while(cur->next != NULL)
    {
        if(count == (position-1))
        {
            nthnode = cur->next;
            break;
        }
        printf("%p ", cur);
        cur = cur->next;
        count++;
    }
    printf("\n");
    cur->next = new_node;
    new_node->next = nthnode;
    printf("KK_insertNodeAtPosition => data:%d => new_node:%p cur:%p, head:%p ", data, new_node, cur, head);
    printf("nthnode:%p\n", nthnode);    //KK_
    return head;
}

int main()
{
    //KK_FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    FILE* fptr = fopen("a.txt", "w");

    SinglyLinkedList* llist = malloc(sizeof(SinglyLinkedList));
    llist->head = NULL;
    llist->tail = NULL;

    char* llist_count_endptr;
    char* llist_count_str = readline();
    int llist_count = strtol(llist_count_str, &llist_count_endptr, 10);

    printf("input[001] %d\n", llist_count);

    if (llist_count_endptr == llist_count_str || *llist_count_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int i = 0; i < llist_count; i++) {
        char* llist_item_endptr;
        char* llist_item_str = readline();
        int llist_item = strtol(llist_item_str, &llist_item_endptr, 10);    //convert string to long integer

        if (llist_item_endptr == llist_item_str || *llist_item_endptr != '\0') { exit(EXIT_FAILURE); }

        insert_node_into_singly_linked_list(&llist, llist_item);
    }

    char* data_endptr;
    char* data_str = readline();
    int data = strtol(data_str, &data_endptr, 10);

    if (data_endptr == data_str || *data_endptr != '\0') { exit(EXIT_FAILURE); }

    char* position_endptr;
    char* position_str = readline();
    int position = strtol(position_str, &position_endptr, 10);

    if (position_endptr == position_str || *position_endptr != '\0') { exit(EXIT_FAILURE); }

    SinglyLinkedListNode* llist_head = insertNodeAtPosition(llist->head, data, position);   //KK_ 
    //KK_SinglyLinkedListNode* llist_head = llist->head; //KK_ added for test
    char *sep = " ";

    print_singly_linked_list(llist_head, sep, fptr);    //KK_ 
    fprintf(fptr, "\n%s", "KK_000001\n");
    fprintf(fptr, "%s", "KK_000002\n");
    fprintf(fptr, "%s", "\n");

    free_singly_linked_list(llist_head);          //KK_ 

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}
