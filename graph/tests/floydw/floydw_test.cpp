#include <iostream>
#include <math.h>
#include <string>
#include "../../floydw.h"
#include <vector>
#include <limits>

using namespace std;

int main() {
    const int INF = std::numeric_limits<int>::max();
    const int NEG_INF = std::numeric_limits<int>::min();
    vector <vector<double>> wt(150, vector<double>(150));
    int nrOfNodes, nrOfEdges, goal, cost;
    int a, b, queries, source;
    int ans;
    while (3 == scanf("%d %d %d", &nrOfNodes, &nrOfEdges, &queries)) {
        if (nrOfNodes == 0 && nrOfEdges == 0 && queries == 0) {
            break;
        }
        for (int i = 0; i < 150; i++) {
            for (int j = 0; j < 150; j++) {
                wt[i][j] = INF;
            }
        }

        for (int i = 0; i < nrOfEdges; i++) {
            scanf("%d %d %d", &a, &b, &cost);
            wt[a][b] = std::min(wt[a][b], (double) cost); //only save the cheapest edge
        }
        Floydw fd(wt, 150);
        for (int i = 0; i < queries; i++) {
            scanf("%d %d", &source, &goal);
            ans = (int) fd.distance(source, goal);
            if (ans == INF) {
                printf("Impossible\n");
            } else if (ans == NEG_INF) {
                printf("-Infinity\n");

            } else {
                printf("%d\n", ans);
            }
        }
        printf("\n");
    }
    return 0;
}
