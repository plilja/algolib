/*
 * Find all minimum distances between nodes in a directed graph. This
 * is done using the Floyd-Warshall algorithm.
 */
#pragma once

#include <math.h>
#include <vector>

class Floydw {
public:
    /*
     * The constructor will perform the actual algorithm and therefore runs
     * in time O(N^3)
     *
     * Parameters:
     * wt = wt[i][j] contains the cost to travel between node i and node j. Note that
     * 			if the graph may contain multiple edges this number should be the smallest
     * 			edge between i and j. If no edge exists between i and j, wt[i][j] must equal
     * 			std::numeric_limits<int>::max().
     */
    Floydw(std::vector <std::vector<double>> wt, int n);

    /*
     * Get the minimum distance between two nodes.
     *
     * Runs in time O(1)
     *
     * Parameters:
     * s: The index of the source node
     * d: The index of the destination node
     *
     * Returns: The minimum distance between node s and node d. If there exists infinitely short paths between
     * 			s and d the return value will equal std::numeric_limits<int>::min(). If a path doesn't exist
     * 			the return value will equal std::numeric_limits<int>::max().
     */
    double distance(int s, int d);

private:
    std::vector <std::vector<double>> dist;
    int n;
};

