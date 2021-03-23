#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x;
    double y;

};

void print(Point p) {
    cout << &p << endl;
}

void print1(Point* p) {
    cout << &p << endl;
}

int main()
{
        Point t;
        t.x=5;
        t.y=4;
        print(t);
        print1(&t);
}

