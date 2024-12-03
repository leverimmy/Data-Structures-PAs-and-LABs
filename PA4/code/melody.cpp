#include <cstdio>
#include <iostream>
#include <cstring>

const int N = 1.5e6 + 5;
const int Q = 1e6 + 5;
const int L = 20 + 5;

int n, m, a[N], opr[Q], f[N][L], g[N];
int lg2[N] = { -1 }, dep[N] = { 0, 1 };

// 求 u 和 v 的最近公共祖先，使用倍增算法
int lca(int u, int v) {
    if(dep[u] < dep[v])
        std::swap(u, v);
    int del = dep[u] - dep[v];
    for (int i = 0; i <= lg2[dep[u]]; ++i)
        if (del & (1 << i))
            u = f[u][i];
    if (u == v)
        return u;
    for (int i = lg2[dep[v]]; i >= 0; --i)
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    return f[u][0];
}

// 求 a[l...r] 内的 next 数组（及其构成的树）
void getNext(int l, int r) {
    for (int i = l, k = f[l - 1][0]; i <= r; ++i) {
        while (k > 0 && a[k + 1] != a[i])
            k = f[k][0];
        if (a[k + 1] == a[i])
            ++k;
        // i 的父亲为 k
        f[i][0] = k;
        // 求 next 树里的深度
        dep[i] = dep[k] + 1;
        // 倍增预处理 next 树上 i 的 2^j 级父亲
        for (int j = 1; j <= lg2[dep[i]]; ++j)
            f[i][j] = f[f[i][j - 1]][j - 1];
    }
}

// 求 a[l...r] 内的 jump 数组 g[]
void getJump(int l, int r) {
    for (int i = l, k = g[l - 1]; i <= r; ++i) {
        while (k > 0 && a[k + 1] != a[i])
            k = f[k][0];
        if (a[k + 1] == a[i])
            ++k;
        // 一定要找到 *不重叠的* 前后缀，所以应当由 k * 2 <= i
        while (k * 2 > i)
            k = f[k][0];
        // k 即为满足要求的最长相等的 *不重叠的* 真前缀和真后缀的长度
        g[i] = k;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    // 预处理 log_2(x)
    for (int i = 1; i < N; i++)
        lg2[i] = lg2[i >> 1] + 1;
    getNext(2, n);
    getJump(2, n);
    for (int i = 1; i <= m; i++) {
        int opt, q;
        scanf("%d %d", &opt, &q);
        for (int j = 1; j <= q; j++)
            scanf("%d", &opr[j]);
        if (opt == 1) {
            // 将新增的字符串添加到原字符串的末尾
            memcpy(a + n + 1, opr + 1, q * sizeof(int));
            getNext(n + 1, n + q);
            getJump(n + 1, n + q);
            n += q;
        } else if (opt == 2) {
            // 求所有的 g[ opr[i] ] 的最近公共祖先
            int ans = g[opr[1]];
            for (int j = 2; j <= q; j++)
                ans = lca(ans, g[opr[j]]);
            printf("%d\n", ans);
        }
    }
    return 0;
}