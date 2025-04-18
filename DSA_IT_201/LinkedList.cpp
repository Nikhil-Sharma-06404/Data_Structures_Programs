#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
} *first = NULL;

void insert(int x, int pos)
{
    struct Node *t;
    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;

    // Inserting at head
    if (pos == 0)
    {
        t->next = first;
        first = t;
    }
    else
    {
        struct Node *p = first;
        for (int i = 0; i < pos - 1 && p; i++)
            p = p->next;
        t->next = p->next;
        p->next = t;
    }
}

int pop(int pos)
{
    int x = -1;
    struct Node *p = first;
    struct Node *q = NULL;

    if (pos < 0)
    {
        printf("Invalid position\n");
    }
    else if (pos == 0)
    {
        x = p->data;
        first = p->next;
        free(p);
    }
    else
    {
        int i = 0;
        while (i < pos - 1 && p)
        {
            q = p;
            p = p->next;
            i++;
        }

        if (p)
        {
            q->next = p->next;
            x = p->data;
            free(p);
        }
        else
        {
            printf("Position %d is out of bounds\n", pos);
        }
    }
    return x;
}

void display()
{
    struct Node *temp = first;
    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    insert(30, 0);
    insert(40, 1);
    insert(50, 2);
    insert(20, 0);
    insert(10, 0);
    printf("Elements in Linked List are:\n");
    display();
    printf("Deleting item %d\n", pop(0));
    printf("Deleting item %d\n", pop(3));
    printf("Elements in Linked List are:\n");
    display();

    return 0;
}