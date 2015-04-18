#ifndef FORDFULKERSON_H_
#define FORDFULKERSON_H_

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
};

struct node
{
	std::vector<edge*> edges;
};

void bellmanford(std::list<edge*> &ans, node *N, int nrOfNodes, int source, int sink);
int minCapacityPath(const std::list<edge*> &path);
void fordFulkerson(node *N, int nrOfNodes, int source, int sink);
int flowOutOfNode(node *N, int n);
int fordFulkerson(int &cost, std::list<std::pair<std::pair<int, int>, std::pair<int,int> > > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, std::pair<int,int> > > edges);


#endif /*FORDFULKERSON_H_*/
