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
    int firstDeparture;
    int waitingTime;
    int travelTime;
};

class DijkstraTime {
public:
    /*
     * Parameters:
     * nrOfNodes: The nr of nodes in the graph.
     * source: The index of the source nodes.
     * _edges: pair<pair, int>, The edges in the graph
     * firstDeparture: the i:th element of this vector corresponds to the i:th edge of the _edges vector
     * 					and tells when the first possible time is to travel the i:th edge.
     * waitingTime: Same conditions as firstDeparture but tells how long in between departures for each edge.
     * travelTime: Same as firstDeparture and waitingTime but tells how long time a travel along an edge takes.
     */
    //DijkstraTime(size_t nrOfNodes, int source, std::vector<std::pair<int, int> > &_edges, std::vector<int> &firstDeparture, std::vector<int> &waitingTime, std::vector<int> &travelTime);
    DijkstraTime(int nrOfNodes, int source, const std::vector<std::vector<Edge>> &_edges);

    /*
     * Get a path, if it exists, between the source and some node.
     *
     * Returns:
     * A list of node indexes describing a path between the source and the goal. If
     * a path between the nodes doesn't exist the list will be empty. If The goal node
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

