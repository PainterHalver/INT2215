#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x, y, z;
    bool b;
    cin >> x >> y >> z;
    if ((x < y && y < z) || (x > y && y > z)) b = true;
    else b = false;
    cout << b;
}
