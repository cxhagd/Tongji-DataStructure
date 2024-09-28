#include<iostream>
using namespace std;
 
 
typedef int Elemtype;
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
string s;
int isp[200];
int icp[200];
void InitMap() {
    isp['('] = 1; isp[')'] = 100;
    icp['('] = 100; icp[')'] = 1;
}
int record= 0; int loc; 
int main() {
    LinkStack S = InitStack(S);
    Push(S,-1);
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        if(s[i]=='('){
            Push(S,i);
        }
        if(s[i]==')'){
            int match;
            Pop(S,match);
            if(Empty(S)){
                Push(S,i);
            }else{
                int top;
                if(i-GetTop(S,top)>record){
                    record=i-top;
                    loc=top+1;
                }
                
            }
        }
    }
    cout << record << " " << loc << endl;
 
 
 
 
 
 
 
 
 
 
 
 
}