#include "../../fordfulkerson.h"
#include <cstdio>
#include <vector>
#include <list>

using namespace std;

int main()
{
    int nr_of_nodes, nr_of_edges, sink, source;
    while (4 == scanf("%d %d %d %d", &nr_of_nodes, &source, &sink, &nr_of_edges)) {
        if (nr_of_nodes == 0 && nr_of_edges == 0 && source == 0 && sink == 0) {
            break;
        }
        vector<FlowEdge> edges;
        for (int i = 0; i < nr_of_edges; i++) {
            int a, b, cost;
            scanf("%d %d %d", &a, &b, &cost);
            edges.push_back(FlowEdge({a - 1, b - 1, cost}));
        }
        auto result = max_flow(edges, nr_of_nodes, source, sink);
        printf("%d %d %lu\n", nr_of_nodes, result.flow, result.edges.size());
        for (auto &edge : result.edges) {
            printf("%d %d %d\n", edge.from + 1, edge.to + 1, edge.capacity);
        }
    }
}
