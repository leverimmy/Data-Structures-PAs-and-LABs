#include <cstdio>
#include <cassert>
#include "hashtable.h"

int main(int argc, char* argv[]){
    
    if (argc != 3)
        return -1;

    hashing_strategy* h_stra;
    if (argv[1][0] == '0')
        h_stra = new bad_hashing();
    else if (argv[1][0] == '1')
        h_stra = new good_hashing();
    else
        return -1;

    collision_strategy* c_stra;
    if (argv[2][0] == '0')
        c_stra = new linear_probe();
    else if (argv[2][0] == '1')
        c_stra = new bidirectional_quadratic_probe();
    else if (argv[2][0] == '2')
        c_stra = new overflow_area();
    else
        return -1;


    // hashing_strategy* h_stra = new good_hashing();
    // collision_strategy* c_stra = new bidirectional_quadratic_probe();
    
    int type;
    char buffer[1000];int data;

    hashtable table(TABLE_SIZE, h_stra, c_stra);
    while(true){
        scanf("%d", &type);
        if(type == 0){
            scanf("%s", buffer);scanf("%d",&data);
            table.insert(hash_entry(buffer, data));
        }else if(type == 1){
            scanf("%s",buffer);
            printf("%d\n", table.query(buffer));
        }else break;
    }
    return 0;
}