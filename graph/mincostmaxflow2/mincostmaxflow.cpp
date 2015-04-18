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

const bool PRINT_PATH=true;

/*
 * Se page:
 * http://kattis.csc.kth.se/problem?id=maxflow
 * for a problem description. 
 */
int main()
{
	std::list<std::pair<std::pair<int, int>, std::pair<int,int> > > output;
	int nrOfNodes, nrOfEdges, maxf, cost;
	int sink, source;
	int a, b;
	std::list<std::pair<std::pair<int, int>, std::pair<int,int> > > nodes;
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
			scanf("%d %d %d %d", &a, &b, &maxf, &cost);
			nodes.push_back( make_pair(make_pair(a,b), make_pair(maxf, cost)) );
		}
		flow=fordFulkerson(cost, output, nrOfNodes, source, sink, nodes);
		printf("%d %d\n", flow, cost);

		if(PRINT_PATH)
		{
			for(std::list<std::pair<std::pair<int, int>, std::pair<int,int> > >::iterator it=output.begin(); it!=output.end(); it++)
			{
				printf("%d %d %d %d\n", it->first.first, it->first.second, it->second.first, it->second.second);
			}
			printf("\n\n");
		}
		
	}
	return 0;
	
} 
