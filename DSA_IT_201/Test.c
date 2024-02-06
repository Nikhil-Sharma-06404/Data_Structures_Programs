#include<stdio.h>

struct Term
{
 int coefficient;
 int exponent;
 struct Term *next;
};

void Insert(struct Term **head, int coefficient, int exponent)
{
    struct Term *t = (struct Term *)malloc(sizeof(struct Term));
    t->coefficient = coefficient;
    t->exponent = exponent;
    t->next = NULL;

    if(*head == NULL)
     t = NULL;
    else
    {
        struct Term *curr = *head;
        while(curr != NULL)
        {
            curr = curr->next;
        }
        curr->next = t;
    }
}