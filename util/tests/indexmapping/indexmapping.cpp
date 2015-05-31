#include <iostream>
#include "../../indexmap.h"
#include <string>

using namespace std;

int main()
{
    Indexmap<string> map;
    while (!cin.eof()) {
        string argument;
        cin >> argument;
        if (cin.eof()) {
            break;
        }
        cin.get();
        if (argument == "index") {
            string data;
            getline(cin, data);
            cout << map.getIndex(data) << endl;
        } else if (argument == "object") {
            int index;
            scanf("%u\n", &index);
            cout << map.getObject(index) << endl;
        } else {
            break;
        }
    }

    return 0;
}
