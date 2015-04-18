/*
 * Author: Patrik Lilja
 * Date: 07-09-26
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include "minspantree.h"
#include <limits>
#include <set>

/*
 * Adds an element a pair (a, b) to the vector ans while making sure that the smallest 
 * node is pushed first for exmple (0, 1) is pushed and not (1,0) 
 */
void append_to_solution(std::vector<std::pair<int, int> > &ans, int a, int b)
{
	if(a<b) 
	{
		ans.push_back(std::make_pair(a, b));
	}
	else
	{
		ans.push_back(std::make_pair(b, a));
	}
}

bool prim(std::vector<std::pair<int, int> > &ans, int &ansCost, int nrOfNodes, std::vector<std::pair<std::pair<int, int>, int> > &edges)
{
	ans.clear();
	ansCost=0;

	node *nodes=new node[nrOfNodes];
	int u, v, weight;	
	//initialize nodes variable from the edges variable
	for(std::vector<std::pair<std::pair<int, int>, int> >::iterator it=edges.begin(); it!=edges.end(); it++)
	{
		u=it->first.first;
		v=it->first.second;
		weight=it->second;
		nodes[u].edges.push_back(std::make_pair(v, weight));
		nodes[v].edges.push_back(std::make_pair(u, weight));
	}
	
	int *parent=new int[nrOfNodes];
	int *bestCost=new int[nrOfNodes];
	bool *visited=new bool[nrOfNodes];
	for(int i=0; i<nrOfNodes; i++)
	{
		visited[i]=false;
		parent[i]=-1;
		bestCost[i]=std::numeric_limits<int>::max();
	}
	std::set<std::pair<int, int> > pq; 	
	
	pq.insert(std::make_pair(0, 0)); //begin with node 0 
	bestCost[0]=0;
	int nodeCounter=0;
	std::pair<int, int> p;
	while(pq.size()!=0)
	{
		p=*pq.begin();
		pq.erase(p);
		if(visited[p.second])
		{
			//would create a cycle
			continue;
		}
		visited[p.second]=true;
		for(std::list<std::pair<int, int> >::iterator it=nodes[p.second].edges.begin(); it!=nodes[p.second].edges.end(); it++)
		{
			if((it->second < bestCost[it->first]) && !visited[it->first])
			{
				pq.erase(std::make_pair(bestCost[it->first], it->first));
				bestCost[it->first]=it->second;
				pq.insert(std::make_pair(bestCost[it->first], it->first));
				parent[it->first]=p.second;
			}
		}
		//Add the element we popped from our queue to the solution
		if(parent[p.second]!=-1)
		{
			append_to_solution(ans, p.second, parent[p.second]);
		}
		ansCost += p.first;
		nodeCounter++;
		if(nodeCounter==nrOfNodes)
		{
			//We're done
			break;
		}
	}
	delete[] nodes;
	delete[] parent;
	delete[] visited;
	delete[] bestCost;
	return nodeCounter==nrOfNodes;
}




