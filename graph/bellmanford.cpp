/*
 * Author: Patrik Lilja
 * Date: 07-09-30
 */ 
#include "BellmanFord.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
#include <queue>
#include <functional>

Bellmanford::Bellmanford(int nrOfNodes, std::vector<std::pair<std::pair<int, int>, double> > &_edges, int source)
{
	this->nrOfNodes=nrOfNodes;
	parent=new int[nrOfNodes];
	nrOfEdges=_edges.size();
	edges=new Edge[nrOfEdges];
	this->source=source;
	dist=new double[nrOfNodes];
	initializeEdges(_edges);
	for(int i=0; i<nrOfNodes; i++)
	{
		dist[i]=std::numeric_limits<int>::max();		
	}
	for(int i=0; i<nrOfNodes; i++)
	{
		parent[i]=-1; 
	}
	construct();
}

double Bellmanford::distance(int goal)
{
	return dist[goal];
}

void Bellmanford::getPath(std::list<int> &path, int goal)
{
	path.clear();
	if(dist[goal]==std::numeric_limits<int>::max() || dist[goal]==std::numeric_limits<int>::min()) 
	{
		//impossible case 
		return;
	}
	int current=goal;
	while(current!=source)
	{
		path.push_front(current);
		current=parent[current];
	}
	path.push_front(source);
}

Bellmanford::~Bellmanford()
{
	delete[] dist;
	delete[] edges;
	delete[] parent;
}

void Bellmanford::construct()
{
	dist[source]=0.0;

	Edge uv;
	for(int i=0; i<nrOfNodes-1; i++)
	{
		for(int j=0; j<nrOfEdges; j++)
		{
			uv=edges[j];
			if(dist[uv.source]==std::numeric_limits<int>::max())
			{
				continue; //addition would cause integer overflow
			}
			if(dist[uv.dest]>dist[uv.source]+uv.weight)
			{
				dist[uv.dest]=dist[uv.source]+uv.weight;
				parent[uv.dest]=uv.source;
			}
		}
	}
	
	//Check for negative cycles
	for(int i=0; i<nrOfNodes-1; i++)
	{
		for(int j=0; j<nrOfEdges; j++)
		{
			uv=edges[j];
			if(dist[uv.source]==std::numeric_limits<int>::max())
			{
				continue; //addition would cause integer overflow
			}
			if(dist[uv.source]==std::numeric_limits<int>::min())
			{
				dist[uv.dest]=std::numeric_limits<int>::min();
				continue;
			}
			if(dist[uv.dest]>dist[uv.source]+uv.weight)
			{
				dist[uv.dest]=std::numeric_limits<int>::min();
			}
		}
	}	
}

void Bellmanford::initializeEdges(std::vector<std::pair<std::pair<int, int>, double> > &_edges)
{
	int i=0;
	for(std::vector<std::pair<std::pair<int, int>, double> >::iterator it=_edges.begin(); it!=_edges.end(); it++)
	{
		edges[i].source=it->first.first;
		edges[i].dest=it->first.second;
		edges[i].weight=it->second;
		i++;
	}
}

