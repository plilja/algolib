#include <list>
#include <utility>
#include <algorithm>
#include <math.h>
#include <iostream>

using std::list;
using std::pair;
using std::cout;
using std::endl;

bool cmp_edges (const pair<pair<int, int>, int> &i, const pair<pair<int, int>, int> &j) 
{ 
	return (i.second<j.second); 
}

void greedy_matching(int num_nodes, std::list<pair<pair<int, int>, int> > &mst, std::list<pair<pair<int, int>, int> > &edges, std::list<pair<pair<int, int>, int> > &matching)
{
    edges.sort(cmp_edges);
    bool *odd=new bool[num_nodes];
	bool *covered=new bool[num_nodes];
	for(int i=0; i<num_nodes; ++i)
    {
        odd[i]=false;
		covered[i]=false;
    }

    for(std::list<pair<pair<int, int>, int> >::iterator it=mst.begin(); it!=mst.end(); ++it)
    {
		pair<pair<int, int>, int> &e=*it;
        odd[it->first.first] =!odd[it->first.first];
        odd[it->first.second] =!odd[it->first.second];
    }


    for(std::list<pair<pair<int, int>, int> >::iterator it=edges.begin(); it!=edges.end(); ++it)
	{
		pair<pair<int, int>, int> &e=*it;
		if(!covered[e.first.first] && !covered[e.first.second] && odd[e.first.first] && odd[e.first.second])
		{
			covered[e.first.first]=true;
			covered[e.first.second]=true;
			matching.push_back(e);
		}
	}
    delete []odd;
	delete []covered;
}
