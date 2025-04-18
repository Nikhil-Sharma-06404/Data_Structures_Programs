#include <stdio.h>
#include <stdlib.h>
                   
// Define a structure for a node in the priority queue
struct Node {
    int data;
    int priority;
    struct Node* next;
};

// Define a structure for the master list
struct MasterList {
    struct Node* priorityList;
};

// Function to create a new node with given data and priority
struct Node* createNode(int data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Function to insert an element into the priority queue
void insert(struct MasterList* masterList, int data, int priority) {
    struct Node* newNode = createNode(data, priority);

    // If the master list is empty or the new node has higher priority than the head of the list
    if (masterList->priorityList == NULL || priority < masterList->priorityList->priority) {
        newNode->next = masterList->priorityList;
        masterList->priorityList = newNode;
    } else {
        struct Node* current = masterList->priorityList;

        // Find the correct position to insert the new node
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }

        // Insert the new node after 'current'
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to display the priority queue
void display(struct MasterList* masterList) {
    struct Node* current = masterList->priorityList;
    printf("Priority Queue:\n");
    while (current != NULL) {
        printf("Data: %d, Priority: %d\n", current->data, current->priority);
        current = current->next;
    }
}

int main() {
    struct MasterList masterList;
    masterList.priorityList = NULL;

    // Insert elements into the priority queue
    insert(&masterList, 10, 2);
    insert(&masterList, 20, 1);
    insert(&masterList, 30, 3);
    insert(&masterList, 40, 2);

    // Display the priority queue
    display(&masterList);

    return 0;
}
