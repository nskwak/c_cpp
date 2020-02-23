#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: bit maipulation
// Cracking code page 57, 5.5
// input: 31, 14 -> output: 2
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

#define bit0    0
#define bit1    1
#define bit2    2
#define bit3    3
#define bit4    4
#define bit5    5
#define bit6    6
#define bit7    7

int countXorValue(int in_num)
{
    int count=0;
    while(in_num)
    {
        count += (in_num & 1);
        in_num = (in_num >> 1);
    }
    return count;
}

int swapbit(int in_num)
{
    return ((0xaaaaaaaa & in_num)>>1 | (0x55555555 & in_num)<<1);
}

int main()
{
    int a = 31;
    int b = 14;
    int flag = 0x00;

    flag = flag | (1<<bit1) | (1<<bit3) | (1<<bit5) | (1<<bit7);
    printf("flag = 0x%x , 0x%x\n", flag, flag&0x2);
    printf("0x%x\n", ~0xff);

    if(flag && 0x3)
    {
        printf("flag = 0x%x \n", flag);
    }

    printf("count: %d \n", countXorValue(a^b));

    int c = 0x11111111;
    printf("swapbit of 0x%x = 0x%x\n", c, swapbit(c));

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////
#endif

#if 0   
///////////////////////////////////////////////////////////////////////////////////
// function: bit maipulation
// Cracking code page 58, 5.5
// input: 31, 14 -> output: 2
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int countXorValue(int in_num)
{
    int count=0;
    while(in_num)
    {
        count += (in_num & 1);
        in_num = (in_num >> 1);
    }
    return count;
}

int main()
{
    int a = 31;
    int b = 14;

    printf("count: %d \n", countXorValue(a^b));

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////
#endif

#if 0   
///////////////////////////////////////////////////////////////////////////////////
// function: bit maipulation
// Cracking code page 57, 5.1
// a)  N = 1024 (10000000000),
//     M = 19 (10011),
//     i = 2, j = 6
//     Output : 1100 (1000'10011'00)
// b)  N = 1201 (10010110001)
//     M = 8 (1000)
//     i = 3, j = 6
//     Output: 1217 (1001'1000'001)
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

void bin(int in_num)
{
    if(in_num > 1)
        bin(in_num/2);
    printf("%d ", in_num%2);
}

int main()
{
    int N = 1201;
    int M = 8;
    int i = 3;
    int j = 6;
    int captured_mask, clear_mask;

    printf("N = %d -> ", N);
    bin(N); printf("\n");
    captured_mask = (1 << i) - 1;
    captured_mask &= N;
    printf("captured_mask = %d \n", captured_mask);
    clear_mask = -1 << (j+1);
    printf("clear_mask = %d \n", clear_mask);
    ///////////////////////////////////////////////////////////
    N &= clear_mask;
    printf("%d, ", N); bin(N); printf("\n");

    N |= (M<<i);
    printf("%d, ", N); bin(N); printf("\n");

    N |= captured_mask;
    printf("%d, ", N); bin(N); printf("\n");

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////
#endif

#if 0   
///////////////////////////////////////////////////////////////////////////////////
// function: Linked list Restudy #2
// create node, add new data
//
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

typedef struct Node 
{
    int data;
    struct Node* next;
}NODE;

// insert data at the beginning
void insert(NODE** head_ref, int datain)
{
    NODE* temp = malloc(sizeof(NODE));
    temp->data = datain;
    temp->next = *head_ref;
    *head_ref = temp;
    //printf("insert: addr = %p\n", temp);
}

// append data at the end
void append(NODE** head_ref, int datain)
{
    NODE* temp = malloc(sizeof(NODE));
    NODE* cur = *head_ref;

    temp->data = datain;
    temp->next = NULL;

    while(*head_ref == NULL)
    {
        *head_ref = temp;
        return;
    }
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = temp;
    //printf("append: addr = %p\n", temp);
}

// insert after nthnode
void insertafternode(NODE** head_ref, int nth, int datain)
{
    NODE* temp = malloc(sizeof(NODE));
    NODE* cur = *head_ref;
    NODE* prev;
    int i = 0;

    while((cur != NULL) && (i != nth))
    {
        prev = cur;
        cur = cur->next;
        i++;
    }
    if(cur==NULL)
    {
        printf("NO data can be inserted!!\n");
        return;
    }
    temp->data = datain;
    temp->next = cur;
    prev->next = temp;
    //*head_ref = temp;
    //printf("insert: addr = %p\n", temp);
}

// delete nthnode
void deleteNthNodeFromEnd(NODE** head_ref, int nth)
{
    NODE* temp = malloc(sizeof(NODE));
    NODE* cur = *head_ref;
    NODE* prev;
    int i = 0;

    while(cur != NULL)
    {
        cur = cur->next;
        i++;
    }
    if(nth >= i)
    {
        printf("NO data can be deleted!!\n");
        return;
    }
    cur = *head_ref;
    printf("i=%d, nth=%d\n", i, nth);
    //i = i - nth;
    while(i > nth)
    {
        printf("i=%d\n", i);
        prev = cur;
        cur = cur->next;
        i--;
    }
    prev->next = cur->next;
    free(cur);
}

void delete(NODE** head_ref, int deletedata)
{
    NODE* cur = *head_ref;
    NODE* prev;
    
    while((cur != NULL) && (cur->data != deletedata))
    {
        prev = cur;
        cur = cur->next;
    }
    if(cur->next == NULL)
    {
        printf("NO data can be deleted!!\n");
        return;
    }
    prev->next = cur->next;
    free(cur);
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
    insert(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    printf("display list added              : "); printlist(head);
    delete(&head, 2);
    printf("delete '2'                      : "); printlist(head);
    append(&head, 5);
    append(&head, 6);
    printf("add 5, 6                        : "); printlist(head);
    insertafternode(&head, 4, 99);
    printf("insert 99 after 4th node        : "); printlist(head);
    deleteNthNodeFromEnd(&head, 4);
    printf("delete 4th node from the end    : "); printlist(head);
}
#endif

#if 0   
///////////////////////////////////////////////////////////////////////////////////
// function: Linked list Restudy #1
// create node, add new data
//
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

typedef struct Node 
{
    int data;
    struct Node* left;
    struct Node* right;
}NODE;

NODE *newnode(int datain)
{
    NODE* temp = malloc(sizeof(NODE));
    temp->data = datain;
    temp->left = temp->right = NULL;
    return(temp);
}

void printlist(NODE* cur)
{
    if(cur == NULL)
        return;
    printf("%d ", cur->data);
    printlist(cur->left);
    printlist(cur->right);
}

int main()
{
    NODE* root = NULL;
    root = newnode(1);
    root->left = newnode(2);
    root->right = newnode(3);
    root->right->left = newnode(4);
    root->right->right = newnode(5);
    printlist(root);
}
#endif



#if 0   //KK_ unsolved yet,  need to solved.
///////////////////////////////////////////////////////////////////////////////////
// function: LeetCode:Easy 1. Two Sum with hash table
// Input:  [2, 3, 7, 11, 13], target=9
// Output: [0, 2]
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int main()
{
    int in_num[] = {2, 3, 7, 11, 13};
    int target = 9;
    int i, k;
    int loopcnt = sizeof(in_num)/sizeof(int);
    int hashTarr[256] = {};

    printf("%d \n", loopcnt);

    for(int i=0; i<loopcnt; i++)
    {
        for(int k=1; k<loopcnt; k++)
        {

            if((in_num[i] + in_num[k]) == target)
            {
                printf("%d + %d = %d\n", in_num[i], in_num[k], target);
                break;
            }
        }
        hashTarr[i] = target - in_num[i];
    }
}
#endif

#if 0   //KK_ not start yet
///////////////////////////////////////////////////////////////////////////////////
// function: just double check pointer
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int main()
{
    int i;
    int *p;
    char a, b;

    i = 3;
    *p = 4;
    a = 'a';
    b = 'b';

    printf("i = %d\n", i);  // print i value
    printf("i = %p\n", &i); // print i address
    printf("p = %d\n", *p); // print p value
    printf("p = %p\n", &p); // print p address
    printf("a = %c\n", a);  // print a value
    printf("a = %p\n", &a);  // print a address
    printf("b valu = %c\n", b);  // print a value
    printf("b addr = %p\n", &b);  // print a address

}
#endif



#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// function: swap array
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int main()
{
    char str[] = {'a', 'b', 'c', 'd', 'c'};
    int i;
    char arr[256] = {};
    char result[256] = {};
    int k=0;

    int loopcnt = sizeof(str)/sizeof(char);
    printf("%d \n", loopcnt);

    for(i=0; i<(loopcnt/2); i++)
    {
        k = str[i];
        str[i] = str[loopcnt-1-i];
        str[loopcnt - 1 - i] = k;
        printf("%d: str[%d]:%c  str[%d]:%c\n", i, i, str[i], loopcnt - 1 - i, str[loopcnt - 1 - i]);
    }

    //check result
    for(i=0; i<loopcnt; i++)
    {
        printf("%c", str[i]);
    }
}
#endif

#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// function: find second duplicate with hash table
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int main()
{
    char str[] = {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};
    int i;
    char arr[256] = {};
    char result[256] = {};
    int k=0;

    for(i=0; str[i]; i++)
    {
        arr[str[i]]++;
        if(arr[str[i]] == 2)
        {
            printf("%c\n", str[i]);
            result[k++] = str[i];
            if(k==2)
            {
                printf("%c ", result[1]);
                break;
            }
        }
    }
}
#endif

#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// function: find first duplicate with hash table
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int main()
{
    int str[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'd'};
    int i;
    int arr[256] = {};

    for(i=0; str[i]; i++)
    {
        arr[str[i]]++;
        if(arr[str[i]] == 2)
        {
            printf("%c\n", str[i]);
            break;
        }
    }
}
#endif


#if 0   //KK_ this is too hard, will study later
///////////////////////////////////////////////////////////////////////////////////
// function: 316. Remove Duplicate Letters by using hash table
// Input: "bcabc" -> Output: "abc"
// Input: "cbacdcbc" -> Output: "acdb"
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int main()
{
    char str[] = {"bcabc"};
    int i;
    char arr[256] = {};
    char result[256] = {};
    int k=0;

    for(i=0; str[i]; i++)
    {
        arr[str[i]]++;
        if(arr[str[i]] == 1)
        {
            printf("%c\n", str[i]);
            result[k++] = str[i];
        }
    }

    //print output
    printf("input  = %s\noutput = ", str);
    for(i=0;i<k;i++)
    {
        printf("%c", result[i]);
    }
    printf("\n");
}
#endif


#if 0   //KK_ resolved, this is not very hard.
///////////////////////////////////////////////////////////////////////////////////
// function: 316. Remove Duplicate Letters by using hash table for string input
// Input: "bcabc" -> Output: "bca"
// Input: "cbacdcbc" -> Output: "cbad"
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int main()
{
    char str[] = {"bcabc"};
    int i;
    char arr[256] = {};
    char result[256] = {};
    int k=0;

    for(i=0; str[i]; i++)
    {
        arr[str[i]]++;
        if(arr[str[i]] == 1)
        {
            printf("%c\n", str[i]);
            result[k++] = str[i];
        }
    }
    printf("input  = %s\noutput = ", str);
    for(i=0;i<k;i++)
    {
        printf("%c", result[i]);
    }
    printf("\n");
}
#endif

#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// function: delete duplicate with hash table
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int main()
{
    char str[] = {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};
    int i;
    char arr[256] = {};
    char result[256] = {};
    int k=0;

    for(i=0; str[i]; i++)
    {
        arr[str[i]]++;
        if(arr[str[i]] == 1)
        {
            printf("%c\n", str[i]);
            result[k++] = str[i];
            //break;
        }
    }
    for(i=0;i<k;i++)
    {
        printf("%c ", result[i]);
    }
}
#endif

///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
// after meeting with SM Kang, 2/15/2020
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////


#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// function: LeetCode:Easy 26. Remove Duplicates from Sorted Array
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int removeduplicate (int* number)
{
    int length;
    length = sizeof(number);
    return length;
}

int main()
{
    int result;
    int num[] = {0,0,1,1,1,2,2,3,3,4};
    //int num[] = {15, 50, 34, 20, 10, 79, 100};
    int a = sizeof(num);
    int b = sizeof(int);
    printf("size of num[] is %d / %d = %d\n", a, b, a/b);
    //result = removeduplicate(num);
}
#endif


#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// function: LeetCode:Easy 509. Fibonacci Number, recursion, recursive calling
#include <stdio.h>
#include <malloc.h>

int fibonacci (int number)
{
    int val;
    if (number == 0)
        return 0;
    else if(number == 1)
        return 1;
    else
    {
        val = fibonacci(number - 1) + fibonacci(number - 2);
    }
}

int main()
{
    int result, num = 7;
    result = fibonacci(num);
    printf("fibonacci of %d is %d\n", num, result);
}
#endif


#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// leetcode 19. Remove Nth Node From End of List
// function: Linked List - leetcode 19. Remove Nth Node From End of List
// Given linked list: 1->2->3->4->5, and n = 2.
// After removing the second node from the end, the linked list becomes 1->2->3->5.

#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node* next;
}NODE;

void insert(NODE** head_ref, int new_data)
{
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
    //printf("insert - new_node=%p, data=%c\n", new_node, c);
}

void append(NODE** head_ref, int new_data)
{
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    NODE* cur = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if(*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new_node;
    printf("append - new_node=%p, data=%d\n", new_node, new_data);
}

void printlist(NODE* cur)
{
    while(cur != NULL)
    {
        printf("%d", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void deletenthnode(NODE** head_ref, int nth) 
{
    NODE* cur = *head_ref;
    int i = 1;
    while (cur != NULL) {
        cur = cur->next;
        i++;
        printf("%d -> %d\n", i, cur->data);
    }
    int totalnode = i - nth;
    NODE* again = *head_ref;
    i = 1;
    while (again != NULL) {
        again = again->next;
        i++;
        if (i == totalnode)
        {
            printf("%d -> %d\n", i, again->data);
            break;
        }
    }
}

int main()
{
    NODE* head = NULL;
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);
    printlist(head);

    deletenthnode(&head, 2);
    printlist(head);
    
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////
#endif

#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// function: Kang SM - Finding all paths through a 4x4 grid
//https://stackoverflow.com/questions/19889079/finding-all-paths-through-a-4x4-grid
#endif


#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// function: Kang SM - Heap’s Algorithm for generating permutations
//https://www.geeksforgeeks.org/heaps-algorithm-for-generating-permutations/
#endif

#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// function: Kang SM, load float data
// 
#include <stdio.h>

typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned int uint16_t;
typedef int int16_t;
typedef float FLOAT;

void load_data(uint16_t data)
{
    printf("%f\n", data);
}

int main()
{
    printf("%d \n", sizeof(uint8_t));
    printf("%d \n", sizeof(int8_t));
    printf("%d \n", sizeof(uint16_t));
    printf("%d \n", sizeof(int16_t));
    printf("%d \n", sizeof(FLOAT));

    FLOAT RPM = 1.5;
    printf("%f\n", RPM);
    int *input;
    input = (uint16_t *)(&RPM);

    load_data(input);
}
#endif


#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// function: Kang SM, char i = 256
#include <stdio.h>
typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned int uint16_t;
typedef int int16_t;

int main()
{
    //printf("%d \n", sizeof(uint8_t));
    //printf("%d \n", sizeof(int8_t));
    //printf("%d \n", sizeof(uint16_t));
    //printf("%d \n", sizeof(int16_t));

    for (uint8_t i=0; i<256; i++)
    {
        printf("%d, a\n", i);
    }
}
#endif

#if 0   //KK_ 
///////////////////////////////////////////////////////////////////////////////////
// Cracking the Coding Interview | Data Structure
// Chapter 2. Linked List - remove duplicate nodes.
// function: linkedlist, remove duplicate nodes.
#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
    char ch;
    struct Node* next;
}NODE;

void insert(NODE** head_ref, char c)
{
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    new_node->ch = c;
    new_node->next = *head_ref;
    *head_ref = new_node;
    //printf("insert - new_node=%p, data=%c\n", new_node, c);
}

void append(NODE** head_ref, char c)
{
    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    NODE* cur = *head_ref;

    new_node->ch = c;
    new_node->next = NULL;

    if(*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new_node;
    printf("append - new_node=%p, data=%c\n", new_node, c);
}

void printlist(NODE* cur)
{
    while(cur != NULL)
    {
        printf("%c", cur->ch);
        cur = cur->next;
    }
    printf("\n");
}

void deleteDuplicates(NODE** head_ref) 
{
    NODE* cur = *head_ref;
    while (cur != NULL) {
        // Remove all future nodes that have the same value 
        NODE* runner = cur;
        while (runner->next != NULL) 
        {
            if (runner->next->ch == cur->ch) 
            {
                runner->next = runner->next->next;
            } 
            else 
            {
                runner = runner->next;
            }
        }
        cur = cur->next;
    }
}

int main()
{
    NODE* head = NULL;
    insert(&head, 'F');
    append(&head, 'O');
    append(&head, 'L');
    append(&head, 'L');
    append(&head, 'O');
    append(&head, 'W');
    append(&head, ' ');
    append(&head, 'U');
    append(&head, 'P');
    printlist(head);

    deleteDuplicates(&head);
    printlist(head);
    
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////
#endif

#if 0    
///////////////////////////////////////////////////////////////////////////////////
// function: linkedlist ***************** typedef ******************
#include <stdio.h>
#include <malloc.h>

typedef struct Node {
    int data;
    struct Node* pointer;
} NODE;

void insert(NODE** head_ref, int new_data)
{
    NODE* new_node = (NODE*) malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->pointer = *head_ref;
    (*head_ref) = new_node;
    printf("insert - new_node=%p, data=%d\n", new_node, new_data);
}

void printlist(NODE* cur)
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
    NODE* head = NULL;
    insert(&head, 1);
    printlist(head);
    return(0);
}
///////////////////////////////////////////////////////////////////////////////////
#endif   //KK_ linkedlist typedef

#if 0   // singly linked list
///////////////////////////////////////////////////////////////////////////////////
// function: singly linked list 
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
    printf("A. cur data = %d, cur node: %p, next:%p, -> prev data=%d, %p, next:%p\n", cur->data, cur, cur->pointer, prev->data, prev, prev->pointer);
    //if cur=NULL, there is no matched data to delete
    if (cur == NULL)
    {
        printf("there is no %d to delete!!!!!\n", delete_data);
        return;
    }
    //copy curr->pointer to pre->pointer and delete cur node.
    prev->pointer = cur->pointer;
    printf("B. cur data = %d, cur node: %p, next:%p, -> prev data=%d, %p, next:%p\n", cur->data, cur, cur->pointer, prev->data, prev, prev->pointer);
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
    printf("1. ");     printlist(head);
    insertAfter(head, 100);
    printf("2. ");     printlist(head);
    delete(&head, 100);
    printf("3. ");     printlist(head);
    delete(&head, 2);
    printf("4. ");     printlist(head);
    delete(&head, 44);
    printf("5. ");     printlist(head);
    delete(&head, 4);
    printf("6. ");     printlist(head);
    update(&head, 33, 22);
    printlist(head);

    return(0);
}
///////////////////////////////////////////////////////////////////////////////////
#endif  // singly linked list

#if 0
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// 2020/02/11 
// function: linked list #1
// https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
// insert(at beginning), append(at the end), insertafter(insert after node), printlist

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