#include <iostream>
#include "../../primesieve.h"

int main()
{
	int n, queries;
	scanf("%d %d", &n, &queries);
	
	PrimeSieve ps(n);
	printf("%u\n", ps.numPrimes());
	for (int i = 0; i < queries; ++i) {
		int query;
		scanf("%d", &query);
		printf("%d\n", ps.isPrime(query));
	}
}
