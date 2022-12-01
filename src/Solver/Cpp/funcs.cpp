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

int merge(int* starta, int lenA, int* startb, int lenB, int* out) {
    static int* partA = (int*)malloc(lenA * sizeof(int));
    static int* partB = (int*)malloc(lenB * sizeof(int));
    if (partA == NULL || partB == NULL) {
        return 0;
    }
    memcpy(partA, starta, sizeof(int) * lenA);
    memcpy(partB, startb, sizeof(int) * lenB);
    int pA = 0, pB = 0, pO = 0;
    fail f;
    while(pA < lenA && pB < lenB){
        if (partA[pA] <= partB[pB]) {
            out[pO] = partA[pA];
            pA++;
            f = a;
        }
        else {
            out[pO] = partB[pB];
            pB++;
            f = b;
        }
        pO++;
    }
    if (f == a)
        memcpy(out + pO, partB + pB, lenB - pB);
    else 
        memcpy(out + pO, partA + pA, lenA - pB);
    return 1;
}
std::vector<int> sort(std::vector<int> a) {
    std::vector<int> working = a;
    merge(&a[0], 3, &a[3], 3, &a[0]);
    return a;
}