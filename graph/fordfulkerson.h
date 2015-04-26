#pragma once

#include <vector>
#include <set>

struct FlowEdge {
	int from;
	int to;
	int capacity;
};

struct FlowResult {
	int flow;
    std::vector<FlowEdge> edges;
};

struct MinCutEdgesResult {
	int cost;
    std::vector<FlowEdge> edges;
};

/*
 * Solve a flow problem using the Edmonds-Karp version of the Ford-Fulkerson algorithm. 
 * 
 * Runs in time O(|N|*|V|^2)
 */
FlowResult max_flow(const std::vector<FlowEdge> &edges, int nr_of_nodes, int source, int sink);

/*
 * Find a minimal subset of edges that separates the source from the sink. The subset will be minimal
 * in respect to the sum of the weights of the edges. 
 * 
 * Runs in time O(|N|*|V|^2)
 */
MinCutEdgesResult min_cut_edges(const std::vector<FlowEdge> &edges, int nr_of_nodes, int source, int sink);

/*
 * Find a subset of nodes that separates the source from the sink such that the sum of the edges
 * from the subset to the nodes not in the set is minimal. 
 * 
 * Runs in time O(|N|*|V|^2)
 */
std::set<int> min_cut_nodes(const std::vector<FlowEdge> &edges, int nr_of_nodes, int source, int sink);


