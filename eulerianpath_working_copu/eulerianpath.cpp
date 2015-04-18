#include "eulerianpath.h"
#include <iostream>

using std::cout;
using std::endl;

/*
 * Check for existance of an eulerpath in a graph. 
 * 
 * return:
 * -1 if no eulerpath exists
 * 0 if an eulercycle exists
 * 1 if an euler path exists but not an eulercycle
 * 
 * if 1 is the return value the variables start and end will be
 * set to the appropriate values.
 * 
 * if 0 is the return value the variable start will be updated with a 
 * node that is suitable to start in.  
 */
int checkExistance(int &start, int &end, int nrOfNodes, node *nodes)
{
	int *inDegree=new int[nrOfNodes];
	int *outDegree=new int[nrOfNodes];
	for(int i=0; i<nrOfNodes; ++i)
		inDegree[i]=0;
	
	for(int i=0; i<nrOfNodes; ++i)
	{
		outDegree[i]=nodes[i].edges.size();
		for(std::list<int>::iterator it=nodes[i].edges.begin(); it!=nodes[i].edges.end(); ++it)
		{
			inDegree[*it]++;
		}
	}
	int nrOfOddDegree=0;
	start=-1;
	end=-1;
	for(int i=0; i<nrOfNodes; i++)
	{
		if(inDegree[i]==outDegree[i])
			continue;
		if(std::abs(inDegree[i]-outDegree[i])!=1)
			return -1;
		if(outDegree[i]>inDegree[i])
			start=i;
		else
			end=i;
		nrOfOddDegree++;
	}
	if(nrOfOddDegree==0)
	{
		start=0;
		for(int i=0; i<nrOfNodes; i++) //find a node that has at least one edge if such a node exists
		{
			if(nodes[i].edges.size()>0)
			{
				start=i;
				return 0;
			}
		}
		return 0;
	} 
	else if(nrOfOddDegree==2)
	{
		if(start==-1 || end==-1) 
			return -1; 
		else
			return 1;
	}
	else
	{
		return -1;
	}
}

bool eulerpath(std::list<int> &ans, std::vector<std::pair<int, int> > &edges, int nrOfNodes)
{
	node *nodes=new node[nrOfNodes];
	for(std::vector<std::pair<int, int> >::iterator it=edges.begin(); it!=edges.end(); it++)
	{
		nodes[it->first].edges.push_back(it->second);
	}
	int startNode, endNode;
	int exists=checkExistance(startNode, endNode, nrOfNodes, nodes);
	if(exists==-1)
		return false;
	if(exists==1)
	{
		//find an initial path between startNode and endNode
		int current=startNode;
		while(current!=endNode)
		{
			ans.push_back(current);
			current=nodes[current].edges.front();
			nodes[current].edges.pop_front(); //can't reuse edges
		}
		ans.push_back(endNode);
	}
	if(exists==0)
	{
		ans.push_back(startNode); 
	}
	cout<<"apa"<<endl;
	//while there still is at least one unused edge, augment our euler path
	bool edgesLeft=true;
	while(edgesLeft)
	{
		edgesLeft=false;
		for(std::list<int>::iterator it=ans.begin(); it!=ans.end(); it++)
		{
			if(nodes[*it].edges.size()==0)
				continue;
			edgesLeft=true;
			int current=*it, tmp;
			std::list<int> augmentingPath;
			do
			{
				augmentingPath.push_back(current);
				tmp=nodes[current].edges.front();
				nodes[current].edges.pop_front();
				current=tmp;
			} while(current!=*it);
			ans.insert(it, augmentingPath.begin(), augmentingPath.end());
		}
	}
	
	delete[] nodes;
	return true;
	
}
