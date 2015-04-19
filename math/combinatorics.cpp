#include <vector>
#include <set>
#include "combinatorics.h"

struct cmp
{
    bool operator()(shared_ptr<vector<int>> a, shared_ptr<vector<int>> b)
    {
        return *a < *b;
    }
};

vector<vector<int>> all_ways_to_pick(const vector<int> &symbols, int num_to_pick, int begin_idx)
{
    if (num_to_pick == 0) {
        vector<vector<int>> *result = new vector<vector<int>>();
        result->push_back(vector<int>());
        return unique_ptr<vector<vector<int>>>(result);
    }
    if (num_to_pick > (int)symbols.size() - begin_idx) {
        return unique_ptr<vector<vector<int>>>(new vector<vector<int>>());
    }
    if ((int)symbols.size() == begin_idx + 1) {
		vector<vector<int>> *result = new vector<vector<int>>();
		vector<int> list;
		list.push_back(symbols[begin_idx]);
        result->push_back(list);
        return unique_ptr<vector<vector<int>>>(result);
    }
    int first = symbols[begin_idx];
    unique_ptr<vector<vector<int>>> solutions_excluding_first = all_ways_to_pick(symbols, num_to_pick, begin_idx + 1);
    unique_ptr<vector<vector<int>>> solutions_including_first = all_ways_to_pick(symbols, num_to_pick - 1, begin_idx + 1);
    for (vector<int>& solution : *solutions_including_first) {
        solution.push_back(first);
    }
	vector<vector<int>> *result = new vector<vector<int>>();
    result->insert(result->end(), solutions_excluding_first->begin(), solutions_excluding_first->end());
    result->insert(result->end(), solutions_including_first->begin(), solutions_including_first->end());
    return vector<vector<in>>>(result);
}

unique_ptr<set<vector<int>>> unique_picks(const vector<vector<int>> &picks)
{
	set<vector<int>>* result = new set<vector<int>>();
    for(auto &pick : picks) {
		result->insert(pick);
	}
	return unique_ptr<set<vector<int>>>(result);
}

unique_ptr<set<vector<int>>> ways_to_pick(const vector<int> &symbols, int num_to_pick)
{
    shared_ptr<vector<vector<int>>> all_picks = all_ways_to_pick(symbols, num_to_pick, 0);
	return unique_picks(*all_picks);
}




