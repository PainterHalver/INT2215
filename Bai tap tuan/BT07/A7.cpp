#include <bits/stdc++.h>
using namespace std;


int main() {
	string s,t;
	cin >> s;
	cin >> t;
	int count = 0;
	for(int i =0; i< t.size(); ++i) {
	    char* q= new char[s.size()];
        for(int j=0; j<s.size(); ++j){
            q[j] = t[i+j];
        }
        if(strcmp(&s[0],q) == 0) count++;
	}
	cout << count;

}


