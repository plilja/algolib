/*
 * Author: Patrik Lilja
 * Group: Patrik Lilja, Martin Tittenberger
 */
#include "crt.h"
#include <list>
#include <cassert>
#include <utility>

using namespace std;

int main()
{
	//srand(time(NULL));
	int cases;
	scanf("%d", &cases);
	//cases=100000;
	for(int i=0; i<cases; ++i)
	{
		list<pair<long long int, long long int> > equation;
		
		int a1, a2, n1, n2;
		scanf("%d %d %d %d", &a1, &n1, &a2, &n2);
		/*n1=rand()%1000000000;
		n2=rand()%1000000000;
		a1=rand()%n1;
		a2=rand()%n2;*/
		pair<long long int, long long int> p=crtplus<long long int>(a1,n1,a2,n2);
		if(p.first==-1)
			printf("no solution\n");
		else
			printf("%lld %lld\n", p.first, p.second);
		/*if(p.first==-1)
			continue;
		if(p.first%n1!=a1)
			printf("%d %d %d %d\n", a1, n1, a2, n2);
		//assert(p.first % n1 ==a1);
		if(p.first%n2!=a2)
			printf("%d %d %d %d\n", a1, n1, a2, n2);*/
//		assert(p.first % n2 ==a2);
		
	}
 	return 0;
}
