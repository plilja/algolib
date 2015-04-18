#include "indexmap.h"
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

indexmap::indexmap()
{
	
}

indexmap::~indexmap()
{
	ind.clear();
	objects.clear();
}

int indexmap::getIndex(string s)
{
	std::pair<unordered_map<string, int>::iterator,bool> p;
	std::pair<string, int> insert(s, ind.size());
	p=objects.insert(insert);
	if(p.second==true)
	{
		ind.push_back(s);
	}
	return p.first->second;
}

string indexmap::getObject(int index)
{
	return ind.at(index);
}

int indexmap::size()
{
	return ind.size();
	
}
