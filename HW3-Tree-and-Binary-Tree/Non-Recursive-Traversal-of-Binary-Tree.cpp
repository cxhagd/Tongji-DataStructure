#include<iostream>
#include<stack>
#include<cstring>
#include<set>
using namespace std;
int n;
typedef char ElemType;
set<char>self, seri;
typedef struct BiTNode {
    ElemType data;
    BiTNode* lchild, * rchild, * parent;
}BiTNode, * BiTree;
stack<char> s;
//push代表往下走，如果左为NULL就走，如果左 不为NULL就往右走   pop就是往上走 
void PostOrder(BiTree T) {
    if (T != NULL) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        cout << T->data;
    }
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
    char inlf[500] = { '\0' }, inri[500] = { '\0' }; bool tag = 0;
    int slf = 0, sri = 0;
    for (int i = 0, j = 0; i < strlen(inn); i++) {
        if (inn[i] == root->data) {
            tag = 1; slf = i; sri = strlen(inn) - 1 - slf; continue;
        }
        if (!tag) {
            inlf[i] = inn[i];  continue;
        }
        if (tag) {
            inri[j] = inn[i];  j++; continue;
        }
    }
 
    char prelf[500] = { '\0' }; char preri[500] = { '\0' };
    //pre里有这个now 
    for (int i = 1; i <= slf; i++) {
        prelf[i - 1] = pre[i];
        
    }
    for (int i = strlen(inn) - 1, j = sri - 1; j >= 0; i--, j--) {
        preri[j] = pre[i];
        
    }
 
    if (slf > 0) {
        root->lchild = BuildTree(prelf, inlf);
    }
    if (sri > 0) {
        root->rchild = BuildTree(preri, inri);
    }
    return root;
}
 
 
int pin = 0, ppr = 0;
char inn[200] = { '\n' }, pre[200] = { '\n' };
int  main() {
    cin >> n;
    ElemType e;
    for (int i = 1; i <= 2 * n; i++) {
        string op;
        cin >> op;
        if (op == "push") {
            cin >> e;
            pre[ppr++] = e;
            s.push(e);
        }
        if (op == "pop") {
            e = s.top();
            s.pop();
            inn[pin++] = e;
        }
    }
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root = BuildTree(pre, inn);
    PostOrder(root);
    return 0;
}