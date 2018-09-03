#include<stdlib.h>
#include"time.h"
#include<iostream>
#include<vector>
using namespace std;

/*栈是只能在表尾(栈顶)进行插入和删除操作，是线性表*/
/*栈又称为后进先出线性表：LIFO结构*/
//栈定义

/*顺序储存结构的栈功能实现-数组*/
#define MAXSIZE 15
typedef struct stack1{
    int data[MAXSIZE];
    int top;
}LIFOStack;

bool push(LIFOStack *s, int val){
    if (s->top==MAXSIZE-1){
        return false;
    }
    s->top++;
    s->data[s->top]=val;
    return true;
}
bool pop(LIFOStack *s, int val){
    if(s->top==-1)//empty
    return false;
    val=s->data[s->top];
    s->top--;
    return true;
}
/*两栈共享空间的操作，其实和单独操作没区别，仍然是一个栈底，一个栈顶，栈底top1=-1,栈顶top2=MAXSIZE，增加一个栈号即可，其次就是栈满的标准变成了栈指针隔1.top1+1=top2*/
/*栈的链式储存结构实现-链栈*/
/*对于链栈，头节点的作用被栈顶的指针取代，链栈不需要头结点*/
/*链栈没有满栈的说法，空栈就是栈顶指针指向nullptr*/
typedef struct listnode{
    int data;
    struct listnode *next;
}ListNode;

typedef struct liststack{
    ListNode *top;
    int count;// 计数用
}LIFOListStack;

bool ListStack_push(LIFOListStack *s, int val){
    ListNode *p=new ListNode;
    p->data=val;
    p->next=s->top;
    s->top=p;
    s->count++;
    return true;

}
bool ListStack_pop(LIFOListStack *s, int val){
    if(s->top==nullptr)
    return false;
    ListNode *p;
    p=s->top;
    s->top=s->top->next;
    val=s->top->data;
    delete p;
 //   delete s->top;
    s->count--;
    return true;
}
/*队列*/
/*队列有两个指针，指向头和尾部，尾部添加数据rear，头部删除数据front，循环队列就是rear指向下标为0的地方*/
typedef struct queue{
    int data[MAXSIZE];
    int front;
    int rear;
}Queue;

bool InitQueue(Queue *q){
    q->front=0;
    q->rear=0;
    return true;
}
int QueueLength(Queue *q){
    int i=0;
    while(q->front!=q->rear){
        i++;
        q->front++;
    }
    return i;
//   return (q->rear-q->front+MAXSIZE)%MAXSIZE;
}
bool EnQueue(Queue *q, int val){
    if(q->rear%MAXSIZE==q->front)//未留空元素
    return false;
    q->data[q->rear]=val;
    q->rear=(q->rear+1)%MAXSIZE;
    return true;
}
bool DeQueue(Queue *q, int val){
    if(q->rear==q->front)
    return false;
    val=q->data[q->front];
    q->front=(q->front+1)%MAXSIZE;//+1是直接指向下一个元素，跳过要出队列的元素
    return true;
}
/*链队列实现*/
typedef struct queuenode{
    int data;
    struct queuenode *next;
}QueueNode;
typedef struct listqueue{    
    QueueNode *front;
    QueueNode *rear;
}ListQueue;
bool ListEnqueue(ListQueue *q, int val){
    QueueNode *s=new QueueNode;
    s->data=val;
    s->next=nullptr;
    q->rear->next=s;
    q->rear=s;
    return true;
}
bool ListDeQueue(ListQueue *q, int val){
    if(q->rear==q->front)
    return false;
    QueueNode *s;
    s=q->front->next;
    q->front->next=s->next;
    val=s->data;
    if(q->rear==s)//只有删除最后一个元素才会影响尾指针，需要重新赋值。
    q->rear=q->front;
    delete s;
    return true;

}