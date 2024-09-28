#include<iostream>
#include<queue>
#define MaxSize 10111
using namespace std;
typedef char ElemType;
typedef struct {
    ElemType data;
    int lc, rc, fa;
}Node;
typedef Node Bitree[MaxSize];
Bitree btree1, btree2;
 
bool judge(int root1, int root2) {
    if ((root1 == -1 && root2 != -1) || (root1 != -1 && root2 == -1)) {
        return 0;
    }
    if (root1 == -1 && root2 == -1) {//遍历到空了
        return 1;
    }
    if (btree1[root1].data != btree2[root2].data) {
        return 0;
    }
    bool noswp = judge(btree1[root1].lc, btree2[root2].lc) && judge(btree1[root1].rc, btree2[root2].rc);
    bool swap = judge(btree1[root1].lc, btree2[root2].rc) && judge(btree1[root1].rc, btree2[root2].lc);
    return noswp || swap;
 
}
//bfs求树的深度 
int GetDepth(int root, Bitree& btree) {
    int level = 0;
    if (root == -1)return 0;
    queue<int>q;
    q.push(root);
    while (!q.empty()) {
        int len = q.size();    level++;
        while (len--) {
            int t = q.front();
            q.pop();
            if (btree[t].lc != -1)q.push(btree[t].lc);
            if (btree[t].rc != -1)q.push(btree[t].rc);
        }
    }
    return level;
 
}
int N1, N2;
 
int BuildTree(int& N, Bitree& btree) {
    cin >> N;  int lf, ri;
    int root;
    for (int i = 0; i < N; i++) {
        btree[i].fa = -1;
    }
    for (int i = 0; i < N; i++) {
        cin >> btree[i].data;
        cin >> lf;
        if (cin.good()) {
            btree[i].lc = lf ;
            btree[lf].fa = i;
        }
        else { 
            cin.clear(); 
            btree[i].lc = -1;
        }
        cin >> ri;
        if (cin.good()) {
            btree[i].rc = ri ;
            btree[ri].fa = i;
        }
        else { 
            cin.clear(); 
            btree[i].rc = -1; 
        }
    }
    for (int i = 0; i < N; i++) {
        if (btree[i].fa == -1) {
            root = i; break;
        }
    }
    return root;
}
 
int main() {
    int N1, N2, root1, root2;
    root1 = BuildTree(N1, btree1);
    root2 = BuildTree(N2, btree2);
    if (N1 != N2) {
        cout << "No" << endl;
    }
    if (N1 == N2) {
        if (judge(root1, root2)) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    int dep1 = 0, dep2 = 0;
 
    dep1 = GetDepth(root1, btree1);
    dep2 = GetDepth(root2, btree2);
    cout << dep1 << endl << dep2 << endl;
 
}