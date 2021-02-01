#include <bits/stdc++.h>
using namespace std;


int main() {
    string t;
    cin >> t;
    bool sym = true;
    for (int i = 0; i< t.size()/2; ++i) {
        if(t[i] != t[t.size()-1-i]) {
            sym = false;
            break;
        }
    }
    cout << sym;
}
