/*
 * 区区区间 — 牛客网 NC200195
 * 难度：中等    算法：线段树 / 懒标记
 * 链接：https://ac.nowcoder.com/acm/problem/200195
 *
 * 一句话：区间替换为等差数列 + 区间求和，懒标记只记偏移量。
 *
 * 题目描述：
 *   Keven 特别喜欢线段树，给一个长度为 n 的序列，进行 m 次操作。
 *   操作有两种：
 *     1 l r k：将下标在 [l, r] 区间内的数字替换成
 *              [k, k+1, ..., k+r-l]（公差为 1 的等差数列）
 *     2 l r：查询区间 [l, r] 的区间和
 *
 * 输入格式：
 *   第一行两个整数 n, m。
 *   第二行 n 个整数，表示序列初始值 a[1] ~ a[n]。
 *   接下来 m 行，每行三或四个数字；第一个数字为 1 表示操作 1，否则为操作 2。
 *
 * 输出格式：
 *   对于每个操作 2，输出一行一个整数表示区间和。
 *
 * 约束：
 *   1 ≤ n, m ≤ 2e5，1 ≤ a[i] ≤ 2e5，1 ≤ l ≤ r ≤ n，1 ≤ k ≤ 2e5
 *
 * 解法：
 *   线段树区间修改 + 区间查询，懒标记记录「偏移量」。
 *
 *   关键观察：操作 1 把位置 i（i ∈ [l,r]）替换成 k + (i - l)，
 *   即 new[i] = i + (k - l)。令 c = k - l，则整段区间只是整体平移了 c，
 *   与下标 i 相关的部分只依赖区间本身（已知）。
 *   因此：
 *     - 懒标记只存偏移量 c；
 *     - 节点区间 [l,r] 的和 = 下标和 Σi + c × 长度，
 *       其中 Σi = (l + r) × (r - l + 1) / 2 可在 O(1) 算出（idx_sum）。
 *
 *   下传时左右儿子各自应用同一个 c 即可（idx_sum 会自适应区间），
 *   lazy 用极大值 NONE 标记「无懒标记」。
 *   复杂度 O((n + m) log n)。
 */

#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 10;
const long long NONE = 1e18; // 标记「无懒标记」的特殊值

long long sum[MAXN << 2];
long long lazy[MAXN << 2];

// 计算区间 [l, r] 的下标和
inline long long idx_sum(int l, int r) {
    return 1LL * (l + r) * (r - l + 1) / 2;
}

// 给节点 node 打上懒标记 c，对应区间 [l, r]
void set_tag(int node, int l, int r, long long c) {
    sum[node] = idx_sum(l, r) + c * (r - l + 1);
    lazy[node] = c;
}

void pushup(int node) {
    sum[node] = sum[node << 1] + sum[node << 1 | 1];
}

void pushdown(int node, int l, int r) {
    if (lazy[node] == NONE) return;
    int mid = (l + r) >> 1;
    set_tag(node << 1, l, mid, lazy[node]);
    set_tag(node << 1 | 1, mid + 1, r, lazy[node]);
    lazy[node] = NONE;
}

void build(int node, int l, int r, vector<int>& a) {
    lazy[node] = NONE;
    if (l == r) {
        sum[node] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid, a);
    build(node << 1 | 1, mid + 1, r, a);
    pushup(node);
}

void update(int node, int l, int r, int ul, int ur, long long c) {
    if (ul <= l && r <= ur) {
        set_tag(node, l, r, c);
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) >> 1;
    if (ul <= mid) update(node << 1, l, mid, ul, ur, c);
    if (ur > mid) update(node << 1 | 1, mid + 1, r, ul, ur, c);
    pushup(node);
}

long long query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return sum[node];
    }
    pushdown(node, l, r);
    int mid = (l + r) >> 1;
    long long res = 0;
    if (ql <= mid) res += query(node << 1, l, mid, ql, qr);
    if (qr > mid) res += query(node << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1); // 1-based 下标
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, 1, n, a);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            long long c = k - l;   // 偏移量
            update(1, 1, n, l, r, c);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}
