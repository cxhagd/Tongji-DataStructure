#include<iostream>
#include<string.h>
using namespace std;
int N;
 
int a[21111];
int b[21111];
int ans = 0;
void mergesort(int left, int right) {
    if (left == right)return;
    int mid = (left + right) / 2; int i = left, j = mid + 1, k = left;
    mergesort(left, mid);
    mergesort(mid + 1, right);//把左右分别排好。 
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {//说明两段没有逆序列，赋值， 
            b[k++] = a[i++];
        }
        else {
            ans += mid - i + 1;//说明[i,mid]里的数和[j]都构成逆序列 
            b[k++] = a[j++];
        }
    }
        while (i <= mid) {
            b[k++] = a[i++];
        }
        while (j <= right) {
            b[k++] = a[j++];
        }
        for (int m = left; m <= right; m++) {
            a[m] = b[m];
        }
    
}
 
int main() {
    while (cin >> N) {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        ans = 0;
        if (N == 0) {
            break;
        }
        for (int i = 1; i <= N; i++) {
            cin >> a[i];
        }
        mergesort(1, N);
        cout << ans << endl;
    }
 
}