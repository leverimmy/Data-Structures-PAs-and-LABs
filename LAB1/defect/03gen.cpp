#include <bits/stdc++.h>

int main() {

    freopen("03.in", "w", stdout);

    int n = 500000, m = 250000;

    for (int i = 0; i < n; i++) {
        if (i % 4 <= 1)
            putchar('A');
        else
            putchar('B');
    }
    puts("");

    printf("%d\n", m);

    for (int i = 1; i <= m; i++) {
        if (i & 1) {
            puts("0 A");
        } else 
            puts("0 B");
    }

    return 0;
}