#include <iostream>

#include "stringmultimatching.h"

using namespace std;

/*
 * Se page:
 * http://kattis.csc.kth.se/problem.php?id=stringmultimatching
 * for a description of the main functionality. 
 */
int main()
{	
	vector< vector<int> > ans;
	vector< vector<int> >::iterator oit;
	vector<int>::iterator iit;
	vector<string> patterns;
	int nrOfPatterns;
	char s[100020], text[200020]; 
	while(!cin.eof())
	{
		patterns.clear();
		cin>>nrOfPatterns;
		if(cin.eof())
		{
			break;
		}
		while('\n'!=cin.get()){}
		for(int i=0; i<nrOfPatterns; i++)
		{
			cin.getline(s, 100010);
			patterns.push_back((string) s);
		}
		cin.getline(text, 200010);
		ans=ahocorasick(text, patterns);
		int i=0;
		for(oit=ans.begin(); oit!=ans.end(); oit++)
		{
			for(iit=oit->begin(); iit!=oit->end(); iit++)
			{
				cout<<*iit<<" ";
			}
			cout<<endl;
			i++;
		}
		ans.clear();
	}
}
