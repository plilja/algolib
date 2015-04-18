#ifndef STRINGMULTIMATCHING_H_
#define STRINGMULTIMATCHING_H_

#include "TrieNode.h"
#include <vector>

#include <string>

using namespace std;

typedef unsigned char uchar;


/*
 * An implementations of the Aho-Corasick pattern matching algorithm. 
 * 
 * The total number of characters in all of the patterns that are being 
 * searched may not exceed 100000. 
 * 
 * Time-complexity is O(text.length+sum(patterns.length)+#hits)
 * 
 * Parameters:
 * text: The text to search through
 * patterns: The patterns to search for.
 * 
 * Returns:
 * Vector of vectors where an inner vector v_i contains the indexes
 * where the i:th patterns has been found in the text. Indexes start
 * at 0 for the first position in the text.
 * 
 * Se article below for a description of the algorithm. 
 * Aho, Alfred V.; Margaret J. Corasick (June 1975). 
 * "Efficient string matching: An aid to bibliographic search"
 * 
 */
vector< vector<int> > ahocorasick(string text, vector<string> patterns);


#endif /*STRINGMULTIMATCHING_H_*/
