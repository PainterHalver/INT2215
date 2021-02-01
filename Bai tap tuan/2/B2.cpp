#include <bits/stdc++.h>
using namespace std;


int main() {
    long long x;
    cin >> x;
    for(int i = 0; i < x; ++i) {
        for(int j = 0; j < x; ++j) {
            if (j < i) cout << " "; else cout << "*";
        }
        cout << "\n";
    }
}
