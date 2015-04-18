/*
 * Author: Patrik Lilja
 * Date: 07-10-05
 */ 
#ifndef FLOWGRAPH_H_
#define FLOWGRAPH_H_

#include <list>
#include "Edge.h"
#include "Node.h"

class FlowGraph
{
public:
	FlowGraph(int size, int source, int sink);
	virtual ~FlowGraph();

	//void addNode(Node node);
	void addEdge(Edge &edge);
	Node* getNode(int node);
	int getNumberOfNodes();
	Node* getSink();
	Node* getSource();

private:
	Node *V;
	int s,t;
	int nrOfNodes;
};

#endif /*FLOWGRAPH_H_*/
