#include<iostream>
#include<bits/stdc++.h>

struct Node
{
  struct Node *prev;
  int data;
  struct Node *next;
}*first = NULL;

void create(int A[], int n)
{
    struct Node *t,*last;
    int i;
    first = new Node;

    first->data = A[0];
    first->prev = first->next = NULL;
    last = first;

    for(i=1; i<n; i++)
    {
        t = new Node;
        t->data = A[i];
        t->prev = last;
        t->next = last->next;
        last->next = t;
        last = t;
    }
}

void display(struct Node *p)
{
    while(p)
    {
        printf("%d ",p->data);
        p = p->next;
    }
}

int Length(struct Node *p)
{
    int len = 0;
    while(p)
    {
        len++;
        p = p->next;
    }
    return len;
}

void Insert(struct Node *p, int pos, int x)
{
    struct Node *t;
    int i;

    if(pos  < 0 || pos > Length(p))
    {
        return;
    }

    if(pos == 0)
    {
      t = new Node;
      t->data = x;
      t->prev = NULL;
      t->next = first;
      first->prev = t;
      first = t;
    }
    else
    {
        for(i=0; i<pos-1; i++)
         p = p->next;
        
        t = new Node;
        t->data = x;
        t->prev = p;
        t->next = p->next;
        if(p->next)
          p->next->prev = t;
        p->next = t;
    }
}

int Delete(struct Node* &p, int pos)
{
   
    struct Node *q;
    int x;

    if (pos == 1)
    {
        q = p;
        p = p->next;
        if (p)
            p->prev = NULL;
        x = q->data;
        delete q;
    }
    else
    {
        for (int i = 0; i < pos - 1; i++)
            p = p->next;

        q = p;
        p->prev->next = p->next;
        if (p->next)
            p->next->prev = p->prev;
        x = q->data;
        delete q;
    }

    return x;
}

/*
void Reverse(struct Node *p)
{
    struct Node *temp = NULL;
    while(p != NULL)
    {
        temp = p->next;
        p->next = p->prev;
        p->prev = temp;

        p = p->prev;

        if(p->next == NULL && p != NULL)
          first = p;
    }
}
*/

int main()
{
   int A[] = {2,4,6,8,10};
   create(A,5);
  /* Reverse(first);*/
  Insert(first,0,5);
  Insert(first,1,12);
  display(first);
  printf("\nDeleted element is %d\n",Delete(first,1));
  display(first);
  return 0;
}