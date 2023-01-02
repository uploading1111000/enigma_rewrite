#pragma once
#include <vector>
#include <iostream>
enum fail {
    a, b
};
namespace sorts {
    std::vector<int> mergesort(std::vector<int> a);
    std::vector<int> quicksort(std::vector<int> in);
}