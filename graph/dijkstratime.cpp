#include "dijkstratime.h"
#include <vector>
#include <limits>
#include <queue>

using std::vector;

const int INF = std::numeric_limits<int>::max();

DijkstraTime::DijkstraTime(int _nrOfNodes, int _source, const vector<vector<Edge>> &_edges) :
    nrOfNodes(_nrOfNodes),
    source(_source),
    parent(vector<int>(nrOfNodes, -1)),
    dist(vector<int>(nrOfNodes, INF)),
    adj_list(_edges)
{
    construct();
}

int DijkstraTime::distance(int goal)
{
    if (dist[goal] < std::numeric_limits<int>::max()) {
        return dist[goal];
    }
    return -1;
}

std::vector<int> DijkstraTime::getPath(int goal)
{
    std::vector<int> ans;
    if (dist[goal] >= std::numeric_limits<int>::max()) {
        return ans;
    }
    int n = goal;
    while (n != source) {
        if (n == -1) {
            //ERROR
            ans.clear();
            return ans;
        }
        ans.push_back(n);
        n = parent[n];
    }
    ans.push_back(source);
    std::reverse(ans.begin(), ans.end());
    return ans;
}

int getArrivalTime(int currentTime, int firstDeparture, int waitingTime, int travelTime)
{
    int arrival = std::max(currentTime, firstDeparture);
    arrival += travelTime;
    if (waitingTime != 0) {
        if (currentTime > firstDeparture) {
            int corr = (currentTime - firstDeparture) % waitingTime;
            if (corr != 0) { //need to wait
                arrival += waitingTime - (currentTime - firstDeparture) % waitingTime; //waiting time for next departure
            }
        }
    } else {
        if (currentTime > firstDeparture) {
            arrival = std::numeric_limits<int>::max();
        }
    }
    return arrival;
}

void DijkstraTime::construct()
{
    typedef std::pair<int, std::pair<int, int>> QueueItem;

    std::priority_queue <QueueItem, vector<QueueItem>, std::greater<QueueItem>> pq;

    vector<bool> visited(nrOfNodes, false);
    dist[source] = 0;

    pq.push({0, { -1, source}});

    std::pair<int, int> p;
    while (!pq.empty()) {
        auto qi = pq.top();
        pq.pop();

        int timeParent = qi.first;
        int from = qi.second.first;
        int to = qi.second.second;

        if (visited[to]) {
            continue;
        }
        dist[to] = timeParent;
        parent[to] = from;
        visited[to] = true;
        for (auto edge : adj_list[to]) {
            if (!visited[edge.to]) {
                int possibleArrival = getArrivalTime(timeParent, edge.firstDeparture, edge.waitingTime, edge.travelTime);
                if (possibleArrival < INF) {
                    pq.push({possibleArrival, {to, edge.to}});
                }
            }
        }
    }
}




