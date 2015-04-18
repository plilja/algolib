/*
 * Author: Patrik Lilja
 * Date: 07-09-26
 * 
 * An implementation of prims algorithm for finding the minimal spanning tree
 * i an undirected graph. The weights of the edges may be both negativa and positive. 
 * 
 * The algorithm runs in time O( (|E|+|V|)*log(|V|).
 */
#ifndef MINSPANTREE_H_
#define MINSPANTREE_H_

#include <vector>
#include <list>

struct node
{
	std::list<std::pair<int, double> > edges; //pair.first=where to, pair.second=edge cost
};

/*
 * An implementation of prims algorithm for finding the minimal spanning tree
 * i an undirected graph. The weights of the edges may be both negativa and positive. 
 * 
 * The algorithm runs in time O( |E|+|V|)*log(|V|).
 * 
 * Parameters:
 * ans : A vector in which the nodes of the answer will be placed as pairs
 * ansCost : A double in which the cost of the tree will be placed. 
 * nrOfNodes: The number of nodes in the graph
 * edges : A list of the edges in the graph allong with their weights. Note that nodes
 * 			are numbered from 0..nrOfNodes-1. Also note that edges are undirected.  
 * 
 * Return: A boolean telling weather a spanning tree exists or not.  
 */
bool prim(std::vector<std::pair<int, int> > &ans, double &ansCost, int nrOfNodes, std::vector<std::pair<std::pair<int, int>, double> > &edges);

#endif /*MINSPANTREE_H_*/
