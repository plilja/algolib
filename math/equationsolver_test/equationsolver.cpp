#include "../gaussjordan.h"
#include <vector>
#include <cstdio>

using namespace std;

int main()
{
    int n;
    while (true) {
        scanf("%d", &n);
        if (n == 0)
            break;
        vector<double> x;
        vector<vector<double> > A(n, vector<double>(n));
        vector<double> y(n);
        double tmp;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%lf", &tmp);
                A[i][j] = tmp;
            }
        }
        for (int i = 0; i < n; ++i) {
            scanf("%lf", &tmp);
            y[i] = tmp;
        }
        auto ans = gaussjordan<double>(A, y, x);
        if (ans == INCONSISTENT) {
            printf("inconsistent\n");
        } else if (ans == MULTIPLE) {
            printf("multiple\n");
        } else if (ans == SUCCESS) {
            for (int i = 0; i < n; ++i) {
                printf("%.4lf ", x[i]);
            }
            puts("");
        }
    }
    return 0;
}
