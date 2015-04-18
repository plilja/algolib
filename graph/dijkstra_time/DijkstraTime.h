/*
 * Author: Patrik Lilja
 * Date: 07-19-01
 * 
 * A class that holds the representation of a graph and is able to answer questions 
 * about the minimum time distance between a predetermined source and some goal node and
 * also produce a path of that minimum distance.  
 * 
 * To to this it uses Dijkstras algorithm. 
 */
#ifndef DIJKSTRATIME_H_
#define DIJKSTRATIME_H_

#include <vector>
#include <list>

struct edge
{
	int to;
	int firstDeparture;
	int waitingTime;
	int travelTime;
};

struct node
{
	std::list<edge> edges; //pair.first=where to, pair.second=edge cost
};

class DijkstraTime
{
public:
	/*
	 * The contructor used to create a DijkstraTime object. Everything will be initialized after
	 * a call to this contructor. Afterwards you may start querying the the getPath() or distance
	 * methods. 
	 * 
	 * Running time O((|E|+|V|)*log|V|), |V|=nrOfNodes, |E|=nrOfEdges
	 * 
	 * Parameters:
	 * nrOfNodes: The nr of nodes in the graph. 
	 * source: The index of the source nodes. 
	 * _edges: pair<pair, int>, The edges in the graph
	 * firstDeparture: the i:th element of this vector corresponds to the i:th edge of the _edges vector
	 * 					and tells when the first possible time is to travel the i:th edge.
	 * waitingTime: Same conditions as firstDeparture but tells how long in between departures for each edge.
	 * travelTime: Same as firstDeparture and waitingTime but tells how long time a travel along an edge takes. 
	 */
	DijkstraTime(size_t nrOfNodes, int source, std::vector<std::pair<int, int> > &_edges, std::vector<int> &firstDeparture, std::vector<int> &waitingTime, std::vector<int> &travelTime);
	
	/*
	 * Destructor. 
	 */
	virtual ~DijkstraTime();
	
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
	std::list<int> getPath(int goal);
	
	/*
	 * Get the minimum travel time between the source and a goal node.
	 * 
	 * Parameters:
	 * goal: The index of the goal node. 
	 * 
	 * Returns:
	 * An integer describing the minimum travel time of a path between the source and thee goal node.
	 * If a path doesn't exist this integer will be -1. 
	 */
	int distance(int goal);
	
private:
	/*
	 * Calculate when you would arrive given some conditions. 
	 * 
	 * Params:
	 * currentTime: what time is it now?
	 * firstDeparture: When is the first departure?
	 * waitingTime: How far is it between depatures?
	 * travelTime: How long does the travel take? 
	 */
	int getArrivalTime(int currentTime, int firstDeparture, int waitingTime, int travelTime);

	/*
	 * Perform the actual Dijkstra algorithm. 
	 */
	void construct();

	/*
	 * Perform necesary initializations on the nodes variable. 
	 */
	void initializeNodes(size_t nrOfNodes, std::vector<std::pair<int, int> > &_edges, std::vector<int> &firstDeparture, std::vector<int> &waitingTime, std::vector<int> &travelTime);

	int *dist;
	int source;
	int nrOfNodes;
	node *nodes;
	int *parent;
};

#endif /*DIJKSTRATIME_H_*/
