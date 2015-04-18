/*
 * A class that holds the representation of a graph and is able to answer questions 
 * about the minimum distance between a predetermined source and some goal node and
 * also produce a path of that minimum distance. 
 * 
 * To to this it uses BellmanFords algorithm which means that the weights on the edges may
 * be negative. 
 */
#ifndef BELLMANFORD_H_
#define BELLMANFORD_H_

#include <vector>
#include <list>

struct Edge {
    int source;
    int dest;
    double weight;
};

class Bellmanford
{
public:
	/*
	 * The contructor used to create a BellmanFord object. Everything will be initialized after
	 * a call to this contructor. Afterwards you may start querying the the getPath() or distance
	 * methods. 
	 * 
	 * Running time O(|E|*|V|)
	 * 
	 * Parameters:
	 * nrOfNodes: The nr of nodes in the graph. 
	 * _edges: pair<pair, int>, the inner pair contains the indexes of the nodes that there is an edge between,
	 * 			the double in the outer pair contains the weight on that edge. Note that the indexes must be in the
	 * 			range 0<= index <=nrOfNodes-1 
	 * source: The index of the source nodes. 
	 */
	Bellmanford(int nrOfNodes, std::vector<std::pair<std::pair<int, int>, double> > &_edges, int source);
	
	/*
	 * Destructor. 
	 */
	virtual ~Bellmanford();
	
	/*
	 * Get a path, if it exists, between the source and some node. 
	 * 
	 * Runs in time O(|V|)
	 * 
	 * Parameters:
	 * goal: The index of the goal node
	 * 
	 * path: This list will contain the answer of the function call. a list of node indexes 
	 * describing a path between the source and the goal. If
	 * a path between the nodes doesn't exist the list will be empty. If the path
	 * would mean ending up in an infinite negative cycle the list will also be empty. 
	 * If The goal node is the same as the source node, the list will simply contain this node. 
	 */
	void getPath(std::list<int> &path, int goal);
	
	/*
	 * Get the best distance between the source and a goal node.
	 * 
	 * Parameters:
	 * goal: The index of the goal node. 
	 * 
	 * Returns:
	 * A double describing the minimum cost of a path between the source and thee goal node.
	 * If a path doesn't exist this double will be equal to std::numeriv_limits<int>::max(). If
	 * the path would end up in a negativa cycle the result will equal std::numeric_limits<int>::min() 
	 */
	double distance(int goal);
	
private:

	/*
	 * Perform the actual BellmanFord algorithm. 
	 */
	void construct();

	/*
	 * Perform necesary initializations on the edges variable. 
	 */
	void initializeEdges(std::vector<std::pair<std::pair<int, int>, double> > &edges);	

	int source;
	int nrOfNodes;
	int nrOfEdges;
	Edge *edges;
	double *dist;
	int *parent;
};

#endif /*BELLMANFORD_H_*/
