/*
 * Author: Patrik Lilja
 * Date: 07-09-27
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include "eulerianpath.h"
#include "UndirectedNode.h"
#include <cassert>
#include <limits>
#include <list>

using std::vector;
using std::pair;
using std::make_pair;
using std::list;

bool eulerpath(list<UndirectedNode*> &path, vector<UndirectedNode*> &nodes)
{
	path.clear();
	UndirectedNode *tmp;
	int nrOfEdges=0;
	int outDegree, inDegree;
	//list<UndirectedNode> path;
	int nrOfOdd=0;
	
	//Start by performing a count of the edges and check that an euler path is possible
	//Remember: 0 or possibly 2 nodes may have odd degree, nothing else works
	for(vector<UndirectedNode*>::iterator it=nodes.begin(); it!=nodes.end(); it++)
	{
		inDegree=(*it)->edgesIn.size();
		outDegree=(*it)->edgesOut.size();
		if(inDegree!=outDegree)
		{
			if(path.size()==0 && outDegree>inDegree)
			{
				path.push_back(*it);
			}
			nrOfOdd++;
		}
		if(nrOfOdd>2)
		{
			return false;
		}
		nrOfEdges += outDegree;
	}
	if(nrOfOdd==1)
	{
		return false;
	}
	if(nrOfOdd==0)
	{
		for(vector<UndirectedNode*>::iterator it=nodes.begin(); it!=nodes.end(); it++)
		{
			outDegree=(*it)->edgesOut.size();
			if(outDegree>0)
			{
				path.push_back(*it);
				break;
			}
		}
	}
	
	list<UndirectedNode*> tmpPath;
	UndirectedNode *front;
	UndirectedNode *current=path.front();
	UndirectedNode *next;
	int visitedCounter=0;
	size_t progress=std::numeric_limits<size_t>::max(); 


	//We start by creating an initial path, that is a walk for as long as we can
	while(current->edgesOut.size()>0)
	{
		tmp=current->edgesOut.front().first;
		current->edgesOut.pop_front();
		current=tmp;
		visitedCounter++;
		path.push_back(current);
	}

	//Now try to add segments to that path if possible
	while(visitedCounter<nrOfEdges)
	{
		if(progress==path.size()) //no progress, graph must be disconnected 
		{
			break;
		}
		progress=path.size();
		tmpPath.clear();
		for(list<UndirectedNode*>::iterator it=path.begin(); it!=path.end(); it++)
		{
			path.insert(it, tmpPath.begin(), tmpPath.end());
			tmpPath.clear();
			front=*it;
			current=front;
			while(true)
			{
				if(current->edgesOut.size()==0)
				{
					break;
				}
				tmp=current->edgesOut.front().first;
				current->edgesOut.pop_front();
				current=tmp;
				visitedCounter++;
				tmpPath.push_back(current);
				if(current==front)
				{
					break;
				}
			}

		}
		path.insert(path.end(), tmpPath.begin(), tmpPath.end());
	}	
	return visitedCounter==nrOfEdges;
	
}
