
 
#include<iostream>
#include<iomanip>
using namespace std;
 
int main()
{
    double sum = 0, a;
    for (int i = 0; i < 12; i++)
    {
        cin >> a;
        sum += a;
    }
    cout << "¥" << fixed << setprecision(2) << sum / 12.0 << endl;
}
×