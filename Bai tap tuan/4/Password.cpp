#include <bits/stdc++.h>
using namespace std;

bool check(string a, string b) {
	if(a.length() != b.length()) return false;
	for(int i = 0; i < a.length(); ++i) {
		if(a[i] != b[a.length()-1-i]) return false; //co the sai o day
	}
	return true;
}

int main(){
	int num;
	cin >> num;
	string str[num];
	for(int i =0; i < num; ++i) {
		cin >> str[i];
	}
	for(int i =0; i < num-1; ++i) {
		for(int j = i+1; j < num; ++j) {
			if (check(str[i], str[j])) {
				cout << str[i].length() << " " << str[i][str[i].length()/2];
				return 0;
			}
		}
	}
}


