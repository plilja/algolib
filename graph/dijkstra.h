/*
 * A class that holds the representation of a graph and is able to answer questions 
 * about the minimum distance between a predetermined source and some goal node and
 * also produce a path of that minimum distance. 
 * 
 * To do this it uses Dijkstras algorithm. 
 */
#pragma once

#include <vector>

class Dijkstra
{
public:
	/*
	 * The contructor used to create a Dijkstra object. Everything will be initialized after
	 * a call to this contructor. Afterwards you may start querying the getPath() or distance
	 * methods. 
	 * 
	 * Running time O((|E|+|V|)*log|V|), |V|=nrOfNodes, |E|=nrOfEdges
	 * 
	 * Parameters:
	 * nrOfNodes: The nr of nodes in the graph. 
	 * _nodes: pair<pair, int>, the inner pair contains the indexes of the nodes that there is an edge between,
	 * 			the double in the outer pair contains the weight on that edge. Note that the indexes must be in the
	 * 			range 0<= index <=nrOfNodes-1 
	 * source: The index of the source nodes. 
	 */
	Dijkstra(std::size_t nr_of_nodes, const std::vector<std::pair<std::pair<int, int>, double> > &_nodes, int source);
	
	/*
	 * Get a path, if it exists, between the source and some node. 
	 * 
	 * Runs in time O(|V|)
	 * 
	 * Parameters:
	 * goal: The index of the goal node
	 * 
	 * Returns:
	 * A list of node indexes describing a path between the source and the goal. If
	 * a path between the nodes doesn't exist the list will be empty. If The goal node
	 * is the same as the source node, the list will simply contain this node. 
	 */
	std::vector<int> get_path(int goal);
	
	/*
	 * Get the best distance between the source and a goal node.
	 * 
	 * Parameters:
	 * goal: The index of the goal node. 
	 * 
	 * Returns:
	 * A double describing the minimum cost of a path between the source and thee goal node.
	 * If a path doesn't exist this integer will be -1. 
	 */
	double distance(int goal);
	
private:

	void construct();

    std::vector<double> dist;
	int source;
	int nr_of_nodes;
    std::vector<std::vector<std::pair<int, double>>> adj_list;
    std::vector<int> parent;
};

