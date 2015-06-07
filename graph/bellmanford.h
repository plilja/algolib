/*
 * An implemenation of the Bellman-Ford algorithm for finding the shortest distance
 * between two vertices in a graph.
 */
#pragma once

#include <vector>
#include <list>

class BellmanFord
{
public:
    /*
     * Parameters:
     * n: The nr of nodes in the graph.
     * _edges: pair<pair, int>, the inner pair contains the indexes of the nodes that there is an edge between,
     * 			the double in the outer pair contains the weight on that edge. Note that the indexes must be in the
     * 			range 0<= index <=nr_of_nodes - 1
     * source: The index of the source nodes.
     */
    BellmanFord(int n, std::vector <std::pair<std::pair<int, int>, double>> &_edges, int source);

    /*
     * Get a path, if it exists, between the source and some node. If no path exists, an empty list
     * is returned.
     */
    std::vector<int> getPath(int goal);

    /*
     * Get the best distance between the source and a goal node.
     *
     * Returns:
     * A double describing the minimum cost of a path between the source and thee goal node.
     * If a path doesn't exist this double will be equal to std::numeric_limits<double>::infinity(). If
     * the path would end up in a negativa cycle the result will equal -std::numeric_limits<double>::infinity()
     */
    double distance(int goal);

private:

    void construct();

    int source;
    int nr_of_nodes;
    std::vector <std::pair<std::pair<int, int>, double>> edges;
    std::vector<double> dist;
    std::vector<int> parent;
};

