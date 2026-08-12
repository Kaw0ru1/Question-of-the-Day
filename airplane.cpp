/*
 * 飞机 — 牛客网 NC310831
 * 链接：https://ac.nowcoder.com/acm/problem/310831
 *
 * 题目描述：
 *   一个「飞机」有恰好 10 张牌：
 *     - 两组连续的三张相同牌：{a,a,a, a+1,a+1,a+1}
 *     - 两组两张相同牌：{b,b, c,c}
 *   求能组成多少种不同的「飞机」（可重集合不同才算不同）。
 *
 * 解法：
 *   枚举三元组起始值 a，要求 cnt[a]≥3, cnt[a+1]≥3。
 *   扣除 triplet 所用后，用 delta 调整各值的「能力池」再组合计数。
 */

#include <iostream>
using namespace std;

const int MOD = 998244353;
const int inv2 = 499122177;  // 2 在模 998244353 下的逆元
const int MAXN = 200010;

int cnt[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        cnt[x]++;
    }

    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i < MAXN; ++i) {
        if (cnt[i] >= 2) cnt1++;
        if (cnt[i] >= 4) cnt2++;
    }

    long long ans = 0;
    for (int a = 1; a < MAXN - 1; ++a) {
        if (cnt[a] >= 3 && cnt[a + 1] >= 3) {
            // a 的 delta：扣 3 张 triplet 后，还能不能出 1 个/2 个对子
            int old1a = (cnt[a] >= 2) ? 1 : 0;
            int old2a = (cnt[a] >= 4) ? 1 : 0;
            int new1a = (cnt[a] >= 5) ? 1 : 0;
            int new2a = (cnt[a] >= 7) ? 1 : 0;
            int d1a = new1a - old1a;
            int d2a = new2a - old2a;

            // a+1 的 delta
            int old1b = (cnt[a + 1] >= 2) ? 1 : 0;
            int old2b = (cnt[a + 1] >= 4) ? 1 : 0;
            int new1b = (cnt[a + 1] >= 5) ? 1 : 0;
            int new2b = (cnt[a + 1] >= 7) ? 1 : 0;
            int d1b = new1b - old1b;
            int d2b = new2b - old2b;

            int t1 = cnt1 + d1a + d1b;
            int t2 = cnt2 + d2a + d2b;

            long long comb = 0;
            if (t1 >= 2) {
                comb = 1LL * t1 * (t1 - 1) % MOD;
                comb = comb * inv2 % MOD;
            }
            ans = (ans + comb + t2) % MOD;
        }
    }

    cout << ans % MOD << endl;
    return 0;
}
