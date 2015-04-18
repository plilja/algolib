#ifndef GREEDYMATCHING_H_
#define GREEDYMATCHING_H_


#include <list>
#include <utility>
#include <algorithm>
#include <math.h>
#include <iostream>

using std::list;
using std::pair;
using std::cout;
using std::endl;

void greedy_matching(int num_nodes, std::list<pair<pair<int, int>, int> > &mst, std::list<pair<pair<int, int>, int> > &edges, std::list<pair<pair<int, int>, int> > &matching);


#endif 
