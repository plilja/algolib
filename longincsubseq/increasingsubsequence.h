#ifndef INCREASINGSUBSEQUENCE_H_
#define INCREASINGSUBSEQUENCE_H_
#include <math.h>
#include <memory>
#include <vector>

#define NEG_INF -2147483648
#define D_NEG_INF -2147483648.0
#define INF 2147483647

using namespace std;

/*
 * Solves the longest incresing subsequence problem.
 * 
 * Returns a list of indices in the longest increasing subsequence.
 * 
 * Runs in time O(n*log n)
 */
unique_ptr<vector<int>> longest_increasing_subsequence(int *seq, int len);


#endif /*INCREASINGSUBSEQUENCE_H_*/
