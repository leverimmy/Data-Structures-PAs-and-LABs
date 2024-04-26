#include <bits/stdc++.h>

int main() {
    system("gen1.exe>inp.in");
    puts("Dataset 1:");
    auto s1 = clock();
    system("splay.exe");
    auto e1 = clock();
    printf("Splay: %.2f s\n", (double)(e1 - s1) / CLOCKS_PER_SEC);
    auto s2 = clock();
    system("AVL.exe");
    auto e2 = clock();
    printf("AVL: %.2f s\n", (double)(e2 - s2) / CLOCKS_PER_SEC);
    system("gen2.exe>inp.in");
    puts("Dataset 2:");
    auto s3 = clock();
    system("splay.exe");
    auto e3 = clock();
    printf("Splay: %.2f s\n", (double)(e3 - s3) / CLOCKS_PER_SEC);
    auto s4 = clock();
    system("AVL.exe");
    auto e4 = clock();
    printf("AVL: %.2f s\n", (double)(e4 - s4) / CLOCKS_PER_SEC);
    return 0;
}