#include<iostream>
using namespace std;

struct Stack
{
    int size;
    int top;
    int *S;
};

void create(struct Stack *s,int size)
{
    s->size = size;
    s->top = -1;
    s->S = (int *)malloc(sizeof(int) * s->size);
}

void push(struct Stack *s, int x)
{
   if(s->top == s->size-1)
     printf("\n Stack Overflow !");
    else
    {
        s->top++;
        s->S[s->top] = x;
    }
}

int pop(struct Stack *s)
{
    int x = -1;
    if(s->top == -1)
     printf("\n Stack Underflow !");
    else
    {
        x = s->S[s->top];
        s->top--;
    }
    return x;
}

int isEmpty(struct Stack *s)
{
    return s->top == -1?1:0;
}

int isFull(struct Stack *s)
{
    if(s->top == s->size -1)
     return 1;
    return 0;
}

void Enqueue(struct Stack *s1, int x)
{
  push(s1,x);
}

int Dequeue(struct Stack *s1, struct Stack *s2)
{
    int x = -1;
    if(isEmpty(s2))
    {
        if(isEmpty(s1))
        {
            printf("\nQueue is Empty!");
            return x;
        }
        else{
            while(!isEmpty(s1))
            {
                push(s2,pop(s1));
            }
        }
    }
    return pop(s2);
}

int main()
{
    struct Stack s1,s2;
    create(&s1,10);
    create(&s2,10);

    Enqueue(&s1,10);
    Enqueue(&s1,20);
    Enqueue(&s1,30);

    cout<<Dequeue(&s1,&s2);
    cout<<Dequeue(&s1,&s2);
    cout<<Dequeue(&s1,&s2);
    cout<<Dequeue(&s1,&s2);
    
    return 0;
}