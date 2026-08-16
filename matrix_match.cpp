/*
 * Matrix — 牛客网 NC51003
 * 难度：中等    算法：二维哈希 / 前缀哈希 / 二分查找
 * 链接：https://ac.nowcoder.com/acm/problem/51003
 *
 * 一句话：判断询问的 A×B 01 子矩阵是否在原矩阵中出现过。
 *
 * 题目描述：
 *   给定一个 M 行 N 列的 01 矩阵（只包含 0 或 1），再执行 Q 次询问，
 *   每次询问给出一个 A 行 B 列的 01 矩阵，判断该矩阵是否在原矩阵中出现过。
 *
 * 输入格式：
 *   第一行四个整数 M, N, A, B。
 *   接下来一个 M 行 N 列的 01 矩阵，数字之间没有空格。
 *   接下来一个整数 Q。
 *   接下来 Q 个 A 行 B 列的 01 矩阵，数字之间没有空格。
 *
 * 输出格式：
 *   对于每个询问，输出 1 表示出现过，0 表示没有。
 *
 * 约束：
 *   M, N ≤ 1000，A, B ≤ 100，Q ≤ 1000
 *
 * 解法：
 *   二维哈希板子题。
 *   1. 先对每行做一维前缀哈希（基数 base1）。
 *   2. 再对列方向做二次前缀哈希（基数 base2），得到二维前缀哈希 h[i][j]。
 *   3. 用容斥公式 O(1) 求出原矩阵中所有 A×B 子矩阵的哈希值，排序。
 *   4. 每次询问按同样方式计算查询矩阵哈希值，二分查找是否存在。
 *
 *   关键点：
 *   - 不能只做一维前缀和式哈希，否则丢失二维行列信息；
 *     必须按行、按列分别用不同基数构建，并用 pow1[B]、pow2[A] 幂次还原。
 *   - 字符转数值 +1（'0'→1, '1'→2），避免 0 值导致哈希歧义。
 *   - 用 unsigned long long 自然溢出取模。
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const int MAXN = 1005;
const ull base1 = 131;   // 行方向哈希基数
const ull base2 = 13331; // 列方向哈希基数

ull pow1[MAXN], pow2[MAXN];
ull row_hash[MAXN][MAXN];
ull h[MAXN][MAXN];
int val[MAXN][MAXN];

// 预处理基数的幂次
void init_pow() {
    pow1[0] = 1;
    pow2[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        pow1[i] = pow1[i - 1] * base1;
        pow2[i] = pow2[i - 1] * base2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init_pow();

    int M, N, A, B;
    cin >> M >> N >> A >> B;

    for (int i = 1; i <= M; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= N; ++j) {
            // 字符转数值+1，避免 '0' 对应 0 带来的哈希冲突风险
            val[i][j] = s[j - 1] - '0' + 1;
        }
    }

    // 1. 每行的一维前缀哈希
    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= N; ++j) {
            row_hash[i][j] = row_hash[i][j - 1] * base1 + val[i][j];
        }
    }

    // 2. 二维前缀哈希（对行哈希按列方向做二次哈希）
    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= N; ++j) {
            h[i][j] = h[i - 1][j] * base2 + row_hash[i][j];
        }
    }

    // 3. 收集所有 A×B 子矩阵的哈希值
    vector<ull> hashes;
    if (A <= M && B <= N) { // 边界：子矩阵不能大于原矩阵
        for (int i = A; i <= M; ++i) {
            for (int j = B; j <= N; ++j) {
                int x1 = i - A + 1;
                int y1 = j - B + 1;
                // 二维子矩阵哈希（容斥原理）
                ull hash_val = h[i][j]
                    - h[x1 - 1][j] * pow2[A]
                    - h[i][y1 - 1] * pow1[B]
                    + h[x1 - 1][y1 - 1] * pow1[B] * pow2[A];
                hashes.push_back(hash_val);
            }
        }
    }

    sort(hashes.begin(), hashes.end());

    int Q;
    cin >> Q;
    while (Q--) {
        // 4. 计算查询矩阵的哈希值
        vector<ull> rh(A);
        for (int i = 0; i < A; ++i) {
            string s;
            cin >> s;
            ull r = 0;
            for (int j = 0; j < B; ++j) {
                r = r * base1 + (s[j] - '0' + 1);
            }
            rh[i] = r;
        }
        ull q_hash = 0;
        for (int i = 0; i < A; ++i) {
            q_hash = q_hash * base2 + rh[i];
        }

        // 5. 二分查找判断是否存在
        bool exist = binary_search(hashes.begin(), hashes.end(), q_hash);
        cout << (exist ? 1 : 0) << '\n';
    }

    return 0;
}
