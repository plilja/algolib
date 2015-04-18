/*
 * Author: Patrik Lilja
 * Date: 07-09-11
 * 
 * Se page:
 * http://kattis.csc.kth.se/problem.php?id=indexmapping
 * 
 * for description of this file, for library functionality look at
 * indexmap.h 
 */
#include <iostream>
#include <math.h>
#include "indexmap.h"
#define NDEBUG
#include <cassert>

using namespace std;

/*
 * Se page:
 * http://kattis.csc.kth.se/problem.php?id=indexmapping
 * 
 * for description of the program's main method. 
 */
int main()
{
	string argument;
	char data[100000];
	int index;
	indexmap map;
	while(!cin.eof())
	{
		cin>>argument;
		if(cin.eof())
		{
			break;
		}
		cin.get();
		if(argument=="index")
		{
			cin.getline(data, 100000);			
			cout<<map.getIndex((string) data)<<endl;
		}
		else if(argument=="object")
		{
			scanf("%u\n", &index);
			cout<<map.getObject(index)<<endl;
		}
		else
		{
			break;
		}
	}

	return 0;
}
