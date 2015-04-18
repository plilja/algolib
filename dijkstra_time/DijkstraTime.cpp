/*
 * Author: Patrik Lilja
 * Date: 07-19-01
 */
#include "DijkstraTime.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
#include <functional>
#include <set>

DijkstraTime::DijkstraTime(size_t nrOfNodes, int source, std::vector<std::pair<int, int> > &_edges, std::vector<int> &firstDeparture, std::vector<int> &waitingTime, std::vector<int> &travelTime)
{
	this->nrOfNodes=nrOfNodes;
	parent=new int[nrOfNodes];
	initializeNodes(nrOfNodes, _edges, firstDeparture, waitingTime, travelTime);	
	this->source=source;
	for(size_t i=0; i<nrOfNodes; i++)
	{
		parent[i]=-1; 
	}
	construct();
}

int DijkstraTime::distance(int goal)
{
	if(dist[goal]<std::numeric_limits<int>::max())
	{
		return dist[goal];
	}
	return -1;
}

std::list<int> DijkstraTime::getPath(int goal)
{
	std::list<int> ans;
	if(dist[goal]>=std::numeric_limits<int>::max())
	{
		return ans;
	}
	int n=goal;
	while(n!=source)
	{
		if(n==-1)
		{
			//ERROR
			ans.clear();
			return ans;
		}
		ans.push_front(n);
		n=parent[n];
	}
	ans.push_front(source);
	return ans;
}

DijkstraTime::~DijkstraTime()
{
	delete[] nodes;
	delete[] parent;
	delete[] dist;
}

void DijkstraTime::construct()
{
	std::set<std::pair<int, int> > pq; //pair.first=min known cost to node nr pair.second
	bool *visited=new bool[nrOfNodes];
	for(int i=0; i<nrOfNodes; i++)
		visited[i]=false;
	dist=new int[nrOfNodes];
	for(int i=0; i<nrOfNodes; i++)
		dist[i]=std::numeric_limits<int>::max();

	dist[source]=0;
	pq.insert(std::make_pair(0, source));

	std::pair<int, int> p;
	int timeParent, possibleArrival;
	while(pq.size()>0)
	{
		p=*pq.begin();
		pq.erase(p);
		timeParent=p.first;
		if(visited[p.second] || timeParent==std::numeric_limits<int>::max())
		{
			continue;
		}
		visited[p.second]=true;
		for(std::list<edge>::iterator it=nodes[p.second].edges.begin(); it!=nodes[p.second].edges.end(); it++)
		{
			possibleArrival=getArrivalTime(timeParent, it->firstDeparture, it->waitingTime, it->travelTime);
			
			if((dist[it->to] > possibleArrival) && !(visited[it->to]))
			{
				parent[it->to]=p.second;
				pq.erase(std::make_pair(dist[it->to], it->to));
				dist[it->to]=possibleArrival;
				pq.insert(std::make_pair(dist[it->to], it->to));
			}
		}
	}
	delete[] visited;
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

void DijkstraTime::initializeNodes(size_t nrOfNodes, std::vector<std::pair<int, int> > &_edges, std::vector<int> &firstDeparture, std::vector<int> &waitingTime, std::vector<int> &travelTime)
{
	std::pair<int, int> p1;
	nodes=new node[nrOfNodes];
	edge e;
	for(size_t i=0; i<_edges.size(); i++)
	{
		e.to=_edges[i].second;
		e.firstDeparture=firstDeparture[i];
		e.travelTime=travelTime[i];
		e.waitingTime=waitingTime[i];
		nodes[_edges[i].first].edges.push_back(e);
	}
}

