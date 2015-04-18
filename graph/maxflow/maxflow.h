
#ifndef MAXFLOW_H
#define MAXFLOW_H

#include <list>
#include <queue>
#include <limits>
#include "FlowGraph.h"
#include "Edge.h"
#include "maxflow.h"
#include "Node.h"

void fordFulkerson(std::list<std::pair<std::pair<int, int>, int> > &output, int nrOfNodes, int source, int sink, std::list<std::pair<std::pair<int, int>, int> > edges);
void fordFulkerson(FlowGraph &G);
void solveFlowProblem();
void findPath(std::list<Edge*> &path, Node* s, Node* t, FlowGraph &G);
int minCf(std::list<Edge*> &path);

#endif 
