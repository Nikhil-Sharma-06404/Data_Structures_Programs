#include<iostream>
using namespace std;

struct Node
{
    int data;
    struct Node *next;
}*Head = NULL; 

void create(int A[], int n)
{
    struct Node *t, *last;
    int i;
    Head = new Node; 
    Head->data = A[0];
    Head->next = Head;
    last = Head;

    for(i = 1; i < n; i++)
    {
        t = new Node; 
        t->data = A[i];
        t->next = last->next;
        last->next = t;
        last = t;
    }
}

void display(struct Node *p)
{
    struct Node *temp = p; 

    if (temp != NULL) 
    {
        do
        {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != Head);
    }
}

int Length(struct Node *p)
{
    struct Node *temp = p; 
    int len = 0;

    if (temp != NULL) 
    {
        do
        {
            len++;
            temp = temp->next;
        } while (temp != Head);
    }
    return len;
}

void Insert(struct Node *p, int pos, int x)
{
    struct Node *t;
    int i;

    if (pos < 0 || pos > Length(p))
    {
        return;
    }
    if (pos == 0)
    {
        t = new Node;
        t->data = x;
        if (Head == NULL)
        {
            Head = t;
            Head->next = Head;
        }
        else
        {
            while (p->next != Head)
                p = p->next;

            p->next = t;
            t->next = Head;
            Head = t;
        }
    }
    else
    {
        for (i = 0; i < pos - 1; i++)
        {
            p = p->next;
        }
        t = new Node;
        t->data = x;
        t->next = p->next;
        p->next = t;
    }
}

int Delete(struct Node *p, int pos)
{
    struct Node *q;
    int i, x = -1;

    if (pos == 1)
    {
        while (p->next != Head)
            p = p->next;

        x = Head->data;
        if (Head == p)
        {
            delete Head; 
            Head = NULL;
        }
        else
        {
            p->next = Head->next;
            delete Head; 
            Head = p->next;
        }
    }
    else
    {
        for (i = 0; i < pos - 2; i++)
            p = p->next;

        q = p->next;
        x = q->data;
        p->next = q->next;
        delete q;
    }
    return x;
}

int main()
{
    int A[] = {1, 2, 3, 4, 5};
    create(A, 5); 

    Insert(Head, 5, 5);
    Insert(Head, 6, 6);
    display(Head);
    cout << "\nDeleted Element is: " << Delete(Head, 1) << endl; 
    display(Head);
    return 0;
}
