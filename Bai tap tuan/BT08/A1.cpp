#include <bits/stdc++.h>
using namespace std;

void f(int xval)
{
   int x;
   x = xval;
   // in địa chỉ của x tại đây
   cout << &x;
}
void g(int yval)
{
   int y;
   // in địa chỉ của y tại đây
   cout << &y;
}
int main()
{
   f(7);
   g(11);
   return 0;
}
