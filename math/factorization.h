#include <vector>
#include <cmath>

#pragma once

template <typename T>
std::vector<T> factorization(T x)
{
    std::vector<T> ans;
    while (x % 2 == 0) {
        ans.push_back(2);
        x /= 2;
    }
    T upper_lim = sqrt(x);
    for (int i = 3; i <= upper_lim; i += 2) {
        bool redefine_limit = false;
        while (x % i == 0) {
            ans.push_back(i);
            x /= i;
            redefine_limit = true;
        }
        if (redefine_limit)
            upper_lim = sqrt(x);

    }
    if (x > 1) 
        ans.push_back(x);
    
    return ans;
}
