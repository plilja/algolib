#include "../../bellmanford.h"
#include <cstdio>
#include <vector>
#include <limits>

using namespace std;

int main()
{
    int n, e, queries, source;
    while (4 == scanf("%d %d %d %d", &n, &e, &queries, &source)) {
        if (n == 0 && e == 0 && queries == 0 && source == 0) {
            break;
        }
        vector<pair<pair<int, int>, double> > nodes;

        for (int i = 0; i < e; i++) {
            int a, b, cost;
            scanf("%d %d %d", &a, &b, &cost);
            nodes.push_back(make_pair(make_pair(a, b), (double)cost));
        }
        BellmanFord bf(n, nodes, source);
        for (int i = 0; i < queries; i++) {
            int goal;
            scanf("%d", &goal);
            double ans = bf.distance(goal);
            if (ans == std::numeric_limits<double>::infinity()) {
                printf("Impossible\n");
            } else if (ans == -std::numeric_limits<double>::infinity()) {
                printf("-Infinity\n");
            } else {
                printf("%d\n", (int)ans);
            }
            printf("Path: ");
            vector<int> path = bf.getPath(goal);
            for (auto v : path) {
                printf("%d ", v);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;

}
