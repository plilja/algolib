#include "fordfulkerson.h"
#include <vector>
#include <queue>
#include <limits>
#include <set>
#include <algorithm>
#include <set>

using std::vector;
using std::queue;
using std::set;

struct Edge {
    int from; //index of the from node
    int to; //index of the to node
    int c; //capacity
    int f; //flow
    Edge *reverse;
};

vector<Edge *> find_path(vector<vector<Edge *>> &flow_network, int nr_of_nodes, int source, int sink)
{
    vector<Edge *> predecessor(nr_of_nodes, NULL);
    vector<bool> visited(nr_of_nodes, false);

    queue<int> q;
    q.push(source);

    visited[source] = true;
    while (visited[sink] == false && q.size() != 0) {
        int u = q.front();
        q.pop();
        for (auto &e : flow_network[u]) {
            if (visited[e->to] == false && e->c > 0) {
                visited[e->to] = true;
                q.push(e->to);
                predecessor[e->to] = e;
            }
        }
    }

    vector<Edge *> path;
    if (visited[sink]) {
        int i = sink;
        while (predecessor[i] != NULL) {
            path.push_back(predecessor[i]);
            i = predecessor[i]->from;
        }
        reverse(path.begin(), path.end());
    }
    return path;
}

int capacity_of_path(const vector<Edge *> &path)
{
    int c = std::numeric_limits<int>::max();
    for (auto &e : path) {
        c = std::min(c, e->c);
    }
    return c;
}

vector<vector<Edge *>> initialize_flow_network(const vector<FlowEdge> &edges, int nr_of_nodes)
{
    vector<vector<Edge *>> flow_network(nr_of_nodes, vector<Edge *>());
    for (auto &flow_edge : edges) {
        Edge *e = new Edge;
        Edge *e_rev = new Edge;

        e->from = flow_edge.from;
        e->to = flow_edge.to;

        e_rev->from = e->to;
        e_rev->to = e->from;

        e->f = 0;
        e_rev->f = 0;

        e->c = flow_edge.capacity;
        e_rev->c = 0;

        e->reverse = e_rev;
        e_rev->reverse = e;

        flow_network[e->from].push_back(e);
        flow_network[e->to].push_back(e_rev);
    }
    return flow_network;
}

/**
 * Perform the actual Ford Fulkerson algorithm. Returns the resulting
 * flow network.
 */
vector<vector<Edge *>> ford_fulkerson(const vector<FlowEdge> &edges, int nr_of_nodes, int source, int sink)
{
    auto flow_network = initialize_flow_network(edges, nr_of_nodes);
    while (true) {
        vector<Edge *> path = find_path(flow_network, nr_of_nodes, source, sink);
        if (path.size() == 0) {
            break;
        }
        int c = capacity_of_path(path);
        for (auto &e : path) {
            e->f += c;
            e->reverse->f -= c;
            e->c -= c;
            e->reverse->c += c;
        }
    }
    return flow_network;
}

int flow_out_of_node(const vector<vector<Edge *>> &flow_network, int n)
{
    int flow = 0;
    for (auto e : flow_network[n]) {
        flow += e->f;
    }
    return flow;
}

FlowResult max_flow(const vector<FlowEdge> &edges, int nr_of_nodes, int source, int sink)
{
    auto flow_network = ford_fulkerson(edges, nr_of_nodes, source, sink);

    //Build the solution
    vector<FlowEdge> output;
    for (int i = 0; i < nr_of_nodes; i++) {
        for (auto e : flow_network[i]) {
            if (e->f > 0) {
                output.push_back(FlowEdge({e->from, e->to, e->f}));
            }
        }
    }
    int flow = flow_out_of_node(flow_network, source);
    return FlowResult({flow, output});
}

vector<bool> reachable_from_source(const vector<vector<Edge *>> &flow_network, int nr_of_nodes, int source)
{
    queue<int> q;
    vector<bool> d(nr_of_nodes, false);
    q.push(source);
    d[source] = true;
    int u;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (auto &e : flow_network[u]) {
            if (d[e->to] == false && e->c > 0) {
                d[e->to] = true;
                q.push(e->to);
            }
        }
    }
    return d;
}

MinCutEdgesResult min_cut_edges(const std::vector<FlowEdge> &edges, int nr_of_nodes, int source, int sink)
{
    auto flow_network = ford_fulkerson(edges, nr_of_nodes, source, sink);

    //Build the solution
    vector<bool> reachable = reachable_from_source(flow_network, nr_of_nodes, source);
    vector<FlowEdge> output;
    for (auto &e : edges) {
        if (reachable[e.from] && !reachable[e.to]) {
            output.push_back(e);
        }
    }
    int cost = flow_out_of_node(flow_network, source); //mincut=maxflow
    return MinCutEdgesResult({cost, output});
}

MinCutNodesResult min_cut_nodes(const std::vector<FlowEdge> &edges, int nr_of_nodes, int source, int sink)
{
    auto flow_network = ford_fulkerson(edges, nr_of_nodes, source, sink);

    //Build the solution
    vector<bool> reachable = reachable_from_source(flow_network, nr_of_nodes, source);
    set<int> output;
    for (int i = 0; i < nr_of_nodes; i++) {
        if (reachable[i]) {
            output.insert(i);
        }
    }
    int cost = flow_out_of_node(flow_network, source); //mincut=maxflow
    return MinCutNodesResult({cost, output});;
}
