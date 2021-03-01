#include <bits/stdc++.h>
using namespace std;

int count_even(int* arr, int n) {
    int count = 0;
    for(int i = 0; i < n; ++i) {
        if(arr[i] % 2 == 0) count++;
    }
    return count;
}

int main(){
    int A[10] = {0,1,2,3,4,5,6,7,8,9};
    cout << count_even(A, 5) << endl;
    cout << count_even(&A[10-5], 5);
}


