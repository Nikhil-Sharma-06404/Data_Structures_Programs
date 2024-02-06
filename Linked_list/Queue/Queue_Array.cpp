#include<iostream>
#include<bits/stdc++.h>

using namespace std;

struct Queue
{
  int size;
  int front;
  int rear;
  int *Q; // Dynamic Memory allocation
};

void create(struct Queue *q, int size)
{
    q->size = size;
    q->front = q->rear = -1;
    q->Q = (int *)malloc(sizeof(int) * q->size);
}

void enqueue(struct Queue *q, int x)
{
    if(q->rear == q->size-1)
      printf("Queue is full !");
    else
     q->rear++;
     q->Q[q->rear] = x;
}

int dequeue(struct Queue *q)
{
    int x = -1;
    if(q->front == q->rear)
      printf("Queue is Empty !");
    else
    {
        q->front ++;
        x = q->Q[q->front];
    }
    return x;
}

void display(struct Queue q)
{
   int i;
   for(i = q.front+1; i<=q.rear; i++)
    {
        printf("%d ",q.Q[i]);
    }
    printf("\n");
}

int main()
{
    struct Queue q;
    create(&q,5);
    enqueue(&q,10);
    enqueue(&q,20);
    enqueue(&q,30);
    printf("Elements in a queue are:\n");
    display(q);
    cout<<"Deleted element is: "<< dequeue(&q)<<"\n";
    printf("Elements in a queue are:\n");
    display(q);
    
    return 0;
}