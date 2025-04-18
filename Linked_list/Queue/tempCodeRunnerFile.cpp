#include<stdio.h>
#include<stdlib.h>

struct Queue
{
  int data;
  struct Queue *next;
}*front = NULL, *rear = NULL;

void Enqueue(int x)
{
    struct Queue *t;
    if(t == NULL)
    {
        printf("Queue is Empty !");
    }

    t = (struct Queue *)malloc(sizeof(struct Queue));
    t->data = x;
    t->next = NULL;

    if(front == NULL && rear == NULL)
    {
      front = rear = t;  
    }
    else
    {
      rear->next = t;
      rear = t;
    }
}


int Dequeue()
{
    int x = -1;
    struct Queue *temp;
    temp = front;

    if(front == NULL && rear == NULL)
    {
        printf("Queue is Empty !");
    }
    else
    {
        x = front->data;
        front = front->next;
        free(temp);
    }
}

void Display()
{
    struct Queue *p;
    p = front;
    while(p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
}

int main()
{
    Enqueue(10);
    Enqueue(20);
    Enqueue(30);
    printf("Elements in queue are:\n");
    Display();
    printf("\nElement popped is %d\n",Dequeue());
    printf("Elements in queue are:\n");
    Display();
    return 0;
}