#include "longincsubseq.h"
#include <cmath>

using std::vector;

/*
 * Do a binary search for the integer j. Such that lowerBound<=j<=upperBound
 * and that maximizes seq[M[j]] while keeping seq[M[j]]<x.
 */
int binSearch(vector<int> &M, const vector<int> &seq, int x, int lowerBound, int upperBound)
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

vector<int> recreateSolution(vector<int> &P, int ans_length, int final_idx)
{
    vector<int> result(ans_length);
    int tmp = final_idx;
    for (int i = ans_length - 1; i >= 0; --i) {
        result[i] = tmp;
        tmp = P[tmp];
    }
    return result;

}

vector<int> longincsubseq(const vector<int> &seq)
{
    int len = seq.size();
    vector<int> M(len + 1);
    vector<int> P(len);
    int ans_length = 0;
    M[0] = 0;
    for (int i = 0; i < len; ++i) {
        int lo = binSearch(M, seq, seq[i], 1, ans_length);
        P[i] = M[lo - 1];
        M[lo] = i;
        ans_length = std::max(ans_length, lo);
    }
    return recreateSolution(P, ans_length, M[ans_length]);
}
