#include "../../fordfulkerson.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int nr_of_nodes, nr_of_edges, sink, source;
    while (4 == scanf("%d %d %d %d", &nr_of_nodes, &nr_of_edges, &source, &sink)) {
        if (nr_of_nodes == 0 && nr_of_edges == 0 && source == 0 && sink == 0) {
            break;
        }
        vector<FlowEdge> edges;
        for (int i = 0; i < nr_of_edges; i++) {
            int a, b, cost;
            scanf("%d %d %d", &a, &b, &cost);
            edges.push_back(FlowEdge({a, b, cost}));
        }
        auto result = minCutNodes(edges, nr_of_nodes, source, sink);
        printf("%lu\n", result.size());
        for (auto node : result) {
            printf("%d\n", node);
        }
        printf("\n");
    }
    return 0;

}
