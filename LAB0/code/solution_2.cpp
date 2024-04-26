#include <cstdio>
#include <ctime>

// int matrix[2000][2000];
// int rowsum[2000][2000];

int matrix[2005][2005];
long long rowsum[2005][2005];

int main() {
    time_t begin = clock();
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        rowsum[i][0] = 0;
        for (int j = 1; j <= m; ++j) {
            rowsum[i][j] = rowsum[i][j - 1] + matrix[i][j];
        }
    }
    scanf("%d", &q);
    // int sum = 0;
    for (int i = 1; i <= q; ++i) {
        int x, y, a, b;
        long long sum = 0; // 添加这一行
        scanf("%d %d %d %d", &x, &y, &a, &b);
        for (int j = 0; j < a; ++j) {
            // sum += rowsum[x + j][y + b] - rowsum[x + j][y];
            sum += rowsum[x + j][y + b - 1] - rowsum[x + j][y - 1];
        }
        // printf("%d\n", sum);
        printf("%lld\n", sum);
    }
    time_t end = clock();
    printf ("%d", end - begin);
    return 0;
}