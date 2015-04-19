#include <memory>
#include <vector>
#include "combinatorics.h"
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

string vec_to_string(vector<int> pick)
{
	string res = "[";
	for (unsigned long i = 0; i< pick.size(); ++i) {
		res = res + to_string(pick[i]);
		if (i != pick.size() -1) {
			res = res + ", ";
		}
}
	res += "]";
	return res;
}

int main() {
	int len, num_to_pick;
	scanf("%d %d", &len, &num_to_pick);
	vector<int> symbols;
	for (int i = 0; i < len; ++i)
	{
		int num;
		scanf("%d", &num);
		symbols.push_back(num);
	}
	unique_ptr<set<vector<int>>> result = ways_to_pick(symbols, num_to_pick);
	vector<string> result_as_strings;
	for (auto pick : *result) {
		result_as_strings.push_back(vec_to_string(pick));
	}
	sort(result_as_strings.begin(), result_as_strings.end());
	for (auto &s: result_as_strings) {
		cout<<s<<endl;
	}
}
