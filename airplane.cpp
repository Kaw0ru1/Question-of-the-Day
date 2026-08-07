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
 * 输入：
 *   第一行 n (1 ≤ n ≤ 2×10^5)
 *   第二行 n 个整数 a_i (1 ≤ a_i ≤ 2×10^5)
 *
 * 解法：
 *   枚举 a（连续三张的起始值），要求 cnt[a]≥3, cnt[a+1]≥3。
 *   对于每对 (b,c) b≤c，检查是否能从 cnt 中取出对应数量的牌。
 *   不同飞机 = 不同的可重集合 = 不同的 (a, b, c) 三元组。
 *
 *   分类计数：
 *     1. b<c, b,c 均 ∉ {a,a+1}: C(|P2|-2, 2)
 *     2. b=a, c∉{a,a+1} 或 c=a, b∉{a,a+1}: 2*(a∈P5)*(|P2|-2)
 *     3. b=a+1, c∉{a,a+1} 或 c=a+1, b∉{a,a+1}: 2*(a+1∈P5)*(|P2|-2)
 *     4. b=a, c=a+1: (a∈P5 && a+1∈P5)
 *     5. b=c∉{a,a+1}: |P4| - [a∈P4] - [a+1∈P4]
 *     6. b=c=a: (a∈P7)
 *     7. b=c=a+1: (a+1∈P7)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200000;
const int MOD = 998244353;

int cnt[MAXV + 5];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    int maxVal = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
        maxVal = max(maxVal, x);
    }

    // 统计满足条件的值的个数
    int p2 = 0, p4 = 0;  // cnt≥2, cnt≥4
    for (int v = 1; v <= maxVal; v++) {
        if (cnt[v] >= 2) p2++;
        if (cnt[v] >= 4) p4++;
    }

    long long ans = 0;

    for (int a = 1; a < maxVal; a++) {
        if (cnt[a] < 3 || cnt[a + 1] < 3) continue;

        int out2 = p2 - 2;  // 排除 a, a+1 后 cnt≥2 的个数
        int out4 = p4 - (cnt[a] >= 4) - (cnt[a + 1] >= 4);

        bool p5a = (cnt[a] >= 5);
        bool p5a1 = (cnt[a + 1] >= 5);
        bool p7a = (cnt[a] >= 7);
        bool p7a1 = (cnt[a + 1] >= 7);

        // 情况 1: b<c, b,c ∉ {a,a+1}
        if (out2 >= 2) {
            ans += (long long)out2 * (out2 - 1) / 2;
        }
        // 情况 2 & 3: 一个 pair 在 triplet 值上
        if (p5a) ans += 2LL * out2;
        if (p5a1) ans += 2LL * out2;
        // 情况 4: b=a, c=a+1
        if (p5a && p5a1) ans++;
        // 情况 5: b=c ∉ {a,a+1}
        ans += out4;
        // 情况 6 & 7: b=c=a 或 b=c=a+1
        if (p7a) ans++;
        if (p7a1) ans++;

        ans %= MOD;
    }

    cout << ans % MOD << '\n';
    return 0;
}
