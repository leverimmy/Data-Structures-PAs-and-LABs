#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#define LL long long

namespace io {
    template <typename T> inline void read(T & _x) {
        int f = 0, ch; _x = 0;
        while(!isdigit(ch = getchar())) f |= ch == '-';
        while(isdigit(ch)) _x = _x * 10 + ch - '0', ch = getchar();
        if(f) _x = -_x;
    }
    template <typename T, typename ... Args> inline void read(T &_f, Args& ... args) {
        read(_f), read(args ...);
    }
}

const int D = 5;
const int N = 4e5 + 5;
const LL oo = __LONG_LONG_MAX__;

int d, n, q, dim;
LL globalMinDist;
int cntNode, rt, ch[N][2], minVal[N][D], maxVal[N][D];

struct Node {
    int x[D];
    bool operator<(const Node &rhs) const {
        return x[dim] < rhs.x[dim];
    }
} ptr[N], val[N];

// 求两点之间的距离
LL dist(const Node &a, const Node &b) {
    LL ans = 0;
    for (int i = 0; i < d; i++)
        ans += 1LL * (a.x[i] - b.x[i]) * (a.x[i] - b.x[i]);
    return ans;
}

// O(n) 查找第 k 大元素
void nth_element(Node *arr, int rk, int len) {
    if (len <= 1)
        return;
    Node pivot = arr[rand() % len];
    int i = 0, j = 0, k = len;
    while (i < k) {
        if (arr[i] < pivot)
            std::swap(arr[i++], arr[j++]);
        else if (pivot < arr[i])
            std::swap(arr[i], arr[--k]);
        else
            i++;
    }
    if (rk < j)
        nth_element(arr, rk, j);
    else if (rk >= k)
        nth_element(arr + k, rk - k, len - k);
}

// 上传
void pushup(int p) {
    for (int i = 0; i < d; i++) {
        if (ch[p][0]) {
            minVal[p][i] = std::min(minVal[p][i], minVal[ch[p][0]][i]);
            maxVal[p][i] = std::max(maxVal[p][i], maxVal[ch[p][0]][i]);
        }
        if (ch[p][1]) {
            minVal[p][i] = std::min(minVal[p][i], minVal[ch[p][1]][i]);
            maxVal[p][i] = std::max(maxVal[p][i], maxVal[ch[p][1]][i]);
        }
    }
}

// 建树
void build(int &p, int l, int r, int id) {
    if (l > r)
        return;
    p = ++cntNode, dim = id;
    int mid = l + r >> 1;
    nth_element(ptr + l, (r - l + 1) / 2 - 1, r - l + 1);

    val[p] = ptr[mid];

    for (int i = 0; i < d; i++)
        minVal[p][i] = maxVal[p][i] = val[p].x[i];
    
    build(ch[p][0], l, mid - 1, (id + 1) % d);
    build(ch[p][1], mid + 1, r, (id + 1) % d);
    pushup(p);
}

// 搜索剪枝, credit: https://oi-wiki.org/ds/kdt/
LL getDist(int p, const Node &y) {
    LL ans = 0;
    for (int i = 0; i < d; i++)
        ans += 1LL * (val[p].x[i] - y.x[i]) * (val[p].x[i] - y.x[i]);
    return ans;
}

LL f(int p, const Node &y) {
    LL ans = 0;
    for (int i = 0; i < d; i++) {
        if (y.x[i] > maxVal[p][i])
            ans += 1LL * (y.x[i] - maxVal[p][i]) * (y.x[i] - maxVal[p][i]);
        if (y.x[i] < minVal[p][i])
            ans += 1LL * (minVal[p][i] - y.x[i]) * (minVal[p][i] - y.x[i]);
    }
    return ans;
}

// 查询
void query(int p, const Node &y) {
    if (!p)
        return;
    LL dist = getDist(p, y);
    if (dist < globalMinDist)
        globalMinDist = dist;
    LL ldis = oo, rdis = oo;
    if (ch[p][0])
        ldis = f(ch[p][0], y);
    if (ch[p][1])
        rdis = f(ch[p][1], y);
    if (ldis < rdis) {
        if (ldis < globalMinDist)
            query(ch[p][0], y);
        if (rdis < globalMinDist)
            query(ch[p][1], y);
    } else {
        if (rdis < globalMinDist)
            query(ch[p][1], y);
        if (ldis < globalMinDist)
            query(ch[p][0], y);
    }
}

int main() {
    srand(time(0));

    io::read(d, n);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < d; j++)
            io::read(ptr[i].x[j]);
    build(rt, 1, n, dim = 0);

    io::read(q);
    for (int i = 1; i <= q; i++) {
        Node y;
        for (int j = 0; j < d; j++)
            io::read(y.x[j]);
        globalMinDist = oo;
        query(rt, y);
        printf("%lld\n", globalMinDist);
    }
    return 0;
}