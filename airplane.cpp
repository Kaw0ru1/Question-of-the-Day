/*
 * 飞机 — 牛客网 NC310831
 *
 * 题目描述：
 *   一个「飞机」有恰好 10 张牌：
 *     - 两组连续的三张相同牌：{a,a,a, a+1,a+1,a+1}
 *     - 两组两张相同牌：{b,b, c,c}
 *   给定 n 张牌，求能组成多少种不同的「飞机」（可重集合不同才算不同）。
 *   答案对 998244353 取模。
 *
 * 解法：
 *   枚举 a（连续三张的起始值），要求 cnt[a]≥3, cnt[a+1]≥3。
 *   两个 pair 从「能力池」中选取：
 *     - 能出一个 pair 的值：cnt[v] ≥ 2，但如果 v 是 a 或 a+1 且 cnt[v] 只有 3~4
 *       （不够同时做 triplet+pair），则需要排除
 *     - 能出两个 pair 的值（b=c）：cnt[v] ≥ 4，但 v 是 a 或 a+1 时需要 cnt[v] ≥ 7
 *   C(x1, 2) 从池中选 2 个不同值各出一个 pair，x2 选 1 个值出两个 pair。
 */

#include <iostream>
using namespace std;
using ll = long long;

const int N = 200020;
const int MOD = 998244353;
int cnt[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    int maxn = 0;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        cnt[x]++;
        maxn = max(maxn, x);
    }

    // 全局统计：能出 2 张牌 / 能出 4 张牌（两个 pair 同值）的值有几个
    int f1 = 0, f2 = 0;
    for (int i = 1; i <= maxn; i++) {
        if (cnt[i] >= 2) f1++;
        if (cnt[i] >= 4) f2++;
    }

    ll res = 0;
    for (int i = 1; i < maxn; i++) {
        if (cnt[i] >= 3 && cnt[i + 1] >= 3) {
            // 排除不够同时做 triplet+pair 的值
            // x1: 能出一个 pair 的值（cnt≥2，且如果用在 triplet 位上需要 cnt≥5）
            int x1 = f1 - (cnt[i] < 5) - (cnt[i + 1] < 5);
            // x2: 能出两个 pair 同值的值（cnt≥4，且如果用在 triplet 位上需要 cnt≥7）
            int x2 = f2 - (cnt[i] >= 4 && cnt[i] < 7) - (cnt[i + 1] >= 4 && cnt[i + 1] < 7);

            res = (res + (ll)x1 * (x1 - 1) / 2 + x2) % MOD;
        }
    }

    cout << res << '\n';
    return 0;
}
