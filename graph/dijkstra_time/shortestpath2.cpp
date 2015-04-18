/*
 * Author: Patrik Lilja
 * Date: 07-19-01
 * 
 * Se page:
 * http://kattis.csc.kth.se/problem?id=shortestpath2
 * for a problem description. 
 */
#include <cstdio>
#include <iostream>
#define NDEBUG
#include <cassert>
#include <vector>
#include "DijkstraTime.h"
#include <string>
#include <queue>

//To we want to print the path with each query?
#define PRINTPATH false

using namespace std;

/*
 * Test function. 
 */
/*void generateCase(int &nrOfNodes, int &nrOfEdges, int &source, int &goal, vector<pair<pair<int,int>, int> > &nodes)
{
	srand(time(NULL));
	int cost;
	for(int j=0; j<10000; j++)
	{
		nodes.clear();
		nrOfNodes=1+rand()%1000;
		assert(nrOfNodes>0);
		nrOfEdges=rand()%1500;
		nrOfEdges=0;
		int a, b;
	
		source=rand()%nrOfNodes;
		cost=rand()%30000;
		for(int i=0; i<nrOfEdges; i++)
		{
			a=rand()%nrOfNodes;
			b=rand()%nrOfNodes;
			nodes.push_back(make_pair(make_pair(a,b), cost));
			
			
		}
		int pathlen=rand() % (1+nrOfNodes/2);
		int pathcost=0;
		a=source;
		for(int i=0; i<pathlen; i++)
		{
			cost=rand()%5000;
			b=rand()%nrOfNodes;
			pathcost += cost;
			nodes.push_back(make_pair(make_pair(a, b),cost));
			a=b;
		}
		DijkstraTime *d=new DijkstraTime(nrOfNodes, nodes, source);
		assert(d->distance(b) <=pathcost);
		delete d;
	}	
}*/

/*
 * Se page:
 * http://kattis.csc.kth.se/problem?id=shortestpath2
 * for a problem description. 
 */
int main()
{
	int nrOfNodes, nrOfEdges, cost, goal;
	int a, b, queries, source, trTime, first, wait;
	DijkstraTime *dj;
	vector<pair<int,int> > edges;
	vector<int> firstDeparture;
	vector<int> waitingTime;
	vector<int> travelTime;
	int ans;
	//generateCase(nrOfNodes, nrOfEdges, source, goal, nodes);
	while(4==scanf("%d %d %d %d", &nrOfNodes, &nrOfEdges, &queries, &source))
	{
		if(nrOfNodes==0 && nrOfEdges==0 && queries==0 && source==0)
		{
			break;
		}
		edges.clear();
		firstDeparture.clear();
		waitingTime.clear();
		travelTime.clear();
			
		for(int i=0; i<nrOfEdges; i++)
		{
			scanf("%d %d %d %d %d", &a, &b, &first, &wait, &trTime);
			edges.push_back(make_pair(a,b));
			firstDeparture.push_back(first);
			waitingTime.push_back(wait);
			travelTime.push_back(trTime);
		}
		dj=new DijkstraTime(nrOfNodes, source, edges, firstDeparture, waitingTime, travelTime);
		for(int i=0; i<queries; i++)
		{
			scanf("%d", &goal);
			ans=dj->distance(goal);
			if(ans==-1)
			{
				printf("Impossible\n");
			}
			else
			{
				printf("%d\n", ans);
			}
			if(PRINTPATH)
			{
				printf("Path: ");
				list<int> path=dj->getPath(goal);
				for(list<int>::iterator it=path.begin(); it!=path.end(); it++)
				{
					printf("%d ", *it);
				}
				printf("\n\n");
			}
		}
		delete dj;
		cout<<endl;
	}
	return 0;
	
} 
