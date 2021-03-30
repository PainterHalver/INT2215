#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x;
    double y;

};

void print(Point p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

int main()
{
        Point t;
        t.x=5;
        t.y=4;
        print(t);
}

