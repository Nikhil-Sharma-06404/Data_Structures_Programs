#include<iostream>
#include<bits/stdc++.h>
#include<stack>

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

struct Queue
{
   int size;
   int front;
   int rear;
   struct Tree* *Q;    
};

void create_Queue(struct Queue *q, int size)
{
   q->size = size;
   q->front = q->rear = 0;
   q->Q = (struct Tree **)malloc(sizeof(struct Tree));
}

void Enqueue(struct Queue *q, struct Tree *x)
{
    if(((q->rear+1)%q->size) == q->front)
      printf("\n Queue is full !");
    else
    {
      q->rear = (q->rear + 1)% q->size;
      q->Q[q->rear] = x;
    }
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

int isEmpty_Queue(struct Queue *q)
{
    return q->front == q->rear;
}

void create_Stack(struct Stack *st, int size)
{
    st->size = size;
    st->top = -1;
    st->S = (struct Tree **)malloc(sizeof(struct Tree));
}

void push(struct Stack *st, struct Tree *t)
{
    if(st->top == st->size-1)
      printf("Stack Overflow !");
    else
    {
       st->S[++st->top] = t;
    }
}

struct Tree* pop(struct Stack *st)
{
  struct Tree *t = NULL;
  if(st->top == -1)
    printf("\nSatck is Underflow! ");
  else
  {
    t = st->S[st->top];
    st->top--;
  }
  return t;
}

int isEmpty(struct Stack st)
{
    return st.top?0:1;
}


void create_Tree()
{
    struct Queue q;
    create_Queue(&q,100);
    int x = 0;

    struct Tree *t,*p;
    cout << "Enter the root data: ";
    cin >> x;
    root = (struct Tree *)malloc(sizeof(struct Tree));
    root->data = x;
    root->lchild = root->rchild = NULL;
    Enqueue(&q,root);

    while(!isEmpty_Queue(&q))
    {
        p = Dequeue(&q);
        printf("Enter the left child of %d: ",p->data);
        cin >> x;

        if(x != -1)
        {
            t = new Tree;
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->lchild = t;
            Enqueue(&q,t);
        }

        printf("Enter the right child of %d: ",p->data);
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

void preorder(struct Tree *t)
{
    if(t)
    {
        printf("%d ",t->data);
        preorder(t->lchild);
        preorder(t->rchild);
    }
}

void postorder(struct Tree *t)
{
    if(t)
    {
        postorder(t->lchild);
        postorder(t->rchild);
        printf("%d ",t->data);
    }
}

void inorder(struct Tree *t)
{
    if(t)
    {
        inorder(t->lchild);
        printf("%d ",t->data);
        inorder(t->rchild);
    }
}

void Iterative_Preorder(struct Tree *t)
{
    struct Stack st;
    create_Stack(&st, 100);

    while (t != NULL || !isEmpty(st))
    {
        if (t != NULL)
        {
            printf("%d ", t->data);
            push(&st, t);
            t = t->lchild;
        }
        else
        {
            t = pop(&st);
            t = t->rchild;
        }
    }
}

void Iterative_Inorder(struct Tree *t)
{
    struct Stack st;
    create_Stack(&st,100);

    while(t || !isEmpty(st))
    {
        if(t)
        {
            push(&st,t);
            t = t->lchild;
        }
        else
        {
            t = pop(&st);
            printf("%d ",t->data);
            t = t->rchild;
        }
    }
}

void Iterative_Postorder(struct Tree *t)
{
    struct Tree *temp;
    stack<struct Tree *>stk;

    while(t != NULL || !stk.empty())
    {
        if(t != NULL)
          {
            stk.push(t);
            t = t->lchild;
          }
        else
        {
            temp = stk.top();
            stk.pop();
            if(temp->rchild == NULL)
            {
             cout << temp->data;
            }
            else{
            stk.push(temp);
            stk.push(NULL);
            t = temp->rchild;
        }
    }
}
cout << endl;
}



int main()
{
    create_Tree();
    cout<<"Recursive Preorder Traversal of Tree : ";
    preorder(root);
    cout<<"\nIterative Preorder Traversal of Tree : ";
    Iterative_Preorder(root);
    cout<<"\nIterative Inorder Traversal of Tree : ";
    Iterative_Inorder(root);
    cout << "\nIterative Postorder Traversal of Tree : ";
    Iterative_Postorder(root);

    return 0;
}