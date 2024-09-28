#include<iostream>
#include<string.h>
#include<string>
#define Maximun 500
using namespace std;
//用顺序表，顺序表遍历很方便
int N, A;
typedef struct {
    int c[Maximun];
    int length;
}LargeInt;                     //定义大整数结构体
 
typedef LargeInt ElemType;        //声明在此程序中，ElemType是LargeInteger的同义词
//提高代码复用性
constexpr auto MaxSize = 500;
typedef struct {
    ElemType* elem;                //顺序表的元素
    int length;                    //顺序表的当前长度
}SqList;                        //顺序表的类型定义
 
void InitList(SqList& L) {        //创建一个空的顺序表 
    L.elem = new ElemType[MaxSize];
    if (!L.elem) {
        exit(0);
    }
    else {
        L.length = 0;
    }
}
//插入操作，在表L的第i个位置上插入指定元素e 
bool ListInsert(SqList& L, int i, ElemType e) {
    if (i<1 || i>L.length + 1) {
        return false;
    }
    if (L.length >= MaxSize) {
        return false;
    }
    for (int j = L.length + 1; j > i; j--) {
        L.elem[j] = L.elem[j - 1];
    }
    L.elem[i] = e;
    L.length++;//长度要++
    return true;
}
LargeInt IntoLarge(int minum) {
    LargeInt lanum;
    memset(lanum.c, 0, sizeof(lanum.c));
    lanum.length = 1;
    for (int i = 1; minum != 0; i++) {
        int temp = minum % 10;
        minum /= 10;
        lanum.c[i] = temp;
        lanum.length = i;
    }
    return lanum;
}
 
LargeInt multi(LargeInt num, LargeInt base) {
    LargeInt ans;
    ans.length = 1;
    memset(ans.c, 0, sizeof(ans.c));
    ans.length = num.length + base.length;
    for (int i = 1; i <= num.length; i++) {
        for (int j = 1; j <= base.length; j++) {
            ans.c[i + j - 1] += num.c[i] * base.c[j];
            ans.c[i + j] += ans.c[i + j - 1] / 10;
            ans.c[i + j - 1] %= 10;
        }
    }
    while (ans.c[ans.length] == 0 && ans.length > 1) {
        ans.length--;
    }
 
    return ans;
}
LargeInt add(LargeInt a, LargeInt b) {
    LargeInt ans;
    memset(ans.c, 0, sizeof(ans.c));
    ans.length = max(a.length, b.length) + 1;
 
    for (int i = 1; i <= ans.length; i++) {
        ans.c[i] += a.c[i] + b.c[i];
        ans.c[i + 1] += ans.c[i] / 10;
        ans.c[i] %= 10;
    }
 
    if (ans.c[ans.length] == 0) {
        ans.length--;
    }
 
 
    return ans;
}
void LargePrint(LargeInt num) {
    for (int i = num.length; i > 0; i--) {
        printf("%d", num.c[i]);
    }
    cout << endl;
}
 
 
int main() {
    string s1, s2;
    char c1, c2;
    LargeInt base;
    LargeInt ans;
    int N, A;
cin>>N>>A;
            SqList L;
            InitList(L);
            base = IntoLarge(A);
            memset(ans.c, 0, sizeof(ans.c));
 
            L.elem[0] = IntoLarge(1);
            for (int i = 1; i <= N; i++) {
                memset(L.elem[i].c, 0, sizeof(L.elem[i].c));
 
                L.elem[i] = multi(L.elem[i - 1], base);
                L.elem[i - 1] = multi(L.elem[i - 1], IntoLarge(i - 1));
                ans = add(ans, L.elem[i - 1]);
            }
            L.elem[N] = multi(L.elem[N], IntoLarge(N));
            ans = add(ans, L.elem[N]);
            LargePrint(ans);
        
    return 0;
}