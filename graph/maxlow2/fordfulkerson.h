/*
 * Author: Patrik Lilja
 * Date: 07-10-05
 * 
 * Provides an algorithm for finding the maximum flow in a flow graph and also
 * constructing a solution corresponding to that maximum flow. Also provides
 * functions for finding minimal cuts in flowgraphs. 
 */ 
#ifndef FORDFULKERSON_H_
#define FORDFULKERSON_H_

#include <vector>
#include <set>
#include <list>
#include <queue>
#include <limits>

struct edge{
	int from; //index of the from node
	int to; //index of the to node
	int c; //capacity
	int cf; //rest capacity
	int f; //flow
	edge *reverse;
	
};

struct node{
	std::vector<edge*> edges;
};

/*
 * Solve a flow problem using the Edmonds-Karp version of the Ford-Fulkerson algorithm. 
 * 
 * Runs in time O(|N|*|V|^2)
 * 
 * Parameters:
 * output: output parameter, each edge with a positive flow will be listed here.
 * nrOfNodes: the number of nodes. Note that nodes are assumed to be indexed from 0..nrOfNodes-1
 * source: the index of the source node. 
 * sink: The index of the sink node.
 * edges: The edges in the graph. The rightmost int describes the capacity throught the edge. The left pair
 * 		tells which nodes the edge goes between. 
 * 
 * Returns:
 * The flow between the source and the sink
 */
int fordFulkerson(std::list<std::pair<std::pair<int, int>, int> > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, int> > edges);

/*
 * Find a minimal subset of edges that separates the source from the sink. The subset will be minimal
 * in respect to the sum of the weights of the edges. 
 * 
 * Runs in time O(|N|*|V|^2)
 * 
 * Parameters:
 * output: output parameter, each edge in the minimal cut will be listed here
 * nrOfNodes: the number of nodes. Note that nodes are assumed to be indexed from 0..nrOfNodes-1
 * source: the index of the source node. 
 * sink: The index of the sink node.
 * edges: The edges in the graph. The rightmost int describes the capacity throught the edge. The left pair
 * 		tells which nodes the edge goes between. 
 * 
 * Returns:
 * The flow between the source and the sink
 */
int minCutEdges(std::list<std::pair<int, int> > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, int> > edges);

/*
 * Find a subset of nodes that separates the source from the sink such that the sum of the edges
 * from the subset to the nodes not in the set is minimal. 
 * 
 * Runs in time O(|N|*|V|^2)
 * 
 * Parameters:
 * output: output parameter, each node in minimal cut will be listed here
 * nrOfNodes: the number of nodes. Note that nodes are assumed to be indexed from 0..nrOfNodes-1
 * source: the index of the source node. 
 * sink: The index of the sink node.
 * edges: The edges in the graph. The rightmost int describes the capacity throught the edge. The left pair
 * 		tells which nodes the edge goes between. 
 * 
 * Returns:
 * The flow between the source and the sink
  * 
 * 
 */
int minCutNodes(std::set<int> &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, int> > edges);


#endif /*FORDFULKERSON_H_*/
