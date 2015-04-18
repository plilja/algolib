/*
 * Author: Patrik Lilja
 * Date: 07-10-04
 *
 * Se page:
 * http://kattis.csc.kth.se/problem?id=allpairspath
 * for a problem description.
 */
#include <iostream>
#include <math.h>
#include <string>
#include "Floyd.h"
#include <vector>
#include <limits>

using namespace std;

/*
 * Se page:
 * http://kattis.csc.kth.se/problem?id=allpairspath
 * for a problem description.
 */
int main()
{
    const int INF = std::numeric_limits<int>::max();
    const int NEG_INF = std::numeric_limits<int>::min();
    vector<vector<double>> wt(150, vector<double>(150));
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
        Floyd fd(150, wt);
        for (int i = 0; i < queries; i++) {
            scanf("%d %d", &source, &goal);
            ans = (int)fd.distance(source, goal);
            if (ans == INF) {
                printf("Impossible\n");
            } else if (ans == NEG_INF) {
                printf("-Infinity\n");

            } else {
                printf("%d\n", ans);
            }
        }
        //fd.printAll();
        printf("\n");
    }
    return 0;
}
