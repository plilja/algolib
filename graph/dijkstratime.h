/*
 * A class that holds the representation of a graph and is able to answer questions
 * about the minimum time distance between a predetermined source and some goal node and
 * also produce a path of that minimum distance.
 *
 * To to this it uses Dijkstras algorithm.
 */
#pragma once

#include <vector>

struct Edge {
    int to;
    int firstDeparture; // Tells when the first possible time to travel along this edge is
    int waitingTime; // Tells the time between each departure along this edge
    int travelTime;
};

class DijkstraTime {
public:
    /*
     * Parameters:
     * nrOfNodes: The nr of nodes in the graph.
     * source: The index of the source nodes.
     * _edges: The edges in the graph
     */
    DijkstraTime(int nrOfNodes, int source, const std::vector<std::vector<Edge>> &_edges);

    /*
     * Get a path, if it exists, between the source and some node.
     *
     * Returns:
     * A vector of node indexes describing a path between the source and the goal. If
     * a path between the nodes doesn't exist the list will be empty. If the goal node
     * is the same as the source node, the list will simply contain this node.
     */
    std::vector<int> getPath(int goal);

    /*
     * Get the minimum travel time between the source and a goal node.
     *
     * Returns:
     * An integer describing the minimum travel time of a path between the source and thee goal node.
     * If a path doesn't exist this integer will be -1.
     */
    int distance(int goal);

private:
    void construct();

    int nrOfNodes;
    int source;
    std::vector<int> parent;
    std::vector<int> dist;
    std::vector<std::vector<Edge>> adj_list;
};

