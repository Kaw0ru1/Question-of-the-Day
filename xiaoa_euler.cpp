/*
 * 小A与欧拉路 — 牛客网 NC22618
 * 难度：中等    算法：树的直径 / BFS / 欧拉路
 * 链接：https://ac.nowcoder.com/acm/problem/22618
 *
 * 一句话：每条边复制任意次求最短欧拉路 = 2×边权和 − 树的直径。
 *
 * 题目描述：
 *   小A给了一棵树，对每条边都可以复制任意次（可以为 0），
 *   即在这条边连接的两个点之间再加一条边权相同的边。
 *   求所有可能新形成的图中「欧拉路」的最短长度。
 *
 *   欧拉路：从图中任意一点开始到任意一点结束的路径，
 *   且图中每条边只通过恰好一次。
 *
 * 输入格式：
 *   第一行一个数 n，表示节点个数。
 *   接下来 n-1 行，每行三个整数 u, v, w，表示 u 到 v 有一条边权为 w 的无向边。
 *   保证数据是一棵树。
 *
 * 输出格式：
 *   一行一个整数，表示答案。
 *
 * 约束：
 *   1 ≤ n ≤ 2×10^5，1 ≤ w ≤ 10^4
 *
 * 解法：
 *   结论：答案 = 2 × Σw − 树的直径。
 *
 *   直观理解：
 *   - 若要求欧拉回路（起点 = 终点），每条边都要走两次，长度 = 2×Σw。
 *   - 欧拉路允许起点 ≠ 终点，等价于从「欧拉回路」中去掉一段连续的回程，
 *     省掉的长度应尽量长 → 去掉树上最长的一条简单路径，即树的直径。
 *
 *   实现：
 *   - 两次 BFS 求树的直径：任选起点 bfs 得最远点 u，
 *     再从 u bfs 得最远距离即为直径（边权为 w，需累计权值）。
 *   - 注意 w 可达 1e4、n 可达 2e5，直径与答案要开 long long。
 *
 *   时间复杂度 O(n)。
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii; // first: 邻接点, second: 边权

int n;
vector<vector<pii>> adj;

// 从 start 出发，返回 (最远距离, 最远节点编号)
pair<ll, int> bfs(int start) {
    vector<ll> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] == -1) { // 树无环，只需避免走回父节点
                dist[v] = dist[u] + w;
                q.push(v);
            }
        }
    }

    ll max_dist = -1;
    int far_node = start;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] > max_dist) {
            max_dist = dist[i];
            far_node = i;
        }
    }
    return {max_dist, far_node};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    adj.resize(n + 1);
    ll sum = 0;

    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
        sum += w;
    }

    // 两次 BFS 求直径
    auto [_, u] = bfs(1);
    auto [diameter, __] = bfs(u);

    ll ans = 2 * sum - diameter;
    cout << ans << endl;

    return 0;
}
