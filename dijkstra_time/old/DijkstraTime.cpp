/*
 * Author: Patrik Lilja
 * Date: 07-19-01
 */ 
#include "UndirectedNode.h"
#include "DijkstraTime.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
#include <queue>
#include <functional>

using std::vector;
using std::pair;
using std::make_pair;
using std::priority_queue;
/*using std::cout;
using std::endl;*/

typedef UndirectedNode* puNode;

/*
 * Used to sort edges in a priority queue so the ones with the smallest 
 * weights gets placed first in the queue.
 * 
 * The second parameter contains the current known mincost. For some reason the uncommented 
 * comparison function below doesnt work. If you have a patch I'll be glad to hear it.
 */
struct compareEdges
{
	bool operator()(const pair<UndirectedNode*, int> &x, const pair<UndirectedNode*, int> &y)
	{
		return x.second > y.second;
	}
};
/*struct compareEdges//:std::binary_function<UndirectedNode*,UndirectedNode*,bool>
{
	bool operator()(const puNode &x, const puNode &y)
	{
		return x->minCost > y->minCost;
		//return x->minCost > y->minCost;
	}
};*/


DijkstraTime::DijkstraTime(size_t nrOfNodes, int source, std::vector<std::pair<int, int> > &_edges, std::vector<int> &firstDeparture, std::vector<int> &waitingTime, std::vector<int> &travelTime)
{
	this->nrOfNodes=nrOfNodes;
	parent=new UndirectedNode*[nrOfNodes];
	initializeNodes(nrOfNodes, _edges, firstDeparture, waitingTime, travelTime);	
	this->source=&nodes[source];
	for(size_t i=0; i<nrOfNodes; i++)
	{
		parent[i]=NULL; //visited=false, minCost=INF by default
	}
	construct();
}

int DijkstraTime::distance(int goal)
{
	if(nodes[goal].visited)
	{
		return nodes[goal].minTime;
	}
	return -1;
}

list<int> DijkstraTime::getPath(int goal)
{
	list<int> ans;
	if(!nodes[goal].visited)
	{
		return ans;
	}
	UndirectedNode *n=&nodes[goal];
	while(n!=source)
	{
		if(n==NULL)
		{
			ans.clear();
			return ans;
		}
		ans.push_front(n->name);
		n=parent[n->name];
	}
	ans.push_front(source->name);
	return ans;
}

DijkstraTime::~DijkstraTime()
{
	delete[] nodes;
	delete[] parent;
}

int DijkstraTime::getArrivalTime(int currentTime, int firstDeparture, int waitingTime, int travelTime)
{
	int arrival = std::max(currentTime, firstDeparture);
	arrival += travelTime;
	if(waitingTime!=0)
	{
		if(currentTime>firstDeparture)
		{
			int corr=(currentTime-firstDeparture)%waitingTime;
			if(corr!=0) //need to wait
			{
				arrival += waitingTime-(currentTime-firstDeparture)%waitingTime; //waiting time for next departure
			}
		}
	}
	else
	{
		if(currentTime>firstDeparture)
		{
			arrival=std::numeric_limits<int>::max();
		}
	}
	return arrival;
}

void DijkstraTime::construct()
{
	list<Edge>::iterator it;
	priority_queue<pair<UndirectedNode*, int>, vector<pair<UndirectedNode*, int> >, compareEdges > pq;
	source->minTime=0;
	pq.push(make_pair(source, 0));

	Edge e;
	UndirectedNode *p;
	int timeParent, possibleArrival;
	while(pq.size()>0)
	{
		p=pq.top().first;
		pq.pop();
		if(p->visited)
		{
			continue;
		}
		timeParent=p->minTime;
		p->visited=true;
		p->edgesOut.begin();

		for(it=p->edgesOut.begin(); it!=p->edgesOut.end(); it++)
		{
			e=*it;
			possibleArrival=getArrivalTime(timeParent, e.firstDeparture, e.waitingTime, e.travelTime);
			if(it->dest->minTime > possibleArrival)
			{
				parent[e.dest->name]=p;
				e.dest->minTime=possibleArrival;
				pq.push(make_pair(e.dest, possibleArrival));
			}
		}
	}
}


void DijkstraTime::initializeNodes(size_t nrOfNodes, std::vector<std::pair<int, int> > &_edges, std::vector<int> &firstDeparture, std::vector<int> &waitingTime, std::vector<int> &travelTime)
{
	pair<int, int> p1;
	pair<pair<int, int>, int> p2;
	nodes=new UndirectedNode[nrOfNodes];
	for(size_t i=0; i<nrOfNodes; i++)
	{
		nodes[i].name=i;
	}
	for(size_t i=0; i<_edges.size(); i++)
	{
		nodes[_edges[i].first].addEdgeOut(&nodes[_edges[i].second], firstDeparture[i], waitingTime[i], travelTime[i]);
	}
}

