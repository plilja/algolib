/*
 * Author: Patrik Lilja
 * Date: 07-09-27
 */
#ifndef UNDIRECTEDNODE_H_
#define UNDIRECTEDNODE_H_
#include <list>

using std::list;

struct Edge;

class UndirectedNode
{
public:
	int name;
	int minTime; 
	bool visited;
	
	//The edges that goes out of this node and the weight on them
	list<Edge> edgesOut;
		
	/*
	 * Default constructor. Visited will be initialized to false.
	 */
	UndirectedNode();

	UndirectedNode(const UndirectedNode &n);
	
	/*
	 * Destructor
	 */
	~UndirectedNode();

	UndirectedNode& operator= (const UndirectedNode &n);


	/*
	 * Returns true if the name of this node is smaller
	 * than the name of node n. 
	 */
	bool operator< (const UndirectedNode &n) const;
	
	/*
	 * Add an edge out of this node and a cost. 
	 */
	void addEdgeOut(UndirectedNode *n, int firstDeparture, int waitingTime, int travelTime);
		
};

struct Edge {
	UndirectedNode *dest;
	int firstDeparture;
	int waitingTime;
	int travelTime;	
};

#endif /*NODE_H_*/
