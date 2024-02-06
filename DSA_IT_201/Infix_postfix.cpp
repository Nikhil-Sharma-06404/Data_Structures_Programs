#include<iostream>
#include<cstring>
using namespace std;

struct Stack
{
    char data;
    struct Stack *next;
}*top = NULL;

void push(struct Stack *p, char x)
{
    struct Stack *t = new Stack;
    if(t == NULL)
     {
        printf("Stack is Overflow !");
        exit(1);
     }
    else
    {
        t->data = x;
        t->next = top;
        top = t;
    }
}

char pop()
{
    struct Stack *p;
    char x;

    if(top == NULL)
    {
        printf("Stack is Empty !");
        exit(1);
    }
    else
    {
        p = top;
        x = p->data;
        top = p->next;
        delete p;
        return x;
    }
    return '0';
}

int isEmpty()
{
    return top ? 0:1;
}

char StackTop()
{
    if(top)
     return top->data;
    return '0';
} 

int precedence(char x)
{
    if(x == '+' || x == '-')
     return 1;
    else if(x == '/' || x == '*')
      return 2;
    else if(x == '$')
      return 3;
    else
     return 0;
}

int isOperand(char x)
{
    if(x == '+' || x == '-' || x == '/' || x == '*' || x == '$')
     return 0;
    return 1;
}

char *infix_to_postfix(char *infix)
{
    char *postfix = new char[strlen(infix) + 1];
    int i=0,j=0;

    while(infix[i] != '\0')
    {
        if(isOperand(infix[i]))
         postfix[j++] = infix[i++];
        else
        {
            if(precedence(infix[i]) > precedence(StackTop()))
              push(top,infix[i++]);
            else
            postfix[j++] = pop();
        }
    }

    while(!isEmpty())
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
    return postfix;
}

int main()
{
  char infix[] = "a+b*c-d/e";
   char *postfix = infix_to_postfix(infix);
   printf("\n\n%s ",postfix);

    return 0;   
}