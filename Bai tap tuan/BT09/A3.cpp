#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x;
    double y;

};

Point mid_point(const Point p1, const Point p2) {
    Point re;
    re.x = (p1.x+p2.x)/2;
    re.y = (p1.y+p2.y)/2;
    return re;
}

int main()
{
        Point t;
        t.x=5;
        t.y=4;
        Point ts;
        ts.x=5;
        ts.y=4;
        mid_point(ts,t);
}

