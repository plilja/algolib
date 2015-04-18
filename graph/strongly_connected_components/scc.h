#include <vector>
#include <set>
#include <memory>

/*
 * Finds the strongle connected components in a directed graph.
 *
 * Running time: O(num nodes + num edges)
 */
std::unique_ptr<std::vector<std::set<int>>> scc(const std::vector<std::vector<int>> &graph);
