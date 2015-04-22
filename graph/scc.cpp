#include "scc.h"
#include <vector>
#include <set>
#include <deque>

using std::vector;
using std::deque;
using std::set;

void dfs(int starting_point, deque<int> &visited_order_stack, vector<bool> &visited, const vector <vector<int>> &graph)
{
    visited[starting_point] = true;
    for (auto &neighbour : graph[starting_point]) {
        if (!visited[neighbour]) {
            dfs(neighbour, visited_order_stack, visited, graph);
        }
    }
    visited_order_stack.push_front(starting_point);
}

void build_reverse_graph(const vector <vector<int>> &graph, vector <vector<int>> &reverse_graph)
{
    for (unsigned int i = 0; i < graph.size(); ++i) {
        auto v = graph[i];
        for (auto &neighbour : v) {
            reverse_graph[neighbour].push_back(i);
        }
    }
}

vector <set<int>> scc(const vector <vector<int>> &graph)
{

    deque<int> s;
    vector<bool> visited(graph.size(), false);
    for (unsigned int i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            dfs(i, s, visited, graph);
        }
    }

    vector <vector<int>> reverse_graph(graph.size(), vector<int>());
    build_reverse_graph(graph, reverse_graph);
    visited = vector<bool>(graph.size(), false);
    vector <set<int>> result;
    while (!s.empty()) {
        int next_to_visit = s.front();
        s.pop_front();
        if (visited[next_to_visit]) {
            continue;
        }

        deque<int> visited_from;
        dfs(next_to_visit, visited_from, visited, reverse_graph);

        set<int> component(visited_from.begin(), visited_from.end());
        result.push_back(component);
    }

    return result;
}




