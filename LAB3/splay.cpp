#include <cstdio>
#include <iostream>

const int N = 1e6 + 5;

int n, cnt, rt, fa[N], ch[N][2], siz[N], dat[N];

inline int son(int x) {
    return x == ch[fa[x]][1];
}

inline int make(int f, int v) {
    fa[++cnt] = f;
    dat[cnt] = v;
    siz[cnt] = 1;
    return cnt;
}

inline void pushup(int p) {
    siz[p] = siz[ch[p][0]] + siz[ch[p][1]] + 1;
}

inline void connect(int p, int f, int o) {
    ch[f][o] = p;
    fa[p] = f;
}

// 旋转 p
void rotate(int p) {
    int f = fa[p], g = fa[f];
    bool o1 = son(p), o2 = son(f);
    connect(ch[p][o1 ^ 1], f, o1);
    connect(f, p, o1 ^ 1);
    connect(p, g, o2);
    pushup(f), pushup(p);
}

// 将 p 伸展至 tar
void splay(int p, int tar) {
    int tarfa = fa[tar];
    while(fa[p] != tarfa) {
        int f = fa[p], g = fa[f];
        if(tarfa != g)
            son(p) ^ son(f) ? rotate(p) : rotate(f);
        rotate(p);
    }
    if(tar == rt)
        rt = p;
}

void insert(int v) {
    if (!rt) {
        rt = make(0, v);
        return;
    }
    int p = rt;
    while (true) {
        int &nxt = ch[p][v > dat[p]];
        if (!nxt) {
            nxt = make(p, v);
            splay(nxt, rt);
            break;
        }
        p = nxt;
    }
}

void remove(int v) {
    int p = rt;
    while (true) {
        if (dat[p] == v)
            break;
        p = ch[p][v > dat[p]];
    }
    splay(p, rt);
    if (!ch[p][0] || !ch[p][1]) {
        rt = ch[p][0] + ch[p][1];
        fa[rt] = 0;
        return;
    }
    int rs = ch[p][1];
    while (ch[rs][0])
        rs = ch[rs][0];
    splay(rs, rt);
    connect(ch[p][0], rs, 0);
    connect(rs, 0, 1);
    pushup(rs);
}

int query(int x) {
    int p = rt, ret = -1, f = 0;
    while (p) {
        if (dat[p] <= x)
            ret = std::max(ret, dat[p]);
        f = p;
        p = ch[p][x > dat[p]];
    }
    splay(f, rt);
    return ret;
}

int main() {
    freopen("inp.in", "r", stdin);
    freopen("oup1.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        char opt[2];
        int x;
        scanf("%s %d", opt, &x);
        if (opt[0] == 'A') {
            insert(x);
        } else if (opt[0] == 'B') {
            remove(x);
        } else if (opt[0] == 'C') {
            printf("%d\n", query(x));
        }
    }
    return 0;
}