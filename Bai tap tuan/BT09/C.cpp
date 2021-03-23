#include <bits/stdc++.h>
using namespace std;

struct String{
    int n;
    const char* str;

    String(const char* s) {
        const char* _str = new char;
        _str = s;
        str = _str;
    }

    ~String() {
        delete [] str;
    }

    void print() {
        cout << str;
    }

    void append(const char* other) {

    }
};

int main() {
    String hel("Helloo");
    hel.append(" There!")
    hel.print();
}

