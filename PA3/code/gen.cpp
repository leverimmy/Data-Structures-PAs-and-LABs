#include <bits/stdc++.h>

const int N = 4e5 + 5;

int n, m;
char str[N];

int random(int l, int r) {
    return rand() * rand() % (r - l + 1) + l;
}

int main() {
    freopen("inp.in", "w", stdout);
    srand(time(0));
    n = random(10, 10), m = random(10, 10);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++)
        str[i] = random('a', 'b');
    puts(str);
    for (int i = 1; i <= m / 2; i++) {
        int opt = random(1, 3);
        printf("%d ", opt);
        if (opt == 1) {
            int pos = random(0, n);
            char c = random('a', 'b');
            printf("%d %c\n", pos, c);
            n++;
        } else if (opt == 2) {
            int pos = random(0, n - 1);
            printf("%d\n", pos);
            n--;
        } else if (opt == 3) {
            int l = random(0, n - 1), r = random(l, n - 1);
            printf("%d %d\n", l, r);
        }
    }
    for (int i = m / 2 + 1; i <= m; i++) {
        int opt = 4, l = random(0, n - 1), r = random(l, n - 1), len = random(1, n - r);
        printf("%d %d %d %d\n", opt, l, r, len);
    }

    return 0;
}