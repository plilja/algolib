/*
 * Author: Patrik Lilja
 * Date: 07-09-27
 */
#include "UndirectedNode.h"
#include <iostream>

UndirectedNode::UndirectedNode()
{
	visited=false;
	minTime=std::numeric_limits<int>::max();
}

UndirectedNode::UndirectedNode(const UndirectedNode &n)
{
	edgesOut=n.edgesOut;
	visited=n.visited;
	name=n.name;
	minTime=n.minTime;
}


UndirectedNode::~UndirectedNode()
{
	edgesOut.clear();
}

void UndirectedNode::addEdgeOut(UndirectedNode *n, int firstDeparture, int waitingTime, int travelTime)
{
	Edge e;
	e.dest=n;
	e.firstDeparture=firstDeparture;
	e.waitingTime=waitingTime;
	e.travelTime=travelTime;
	edgesOut.push_back(e);
}

UndirectedNode& UndirectedNode::operator= (const UndirectedNode &n)
{
	edgesOut=n.edgesOut;
	visited=n.visited;
	name=n.name;
	minTime=n.minTime;
	return *this;	
}


bool UndirectedNode::operator< (const UndirectedNode &n) const
{
	return name<n.name;	
}
