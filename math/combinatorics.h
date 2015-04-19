#include <vector>
#include <set>

namespace {

    template<typename T>
    std::vector<std::vector<T>> all_ways_to_pick(const std::vector<T> &symbols, int num_to_pick, int begin_idx)
    {
        if (num_to_pick == 0) {
            std::vector<std::vector<T>> result;
            result.push_back(std::vector<T>());
            return result;
        }
        if (num_to_pick > (int)symbols.size() - begin_idx) {
            return std::vector<std::vector<T>>();
        }
        if ((int)symbols.size() == begin_idx + 1) {
            std::vector<std::vector<T>> result;
            std::vector<T> list;
            list.push_back(symbols[begin_idx]);
            result.push_back(list);
            return result;
        }
        int first = symbols[begin_idx];
        auto solutions_excluding_first = all_ways_to_pick(symbols, num_to_pick, begin_idx + 1);
        auto solutions_including_first = all_ways_to_pick(symbols, num_to_pick - 1, begin_idx + 1);
        for (auto& solution : solutions_including_first) {
            solution.push_back(first);
        }
        std::vector<std::vector<T>> result;
        result.insert(result.end(), solutions_excluding_first.begin(), solutions_excluding_first.end());
        result.insert(result.end(), solutions_including_first.begin(), solutions_including_first.end());
        return result;
    }

    template <typename T>
    std::set<std::vector<T>> unique_picks(const std::vector<std::vector<int>> &picks)
    {
        std::set<std::vector<T>> result;
        for(auto &pick : picks) {
            result.insert(pick);
        }
        return result;
    }
}

/**
 * Returns all possible ways to pick the speciefied number of objects
 * from the symbols provided.
 */
template <typename T>
std::set<std::vector<T>> ways_to_pick(const std::vector<T> &symbols, int num_to_pick)
{
    auto all_picks = all_ways_to_pick(symbols, num_to_pick, 0);
	return unique_picks<T>(all_picks);
}



