/*
 * 最小质因子求和 — 牛客网 NC53079
 * 链接：https://ac.nowcoder.com/acm/problem/53079
 *
 * 题目描述：
 *   f(x) = x 的最小质因子（若无则返回 0，即 f(1) = 0）
 *   求 Σ f(i)  (i = 1..n)
 *
 * 约束：1 ≤ n ≤ 3×10^7
 *
 * 解法：
 *   欧拉线性筛（Euler Sieve）O(n) 预处理每个数的最小质因子。
 *   核心：每个合数只被其最小质因子筛掉一次。
 *
 *   筛法不变式：
 *     minp[i] = i 的最小质因子（i 为质数时等于 i）
 *     遍历质数 p：if p > minp[i] || i * p > n → break
 *     标记 minp[i * p] = p
 *
 *   最后累加所有 minp[i] 即可（需用 long long，n=3e7 时答案超 32 位）。
 */

#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int MAXN = 3e7 + 5;
int minp[MAXN];
vector<int> primes;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    minp[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if (!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > minp[i] || 1LL * i * p > n) break;
            minp[i * p] = p;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; ++i) ans += minp[i];
    cout << ans << '\n';

    return 0;
}
