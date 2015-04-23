#include "../../suffixarray.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    while (!cin.eof()) {
        string s;
        getline(cin, s);
        if (cin.eof()) {
            break;
        }
        Suffixarray suff(s);
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int tmp;
            cin >> tmp;
            cout << suff.get_element_at(tmp) << " ";
        }
        while ('\n' != cin.get()) {}
        cout << endl;
    }


}
