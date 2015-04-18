/*
 * Author: Patrik Lilja
 * Date: 07-09-27
 * 
 * Se page:
 * http://kattis.csc.kth.se/problem?id=eulerianpath
 * for a problem description. 
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include "eulerianpath.h"
#include <list>

using namespace std;


/*
 * Se page: 
 * http://kattis.csc.kth.se/problem?id=eulerianpath
 */
int main()
{
	int nrOfNodes, nrOfEdges;
	int a, b;
	vector<pair<int, int> > edges;
	list<int> ans;
	while(true)
	{
		scanf("%d %d", &nrOfNodes, &nrOfEdges);
		if(nrOfNodes==0 && nrOfEdges==0)
		{
			break;
		}
		ans.clear();
		edges.clear();
			
		for(int i=0; i<nrOfEdges; i++)
		{
			scanf("%d %d", &a, &b);
			edges.push_back(make_pair(a,b));
		}
		if(!eulerpath(ans, edges, nrOfNodes))
		{
			printf("Impossible\n");
		}
		else
		{
			for(list<int>::iterator it=ans.begin(); it!=ans.end(); it++)
			{
				printf("%d ",*it);
			}
			printf("\n");
		}
	}
	return 0;
	
} 
