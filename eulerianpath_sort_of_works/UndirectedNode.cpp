/*
 * Author: Patrik Lilja
 * Date: 07-09-27
 */
#include "UndirectedNode.h"
#include <iostream>

UndirectedNode::UndirectedNode()
{
	visited=false; 
}

UndirectedNode::~UndirectedNode()
{
	edgesIn.clear();
	edgesOut.clear();
}

void UndirectedNode::addEdgeOut(UndirectedNode *e, int cost)
{
	edgesOut.push_back(std::make_pair(e, cost));
	e->addEdgeIn(this, cost);
}

void UndirectedNode::addEdgeIn(UndirectedNode *e, int cost)
{
	edgesIn.push_back(std::make_pair(this, cost));
}


bool UndirectedNode::operator< (const UndirectedNode &n) const
{
	return name<n.name;	
}
