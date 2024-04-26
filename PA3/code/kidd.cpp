#include <cstdio>
#include <cstdlib>
#include <cassert>
#define LL long long

const int M = 2e5 + 5;

int n, m, cnt, raw[M << 1];

struct Operation {
    char opt[2];
    int l, r;
} q[M];

struct Interval {
    int l, r;
    Interval() { }
    Interval(int ll, int rr) : l(ll), r(rr) { }
} itv[M << 2];

LL sum[M << 4];
int ch[M << 4][2], add[M << 4], len[M << 4];

void pushup(int x) {
    sum[x] = sum[x << 1] + sum[x << 1 | 1];
    len[x] = len[x << 1] + len[x << 1 | 1];
}

void pushdown(int x) {
    if (add[x]) {
        add[x << 1] += add[x];
        add[x << 1 | 1] += add[x];
        sum[x << 1] += 1LL * add[x] * len[x << 1];
        sum[x << 1 | 1] += 1LL * add[x] * len[x << 1 | 1];
        add[x] = 0;
    }
}

void build(int p, int l, int r) {
    ch[p][0] = l, ch[p][1] = r;
    if (l == r) {
        len[p] = itv[l].r - itv[l].l + 1;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void modify(int p, int l, int r, int v) {
    if (l <= ch[p][0] && ch[p][1] <= r) {
        add[p] += v;
        sum[p] += 1LL * v * len[p];
        return;
    }
    pushdown(p);
    int mid = ch[p][0] + ch[p][1] >> 1;
    if (l <= mid)
        modify(p << 1, l, r, v);
    if (mid < r)
        modify(p << 1 | 1, l, r, v);
    pushup(p);
}

LL query(int p, int l, int r) {
    if (l <= ch[p][0] && ch[p][1] <= r)
        return sum[p];
    pushdown(p);
    int mid = ch[p][0] + ch[p][1] >> 1;
    LL ret = 0;
    if (l <= mid)
        ret += query(p << 1, l, r);
    if (mid < r)
        ret += query(p << 1 | 1, l, r);
    return ret;
}

int cmp(const void* p1, const void* p2) {
    return *(int*)p1 - *(int*)p2;
}

// 去重
void deduplicate() {
    cnt = 0;
    qsort(raw, 2 * m, sizeof(int), cmp);
    for (int i = 0, j = 0; j < 2 * m; i++) {
        while (raw[j] == raw[i])
            j++;
        raw[i + 1] = raw[j];
        cnt++;
    }
}

int search(int l, int r, int v) {
    // 答案区间为 [l, r)
    while (l < r - 1) {
        int mid = l + r >> 1;
        if (itv[mid].l <= v) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l;
}

int getRank(int v) {
    return search(1, n + 1, v);
}

int main() {

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        char opt[2];
        int l, r;
        scanf("%s %d %d", q[i].opt, &q[i].l, &q[i].r);
        raw[i - 1 << 1] = q[i].l;
        raw[i - 1 << 1 | 1] = q[i].r;
    }

    deduplicate();

    n = 0;
    for (int i = 0; i < cnt; i++) {
        itv[++n] = Interval(raw[i], raw[i]);
        if (i < cnt - 1 && raw[i + 1] - raw[i] > 1)
            itv[++n] = Interval(raw[i] + 1, raw[i + 1] - 1);
    }

    build(1, 1, n);

    for (int i = 1; i <= m; i++) {
        int l = getRank(q[i].l);
        int r = getRank(q[i].r);

        if (q[i].opt[0] == 'H')
            modify(1, l, r, 1);
        else if (q[i].opt[0] == 'Q')
            printf("%lld\n", query(1, l, r));
    }

    return 0;
}
