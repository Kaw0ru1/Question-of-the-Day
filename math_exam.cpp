/*
 * 数学考试 — 牛客网 NC15553
 * 难度：简单    算法：前缀和 / 枚举
 * 链接：https://ac.nowcoder.com/acm/problem/15553
 *
 * 一句话：选 2 个不重叠、长度均为 k 的区间，使分数之和最大。
 *
 * 题目描述：
 *   qwb 参加数学考试，试卷共 n 道题，第 i 题得分 a[i]。
 *   他想选 2 个不连续的长度为 k 的区间：
 *     [L, L+1, ..., L+k-1] 和 [R, R+1, ..., R+k-1]（R >= L+k）
 *   求这两个区间分数之和的最大值。
 *
 * 输入格式：
 *   第一行一个整数 T（T <= 10），表示数据组数。
 *   每组数据：
 *     第一行两个整数 n, k（2 <= n <= 200000，1 <= k，2k <= n）
 *     第二行 n 个整数 a1, a2, ..., an（-100000 <= ai <= 100000）
 *
 * 输出格式：
 *   每组输出一个整数，表示能获得的最大分数。
 *
 * 约束：
 *   T ≤ 10，2 ≤ n ≤ 200000，1 ≤ k，2k ≤ n，-100000 ≤ ai ≤ 100000
 *
 * 解法：
 *   前缀和预处理，O(1) 求任意长度为 k 的区间和。
 *   枚举第二个区间的起点 j（从 k+1 开始，保证与第一个区间不重叠），
 *   同时维护左侧所有合法「第一个区间」的最大和 left_max，
 *   则 ans = max(ans, left_max + 第二个区间和)。
 *   时间复杂度 O(n)，每组数据线性扫一遍。
 */

#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 10;
const ll INF = 1e18;

ll a[MAXN], s[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        // 前缀和
        s[0] = 0;
        for (int i = 1; i <= n; ++i) {
            s[i] = s[i - 1] + a[i];
        }
        int m = n - k + 1;   // 长度为 k 的区间的总个数（起点范围 1..m）
        ll left_max = -INF;  // 左侧合法「第一个区间」的最大和
        ll ans = -INF;
        // 枚举第二个区间的起点 j
        for (int j = k + 1; j <= m; ++j) {
            int idx = j - k;  // 新纳入考虑的第一个区间起点
            ll sum_idx = s[idx + k - 1] - s[idx - 1];
            left_max = max(left_max, sum_idx);          // 更新左侧最大值
            ll sum_j = s[j + k - 1] - s[j - 1];         // 第二个区间和
            ans = max(ans, left_max + sum_j);           // 更新全局答案
        }
        cout << ans << '\n';
    }
    return 0;
}
