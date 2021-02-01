#include <iostream>
using namespace std;

bool check(int* arr, int num) {
    long sumLeft = 0;
    long sumRight = 0;
    for(int j = 0; j < num; ++j) {
            sumRight += arr[j];
        }
    for(int i = 0; i < num; ++i) {

        sumLeft += arr[i-1];


        sumRight -= arr[i];

        if(sumLeft == sumRight) return true;
    }
    return false;
}

int main(){
    int times;
    cin >> times;
    for(int i = 0; i < times; ++i) {
        int num;
        cin >> num;
        int arr[num];
        for (int j = 0; j < num; ++j) {
            cin >> arr[j];
        }
        if(check(arr, num)) cout << "YES"; else cout << "NO";
        cout << endl;
    }
}


