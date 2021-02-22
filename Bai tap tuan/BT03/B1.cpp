#include <bits/stdc++.h>
using namespace std;


int main() {
    bool b = false;
    int n;
    int arr[n];
    cin >> n;
    for(int i = 0; i< n; ++i) {
        cin >> arr[i];
    }
    for(int i = 0; i< n; ++i) {
        for(int j = i; j< n; ++j) {
            if(arr[i] == arr[j]) {b=true; break;}
        }
    }
    cout << b;
}
