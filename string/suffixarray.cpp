#include "suffixarray.h"
#include <math.h>
#include <algorithm>
#include <vector>
#include <cassert>

using std::vector;
using std::pair;
using std::string;

typedef long long int ll;

Suffixarray::Suffixarray(const string &s) : base(s), sorted(s.length()), size(s.length())
{
    assert(size < MAX_STRING_LENGTH);
    suffixSort();
}

int Suffixarray::getElementAt(int i)
{
    return sorted[i];
}

void Suffixarray::suffixSort()
{
    vector <pair<ll, int>> suff(size);
    vector <ll> rank(size);
    //Begin with sorting on the first character
    for (int i = 0; i < size; i++) {
        suff[i] = {(int) base.at(i), i};
        rank[i] = (int) base.at(i);
    }
    sort(suff.begin(), suff.end());
    ll H = 1;

    //Now use the result from previous sorting round in the next round
    while (H < size) {
        //First give every suffix a new rank based on it's current rank
        //and the rank of it's remaining letters.
        ll p = 0;
        ll old_rank = 0;
        for (int j = 0; j < size; j++) {
            ll p = suff[j].second;
            suff[j].first = rank[p] * MAX_STRING_LENGTH;
            if (p + H < size) {
                suff[j].first += rank[p + H];
            }
        }

        //Now sort the array in chunks. They were determined in the previous round.
        old_rank = rank[suff[0].second];
        ll start_pos = 0;
        for (int j = 1; j < size; j++) {
            if (old_rank < rank[suff[j].second]) {
                old_rank = rank[suff[j].second];
                sort(suff.begin() + start_pos, suff.begin() + j);
                start_pos = j;
            }
        }
        if (start_pos < size) {
            sort(suff.begin() + start_pos, suff.end());
        }

        //Reindex the rank from 0 to avoid overflow
        p = 0;
        old_rank = 0;
        for (int j = 0; j < size; j++) {
            if (old_rank < suff[j].first) {
                old_rank = suff[j].first;
                p++;
            }
            rank[suff[j].second] = p;
        }

        H = H * 2;
    }//end while(H<size)

    for (int j = 0; j < size; j++) {
        sorted[j] = suff[j].second;
    }
}
