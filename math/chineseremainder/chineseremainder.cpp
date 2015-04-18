#include "crt.h"
#include <list>
#include <utility>

using namespace std;

int main()
{
	int cases;
	scanf("%d", &cases);
	for(int i=0; i<cases; ++i)
	{
		list<pair<long long int, long long int> > equation;
		int a1, a2, n1, n2;
		scanf("%d %d %d %d", &a1, &n1, &a2, &n2);
		equation.push_back(make_pair(a1,n1));
		equation.push_back(make_pair(a2,n2));
		pair<long long int, long long int> p=crt<long long int>(equation);
		printf("%llu %llu\n", p.first, p.second);
		
	}
 	return 0;
}
