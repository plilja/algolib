#include <iostream>
#include <vector>
#include <cassert>
#include "../../factorization.h"

using namespace std;

int main()
{
    int cases;
    scanf("%d", &cases);
    for (int i = 0; i < cases; ++i) {
        int num;
        scanf("%d", &num);
        vector<int> factors = divisors<int>(num);
        printf("divisors of %d == [", num);
        bool first = true;
        for (auto &factor : factors) {
            if (!first)
                printf(", ");
            printf("%d", factor);
            first = false;
        }
        printf("]\n");
    }
}
