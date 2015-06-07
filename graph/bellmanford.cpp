#include "bellmanford.h"
#include <vector>
#include <limits>
#include <algorithm>

using std::vector;
using std::pair;

typedef pair<pair<int, int>, double> Edge;

const double INF = std::numeric_limits<double>::infinity();
const double NINF = -INF;

BellmanFord::BellmanFord(int _nr_of_nodes, vector <Edge> &_edges, int _source) :
        source(_source),
        nr_of_nodes(_nr_of_nodes),
        edges(_edges),
        dist(nr_of_nodes, INF),
        parent(nr_of_nodes, -1)
{
    construct();
}

double BellmanFord::distance(int goal)
{
    return dist[goal];
}

vector<int> BellmanFord::getPath(int goal)
{
    vector<int> path;
    if (dist[goal] == INF || dist[goal] == NINF) {
        //no path exists
        return path;
    }
    int current = goal;
    while (current != source) {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());
    return path;
}


inline int from(Edge &e)
{
    return e.first.first;
}

inline int to(Edge &e)
{
    return e.first.second;
}

inline double weight(Edge &e)
{
    return e.second;
}

void BellmanFord::construct()
{
    dist[source] = 0.0;

    for (int i = 0; i < nr_of_nodes - 1; i++) {
        for (int j = 0; j < (int) edges.size(); j++) {
            auto uv = edges[j];
            if (dist[from(uv)] == INF) {
                continue;
            }
            if (dist[to(uv)] > dist[from(uv)] + weight(uv)) {
                dist[to(uv)] = dist[from(uv)] + weight(uv);
                parent[to(uv)] = from(uv);
            }
        }
    }

    //Check for negative cycles
    for (int i = 0; i < nr_of_nodes - 1; i++) {
        for (int j = 0; j < (int) edges.size(); j++) {
            auto uv = edges[j];
            if (dist[from(uv)] == INF) {
                continue;
            }
            if (dist[from(uv)] == NINF) {
                dist[to(uv)] = NINF;
                continue;
            }
            if (dist[to(uv)] > dist[from(uv)] + weight(uv)) {
                dist[to(uv)] = NINF;
            }
        }
    }
}

