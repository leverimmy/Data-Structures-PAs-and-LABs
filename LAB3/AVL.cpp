#include <cstdio>
#include <iostream>

const int N = 1e6 + 5;

int n, rt, cnt, ch[N][2] = { 1 }, siz[N], h[N], dat[N];

inline int balance(int p) {
    return h[ch[p][0]] - h[ch[p][1]];
}

inline int make(int v) {
    dat[++cnt] = v;
    siz[cnt] = h[cnt] = 1;
    return cnt;
}

inline void pushup(int p) {
    siz[p] = siz[ch[p][0]] + siz[ch[p][1]] + 1;
    h[p] = std::max(h[ch[p][0]], h[ch[p][1]]) + 1;
}

void zig(int &p) {
    int l = ch[p][0];
    ch[p][0] = ch[l][1];
    ch[l][1] = p;
    p = l;
    pushup(ch[p][1]), pushup(p);
}

void zag(int &p) {
    int r = ch[p][1];
    ch[p][1] = ch[r][0];
    ch[r][0] = p;
    p = r;
    pushup(ch[p][0]), pushup(p);
}

void check(int &p) {
    if (balance(p) > 1) {
        if (balance(ch[p][0]) > 0)
            zig(p);
        else
            zag(ch[p][0]), zig(p);
    }
    else if (balance(p) < -1) {
        if (balance(ch[p][1]) < 0)
            zag(p);
        else
            zig(ch[p][1]), zag(p);
    } else if (p)
        pushup(p);
}

void insert(int &p, int v) {
    if (!p) {
        p = make(v);
        return;
    }
    insert(ch[p][v > dat[p]], v);
    check(p);
}

void remove(int &p, int v) {
    if (v == dat[p]) {
        if (!ch[p][0] || !ch[p][1])
            p = ch[p][0] + ch[p][1];
        else if (balance(p) > 0)
            zig(p), remove(ch[p][1], v);
        else
            zag(p), remove(ch[p][0], v);
        return;
    }
    remove(ch[p][v > dat[p]], v);
    check(p);
}

int query(int x) {
    int p = rt, ret = -1;
    while (p) {
        if (dat[p] <= x)
            ret = std::max(ret, dat[p]);
        p = ch[p][x > dat[p]];
    }
    return ret;
}

int main() {
    freopen("inp.in", "r", stdin);
    freopen("oup2.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        char opt[2];
        int x;
        scanf("%s %d", opt, &x);
        if (opt[0] == 'A') {
            insert(rt, x);
        } else if (opt[0] == 'B') {
            remove(rt, x);
        } else if (opt[0] == 'C') {
            printf("%d\n", query(x));
        }
    }
    return 0;
}