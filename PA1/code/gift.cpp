#include <cstdio>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define LL long long
#define ULL unsigned long long

const int N = 40 + 5;

int n, p, x[N], y[N];
LL ans;

std::vector <LL> pre;

int main() {

    scanf("%d %d", &n, &p);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &x[i], &y[i]);

    for (unsigned u = 0; u < 1u << (n / 2); u++) {
        LL sum = 0LL;
        for (int i = 0; i < n / 2; i++) {
            if (u & (1u << i)) {
                sum += x[i];
            } else {
                sum += y[i];
            }
        }
        pre.push_back(sum);
    }

    std::sort(pre.begin(), pre.end());

    for (unsigned u = 0; u < 1u << (n - n / 2); u++) {
        LL sum = 0LL;
        for (int i = n / 2; i < n; i++) {
            if (u & (1u << i - n / 2)) {
                sum += x[i];
            } else {
                sum += y[i];
            }
        }
        LL it = std::upper_bound(pre.begin(), pre.end(), p - sum) - pre.begin();
        ans += it;
    }

    printf("%lld", ans);

    return 0;
}
