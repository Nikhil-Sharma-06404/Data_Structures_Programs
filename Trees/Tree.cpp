#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct Tree
{
    struct Tree *lchild;
    int data;
    struct Tree *rchild;
}*root = NULL;

struct Queue
{
    int size;
    int front;
    int rear;
    Tree **Q;
};

void create(struct Queue *q, int size)
{
    q->size = size;
    q->front = q->rear = 0;
    q->Q = (struct Tree **)malloc(q->size * sizeof(struct Tree));
}

void Enqueue(struct Queue *q, struct Tree *x)
{
    if((q->rear+1)%q->size == q->front)
      printf("\nQueue is full !");
    else
    {
      q->rear = (q->rear+1)%q->size;
      q->Q[q->rear] = x;   
    }
}

struct Tree * Dequeue(struct Queue *q)
{
    Tree *x = NULL;
    if(q->front == q->rear)
     printf("Queue is Empty !");
    else
     {
        q->front = (q->front+1)%q->size;
        x = q->Q[q->front];
     }
     return x;
}

int isEmpty(struct Queue q)
{
    return q.front == q.rear;
}

void create_Tree()
{ 
  struct Queue q;
  create(&q,100);
  int x = 0;
  
  struct Tree *p,*t;
  root = new Tree;
  printf("Enter the root data: "); 
  cin >> x;
  root->data = x;
  root->lchild = root->rchild = NULL;
  Enqueue(&q,root); 

  while(!isEmpty(q))
  {
    p = Dequeue(&q);
    printf("\nEnter the left child of %d :",p->data);
    cin >> x;
    if(x != -1)
    {
        t = new Tree;
        t->data = x;
        t->lchild = t->rchild = NULL;
        p->lchild = t;
        Enqueue(&q,t);
    }

    printf("\nEnter the right child of %d :",p->data);
    cin >> x;
    if(x != -1)
    {
        t = new Tree;
        t->data = x;
        t->lchild = t->rchild = NULL;
        p->rchild = t;
        Enqueue(&q,t);
    }
  }
}

void preorder(struct Tree *p)
{
    if(p)
    {
        printf("%d ",p->data);
        preorder(p->lchild);
        preorder(p->rchild);
    }
}

void postorder(struct Tree *p)
{
    if(p)
    {
        postorder(p->lchild);
        postorder(p->rchild);
        printf("%d ",p->data);
    }
}

void inorder(struct Tree *p)
{
    if(p)
    {
        inorder(p->lchild);
        printf("%d ",p->data);
        inorder(p->rchild);
    }
}

int count(struct Tree *p)
{
    if(p)
     return count(p->lchild) + count(p->rchild) + 1;
    return 0;
}

void Levelorder(struct Tree *p)
{
    struct Queue q;
    create(&q,100);

    printf("%d ",p->data);
    Enqueue(&q,p);

    while(!isEmpty(q))
    {
        p = Dequeue(&q);
        if(p->lchild)
        {
            printf("%d ",p->lchild->data);
            Enqueue(&q,p->lchild);
        }
        if(root->rchild)
        {
            printf("%d ",p->rchild->data);
            Enqueue(&q, p->rchild);
        }
    }
}

int Height(struct Tree *p)
{
    int x=0, y=0; 
    if(p == 0)
      return 0;
    
    x = Height(p->lchild);
    y = Height(p->rchild);

    return x>y?x+1:y+1;

}

int main()
{   
    create_Tree();
    cout<<"Preorder is: ";
    preorder(root);
    cout<<endl;

    cout<<"Inorder is: ";
    inorder(root);
    cout<<endl;

    cout<<"Postorder is: ";
    postorder(root);
    cout<<endl;

    cout<<"Level order is: ";
    Levelorder(root);
    cout<<endl;

    cout<<"Total Nodes are: ";
    count(root);
    cout<<endl;

    cout<<"Height of tree: ";
    Height(root);
    cout<<endl;

    return 0;
}

