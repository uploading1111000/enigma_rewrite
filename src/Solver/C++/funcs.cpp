#include "funcs.h"
item::item(int a, int b){
    item::a = a;
    item::b = b;
}
int item::calc(int n){
    if (n < 2) {
        return (n==0) ? a : b;
    }
    int j = a;
    int k = b;
    int l = a + b;
    for (int i = 1; i < n; i++){
        l = j + k;
        j = k;
        k = l;
    }
    return k;
}