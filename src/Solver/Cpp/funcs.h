#pragma once
#include <vector>
#include <iostream>
enum fail {
    a, b
};
int merge(int* starta, int lenA, int* startb, int lenB, int* out);
namespace sorts {
    std::vector<int> mergesort(std::vector<int> a);
    std::vector<int> quicksort(std::vector<int> in);
}