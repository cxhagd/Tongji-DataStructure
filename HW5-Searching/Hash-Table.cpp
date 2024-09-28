#include<iostream>
#include<cstring>
using namespace std;
#define maxn 11001
int N, P;
int prime[maxn];//存储筛出来的素数 
int vispr[maxn];
bool vis[maxn] = {0};//散列表当中的位置 
int inipri(int prime[maxn], int vispr[maxn]) {//返回的是素数个数 
    memset(vispr, 0, sizeof(vispr));
    vispr[0] = 1; vispr[1] = 1;//0和1标记为已访问
    int k = 0;//k是筛出来的素数个数 
    for (int i = 2; i <= maxn; i++) {
        if (vispr[i] == 0) {//说明这个数是目前最小的已经确认的素数 
            prime[k++] = i;
        }
        for (int j = 2; i * j <= maxn; j++) {//以i为基点，向n构造合数
            vispr[i * j] = 1;
        }
    }
    return k;
}
int hasher(string s,int mod ) {
    int h = 0;
    for (int i = 0; i < s.length(); i++) {
        h = (h * 37 + s[i]) % mod;
    }
    return h;
}
int findpos(int hash, int p) {
    
    hash %= p;
    
    if (!vis[hash]) {
        vis[hash] = 1;
        return hash;
    }
    else if (vis[hash]) {//开始平方探测 
        for (int i = 1;i<=p/2; i++) {
            if (!vis[(hash + i * i) % p]) {
                vis[(hash + i * i) % p] = 1;
                return (hash + i * i) % p;
            }
            if (!vis[((hash - i * i) % p + p) % p]) {
                vis[((hash - i * i) % p +p) % p] = 1;
                return ((hash - i * i) % p + p) % p;
            }
        }
    }
    return -1;
}
 
int main() {
    cin >> N >> P;//待插入关键字总数  散列长度 
    if (P == 1) {
        P++;
    }
    int prinum = inipri(prime, vispr);//得到一个素数表 prime,大小为prinum 
    for (int i = 0; i < prinum; i++) {//算表长 
        if (prime[i] == P) {
            break;
        }
        if (i + 1 < prinum) {
            if (prime[i]<P && prime[i + 1]>P) {
                P = prime[i + 1];
            }
        }
    }
 
    for (int o = 1; o <= N; o++) {
        string s; cin >> s;
        
        int hash = hasher(s,P);//一边算一边取模 
        int pos = findpos(hash,P);
        if (pos == -1) {//探测后始终找不到位置 
            cout << "-" << " ";
        }
        else {
            cout << pos << " ";
        }
 
 
    }
 
 
 
}