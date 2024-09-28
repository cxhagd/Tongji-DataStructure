#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include<string.h>
using namespace std;
struct zzz {
    int t, nex;
}e[1011 << 1]; int head[1011], tot;
void add(int x, int y) {
    e[++tot].t = y;
    e[tot].nex = head[x];
    head[x] = tot;
}
 
int depth[1011], fa[1011][22], lg[1011];
void dfs(int now, int fath) {
    fa[now][0] = fath; depth[now] = depth[fath] + 1;
    for (int i = 1; i <= lg[depth[now]]; ++i)
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (int i = head[now]; i; i = e[i].nex)
        if (e[i].t != fath) dfs(e[i].t, now);
}
int LCA(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);
    while (depth[x] > depth[y])
        x = fa[x][lg[depth[x] - depth[y]] - 1];
    if (x == y) return x;
    for (int k = lg[depth[x]] - 1; k >= 0; --k)
        if (fa[x][k] != fa[y][k])
            x = fa[x][k], y = fa[y][k];
    return fa[x][0];
}
 
bool ro[1011] = { 1 };
int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        memset(head, 0, sizeof(head));
        memset(depth, 0, sizeof(depth));
        memset(fa, 0, sizeof(fa));
        memset(&e, 0, sizeof(struct zzz));
        tot = 0;
        memset(ro, 1, sizeof(ro));
        int n, m, s; cin >> n >> m;
    
        for (int i = 1; i <= n - 1; ++i) {
            int a, b; cin >> a >> b;
            if (a >= 1 && b >= 1) {
                add(a, b); add(b, a);
                ro[b] = 0;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (ro[i]) {
                s = i;
                break;
            }
        }
        for (int i = 1; i <= n; ++i)
            lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
        dfs(s, 0);
        for (int i = 1; i <= m; ++i) {
            int x, y; cin >> x >> y;
            printf("%d\n", LCA(x, y));
        }
    }
    return 0;
}