#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <time.h>
#include <assert.h>

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
		vector<int> seq;
		int n = iRand(90000, 100000);
		for (int j = 0; j < n; ++j)
		{
			int num = iRand(-10, 10);
			seq.push_back(num);
		}
		
		cout<<n<<endl;
		for (auto i = seq.begin(); i != seq.end(); ++i) {
			std::cout << *i << " ";
		}
		cout<<endl;

	
	}
}
