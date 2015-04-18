/*
 * Author: Patrik Lilja
 * Date: 07-09-18
 * 
 * This Suffixarray class is used to create a sorted suffix array
 * from a string. The array will store the suffixes of the string 
 * sorted in lexicographic order. 
 */ 

#ifndef SUFFIXARRAY_H_
#define SUFFIXARRAY_H_
#include <string>
#include <vector>
using namespace std;

//The maximum string length accepted, 
#define MAX_STRING_LENGTH 100000

class Suffixarray
{
public:

	/*
	 * Construct a suffix array from string s. The
	 * construction runs in time O(n*(log n)^2).  
	 * 
	 * The suffix array will be immutable. 
	 */
	Suffixarray(string s);
	
	/*
	 * Destructor. 
	 */
	virtual ~Suffixarray();
	
	/*
	 * Returns the the index in the string of the
	 * i:th smallest suffix.
	 * 
	 * Runs in O(1)  
	 */
	int getElementAt(int i);
private:
	string base; //the string this suffixarray is created from
	int *sorted; //the sorted indexes
	int size; //size of Suffixarray

	/*
	 * Construct the suffixarray by arranging the suffixes in sorted order. 
	 * 
	 * After a call to this function the array named sorted will be updated. 
	 * 
	 * This runs in time O(n*(log n)^2)
	 */
	void suffixSort();
};

#endif /*SUFFIXARRAY_H_*/
