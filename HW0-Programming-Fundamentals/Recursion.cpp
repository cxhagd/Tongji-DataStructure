#include <iostream>
using namespace std;
int n, k, f;
int main()
{
    cin >> n >> k;
    for (int i = 2; i <= n; i++) {
        f = (f + k) % i;
    }
    cout << f<< endl;
    return 0;
}
×