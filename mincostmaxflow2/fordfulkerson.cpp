/*
 * Author: Patrik Lilja
 * Date: 07-10-05
 */ 
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <set>
#include <iostream>
#include "fordfulkerson.h"

using std::cout;
using std::endl;



void bellmanford(std::list<edge*> &ans, node *N, int nrOfNodes, int source, int sink)
{
	ans.clear();
    edge **predecessor=new edge*[nrOfNodes];
	int *dist=new int[nrOfNodes];
	for(int i=0; i<nrOfNodes; i++)
	{
		dist[i]=std::numeric_limits<int>::max();
	}
	dist[source]=0;
	predecessor[source]=0;

	edge *uv;
	for(int k=0; k<nrOfNodes-1; k++)
	{
		for(int i=0; i<nrOfNodes; i++)
		{
			for(std::vector<edge*>::iterator it=N[i].edges.begin(); it!=N[i].edges.end(); it++)
			{
				uv=*it;
				if(uv->cf<=0 || dist[uv->from]==std::numeric_limits<int>::max())
				{
					continue; //addition would cause integer overflow || no capacity left
				}
				if(dist[uv->to]>dist[uv->from]+uv->cost)
				{
					dist[uv->to]=dist[uv->from]+uv->cost;
					predecessor[uv->to]=uv;
				}
			}
		}
	}
	//Check for negative cycles
	/*for(int k=0; k<nrOfNodes; k++)
	{
		for(int i=0; i<nrOfNodes; i++)
		{
			for(std::vector<edge*>::iterator it=N[i].edges.begin(); it!=N[i].edges.end(); it++)
			{
				uv=*it;
				if(dist[uv->from]==std::numeric_limits<int>::max())
				{
					continue; //addition would cause integer overflow
				}
				if(dist[uv->from]==std::numeric_limits<int>::min())
				{
					dist[uv->to]=-100000;//std::numeric_limits<int>::min();
					continue;
				}
				if(dist[uv->to]>dist[uv->from]+uv->cost)
				{
					dist[uv->to]=-100000;//std::numeric_limits<int>::min();
				}
			}
		}
	}*/

    bool doLoop=true;
    if(dist[sink]==std::numeric_limits<int>::max() || dist[sink]==-100000)
    {
    	doLoop=false;
    }
    int i=sink;
    if(doLoop)
    { 
	    while(predecessor[i]!=0)
	    {
	    	ans.push_front(predecessor[i]);
			i=predecessor[i]->from;
	    }
    }
    delete[] dist;
    delete[] predecessor;	
}




/*
 * Find the minimum capacity of all the edges in a list of edges.
 */
int minCapacityPath(const std::list<edge*> &path)
{
	int maxCost=0;
	int min=std::numeric_limits<int>::max(); 
	edge *e;
	cout<<"begin stig"<<endl;
	for(std::list<edge*>::const_iterator it=path.begin(); it!=path.end(); it++)
	{
		e=*it;
		cout<<e->from<<" "<<e->to<<" "<<e->cost<<endl;
		maxCost=std::max(maxCost, e->cost);
		min=std::min(min, e->cf);
	}
	cout<<"slut stig, kostnad: "<<maxCost<<endl;
	return min;	
}

/*
 * Perform the actual Ford-Fulkerson algorithm. 
 * 
 * Runs in time O(|N|*|V|^2)
 * 
 * Parameters:
 * N: The nodes of a flowgraph, the output from the algorithm is given in N. 
 * nrOfNodes: the number of nodes
 * source: the index of the source node
 * sink: the index of the sink
 */
void fordFulkerson(node *N, int nrOfNodes, int source, int sink)
{
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
		bellmanford(path, N, nrOfNodes, source, sink);
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

int fordFulkerson(int &cost, std::list<std::pair<std::pair<int, int>, std::pair<int,int> > > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, std::pair<int,int> > > edges)
{
//	output.clear();
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
		eRev->from=it->first.second;
		eRev->to=it->first.first;
		eRev->c=0;//it->second;
		eRev->cost=-it->second.second;		

		e->reverse=eRev;
		eRev->reverse=e;
		N[e->from].edges.push_back(e);
		N[e->to].edges.push_back(eRev);
	}
	fordFulkerson(N, nrOfNodes, source, sink);

	//Build the solution
	cost=0;
	for(int i = 0; i<nrOfNodes;i++)
	{
		for(std::vector<edge*>::iterator it=N[i].edges.begin(); it!=N[i].edges.end(); it++)
		{
			e = *it;
			if(e->f > 0)
			{
				cost += e->f * e->cost;
				output.push_back(std::make_pair(std::make_pair(e->from, e->to), std::make_pair(e->f, e->cost)));
			}
		}
	}
	
	int ans=flowOutOfNode(N, source);
	delete[] N;
	return ans;
}

