#include <cstdio>

#define LL long long

const int N = 2e5 + 5;
const int M = 2e5 + 5;

int n, m;
LL x[N], y[N], tmp[N];

bool check(int i, LL tx, LL ty) {
    if (i == 0)
        return true;
    LL nomi = tx * y[i] + ty * x[i];
    LL deno = x[i] * y[i];
    return nomi >= deno;
}

int solve(LL tx, LL ty) {
    int l = 0, r = n + 1;
    while (l < r) { // [l, r) 为答案区间
        int mid = l + r >> 1;
        if (check(mid, tx, ty)) {
            l = mid;
        } else {
            r = mid;
        }
        if (l == r - 1)
            break;
    }
    return l;
}

void mergeSort(int l, int r, LL q[]) {
	if (l >= r)
        return;

	int mid = l + r >> 1;
	mergeSort(l, mid, q);
    mergeSort(mid + 1, r, q);
	
	int i = l, j = mid + 1, k = 0;
	while (i <= mid && j <= r) {    
		if(q[i] < q[j])
            tmp[k++] = q[i++];
		else
            tmp[k++] = q[j++];
	}
	while (i <= mid)
        tmp[k++] = q[i++];
	while (j <= r)
        tmp[k++] = q[j++];
    
	for (i = l, j = 0; i <= r; ++i, ++j)
		q[i] = tmp[j];
}

int main() {

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &x[i]);
    mergeSort(1, n, x);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &y[i]);
    mergeSort(1, n, y);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        LL px, py;
        scanf("%lld %lld", &px, &py);
        printf("%d\n", solve(px, py));
    }
    return 0;
}
