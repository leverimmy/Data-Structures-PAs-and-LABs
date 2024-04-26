#include <cstdio>
#include <iostream>

const int N = 1e6 + 5;
const int inf = 0x3f3f3f3f;

int n, m, k, q, a[N], p[N], tmp[N];

struct Heap {
    int _capacity, _siz, *val;
    // 弹出堆顶元素（最小元素）
    void pop() {
        // 将其与最深元素交换后，再重新从上往下调整位置，维持小根堆的性质
        std::swap(val[1], val[_siz--]);
        int cur = 1;
        while ((cur << 1) <= _siz) {
            int lc = cur << 1, rc = lc + 1, nxt;
            if (rc <= _siz) {
                if(val[lc] <= val[rc])
                    nxt = lc;
                else
                    nxt = rc;
            } else
                nxt = lc;
            if (val[cur] > val[nxt])
                std::swap(val[cur], val[nxt]);
            else
                break;
            cur = nxt;
        }
    }
    // 重点：保证堆内元素个数不多于 k，这样当元素个数为 k 时，堆顶即为第 k 大的值
    void push(int v) {
        // 如果堆中元素已经为 k
        if (_siz == k) {
            // 如果新加入元素比堆顶大，那么就把堆顶丢掉，重新维护第 k 大的值
            if (v > val[1]) {
                pop();
            } else {
                return;
            }
        }
        // 进行扩容，每次扩容成原来大小的两倍
        if (_siz == _capacity) {
            for (int i = 1; i <= _siz; i++)
                tmp[i] = val[i];
            delete[] val;
            _capacity <<= 1;
            val = new int[_capacity + 1];
            for (int i = 1; i <= _siz; i++)
                val[i] = tmp[i];
        }
        // 向上交换，维持小根堆的性质
        val[++_siz] = v;
        int cur = _siz;
        while (cur > 1) {
            if (val[cur] < val[cur >> 1])
                std::swap(val[cur], val[cur >> 1]);
            else
                break;
            cur >>= 1;
        }
    }
    int size() {
        return _siz;
    }
    int top() {
        return val[1];
    }
    void init(int x) {
        val = new int[2];
        val[1] = x;
        _capacity = _siz = 1;
    }
    Heap() {

    }
} h[N];

// 路径压缩的并查集
int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
}

// 按秩合并的并查集，启发式合并使复杂度为均摊 O(log n)
void join(int x, int y) {
    int px = find(x), py = find(y);
    if (px != py) {
        if (h[px].size() < h[py].size())
            std::swap(px, py);
        while (h[py].size()) {
            int v = h[py].top();
            h[py].pop();
            h[px].push(v);
        }
        p[py] = px;
        delete h[py].val;
    }
}

// 查询，如果堆大小小于 k，则返回 -1
int query(int x) {
    int p = find(x);
    return h[p].size() < k ? -1 : h[p].top();
}

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        p[i] = i;
        h[i].init(a[i]);
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        join(u, v);
    }
    for (int i = 1; i <= q; i++) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int u, v;
            scanf("%d %d", &u, &v);
            join(u, v);
        } else if (opt == 2) {
            int u;
            scanf("%d", &u);
            printf("%d\n", query(u));
        }
    }
    return 0;
}