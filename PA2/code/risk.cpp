#include <cstdio>
#include <cstdlib>

#define LL long long

const int N = 1e6 + 5;

int n, a[N], k[N], T, maxValue;

// 这里参考了此篇博文中描述的单调队列的原理: https://zhuanlan.zhihu.com/p/437438743
class Queap {
private:
    int _head, _tail;
    int _a[N];

public:
    int front() {
        return _a[_head];
    }
    int back() {
        return _a[_tail - 1];
    }
    void enqueue(int x) {
        while (_head < _tail && a[x] > a[_a[_tail - 1]])
            _tail--;
        _a[_tail++] = x;
    }
    void dequeue() {
        _head++;
    }
    Queap() {
        _head = _tail = 0;
    }
} qp;


int cmp(const void* p1, const void* p2) {
    return *(int*)p1 - *(int*)p2;
}

int search(int l, int r, LL v) {
    if (v > maxValue)
        return r + 1;
    // 在 (l, r] 中找到第一个 >= v 的位置
    int mid = l + r >> 1;
    while (l < r - 1) {
        int mid = l + r >> 1;
        if (k[mid] < v) {
            l = mid;
        } else {
            r = mid;
        }
        if (l == r - 1)
            break;
    }
    return r;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        LL m;
        scanf("%lld", &m);
        while (qp.front() < i - m)
            qp.dequeue();
        k[i] = a[qp.front()];
        qp.enqueue(i);
    }

    qsort(k + 1, n, sizeof(int), cmp);
    maxValue = k[n];
    
    scanf("%d", &T);
    while (T--) {
        LL p, q;
        scanf("%lld %lld", &p, &q);
        int pos1 = search(0, n, p);
        int pos2 = search(0, n, q);
        printf("%d %d\n", pos1 - 1, pos2 - pos1);
    }
    return 0;
}
