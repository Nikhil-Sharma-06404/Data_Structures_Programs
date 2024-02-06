#include<stdio.h>
#include<cstdlib>
using namespace std;

struct Stack
{
    char data;
    struct Stack *next;
}*TOP = NULL;

void push(char x)
{
    struct Stack *t = new Stack;
    if(t == NULL)
     {
        printf("Stack is Full !");
        exit(1);
     }
    else
    {
        t->data = x;
        t->next = TOP;
        TOP = t;
    }
}

void pop()
{
    struct Stack *p;
    char x;
    if(TOP == NULL)
    {
        printf("Stack is EMPTY !");
        exit(1);
    }
    else
    {
        p = TOP;
        x = p->data;
        TOP = TOP->next;
        delete p;
    }
}

int isEmpty()
{
    return TOP==NULL?1:0;
}

int isBalanced(char *exp)
{
    for(int i=0; exp[i] != '\0'; i++)
    {
        if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
         push(exp[i]);
        else if(exp[i] == ')' || exp[i] == ']' || exp[i] == '}')
        {
            if(isEmpty())
             return false;
             
             char top = TOP->data;
             if(exp[i] == ')' && top != '(' || exp[i] == '{' && top != '}' || exp[i] == '[' && top != ']')
               return false;
             pop();
        }
    }
    return isEmpty()?1:0;
}

int main()
{
    char first[] = "{[a+b]*(b-e)}";
    if(isBalanced(first))
    {
        printf("%s is Valid Expression.\n",first);
    }
    else
    {
     printf("%s is Invalid Expression.\n",first);   
    }

    char second[] = "{[(i-t)}/(o*t]";
     if(isBalanced(second))
    {
        printf("%s is Valid Expression.\n",second);
    }
    else
    {
     printf("%s is Invalid Expression.\n",second);   
    }

    return 0;
}