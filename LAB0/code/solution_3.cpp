#include <cstdio>
// #include <ctime>

const int N = 2e3 + 5;
const int M = 2e3 + 5;

int matrix[N][M];
int sumOfMatrix[N][M];

int main(int argc, char** argv) {

#ifndef _OJ_
    freopen("rand.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    /*从 https://zh.cppreference.com/w/cpp/header/ctime 查询相关用法*/
    // time_t begin = clock();
    int n, m, q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &matrix[i][j]);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            sumOfMatrix[i][j] = sumOfMatrix[i - 1][j] + sumOfMatrix[i][j - 1] - sumOfMatrix[i - 1][j - 1] + matrix[i][j];

    /*for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            printf ("%d ", sumOfMatrix[i][j]);
        puts("");
    }*/

    scanf("%d", &q);

    for (int i = 1; i <= q; ++i) {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);

        printf("%d\n", sumOfMatrix[x + a - 1][y + b - 1] - sumOfMatrix[x - 1][y + b - 1] - sumOfMatrix[x + a - 1][y - 1] + sumOfMatrix[x - 1][y - 1]);
    }
    // time_t end = clock();
    // printf ("%d", end - begin);
    return 0;
}