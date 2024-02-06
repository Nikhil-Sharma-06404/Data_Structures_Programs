#include <iostream>
#include <stdlib.h>
using namespace std;

struct Stack
{
    int size;
    int top;
    int *S;
};

void create_Stack(struct Stack *s,int size)
{
    s->size = size;
    s->top = -1;
    s->S = (int *)malloc(s->size*sizeof(struct Stack));
}

void Push(struct Stack *s, int x)
{
    if (s == NULL)
        printf("Stack is Full  !");
    else
    {
        s->top++;
        s->S[s->top] = x;
    }
}

int Pop(struct Stack *s)
{
    int x = 0;
    if (s->top == -1)
        printf("\nStack is Empty !");
    else
    {
        x = s->S[s->top];
        s->top--;
    }
    return x;
}

int is_Empty(struct Stack s)
{
    return s.top == -1;
}

int stack_top(struct Stack s)
{
    if (!is_Empty(s))
    {
        return s.top;
    }
    return -1;
}

void display(struct Stack s)
{
    cout<<"Elements in Stack are:\n";
    while(!is_Empty(s))
    {
      printf("%d ",s.S[(s.top)--]);
    }
    cout<<"\n";
}

int main()
{
    struct Stack s;
    create_Stack(&s,100);
    Push(&s, 10);
    Push(&s, 20);
    Push(&s, 30);
    Push(&s, 40);
    display(s);
    printf("Deleted Element from Stack top is: %d\n",Pop(&s));
    printf("Deleted Element from Stack top is: %d\n",Pop(&s));
    display(s);
    return 0;
}