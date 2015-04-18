#include "Floyd.h"
#include <limits>

Floyd::Floyd(int N, std::vector<std::vector<double>> wt)
{
    const int INF = std::numeric_limits<int>::max();
    const int NEG_INF = std::numeric_limits<int>::min();
    path = new double*[N];
    this->N = N;
    for (int i = 0; i < N; i++)
        path[i] = new double[N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            path[i][j] = wt[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        path[i][i] = std::min(0.0, wt[i][i]);
    }
    double tmp;
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                tmp = path[i][k] + path[k][j];
                if (path[i][k] == INF || path[k][j] == INF) {
                    tmp = INF;
                }
                path[i][j] = std::min(path[i][j], tmp);
            }
        }
    }

    //Detect negative cycles
    for (int i = 0; i < N; i++) {
        if (path[i][i] < 0) {
            for (int j = 0; j < N; j++) {
                if (path[i][j] < INF) {
                    path[i][j] = NEG_INF;
                    path[j][j] = NEG_INF;
                    for (int h = 0; h < N; h++) {
                        if (path[h][j] < INF)
                            path[h][j] = NEG_INF;
                    }
                }
            }
        }
    }
}

Floyd::~Floyd()
{
    for (int i = 0; i < N; i++)
        delete[] path[i];
    delete[] path;
}

double Floyd::distance(int s, int d)
{
    return path[s][d];
}

void Floyd::printAll()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (path[i][j] == std::numeric_limits<int>::max())
                std::cout << "* ";
            else if (path[i][j] == std::numeric_limits<int>::min())
                std::cout << "x ";
            else
                std::cout << path[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

