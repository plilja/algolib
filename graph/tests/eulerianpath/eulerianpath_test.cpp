#include "../../eulerianpath.h"
#include <cstdio>
#include <vector>

using namespace std;

int main()
{

    while (true) {
        int n, e;
        scanf("%d %d", &n, &e);
        if (n == 0 && e == 0) {
            break;
        }
        vector<pair<int, int>> edges;

        for (int i = 0; i < e; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            edges.push_back({a, b});
        }
        auto eulerpath_result = eulerpath(edges, n);

        if (eulerpath_result.valid) {
            for (auto v : eulerpath_result.path) {
                printf("%d ", v);
            }
            printf("\n");
        } else {
            printf("Impossible\n");
        }
    }
    return 0;

}
