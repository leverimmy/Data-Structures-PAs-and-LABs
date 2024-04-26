#include <cstdio>
#include <cassert>

const int N = 1e6 + 5;

int n, m;
int next[N], prev[N], treeSize[N], ch[N][2], fa[N], chSize[N], maxSuffix[N];

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int height(int u) {
    if (chSize[u] == 0)
        return 0;
    return maxSuffix[ch[u][0]] + 1;
}

void update(int u) {
    // 更新从 u 开始（包括 u）往前的所有 maxSuffix
    if (u == ch[fa[u]][1])
        maxSuffix[u] = height(u);
    else // if (u != ch[fa[u]][0])
        maxSuffix[u] = max(height(u), maxSuffix[next[u]]);
    if (u == ch[fa[u]][0])
        return;
    for (int i = prev[u]; i; i = prev[i]) {
        maxSuffix[i] = max(height(i), maxSuffix[next[i]]);
    }
}

void build(int u) {
    treeSize[u] = 1;
    if (chSize[u] == 0) {
        return;
    }
    for (int i = ch[u][0], j = 1; j <= chSize[u]; i = next[i], j++) {
        build(i);
        treeSize[u] += treeSize[i];
    }
    update(ch[u][1]);
}

int main() {

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int t;
        scanf("%d", &t);
        for (int j = 0; j < t; j++) {
            int u;
            scanf("%d", &u);
            if (!chSize[i]) {
                ch[i][0] = ch[i][1] = u;
            } else {
                prev[u] = ch[i][1];
                next[ch[i][1]] = u;
                ch[i][1] = u;
            }
            chSize[i]++;
            fa[u] = i;
        }
    }

    ch[0][0] = ch[0][1] = 1, chSize[0] = 1, build(0);

    for (int i = 1; i <= m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 0) {
            int h, cur = 1, tar = 1, flag = 1, rk, f = 0, frk = 0;
            scanf("%d", &h);
            for (int j = 1; j <= h; j++) {
                int x;
                scanf("%d", &x);
                if (flag && x < chSize[cur]) {
                    f = cur;
                    frk = x;
                    for (int k = ch[cur][0], l = 0; l <= x; k = next[k], l++)
                        cur = k;
                }
                else
                    flag = 0;
            }

            // 删除

            if (frk == 0) {
                ch[f][0] = next[cur];
                prev[ch[f][0]] = 0;
                prev[cur] = next[cur] = 0;
                --chSize[f];
            } else if (frk == chSize[f] - 1) {
                ch[f][1] = prev[cur];
                next[ch[f][1]] = 0;
                update(prev[cur]);
                prev[cur] = next[cur] = 0;
                --chSize[f];
            } else {
                next[prev[cur]] = next[cur];
                prev[next[cur]] = prev[cur];
                update(prev[cur]);
                prev[cur] = next[cur] = 0;
                --chSize[f];
            }

            // 这里没有更新根的 treeSize
            // assert(f != 0);
            for (int j = f; j != 1; j = fa[j]) {
                treeSize[j] -= treeSize[cur];
                update(j);
            }
            update(1);

            flag = 1;

            scanf("%d", &h);
            for (int j = 1; j <= h; j++) {
                int x;
                scanf("%d", &x);
                if (flag && x < chSize[tar]) {
                    for (int k = ch[tar][0], l = 0; l <= x; k = next[k], l++)
                        tar = k;
                    // 这里不会更新根的 treeSize
                    treeSize[tar] += treeSize[cur];
                }
                else
                    flag = 0;
            }


            scanf("%d", &rk);

            // 得到了 cur, tar, rk, f, frk
            // 插入

            if (chSize[tar] == 0) {
                prev[cur] = next[cur] = 0;
                ch[tar][0] = ch[tar][1] = cur;
                chSize[tar]++;
            } else if (rk == 0) {
                prev[cur] = 0;
                next[cur] = ch[tar][0];
                prev[ch[tar][0]] = cur;
                ch[tar][0] = cur;
                chSize[tar]++;
            } else if (rk == chSize[tar]) {
                prev[cur] = ch[tar][1];
                next[cur] = 0;
                next[ch[tar][1]] = cur;
                ch[tar][1] = cur;
                chSize[tar]++;
            } else {
                int chTar = ch[tar][0];
                for (int j = 0; j < rk; j++)
                    chTar = next[chTar];
                prev[cur] = prev[chTar];
                next[cur] = chTar;
                next[prev[chTar]] = cur;
                prev[chTar] = cur;
                chSize[tar]++;
            }

            fa[cur] = tar;

            for (int j = cur; j; j = fa[j])
                update(j);

        } else if (op == 1) {
            int h, cur = 1, flag = 1;
            scanf("%d", &h);
            for (int j = 1; j <= h; j++) {
                int x;
                scanf("%d", &x);
                if (flag && x < chSize[cur]) {
                    for (int k = ch[cur][0], l = 0; l <= x; k = next[k], l++)
                        cur = k;
                }
                else
                    flag = 0;
            }
            printf("%d\n", height(cur));

        } else if (op == 2) {
            int h, cur = 1, flag = 1;
            scanf("%d", &h);
            for (int j = 1; j <= h; j++) {
                int x;
                scanf("%d", &x);
                if (flag && x < chSize[cur]) {
                    for (int k = ch[cur][0], l = 0; l <= x; k = next[k], l++)
                        cur = k;
                }
                else
                    flag = 0;
            }
            printf("%d\n", treeSize[cur]);
        }
    }

    return 0;
}
