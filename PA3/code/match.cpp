#include <cstdio>

const int mod = 1e9 + 7;
const int pri = 19260817;
const int N = 8e5 + 5;

int n, m, arr[N], qpow[N] = { 1 };
char str[N];

void swap(int &x, int &y) {
    x ^= y ^= x ^= y;
}

struct SPLAY {
    bool rev[N];
    // hash[ ][0] 存正向 hash 值
    // hash[ ][1] 存反向 hash 值
    int cnt, rt, val[N], hash[N][2], ch[N][2], fa[N], siz[N];

    // 判断是左儿子 ( 返回 0) 还是右儿子 ( 返回 1)
    int son(int x) {
        return x == ch[fa[x]][1];
    }
    // 新建结点
    int make(int f, int v) {
        val[++cnt] = v;
        fa[cnt] = f;
        siz[cnt] = 1;
        hash[cnt][0] = hash[cnt][1] = v;
        return cnt;
    }
    // 上传更新正序、倒序 hash 值以及子树大小
    void pushup(int p) {
        hash[p][0] = ((1LL * hash[ch[p][0]][rev[ch[p][0]]] * qpow[siz[ch[p][1]] + 1] % mod + 1LL * val[p] * qpow[siz[ch[p][1]]] % mod) % mod + hash[ch[p][1]][rev[ch[p][1]]]) % mod;
        hash[p][1] = ((1LL * hash[ch[p][1]][rev[ch[p][1]] ^ 1] * qpow[siz[ch[p][0]] + 1] % mod + 1LL * val[p] * qpow[siz[ch[p][0]]] % mod) % mod + hash[ch[p][0]][rev[ch[p][0]] ^ 1]) % mod;
        siz[p] = siz[ch[p][0]] + siz[ch[p][1]] + 1;
    }
    // 下传标记
    void pushdown(int p) {
        if(rev[p]) {
            swap(ch[p][0], ch[p][1]);
            swap(hash[p][0], hash[p][1]);
            rev[ch[p][0]] ^= 1;
            rev[ch[p][1]] ^= 1;
            rev[p] = 0;
        }
    }
    void connect(int p, int f, int o) {
        ch[f][o] = p;
        fa[p] = f;
    }
    // 求秩为 x 的结点编号
    int kth(int x) {
        int p = rt;
        while(1) {
            pushdown(p);
            int delta = siz[p] - siz[ch[p][1]];
            if(siz[ch[p][0]] < x && x <= delta)
                break;
            if(x < delta)
                p = ch[p][0];
            else {
                x -= delta;
                p = ch[p][1];
            }
        }
        return p;
    }
    // 旋转 p
    void rotate(int p) {
        int f = fa[p], g = fa[f];
        if (g)
            pushdown(g);
        if (f)
            pushdown(f);
        pushdown(p);
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
    // 建立以 p 为根结点, f 为 p 的父结点, 表示区间 [l, r] 的子树
    void build(int &p, int f, int l, int r) {
        if(l > r)
            return;
        int mid = l + r >> 1;
        p = ++cnt;
        fa[p] = f;
        val[p] = hash[p][0] = hash[p][1] = arr[mid];
        rev[p] = 0;
        build(ch[p][0], p, l, mid - 1);
        build(ch[p][1], p, mid + 1, r);
        pushup(p);
    }
    // 在 str[x] 前面插入 v
    void insert(int x, int v) {
        int p = kth(x - 1);
        int q = kth(x);
        splay(p, rt);
        splay(q, ch[rt][1]);
        int tar = ch[rt][1];
        ch[tar][0] = make(tar, v);
        splay(ch[tar][0], rt);
    }
    // 删除 str[x]
    void remove(int x) {
        int p = kth(x - 1);
        int q = kth(x + 1);
        splay(p, rt);
        splay(q, ch[rt][1]);
        ch[ch[rt][1]][0] = 0;
        splay(ch[rt][1], rt);
    }
    // 翻转 [l, r]
    void reverse(int l, int r) {
        int p = kth(l - 1);
        int q = kth(r + 1);
        splay(p, rt);
        splay(q, ch[rt][1]);
        int tar = ch[ch[rt][1]][0];
        rev[tar] ^= 1;
    }
    bool check(int p, int q, int len) {
        // [p, p + len - 1] 的区间 hash 值
        int x = kth(p - 1);
        int y = kth(p + len);
        splay(x, rt);
        splay(y, ch[rt][1]);
        int tar = ch[ch[rt][1]][0];
        int hash1 = hash[tar][rev[tar]];

        // 求解 [q, q + len - 1] 的区间 hash 值
        x = kth(q - 1);
        y = kth(q + len);
        splay(x, rt);
        splay(y, ch[rt][1]);
        tar = ch[ch[rt][1]][0];
        int hash2 = hash[tar][rev[tar]];

        return hash1 == hash2;
    }
    // 中序遍历以 p 为根的子树
    void print(int p) {
        if (rev[p]) {
            if (ch[p][1])
                print(ch[p][1]);
            if (val[p])
                printf("%c ", val[p] + 'a' - 1);
            if (ch[p][0])
                print(ch[p][0]);
        } else {
            if (ch[p][0])
                print(ch[p][0]);
            if (val[p])
                printf("%c ", val[p] + 'a' - 1);
            if (ch[p][1])
                print(ch[p][1]);
        }        
    }
} t;

// 初始化
void initialize() {
    // 预处理 p^i % mod
    for (int i = 1; i <= n + m; i++)
        qpow[i] = 1LL * qpow[i - 1] * pri % mod;
    for (int i = 1; i <= n; i++)
        arr[i + 1] = str[i - 1] - 'a' + 1;
    // 建树
    t.build(t.rt, 0, 1, n + 2);
}

int main() {
    
    scanf("%d %d", &n, &m);
    // 如果 n == 0, 则 str 为空串!
    if (n)
        scanf("%s", str);
    initialize();

    for (int i = 1; i <= m; i++) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int pos;
            char c[2];
            scanf("%d %s", &pos, c);
            t.insert(pos + 2, c[0] - 'a' + 1);
        } else if (opt == 2) {
            int pos;
            scanf("%d", &pos);
            t.remove(pos + 2);
        } else if (opt == 3) {
            int l, r;
            scanf("%d %d", &l, &r);
            t.reverse(l + 2, r + 2);
        } else if (opt == 4) {
            int l, r, len;
            scanf("%d %d %d", &l, &r, &len);
            putchar(t.check(l + 2, r + 2, len) ? 'T' : 'F');
        }
    }
    return 0;
}
