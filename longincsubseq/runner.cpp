#include <iostream>
#include <math.h>
#include "increasingsubsequence.h"
#include <assert.h>

using namespace std;

int main()
{
    int seqLength;
    int seq[100010];
    while (1 == scanf("%d", &seqLength)) {
        for (int i = 0; i < seqLength; i++) {
            int nr;
            scanf("%d", &nr);
            seq[i] = nr;
        }
        unique_ptr<vector<int>> ans = longest_increasing_subsequence(seq, seqLength);
        printf("%lu\n", ans->size());

        for (auto i = ans->begin(); i != ans->end(); ++i) {
            printf("%d ", *i);
        }

        printf("\n");
    }
    return 0;
}
