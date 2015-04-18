/*
 * Author: Patrik Lilja
 * Date: 07-10-05
 */ 
#include <list>
#include <queue>
#include <limits>
#include "FlowGraph.h"
#include "Edge.h"
#include "maxflow.h"
#include "Node.h"

//void fordFulkerson(std::vector<std::pair<std::pair<int, int>, int> > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, int> > edges);


/*private FlowGraph createGraphImplementation(){
	FlowGraph fg = new FlowGraph(Mio.GetInt(),Mio.GetInt(),Mio.GetInt());
	
	int numEdges = Mio.GetInt();
	
	for(int i = 0; i < numEdges; i++){
		Edge edge = new Edge(Mio.GetInt(),Mio.GetInt(),Mio.GetInt());
		Edge rEdge = new Edge(edge.getNodeTo(),edge.getNodeFrom(),0);
		edge.setReverse(rEdge);
		rEdge.setReverse(edge);
		
		fg.addEdge(edge);
		fg.addEdge(rEdge);
	}
	
	return fg;
}*/

//MAYBE NEED TO CHECK FOR MULTIPLE EDGES!!
void fordFulkerson(std::list<std::pair<std::pair<int, int>, int> > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, int> > edges)
{
	FlowGraph solution(nrOfNodes, source, sink);
	Edge *e, *eRev;
	for(std::list<std::pair<std::pair<int, int>, int> >::iterator it=edges.begin(); it!=edges.end(); it++)
	{
		e=new Edge(it->first.first, it->first.second, it->second);
		eRev=new Edge(it->first.second, it->first.first, it->second);
		e->setReverse(eRev);
		eRev->setReverse(e);
		solution.addEdge(*e);
		solution.addEdge(*eRev);
	}
	fordFulkerson(solution);
	int size=solution.getNumberOfNodes();
	Node *current;
	Edge *edge;
	for(int i = 1; i<=size;i++)
	{
		current = solution.getNode(i);
		for(Node::iterator it=current->begin(); it!=current->end(); it++)
		{
			*edge = *it;
			if(edge->getFlow() > 0)
			{
				output.push_back(std::make_pair(std::make_pair(edge->getNodeFrom(), edge->getNodeTo()), edge->getFlow()));
			}
		}
	}
	
	Node *source_ = solution.getSource();
	Node *sink_ = solution.getSink();
	if(source_->size()<sink_->size())
	{
		output.push_front(std::make_pair(std::make_pair(source_->getNumber(), sink_->getNumber()), source_->flowFrom()));
	}
	else
	{
		output.push_front(std::make_pair(std::make_pair(source_->getNumber(), sink_->getNumber()), sink_->flowTo()));
	}
					
}


/**
 * Solve the maximum flow problem using Ford-Fulkerson. 
 * Solve the problem in graph G with source s and goal t. 
 * @param G The graph for which to solve flow problem
 * @param s The source. 
 * @param t
 * @return 
 */
void fordFulkerson(FlowGraph &G)
{
	std::list<Edge*> p;
	Edge *e, *eRev; 
	int r;
	Node* s = G.getSource(); 
	Node* t = G.getSink();
//		for(int i=0; i<V; i++){
//			it=G.getNode(i).iterator();
//			while(it.hasNext()){
//				e=(Edge) it.next();
//				e.setFlow(0);
//				e.setRestCapacity(e.getCapacity());
//			}
//		}

	findPath(p,s,t,G);
	while(p.size()>0)
	{
		r=minCf(p);
		for(std::list<Edge*>::iterator it=p.begin(); it!=p.end(); it++)
		{
			e=*it; 
			eRev=e->getReverse();
			e->addToFlow(r); 
			eRev->setFlow(-e->getFlow());
			e->setRestCapacity(e->getCapacity()-e->getFlow());
			eRev->setRestCapacity(eRev->getCapacity()-eRev->getFlow());
		}
		findPath(p,s,t,G);
	}
}

/**
 * Get minimum rest capacity in a path. 
 * @param path The path in which to find min rest capacity. 
 * @return int with minimum capacity. 
 */
int minCf(std::list<Edge*> &path)
{
	int min=std::numeric_limits<int>::max(); 
	Edge *e;
	for(std::list<Edge*>::iterator it=path.begin(); it!=path.end(); it++)
	{
		e=*it;
		min=std::min(min, e->getRestCapacity());
	}
	return min;
}


/**
 * Find the shortest path i a graph using breadh first
 * search. Returns null if there is no path in between. 
 * @param s The startpoint.
 * @param t The endpoint,
 * @param G The graph in which to find a path. 
 * @return A list containing the shortest path between s and t.
 * 			null if there isn't any path between the points.  
 */
void findPath(std::list<Edge*> &path, Node* s, Node* t, FlowGraph &G)
{
	std::queue<Node*> q;
    int V=G.getNumberOfNodes();
    Edge **predecessor=new Edge*[V];
    bool *d=new bool[V];
    for(int i=0; i<V; i++)
    {
    	d[i]=false;
    }
    
    Node* u;
    q.push(s);
    predecessor[s->getNumber()]=NULL;
    
    d[s->getNumber()]=true; 
    Edge *e;
    while(d[t->getNumber()]==false && q.size()!=0)
    {
		u=q.front();
		q.pop();
		for(Node::iterator it=u->begin(); it!=u->end(); it++)
		{
			*e=*it;
			if(d[e->getNodeTo()]==false && e->getRestCapacity()>0)
			{
				d[e->getNodeTo()]=true;
			    q.push(G.getNode(e->getNodeTo()));
			    predecessor[e->getNodeTo()]=e;
			}
		}
    }
    
    if(q.size()==0){
    	return;
    }
    int i=t->getNumber(); 
    while(predecessor[i]!=NULL)
    {
    	path.push_front(predecessor[i]);
		i=predecessor[i]->getNodeFrom();
    }

    return;
}
