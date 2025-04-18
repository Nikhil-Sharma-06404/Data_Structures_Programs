#include<iostream>
using namespace std;

struct Tree
{
  struct Tree *lchild;
  int data;
  struct Tree *rchild;
}*root = NULL;

struct Stack
{
int size;
int top;
struct Tree* *S;
};

void createStack(struct Stack *s, int size)
{
  s->size = size;
  s->top = -1;
  s->S = (struct Tree **)malloc(s->size * sizeof(struct Tree));
}

void push(struct Stack *s, struct Tree *x)
{
  if(s->top == s->size-1)
   printf("StackOverflow !");
  else
  {
    s->top++;
    s->S[s->top] = x;
  }
}

struct Tree *pop(struct Stack *s)
{
  struct Tree *x = NULL;
  if(s->top == -1)
   printf("Stack Underflow !");
  else
  {
    x = s->S[s->top--];
  }
  return x;
}

int StackTop(struct Stack *s)
{
  struct Tree *x = NULL;
  if(s->top >= 0)
  {
    x = s->S[s->top];
  }
  return x->data;
}

void BST_Generate(int preorder[], int n)
{
  int i=0;
  struct Tree *t,*p;
  struct Stack s;
  createStack(&s,100);

  root = (struct Tree *)malloc(sizeof(struct Tree));
  root->data = preorder[i++];
  root->lchild = root->rchild = NULL;
  p = root;
  
  while(i < n)
  {
    if(p->data > preorder[i])
    {
      t = (struct Tree *)malloc(sizeof(struct Tree));
      t->data = preorder[i++];
      t->lchild = t->rchild = NULL;
      p->lchild = t;
      push(&s,p);
      p = t;
    }
   else
  {
    if((preorder[i] > p->data) && (preorder[i] < StackTop(&s)))
    {
        t = (struct Tree *)malloc(sizeof(struct Tree));
        t->data = preorder[i++];
        t->lchild = t->rchild = NULL;
        p->rchild = t;
        p = t;
    }
    else
    {
        p = pop(&s);
    }
}
  }
}

void Inorder(struct Tree *p)
{
  if(p)
  {
    Inorder(p->lchild);
    printf("%d \t",p->data);
    Inorder(p->rchild);
  }
}

int main()
{
int preorder[] = {30,20,10,15,25,40,50,45};
int size = sizeof(preorder)/sizeof(preorder[0]);

struct Stack s;
createStack(&s,100);

BST_Generate(preorder,size);

Inorder(root);

return 0;
}