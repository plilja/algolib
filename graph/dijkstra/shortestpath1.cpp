#include <cstdio>
#include <iostream>
#define NDEBUG
#include <cassert>
#include <vector>
#include "Dijkstra.h"
#include <string>
#include <queue>

//To we want to print the path with each query?
#define PRINTPATH false

using namespace std;

int main()
{
    int nrOfNodes, nrOfEdges, cost, goal;
    int a, b, queries, source;
    Dijkstra *dj;
    vector<pair<pair<int, int>, double> > nodes;
    int ans;
    while (4 == scanf("%d %d %d %d", &nrOfNodes, &nrOfEdges, &queries, &source)) {
        if (nrOfNodes == 0 && nrOfEdges == 0 && queries == 0 && source == 0) {
            break;
        }
        nodes.clear();

        for (int i = 0; i < nrOfEdges; i++) {
            scanf("%d %d %d", &a, &b, &cost);
            nodes.push_back(make_pair(make_pair(a, b), (double)cost));
        }
        dj = new Dijkstra(nrOfNodes, nodes, source);
        for (int i = 0; i < queries; i++) {
            scanf("%d", &goal);
            ans = (int) dj->distance(goal);
            if (ans == -1) {
                printf("Impossible\n");
            } else {
                printf("%d\n", ans);
            }
            if (PRINTPATH) {
                printf("Path: ");
                list<int> path = dj->getPath(goal);
                for (list<int>::iterator it = path.begin(); it != path.end(); it++) {
                    printf("%d ", *it);
                }
                printf("\n\n");
            }
        }
        delete dj;
        printf("\n");
    }
    return 0;

}
