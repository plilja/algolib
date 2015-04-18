/*
 * Author: Patrik Lilja
 * Date: 07-09-26
 * 
 * Se page:
 * http://kattis.csc.kth.se/problem?id=minspantree
 * for a problem description. 
 */
#include "maxflow.h"
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
 * http://kattis.csc.kth.se/problem?id=minspantree
 * for a problem description. 
 */
int main()
{
	std::list<std::pair<std::pair<int, int>, int> > output;
	int nrOfNodes, nrOfEdges, cost, goal;
	int sink, source;
	int a, b, queries;
	vector<pair<pair<int,int>, int> > nodes;
	int ans;
	//generateCase(nrOfNodes, nrOfEdges, source, goal, nodes);
	//while(4==scanf("%d %d %d %d", &nrOfNodes, &nrOfEdges, &queries, &source))
	{
		scanf("%d", &nrOfNodes);
		scanf("%d %d", &source, &sink);
		scanf("%d", &nrOfEdges);
		nodes.clear();
		output.clear();
			
		for(int i=0; i<nrOfEdges; i++)
		{
			scanf("%d %d %d", &a, &b, &cost);
			nodes.push_back( make_pair(make_pair(a,b), cost) );
		}
		fordFulkerson(output, nrOfNodes, source, sink, nodes);
		
		

		scanf("%d", &goal);
		if(ans==-1)
		{
			printf("Impossible\n");
		}
		else
		{
			printf("%d\n", ans);
		}
	}
	return 0;
	
} 
