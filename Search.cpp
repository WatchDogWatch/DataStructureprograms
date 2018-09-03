#include <iostream>
#include <stdlib.h>

#define MAXSIZE 1000
using namespace std;
//顺序表查找
int Swquential_Search(int *a, int n, int key){//a是数组，n是数组元素数量，key是待查找关键字
    int i=n;
    a[0]=key;//放置哨兵，可以避免在查找过程中每次比较后都要判断查找位置是否越界，直接循环即可。
    while(a[i]!=key){
        i--;
    }
    return i;
}
//有序表查找
////折半查找-二分查找
int BinarySearch(int *a, int n, int key){
    int low, mid, high;
    low=1;
    high=n;    
    while(low<=high){
        //mid=(high+low)/2;//传统二分查找
        mid=low+(high+low)*(key-a[low])/(a[high]-a[low]);//插值查找，因为有用插值公式计算mid位置
        if(key<a[mid]){
            high=mid-1;
        }
        if(key>a[mid]){
            low=mid+1;
        }
        if(key==a[mid])
            return mid;
    }
    return 0;//not found...
}
////FIbonacci查找
int F(int n){
    if(n==1)
        return 1;
    if(n==2)
        return 1;
    return F(n-1)+F(n-2);
}

int FibSearch(int *a,int n, int key){
    int low, high,mid,i,k;
    low=1;
    high=n;
    k=0;
    while(n>F(k)-1)
        k++;
    for(i=n;i<F(k)-1;i++)
        a[i]=a[n];
    while(low<=high){
        mid=low+F(k-1)-1;//优势是没有乘除法
        if(key<a[mid]){
            high=mid-1;
            k--;
        }
        if(key>a[mid]){
            low=mid+1;
            k=k-2;//F(n)=F(n-1)+F(n-2)
        }
        if(key==a[mid]){
            if(mid<=n)
                return mid;
            return n;
        }
    }
    return 0;   
}
//二叉排序树-基本排序树
typedef struct BitNode{
    int data;
    struct BitNode *lchild, *rchild;
}BitTree;
//二叉排序树的搜索
bool SearchBitTree(BitTree *T,int key, BitTree *f, BitTree **p){//T是待查找树，key是待查找关键字，f指向T的双亲节点，初始值维nullptr，p指向某个元素节点
    if(!T){//判断是不是叶节点
        *p=f;//f指向T的双亲节点
        return false;

    }
    else if(key==T->data){
        *p=T;
        return true;
    }
    else if(key<T->data)
        SearchBitTree(T->lchild,key,T,p);//f作用在递归调用时有用
    else
        SearchBitTree(T->rchild,key,T,p);        
}
//二叉排序树插入操作
bool InsertBitTree(BitTree *T, int key){//永远时插在最后
    BitTree *p,*s;
    if(!SearchBitTree(T,key,nullptr,&p)){//要查询不成功时再插入
        s=new BitTree;
        s->data=key;
        s->lchild=nullptr;
        s->rchild=nullptr;
        if(!p)
            T=s;
        else if(key<p->data)
            p->lchild=s;
        else
            p->rchild=s;       
        return true;     
    }        
    return false;
}
//二叉排序树删除操作
bool Delete(BitTree *T){
    BitTree *q,*s;
    if(T->lchild==nullptr&&T->rchild==nullptr)
        delete T;
    else if(T->lchild=nullptr){
        q=T;
        T=T->rchild;
        delete q;
    }
    else if(T->rchild=nullptr){
        q=T;
        T=T->lchild;
        delete q;
    }
    else{
        q=T;
        s=T->lchild;
        while(s->rchild){
            q=s;
            s=s->rchild;
        }
        T->data=s->data;
        if(q!=T)
            q->rchild=s->lchild;//rchild is null
        else
            q->lchild=s->lchild;
        delete s;
        
    }
    return true;
}
bool DeleteBitTree(BitTree *T, int key){
    if(!T)
        return false;
    else{
        if(key==T->data)
            return Delete(T);
        else if(key<T->data)
            return DeleteBitTree(T->lchild,key);
        else    
            return DeleteBitTree(T->rchild,key);        
    }

}
//平衡二叉树实现算法AVL树
typedef struct AVLNode{
    int data;
    struct AVLNode *lchild, *rchild;
    int bf;
} AVLTree;
void R_Rotate(AVLTree* &T){//对p为根的子树进行右旋操作
    AVLTree *l;
    l=T->lchild;//new root node
    T->lchild=l->rchild;
    l->rchild=T;
    T=l;
}
void L_Rotate(AVLTree* &T){
    AVLTree *L;
    L=T->rchild;
    T->rchild=L->lchild;
    L->lchild=T;
    T=L;
}
void LB_Rotate(AVLTree* &T){//左平衡旋转(右旋)左bf>1
    AVLTree *L, *Lr;
    L=T->lchild;
    switch(L->bf){
        case 1:
            T->bf=0;
            L->bf=0;
            R_Rotate(T);
            break;
        case -1:
            Lr=L->rchild;
            switch(Lr->bf){
                case 1:
                    T->bf=1;
                    L->bf=-1;
                    break;
                case 0:
                    T->bf=0;
                    L->bf=0;
                    break;
                case -1:
                    T->bf=-1;
                    L->bf=0;
                    break;
            }
            Lr->bf=0;
            L_Rotate(L);
            T->lchild=L;
            R_Rotate(T);
    }
}
void RB_Rotate(AVLTree* &T){//右平衡旋转(左旋)左bf<-1
    AVLTree *L, *Ll;
    L=T->rchild;
    switch(L->bf){
        case -1:
            T->bf=0;
            L->bf=0;
            L_Rotate(T);
            break;
        case 1:
            Ll=L->lchild;
            switch(Ll->bf){
                case 1:
                    T->bf=1;
                    L->bf=0;
                    break;
                case 0:
                    T->bf=0;
                    L->bf=0;
                    break;
                case -1:
                    T->bf=-1;
                    L->bf=1;
                    break;
            }
            Ll->bf=0;
            R_Rotate(L);
            T->rchild=L;
            L_Rotate(T);
    }
}
bool AVLTreemain(AVLTree* &T, int e, bool &taller){

    if(T==nullptr){//
        T=new AVLNode;
        T->data=e;
        T->lchild=nullptr;
        T->rchild=nullptr;
        T->bf=0;
        taller=true;
    }
    else{
        if(e==T->data){
            taller=false;
            return false;
        }
        if(e<T->data){
            if(!AVLTreemain(T->lchild, e, taller)){//返回true说明可以插入新节点
                return false;
            }
            if(taller){
                switch(T->bf){
                    case 1:
                        LB_Rotate(T);
                        taller=false;
                        break;
                    case 0:
                        taller=true;
                        T->bf=1;
                        break;
                    case -1:
                        T->bf=0;
                        taller=false;
                        break;
                    }
            }
        }
        else{
            if(!AVLTreemain(T->rchild, e, taller)){//返回true说明可以插入新节点
                return false;
            }
            if(taller){
                switch(T->bf){
                    case 1:
                        T->bf=0;
                        taller=false;
                        break;
                    case 0:
                        T->bf=-1;
                        taller=true;
                        break;
                    case -1:
                        RB_Rotate(T);
                        taller=false;
                        break;
                }
            }

        }
    }
    return true;

}

void InOrderTraverse(AVLTree *T){
    if (T==nullptr)
    return;
    InOrderTraverse(T->lchild);
    cout<<T->data<<'\n';
    InOrderTraverse(T->rchild);
}

//红黑树
//红黑树保证最差情况下时间复杂度为O(n)。
//红黑树给每个节点增加了一个颜色属性，要求每个节点到其所有后代节点的简单路径上均包含相同数目的黑色节点。进而保证没有一条从根到叶子的简单路径比其他该路径长2倍。
//红黑树性质：1.每个节点为红色或黑色；2.根节点是黑色的；3.空的叶节点(nullptr)是黑色的；如果一个结点是红色的那么其子节点是黑色的。5.每个节点到其所有子节点的简单路径均包含相等的黑节点。(黑高相等)
//红黑树插入：搜索后插入节点，默认红色(这样就一直不会违背性质5，不需要处理)，然后通过旋转和重新着色修正该红黑树.主要三种情况：插入根节点，插入到黑节点的子节点，插入到红节点的子节点，又分三种情况。
//红黑树删除：正常删除后，修正红黑树。

//2-3树
//一个节点具有两个孩子或三个孩子：2节点（2孩子）包括一个元素喝两个孩子，三节点包括两个元素喝三个孩子，两个元素一大一小，将数据分成三部分，对应三个孩子。2-3树所有叶子节点都在同一层上。
//插入操作：必须保持树叶子再同一层上，高度增加是通过插入的传播效应导致根节点拆分产生的。
//1.对于空树，直接插入一个二节点即可。
//2.插入到一个二节点叶子上，将其升级为三节点即可，谁大谁在后。
//3.往三节点中插入一个元素，需要将三节点进行拆分，选择其中一个元素向上移动一层，在其父节点处组成三节点，若以是三节点，则继续往上拆分，直至根节点，若根节点也已经是三节点，则将根节点拆分成二节点，树高度加一。
//删除操作，反向插入
//1.删除三节点元素，直接删除即可，不影响书的结构。
//2.删除二节点元素，分四种情况：1：双亲2节点，右孩子三节点，则删除后左旋转即可；2：双亲2节点，右孩子二节点，那我们让右孩子变成三节点，让其后继元素前提，然后左旋；3：满二叉树，没有三节点孩子，则降低树高。
//  4：双亲是三节点，孩子是2节点，则拆开三节点。
//3.删除非叶子节点，则直接让前继元素(删除三节点)或后继元素(二节点)补位。 

//2-3-4树
//还包括一个四节点的使用，三个元素四个孩子。同样所有叶子须在同一层。插入删除同2-3树，插入二三节点时直接插入，删除三四节点时直接删除，二节点或四节点操作同2-3树的2，3节点操作。

//B树
//平衡的多路查找树，节点最大孩子的数目称为B树的阶。
//B树查找：指针搜索和关键字查询结合的过程：根据指针找到节点，然后再节点中查找关键字。重复该过程。
//B树删除：先查询，再删除，删除方法同2-3树和2-3-4树。
//优势：让B树的阶数与硬盘储存的页面大小匹配，比如1000阶，高度为2，那么我们可以通过两次读取盘就找到关键字。大大减少了内存和硬盘的数据交换次数，减少访问外盘的次数，提高性能。
//缺点：若进行中序遍历，那么部分元素会被多次访问。

//B+树
//应用于文件系统。
//分支节点的元素会再其后继叶子节点中再次列出，并多了一个指向后一个叶子节点的指针。因此叶子节点包含所有的关键字信息了。通过遍历叶子节点即可。B+树中分支节点只作为索引使用，要到其叶节点访问。

//哈希表-散列表，散列：数据的储存位置与关键词之间有一个确定的对应关系f，使得每个关键字key对应一个储存位置。f称为散列函数，哈希函数。采用散列技术将记录储存在一块连续的储存空间中，这块连续储存空间称为散列表。
//查找记录时通过散列函数计算散列地址，按此地址访问该记录。因此散列技术是一种储存方法，也是一种查找方法。 
//优势：适合查找与给定值相等的记录。即一对一，不适合一对多。
//散列函数构造方法  哈希计算的是区域内的分布地址(如数组的下标)，不是内存的真实物理地址。
//原则：速度快；散列地址均匀分布。
//1.直接定址法
//取关键字的某个线性函数值为散列地址，即：f(key)=a*key+b;此种方法需要事先知道关键字的分布情况。
//2.数字分析法
//抽取关键字的一部分来计算散列储存位置，比如手机号的后四位，对后四位做反转，左移等操作；此方法适合关键字位数比较大的情况，且关键字的若干位分布均匀。
//3.平方取中法
//将关键字(数字)平方后取结果的中间几位数字做散列地址；此方法适合不知道关键字分布，且位数不是很大的情况。
//4.折叠法
//将关键字从左到右分割成位数相等的几部分，将其叠加求和后按散列表长取后几位作为散列地址；此方法不需要知道关键字分布，适合关键字位数较多的情况。
//5.除留余数法
//此法最常用，f(key)=key mod p ,p<m。不仅可以直接取余数，还可以平方后，平方取中后取模。p很关键。p一般为小于等于表长的最小质数或不包含小于20质因子的合数。
//6.随机数法
//f(key)=random(key)。此方法适合关键字的长度不等的情况。

//对于字符串等关键字，可以将其按某种方式转换为数字，然后如上操作。
//冲突：给定两个不一样的关键字，通过哈希函数得到的结果相同。堆积：不是同义词确要争夺同一个地址。
//解决方法
//1.开放定址法。一旦发生了冲突，就去寻找下一个空的散列地址，f1(key)=(f(key)+d) mod p. d=1,2...p-1，逐渐增大d，直至找到空位置。这是线性探测法，但容易产生堆积现象。
//  通过改进d=1，-1，2，-2，4，-4，8，-8等取值实现定址称为二次探测法，目的是不让关键字聚集在一起，发生堆积现象。 对d采用随机函数计算，称为随机探测法。
//2.再散列函数法：使用多个散列函数备用，发生冲突时换个函数，避免冲突和堆积。
//链地址法：用散列表储存同义词子链表的头指针，遇到冲突就在对应子链表中添加节点即可。完全不用担心冲突，缺陷是会因为遍历链表增加耗时。
//3.公共溢出区法，将所有冲突元素根据冲突顺序储存到一个溢出区中，查询时先查找散列地址，不对再去溢出区查找。冲突少时速度快。

//装填因子alpha：已有记录个数/散列表长度。alpha越大表示冲突的可能性越大。因此实际选取时会选择较大的存储空间以保证alpha再一定范围内。
//hash list
typedef struct hashlist{
    int *elem;
    int conut;
}HashSearch;
bool InitHashTable(HashSearch *H, int m){
    int i;
    H->conut=m;
    H->elem=new int[m];
    for(i=0;i<m;i++)
        H->elem[i]=0;
    return true;
}
int Hash(int key){//哈希函数
    return key % 12;
}
void HashInsert(HashSearch *H, int key){
    int addre=Hash(key);
    while(H->elem[addre]!=0)
        addre=(addre+1)%12;
    H->elem[addre]=key;
}

int main(){
    int i;
    int a[10]={3,2,1,4,5,6,7,10,9,8};
    AVLTree *T=nullptr;
    bool taller;
    for(i=0;i<10;i++){
        AVLTreemain(T,a[i], taller);
    }
    InOrderTraverse(T);
    system("pause");
    return 1;
}