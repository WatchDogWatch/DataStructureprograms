#include<stdlib.h>
#include"time.h"
#include<iostream>
#include<vector>
using namespace std;
#define MAXSIZE 1000
typedef struct {
    int data;
    int cur;
} Node[MAXSIZE];//链表元素读取
//静态链表是由数组实现的，首元素指针指向第一个备用链表位置，末元素指针指向第一个储存元素的位置
bool InitStaticList(Node array){
    int i;
    for(i=0;i<MAXSIZE-1;i++){
        array[i].cur=i+1;      
    }
    array[MAXSIZE-1].cur=0;
    return true;
}
bool CreateRandomStaticList( int n){//L是头节点
    int i;
    Node array;
    InitStaticList(array);
    if(n>MAXSIZE){
        cout<<"number too big"<<'\n';
        return false;
    }
    srand(4391);//使用种子，每次随机数序列相同 
    for(i=1;i<=n;i++){
        int data=rand()%100+1;
        array[i].data=data; 
        }
    array[n].cur=1001;
    array[0].data=n+1;
    array[MAXSIZE-1].data=1;    
    int j=0;
    while(j!=1001){
        cout<<array[j].data<<':';
        cout<<array[j].cur<<'\n';
        
        if(array[j+1].cur==0){
            cout<<array[j+1].data<<':';
            cout<<array[j+1].cur<<'\n';
        }
        j=array[j].cur;

    }
    cout<<array[MAXSIZE-1].data<<'\n';
    
    return true;
}
bool StaticListInsert(int n, int index, int val){
    int i;
    Node array;
    InitStaticList(array);
    if(n>MAXSIZE){
        cout<<"number too big"<<'\n';
        return false;
    }
    srand(4391);//使用种子，每次随机数序列相同 
    for(i=1;i<=n;i++){
        int data=rand()%100+1;
        array[i].data=data; 
        }
    array[n].cur=1001;
    array[0].data=n+1;
    array[MAXSIZE-1].data=1; 
    //插入元素   
    array[array[0].data].data=val;    
    array[array[0].data].cur=array[index-1].cur;
    array[index-1].cur=array[0].data;
    array[0].data+=1;
    //输出链表
    int j=0;
    while(j!=1001){
        cout<<array[j].data<<':';
        cout<<array[j].cur<<'\n';
        
        if(array[j+1].cur==0){
            cout<<array[j+1].data<<':';
            cout<<array[j+1].cur<<'\n';
        }
        j=array[j].cur;

    }
    cout<<array[MAXSIZE-1].data<<'\n';
    
    return true;

}
bool StaticListDelete(int n, int index){
    int i;
    Node array;
    InitStaticList(array);
    if(n>MAXSIZE){
        cout<<"number too big"<<'\n';
        return false;
    }
    srand(4391);//使用种子，每次随机数序列相同 
    for(i=1;i<=n;i++){
        int data=rand()%100+1;
        array[i].data=data; 
        }
    array[n].cur=1001;
    array[0].data=n+1;
    array[MAXSIZE-1].data=1; 
    //删除元素   
    array[index-1].cur=array[index].cur;
    
    
    //输出链表
    int j=0;
    while(j!=1001){
        cout<<array[j].data<<':';
        cout<<array[j].cur<<'\n';
        
        if(array[j+1].cur==0){
            cout<<array[j+1].data<<':';
            cout<<array[j+1].cur<<'\n';
        }
        j=array[j].cur;

    }
    cout<<array[MAXSIZE-1].data<<'\n';
    
    return true;

}
int main(void){
    
    cout<<"Random StaticList Generation:"<<'\n';
    CreateRandomStaticList(10);    
    cout<<"insert a element"<<'\n';
    StaticListInsert(10,5,88);
    cout<<"delete a element"<<'\n';
    StaticListDelete(10,6);
    system("pause");
    return 1;
}
 //       list.push_back(P->data);