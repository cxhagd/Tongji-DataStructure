#include<iostream>
#include<algorithm>
using namespace std;
 
#define MaxVertexNum 100
constexpr auto MaxEdgeNum = 11000;
typedef int VertexType;
typedef int EdgeType;//边的内容是边权 
typedef struct {
    int n1, n2;
    int weight;
    bool vis;
}Edge;
typedef struct {
    VertexType vex[MaxVertexNum];//这里是fa 
    Edge edge [MaxEdgeNum];
    int vexnum, arcnum;
}MGraph;
 
MGraph G;
bool cmp(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}
int m;
int find(int x) {
    if (G.vex[x] != x) {
        G.vex[x] = find(G.vex[x]);
    }
    return G.vex[x];
}
void unity(int x, int y) {
    G.vex[find(x)] = find(y);
}
int main() {
 
    cin >> G.vexnum;
    
    for (int i = 1,o=1; i <= G.vexnum; i++) {
        for (int j = 1; j <= G.vexnum; j++) {
            cin >> G.edge[o].weight; G.edge[o].n1 = i; G.edge[o].n2 = j;
            o++;
        }
    }
    for (int i = 1; i <= G.vexnum; i++) {
        G.vex[i] = i;
    }
    sort(&G.edge[1], &G.edge[G.vexnum*G.vexnum + 1], cmp);
    cin >> m;
 
    for (int i = 1; i <= m; i++) {
        int a, b; cin >> a >> b;
        for (int j = 1; j <= G.vexnum * G.vexnum; j++) {
            if ((G.edge[j].n1 == a && G.edge[j].n2 == b) || (G.edge[j].n1 == b && G.edge[j].n2 == a)) {
                G.edge[j].vis = true; unity(a, b); break;
            }
        }
 
    }
    int ans = 0;
    for (int i = 1; i <= G.vexnum * G.vexnum; i++) {
        if (find(G.edge[i].n1) != find(G.edge[i].n2)) {
            unity(G.edge[i].n1, G.edge[i].n2);
            ans += G.edge[i].weight;
        }
    }
    cout << ans << endl;
 
}