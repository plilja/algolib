#include <iostream>
#include <math.h>
#include "indexmap.h"
#define NDEBUG
#include <cassert>

using namespace std;

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
