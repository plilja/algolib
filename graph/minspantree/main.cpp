/*
 * Author: Patrik Lilja
 * Date: 07-09-26
 * 
 * Se page:
 * http://kattis.csc.kth.se/problem?id=minspantree
 * for a problem description. 
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include "minspantree.h"
#include <string>
#include <algorithm>

using namespace std;

/*
 * Se page:
 * http://kattis.csc.kth.se/problem?id=minspantree
 * for a problem description. 
 */
int main()
{
	int nrOfNodes, nrOfEdges, cost;
	double price;
	int a, b;
	std::vector<std::pair<std::pair<int, int>, double> > edges;
	vector <pair<int, int> > ans;
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
			scanf("%d %d %d", &a, &b, &cost);
			edges.push_back(make_pair(make_pair(a, b), (double)cost));
		}

		if(nrOfNodes-1>nrOfEdges || !prim(ans, price, nrOfNodes, edges))
		{
			cout<<"Impossible"<<endl;
		}
		else
		{
			sort(ans.begin(), ans.end());
			printf("%d\n", (int)price);
			for(vector<pair<int, int> >::iterator it=ans.begin(); it!=ans.end(); it++)
			{
				printf("%d %d\n", it->first, it->second);
			}
		}
	}
	return 0;
	
} 
