#include <cstdio>
#include <iostream>
#define NDEBUG
#include <cassert>
#include <vector>
#include <string>
#include <queue>
#include <list>

using namespace std;

int main()
{
	srand(time(NULL));
	int nrOfNodes; 
	scanf("%d", &nrOfNodes);
	int source, sink;
	scanf("%d %d", &source, &sink);
	int nrOfEdges;
	scanf("%d", &nrOfEdges);
	int a, b, c, cost;
	printf("%d %d %d %d\n", nrOfNodes, nrOfEdges, --source, --sink); 
	for(int i=0; i<nrOfEdges; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		cost=1+rand() % 100;
		printf("%d %d %d %d\n", --a, --b, c, cost);
	}
	
}