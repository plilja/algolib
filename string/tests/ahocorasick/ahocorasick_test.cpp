#include "../../ahocorasick.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int nr_of_patterns;
    while (cin >> nr_of_patterns) {
        while ('\n' != cin.get()) { }
        vector <string> patterns;
        for (int i = 0; i < nr_of_patterns; i++) {
            string s;
            getline(cin, s);
            patterns.push_back(s);
        }
        string text;
        getline(cin, text);
        auto ans = ahocorasick(text, patterns);
        for (auto vec : ans) {
            for (int idx : vec) {
                cout << idx << " ";
            }
            cout << endl;
        }
    }
}
