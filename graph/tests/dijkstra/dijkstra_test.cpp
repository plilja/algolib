#include "../../dijkstra.h"
#include <cstdio>
#include <vector>

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
            nodes.push_back({{a, b}, (double)cost});
        }
        Dijkstra dj(n, nodes, source);
        for (int i = 0; i < queries; i++) {
            int goal;
            scanf("%d", &goal);
            int ans = (int) dj.distance(goal);
            if (ans == -1) {
                printf("Impossible\n");
            } else {
                printf("%d\n", ans);
            }
            printf("Path: ");
            vector<int> path = dj.getPath(goal);
            for (auto v : path) {
                printf("%d ", v);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;

}
