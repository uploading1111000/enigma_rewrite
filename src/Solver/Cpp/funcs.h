#pragma once
#include <vector>

class item {
public:
    item(int a, int b);
    int calc(int n);
private:
    int a;
    int b;
};

std::vector<int> sort(std::vector<int> a);