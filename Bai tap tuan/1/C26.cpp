#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    double avg = 0;
    double s;
    cin >> s;
    avg += s/n;
    double max = s;
    double min = s;
    for (int i = 1; i< n; ++i) {
        double t;
        cin >> t;
        avg += t/n;
        if(t > max) max = t;
        if(t < min) min = t;
    }
    cout << "Mean: " << avg << endl;
    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;
}
