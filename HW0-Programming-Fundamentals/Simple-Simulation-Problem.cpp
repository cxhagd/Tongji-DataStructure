#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#define lll __uint128_t
void out(lll x) {//int128输出要自己写
    if (x > 9)out(x / 10);
    putchar(x % 10 + 48);
}
 
lll m[1000001],s[1000001];
 
 
int main(){
    long long int n;
    
 m[0]=0;s[0]=1;
      for(int i=1;i<=1000000;i++){
        m[i]=s[i-1];
        s[i]=m[i-1]+s[i-1]+1;
    }
    while(cin>>n){
        if(n==-1){
            break;
        }
        
        out(m[n]);
        cout<<" ";
        out(s[n]);
        cout<<endl;
    }
    
    
}