/*
 * 缆车观光 — 牛客网 NC23482
 *
 * 题目描述：
 *   N 个景点构成一棵树（N-1 条边），每条边消耗 1 体力。
 *   有两个特殊景点 U,V 之间有缆车直达，消耗 0 体力。
 *   Q 次询问，每次问 x→y 的最小体力消耗。
 *
 * 约束：1 ≤ N ≤ 3×10^5, 1 ≤ Q ≤ 1×10^6
 *
 * 解法（待补）：
 *   树上任意两点距离 dist(a,b) = depth[a] + depth[b] - 2*depth[lca(a,b)]
 *   考虑缆车边后：
 *     ans = min( dist(x,y),
 *                dist(x,U) + dist(V,y),
 *                dist(x,V) + dist(U,y) )
 *   LCA 用倍增或树剖，预处理 O(N log N)，每次询问 O(1)（倍增需要 O(log N)，
 *   但 Q=1e6 需要 O(1) 询问，考虑 ST 表 + 欧拉序求 LCA）。

TODO: 补充 AC 代码
 */
