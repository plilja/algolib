#include "floydw.h"
#include <limits>

const int INF = std::numeric_limits<int>::max();
const int NEG_INF = std::numeric_limits<int>::min();

using std::vector;

Floydw::Floydw(std::vector<std::vector<double>> wt, int _n) : dist(wt), n(_n) {
    for (int i = 0; i < n; i++) {
        dist[i][i] = std::min(0.0, wt[i][i]);
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double tmp = dist[i][k] + dist[k][j];
                if (dist[i][k] == INF || dist[k][j] == INF) {
                    tmp = INF;
                }
                dist[i][j] = std::min(dist[i][j], tmp);
            }
        }
    }

    //Detect negative cycles
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] < INF) {
                    dist[i][j] = NEG_INF;
                    dist[j][j] = NEG_INF;
                    for (int h = 0; h < n; h++) {
                        if (dist[h][j] < INF)
                            dist[h][j] = NEG_INF;
                    }
                }
            }
        }
    }
}

double Floydw::distance(int s, int d) {
    return dist[s][d];
}


