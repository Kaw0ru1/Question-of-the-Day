/*
 * 筱玛爱线段树 — 牛客网 NC25737
 * 难度：中等    算法：树状数组 / 差分 / 倒序处理
 * 链接：https://ac.nowcoder.com/acm/problem/25737
 *
 * 一句话：倒序求出每个操作的执行次数，再用差分算出最终数组。
 *
 * 题目描述：
 *   给定一个长度为 n 的数组 A，初始每一项均为 0。
 *   支持两种操作，共 m 次：
 *     1 l r：将 A[l] ~ A[r] 每一项的值加 1
 *     2 l r：执行操作编号在 [l, r] 内的所有操作各一次（保证 r 小于当前操作编号）
 *   m 次操作结束后，输出 A 数组中每个数在模 1e9+7 意义下的值。
 *
 * 输入格式：
 *   第一行两个数 n, m，分别表示数组长度及操作次数。
 *   接下来 m 行，每行三个数 opt, l, r，表示一次操作。
 *
 * 输出格式：
 *   一行共 n 个数，表示 m 次操作结束后 A[1] ~ A[n] 的值。
 *
 * 约束：
 *   1 ≤ n ≤ 1e5，1 ≤ m ≤ 1e5
 *
 * 解法：
 *   倒序思维 + 差分（两棵差分结构）。
 *
 *   关键点：操作 2 只引用「当前之前」的操作，且 r < 当前编号，
 *   所以每个操作的执行次数只被后面（编号更大）的操作 2 决定。
 *   因此从 m 到 1 倒序遍历：
 *     - 第 m 个操作一定执行 1 次（差分数组初始 d[1] = 1 表示前缀均 +1）。
 *     - 遇到操作 2，它引用的 [l, r] 内操作各增加「当前操作的执行次数」。
 *     - 遇到操作 1，将它的执行次数累加到数组 A 的差分上。
 *   执行次数用一棵 BIT（差分区间加、单点查询）维护；
 *   最终 A 用普通差分数组前缀和得到。
 *
 *   时间复杂度 O((n + m) log m)。
 */

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

// 树状数组：支持区间加、单点查询（维护差分数组）
struct BIT {
    int n;
    vector<long long> tree;

    BIT(int size) : n(size), tree(size + 2, 0) {}

    void update(int idx, long long x) {
        x %= MOD;
        if (x < 0) x += MOD;
        while (idx <= n) {
            tree[idx] = (tree[idx] + x) % MOD;
            idx += idx & -idx;
        }
    }

    long long query(int idx) {
        long long res = 0;
        while (idx > 0) {
            res = (res + tree[idx]) % MOD;
            idx -= idx & -idx;
        }
        return res;
    }
};

struct Op {
    int opt, l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Op> ops(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> ops[i].opt >> ops[i].l >> ops[i].r;
    }

    BIT bit(m);
    bit.update(1, 1); // 初始每个操作执行 1 次，差分数组 d[1] = 1

    vector<long long> cnt(m + 1);
    // 倒序计算每个操作的执行次数
    for (int i = m; i >= 1; --i) {
        cnt[i] = bit.query(i);
        if (ops[i].opt == 2) {
            int l = ops[i].l;
            int r = ops[i].r;
            bit.update(l, cnt[i]);
            bit.update(r + 1, -cnt[i]);
        }
    }

    // 差分数组计算最终 A 数组
    vector<long long> d(n + 2, 0);
    for (int i = 1; i <= m; ++i) {
        if (ops[i].opt == 1) {
            int l = ops[i].l;
            int r = ops[i].r;
            d[l] = (d[l] + cnt[i]) % MOD;
            d[r + 1] = (d[r + 1] - cnt[i] + MOD) % MOD;
        }
    }

    // 前缀和得到结果并输出
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum = (sum + d[i]) % MOD;
        cout << sum << " ";
    }
    cout << endl;

    return 0;
}
