#include "../../scc.h"
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int main()
{
    int n, e;
    scanf("%d %d", &n, &e);
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < e; ++i)
    {
        int from, to;
        scanf("%d %d", &from, &to);
        graph[from].push_back(to);
    }

    vector<set<int>> components = scc(graph);

    for (auto & c : components) {
        for (auto & v : c) {
            printf("%d ", v);
        }
        printf("\n");
    }

}


