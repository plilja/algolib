#pragma once

#include <vector>

struct EulerianPathResult {
    bool valid;
    std::vector<int> path;
};

/*
 * Try to find an eulerpath in a graph. 
 * 
 * Parameters:
 * edges: The edges that make up the graph. Note that edges are directed, i.e. an edge (u,v)
 * 			doesn't indicate an edge (v,u)
 * nr_of_nodes: the number of nodes in the graph.
 * 
 * Return:
 * An eulerian path result. If no eulerian path exists,
 * the valid flag of this result object will be false.
 */
EulerianPathResult eulerpath(const std::vector<std::pair<int, int> > &edges, int nr_of_nodes);

