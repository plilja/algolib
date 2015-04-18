/*
 * Author: Patrik Lilja
 * Date: 07-09-27
 * 
 * Finds an euler path in a graph. 
 */

#ifndef EULERIANPATH_H_
#define EULERIANPATH_H_
#include <vector>
#include "UndirectedNode.h"

/*
 * Try to find an eulerpath in a graph. 
 * 
 * Parameters:
 * path: The nodes will be placed here
 * nodes: The nodes that represents the graph
 * 
 * Return:
 * a boolean telling if an eulerpath existed or not. Note that the path variable
 * may contain nodes after a run even though no euler path was found. 
 */
bool eulerpath(std::list<UndirectedNode*> &path, std::vector<UndirectedNode*> &nodes);
//bool eulerpath(std::vector<std::pair<UndirectedNode, UndirectedNode> > &ans, std::vector<UndirectedNode> &nodes);


#endif /*EULERIANPATH_H_*/
