#include<iostream>
#include<stdlib.h>
using namespace std;

struct Node
{
    int data;
    struct Node *next; // Self referential structure

}*first = NULL,*second = NULL,*third = NULL;

void create(int A[], int n)
{
    int i;
    struct Node *t,*last;
    first = (struct Node *)malloc(sizeof(struct Node));

    first->data = A[0];
    first->next = NULL;
    last = first;

    for(i=1; i<n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

void create2(int B[], int n)
{
    int i;
    struct Node *last,*t;
    second = new Node;
    second->data = B[0];
    second->next = NULL;
    last = second;

    for(i=1; i<n; i++)
    {
        t = new Node;
        t->data = B[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

void Display(struct Node *p)
{
    while(p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
}

void RDisplay(struct Node *p)
{
    if(p != NULL)
    {
        printf("%d ",p->data);
        RDisplay(p->next); // REcursive display
     }
}

int count(struct Node *p)
{
    int l=0;
    while(p)
    { 
        l++;
        p = p->next;
    }
    return l;
}

int Rcount(struct Node *p)
{
    if(!p)
      return 0;
    else 
      return Rcount(p->next) + 1;
}

int add(struct Node *p)
{
    int sum=0;
    while(p != NULL)
    {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

int Radd(struct Node *p)
{
    if(!p)
      return 0;
    
    return Radd(p->next) + p->data;
}

int max(struct Node *p)
{
    int mx = INT_MIN;
    while(p != NULL)
    {
        if(mx < p->data)
        {
            mx = p->data;
        }
        p = p->next;
    }
    return mx;
}

int Rmax(struct Node *p)
{
    int x=0;
    if(p == NULL)
      return INT_MIN;

    x = Rmax(p->next);
    return x>p->data? x:p->data;
}

int min(struct Node *p)
{
    int mn = INT_MAX;
    while(p)
    {
        if(mn > p->data)
          mn = p->data;
    
        p = p->next;
    }
    return mn;
}

int Rmin(struct Node *p)
{
    int x = 0;
    if(p == NULL)
      return 0;
    
    x = Rmin(p->next);
    return x<p->data? x:p->data;
}

struct Node *search(struct Node *p, int key)
{
   while(p != NULL)
   {
    if(key == p->data)
      return p;
    p = p->next;
   }
   return NULL;
}

struct Node *Rsearch(struct Node *p, int key)
{
    if(p == NULL)
      return NULL;
    if(key == p->data)
      return p;
    return Rsearch(p->next,key);
}

//Move to Head
struct Node *NewSearch(struct Node *p,int key)
{
    struct Node *q = NULL;
    while(p != NULL)
    {
        if(key == p->data)
        {
           q->next = p->next;
           p->next = first;
           first = p;
           return p;
        }
        q=p;
        p = p->next;
    }
    return NULL;
}

void Insert(struct Node *p, int pos, int x)
{
    if(pos < 0 || pos > count(p))
      return;
    
    struct Node *t;
    t = new Node;
    if(pos == 0)
    {
        t->data = x;
        t->next = first;
        first = t;
    }
    else
    {
        for(int i=0; p && i<pos-1; i++)
         {
            p = p->next;
         }
        t->data = x;
        t->next = p->next;
        p->next = t;
    }
}

void Sorted_Insert(struct Node *p, int x)
{
    struct Node *t,*q=NULL;
    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;

    if(first == NULL)
     first = t;
    else
    {
        while(p && p->data < x)
        {
            q = p;
            p = p->next;
        }
    }
    if(p == first)
    {
        t->next = first;
        first = t;
    }
    else
    {
        t->next = q->next;
        q->next = t;
    }
}

int Delete(struct Node *p, int pos)
{
    int i,x=-1;
    struct Node *q = NULL;

    if(pos < 1 || pos > count(p))
      return x;
    
    if(pos == 1)
    {
        q = first;
        x = first->data;
        first = first->next;
        free(q); 
        return x;
    }
    else
    {
        for(i=0; i<pos-1 && p; i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        x = p->data;
        delete p;
        return x;
    }
}

int isSorted(struct Node *p)
{
    int x = INT_MIN;
    while(p != NULL)
    {
      if(p->data < x) 
        return false;
      x = p->data;
      p = p->next;
    }
    return true;
}

void Remove_Duplicates(struct Node *p)
{
    struct Node *q = p->next;
    
    while(q)
    {
     if(p->data != q->data)
     {
       p = q;
       q = q->next;
     }
     else
     {
        p->next = q->next;
        delete q;
        q = p->next;
     }
    }
}

void Reverse1(struct Node *p)
{
    int *A;
    A = (int *)malloc(sizeof(int)*count(p));
    int i=0;

    while(p != NULL)
    {
        A[i] = p->data;
        p = p->next;
        i++;
    }
    p=first,i--;
    while(p)
    {
       p->data = A[i--];
        p = p->next;
    }
}

// Using Sliding pointers
void Reverse2(struct Node *p)
{
    struct Node *q = NULL, *r = NULL;

    while(p != NULL)
    {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    first = q;
}

void Reverse3(struct Node *q, struct Node *p)
{
    
    if(p)
    {
        Reverse3(p,p->next);
        p->next = q;
    }
    else
     first = q;
}

void concat(struct Node *p, struct Node *q)
{
    third = p;
    while(p->next != NULL)
     p = p->next;
    
    p->next = q;
}

void Merge(struct Node *p, struct Node *q)
{
    struct Node *last;

    if(p->data < q->data)
    {
        third = last = p;
        p = p->next;
        third->next = NULL;
    }
    else
    {
        third = last = q;
        q = q->next;
        third->next = NULL;
    }

    while(p && q)
    {
        if(p->data < q->data)
        {
            last->next = p;
            last = p;
            p = p->next;
            last->next = NULL;
        }
        else
        {
            last->next = q;
            last = q;
            q = q->next;
            last->next = NULL;
        }
    }

    if(p) last->next = p;
    if(q) last->next = q;
}

int is_Loop(struct Node *f)
{
    struct Node *p,*q;
    p=q=f;
    do
    {
        p = p->next;
        q = q->next;
        if(q->next)
         q = q->next;
    } while (p && q && p != q);
    
    if(p == q)
      return true;
    else
      return false;
}

int Middle(struct Node *p)
{
    struct Node *q = first;

    while(q != NULL)
    {
        q = q->next;
        if(q) q = q->next;
        if(q) p = p->next;
    }
    return p->data;
}


int main()
{
    int A[] = {1,2,3,4,5};
    int B[] = {1,2,3,4,5};
   
    create(A,5);
    create2(B,5);
    
    cout << Middle(first);
    Display(first);
    
    return 0;
}