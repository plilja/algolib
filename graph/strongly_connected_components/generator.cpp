#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <time.h>
#include <set>

using namespace std;

double dRand(double _min, double _max)
{
    double d = (double)rand() / RAND_MAX;
    return _min + d * (_max - _min);
}

double iRand(int _min, int _max)
{
    return _min + (rand() % (_max - _min + 1));
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int e = atoi(argv[2]);
    srand(time(NULL));
    cout<<n<<" "<<e<<endl;
    vector<set<int>> graph(n, set<int>());
    for (int j = 0; j < e; ++j) {
        int from = -1;
        int to = -1;
        while (from == -1 || to == -1 || graph[from].count(to) > 0 || from == to) {
            from = iRand(0, n- 1);
            to = iRand(0, n-1);
        }
        graph[from].insert(to);
    }

    for (int i = 0; i<n; ++i) {
        for (auto& to : graph[i]) {
            cout<<i<<" "<<to<<endl;
        }
    }
}

