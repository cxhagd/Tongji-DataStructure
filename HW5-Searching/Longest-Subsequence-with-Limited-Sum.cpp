#include<iostream>
#include<algorithm>
using namespace std;
 
int num[1111], sum[1111] = { 0 };
int q;
 
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
 
    sort(&num[1], &num[n + 1] );
    for (int i = 1; i <= n; i++) {
        sum[i] += sum[i - 1] + num[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> q;
        //二分法
        int  left = 1, right = n; int mid = 0;
        while (left < right) {
            mid = (left + right) / 2;
            if (sum[mid] <= q) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        cout << left-1 << " ";
    }
 
 
}