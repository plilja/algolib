#include "crt.h"
#include <list>
#include <cassert>
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
		pair<long long int, long long int> p=crtplus<long long int>(a1,n1,a2,n2);
		if(p.first==-1)
			printf("no solution\n");
		else
			printf("%lld %lld\n", p.first, p.second);
	
	}
 	return 0;
}
