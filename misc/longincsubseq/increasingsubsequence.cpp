#include <math.h>
#include <iostream>
#include "increasingsubsequence.h"
#include <memory>

using namespace std;

/*
 * Do a binary search for the integer j. Such that lowerBound<=j<=upperBound
 * and that maximizes seq[M[j]] while keeping seq[M[j]]<x.
 */
int bin_search(int *M, int *seq, int x, int lowerBound, int upperBound)
{

    int lo = lowerBound;
    int hi = upperBound;
    while (lo <= hi) {

        int middle = ceil((lo + hi) / 2.0);

        if (seq[M[middle]] < x) {
            lo = middle + 1;
        } else {
            hi = middle - 1;
        }
    }
    return lo;
}

unique_ptr<vector<int>> recreate_solution(int *P, int ans_length, int final_idx)
{
    int tmp = final_idx;
    unique_ptr<vector<int>> result = unique_ptr<vector<int>>(new vector<int>(ans_length));

    for (int i = ans_length - 1; i >= 0; --i) {
        (*result)[i] = tmp;
        tmp = P[tmp];
    }

    return result;

}

unique_ptr<vector<int>> longest_increasing_subsequence(int *seq, int len)
{
    int M[len + 1];
    int P[len];
    int ans_length = 0;
    M[0] = 0;
    for (int i = 0; i < len; ++i) {
        int lo = bin_search(M, seq, seq[i], 1, ans_length);
        P[i] = M[lo - 1];
        M[lo] = i;
        ans_length = max(ans_length, lo);
    }
    return recreate_solution(P, ans_length, M[ans_length]);
}
