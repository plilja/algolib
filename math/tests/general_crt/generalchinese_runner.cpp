#include "../../crt.h"
#include "../../modulararithmetic.h"
#include <iostream>

using namespace std;

int main()
{
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; ++i) {
        long long a, b, n1, n2;

        cin >> a >> n1 >> b >> n2;

        auto ans = crtGeneral<long long>({a, n1}, {b, n2});

        if (ans.second == -1) {
            cout << "no solution" << endl;
        } else {
            cout << ans.first << " " << ans.second << endl;
        }
    }
}
