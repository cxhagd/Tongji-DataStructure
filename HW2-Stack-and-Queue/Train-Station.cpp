#include<iostream>
#include<string>
constexpr auto MAXSIZE = 100;
using namespace std;
string enter, out;
//用顺序栈实现。
typedef char ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    int top;
}SqStack;
void InitStack(SqStack& S) {
    S.top = -1;
}
bool StackEmpty(SqStack S) {
    return (S.top == -1);
}
bool Push(SqStack& S, ElemType e) {
    if (S.top == MAXSIZE - 1)return false;
    S.data[++S.top] = e;
    return true;
}
bool Pop(SqStack& S, ElemType& e) {
    if (S.top == -1)return false;
    e = S.data[S.top--];
    return true;
}
bool GetTop(SqStack S, ElemType& e) {
    if (S.top == -1)return false;
    e = S.data[S.top];
    return true;
}
 
int main() {
    cin >> enter;
    SqStack S;
    InitStack(S);
    bool jud = 1;
    char ch = cin.get();
    while (getline(cin, out)) {
        int j = 0, i = 0;
        int match = 0;
        while (i < out.size() && j < enter.size()) {
            if (out[i] == enter[j]) {
                //push pop    
                match++;
                j++;
                i++;
            }
            if (out[i] != enter[j]) {
                ElemType top;
                if (GetTop(S, top)&&top == out[i]) {
                    Pop(S, top);
                    match++;
                    i++;
                }
                else {
                    while (enter[j] != out[i] && j < enter.size()) {
                        Push(S, enter[j]);
                        j++;
                    }
                    if (enter[j] == out[i]) {
                        j++; i++;
                        match++;
                    }
                }
 
            }
        }
        while (i < out.size() ) {
            ElemType top;
            if (!StackEmpty(S)) {
                Pop(S, top);
                if (top == out[i]) {//此时弹出栈必匹配 如果不匹配说明应该结束循环
                    i++;
                    match++;
                }
                else {
                    break;
                }
            }
        }
 
        if (match == enter.size()) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
        while (!StackEmpty(S)) {
            ElemType bin;
            Pop(S, bin);
        }
    }
}