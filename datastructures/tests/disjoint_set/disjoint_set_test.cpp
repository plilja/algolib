#include "../../disjoint_set.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int main()
{
    int n, operations;
    cin >> n >> operations;
    DisjointSet disjoint_set(n);
    for (int i = 0; i < operations; ++i) {
        string op;
        cin >> op;
        if (op == "same") {
            int a, b;
            cin >> a >> b;
            cout << disjoint_set.same(a, b) << endl;
        } else if (op == "count") {
            cout << disjoint_set.count() << endl;
        } else if (op == "merge") {
            int a, b;
            cin >> a >> b;
            disjoint_set.merge(a, b);
        } else {
            assert(!"Unknown operation");
        }
    }
}
