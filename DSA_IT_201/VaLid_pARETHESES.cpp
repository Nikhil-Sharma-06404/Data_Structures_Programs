#include<iostream>
using namespace std;

struct Stack
{
  char data;
  struct Stack *next;
}*top = NULL;

void push(struct Stack *p, char x)
{
    struct Stack *t;
    t =(struct Stack *)malloc(sizeof(struct Stack));
    
    if(t == NULL)
     {
        cout<<"Stack is Full !";
        exit(1);
     }
    else
    {
        t->data = x;
        t->next = top;
        top = t;
    }
}

void pop()
{
    struct Stack *p;
    char x = '0';
    if(top == NULL)
    {
        printf("Stack is UNDERFLOW !");
        exit(1);
    }
    else
    {
        p = top;
        x = p->data;
        top = p->next;
        delete p;
    }
}

int isEmpty()
{
    return top?0:1;
}

int isBalanced(char *exp)
{
    for(int i=0;exp[i] != '\0';i++)
    {
        if(exp[i] == '(')
         push(top, exp[i]);
        else
        { 
            if(isEmpty())
              return false;
            else
             pop();
        }
    }
    return isEmpty()?true:false;
}


int main()
{
  char exp[] = "(a+b)*(e/b)";
  cout<<isBalanced(exp)<<"\n";

  char newexp[] = "((d-e)*(f/)";
  cout<<isBalanced(newexp)<<"\n";

 return 0;
}