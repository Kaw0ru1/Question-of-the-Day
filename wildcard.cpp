/*
 * 通配符匹配 — 牛客网 NC19935  [CQOI2014]
 *
 * 题目描述：
 *   几乎所有操作系统的命令行界面都支持文件名的通配符匹配。
 *   通配符有两个：
 *     * : 匹配 0 个及以上任意字符
 *     ? : 匹配恰好 1 个任意字符
 *   给定一个包含通配符的模式串和 n 个文件名，
 *   判断每个文件名是否能被模式串匹配。
 *
 * 输入格式：
 *   第一行：模式串（只含小写字母、*、?）
 *   第二行：整数 n，表示文件名数量
 *   接下来 n 行：每行一个文件名（只含小写字母）
 *
 * 约束：
 *   字符串长度 ≤ 100000，n ≤ 100，通配符（* 和 ?）数量 ≤ 10
 *
 * 解法：
 *   从右往左递归 + 回溯。
 *   遇到 * 时枚举它吃掉 0~k 个字符的所有可能，
 *   利用通配符 ≤ 10 的约束，递归分支在数据中很快被剪枝。
 *   时间复杂度：实际测试数据下可通过，极端数据可能退化。
 */

#include <bits/stdc++.h>
using namespace std;

string patternStr, targetStr;

bool checkMatch(int pIdx, int tIdx) {
    // 两个指针都越界，说明完全匹配
    if (pIdx < 0 && tIdx < 0) {
        return true;
    }

    // 目标字符串匹配完，但模式串还有剩余
    if (tIdx < 0) {
        for (int i = pIdx; i >= 0; --i) {
            if (patternStr[i] != '*') return false;
        }
        return true;
    }

    // 模式串匹配完，目标字符串没匹配完
    if (pIdx < 0) {
        return false;
    }

    // 处理星号通配符
    if (patternStr[pIdx] == '*') {
        // 逆序遍历，边界为 -1（* 匹配到文件名开头之前）
        for (int j = tIdx; j >= -1; --j) {
            if (checkMatch(pIdx - 1, j)) {
                return true;
            }
        }
        return false;
    }

    // 处理单字符匹配或问号
    if (patternStr[pIdx] == targetStr[tIdx] || patternStr[pIdx] == '?') {
        return checkMatch(pIdx - 1, tIdx - 1);
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int queryCount;
    cin >> patternStr >> queryCount;

    for (int k = 0; k < queryCount; ++k) {
        cin >> targetStr;

        int lenP = (int)patternStr.length() - 1;
        int lenT = (int)targetStr.length() - 1;

        if (checkMatch(lenP, lenT)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
