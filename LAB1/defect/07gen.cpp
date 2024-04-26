#include <bits/stdc++.h>

int main() {

    freopen("07.in", "w", stdout);

    int n = 2048, m = 3;

    for (int i = 0; i < n; i++) {
        if (i % 4 <= 1)
            putchar('A');
        else
            putchar('B');
    }
    for (int i = 0; i < n; i++) {
        if (i % 4 <= 1)
            putchar('C');
        else
            putchar('D');
    }
    for (int i = 0; i < n; i++) {
        if (i % 4 <= 1)
            putchar('A');
        else
            putchar('B');
    }
    puts("");

    printf("%d\n", m);

    puts("3072 D");
    puts("2048 D");
    puts("2048 B");

    return 0;
}