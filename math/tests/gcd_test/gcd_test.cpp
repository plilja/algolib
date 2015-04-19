#include <iostream>
#include "../../gcd.h"

using namespace std;

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        int ans = gcd(a, b);
        cout << ans << endl;
    }

}
