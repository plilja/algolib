#include <vector>
#include <set>

/*
 * Finds the strongle connected components in a directed graph.
 *
 * Running time: O(num nodes + num edges)
 */
std::vector<std::set<int>> scc(const std::vector<std::vector<int>> &graph);
