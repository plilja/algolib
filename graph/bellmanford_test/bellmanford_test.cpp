#include <cstdio>
#include <iostream>
#define NDEBUG
#include <cassert>
#include <vector>
#include "../bellmanford.h"
#include <string>
#include <queue>
#include <limits>

//To we want to print the path with each query?
#define PRINTPATH false

using namespace std;

int main()
{
	int nrOfNodes, nrOfEdges, cost, goal;
	int a, b, queries, source;
	Bellmanford *bf;
	vector<pair<pair<int,int>, double> > nodes;
	int ans;
	while(4==scanf("%d %d %d %d", &nrOfNodes, &nrOfEdges, &queries, &source))
	{
		if(nrOfNodes==0 && nrOfEdges==0 && queries==0 && source==0)
		{
			break;
		}
		nodes.clear();
			
		for(int i=0; i<nrOfEdges; i++)
		{
			scanf("%d %d %d", &a, &b, &cost);
			nodes.push_back( make_pair(make_pair(a,b), (double)cost) );
		}
		bf=new Bellmanford(nrOfNodes, nodes, source);
		for(int i=0; i<queries; i++)
		{
			scanf("%d", &goal);
			ans=(int)bf->distance(goal);
			if(ans==std::numeric_limits<int>::max())
			{
				printf("Impossible\n");
			}
			else if(ans==std::numeric_limits<int>::min())
			{
				printf("-Infinity\n");				
			}
			else
			{
				printf("%d\n", ans);
			}
			if(PRINTPATH)
			{
				printf("Path: ");
				list<int> path;
				bf->getPath(path, goal);
				for(list<int>::iterator it=path.begin(); it!=path.end(); it++)
				{
					printf("%d ", *it);
				}
				printf("\n\n");
			}
		}
		delete bf;
        printf("\n");
	}
	return 0;
	
} 
