#include "../../gaussjordan.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int n;
    while (true) {
        scanf("%d", &n);
        if (n == 0)
            break;
        vector<pair<bool, double> > x;
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
        auto ans = gaussjordanplus<double>(A, y, x);
        if (ans == INCONSISTENT) {
            printf("inconsistent\n");
        } else if (ans == MULTIPLE || ans == SUCCESS) {
            for (int i = 0; i < n; ++i) {
                if (x[i].first) {
                    if (isZero(x[i].second)) {
                        printf("0.0000");
                    } else {
                        printf("%.4lf ", x[i].second);
                    }
                } else {
                    printf("? ");
                }
            }
            puts("");
        }

    }
    return 0;
}
