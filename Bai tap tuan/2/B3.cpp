#include <bits/stdc++.h>
using namespace std;


int main() {
    long long x;
    cin >> x;
    for(int i = 1; i <= x; ++i) {
        for(int j = i; j < x; ++j) {
            cout << " ";
        }
        for(int j = 1; j <= i*2-1; ++j) {
            cout << "*";
        }
        cout << endl;
    }
}
