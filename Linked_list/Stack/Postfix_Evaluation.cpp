#include<iostream>
using namespace std;

struct Stack
{ 
    int data;
    struct Stack *next;
}*top = NULL;

void push(int x)
{
    struct Stack *t;
    t = (struct Stack *)malloc(sizeof(struct Stack));
    if(t == NULL)
     printf("Stack Overflow !");
    else
    {
        t->data = x;
        t->next = top;
        top = t;
    } 
}

int pop()
{
    int x = -1;
    if(top == NULL)
    {
        printf("Stack Underflow !");
        return x;
    }
    else
    {
        struct Stack *p;
        p = top;
        x = p->data;
        top = top->next;
        delete p;
        return x;
    }
}

int isFull()
{
 struct Stack *t = new Stack;
  int r = t?1:0;
  free(t);
  return r;
}

int isEmpty()
{
  return top?0:1;    
}

int stack_Top()
{
    if(top)
      return top->data;
    return -1;
}

int isOperand(char x)
{
    if(x == '-' || x == '*' || x == '+' || x == '/')
      return 0;
    return 1;
}


int eval(char *postfix)
{
    int i,x1,x2,r;
    for(i=0; postfix[i] != '\0'; i++)
    {
      if(isOperand(postfix[i]))
        push(postfix[i] - '0');
    else
    {
        x2 = pop();
        x1 = pop();
        switch(postfix[i])
        {
            case '+' : r = x1+x2; push(r); break;
            case '-' : r = x1-x2; push(r); break;
            case '*' : r = x1*x2; push(r); break;
            case '/' : r = x1/x2; push(r); break;
        }
    }
    }
    return pop();
}

int main()
{
   char postfix[] = "35*62/+4-";
   printf("\nResult is : %d ",eval(postfix));
    return 0;
}