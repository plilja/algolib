#include <string>
#include <iostream>
#include "calculator.h"
#include <math.h>

using namespace std;

int main()
{
	string expr;
	while(!cin.eof())
	{
		getline(cin, expr);
		if(cin.eof() || expr=="")
			break;
		double tmp=eval(expr);
		tmp=round(tmp*100)/100;
		printf("%.2lf\n", tmp);
	}
	return 0;
}
