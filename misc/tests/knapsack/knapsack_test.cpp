#include "../../knapsack.h"
#include <cmath>
#include <vector>
#include <cstdio>

using namespace std;

int main()
{
    double capacityTmp;
    int capacity, num_items;
    while (2 == scanf("%lf %d", &capacityTmp, &num_items)) {
        vector <pair<int, int>> items(0);
        capacity = (int) floor(capacityTmp);
        for (int i = 0; i < num_items; i++) {
            int value, weight;
            scanf("%d %d", &value, &weight);
            items.push_back({value, weight});
        }
        vector<int> ans = knapsack(items, capacity);
        printf("%lu\n", ans.size());
        for (auto item : ans) {
            printf("%d ", item);
        }
        printf("\n");
    }
}
