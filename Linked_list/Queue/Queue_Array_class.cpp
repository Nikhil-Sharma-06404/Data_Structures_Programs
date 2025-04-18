#include<bits/stdc++.h>
using namespace std;

class Queue
{
   private:
    int size;
    int front;
    int rear;
    int *Q;
   public:
      Queue()
     {
        size = 20;
        front = rear = -1;
        Q = new int[20];
     }
       Queue(int size)
     {
       this->size = size;
       front = rear = -1;
       Q = new int[this->size];
     }
       void enqueue(int x);
       int dequeue();
       void display();
};

void Queue :: enqueue(int x)
{
    if(rear == size-1)
      printf("\n Queue is Full");
    else
      {
        rear++;
        Q[rear] = x;
      }
}

int Queue :: dequeue()
{
    int x = -1;
    if(rear == front)
      printf("\n Queue is empty !");
    else
    {
        front ++;
        x = Q[front];
    }
    return x;
}

void Queue :: display()
{
    int i;
    for(i = front + 1; i<=rear; i++)
    {
        printf("%d ",Q[i]);
    }
}

int main()
{
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    
    cout << "Deleted element is: "<<q.dequeue()<<"\n";
    q.display();
    return 0;
}