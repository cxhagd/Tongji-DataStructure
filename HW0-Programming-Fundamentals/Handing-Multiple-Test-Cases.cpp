#include<iostream>
#include<string> 
#include<stdio.h>
using namespace std;
int  as[130];
string s;
int f() {
    int sum = 0;
    for (int i = 0; i < s.size(); i++) {
        sum += (i+1)*as[s[i]];
    }
    return sum;
}
int main() {
    as[' '] = 0;
    for (int i = 0; i <= 25; i++) {
        as['A'+i] = i + 1;
    }
    while (1) {
 
        getline(cin, s);
        int sum = f();
        cout << sum << endl;
        char c = cin.get();
 
 
        if (c == '#') {
            break;
        }
        else {
            ungetc(c,stdin);
        }
        s = "";
    }
}
×