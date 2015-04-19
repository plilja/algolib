#include "../../modulararithmetic.h"
#include <iostream>

using namespace std;

int main()
{
	long long n;
	int cases;
	
	while (scanf("%lld %d", &n, &cases) == 2 && (n != 0 || cases != 0)) {
		for (int i = 0; i < cases; ++i) {
			long long x, y;
			char op;
			
			scanf("%lld %c %lld", &x, &op, &y);
			
			Mod<long long> a(x, n);
			Mod<long long> b(y, n);
			Mod<long long> c(0, n);
			
			switch (op) {
				case '+':
					a += b;
					break;
				
				case '-':
					a -= b;
					break;
				
				case '*':
					a *= b;
					break;
				
				case '/':
					a /= b;
					break;
			}
			
			printf("%lld\n", a.get_value());
		}
	}
}
