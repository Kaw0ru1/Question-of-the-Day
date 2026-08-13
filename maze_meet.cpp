/*
 * 迷宫相遇 — 牛客网 NC23486
 * 难度：中等    算法：BFS / 最短路
 * 链接：https://ac.nowcoder.com/acm/problem/23486
 *
 * 一句话：两人不同速度在迷宫中的最早相遇时间。
 *
 * 题目描述：
 *   小A和小B被困在迷宫中，想找到对方。
 *   小A每次 1 步，8 方向（上下左右 + 对角线）
 *   小B每次 2 步，4 方向（上下左右）
 *   求最早相遇时间，不能相遇则输出 NO。
 *
 * 约束：
 *   N, M ≤ 1000
 *
 * 解法：
 *   双向 BFS 分别计算两人到每个格子的最短步数。
 *   小B 一次走 2 步，所以实际时间 = ceil(步数 / 2)。
 *   枚举所有格子，若两人都能到达，则相遇时间 = max(A时间, B时间)。（核心思路）
 *   取所有格子的最小值。
 */

#include <iostream>
#include <queue>
#include <climits>
using namespace std;

const int MAXN = 1005;
char mp[MAXN][MAXN];
int distA[MAXN][MAXN], distB[MAXN][MAXN];
int n, m;

int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int dx4[] = {-1, 1, 0, 0};
int dy4[] = {0, 0, -1, 1};

void bfs(int sx, int sy, int dx[], int dy[], int dir_cnt, int dist[][MAXN]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist[i][j] = -1;

    queue<pair<int, int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int i = 0; i < dir_cnt; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m
                && mp[nx][ny] != '#'
                && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    int cx, cy, dx, dy;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mp[i][j];
            if (mp[i][j] == 'C') cx = i, cy = j;
            else if (mp[i][j] == 'D') dx = i, dy = j;
        }
    }

    bfs(cx, cy, dx8, dy8, 8, distA);
    bfs(dx, dy, dx4, dy4, 4, distB);

    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (distA[i][j] != -1 && distB[i][j] != -1) {
                int timeB = (distB[i][j] + 1) / 2;
                int t = max(distA[i][j], timeB);
                ans = min(ans, t);
            }
        }
    }

    if (ans == INT_MAX) cout << "NO\n";
    else cout << "YES\n" << ans << '\n';

    return 0;
}
