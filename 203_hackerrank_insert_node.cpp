#include <bits/stdc++.h>

// how to compile
// g++ -g -Wall -std=c++11 203_hackerrank_insert_node.cpp -o 203_hackerrank_insert_node

using namespace std;

class SinglyLinkedListNode {
    public:
        int data;
        SinglyLinkedListNode *next;

        SinglyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
        }
};

class SinglyLinkedList {
    public:
        SinglyLinkedListNode *head;
        SinglyLinkedListNode *tail;

        SinglyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int node_data) {
            SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
            }

            this->tail = node;
        }
};

void print_singly_linked_list(SinglyLinkedListNode* node, string sep, ofstream& fout) {
    while (node) {
        fout << node->data;

        node = node->next;

        if (node) {
            fout << sep;
        }
    }
}

void free_singly_linked_list(SinglyLinkedListNode* node) {
    while (node) {
        SinglyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

// Complete the insertNodeAtPosition function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* head, int data, int position) {
    // make a copy of the input head so that we can alter it and return it
    SinglyLinkedListNode* root;
    root = head;

    // Create a new temp node with wanted data to insert later
    SinglyLinkedListNode* temp = new SinglyLinkedListNode(data);

    // We cannot do negative positions
    if(position < 0)
    {
        return NULL;
    }
    // When position is 0, just put the new node at the front and return the linked list with the temp as the head
    else if(position == 0)
    {
        temp->next = head;
        return temp;
    }
    // For when position is important
    else
    {
        // move the head along the linked list until position is met
        while(position - 1 > 0)
        {
            position--;
            head = head->next;
        }

        temp->next = head->next;
        head->next = temp;

        return root;

    }
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    std::ofstream fout ("203_hackerrank_insert_node.txt", std::ofstream::out);

    SinglyLinkedList* llist = new SinglyLinkedList();

    int llist_count;
    cin >> llist_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < llist_count; i++) {
        int llist_item;
        cin >> llist_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        llist->insert_node(llist_item);
    }

    int data;
    cin >> data;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int position;
    cin >> position;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    SinglyLinkedListNode* llist_head = insertNodeAtPosition(llist->head, data, position);

    print_singly_linked_list(llist_head, " ", fout);
    fout << "\n";

    free_singly_linked_list(llist_head);

    fout.close();

    return 0;
}
