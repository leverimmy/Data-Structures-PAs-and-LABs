#include <bits/stdc++.h>

int main() {

    freopen("06.in", "w", stdout);

    int n = 2048, m = 4096;

    for (int i = 0; i < n; i++) {
        if (i % 4 <= 1)
            putchar('A');
        else
            putchar('B');
    }
    for (int i = 0; i < n; i++) {
        if (i % 4 <= 1)
            putchar('A');
        else
            putchar('B');
    }
    puts("");

    printf("%d\n", m);

    for (int i = 0; i < m; i++) {
        if (i % 4 <= 1)
            printf("%d C\n", 2047);
        else
            printf("%d D\n", 2047);
    }

    return 0;
}