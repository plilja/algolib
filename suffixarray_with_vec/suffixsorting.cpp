/*
 * Author: Patrik Lilja
 * Date: 07-09-18
 */ 

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include "Suffixarray.h"

using namespace std;

int main()
{
	Suffixarray suf("popup");
	cout<<suf.getElementAt(1)<<endl;
	
	return 0;
	Suffixarray *suff;
	string s, text, sTmp;
	
	int n, tmp;

	while(!cin.eof())
	{
		getline(cin, s);
		if(cin.eof())
		{
			break;
		}
		suff=new Suffixarray(s);
		cin>>n;
		for(int i=0; i<n; i++)
		{
			cin>>tmp;
			cout<<suff->getElementAt(tmp)<<" ";
		}
		while('\n'!=cin.get()){}		
		cout<<endl;
		delete suff;
	}

	
}
