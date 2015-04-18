#pragma once

#include <string>
#include <vector>
using namespace std;

#define MAX_STRING_LENGTH 100000

class Suffixarray
{
public:
	Suffixarray(string s);
	virtual ~Suffixarray();
	int getElementAt(int i);
	void suffixSort2();
private:
	string str;
	int *pos;
	void suffixSort();
	int size;
};

