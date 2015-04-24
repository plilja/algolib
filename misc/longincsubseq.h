#pragma once

#include <vector>

#define NEG_INF -2147483648
#define D_NEG_INF -2147483648.0
#define INF 2147483647

/*
 * Solves the longest incresing subsequence problem.
 * 
 * Returns a list of indices in the longest increasing subsequence.
 * 
 * Runs in time O(n*log n)
 */
std::vector<int> longincsubseq(std::vector<int> seq);


