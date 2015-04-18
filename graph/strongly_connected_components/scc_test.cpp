#include <cstdio>
#include <iostream>
#include <vector>
#include "scc.h"
#include <string>
#include <algorithm>

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

    unique_ptr<vector<set<int>>> components = scc(graph);

    for (auto & c : *components) {
        for (auto & v : c) {
            printf("%d ", v);
        }
        printf("\n");
    }

}


