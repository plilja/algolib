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

/*
 * Find a path between two nodes in a flow graph. Uses a breath first search.  
 * 
 * Parameters:
 * ans: The answer will be stored here as a list of edgepointers
 * N: The nodes in a flow graph. 
 * nrOfNodes: The number of nodes. 
 * int source: index of the start node
 * int sink: index of the goal node
 */
void findPath(std::list<edge*> &ans, node* N, int nrOfNodes, int source, int sink)
{
	ans.clear();
	std::queue<int> q;
    edge **predecessor=new edge*[nrOfNodes];

    bool *d=new bool[nrOfNodes];
    for(int i=0; i<nrOfNodes; i++)
    {
    	d[i]=false;
    }
    
    q.push(source);
    predecessor[source]=0;
    
    d[source]=true; 
    edge *e;
    int u;
    while(d[sink]==false && q.size()!=0)
    {
		u=q.front();
		q.pop();
		for(std::vector<edge*>::iterator it=N[u].edges.begin(); it!=N[u].edges.end(); it++)
		{
			e=*it;
			if(d[e->to]==false && e->cf>0)
			{
				d[e->to]=true;
			    q.push(e->to);
			    predecessor[e->to]=e;
			}
		}
    }
    
    bool doLoop=true;
    if(q.size()==0)
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
    delete[] d;
    delete[] predecessor;
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
		findPath(path, N, nrOfNodes, source, sink);
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

int fordFulkerson(std::list<std::pair<std::pair<int, int>, int> > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, int> > edges)
{
	output.clear();
	edge *e, *eRev;
	node *N=new node[nrOfNodes];
	//Initialize nodes and edges
	for(std::list<std::pair<std::pair<int, int>, int> >::iterator it=edges.begin(); it!=edges.end(); it++)
	{
		e=new edge;
		eRev=new edge;
		e->from=it->first.first;
		e->to=it->first.second;
		e->c=it->second;
		eRev->from=it->first.second;
		eRev->to=it->first.first;
		eRev->c=0;//it->second;		
		e->reverse=eRev;
		eRev->reverse=e;
		N[e->from].edges.push_back(e);
		N[e->to].edges.push_back(eRev);
	}
	fordFulkerson(N, nrOfNodes, source, sink);

	//Build the solution
	for(int i = 0; i<nrOfNodes;i++)
	{
		for(std::vector<edge*>::iterator it=N[i].edges.begin(); it!=N[i].edges.end(); it++)
		{
			e = *it;
			if(e->f > 0)
			{
				output.push_back(std::make_pair(std::make_pair(e->from, e->to), e->f));
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

int minCutEdges(std::list<std::pair<int, int> > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, int> > edges)
{
	output.clear();
	edge *e, *eRev;
	node *N=new node[nrOfNodes];
	//Initialize nodes and edges
	for(std::list<std::pair<std::pair<int, int>, int> >::iterator it=edges.begin(); it!=edges.end(); it++)
	{
		e=new edge;
		eRev=new edge;
		e->from=it->first.first;
		e->to=it->first.second;
		e->c=it->second;
		eRev->from=it->first.second;
		eRev->to=it->first.first;
		eRev->c=0;		
		e->reverse=eRev;
		eRev->reverse=e;
		N[e->from].edges.push_back(e);
		N[eRev->from].edges.push_back(eRev);
	}
	fordFulkerson(N, nrOfNodes, source, sink);
	
	std::queue<int> q;
    bool *d=new bool[nrOfNodes];
    for(int i=0; i<nrOfNodes; i++)
    {
    	d[i]=false;
    }    
    q.push(source);
    d[source]=true; 
    int u;
    while(d[sink]==false && q.size()!=0)
    {
		u=q.front();
		q.pop();
		for(std::vector<edge*>::iterator it=N[u].edges.begin(); it!=N[u].edges.end(); it++)
		{
			e=*it;
			if(d[e->to]==false && e->cf>0)
			{
				d[e->to]=true;
			    q.push(e->to);
			}
		}
    }

	//Build the solution
	for(int i = 0; i<nrOfNodes;i++)
	{
		for(std::vector<edge*>::iterator it=N[i].edges.begin(); it!=N[i].edges.end(); it++)
		{
			e = *it;
			if(d[e->from] && !d[e->to])
			{
				output.push_back(std::make_pair(e->from, e->to));
			}
		}
	}
	int ans=flowOutOfNode(N, source); //mincut=maxflow
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

int minCutNodes(std::set<int> &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, int> > edges)
{
	output.clear();
	edge *e, *eRev;
	node *N=new node[nrOfNodes];
	//Initialize nodes and edges
	for(std::list<std::pair<std::pair<int, int>, int> >::iterator it=edges.begin(); it!=edges.end(); it++)
	{
		e=new edge;
		eRev=new edge;
		e->from=it->first.first;
		e->to=it->first.second;
		e->c=it->second;
		eRev->from=it->first.second;
		eRev->to=it->first.first;
		eRev->c=0;		
		e->reverse=eRev;
		eRev->reverse=e;
		N[e->from].edges.push_back(e);
		N[eRev->from].edges.push_back(eRev);
	}
	fordFulkerson(N, nrOfNodes, source, sink);
	
	std::queue<int> q;
    bool *d=new bool[nrOfNodes];
    for(int i=0; i<nrOfNodes; i++)
    {
    	d[i]=false;
    }    
    q.push(source);
    d[source]=true; 
    int u;
    while(d[sink]==false && q.size()!=0)
    {
		u=q.front();
		q.pop();
		for(std::vector<edge*>::iterator it=N[u].edges.begin(); it!=N[u].edges.end(); it++)
		{
			e=*it;
			if(d[e->to]==false && e->cf>0)
			{
				d[e->to]=true;
			    q.push(e->to);
			}
		}
    }

	//Build the solution
	for(int i = 0; i<nrOfNodes;i++)
	{
		if(d[i])
		{
			output.insert(i);
		}
	}
	int ans=flowOutOfNode(N, source); //mincut=maxflow
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
