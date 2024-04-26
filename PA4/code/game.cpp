#include <cstdio>
#include <iostream>
#include <cstring>
#define LL long long

const int N = 1e5 + 5;
const int M = 1e5 + 5;
const int mod = 1e9 + 7;

int n, m, t[N], ans[N << 1];
int cnt, first[N << 1], vis[N << 1];
LL dis[N << 1];

struct Edge {
    int to, next, wt;
} e[M << 2];

void add(int u, int v, int w) {
    e[cnt].to = v;
    e[cnt].wt = w;
    e[cnt].next = first[u];
    first[u] = cnt++;
}

struct Pair {
    int x, v;
    Pair() {

    }
    Pair(int xx, int vv) : x(xx), v(vv) {

    }
    bool operator<(const Pair &rhs) const {
        return v < rhs.v;
    }
};

// 小根堆，优化 Dijkstra 算法
struct Heap {
    int _siz;
    Pair val[N << 1];
    void push(Pair x) {
        val[++_siz] = x;
        int cur = _siz;
        while (cur > 1) {
            if (val[cur] < val[cur >> 1])
                std::swap(val[cur], val[cur >> 1]);
            else
                break;
            cur >>= 1;
        }
    }
    void pop() {
        std::swap(val[1], val[_siz--]);
        int cur = 1;
        while (cur << 1 <= _siz) {
            int lc = cur << 1, rc = cur << 1 | 1, nxt;
            if (rc <= _siz) {
                if(val[lc] < val[rc])
                    nxt = lc;
                else
                    nxt = rc;
            } else
                nxt = lc;
            if (val[nxt] < val[cur])
                std::swap(val[cur], val[nxt]);
            else
                break;
            cur = nxt;
        }
    }
    Pair top() {
        return val[1];
    }
    bool empty() {
        return _siz == 0;
    }
    Heap() {
        _siz = 0;
    }
} h;

// Dijkstra 算法求单源最短路径
void Dijkstra(int s) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0LL;
    ans[s] = 1;
    h.push(Pair(s, 0));
    while (!h.empty()) {
        int x = h.top().x;
        h.pop();
        if (vis[x])
            continue;
        vis[x] = 1;
        for (int i = first[x]; ~i; i = e[i].next) {
            int y = e[i].to;
            if (dis[y] > dis[x] + e[i].wt) {
                dis[y] = dis[x] + e[i].wt;
                // 松弛时更新最短路数量
                ans[y] = ans[x];
                if (!vis[y])
                    h.push(Pair(y, dis[y]));
            } else if (dis[y] == dis[x] + e[i].wt)
                // 长度恰好为最短路长度，累加最短路数量
                ans[y] = (ans[y] + ans[x]) % mod;
        }
    }
}

int main() {
    memset(first, -1, sizeof(first));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &t[i]);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // 点权转化为边权 - 1
        add(u, v, t[u] + t[v]);
        add(v, u, t[u] + t[v]);
    }
    Dijkstra(1);
    // 点权转化为边权 - 2
    printf("%lld\n%d", dis[n] + t[1] + t[n] >> 1, ans[n]);
    return 0;
}