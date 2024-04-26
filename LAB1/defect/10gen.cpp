#include <bits/stdc++.h>

int main() {

    freopen("10.in", "w", stdout);

    int n = 4098, m = 1;

    for (int i = 0; i < n; i++) {
        if (i % 4 <= 1)
            putchar('A');
        else
            putchar('B');
    }
    puts("");

    printf("%d\n", m);

    puts("2048 A");
    return 0;
}