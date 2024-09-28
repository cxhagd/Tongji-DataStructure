#include<iostream>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#include<set>
#include <utility>
 
using namespace std;
#define MaxVertexNum 2011//图中顶点数目的最大值
 
typedef struct VNode {//顶点 
    int indegree;//入度 
    vector<int>adj;//出去的点 
    int num;
}Vnode;
typedef struct {
    Vnode vex[MaxVertexNum];//
    int vexnum, arcnum;//图的顶点数和弧数 
}Graph; //ALGraph是以邻接表存储的图的类型 
void AddEdge(Graph& G, int x, int y) {
    G.vex[y].indegree++;
    G.vex[x].adj.push_back(y);//x到y有一条边 
}
Graph Grow, Gcol; int k, n, m;
int pos[1000][1000] = { 0 };
int main() {
 
    cin >> k >> n >> m; Grow.arcnum = n; Gcol.arcnum = m;
    set<pair<int, int>> setrow; set<pair<int, int>> setcol;
    for (int o = 1; o <= n; o++) {
        int x; int y; cin >> x >> y; pair<int, int>a(x, y);
        if (!setrow.count(a)) {
            setrow.insert(a);
            AddEdge(Grow, x, y);
        }
    }
 
    for (int o = 1; o <= m; o++) {
        int x; int y; cin >> x >> y; pair<int, int>a(x, y);
        if (!setcol.count(a)) {
            setcol.insert(a);
            AddEdge(Gcol, x, y);
        }
    }
 
    int countrow = 0, countcol = 0;
    queue<int>qrow, qcol;
    for (int i = 1; i <= k; i++) {
        if (Grow.vex[i].indegree == 0) {
            qrow.push(i);
            Grow.vex[i].num = ++countrow;
        }
    }
    for (int i = 1; i <= k; i++) {
        if (Gcol.vex[i].indegree == 0) {
            qcol.push(i);
            Gcol.vex[i].num = ++countcol;
        }
    }
 
    while (!qrow.empty()) {
        int temp = qrow.front();
        qrow.pop();
        for (int i = 0; i < Grow.vex[temp].adj.size(); i++) {
            if (--Grow.vex[Grow.vex[temp].adj[i]].indegree == 0) {
                qrow.push(Grow.vex[temp].adj[i]);
                Grow.vex[Grow.vex[temp].adj[i]].num = ++countrow;
            }
        }
    }
    while (!qcol.empty()) {
        int temp = qcol.front();
        qcol.pop();
        for (int i = 0; i < Gcol.vex[temp].adj.size(); i++) {
            if (--Gcol.vex[Gcol.vex[temp].adj[i]].indegree == 0) {
                qcol.push(Gcol.vex[temp].adj[i]);
                Gcol.vex[Gcol.vex[temp].adj[i]].num = ++countcol;
            }
        }
    }
    if (countrow != k || countcol != k) {
        cout << -1 << endl;
        return 0;
    }
    for (int i = 1; i <= k; i++) {
        pos[Grow.vex[i].num][Gcol.vex[i].num] = i;
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            cout << pos[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}