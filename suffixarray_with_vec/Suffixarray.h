/*
 * Author: Patrik Lilja
 * Date: 07-09-18
 */ 

#ifndef SUFFIXARRAY_H_
#define SUFFIXARRAY_H_
#include <string>
#include <math.h>
#include <vector>
using namespace std;

#define MAX_STRING_LENGTH 100000

class Suffixarray
{
public:
	Suffixarray(string s);
	virtual ~Suffixarray();
	int getElementAt(int i);
private:
	string base;
	int *sorted;
	void suffixSort();
	int size;
};

#endif /*SUFFIXARRAY_H_*/
