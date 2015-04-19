#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <time.h>
#include <assert.h>
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
    int N = atoi(argv[1]);
    int n = atoi(argv[2]);
    srand(time(NULL));
    printf("%d\n", N);
    for (int j = 0; j < N; ++j) {
        int num = iRand(1, n);
        printf("%d\n", num);
    }
}
