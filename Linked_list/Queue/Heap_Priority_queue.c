#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

typedef struct {
    int data[MAX_HEAP_SIZE];
    int size;
} PriorityQueue;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue* pq, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && pq->data[index] < pq->data[parent]) {
        swap(&pq->data[index], &pq->data[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void heapifyDown(PriorityQueue* pq, int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < pq->size && pq->data[leftChild] < pq->data[smallest])
        smallest = leftChild;

    if (rightChild < pq->size && pq->data[rightChild] < pq->data[smallest])
        smallest = rightChild;

    if (smallest != index) {
        swap(&pq->data[index], &pq->data[smallest]);
        heapifyDown(pq, smallest);
    }
}

void insert(PriorityQueue* pq, int value) {
    if (pq->size >= MAX_HEAP_SIZE) {
        printf("Queue is full. Cannot insert more elements.\n");
        return;
    }

    pq->data[pq->size] = value;
    heapifyUp(pq, pq->size);
    pq->size++;
}

int deleteMin(PriorityQueue* pq) {
    if (pq->size <= 0) {
        printf("Queue is empty. Cannot delete.\n");
        return -1;
    }

    int minValue = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return minValue;
}

int main() {
    PriorityQueue pq;
    pq.size = 0;

    insert(&pq, 5);
    insert(&pq, 2);
    insert(&pq, 8);
    insert(&pq, 1);
    printf("Priority Queue:\n");
    printf("Minimum value: %d\n", deleteMin(&pq));
    printf("Minimum value: %d\n", deleteMin(&pq));
    
    return 0;
}
