/*
 * Author: Patrik Lilja
 * Date: 07-10-09
 * 
 * Provides the ability to find the maximum flow in a flow network, while at
 * the same time minimizing a cost function on the edges. 
 * 
 * Please read about the input restrictions below before usage. 
 */ 
#ifndef MINCOSTMAXFLOW_H_
#define MINCOSTMAXFLOW_H_

#include <vector>
#include <list>

struct edge
{
	int from;
	int to;
	int f;
	int c;
	int cf;
	int cost;
	edge *reverse;
	int a_pi; //the patched cost value that makes sure that Dijkstra get positive weights
};

struct node
{
	std::vector<edge*> edges;
};


/*
 * Solve the minimum cost flow problem. Se wikipedia:
 * http://en.wikipedia.org/wiki/Minimum_cost_flow_problem
 * for a problem description. 
 * 
 * Be advised that some restrictions lie on the flow network: 
 * - The total cost may not exceed 1000000 (this equals infinity here)
 * - The cost on the edges must be greater or equal to 1
 * If these requirements aren't met the result is not guaranteed to be correct.
 * 
 * Running time: O(c*n*m*log n), where n=|V|=nr of nodes,
 * 								m=|e|=nr of edges,
 * 								c=the maximum edge cost
 * 
 * Parameters:
 * cost=The cost of the answer is put here.
 * Output: The edges in the solution is put in the first pair and the corresponding flow and cost is put in
 * 			the second pair. 
 * nrOfNodes: the number of nodes.
 * source: The index of the source node. Note that nodes are numbered from 0..nrOfNodes-1
 * sink: The index of the sink node. 
 * edges: The edges in the flow network along with their capacity and cost. The first pair tells which nodes
 * 			the edge goes between and the second pair tells that the edge has capacity pair.first and cost pair.second.
 * 
 * Returns: The maximum flow between the source node and the sink node. 
 * 
 */
int minCostMaxFlow(int &cost, std::list<std::pair<std::pair<int, int>, std::pair<int,int> > > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, std::pair<int,int> > > edges);


#endif /*MINCOSTMAXFLOW_H_*/
