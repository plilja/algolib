#include "generalchineseremainder.h"
#include <iostream>
#include "modulararithmetic.h"

using namespace std;

int main()
{
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; ++i) {
        long long a, b, n1, n2;

        cin >> a >> n1 >> b >> n2;

        Mod<long long> ans = crt_general<long long>({a, n1}, {b, n2});

        if (ans.getValue() == 0) {
            cout << "no solution" << endl;
        } else {
            cout << ans.getValue() << " " << ans.getSize() << endl;
        }
    }
}
