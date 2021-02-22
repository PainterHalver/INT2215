#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    do {
        cin >> n;
        (n >= 0 && n % 5 == 0) ? cout << n / 5 << endl : cout << -1 << endl;
    }
    while(n!=-1);
    cout << "Bye";
}
