#include <bits/stdc++.h>
using namespace std;

bool isPrime(int number) {
    int count=0;
    for (int i=1; i<=number; ++i)
    {
        if (number%i==0) count++;
    }
    if (count==2) return true;
    else return false;
}

int main() {
    long long x;
    cin >> x;
    if(isPrime(x)) cout << "yes"; else cout << "no";
}
