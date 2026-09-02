/*
 * Fancy Signal Translate — 牛客网 NC14270
 * 难度：简单    算法：位运算 / 滑动窗口 / 滚动哈希
 * 链接：https://ac.nowcoder.com/acm/problem/14270
 *
 * 一句话：求未出现过的最短 01 子串的长度。
 *
 * 题目描述：
 *   FST 发明了一种奇特的加密方式：对于一个 01 串，他会构造另一个 01 串，
 *   使得原串是在新串中没有出现过的最短的串。
 *   由于加密方式有 BUG，没出现过的最短串不止一个。
 *   求没出现过的最短串的长度。
 *
 * 输入格式：
 *   一行一个 01 串。
 *
 * 输出格式：
 *   一行一个正整数，表示没有出现过的最短串的长度。
 *
 * 约束：
 *   字符串长度 ≤ 1e5
 *
 * 解法：
 *   从小到大枚举长度 k，判断是否存在「未出现的长度为 k 的 01 串」。
 *
 *   - 长度 k 的 01 串共有 2^k 种。若原串里长度为 k 的不同子串数量
 *     不足 2^k，说明至少有一种没出现，答案就是 k。
 *   - 长度 k 一旦超过 n，原串根本没有长度为 k 的子串，必然存在未出现者。
 *     由于 n ≤ 1e5，2^k > n 时 k ≈ 17，枚举量很小。
 *
 *   实现：把每个长度为 k 的子串看成 k 位二进制数，用滑动窗口 O(1) 滚动：
 *     cur = ((cur << 1) | 新字符) & (2^k - 1)
 *   开一个 2^k 的 bool 数组去重计数。
 *   复杂度 O(Σ 2^k)（k 增到首个缺失长度即停）。
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    for (int k = 1; ; ++k) {
        int total = 1 << k; // 长度为 k 的 01 串总共有 2^k 种
        if (k > n) { // 长度 k 超过字符串长度，必然不存在该长度子串
            cout << k << endl;
            return 0;
        }

        vector<bool> vis(total, false);
        int cur = 0;
        // 初始化第一个窗口的数值
        for (int i = 0; i < k; ++i) {
            cur = cur * 2 + (s[i] - '0');
        }
        vis[cur] = true;
        int cnt = 1;

        int mask = total - 1; // 掩码，保留低 k 位
        // 滑动窗口遍历剩余子串
        for (int i = 1; i <= n - k; ++i) {
            // 左移 1 位，加入新字符，取低 k 位
            cur = ((cur << 1) | (s[i + k - 1] - '0')) & mask;
            if (!vis[cur]) {
                vis[cur] = true;
                ++cnt;
            }
        }

        if (cnt < total) { // 存在未出现的长度为 k 的子串
            cout << k << endl;
            return 0;
        }
    }

    return 0;
}
