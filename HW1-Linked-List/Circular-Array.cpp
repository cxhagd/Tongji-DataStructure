#include<iostream>
using namespace std;
 
long long int a[100000+11],b[100000+11];
int main(){
    long long int n,k;
    cin>>n>>k;
    k%=n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
}
    for(int i=1,j=n-k+1;i<=n;i++,j++){
        if(j>n){
            j%=n;
        }
        b[i]=a[j];
    }
    
    
    
    for(int i=1;i<=n;i++){
        cout<<b[i]<<" ";
    }
    cout<<endl; 
}