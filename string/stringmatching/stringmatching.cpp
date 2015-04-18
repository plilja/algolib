/*
 * Author: Patrik Lilja
 * Date: 07-09-16
 * 
 * Se page:
 * http://kattis.csc.kth.se/problem.php?id=stringmatching
 * for a description of this file.
 * 
 * The solution uses the string matching functionality from
 * stringmultimatching.h.  
 */ 

#include <iostream>
#include <string>
#include <vector>
#define NDEBUG //Do we wan't assertions?
#include <cassert>
#include "stringmultimatching.h"

/*
 * Se page:
 * http://kattis.csc.kth.se/problem.php?id=stringmatching
 * for a description of the main functionality. 
 */
int main()
{	
	vector< vector<int> > ans;
	vector< vector<int> >::iterator oit;
	vector<int>::iterator iit;
	vector<string> patterns;
	string s, text;
	while(!cin.eof())
	{
		patterns.clear();
		getline(cin, s);		
		if(cin.eof())
		{
			break;
		}
		patterns.push_back(s);
		getline(cin, text);
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
