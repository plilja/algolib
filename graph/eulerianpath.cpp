#include "eulerianpath.h"
#include <queue>
#include <cassert>
#include <list>
#include <cmath>

using std::vector;
using std::queue;
using std::list;

/*
 * Check if we can reach overy other (non isolated) node in a graph from a given
 * start node.   
 */
bool checkConnectivity(vector<list<int> > adj_list, int nr_of_nodes, int startNode)
{
    vector<bool> visited(nr_of_nodes, false);
    visited[startNode] = true;
    queue<int> q;
    q.push(startNode);
    int n;
    while (!q.empty()) {
        n = q.front();
        q.pop();
        for (auto v : adj_list[n]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
            }
        }
    }
    for (int i = 0; i < nr_of_nodes; i++) {
        if (!visited[i] && adj_list[i].size() > 0) {
            return false;
        }
    }
    return true;
}

/*
 * Check for existance of an eulerpath in a graph. 
 * 
 * return:
 * -1 if no eulerpath exists
 * 0 if an eulercycle exists
 * 1 if an euler path exists but not an eulercycle
 * 
 * if 1 is the return value the variables start and end will be
 * set to the appropriate values.
 * 
 * if 0 is the return value the variable start will be updated with a 
 * node that is suitable to start in.  
 */
int checkExistance(int nr_of_nodes, vector <list<int>> adj_list, int &start, int &end)
{
    vector<int> in_degree(nr_of_nodes, 0);
    vector<int> out_degree(nr_of_nodes, 0);

    for (int i = 0; i < nr_of_nodes; ++i) {
        out_degree[i] = adj_list[i].size();
        for (int neighbour : adj_list[i]) {
            in_degree[neighbour]++;
        }
    }
    int nr_of_odd_degree = 0;
    start = -1;
    end = -1;
    for (int i = 0; i < nr_of_nodes; i++) {
        if (in_degree[i] == out_degree[i]) {
            continue;
        }
        if (std::fabs(in_degree[i] - out_degree[i]) != 1) {
            return -1;
        }
        if (out_degree[i] > in_degree[i]) {
            start = i;
        } else {
            end = i;
        }
        nr_of_odd_degree++;
    }

    if (nr_of_odd_degree != 0 && nr_of_odd_degree != 2) {
        return -1;
    }
    if (nr_of_odd_degree == 0) {
        for (int i = 0; i < nr_of_nodes; i++) //find a node that has at least one edge if such a node exists
        {
            if (adj_list[i].size() > 0) {
                start = i;
                if (checkConnectivity(adj_list, nr_of_nodes, i)) {
                    return 0;
                } else {
                    return -1;
                }
            }
        }
        return 0;
    }
    assert(nr_of_odd_degree == 2);

    if (start == -1 || end == -1) {
        return -1;
    } else {
        if (checkConnectivity(adj_list, nr_of_nodes, start)) {
            return 1;
        } else {
            return -1;
        }
    }
}

inline vector<int> toVec(list<int> &l) {
    return vector<int>(l.begin(), l.end());
}

EulerianPathResult eulerpath(const vector <std::pair<int, int>> &edges, int nr_of_nodes)
{
    list<int> path;
    vector <list<int>> adj_list(nr_of_nodes, list<int>());
    for (auto &edge : edges) {
        adj_list[edge.first].push_back(edge.second);
    }
    int start_node, end_node;
    int exists = checkExistance(nr_of_nodes, adj_list,  start_node, end_node);
    if (exists == -1) {
        return EulerianPathResult({false, vector<int>()});
    }
    if (exists == 1) {
        //find an initial path between startNode and endNode
        int current = start_node;
        while (current != end_node) {
            path.push_back(current);
            int tmp = adj_list[current].front();
            adj_list[current].pop_front(); //can't reuse edges
            current = tmp;
        }
        path.push_back(end_node);
    }
    if (exists == 0) {
        path.push_back(start_node);
    }
    //while there still is at least one unused edge, augment our euler path
    bool edges_left = true;
    while (edges_left) {
        edges_left = false;
        for (list<int>::iterator it = path.begin(); it != path.end(); it++) {
            if (adj_list[*it].empty()) {
                continue;
            }
            edges_left = true;
            int current = *it;
            std::list<int> augmenting_path;
            do {
                augmenting_path.push_back(current);
                int tmp = adj_list[current].front();
                adj_list[current].pop_front();
                current = tmp;
            } while (current != *it);

            path.insert(it, augmenting_path.begin(), augmenting_path.end());
        }
    }

    return EulerianPathResult({true, toVec(path)});
}
