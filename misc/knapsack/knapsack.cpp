#include "knapsack.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

bool by_weight(const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b)
{
	return a.first.second < b.first.second;
}

unique_ptr<vector<int> > knapsack(int sack_capacity, vector<pair<int, int> > items)
{
	vector<vector<int>> maxv(items.size() + 1, vector<int>(sack_capacity + 1));
	for (int j = 0; j <= sack_capacity; ++j)
	{
		maxv[0][j] = 0;
		
	}
	for (uint i = 1; i <= items.size(); ++i)
	{
		auto item = items[i - 1];
		int value = item.first;
		int weight = item.second;

		for (int j = 0; j < weight && j <= sack_capacity; ++j)
		{
			maxv[i][j] = maxv[i - 1][j];
		}
		for (int j = weight; j <= sack_capacity; ++j)
		{
			maxv[i][j] = max(maxv[i - 1][j], maxv[i - 1][j - weight] + value);			
		}
	}

	unique_ptr<vector<int>> ans = unique_ptr<vector<int> >(new vector<int>());
	int i=items.size(), j=sack_capacity;
	//Backtrace through answer matrix to find items choosen
	while(i>0 && j>0)
	{
		auto item = items[i - 1];
		int weight = item.second;
		if(maxv[i-1][j] != maxv[i][j]) //is element i part of optimal solution?
		{
			ans->push_back(i - 1);
			j = j - weight;
		}
		i--;
	}	
	return ans;
}
