#pragma once
#include <vector>
enum fail {
    a, b
};
class item {
public:
    item(int a, int b);
    int calc(int n);
private:
    int a;
    int b;
};

std::vector<int> sort(const std::vector<int> a);