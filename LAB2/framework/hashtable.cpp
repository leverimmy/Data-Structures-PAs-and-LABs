#include "hashtable.h"
int naive_hashing::operator()(char* str, int N){
    if(str == NULL) return 0;
    else return (str[0]+N)%N;
}

int bad_hashing::operator()(char* str, int N) {
    if (str == NULL)
        return 0;
    int sum = 0;
    for (int i = 0; str[i]; i++)
        sum = (sum + str[i]) % N;
    return sum;
}

int good_hashing::operator()(char* str, int N) {
    const int p = 19260817;
    int sum = 0;
    for (int i = 0; str[i]; i++)
        sum = (1LL * sum * p % N + str[i]) % N;
    return sum;
}

int linear_probe::operator()(hash_entry* Table, int table_size, int last_choice){
    return (last_choice + 1) % table_size;
}
void linear_probe::init(){
    return;// do nothing
}

int bidirectional_quadratic_probe::operator()(hash_entry* Table, int table_size, int last_choice){
    if (currentDirection == LEFT) {
        currentDirection = RIGHT;
        int delta = 2LL * currentRadius * currentRadius % table_size;
        return (last_choice - delta + table_size) % table_size;
    }
    if (currentDirection == RIGHT) {
        currentDirection = LEFT;
        currentRadius++;
        int delta = (1LL * (currentRadius - 1) * (currentRadius - 1) % table_size
                    + 1LL * currentRadius * currentRadius % table_size 
                    ) % table_size;
        
        return (last_choice + delta) % table_size;
    }
}
void bidirectional_quadratic_probe::init(){
    currentDirection = RIGHT;
    currentRadius = 0;
}

int overflow_area::operator()(hash_entry* Table, int table_size, int last_choice){
    return BIAS + (++currentLocation);
}
void overflow_area::init(){
    currentLocation = 0;
}