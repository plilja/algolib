/*
 * Author: Patrik Lilja
 * Date: 07-09-18
 * 
 * Se page:
 * http://kattis.csc.kth.se/problem?id=suffixsorting
 * for description of this file. 
 */ 

#include <iostream>
#include <string>
#include <vector>
#include "Suffixarray.h"

using namespace std;

/*
 * Se page:
 * http://kattis.csc.kth.se/problem?id=suffixsorting
 * for description of main function. 
 */
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
