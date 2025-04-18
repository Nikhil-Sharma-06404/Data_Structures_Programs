#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct {
    int data[MAX_NODES];
    int front, rear;
} Queue;

void enqueue(Queue *q, int value) {
    q->data[q->rear++] = value;
}

int dequeue(Queue *q) {
    return q->data[q->front++];
}

void BFS(int graph[MAX_NODES][MAX_NODES], int nodes, int start) {
    int visited[MAX_NODES] = {0};
    Queue q;
    q.front = q.rear = 0;
    
    enqueue(&q, start);
    visited[start] = 1;

    while (q.front < q.rear) {
        int current = dequeue(&q);
        printf("%d ", current);
        
        for (int i = 0; i < nodes; i++) {
            if (graph[current][i] && !visited[i]) {
                enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }
}

int visited[MAX_NODES] = {0};

void DFS(int graph[MAX_NODES][MAX_NODES], int nodes, int current) {
    visited[current] = 1;
    printf("%d ", current);
    
    for (int i = 0; i < nodes; i++) {
        if (graph[current][i] && !visited[i]) {
            DFS(graph, nodes, i);
        }
    }
}

int main() {
    int nodes = 6; 
    int edges = 7; 
    int graph[MAX_NODES][MAX_NODES] = {0}; 
    
    int edgesArray[][2] = {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {4, 5}, {5, 6}};
    
    for (int i = 0; i < edges; i++) {
        int node1 = edgesArray[i][0];
        int node2 = edgesArray[i][1];
        graph[node1][node2] = graph[node2][node1] = 1;
    }

    int start_node = 1; 

    printf("BFS Traversal starting from node %d: \n", start_node);
    BFS(graph, nodes, start_node);

    printf("\nDFS Traversal starting from node %d: \n", start_node);
    DFS(graph, nodes, start_node);
    
    return 0;
}




