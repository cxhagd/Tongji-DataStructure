#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
using namespace std;
 
int isp[200];
int icp[200];
void InitMap() {
    isp['('] = 1; isp[')'] = 100; isp['!'] = 50; isp['&'] = 20; isp['|'] = 10;
    icp['('] = 100; icp[')'] = 1; icp['!'] = 50; icp['&'] = 20; icp['|'] = 10;
}
 
 
typedef char Elemtype;
typedef struct Snode {
    Elemtype elem;
    struct Snode* next;
}Snode, * LinkStack;
LinkStack InitStack(LinkStack& S) {
    LinkStack top = (Snode*)malloc(sizeof(Snode));//top相当于一个头节点 
    if (top != NULL) {
        top->next = NULL;
    }
    return top;
}
bool Empty(LinkStack S) {
    return S->next == NULL;
}
void Push(LinkStack& top, Elemtype e) {
    Snode* node = (Snode*)malloc(sizeof(Snode));
    if (node == NULL) {
        exit(-1);
    }
    node->elem = e;
    node->next = top->next;
    top->next = node;
}
Elemtype Pop(LinkStack& top, Elemtype& e) {//在每一次pop前要判断栈空 top指向的是空的头节点
 
    e = top->next->elem;
    Snode* temp = top->next;
    top->next = top->next->next;
    free(temp);
    return e;
}
 
Elemtype GetTop(LinkStack top, Elemtype& e) {//在每一次gettop前要判空  top指向的是空的头节点
    e = top->next->elem;
    return e;
}
 
void StackDestroy(LinkStack& S) {
    Snode* temp = S;
    while (S->next) {
        temp = S->next;
        S->next = temp->next;
        free(temp);
    }
}
void Do(LinkStack& top, Elemtype op) {
    if (op == '!') {
        Elemtype temp = Pop(top, temp);
        if (temp == 'F')Push(top, 'V');
        if (temp == 'V')Push(top, 'F');
        return;
    }
    if (op == '|') {
        Elemtype a = 'a', b = 'b';    a = Pop(top, a); b = Pop(top, b);
        if (a == 'V' || b == 'V') Push(top, 'V');
        else Push(top, 'F');
        return;
    }
    if (op == '&') {
        Elemtype a = 'a', b = 'b';    a = Pop(top, a); b = Pop(top, b);
        if (a == 'V' && b == 'V') Push(top, 'V');
        else Push(top, 'F');
        return;
    }
}
void HandleS(string s, LinkStack& Op, LinkStack& Num) {
    int len = s.size();
    for (int i = 0; i < len; i++) {
        if (s[i] == 'V' || s[i] == 'F') {
            Push(Num, s[i]);
        }
        else {
            if (Empty(Op) || s[i] == '(') {
                Push(Op, s[i]);
                continue;
            }
            else if (s[i] == ')') {
                Elemtype top;
                while (GetTop(Op, top) != '(') {
                    Elemtype temp = ' ';
                    Pop(Op, temp);
                    Do(Num, temp);
                }
                Elemtype bin = '('; Pop(Op, bin);
                continue;
            }
            else if (s[i] == '!' || s[i] == '|' || s[i] == '&') {
                if (Empty(Op)) { Push(Op, s[i]); }
                else {
                    Elemtype insi = 'c'; insi = GetTop(Op, insi);
                    Elemtype ousi = 'c'; ousi = s[i];
                    while (!Empty(Op) && isp[insi] > icp[ousi]) {//当运算符栈非空且栈中运算符优先级比栈外运算符优先级更大，先做栈里的运算符 
                        insi = Pop(Op, insi);
                        Do(Num, insi);
                        if (Empty(Op))break;
                        insi = GetTop(Op, insi);//还不确定insi要不要做，但是要更新insi，所以是gettop 
                    }
                    Push(Op, s[i]);
                    //最后把外面的放入运算符栈 
                    //不用特判！是因为在！  |  &中  ！优先级最高，必定会入栈 
                }
                continue;
            }
        }
    }
    //如果最后符号栈中还有运算符 
    while (!Empty(Op)) {
        Elemtype opp;
        Pop(Op, opp);
        Do(Num, opp);
    }
    return;
}
 
string s;
 
 
int main() {
    InitMap();
    int i = 0; Elemtype res = 'c';
    while (getline(cin, s)) {
        LinkStack Op = InitStack(Op);
        LinkStack Num = InitStack(Num);
        HandleS(s, Op, Num);
        Pop(Num, res);
        cout << "Expression " << ++i << ": " << res << endl;
    }
}