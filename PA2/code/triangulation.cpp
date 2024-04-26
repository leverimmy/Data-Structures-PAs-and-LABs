#include <cstdio>
#include <cstdlib>
#include <cassert>

const int N = 1e6 + 5;

int n, maxI = -1, minI = 1, rot, maxID;

struct Point {
    int x, y, id;
} p[N];

template <typename T> class Stack {
private:
    T _a[N];
    int _top;
public:
    void push(T v) {
        _a[_top++] = v;
    }
    void pop() {
        _top--;
    }
    T top1() {
        return _a[_top - 1];
    }
    T top2() {
        return _a[_top - 2];
    }
    bool empty() {
        return _top == 0;
    }
    int size() {
        return _top;
    }
    Stack() {
        _top = 0;
    }
};

Stack<Point> stk;

int cmp(const void* p1, const void* p2) {
    Point p11 = *(Point*)p1, p22 = *(Point*)p2;
    return p11.x - p22.x;
}

bool onSameLine(const Point& a, const Point& b) {
    return 1LL * (maxID - a.id) * (maxID - b.id) >= 0;
}

bool ang(const Point& a, const Point& b, const Point& c) {
    // 检查以 b 为顶点，角 abc 是否为劣角
    if (b.id < maxID)
        return (1LL * (b.x - a.x) * (c.y - b.y) - 1LL * (b.y - a.y) * (c.x - b.x)) * rot < 0;
    else
        return (1LL * (b.x - a.x) * (c.y - b.y) - 1LL * (b.y - a.y) * (c.x - b.x)) * rot > 0;
}

void print(const Point& a, const Point& b, const Point& c) {
    printf("%d %d %d %d %d %d\n", a.x, a.y, b.x, b.y, c.x, c.y);
}

int main() {
#ifndef _OJ_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &p[i].x, &p[i].y);
        minI = p[i].x < p[minI].x ? i : minI;
    }

    for (int i = minI, cnt = 1; cnt <= n; cnt++) {
        p[i].id = (i - minI + n) % n + 1;
        int j = (i == 1) ? n : (i - 1);
        int k = (i == n) ? 1 : (i + 1);
        if (maxI == -1 && cnt >= 2 && p[i].x > p[j].x && p[i].x > p[k].x)
            maxI = i;
        (i == n) ? (i = 1) : (i++);
    }

    int pre = (maxI == 1) ? n : (maxI - 1);
    int nxt = (maxI == n) ? 1 : (maxI + 1);

    if (1LL * (p[maxI].x - p[pre].x) * (p[nxt].y - p[maxI].y) - 1LL * (p[maxI].y - p[pre].y) * (p[nxt].x - p[maxI].x) < 0)
        rot = 1;
    else
        rot = -1;

    maxID = p[maxI].id;

    qsort(p + 1, n, sizeof(Point), cmp);

    stk.push(p[1]), stk.push(p[2]);
    for (int i = 3; i <= n; i++) {
        Point t = stk.top1();
        // stack: [bottom, ..., u, v: i
        if (!onSameLine(t, p[i])) {
            while (stk.size() >= 2) {
                Point u = stk.top2();
                Point v = stk.top1();
                print(p[i], v, u);
                stk.pop();
            }
            stk.pop();
            stk.push(t), stk.push(p[i]);
        } else {
            while (stk.size() >= 2) {
                Point u = stk.top2();
                Point v = stk.top1();
                if (ang(u, v, p[i])) {
                    print(p[i], v, u);
                    stk.pop();
                } else {
                    break;
                }
            }
            stk.push(p[i]);
        }
    }
    return 0;
}
