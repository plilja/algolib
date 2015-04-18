/*
 * Author: Patrik Lilja
 * Date: 07-09-26
 * 
 * Se page:
 * http://kattis.csc.kth.se/problem?id=mincut
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
#include <set>

using namespace std;

/*
 * Se page:
 * http://kattis.csc.kth.se/problem?id=mincut
 * for a problem description. 
 */
int main()
{
	set<int> output;
	int nrOfNodes, nrOfEdges, cost;
	int sink, source;
	int a, b;
	list<pair<pair<int,int>, int> > nodes;
	int mc;
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
		mc=minCutNodes(output, nrOfNodes, source, sink, nodes);
		printf("%d\n", output.size());
		for(set<int>::iterator it=output.begin(); it!=output.end(); it++)
		{
			printf("%d\n", *it);
		}
		printf("\n");
	}
	return 0;
	
} 
