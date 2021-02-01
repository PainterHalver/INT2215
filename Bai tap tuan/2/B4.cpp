#include <bits/stdc++.h>
using namespace std;


int main() {
    long long x;
    cin >> x;
    for(int i = x; i >= 1; --i) {
        for(int j = x; j > i; --j) {
            cout << " ";
        }
        for(int j = i*2-1; j >= 1; --j) {
            cout << "*";
        }
        cout << endl;
    }
}
