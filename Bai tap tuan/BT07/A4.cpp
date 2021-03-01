#include <bits/stdc++.h>
using namespace std;

int binarySearch(int* arr, int l, int r, int x) {
  if (r >= l) {
    int mid = l + (r - l) / 2;
    if (*(arr+mid) == x)
      return mid;
    if (*(arr+mid) > x)
      return binarySearch(arr, l, mid - 1, x);
    return binarySearch(arr, mid + 1, r, x);
  }
  return -1;
}

int main(){
    int A[31] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    int n = sizeof(A) / sizeof(A[0]);
    cout << binarySearch(A, 0, n-1, 19);
}


