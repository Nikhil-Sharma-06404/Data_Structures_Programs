#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    int data;
    struct Stack *next;
} *top = NULL;

void push(int x)
{
    struct Stack *t;
    t = (struct Stack *)malloc(sizeof(struct Stack));
    t->data = x;

    if (top == NULL)
    {
        t->next = NULL;
        top = t;
    }
    else
    {
        t->next = top;
        top = t;
    }
}

int pop()
{
    int x = -1;
    struct Stack *p;
    p = (struct Stack *)malloc(sizeof(struct Stack));

    if (top == NULL)
    {
        printf("Stack is Empty");
    }
    else
    {
        p = top;
        x = p->data;
        top = top->next;
        free(p);
    }
    return x;
}

void display()
{
    struct Stack *p = top;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    push(10);
    push(20);
    push(30);
    printf("Elements in Stack are: \n");
    display();
    printf("Deleted element is %d\n",pop());
    printf("Deleted element is %d\n",pop());
    printf("Elements in Stack are: \n");
    display();

    return 0;
}
