#include <bits/stdc++.h>

const int N = 1e7 + 5;

int n, a[N];
std::set<int> s;

int random(int l, int r) {
    return rand() * rand() % (r - l + 1) + l;
}

int main() {
    srand(time(0));
    printf("%d\n", n = 1000000);
    for (int i = 1; i <= n; i++)
        a[i] = i;
    std::random_shuffle(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        int opt = random(1, 3);
        if (s.empty() || opt == 1) {
            printf("A %d\n", a[i]);
            s.insert(a[i]);
        } else if (opt == 2) {
            std::set<int>::const_iterator it(s.begin());
            std:advance(it, random(0, s.size() - 1));
            printf("B %d\n", *it);
            s.erase(it);
        } else if (opt == 3) {
            printf("C %d\n", a[i]);
        }
    }
    return 0;
}