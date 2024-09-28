#include<iostream>
using namespace std;
typedef bool ElemType;
typedef struct LinkNode {
    ElemType data;
    struct LinkNode* next;
}LinkNode;
 
typedef struct {
    LinkNode* front, * rear;
}LinkQueue;
//入队等于在队尾插入节点，出队等于在队头弹出节点 
void InitQueue(LinkQueue& Q) {
    Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
    Q.front->next = NULL;
}
bool Empty(LinkQueue Q) {
    return (Q.front == Q.rear);
}
void EnQueue(LinkQueue& Q, ElemType& e) {
    LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
    s->data = e; s->next = NULL;//创建新节点，插入到队尾
    Q.rear->next = s;
    Q.rear = s;
}
bool DeQueue(LinkQueue& Q, ElemType& e) {
    if (Q.front == Q.rear) return false;
    LinkNode* p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) {
        Q.rear = Q.front;
    }
    free(p);
    return true;
}
 
bool matrix[1011][1011];
bool vis[1011][1011];
int n, m; int ans = 0;
int movx[5] = { 0,0,0,-1,1 };
int movy[5] = { 0,-1,1,0,0 };
bool record;//i j x y n m 
void search(int x, int y) {
    vis[x][y] = 1;
    for (int i = 1; i <= 4; i++) {
        if (matrix[x + movx[i]][y + movy[i]] && !vis[x + movx[i]][y + movy[i]]) {
            search(x + movx[i], y + movy[i]);
        }
    }
    return;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> matrix[i][j];
        }
    }
    for (int i = 2; i <= n-1; i++) {
        for (int j = 2; j <= m-1; j++) {
            if (matrix[i][j] && !vis[i][j]) {
                    search(i, j);
                    ans++;
            }
        }
    }
    cout << ans << endl;
 
}