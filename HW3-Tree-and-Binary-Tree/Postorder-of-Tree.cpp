#include<iostream>
#include<cstring>
#include<map>
#include<set>
using namespace std;
typedef char ElemType;
typedef struct BiTNode {
    ElemType data;
    BiTNode* lchild, * rchild, * parent;
}BiTNode, * BiTree;
set<char>self, seri;
bool flag = 0;
 
BiTNode* BuildNode(ElemType e) {
    BiTNode* t = (BiTNode*)malloc(sizeof(BiTNode));
    t->data = e;
    t->lchild = NULL; t->rchild = NULL;
    return t;
}
 
 
void DestroyTree(BiTree T) {
    if (T == NULL) {
        return;
    }
    if (T->lchild != NULL) {
        BiTree p1 = T->lchild;
        DestroyTree(p1);
    }
    if (T->rchild != NULL) {
        BiTree p2 = T->rchild;
        DestroyTree(p2);
    }
    free(T);
}
BiTree BuildTree(char* pre, char* inn) {//建树的时候每次都在中序中找  pre里有这个now 、
    self.clear();
    seri.clear();
    //建立根节点 
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root->data = pre[0];
    root->lchild = NULL;
    root->rchild = NULL;
    //建左子树和右子树 
    //现在中序中确定左子树和右子树的长度 
    char inlf[70] = { '\0' }, inri[70] = { '\0' }; bool tag = 0;
    int slf = 0, sri = 0;
    for (int i = 0, j = 0; i < strlen(inn); i++) {
        if (inn[i] == root->data) {
            tag = 1; slf = i; sri = strlen(inn) - 1 - slf; continue;
        }
        if (!tag) {
            inlf[i] = inn[i]; self.insert(inlf[i]); continue;
        }
        if (tag) {
            inri[j] = inn[i]; seri.insert(inri[j]); j++; continue;
        }
    }
 
    char prelf[70] = { '\0' }; char preri[70] = { '\0' };
    //pre里有这个now 
    for (int i = 1; i <= slf; i++) {
        prelf[i - 1] = pre[i];
        if (!self.count(prelf[i - 1])) {
        flag = 1;    return NULL;
            
        }
    }
    for (int i = strlen(inn) - 1, j = sri - 1; j >= 0; i--, j--) {
        preri[j] = pre[i];
        if (!seri.count(preri[j])) {
        flag = 1;    return NULL;
            
        }
    }
 
    if (slf > 0) {
        root->lchild = BuildTree(prelf, inlf);
    }
    if (sri > 0) {
        root->rchild = BuildTree(preri, inri);
    }
    return root;
}
 
 
void PostOrder(BiTree T) {
    if (T != NULL) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        cout << T->data;
    }
}
 
int main() {
    char inn[70], pre[79];
    while (cin >> pre >> inn) {
        flag = 0;
        BiTree root = (BiTree)malloc(sizeof(BiTNode));
        root = BuildTree(pre, inn);
        if (root == NULL || flag) {
            cout << "Error" << endl;
        }
        else {
            PostOrder(root); cout << endl;
        }
        DestroyTree(root);
 
    }
 
}