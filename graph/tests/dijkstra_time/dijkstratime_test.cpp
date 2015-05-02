#include "../../dijkstratime.h"
#include <cstdio>
#include <vector>

using namespace std;

int main()
{
    int nrOfNodes, nrOfEdges, queries, source;
    while (4 == scanf("%d %d %d %d", &nrOfNodes, &nrOfEdges, &queries, &source)) {
        if (nrOfNodes == 0 && nrOfEdges == 0 && queries == 0 && source == 0) {
            break;
        }
        vector<vector<Edge>> edges(nrOfNodes, vector<Edge>());

        for (int i = 0; i < nrOfEdges; i++) {
            int a, b, first, wait, trTime;
            scanf("%d %d %d %d %d", &a, &b, &first, &wait, &trTime);
            auto edge = Edge({b, first, wait, trTime});
            edges[a].push_back(edge);
        }
        DijkstraTime dj(nrOfNodes, source, edges);
        for (int i = 0; i < queries; i++) {
            int goal;
            scanf("%d", &goal);
            int ans = dj.distance(goal);
            if (ans == -1) {
                printf("Impossible\n");
            } else {
                printf("%d\n", ans);
            }
            printf("Path: ");
            auto path = dj.getPath(goal);
            for (int v : path) {
                printf("%d ", v);
            }
            printf("\n\n");
        }
        printf("\n");
    }
    return 0;

}
