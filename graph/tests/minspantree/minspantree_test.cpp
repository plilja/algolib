#include <cstdio>
#include <vector>
#include "../../minspantree.h"

using namespace std;

int main()
{
    while (true) {
        int n, e;
        scanf("%d %d", &n, &e);
        if (n == 0 && e == 0) {
            break;
        }
        vector <pair<pair<int, int>, double>> edges;

        for (int i = 0; i < e; i++) {
            int a, b, cost;
            scanf("%d %d %d", &a, &b, &cost);
            edges.push_back(make_pair(make_pair(a, b), (double) cost));
        }

        auto ans = prim(edges, n);
        if (ans.valid) {
            vector<pair<int, int>> edges = ans.edges;
            sort(edges.begin(), edges.end());
            printf("%d\n", (int) ans.total_cost);
            for (auto p : edges) {
                printf("%d %d\n", p.first, p.second);
            }
        } else {
            printf("Impossible\n");
        }
    }
    return 0;

}
