#include <cstdio>
#include <cassert>

const int N = 4e5 + 5;

int n, m;
char str[N];
char tmp[N];

int main() {
    freopen("inp.in", "r", stdin);
    freopen("ans.out", "w", stdout);
    scanf("%d %d", &n, &m);
    if (n)
        scanf("%s", str);
    for (int i = 1; i <= m; i++) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int pos;
            char c[2];
            scanf("%d %s", &pos, c);
            for (int j = n; j > pos; j--)
                str[j] = str[j - 1];
            str[pos] = c[0];
            n++;
        } else if (opt == 2) {
            int pos;
            scanf("%d", &pos);
            for (int j = pos; j < n - 1; j++)
                str[j] = str[j + 1];
            n--;
        } else if (opt == 3) {
            int l, r;
            scanf("%d %d", &l, &r);
            for (int j = l; j <= r; j++)
                tmp[j] = str[j];
            for (int j = l; j <= r; j++)
                str[l + r - j] = tmp[j];
        } else if (opt == 4) {
            int l, r, len;
            scanf("%d %d %d", &l, &r, &len);
            bool flag = true;
            for (int j = 1; j <= len; j++)
                if (str[l + j - 1] != str[r + j - 1])
                    flag = false;
            putchar(flag ? 'T' : 'F');
        } else {
            assert(0);
        }
        // puts(str);
    }
    return 0;
}