#include<iostream>
#include<cstring>
#include<queue>
#include<stack>
using namespace std;
#define MaxVertexNum 2011//图中顶点数目的最大值
typedef struct ArcNode {//边
    int adjvex;//该弧所指向的顶点的位置 
    int weight;
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
typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii>>q;
int H[1200], R[1200];//H个有牧草的点
int r, h;//小马的数量 有牧草的点 
int way[1100][1100] = { 0 }; //way[i][j]i点到j点的最短路 
bool vis[MaxVertexNum];
 
void Initial(Graph& G) {//图的所有顶点的first和tail都指向空
    for (int i = 1; i <= G.vexnum; i++) {
        G.vertices[i].first = NULL;
        G.vertices[i].tail = NULL;
    }
    memset(way, 0x3f3f3f3f, sizeof(way));
}
void AddEdge(Graph& G) {
    for (int o = 1; o <= G.arcnum; o++) {
        int a, b, w;
        cin >> a >> b >> w;
        ArcNode* edge1 = (ArcNode*)malloc(sizeof(ArcNode)); edge1->next = NULL;
        ArcNode* edge2 = (ArcNode*)malloc(sizeof(ArcNode)); edge2->next = NULL;
 
        edge1->adjvex = b;
        edge2->adjvex = a;
        edge1->weight = w;
        edge2->weight = w;
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
 
void dijkstra(Graph G, int s) {
    //node[s].dist = 0;
    memset(vis, 0, sizeof(vis));
    way[s][s] = 0;
    q.push({ way[s][s],s });// // first存储距离，second存储节点编号
    while (!q.empty()) {
        pii tp = q.top();
        q.pop();
        int x = tp.second;
        if (vis[x])continue;
        vis[x] = 1;
        for (ArcNode* w = G.vertices[x].first; w != NULL; w = w->next) {
            int y = w->adjvex;
            int dnew = way[s][x] + w->weight;
            if (dnew < way[s][y]) {
                way[s][y] = dnew;
                q.push({ way[s][y],y });
            }
 
        }
 
    }
}
int main(){
    Graph G;
    cin >> G.vexnum >> G.arcnum;//点和边的数量 
    Initial(G);
    AddEdge(G);
    cin >> h >> r;
    for (int i = 1; i <= h; i++) {
        cin >> H[i];//有牧草的点 对于每一个牧草，去搜它到每一个点的最小路径 
        dijkstra(G, H[i]);//搜了之后得到所有最短路 
    }
    //对于每一个起点和终点：
    for (int o = 1; o <= r; o++) {
        int st, end; cin >> st >> end;
        int temp = 0x3f3f3f3f;
    
        for (int j = 1; j <= h; j++) {
            temp = min(temp, way[H[j]][end]+way[H[j]][st]);
        }
            cout << temp << endl;
    }
}