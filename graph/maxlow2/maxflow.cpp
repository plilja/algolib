/*
 * Author: Patrik Lilja
 * Date: 07-09-26
 * 
 * Se page:
 * http://kattis.csc.kth.se/problem?id=maxflow
 * for a problem description. 
 */
#include "fordfulkerson.h"
#include <cstdio>
#include <iostream>
#define NDEBUG
#include <cassert>
#include <vector>
#include <string>
#include <queue>
#include <list>

using namespace std;

/*
 * Se page:
 * http://kattis.csc.kth.se/problem?id=maxflow
 * for a problem description. 
 */
int main()
{
	std::list<std::pair<std::pair<int, int>, int> > output;
	int nrOfNodes, nrOfEdges, cost;
	int sink, source;
	int a, b;
	list<pair<pair<int,int>, int> > nodes;
	int flow;
	//generateCase(nrOfNodes, nrOfEdges, source, goal, nodes);
	while(4==scanf("%d %d %d %d", &nrOfNodes, &nrOfEdges, &source, &sink))
	{
		if(nrOfNodes==0 && nrOfEdges==0 && source==0 && sink==0)
		{
			break;
		}
		nodes.clear();
		output.clear();
		for(int i=0; i<nrOfEdges; i++)
		{
			scanf("%d %d %d", &a, &b, &cost);
			nodes.push_back( make_pair(make_pair(a,b), cost) );
		}
		flow=fordFulkerson(output, nrOfNodes, source, sink, nodes);
		printf("%d %d %d\n", nrOfNodes, flow, output.size());
		for(std::list<std::pair<std::pair<int, int>, int> >::iterator it=output.begin(); it!=output.end(); it++)
		{
			printf("%d %d %d\n", it->first.first, it->first.second, it->second);
		}
		printf("\n");
	}
	return 0;
	
} 
