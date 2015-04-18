/*
 * Author: Patrik Lilja
 * Date: 07-10-05
 */ 
#include "FlowGraph.h"
#include "Node.h"

FlowGraph::~FlowGraph()
{
	delete[] V;
}

FlowGraph::FlowGraph(int size, int source, int sink)
{
	nrOfNodes=size;
	V = new Node[size]; 
	s = source;
	t = sink;	
}

void FlowGraph::addEdge(Edge &edge)
{
	int from = edge.getNodeFrom();
	V[from].push_back(edge);
	
}

Node* FlowGraph::getNode(int node)
{
	return &V[node];
}

int FlowGraph::getNumberOfNodes()
{
	return nrOfNodes;
}

Node* FlowGraph::getSink()
{
	return &V[t];
}

Node* FlowGraph::getSource()
{
	return &V[s];
}
