/*
 * [SCOI2005]骑士精神 — 牛客网 NC20247
 * 难度：较难    算法：IDA* / 迭代加深 / 启发式搜索
 * 链接：https://ac.nowcoder.com/acm/problem/20247
 *
 * 一句话：5×5 棋盘骑士归位，15 步内最少步数（IDA*）。
 *
 * 题目描述：
 *   一个 5×5 棋盘上有 12 个白骑士和 12 个黑骑士，且有一个空位。
 *   骑士按「日」字走法移动（横纵坐标分别相差 1 和 2），
 *   任何时刻骑士都可以走到空位上。
 *   给定初始棋盘，求经过移动变成目标棋盘的最少步数。
 *   目标棋盘：
 *     11111
 *     01111
 *     00*11
 *     00001
 *     00000
 *   （0 为白骑士，1 为黑骑士，* 为空位）
 *
 * 输入格式：
 *   第一行一个正整数 T（T ≤ 10），表示数据组数。
 *   接下来 T 个 5×5 矩阵，0 表示白骑士，1 表示黑骑士，* 表示空位。
 *   两组数据之间没有空行。
 *
 * 输出格式：
 *   每组数据输出一行。若能在 15 步以内（含 15 步）到达目标，输出步数；
 *   否则输出 -1。
 *
 * 约束：
 *   T ≤ 10，棋盘固定 5×5，限 15 步
 *
 * 解法：
 *   IDA*（迭代加深 + A* 剪枝）。
 *
 *   启发函数 h = 当前状态中与目标位置不同的格子数（空位不计）。
 *   每走一步最多只能把一个错位棋子归位，所以 h 是到达目标所需步数的
 *   一个下界 → 剪枝条件 d + h > maxd 时必然无解，直接剪掉。
 *
 *   实现细节：
 *   - 每次移动本质是「空位」与棋子交换，递归时记录上一步的空位，
 *     避免来回走回头路。
 *   - 移动后增量更新 h（只重算涉及的两个格子），避免 O(25) 重扫。
 *   - 迭代加深枚举深度上限 maxd = 1..15，找到的第一个可行深度即答案。
 *   - 初始即目标时输出 0。
 */

#include <iostream>
#include <algorithm>
using namespace std;

const char target[5][6] = {
    "11111",
    "01111",
    "00*11",
    "00001",
    "00000"
};

int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

char board[5][6];

bool dfs(int x, int y, int d, int maxd, int h, int px, int py) {
    if (d + h > maxd) return false;
    if (h == 0) return true;

    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;
        if (nx == px && ny == py) continue; // 避免走回头路

        char c = board[nx][ny];
        int new_h = h;

        // 减去原位置的错位贡献
        if (target[x][y] != '*') new_h -= 1; // 原 (x,y) 是空位，贡献 1
        if (target[nx][ny] != '*' && c != target[nx][ny]) new_h -= 1; // 原 (nx,ny) 棋子错位

        // 加上新位置的错位贡献
        if (target[x][y] != '*' && c != target[x][y]) new_h += 1; // 新 (x,y) 的棋子是否错位
        if (target[nx][ny] != '*') new_h += 1; // 新 (nx,ny) 是空位，贡献 1

        // 交换空位与棋子
        swap(board[x][y], board[nx][ny]);

        if (dfs(nx, ny, d + 1, maxd, new_h, x, y)) {
            return true;
        }

        // 回溯
        swap(board[x][y], board[nx][ny]);
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int sx = 0, sy = 0;
        for (int i = 0; i < 5; ++i) {
            cin >> board[i];
            for (int j = 0; j < 5; ++j) {
                if (board[i][j] == '*') {
                    sx = i;
                    sy = j;
                }
            }
        }

        // 计算初始错位数量 h
        int h = 0;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (target[i][j] != '*' && board[i][j] != target[i][j]) {
                    h++;
                }
            }
        }

        if (h == 0) {
            cout << 0 << endl;
            continue;
        }

        int ans = -1;
        for (int maxd = 1; maxd <= 15; ++maxd) {
            if (dfs(sx, sy, 0, maxd, h, -1, -1)) {
                ans = maxd;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
