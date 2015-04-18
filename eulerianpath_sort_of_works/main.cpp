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
//#include "minspantree.cpp"
#include <string>
#include <list>
#include <queue>

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
	vector<UndirectedNode*> nodes;
	UndirectedNode *m;
	list<UndirectedNode*> ans;
	while(true)
	{
		//cin>>nrOfNodes>>nrOfEdges;
		scanf("%d %d", &nrOfNodes, &nrOfEdges);
		if(nrOfNodes==0 && nrOfEdges==0)
		{
			break;
		}
		ans.clear();
		nodes.clear();
		for(int i=0; i<nrOfNodes; i++)
		{
			m=new UndirectedNode();
			m->name=i;
			nodes.push_back(m);
		}
			
		for(int i=0; i<nrOfEdges; i++)
		{
			//cin>>a>>b;
			scanf("%d %d", &a, &b);
			nodes[a]->addEdgeOut(nodes[b], 0);
		}
		//createTestCase(nrOfNodes, nrOfEdges, nodes);
		if(!eulerpath(ans, nodes))
		{
			printf("Impossible\n");
		}
		else
		{
			//cout<<ans.size()<<endl;
			assert(ans.size()==nrOfEdges+1);
			for(list<UndirectedNode*>::iterator it=ans.begin(); it!=ans.end(); it++)
			{
				printf("%d ",(*it)->name);
			}
			printf("\n");
		}
	}
	return 0;
	
} 
