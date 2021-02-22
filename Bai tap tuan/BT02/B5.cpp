#include <bits/stdc++.h>
using namespace std;


int main() {
    long long x;
    cin >> x;
    for (int i=1; i<=x; ++i) {
        for (int j =i; j< i+x; ++j) {
            cout << (j > x ? j-x : j) << " ";
        }
        cout << endl;
    }
}
