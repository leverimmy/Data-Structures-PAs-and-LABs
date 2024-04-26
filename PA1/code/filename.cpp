#include <cstdio>
#include <cstring>

const int N = 501000 + 5;
const int M = 501000 + 5;
const int K = 1e2 + 5;

int n, m, k;
int f[2][M];
char a[N], b[M];

inline int max(int _a, int _b) {
    return _a > _b ? _a : _b;
}

inline int min(int _a, int _b) {
    return _a < _b ? _a : _b;
}

int main() {

    scanf("%d %d %d", &n, &m, &k);
    scanf("%s %s", a + 1, b + 1);
    
    for (int i = 1; i <= n; i++) {
        int l = max(1, i - k), r = min(i + k, m);
        for (int j = l; j <= r; j++) {
            f[i & 1][j] = 0;
            if (a[i] == b[j]) {
                f[i & 1][j] = f[(i + 1) & 1][j - 1] + 1;
            } else {
                f[i & 1][j] = max(f[(i + 1) & 1][j], f[i & 1][j - 1]);
            }
        }
    }

    // “所需要的” k 的值
    int needK = m + n - 2 * f[n & 1][m];

    printf("%d", needK > k ? -1 : needK);

    return 0;
}
