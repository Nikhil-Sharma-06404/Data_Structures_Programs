#include <stdio.h>
#include <cstring>
using namespace std;
 
struct Stack
{
    char data;
    struct Stack* next;
}*top = NULL;
 
void push(struct Stack *p,char x) {
    struct Stack* t = new Stack;
    if (t == NULL){
        printf("Stack Overflow !");
    } else {
        t->data = x;
        t->next = top;
        top = t;
    }
}
 
char pop() {
    struct Stack* p;
    char x ;
    if (top == NULL){
        {
        printf("Stack Underflow !");
        return '0';
        }
    } else {
        p = top;
        x = p->data;
        top = top->next;
        delete p;
        return x;
    }
}
 
int isFull() {
    struct Stack* t = new Stack;
    int r = t ? 1 : 0;
    delete t;
    return r;
}
 
int isEmpty() {
    return top ? 0 : 1;
}
 
char stackTop() {
    if (top){
        return top->data;
    }
    return '0';
}
 
char peek(int index) {
    if (isEmpty()){
        return -1;
    } else {
        Stack* p = top;
 
        for (int i=0; p && i<index-1; i++){
            p = p->next;
        }
 
        if (p != nullptr){
            return p->data;
        } else {
           return '0';
        }
    }
}

int isOperand(char x)
{
    if(x == '*' || x == '/' || x == '+' || x == '-')
    {
        return false;
    }
    return 1;
}

int precedence(char x)
{
     if(x == '+' || x == '-')
       return 1;
     else if(x == '*' || x == '/')
       return 2;
     else
      return 0;

}

char *convert(char *infix)
{
    struct Stack st;
    char *postfix = new char[strlen(infix) + 1];
    int i=0,j=0;

    while(infix[i] != '\0')
    {
       if(isOperand(infix[i]))
        {
            postfix[j++] = infix[i++];
        }
        else
        {
            if(precedence(infix[i]) > precedence(stackTop()))
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
   char *postfix = convert(infix);
   printf("Infix Expression is : %s",infix);
   printf("\nPostfix Expression is: %s ",postfix);

    return 0;
 
}