#include<bits/stdc++.h>
#include<stdio.h>

using namespace std;

struct Stack
{
    int size;
    int Top;
    int *S; 
};

void create(struct Stack *st)
{
    printf("Enter the size: ");
    scanf("%d ", &st->size);
     
    st->Top = -1; 
    st->S = (int *)malloc(st->size * sizeof(int));
}

void display(struct Stack st)
{
    int i;
    for(i=st.Top; i>=0; i--)
     printf("%d ",st.S[i]);
    
    printf("\n");
}

void push(struct Stack *st, int x)
{
    if(st->Top == st->size-1)
      printf("Stack Overflow !");
    else
    {
        st->Top++;
        st->S[st->Top] = x;
    }
}

int pop(struct Stack *st)
{
    int x = -1;
    if(st->Top == -1)
     printf("Stack Underflow !");
    else
    {
      x = st->S[st->Top];
      st->Top --;
    }
    return x;
} 

int peek(struct Stack st, int index)
{
    int x = -1;

    if(st.Top-index+1 < 0)
       printf("Invalid Index !");
    else
    {
        x = st.S[st.Top-index+1];
    }
    return x;
}

int isEmpty(struct Stack st)
{
    if(st.Top == -1)
     return 1;
    return 0;
}

int isFull(struct Stack st)
{
    if(st.Top == st.size-1)
      return 1;
    return 0;
}

int StackTop(struct Stack st)
{
    int x = -1;
    if(!isEmpty(st))
    {
      return st.S[st.Top];
    }
    return x;
}


int main()
{
    struct Stack st;

    create(&st);

    push(&st,10);
    cout<<isEmpty(st);
    display(st);

    return 0;
}