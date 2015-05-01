#include "../../pointinpolygon.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int num_points;
    while (scanf("%d", &num_points) && num_points > 0) {
        vector<pair<int, int>> poly;
        for (int i = 0; i < num_points; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            poly.push_back(make_pair(a, b));
        }
        int queries;
        scanf("%d", &queries);
        for (int i = 0; i < queries; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            auto res = pointinpoly({a, b}, poly);
            if (res == IN) {
                printf("in\n");
            } else if (res == ON) {
                printf("on\n");
            } else {
                printf("out\n");
            }
        }
    }
}
