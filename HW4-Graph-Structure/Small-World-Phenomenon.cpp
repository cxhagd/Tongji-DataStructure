#include<iostream>
#include<cstring>
#include<queue>
#include<stack>
using namespace std;
#define MaxVertexNum 2011//图中顶点数目的最大值
typedef struct ArcNode {//边
    int adjvex;//该弧所指向的顶点的位置 
    struct ArcNode* next; //指向下一条弧的指针 
}ArcNode;
typedef float VertexType;
typedef struct VNode {//顶点 
    VertexType data;//顶点信息
    ArcNode* first;//指向第一条依附该顶点的边
    ArcNode* tail;
}Vnode, AdjList[MaxVertexNum];
typedef struct {
    AdjList vertices;//邻接表 顶点是顺序表，边连边是链表 
    int vexnum, arcnum;//图的顶点数和弧数 
}Graph; //ALGraph是以邻接表存储的图的类型 
void Initial(Graph& G) {//图的所有顶点的first和tail都指向空
    for (int i = 1; i <= G.vexnum; i++) {
        G.vertices[i].first = NULL;
        G.vertices[i].tail = NULL;
    }
}
 
 
void BFS(Graph& G, int v);
void AddEdge(Graph& G) {
    for (int o = 1; o <= G.arcnum; o++) {
        int a, b;
        cin >> a >> b;
        ArcNode* edge1 = (ArcNode*)malloc(sizeof(ArcNode)); edge1->next = NULL;
        ArcNode* edge2 = (ArcNode*)malloc(sizeof(ArcNode)); edge2->next = NULL;
 
        edge1->adjvex = b;
        edge2->adjvex = a;
 
        if (G.vertices[a].first == NULL) {
            G.vertices[a].first = edge1;
        }
        if (G.vertices[b].first == NULL) {
            G.vertices[b].first = edge2;
        }
        if (G.vertices[a].tail != NULL) {
            G.vertices[a].tail->next = edge1;
            G.vertices[a].tail = edge1;
        }
        else if (G.vertices[a].tail == NULL) {
            G.vertices[a].tail = edge1;
        }
        if (G.vertices[b].tail != NULL) {
            G.vertices[b].tail->next = edge2;
            G.vertices[b].tail = edge2;
        }
        else if (G.vertices[b].tail == NULL) {
            G.vertices[b].tail = edge2;
        }
 
    }
}
bool vis[MaxVertexNum];
void BFSTraverse(Graph& G) {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= G.vexnum; i++) {
        memset(vis, 0, sizeof(vis));
        BFS(G, i);
    }
}
 
 
void BFS(Graph& G, int v) {
    queue<int>q[7];
    int level1 = 0, level2 = 1, sum = 1;
    q[0].push(v); vis[v] = 1;
    while (level2 <= 6) {
        while (!q[level1].empty()) {
            int tp = q[level1].front();
            q[level1].pop();
            for (ArcNode* w = G.vertices[tp].first; w != NULL; w = w->next) {
                if (!vis[w->adjvex]) {
                    vis[w->adjvex] = 1;
                    q[level2].push(w->adjvex);
                }
            }
        }
        sum += q[level2].size();
        level1++; level2++;
    }
    G.vertices[v].data = (float)(sum*100) / (float)(G.vexnum);
}
void print(Graph G) {
    for (int i = 1; i <= G.vexnum; i++) {
        printf("%d: %.2f", i , G.vertices[i].data);
        cout << "%" << endl;
    }
}
int main() {
    Graph G;
    cin >> G.vexnum >> G.arcnum;
    Initial(G);
    AddEdge(G);
    BFSTraverse(G);
    print(G);
}