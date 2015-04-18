/*
	Martin Tittenberger
	Patrik Lilja
*/

#include "chineseremainder.h"
#include <iostream>

int main()
{
	int cases;
	
	scanf("%d", &cases);
	
	for (int i = 0; i < cases; ++i) {
		int a, b, n1, n2;
		
		scanf("%d %d %d %d", &a, &n1, &b, &n2);
		
		Mod<long long> ans = crt<long long>(std::make_pair(a, n1), std::make_pair(b, n2));
		
		printf("%llu %llu\n", ans.getValue(), ans.getSize());
	}
}