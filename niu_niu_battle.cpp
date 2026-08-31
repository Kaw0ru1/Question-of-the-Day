/*
 * 牛牛的战役 — 牛客网 NC21613
 * 难度：中等    算法：二分答案 / 贪心
 * 链接：https://ac.nowcoder.com/acm/problem/21613
 *
 * 一句话：二分最大经验值，贪心验证能否以该上限击败所有敌人。
 *
 * 题目描述：
 *   牛牛可以指挥若干个 oier 协同作战。
 *   给你数组 a 表示我方每人的战斗力；数组 b 表示敌方战斗力；
 *   数组 c，其中 c[i] 表示战斗力为 b[i] 的敌方人员有 c[i] 个。
 *   每个 oier 每次可选择一名敌方人员战斗，若战斗力 >= 敌方人员即可战胜，
 *   经验值 +1（初始经验均为 0）。
 *   牛牛要打败所有敌方人员，并最小化「最大的经验值」。
 *   若无法打败所有敌人，输出 -1；否则输出最小化的最大经验值。
 *
 * 输入格式：
 *   第一行一个整数 n（1 ≤ n ≤ 50），我方人数。
 *   第二行 n 个整数 a[i]（1 ≤ ai ≤ 10000）。
 *   第三行一个整数 m（1 ≤ m ≤ 50），b 数组长度。
 *   第四行 m 个整数 b[i]（1 ≤ bi ≤ 10000）。
 *   第五行 m 个整数 c[i]（1 ≤ ci ≤ 1e14）。
 *
 * 输出格式：
 *   输出一个整数。
 *
 * 约束：
 *   n, m ≤ 50，ai, bi ≤ 10000，ci ≤ 1e14（需用 long long）
 *
 * 解法：
 *   最大值最小化 → 二分答案 + 贪心验证。
 *
 *   1. 若最强敌人的战斗力 > 我方可击败上限（我方最高战斗力），必输，输出 -1。
 *   2. 二分「每人最多获得的经验值」mid：
 *        - 下界 left = ceil(敌方总人数 / n)（至少平均分），上界 right = 总人数。
 *      check(mid) 贪心验证：我方按战斗力升序，每人最多打 mid 场，
 *      优先分配当前最弱、且能被该人员击败的敌人（双指针扫敌人列表），
 *      若能打完所有敌人则可行。
 *   3. 取满足 check 的最小 mid 即为答案。
 *
 *   时间复杂度 O(n m log(总人数))，n, m ≤ 50 完全够用。
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 验证：当每人最多获得 mid 点经验时，能否击败所有敌人
 */
bool check(long long mid, const vector<int>& a, const vector<pair<int, long long>>& enemies, int n, int m) {
    int j = 0;                        // 当前处理的敌人类型索引
    long long rest = enemies[0].second; // 当前敌人类型的剩余数量
    for (int i = 0; i < n; ++i) {
        long long remain = mid;       // 当前我方人员剩余可出战次数
        // 优先分配最弱的、可击败的敌人
        while (j < m && enemies[j].first <= a[i] && remain > 0) {
            if (rest <= remain) {
                // 当前类型敌人全部分配给该人员
                remain -= rest;
                j++;
                rest = (j < m) ? enemies[j].second : 0;
            } else {
                // 只分配部分，用完当前人员的出战次数
                rest -= remain;
                remain = 0;
            }
        }
        if (j >= m) return true; // 所有敌人已分配完毕
    }
    return j >= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    vector<long long> c(m);
    for (int i = 0; i < m; ++i) {
        cin >> c[i];
    }

    // 我方战斗力升序排序
    sort(a.begin(), a.end());

    // 敌方按战斗力升序排序
    vector<pair<int, long long>> enemies(m);
    for (int i = 0; i < m; ++i) {
        enemies[i] = {b[i], c[i]};
    }
    sort(enemies.begin(), enemies.end());

    // 存在无法击败的敌人，直接输出 -1
    if (enemies.back().first > a.back()) {
        cout << -1 << endl;
        return 0;
    }

    // 计算敌方总人数
    long long total = 0;
    for (auto& e : enemies) {
        total += e.second;
    }

    // 二分答案：左边界为平均每人至少出战次数（向上取整），右边界为总敌人数
    long long left = (total + n - 1) / n;
    long long right = total;
    long long ans = total;

    while (left <= right) {
        long long mid = left + (right - left) / 2; // 避免溢出
        if (check(mid, a, enemies, n, m)) {
            ans = mid;
            right = mid - 1; // 尝试更小的最大值
        } else {
            left = mid + 1;  // 需要更大的最大值
        }
    }

    cout << ans << endl;

    return 0;
}
