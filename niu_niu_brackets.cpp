/*
 * 牛牛学括号 — 牛客网 NC21579
 * 难度：简单    算法：计数 / 组合数学 / 贪心
 * 链接：https://ac.nowcoder.com/acm/problem/21579
 *
 * 一句话：统计每个右括号左侧左括号数作上限，排序后连乘方案数。
 *
 * 题目描述：
 *   给定一个合法的括号序列，每次操作分两步：
 *     第一步：删除第一个左括号
 *     第二步：删除某一个右括号，且保证删除后的括号序列仍合法
 *   求将括号删到空为止一共有多少种不同的删除方法。
 *   两种方法不同当且仅当存在某一步右括号的删除位置不同。答案模 1e9+7。
 *
 * 输入格式：
 *   输入一个字符串 s，只包含左右括号。
 *
 * 输出格式：
 *   输出一个整数，表示删除方法总数（模 1e9+7）。
 *
 * 约束：
 *   2 ≤ |s| ≤ 2500
 *
 * 解法：
 *   贪心计数 + 乘法原理。
 *
 *   每个右括号在某一步被删除时，它左侧还没被删掉的左括号数，
 *   就是它这次可选的「配对左括号」位置数。
 *   由贪心可知：按删除顺序从后往前看，越靠后删除的右括号，
 *   它左侧可用的左括号越多。所以把每个右括号「左侧左括号总数」
 *   作为上限 limits[i]，排序后从小到大依次分配：
 *     第 i 个（从 0 开始）右括号可选的左括号数 = limits[i] - i
 *   （减去的 i 个是被更早删除的右括号占用的左括号位置）。
 *   答案 = Π (limits[i] - i) mod 1e9+7。
 *
 *   等价理解（栈法）：遇到 '(' 计数 +1，遇到 ')' 时
 *   ans *= 当前计数，再 -1；与排序法结果一致。
 *
 *   时间复杂度 O(|s| log |s|)。
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<int> limits;
    int leftCount = 0;
    // 统计每个右括号左侧的左括号数量，作为其删除时间的上限
    for (char c : s) {
        if (c == '(') {
            leftCount++;
        } else {
            limits.push_back(leftCount);
        }
    }

    // 按上限从小到大排序
    sort(limits.begin(), limits.end());

    long long ans = 1;
    for (int i = 0; i < limits.size(); ++i) {
        ans = ans * (limits[i] - i) % MOD;
    }

    cout << ans << '\n';
    return 0;
}
