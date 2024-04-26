#include <cstdio>
#include <ctime>

// int matrix[2000][2000];
int matrix[2005][2005];

int main() {
    time_t begin = clock();
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    scanf("%d", &q);
    // int sum = 0;
    for (int i = 1; i <= q; ++i) {
        int x, y, a, b;
        long long sum = 0; // 添加这一行
        scanf("%d %d %d %d", &x, &y, &a, &b);
        for (int j = 0; j < a; ++j) {
            for (int k = 0; k < b; ++k) {
                sum += matrix[x + j][y + k];
            }
        }
        // printf("%d\n", sum);
        printf("%lld\n", sum);
    }
    time_t end = clock();
    printf ("%d", end - begin);
    return 0;
}