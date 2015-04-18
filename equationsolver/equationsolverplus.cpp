/*
 * Author: Patrik Lilja
 * Group: Patrik Lilja, Martin Tittenberger
 */
#include "gaussjordan.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	int n;
	while(true)
	{
		scanf("%d", &n);
		if(n==0)
			break;
		vector<pair<bool, double> > x;
        vector<vector<double> > A(n, vector<double>(n));
        //fread(A, sizeof(double), n * n, stdin);
		vector<double> y(n);
        double tmp;
		for(int i=0; i<n; ++i)
		{
			for(int j=0; j<n; ++j)
			{
				scanf("%lf", &tmp);
				A[i][j]=tmp;
			}
		}
		for(int i=0; i<n; ++i)
		{
			scanf("%lf", &tmp);
			y[i]=tmp;
		}
		int ans=gaussjordanplus<double>(A, y, x);
		if(ans==INCONSISTENT)
		{
			printf("inconsistent\n");
		}
		else if(ans==MULTIPLE || ans==SUCCESS)
		{
			for(int i=0; i<n; ++i)
			{
				if(x[i].first)
					if(isZero(x[i].second))
						cout<<"0 ";
					else
						cout<<x[i].second<<" ";
				else
					cout<<"? ";
			}
			cout<<endl;
		}
		
	}
	return 0;
}
