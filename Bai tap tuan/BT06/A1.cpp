#include <bits/stdc++.h>
using namespace std;

void f(int arr[]){
    cout << arr <<endl<< &arr[1] << endl;
}

int main(){
    int arr[3] = {1,2,3};
    cout << arr << endl << &arr[1] << endl;
    f(arr);
}


