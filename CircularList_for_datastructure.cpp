#include<stdlib.h>
#include"time.h"
#include<iostream>
#include<vector>
using namespace std;


typedef struct Node{
    int data;
    struct Node *next;
} Node;//链表元素读取
 int GetElem(Node *L, int i=1){
     int j,data;
     Node *p;
     p=L->next;
     if (i==1)
     return L->data;
     j=2;//包括头节点
     while((p->next!=L)&&j<i){
         p=p->next;
         j++;
     }
     if(p==L)
     return false;//reach list end

     data=p->data;
     return data;
 }
 bool ListInsert(Node *L, int i=2, int e=100){//i>1
     int j=2;
     Node *p=L->next;
     Node *s=new Node;
     if(i==2){
         s->data=e;
         s->next=L->next;
         L->next=s;
         return true;
     }
     while((p->next!=L)&&j<i-1){
         p=p->next;
         j++;
     }
     if (p==L)
     return false;
     s->data=e;
     s->next=p->next;
     p->next=s;

     L->data+=1;
     return true;
 }
int ListDelete(Node *L, int i){//i>1
    int j=2;
    int data;
    Node *p=L->next;
    Node *q;
    if(i==2){
        q=L->next;
        L->next=q->next;
        data=q->data;
        delete q;
        L->data-=1;
         return data;
     }
    while((p->next!=L)&&j<i-1){
        p=p->next;
        j++;
    }
    if(p==L)
    return false;
    q=p->next;
    p->next=q->next;
    data=q->data;
    delete q;
    L->data-=1;
    return data;
}
Node *CreateRandomList( int n, bool dir=true){//L是头节点
    int i;
    Node *L=new Node;
    L->data=n;
//    srand((unsigned int)time(0));
    srand(4391);//使用种子，每次随机数序列相同
    L->next=L;//(*)L.a=L->a
    if(dir==true){
        for(i=1;i<n;i++){
        int data=rand()%100+1;
    //   ListInsert(p,1,data);
        Node *p=new Node;
        p->data=data;        
        p->next=L->next;
        L->next=p;
        }
        
    }
    if(dir==false){
        Node *r=L;
        for(i=1;i<n;i++){
        int data=rand()%100+1;
        Node *p=new Node;
        p->next=L;
        p->data=data;
        r->next=p;
        r=p;
    
    }
    }

    return L;

}
bool ClearList(Node *L){
    Node *p=new Node;
    Node *q=new Node;
    p->next=L->next;    
    while(p->next!=L){
        q=p;
        p=p->next;
        delete q;        
    }  
    delete p;  
    L->next=L;
    return true;
}

int main(void){// 头节点算元素数量
    Node *P,*L;
    int data,index;
 //   vector<int> list;
 /*打印随机生成的列表*/
    cout<<"random list generation:"<<'\n';
    P=CreateRandomList(10, false);   
    L=P;
    while(P->next!=L){
        std::cout<<P->data<<':'; 
        cout<<P->next<<'\n';       
        P=P->next;
        if(P->next==L){
            std::cout<<P->data<<':'; //打印尾节点
            cout<<P->next<<'\n';
        }
 //       list.push_back(P->data);
    }
 /*获取链表元素*/   
    P=CreateRandomList(10);
    
    cout<<"get list's element(input a number):"<<'\n';
//    cin>>index;
    data=GetElem(P);
    cout<<data<<'\n';
/*链表插入元素*/
cout<<"inset elemnt in list"<<'\n';
    P=CreateRandomList(10);
    L=P;
//    cin>>index;
    ListInsert(P);
    while(P->next!=L){
        std::cout<<P->data<<':'; 
        cout<<P->next<<'\n';       
        P=P->next;
        if(P->next==L){
            std::cout<<P->data<<':'; //打印尾节点
            cout<<P->next<<'\n';
        }    
    }
/*链表元素删除*/
    cout<<"delete list's element"<<'\n';
    P=CreateRandomList(10);
    L=P;
    data=ListDelete(P,4);
    cout<<data<<'\n';
    while(P->next!=L){
        std::cout<<P->data<<':'; 
        cout<<P->next<<'\n';       
        P=P->next;
        if(P->next==L){
            std::cout<<P->data<<':'; //打印尾节点
            cout<<P->next<<'\n';
        }    
    }
/*链表的整体删除*/
    cout<<"delete list"<<'\n';
    P=CreateRandomList(10);
    L=P;
    ClearList(P);
    if(P->next==L)
    cout<<"list is empty"<<'\n';

    system("pause");
    return 1;
}

