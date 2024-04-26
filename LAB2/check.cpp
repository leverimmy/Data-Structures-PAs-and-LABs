#include <bits/stdc++.h>

char cmd[200];

int main() {

    const char* h_str[] = { "bad_hashing", "good_hashing" };
    const char* c_str[] = { "linear_probe", "bidirectional_quadratic_probe", "overflow_area" };

    freopen("result.txt", "w", stdout);
    for (int op3 = 1; op3 <= 3; op3++) {
        for (int op1 = 0; op1 <= 1; op1++) {
            for (int op2 = 0; op2 <= 2; op2++) {
                double t1 = clock();
                sprintf(cmd, ".\\framework\\main.exe %d %d < .\\dataset\\%d.in > .\\dataset\\%d%d%d.out", op1, op2, op3, op1, op2, op3);
                system(cmd);
                double t2 = clock();
                printf("Case Number: %d\tTime used = %.3fs\tCombination: (%s,\t%s)\n", op3, (t2 - t1) / CLOCKS_PER_SEC, h_str[op1], c_str[op2]);
            }
        }
    }

    return 0;
}