#include <iostream>
#include <string>
#include <vector>
#include "Suffixarray.h"

using namespace std;

int main()
{
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
