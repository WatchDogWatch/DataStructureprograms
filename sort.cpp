#include <iostream>
#include <stdlib.h>

#define MAXSIZE 1000
using namespace std;
typedef struct {
    int r[MAXSIZE+1];//r[0]做哨兵用，快排中减少比较操作
    int length;
}sqlist;
void swap(sqlist *L, int i,int j){
    int temp=L->r[i];
    L->r[i]=L->r[j];
    L->r[j]=temp;
}

//数组初始化
void init(sqlist *L, int num){
    L->length=num;
    int i=1;
    srand(4391);
    while(i<num){
        L->r[i]=rand()%1000+1;
        i++;
    }
    L->r[0]=65535;
}
//数组打印
void printlist(sqlist *L){
    for(int i=0;i<L->length;i++){
        cout<<L->r[i]<<',';
        if(i%25==0&&i!=0)
            cout<<'\n';
    }
    cout<<'\n';
}
/*冒泡排序算法*/
//两两比较，如果顺序相反，则交换位置，一直到最后
void BubbleSort(sqlist *L){
    int i;
    int j;
    for(i=1;i<L->length;i++){
        for(j=i+1;j<L->length;j++){
            if(L->r[i]>L->r[j]){
                int temp=L->r[i];
                L->r[i]=L->r[j];
                L->r[j]=temp;
            }
        }
    }
}
void BubbleSort_V1(sqlist *L){//real version
    int i,j;
    for(i=1;i<L->length;i++){
        for(j=L->length-1;j>=i;j--){
            if(L->r[j]>L->r[j+1]){
                int temp=L->r[j+1];
                L->r[j+1]=L->r[j];
                L->r[j]=temp;

            }
            //swap(L,j,j+1);

        }
    }
}
void BubbleSort_V2(sqlist *L){
    int i,j;
    bool flag=true;
    for(i=1;i<L->length&&flag;i++){
        flag=false;
        for(j=L->length-1;j>=i;j--){
            if(L->r[j]>L->r[j+1]){
                int temp=L->r[j];
                L->r[j+1]=L->r[j];
                L->r[j]=temp;
                flag=true;
            }
        }
    }

}
//简单选择排序
//通过n-i次关键字间的比较，从n-i+1个记录中选出关键字最小的记录，并和第i个记录交换。
void SimpleSelectSort(sqlist *L){
    int i,j;
    for (i=1;i<L->length;j++){
        int min=i;
        for(j=i+1;j<L->length;j++){
            if(L->r[i]>L->r[j]){
                int min=j;
            }
        }
        if(i!=min){
            swap(L,i, min);
        }        
    }
}
//直接插入排序
//选定第一个元素维基准点，小于的在前面排序，根据值确定插入位置，大于的不动
void StraightInsertionSort(sqlist *L){
    int i,j;
    for(i=2;i<=L->length;i++){//main loop：遍历元素
        if(L->r[i]<L->r[i-1]){
            L->r[0]=L->r[i];
            for(j=i-1;L->r[j]>L->r[0];j--){
                L->r[j+1]=L->r[j];
            }
        L->r[j+1]=L->r[0];
        }

    }
}
//希尔排序
//逐级分块插入排序，减小移动的距离，降低排序复杂度
void ShellSort(sqlist *L){
    int i,j;
    int incre=L->length;
    while(incre>1){
        incre=incre/3+1;//增量序列
        for(i=incre+1;i<=L->length;i++){
            if(L->r[i]<L->r[i-incre]){
                L->r[0]=L->r[i];
                for(j=i-incre;j>0&&L->r[j]>L->r[0];j=j-incre){//此处同插排，但是增量由1变成了incre
                    L->r[j+incre]=L->r[j];
                }
                L->r[j+incre]=L->r[0];
            }
        }
    }
}
//堆排序
//将序列调整为大顶堆，然后交换根节点和最后的节点，然后再次堆排序重复交换位置。就是用树的方法记录序列的大小关系，减少搜索时间。
void HeapAdjust(sqlist *L, int s, int t){
    int temp, i;
    temp=L->r[s];
    for(i=2*s;i<=t;i=i*2){
        if(i<t&&L->r[i]<L->r[i+1])
            i++;
        if(L->r[s]>=L->r[i])
            break;
        L->r[s]=L->r[i];
        s=i;
    }
    L->r[s]=temp;
}
void HeapSort(sqlist *L){
    int i,j;
    for(i=L->length/2;i>0;i--){
        HeapAdjust(L,i,L->length);
    }
    for(i=L->length;i>1;i--){
        swap(L,1,i);
        HeapAdjust(L,1,i-1);
    }

}
//归并排序
//将序列递归分组至不可分，不如1，然后进行merge操作将各分组逐步融合到一起，最终得到一个排序的数组。
void Merge(int ss[], int tt[], int s,int m, int t){
    int i,j,k;
    for(i=s,j=m+1;s<=m&&j<=t;i++){//i是tt数组的下标变化
        if(ss[s]<ss[j])
            tt[i]=ss[s++];
        else
            tt[i]=ss[j++];
    }
    if(s<=m){
        for(k=0;k<=m-i;k++){
            tt[i+k]=ss[s+k];
        }
    }
    if(j<=t){
        for(k=0;k<=t-j;k++){
            tt[i+k]=ss[j+k];
        }
    }
}   
void MSort(int ss[], int tt[], int s, int t){//s是起始下标，t是终止下标
//对ss进行归并，合并到tt中，
    int m;//分割值
    int st[MAXSIZE+1];
    if(s==t)
    tt[s]=ss[s];
    else
    {
        m=(s+t)/2;//2分归并
        MSort(ss,st,s,m);
        MSort(ss,st,m+1,t);
        Merge(st,tt,s,m,t);
    }
}
void MergeSort(sqlist *L){
    MSort(L->r,L->r,1,L->length);
}
//非递归归并排序
void MergePass(int ss[],int tt[],int s, int n){
    int i=1;
    int j;
    while(i<=n-2*s+1){//i+2s-1<n
        Merge(ss,tt,i,i+s-1,i+2*s-1);
        i=i+2*s;
    }
    if(i<n-s+1)
        Merge(ss,tt, i, i+s-1, n);
    else{
        for(j=i;j<=n;j++)
            tt[j]=ss[j];
    }
}
void MergeSort(sqlist *L){
    int *st=new int[MAXSIZE+1];
    int k=1;
    while(k<L->length){
        MergePass(L->r,st,k,L->length);
        k=k*2;
        MergePass(st,L->r,k,L->length);
        k=k*2;
    }
}
//快速排序，是冒泡排序的升级版，递归将序列分成两部分排序
int partition(sqlist *L, int low, int high){//选取一个关键字-枢轴，并放到一个位置上，左边值比他小，右边值比他大
    int pivotkey;
    int m=low+(high-low)/2;
    if(L->r[low]>L->r[high])
        swap(L,low,high);
    if(L->r[m]>L->r[high])
        swap(L,m,high);
    if(L->r[low]<L->r[m])
        swap(L,low,m);//让中值在开头，方便后面迭代
    pivotkey=L->r[low];//median value at begin
    L->r[0]=pivotkey;
    while(low<high){
        while(low<high&&L->r[high]>=pivotkey)
            high--;
 //       swap(L,low,high); 
        L->r[low]=L->r[high];
        while(low<high&&L->r[low]<=pivotkey)
            low++;
 //       swap(L,low,high);
        L->r[high]=L->r[low];
    }
    L->r[low]=L->r[0];
    return low;//low=high=pivot's index
}
void QSort(sqlist *L, int low, int high){
    int pivot;
    // if(low<high){
    //     pivot=partition(L,low, high);
    //     QSort(L,low,pivot-1);
    //     QSort(L,pivot+1,high);
    // }
    if(low<high){//不考虑小数组情况
        while(low<high){
            pivot=partition(L,low,high);
            QSort(L,low,pivot-1);//递归一次，减少空间消耗
            low=pivot+1;
        }
    }
}
void QuickSort(sqlist *L){
    QSort(L,1,L->length);
}
int main(){
    sqlist *ll=new sqlist;
    init(ll,100);
    printlist(ll);
    cout<<"BubbleSort result:"<<'\n';
    BubbleSort(ll);
    printlist(ll);
    cout<<"BubbleSort_V1 result:"<<'\n';
    BubbleSort_V1(ll);
    printlist(ll);
    system("pause");
    return 1;
}
