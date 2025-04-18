#include<iostream>
using namespace std;

struct Queue
{
    int data;
    struct Queue *next;
}*front=NULL,*rear=NULL;

void insert(int x)
{
   struct Queue *t;
   t = (struct Queue *)malloc(sizeof(struct Queue));
   if(t == NULL)
     printf("Queue is Full !");
  
    t->data = x;
   if(rear == NULL)
   {
    t->data = x;
    t->next = NULL;
    front = rear = t;
   }

   while(rear->next)
     rear = rear->next;

   rear->next = t;
   t->next = NULL;
   rear = t;
}

int dequeue()
{
    if(front == NULL)
      printf("Queue is Empty !");
    struct Queue *t = front;
    int x = t->data;
    front = front->next;
    free(t);
    return x;
}

void display()
{
    struct Queue *t = front;
    while(t)
    {
        printf("%d ",t->data);
        t = t->next;
    }
}

int main()
{
    insert(10);
    insert(20);
    insert(30);
    printf("Elements in Queue are:\n");
    printf("Deleted Element is %d\n",dequeue());
    printf("After deletion Elements in Queue are:\n");
    display();
    return 0;
}