#include <bits/stdc++.h>

const int N = 5e5;

int n, m;

struct User {
    std::string name;
    int acc, sub;
} p[N + 1], q;

int random(int l, int r) {
    return rand() * rand() % (r - l + 1) + l;
}

int main() {
    srand(time(0));
    freopen("./dataset/poj.txt", "r", stdin);

    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    for (int i = 1; i <= N; i++) {
        int x;
        std::cin >> x >> p[i].name >> p[i].acc >> p[i].sub;
    }

    freopen("./dataset/1.in", "w", stdout);

    n = 100, m = 200;

    for (int i = 1; i <= n; i++) {
        q = p[i];
        std::cout << "0 " << q.name << " " << q.acc << std::endl;
    }
    for (int i = 1; i <= m; i++) {
        q = p[random(1, std::min(N, n * 2))];
        std::cout << "1 " << q.name << std::endl;
    }

    std::cout << 2 << std::endl;

    freopen("./dataset/2.in", "w", stdout);

    n = 10000, m = 20000;

    for (int i = 1; i <= n; i++) {
        q = p[N - i + 1];
        std::cout << "0 " << q.name << " " << q.acc << std::endl;
    }
    for (int i = 1; i <= m; i++) {
        q = p[random(N - n + 1, N)];
        std::cout << "1 " << q.name << std::endl;
    }

    std::cout << 2 << std::endl;

    freopen("./dataset/3.in", "w", stdout);

    n = 200000, m = 300000;

    for (int i = 1; i <= n; i++) {
        q = p[i];
        std::cout << "0 " << q.name << " " << q.acc << std::endl;
    }
    for (int i = 1; i <= m; i++) {
        q = p[random(1, std::min(N, n * 2))];
        std::cout << "1 " << q.name << std::endl;
    }
    
    std::cout << 2 << std::endl;

    return 0;
}