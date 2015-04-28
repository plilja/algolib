#include "../../crt.h"
#include <cstdio>

int main()
{
	int cases;
	
	scanf("%d", &cases);
	
	for (int i = 0; i < cases; ++i) {
		int a, b, n1, n2;
		
		scanf("%d %d %d %d", &a, &n1, &b, &n2);
		
		auto ans = crt<long long>(std::make_pair(a, n1), std::make_pair(b, n2));
		
		printf("%llu %llu\n", ans.first, ans.second);
	}
}
