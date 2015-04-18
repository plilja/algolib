#ifndef EULERIANPATH_H_
#define EULERIANPATH_H_

#include <vector>
#include <list>

struct node
{
	std::list<int> edges; 
};


bool eulerpath(std::list<int> &ans, std::vector<std::pair<int, int> > &edges, int nrOfNodes);

#endif /*EULERIANPATH_H_*/
