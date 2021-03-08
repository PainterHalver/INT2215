#include <bits/stdc++.h>
using namespace std;

int main( )
{
   char a[4] = "abc";
   for (char *cp = a; (*cp) != '\0'; cp++) {
      cout << (void*) cp << " : " << (*cp) << endl;
   }
   int arr[3] = {10};
   cout << &arr[2] - &arr[0] << endl;
   double db[3] = {0.0};
   cout << &db[2] - &db[0] << endl;
}
