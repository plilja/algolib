#include "Dijkstra.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
#include <functional>
#include <set>

using namespace std;

Dijkstra::Dijkstra(size_t nrOfNodes, vector<pair<pair<int, int>, double> > &_nodes, int source)
{
    this->nrOfNodes = nrOfNodes;
    parent = new int[nrOfNodes];
    initializeNodes(nrOfNodes, _nodes);
    this->source = source;
    for (size_t i = 0; i < nrOfNodes; i++) {
        parent[i] = -1;
    }
    construct();
}

double Dijkstra::distance(int goal)
{
    if (dist[goal] < numeric_limits<int>::max()) {
        return dist[goal];
    }
    return -1;
}

list<int> Dijkstra::getPath(int goal)
{
    list<int> ans;
    if (dist[goal] >= numeric_limits<int>::max()) {
        return ans;
    }
    int n = goal;
    while (n != source) {
        if (n == -1) {
            //ERROR
            ans.clear();
            return ans;
        }
        ans.push_front(n);
        n = parent[n];
    }
    ans.push_front(source);
    return ans;
}

Dijkstra::~Dijkstra()
{
    delete[] nodes;
    delete[] parent;
    delete[] dist;
}

void Dijkstra::construct()
{
    set<pair<double, int> > pq; //pair.first=min known cost to node nr pair.second
    bool *visited = new bool[nrOfNodes];
    for (int i = 0; i < nrOfNodes; i++)
        visited[i] = false;
    dist = new double[nrOfNodes];
    for (int i = 0; i < nrOfNodes; i++)
        dist[i] = numeric_limits<int>::max();

    dist[source] = 0;
    pq.insert(make_pair(0, source));

    pair<double, int> p;
    double costParent;
    while (pq.size() > 0) {
        p = *pq.begin();
        pq.erase(p);
        costParent = p.first;
        if (visited[p.second] || costParent == numeric_limits<int>::max()) {
            continue;
        }
        visited[p.second] = true;
        for (list<pair<int, double> >::iterator it = nodes[p.second].edges.begin(); it != nodes[p.second].edges.end(); it++) {
            if ((dist[it->first] > costParent + it->second) && !(visited[it->first])) {
                parent[it->first] = p.second;
                pq.erase(make_pair(dist[it->first], it->first));
                dist[it->first] = costParent + it->second;
                pq.insert(make_pair(dist[it->first], it->first));
            }
        }
    }
    delete[] visited;
}

void Dijkstra::initializeNodes(size_t nrOfNodes, vector<pair<pair<int, int>, double> > &from)
{
    pair<int, int> p1;
    nodes = new node[nrOfNodes];
    for (vector<pair<pair<int, int>, double> >::iterator it = from.begin(); it != from.end(); it++) {
        p1 = it->first;
        nodes[p1.first].edges.push_back(make_pair(p1.second, it->second));
    }
}

