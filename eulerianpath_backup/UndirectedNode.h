/*
 * Author: Patrik Lilja
 * Date: 07-09-27
 */
#ifndef UNDIRECTEDNODE_H_
#define UNDIRECTEDNODE_H_
#include <list>

using std::list;

class UndirectedNode
{
public:
	int name; 
	bool visited;
	
	//The edges that goes out of this node and the weight on them
	list<std::pair<UndirectedNode*, int> > edgesOut;
	
	//The edges that goes in to this node and the weight on them
	list<std::pair<UndirectedNode*, int> > edgesIn;
	
	/*
	 * Default constructor. Visited will be initialized to false.
	 */
	UndirectedNode();
	
	/*
	 * Destructor
	 */
	~UndirectedNode();

	/*
	 * Returns true if the name of this node is smaller
	 * than the name of node n. 
	 */
	bool operator< (const UndirectedNode &n) const;
	
	/*
	 * Add an edge out of this node and a cost. 
	 */
	void addEdgeOut(UndirectedNode *e, int cost);
	
	/*
	 * Add an edge out in to this node and a cost. 
	 */
	void addEdgeIn(UndirectedNode *e, int cost);
	
};

#endif /*NODE_H_*/
