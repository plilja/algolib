#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <time.h>

using namespace std;

double dRand(double _min, double _max)
{
	double d = (double)rand() / RAND_MAX;
	return _min + d * (_max - _min);
}

double iRand(int _min, int _max)
{
	return _min + (rand() % (_max - _min + 1));
}


int main()
{
	srand(time(NULL));
	for (int i = 0; i < 20; ++i)
	{
		vector<pair<int, int> > items(0);
		double capacity = dRand(1, 20);
		for (int j = 0; j < 2000; ++j)
		{
			int value = iRand(1, 10000);
			int weight = iRand(1, 10000);
			items.push_back({value, weight});
		}
		
		cout<<capacity<<" "<<items.size()<<endl;
		for (auto i = items.begin(); i != items.end(); ++i) {
			std::cout << i->first << " " << i->second << std::endl;
		}

	
	}
}
