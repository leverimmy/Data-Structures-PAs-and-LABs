#include<cstdio>
#include<cstdlib>
#include<ctime>
int main(){
    // randomly generate input data:
    // n between 10 and 100,
    // m between 10 and 100
    // matrix element between 0 and 1000
    // q between 10 and 20
    // x between 1 and n
    // y between 1 and m
    // a between 1 and n-x+1,
    // b between 1 and m-y+1
    srand(time(0));
    int n = 1000;
    int m = 1000;
    printf("%d %d\n",n,m);
    //TODO: generate matrix, q, and queries.
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            printf("%d ",rand()%1001);
        }printf("\n");
    }
    int q = 100;
    printf("%d\n",q);
    for(int i=1;i<=q;++i){
        int x = rand()%n + 1,y = rand()%m + 1;
        int a = rand()%(n-x+1)+1, b = rand()%(m-y+1) + 1;
        printf("%d %d %d %d\n",x,y,a,b);
    }
    return 0;
}