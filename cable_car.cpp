/*
 * 缆车观光 — 牛客网 NC23482
 *
 * 题目描述：
 *   N 个景点构成一棵树（N-1 条边），每条边消耗 1 体力。
 *   有两个特殊景点 U,V 之间有缆车直达，消耗 0 体力。
 *   Q 次询问，每次问 x→y 的最小体力消耗。
 *
 * 约束：1 ≤ N ≤ 3×10^5, 1 ≤ Q ≤ 1×10^6
 *
 * 解法：
 *   树上任意两点距离：dist(a,b) = depth[a] + depth[b] - 2*depth[lca(a,b)]
 *   考虑缆车(U,V)后，x→y 有三种走法：
 *     1. 不走缆车：dist(x, y)
 *     2. 走 U→V：  dist(x, U) + 0 + dist(V, y)
 *     3. 走 V→U：  dist(x, V) + 0 + dist(U, y)
 *   取三者最小值。
 *
 *   实现：
 *   - 倍增 LCA（O(N log N) 预处理，O(log N) 每次询问）
 *   - BFS 预处理所有点到 U 和 V 的距离（O(N)）
 *   - 快速读入/输出应对 Q=1e6
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 300005;
const int LOG = 20;

vector<int> adj[MAXN];
int fa[LOG][MAXN];
int depth[MAXN];
int disU[MAXN], disV[MAXN];
int N, U, V, Q;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * f;
}

inline void write(int x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

void bfs_lca(int root) {
    queue<int> q;
    q.push(root);
    fa[0][root] = 0;
    depth[root] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (v != fa[0][u]) {
                fa[0][v] = u;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }
    for (int k = 1; k < LOG; ++k)
        for (int i = 1; i <= N; ++i)
            fa[k][i] = fa[k - 1][fa[k - 1][i]];
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int k = 0; k < LOG; ++k)
        if (diff >> k & 1) u = fa[k][u];
    if (u == v) return u;
    for (int k = LOG - 1; k >= 0; --k)
        if (fa[k][u] != fa[k][v])
            u = fa[k][u], v = fa[k][v];
    return fa[0][u];
}

int dist(int u, int v) {
    int anc = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[anc];
}

void bfs_dist(int start, int dis[]) {
    fill(dis, dis + N + 1, -1);
    queue<int> q;
    q.push(start);
    dis[start] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u])
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
    }
}

int main() {
    N = read();
    for (int i = 0; i < N - 1; ++i) {
        int u = read(), v = read();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    U = read(), V = read();

    bfs_lca(1);
    bfs_dist(U, disU);
    bfs_dist(V, disV);

    Q = read();
    while (Q--) {
        int x = read(), y = read();
        int d1 = dist(x, y);
        int d2 = disU[x] + disV[y];
        int d3 = disV[x] + disU[y];
        int ans = min(d1, min(d2, d3));
        write(ans);
        putchar('\n');
    }
    return 0;
}
