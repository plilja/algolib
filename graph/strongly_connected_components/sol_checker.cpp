#include <cstdio>
#include <iostream>
#include <vector>
#include "scc.h"
#include <string>
#include <algorithm>

using namespace std;

bool path_between(int a, int b, vector<vector<int>> &g, set<int> &visited)
{
    visited.insert(a);
    if (a == b)
        return true;
    int ans = false;

    for (auto &neighbour : g[a]) {
        if (visited.count(neighbour) > 0)
            continue;
        ans = ans || path_between(neighbour, b, g, visited);
    }

    return ans;
}

void check_sol(vector<vector<int>> &graph, vector<set<int>> &components)
{
    for (auto &comp : components) {
        for (auto i1 : comp) {
            for (auto i2 : comp) {
                if (i1 == i2)
                    continue;
                set<int> visited;
                if (!path_between(i1, i2, graph, visited))
                    cerr << "Felaktig losning "<<i1<<" "<<i2 << endl;
            }
        }
    }
}

int main()
{
    int n, e;
    scanf("%d %d", &n, &e);
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < e; ++i) {
        int from, to;
        scanf("%d %d", &from, &to);
        graph[from].push_back(to);
    }

    unique_ptr<vector<set<int>>> components = scc(graph);
    check_sol(graph, *components);

    for (auto &c : *components) {
        for (auto &v : c) {
            printf("%d ", v);
        }
        printf("\n");
    }

}

