#include "knapsack.h"
#include "math.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<int> ans;
	vector<int>::iterator it;
	double capacityTmp;
	int capacity, num_items;
	while(2==scanf("%lf %d", &capacityTmp, &num_items))
	{
		vector<pair<int, int> > items(0);
		capacity=(int) floor(capacityTmp);
		for(int i=0; i<num_items; i++)
		{
			int value, weight;
			scanf("%d %d", &value, &weight);
			items.push_back({value, weight});
		}
		unique_ptr<vector<int> > ans = knapsack(capacity, items);
		printf("%lu\n", ans->size());
		for(it=ans->begin(); it!=ans->end(); it++)
		{
			printf("%d ", *it);
		}
		printf("\n");
	}
}
