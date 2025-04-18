#include<iostream>
using namespace std;

struct Tree
{
    struct Tree *lchild;
    int data;
    struct Tree *rchild;
}*root = NULL;

struct Queue
{
  int front;
  int rear;
  int size;
  struct Tree* *Q;
};

void create(struct Queue *q, int size)
{
  q->size = size;
  q->front = q->rear = -1;
  q->Q = (struct Tree **)malloc(q->size * sizeof(struct Tree));
}

void Enqueue(struct Queue *q, struct Tree *x)
{
    if((q->rear+1)%q->size == q->front)
     printf("Not Enough space !");
    else
     {
      q->rear = (q->rear + 1)%q->size;
      q->Q[q->rear] = x;
     }
}

int isEmpty(struct Queue *q)
{
    return q->front==q->rear;
}

struct Tree *Dequeue(struct Queue *q)
{
    struct Tree *x = NULL;
    if(q->front == q->rear)
     printf("Queue is Empty !");
    else
     {
        q->front = (q->front + 1)%q->size;
        x = q->Q[q->front];
     }
    return x;
}


void CreateTree()
{
    int x = 0;
    struct Tree *t,*p;
    struct Queue q; 
    create(&q,100);
    cout<<"Enter the root data: ";
    cin>>x;
    root = (struct Tree *)malloc(sizeof(struct Tree));
    root->data = x;
    root->lchild = root->rchild = NULL;
    Enqueue(&q,root);

    while(!isEmpty(&q))
    {
        p = Dequeue(&q);
        cout<<"Enter the left child of "<<p->data<<": ";
        cin>>x;

        if(x != -1)
        {
            t = (struct Tree *)malloc(sizeof(struct Tree));
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->lchild = t;
            Enqueue(&q,t);
        }

        cout<<"Enter the right child of "<<p->data<<": ";
        cin >> x;

        if(x != -1)
        {
            t = (struct Tree *)malloc(sizeof(struct Tree));
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->rchild = t;
            Enqueue(&q,t);
        }
    }    
}

void Inorder(struct Tree *p)
{
    if(p)
    {
        Inorder(p->lchild);
        cout<<p->data<<"\n";
        Inorder(p->rchild);
    }
}

void Preorder(struct Tree *p)
{
    if(p)
    {
        cout<<p->data<<"\n";
        Preorder(p->lchild);
        Preorder(p->rchild);
    }
}


void Postorder(struct Tree *p)
{
    if(p)
    {
        Postorder(p->lchild);
        Postorder(p->rchild);
        cout<<p->data<<"\n";
    }
}



int main()
{
  CreateTree();
  cout<<"Inorder: \n";
  Inorder(root);
  cout<<"\nPreorder:\n";
  Preorder(root);
  cout<<"\nPostorder:\n";
  Postorder(root);
  return 0;
}