#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
int m, n;
bool vis[2100][2100] = { 0 };
vector<pair<int, int>> rec;
//////////////////////销毁链表 
typedef struct {
    int p;
    int e;
}poly;
 
typedef poly ElemType;
typedef struct Lnode {
    ElemType data;
    struct Lnode* next, * prior;
}Lnode, * LinkList;    //LinkList定义为单链表的头指针名字
 
Lnode* TailInsert(Lnode*& p1, Lnode* newnod) {
    Lnode* temp;
    temp = (Lnode*)malloc(sizeof(Lnode));
    temp->next = NULL;
    p1->next = temp;
 
    temp->data.p = newnod->data.p;
    temp->data.e = newnod->data.e;
    p1 = p1->next;
    return p1;
 
}
 
LinkList List_add(LinkList L1, LinkList L2, LinkList L3) {//L3是空的
    Lnode* p1 = L1->next;
    Lnode* p2 = L2->next;
    Lnode* tail3 = L3;
    Lnode* temp;
    temp = (Lnode*)malloc(sizeof(Lnode));
    while (p1 != NULL && p2 != NULL) {
        if (p1->data.e == p2->data.e) {
            temp->data.p = p1->data.p + p2->data.p;
            temp->data.e = p1->data.e;
            if (temp->data.p != 0) {
                tail3 = TailInsert(tail3, temp);
            }
            p1 = p1->next;
            p2 = p2->next;
            continue;
        }
        if (p1->data.e <p2->data.e) {
            temp->data.p = p1->data.p;
            temp->data.e = p1->data.e;
            if (temp->data.p != 0) {
                tail3 = TailInsert(tail3, temp);
            }
            p1 = p1->next;
            continue;
        }
        if (p2->data.e < p1->data.e) {
            temp->data.p = p2->data.p;
            temp->data.e = p2->data.e;
            if (temp->data.p != 0) {
                tail3 = TailInsert(tail3, temp);
            }
            p2 = p2->next;
            continue;
        }
    }
    while (p1 != NULL) {
        temp->data.p = p1->data.p;
        temp->data.e = p1->data.e;
        tail3 = TailInsert(tail3, temp);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        temp->data.p = p2->data.p;
        temp->data.e = p2->data.e;
        tail3 = TailInsert(tail3, temp);
        p2 = p2->next;
    }
    free(temp);
    return L3;
}
 
 
 
 
void ListDestroy(LinkList& L) {
    Lnode* pp = L;
 
    while (L->next) {
        pp = L->next;
        L->next = pp->next;
        free(pp);
    }
}
 
 
 
 
 
LinkList List_multiple(LinkList L1, LinkList L2, LinkList& L3) {
    Lnode* p1 = L1->next;
    Lnode* p2 = L2->next;
 
 
    
 
    
    Lnode* temp;
    temp = (Lnode*)malloc(sizeof(Lnode));
 
    
    while (p1 != NULL) {
        LinkList L4 = (LinkList)malloc(sizeof(Lnode));//L4是一个暂时的 
        L4->data.e = -99999999;
        Lnode* temp2 = L4;
        LinkList L5 = (LinkList)malloc(sizeof(Lnode));
        L5->next = NULL;
        L5->data.e = -99999999;
 
        while (p2 != NULL) {
            temp->data.p = p1->data.p * p2->data.p;
            temp->data.e = p1->data.e + p2->data.e;
 
            temp2 = TailInsert(temp2, temp);
            p2 = p2->next;
        }
        L3 = List_add(L3, L4, L5);
        ListDestroy(L4);
        L5 = NULL;
        free(L5);
        p2 = L2->next;
        p1 = p1->next;
    }
 
    free(temp);
    return L3;
}
void List_print(LinkList& L) {
    Lnode* pp = L->next;
    if (pp->data.p == 0 && pp->data.e == 0) {
        return;
    }
    while (pp != NULL) {
        cout << pp->data.p << " " << pp->data.e << " ";
        pp = pp->next;
    }
    cout << endl;
}
 
int main() {
 
    LinkList L1 = (LinkList)malloc(sizeof(Lnode));//创建头节点 
    Lnode* tail1 = (Lnode*)malloc(sizeof(Lnode));
    tail1 = L1;
    L1->next = NULL;
    L1->data.e = -99999999;
 
    LinkList L2 = (LinkList)malloc(sizeof(Lnode));//创建头节点 
    Lnode* tail2 = (Lnode*)malloc(sizeof(Lnode));
    tail2 = L2;
    L2->next = NULL;
    L2->data.e = -99999999;
 
    LinkList L3 = (LinkList)malloc(sizeof(Lnode));//创建头节点 
    Lnode* tail3 = (Lnode*)malloc(sizeof(Lnode));
    tail3 = L3;
    L3->next = NULL;
    L3->data.e = -99999999;
    LinkList L4 = (LinkList)malloc(sizeof(Lnode));//创建头节点 
    L4->next = NULL;
    L4->data.e = -99999999;
    cin >> m;
    Lnode* temp = (LinkList)malloc(sizeof(Lnode));;
    for (int i = 1; i <= m; i++) {
        cin >> temp->data.p >> temp->data.e;
        tail1 = TailInsert(tail1, temp);
    }
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (temp->data.p) >> (temp->data.e);
        tail2 = TailInsert(tail2, temp);
    }
    int choice;
    cin >> choice;
    if (choice == 0) {
        L3 = List_add(L1, L2, tail3);
        List_print(L3);
    }
    if (choice == 1) {
        L3 = List_multiple(L1, L2, L3);
        List_print(L3);
    }
    if (choice == 2) {
        L3 = List_add(L1, L2, tail3);
        L4 = List_multiple(L1, L2, L4);
        List_print(L3);
        List_print(L4);
    }
    ListDestroy(L1);
    ListDestroy(L2);
    ListDestroy(L3);
    ListDestroy(L4);
    return 0;
}