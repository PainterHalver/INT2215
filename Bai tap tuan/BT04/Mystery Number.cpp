#include <bits/stdc++.h>
using namespace std;

void manSort(int* arr, int num) {
	for(int i = 0; i < num-1; ++i) {
        for (int j = i +1; j < num;++j) {
            if(arr[i] > arr[j]) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
	}

}

int main(){

    int num;
    cin >> num;
    int arr1[num];
    int arr2[num+1];
    for(int i = 0; i < num; i++) {
        cin >> arr1[i];
    }
    for(int i = 0; i < num+1; i++) {
        cin >> arr2[i];
    }
    manSort(arr1, num);
    manSort(arr2, num+1);
    bool end = false;
    for(int i = 0; i < num; ++i) {
        if(arr1[i] != arr2[i]) {
            end = true;
            cout << arr2[i];
            return 0;
        }
    }
    if(!end) cout << arr2[num];
}


