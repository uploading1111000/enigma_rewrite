#include "funcs.h"
#include "funcs.h"

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
        memcpy(out + pO, partB + pB, (lenB - pB) * sizeof(int));
    else 
        memcpy(out + pO, partA + pA, (lenA - pA)*sizeof(int));
    return 1;
}
struct sortedList {
    int index;
    int length;
};
void printvec(std::vector<int> v) {
    std::cout << "\n";
    for (int i : v) {
        std::cout << i << ", ";
    }
}

std::vector<int> sorts::mergesort(std::vector<int> a) { //DOESN'T WORK
    std::vector<int> working = a;
    std::vector<sortedList> sorted;
    sorted.reserve(working.size());
    for (int i = 0; i < working.size(); i++) {
        sorted.push_back(sortedList{ i, 1 });
    }
    std::vector<sortedList> sortedC;
    while (sorted.size() > 1) {
        for (int i = 0; i < sorted.size()-1; i += 2) {
            merge(
                &working[sorted.at(i).index], sorted.at(i).length,
                &working[sorted.at(i + 1).index], sorted.at(i + 1).length,
                &working[sorted.at(i).index]
            );
            sortedC.push_back(sortedList{ sorted.at(i).index,sorted.at(i).length + sorted.at(i + 1).length });
        }
        if (sorted.size() & 1) 
            sortedC.push_back(sortedList{ sorted[sorted.size() - 1].index,sorted[sorted.size() - 1].length });
        sorted.swap(sortedC);
        sortedC.clear();
        sortedC.reserve(sorted.size() / 2);
    }
    return working;
}

std::vector<int> sorts::quicksort(std::vector<int> in)
{
    
    return std::vector<int>();
}
