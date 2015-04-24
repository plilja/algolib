#include "../../longincsubseq.h"
#include <cstdio>

using namespace std;

int main()
{
    int seq_length;
    while (1 == scanf("%d", &seq_length)) {
        vector<int> seq(seq_length);
        for (int i = 0; i < seq_length; i++) {
            scanf("%d", &seq[i]);
        }
        vector<int> ans = longincsubseq(seq);
        printf("%lu\n", ans.size());

        for (auto i : ans) {
            printf("%d ", i);
        }

        printf("\n");
    }
    return 0;
}
