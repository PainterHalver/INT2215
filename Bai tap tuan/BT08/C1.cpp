#include <bits/stdc++.h>
using namespace std;

int strLen(char* s){
    int count = 0;
    while(*s != '\0') {
        count++;
        s +=1;
    }
    return count;
}

void delete_char(char *S, char c){
    char* pr = S, * pw = S;
    while (*pr !='\0') {
        *pw = *(pr++);
        if(*pw != c) pw++;
    }
    *pw = '\0';
}

void pad_right(char *s, int n){
    if(strLen(s)<n){
        *(s+strLen(s))='_';
        return pad_right(s, n);
    }
}

void pad_left(char *s, int n){
    if(strLen(s)<n){
        for(int i=strLen(s)-1;i>=0;i--){
            s[i+1]=s[i];
        }
        s[0]='_';
        return pad_left(s,n);
    }
}

void reverse(char *s){
    for(int i =0; i < strLen(s)/2;++i ){
        char t = s[i];
        s[i]=s[strLen(s)-i-1];
        s[strLen(s)-i-1] = t;
    }
}

void trim_right(char *s){
    // int i=0;
    // while(s[i]!='\0'){
    //     i++;
    // }
    // s[i-1]='\0';
}

#include<cstring>
void trim_left(char *s){
    for(int i = 0; i <strlen(s); ++i){
        if(s[0]!=' ') break;
        if(*(s+i) != ' ') {
           for(int j=i; j<strlen(s); ++j) {
               char temp = *(s+j-i);
               *(s+j-i)=*(s+j);
               *(s+j) = temp;
           }
           break;
        }
    }
}

int main()
{
    char* s = "aaasdd";
    cout << strLen(s) << endl;
}

