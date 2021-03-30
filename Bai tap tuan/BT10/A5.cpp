#include <bits/stdc++.h>
using namespace std;


int main()
{
    int arr[5] = {1};
    int irr[5];
    irr = arr;
    irr[3] = 2;
    for(int i = 0; i<5; ++i) {
        cout << arr[i] << " ";
    }
}

