#include <bits/stdc++.h>

const int N = 1e7 + 5;

int n, a[N];

int random(int l, int r) {
    return rand() * rand() % (r - l + 1) + l;
}

int main() {
    srand(time(0));
    printf("%d\n", n = 1000000);
    for (int i = 1; i <= n; i++)
        a[i] = i;
    for (int i = 1; i <= n / 2; i++) {
        printf("A %d\n", a[i]);
    }
    for (int i = n / 2 + 1; i <= n; i++) {
        printf("C %d\n", a[n]);
    }
    return 0;
}