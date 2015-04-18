/*
 * Author: Patrik Lilja
 * Date: 07-10-09
 */ 
#include <vector>
#include <list>
#include <limits>
#include <cassert>
#include <set>
#include <iostream>
#include "mincostmaxflow.h"

const int INF= 1000000;

/*
 * Find the cheapest augmenting path using the Dijkstra algorithm. Also update the dist array with
 * the distance from the source node with respect to cost between nodes.
 * 
 * Precondition:
 * For every edge in the graph, edge->a_pi>=0
 * 
 * Output:
 * the path variable will be updated with the cheapest augmenting path. 
 */ 
void dijkstra_patched(std::list<edge*> &path, int *dist, node *N, int nrOfNodes, int source, int sink)
{
	bool *visited=new bool[nrOfNodes];
	edge **parent=new edge*[nrOfNodes];
	for(int i=0; i<nrOfNodes; i++)
	{
		dist[i]=INF;
		visited[i]=false;
	}
	std::set<std::pair<int, int> > pq;
	pq.insert(std::make_pair(0, source));
	dist[source]=0;
	std::pair<int, int> p;
	int costParent;
	int u, v, cost;
	while(pq.size()>0)
	{
		p=*(pq.begin());
		pq.erase(pq.begin(), ++pq.begin()); //remove first element
		if(visited[p.second])
		{
			continue;
		}
		costParent=p.first;
		visited[p.second]=true;
		for(std::vector<edge*>::iterator it=N[p.second].edges.begin(); it!=N[p.second].edges.end(); it++)
		{
			u=(*it)->from;
			v=(*it)->to;
			cost=(*it)->cost;
			if((*it)->cf<=0 || cost==INF)//no capacity?
				continue; 
			if(dist[v] > costParent+(*it)->a_pi && !(visited[v]))
			{
				pq.erase(std::make_pair(dist[v], v));
				parent[v]=*it;
				dist[v]=costParent + (*it)->a_pi;
				pq.insert(std::make_pair(dist[v], v));
			}
		}
	}
	path.clear();
	if(visited[sink])
	{
		int c=sink;
		while(c!=source)
		{
			path.push_front(parent[c]);
			c=parent[c]->from;
		}
	}
	delete[] parent;
	delete[] visited;
}

/*
 * Find the minimum capacity of all the edges in a list of edges.
 */
int minCapacityPath(const std::list<edge*> &path)
{
	int min=std::numeric_limits<int>::max(); 
	edge *e;
	for(std::list<edge*>::const_iterator it=path.begin(); it!=path.end(); it++)
	{
		e=*it;
		min=std::min(min, e->cf);
	}
	return min;	
}

/*
 * Perform the adapted version Ford-Fulkerson algorithm for the minimum cost maximum
 * flow problem. 
 * 
 * Running time: O(c*n*m*log n), where n=|V|=nr of nodes,
 * 								m=|e|=nr of edges,
 * 								c=the maximum edge cost
 * 
 * Parameters:
 * N: The nodes of a flowgraph, the output from the algorithm is given in N. 
 * nrOfNodes: the number of nodes
 * source: the index of the source node
 * sink: the index of the sink
 */
void fordFulkerson(node *N, int nrOfNodes, int source, int sink)
{
	int *pi=new int[nrOfNodes]; //potential function	
	for(int i=0; i<nrOfNodes; i++)
	{
		for(std::vector<edge*>::iterator it=N[i].edges.begin(); it!=N[i].edges.end(); it++)
		{
			(*it)->f=0;
			(*it)->cf=(*it)->c;
		}		
	}
	std::list<edge*> path;
	int min;
	edge *e;
	
	while(true)
	{
		dijkstra_patched(path, pi, N, nrOfNodes, source, sink); //pi=distance from source
		
		//Repatch our edge->a_pi values
		for(int j=0; j<nrOfNodes; j++)
		{
			for(std::vector<edge*>::iterator it=N[j].edges.begin(); it!=N[j].edges.end(); it++)
			{
				e=*it;
				e->a_pi=e->a_pi + pi[e->from] - pi[e->to];
			}
		}
		
		if(path.size()==0)
		{
			break;
		}
		min=minCapacityPath(path);
		for(std::list<edge*>::iterator it=path.begin(); it!=path.end(); it++)
		{
			e=*it;
			e->f += min;
			e->reverse->f = -e->f;
			e->cf = e->c - e->f;
			e->reverse->cf=e->reverse->c - e->reverse->f;
		}
	}
	delete[] pi;
}

/*
 * Compute the sum of the flow through the edges out of a node. 
 */
int flowOutOfNode(node *N, int n)
{
	int flow=0;
	for(std::vector<edge*>::iterator it=N[n].edges.begin(); it!=N[n].edges.end(); it++)
	{
		flow += (*it)->f;
	}
	return flow;
}

int minCostMaxFlow(int &cost, std::list<std::pair<std::pair<int, int>, std::pair<int,int> > > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, std::pair<int,int> > > edges)
{
	edge *e, *eRev;
	node *N=new node[nrOfNodes];
	//Initialize nodes and edges
	for(std::list<std::pair<std::pair<int, int>, std::pair<int,int> > >::iterator it=edges.begin(); it!=edges.end(); it++)
	{
		e=new edge;
		eRev=new edge;
		e->from=it->first.first;
		e->to=it->first.second;
		e->c=it->second.first;
		e->cost=it->second.second;
		e->a_pi=it->second.second;
		eRev->from=it->first.second;
		eRev->to=it->first.first;
		eRev->c=0;
		eRev->cost=-it->second.second;
		eRev->a_pi=-it->second.second;

		e->reverse=eRev;
		eRev->reverse=e;
		N[e->from].edges.push_back(e);
		N[e->to].edges.push_back(eRev);
	}
	fordFulkerson(N, nrOfNodes, source, sink);

	//Build the solution
	output.clear();
	cost=0;
	for(int i = 0; i<nrOfNodes;i++)
	{
		for(std::vector<edge*>::iterator it=N[i].edges.begin(); it!=N[i].edges.end(); it++)
		{
			e = *it;
			if(e->f > 0)
			{
				cost += e->f * e->cost;
				output.push_back(std::make_pair(std::make_pair(e->from, e->to), std::make_pair(e->f, e->f * e->cost)));
			}
		}
	}
	
	int ans=flowOutOfNode(N, source);
	for(int i = 0; i<nrOfNodes;i++)
	{
		for(std::vector<edge*>::iterator it=N[i].edges.begin(); it!=N[i].edges.end(); it++)
		{
			delete *it;
		}
	}
	delete[] N;
	return ans;
}

