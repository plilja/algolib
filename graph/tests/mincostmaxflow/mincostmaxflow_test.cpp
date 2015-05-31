#include "../../fordfulkerson.h"
#include <cstdio>
#include <vector>
#include <list>

using namespace std;

int main()
{
    int nrOfNodes, nrOfEdges, sink, source;
    while (4 == scanf("%d %d %d %d", &nrOfNodes, &nrOfEdges, &source, &sink)) {
        if (nrOfNodes == 0 && nrOfEdges == 0 && source == 0 && sink == 0) {
            break;
        }
        vector<CostFlowEdge> edges;
        for (int i = 0; i < nrOfEdges; i++) {
            int a, b, maxf, cost;
            scanf("%d %d %d %d", &a, &b, &maxf, &cost);
            edges.push_back(CostFlowEdge({a, b, maxf, cost}));
        }
        auto res = minCostMaxFlow(edges, nrOfNodes, source, sink);
        printf("%d %d\n", res.flow, res.cost);

        for (auto e : res.edges) {
            printf("%d %d %d %d\n", e.from, e.to, e.capacity, e.cost);
        }
    }
    return 0;

}
