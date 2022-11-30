#include "funcs.h"
item::item(int a, int b){
    item::a = a;
    item::b = b;
}
int item::calc(int n){
    for (int i = 2; i < n; i++){
        int c = a + b;
        a = b;
        b = c;
    }
    return a;
}