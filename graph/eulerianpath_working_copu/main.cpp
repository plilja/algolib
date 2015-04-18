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
#define NDEBUG
#include <cassert>
#include <vector>
#include "eulerianpath.h"
#include <string>
#include <list>

using namespace std;

/*
 * Test case creator. 
 */
/*void createTestCase(int &nrOfNodes, int &nrOfEdges, vector<UndirectedNode> nodes)
{
	UndirectedNode *m;
	nodes.clear();
	nrOfNodes=rand()%100;
	nrOfEdges=rand()%200;
	cout<<nrOfNodes<<" "<<nrOfEdges<<endl;
	for(int i=0; i<nrOfNodes; i++)
	{
		m=new UndirectedNode();
		m->name=i;
		nodes.push_back(*m);
	}
	int to, from=rand()%nrOfNodes;
	for(int i=0; i<nrOfEdges; i++)
	{
		to=rand()%nrOfNodes;
		cout<<from<<" "<<to<<endl;
		nodes[from].addEdgeOut(&nodes[to], 0);
		from=to;
	}
	cout<<"apa "<<nodes[0].name<<endl;
}*/

/*
 * Se page: 
 * http://kattis.csc.kth.se/problem?id=eulerianpath
 */
int main()
{
	//srand(time(NULL));
	int nrOfNodes, nrOfEdges, cost;
	int a, b, price;
	vector<pair<int, int> > edges;
	list<int> ans;
	while(true)
	{
		//cin>>nrOfNodes>>nrOfEdges;
		scanf("%d %d", &nrOfNodes, &nrOfEdges);
		if(nrOfNodes==0 && nrOfEdges==0)
		{
			break;
		}
		ans.clear();
		edges.clear();
			
		for(int i=0; i<nrOfEdges; i++)
		{
			//cin>>a>>b;
			scanf("%d %d", &a, &b);
			edges.push_back(make_pair(a,b));
		}
		//createTestCase(nrOfNodes, nrOfEdges, nodes);
		if(!eulerpath(ans, edges, nrOfNodes))
		{
			printf("Impossible\n");
		}
		else
		{
			//cout<<ans.size()<<endl;
			for(list<int>::iterator it=ans.begin(); it!=ans.end(); it++)
			{
				printf("%d ",*it);
			}
			printf("\n");
		}
	}
	return 0;
	
} 
