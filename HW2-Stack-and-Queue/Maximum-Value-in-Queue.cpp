#include<iostream>
using namespace std;
typedef long long int ElemType;
typedef struct LinkNode {
    ElemType data;
    struct LinkNode* next;
}LinkNode;
 
typedef struct {
    LinkNode* front, * rear;
    int len;
}LinkQueue;
//入队等于在队尾插入节点，出队等于在队头弹出节点 
void InitQueue(LinkQueue& Q) {
    Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
    Q.front->next = NULL;//初始时为空 
    Q.len = 0;
}
bool Empty(LinkQueue Q) {
    return (Q.front == Q.rear);
}
void EnQueue(LinkQueue& Q, ElemType& e) {
    LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
    s->data = e; s->next = NULL;//创建新节点，插入到队尾
    Q.rear->next = s;
    Q.rear = s;
    Q.len++;
}
 
bool DeQueue(LinkQueue& Q, ElemType& e) {
    if (Q.front == Q.rear) return false;
    LinkNode* p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    Q.len--;
    if (Q.rear == p) {
        Q.rear = Q.front;//如果原队列中只有一个节点，删除之后变空 
    }
    free(p);
    return true;
}
 
 
//用双向链表写双端队列 
typedef struct Dnode {
    ElemType data;
    struct Dnode* prior, * next;
}Dnode;
typedef struct {
    Dnode* front, * rear;//双端队列 的队头和队尾指针 
}DQueue;
void InitDQueue(DQueue& Q) {
    Q.front = Q.rear = (Dnode*)malloc(sizeof(Dnode));
    Q.front->next = NULL;//初始时，front和rear指向同一个next为NULL的节点， 
}
//这个双端队列是单调递减的，当一个元素需要从队尾入队，
//需要从队尾一直pop出比这个元素小的元素，直到碰到不比它小的，把它插入
//GetMax即从队头Pop出最大的元素
//这个双端队列相当于是栈顶开口的优先栈 
//
bool DEmpty(DQueue Q) {
    return Q.rear == Q.front;
}
void RearPush(DQueue& Q, ElemType e) {
    Dnode* node = (Dnode*)malloc(sizeof(Dnode));
    Q.rear->next = node;
    node->data = e;
    node->prior = Q.rear;
    node->next = NULL;
    Q.rear = node;
}
void RearPop(DQueue& Q) {
    Dnode* bin = Q.rear;
    Q.rear = Q.rear->prior;
    Q.rear->next = NULL;
    free(bin);
}
void FrontPop(DQueue& Q) {//front指向的是空数据域节点，因为每增一个节点，rear就指向这个新增节点
    Dnode* bin = Q.front->next;
    if (Q.front->next->next == NULL) {//说明删完这个元素，尾指针会发生变化
        Q.front->next = NULL;
        Q.rear = Q.front;
    }
    else {
        Q.front->next->next->prior = Q.front;
        Q.front->next = Q.front->next->next;
    }
    free(bin);
}
void PriEnQue(DQueue& Q, ElemType& e) {
    if (DEmpty(Q)) {
        RearPush(Q, e);
        return;
    }
    else {
        while (Q.rear->data < e) {//队为空 
            RearPop(Q);
            if (DEmpty(Q))break;
        }
        RearPush(Q, e);
    }
}
 
ElemType GetTop(DQueue Q, ElemType& e) {
    e = Q.front->next->data;
    return e;
}
 
 
string s;
void PrintQueue(LinkQueue Q) {
    LinkNode* p;
    p = Q.front;
    while (p->next != NULL) {
        p = p->next;
        cout << p->data << " ";
    }
    cout<< endl;
}
int main() {
    int n;
    cin >> n;
    ElemType e;
    LinkQueue Q;    InitQueue(Q);
    DQueue P;    InitDQueue(P);//只有队头节点有意义，是用来求max的 
    while (cin >> s) {
        if (s == "dequeue") {
            if (Empty(Q)) {
                cout << "Queue is Empty" << endl;
            }
            else {
                DeQueue(Q, e);
                if (!DEmpty(P)) {
                    ElemType ptop = GetTop(P, ptop);
                    if (e == ptop) {
                        FrontPop(P);
                    }
                }
                cout << e << endl;
            }
            continue;
        }
        if (s == "enqueue") {
            cin >> e;
            if (Q.len >= n) {
                cout << "Queue is Full" << endl;
 
            }
            else {
                EnQueue(Q, e);
                PriEnQue(P, e);
            }
            continue;
        }
        if (s == "max") {
            if (Empty(Q)) {
                cout << "Queue is Empty" << endl;
            }
            else {
                e = GetTop(P, e);
                cout << e << endl;
            }
            continue;
        }
        if (s == "quit") {
            if (Empty(Q)) {
                cout << "Queue is Empty" << endl;
            }
            else {
                PrintQueue(Q);
            }
            break;
            continue;
        }
    }
    return 0;
 
}