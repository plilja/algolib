/*
 * Author: Patrik Lilja
 * Date: 07-10-15
 * 
 * Provides an algorithm for finding an eulerian path or an eulerian cycle in a graph.
 */ 
#ifndef EULERIANPATH_H_
#define EULERIANPATH_H_

#include <vector>
#include <list>

struct node
{
	std::list<int> edges; 
};

/*
 * Try to find an eulerpath in a graph. 
 * 
 * Parameters:
 * path: The nodes will be placed here
 * edges: The edges that make up the graph. Note that edges are directed, i.e. an edge (u,v)
 * 			doesn't indicate an edge (v,u)
 * nrOfNodes: the number of nodes in the graph.
 * 
 * Return:
 * a boolean telling if an eulerpath existed or not.  
 */
bool eulerpath(std::list<int> &ans, std::vector<std::pair<int, int> > &edges, int nrOfNodes);

#endif /*EULERIANPATH_H_*/
