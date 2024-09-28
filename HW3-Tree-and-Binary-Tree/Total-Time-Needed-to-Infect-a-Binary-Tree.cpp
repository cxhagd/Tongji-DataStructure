#include<iostream>
using namespace std;
#define MaxSize 100000+11
typedef int ElemType;
int n, start;
typedef struct BiTNode {
    ElemType data;
    bool vis;
    BiTNode* lchild, * rchild, *parent;
}BiTNode;
BiTNode* beg;
 
 
void InitTree(BiTNode* now) {
    now->vis = 0;
    if (now->data == start) {
        beg = now;
    }
    int left, right;
    cin >> left >> right;
    if (left == -1) {
        now->lchild = NULL;
    }
    if (left != -1) {
        BiTNode* t1 = (BiTNode*)malloc(sizeof(BiTNode));
        now->lchild = t1; t1->data = left; t1->parent = now;
        InitTree(t1);
    }
    if (right == -1) {
        now->rchild = NULL;
    }
    if (right != -1) {
        BiTNode* t2 = (BiTNode*)malloc(sizeof(BiTNode));
        now->rchild = t2; t2->data = right; t2->parent = now;
        InitTree(t2);
    }
    if (now->data == start) {
        beg = now;
    }
 
}
int Depth(BiTNode* T) {
    T->vis = 1;
    int depl=0; 
    int depr=0; int depf=0;
    if (T) {
        if(T->lchild!=NULL)if(!T->lchild->vis)depl = Depth(T->lchild);
        if (T->rchild != NULL)if (!T->rchild->vis)depr = Depth(T->rchild);
        if (T->parent != NULL)if (!T->parent->vis)depf = Depth(T->parent);
        return max(depl, max(depr, depf)) + 1;
    }
    return 0;
}
 
int main() {
 
    cin >> n >> start;
    BiTNode* t = (BiTNode*)malloc(sizeof(BiTNode));
    t->parent = NULL;
    t->data = 0;
    InitTree(t);
    int d1 = 0, d2 = 0, d3 = 0;
    beg->vis = 1;
    if (beg->parent != NULL) {
        d1 = Depth(beg->parent);
    }
    if (beg->lchild != NULL) {
        d2 = Depth(beg->lchild);
    }
    if (beg->rchild != NULL) {
        d3 = Depth(beg->rchild);
    }
    cout << max(d1, max(d2, d3)) << endl;
 
}