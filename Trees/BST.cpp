#include<iostream>
using namespace std;

struct Tree
{
  struct Tree *lchild;
  int data;
  struct Tree *rchild;
}*root = NULL;

void Insert(int Key)
{
    struct Tree *t = root; 
    struct Tree *p,*r;
    if(t == NULL)
    {
        p = (struct Tree *)malloc(sizeof(struct Tree));
        p->data = Key;
        p->lchild = p->rchild = NULL;
        root = p;
        return;
    }
    while(t != NULL)
    {
        r = t;
        if(Key == t->data)
        return;
        else if(Key < t->data)
         t = t->lchild;
        else
         t = t->rchild;
    }

        p = (struct Tree *)malloc(sizeof(struct Tree));
        p->data = Key;
        p->lchild = p->rchild = NULL;

        if(p->data < r->data)
        r->lchild = p;
        else
        r->rchild = p;
}

// Iterative way to Search in BST
struct Tree *Search(struct Tree *t,int Key)
{
  while(t != NULL)
  {
    if(Key == t->data)
      return t;
    else if(Key < t->data)
     t = t->lchild;
    else 
      t = t->rchild;
  }
  return NULL;
}

//Recusive Way to Search in BST
struct Tree *Rsearch(struct Tree *t, int key)
{
  if(t == NULL)
   return NULL;
  if(key == t->data)
   return t;
  else if(key < t->data)
   return Rsearch(t->lchild,key);
  else
   return Rsearch(t->rchild,key);
}


//Recursive Insert
struct Tree *insert(struct Tree *p, int key)
{
  struct Tree *t=NULL;
  if(p == NULL)
  {
   t = new Tree;
   t->data = key;
   t->lchild=t->rchild=NULL;
   return t;
  }
  if(key < p->data)
  {
    p->lchild = insert(p->lchild,key);
  }
  else if(key > p->data)
   p->rchild = insert(p->rchild,key);
  return p;
 }

 int Height(struct Tree *p)
 {
  int x,y;
  if(p == NULL)
   return 0;
  x = Height(p->lchild);
  y = Height(p->rchild);

  return x>y?x+1:y+1;
 }

 struct Tree *InPre(struct Tree *p)
 {
  while(p && p->rchild != NULL)
  {
    p = p->rchild;
  }
  return p;
 }

 struct Tree *InSucc(struct Tree *p)
 {
  while(p && p->lchild != NULL)
  {
    p = p->lchild;
  }
  return p;
 }

// Deleting in BST
struct Tree *Delete(struct Tree *p, int Key)
{
  struct Tree *q;
  if(p == NULL)
    return NULL;
  
  if(p->lchild == NULL && p->rchild == NULL)
  {
    if(p == root)
     root = NULL;
    free(p);
    return NULL;
  }

  if(Key < p->data)
   p->lchild = Delete(p->lchild,Key);
  else if(Key > p->data)
   p->rchild = Delete(p->rchild,Key);
  else
  {
    if(Height(p->lchild) > Height(p->rchild))
    {
      q = InPre(p->lchild);
      p->data = q->data;
      p->lchild = Delete(p->lchild,q->data);
    }
     else
    {
      q = InSucc(p->rchild);
      p->data = q->data;
      p->rchild = Delete(p->rchild,q->data);
    }
  }
  return p;
}

void Inorder(struct Tree *t)
{
    if(t != NULL)
    {
        Inorder(t->lchild);
        printf("%d ",t->data);
        Inorder(t->rchild);
    }
}

int main()
{
    struct Tree *temp;
   Insert(10);
   Insert(5);
   Insert(20);
   Insert(30); 
   printf("Elements in BST are:\n");
   Inorder(root);
   Delete(root,20);
   cout<<"\nAfter Deleting 20: \n"; 
   Inorder(root);
    return 0;
}