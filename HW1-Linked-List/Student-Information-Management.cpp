#include<iostream>
using namespace std;
int n = 0;
 
typedef struct {
    string id;                    //学号
    string name;                //姓名
}student;                        //定义学生信息结构体
 
typedef student ElemType;        //声明在此程序中，ElemType是student的同义词
                                //提高代码复用性
constexpr auto MaxSize = 100001;//定义线性表的最大长度,一定要够大 ，最开始定义了1e4，只有50分，改成100001 80分 一个time limitexceed 
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
    if (L.length >=MaxSize) {
        return false;
    }
    for (int j = L.length+1; j > i; j--) {
        L.elem[j] = L.elem[j - 1];
    }
    L.elem[i] = e;
    L.length++;//长度要++
    return true;
}
//删除顺序表中第i个元素（1<=i<=L.length）,用引用变量e返回，如果i的位置不合法，则
//返回false，否则，把被删除的元素赋给e，
//并把从i+1个元素开始之后的元素都往前移一位
//L.length-1 
//return true 
bool ListDelete(SqList& L, int i, ElemType& e) {
    if (i<1 || i>L.length) {
        return false;
    }
    e = L.elem[i];
    for (int j = i+1; j <= L.length; j++) {
        L.elem[j - 1] = L.elem[j];
    }
    L.length--;
    return true;
}
int LocateName(SqList L, string nam) {
    for (int i = 1; i <= L.length; i++) {
        if (L.elem[i].name == nam) {
            return i;
        }
    }
    return 0;
}
int LocateID(SqList L, string ID) {
    for (int i = 1; i < L.length; i++) {
        if (L.elem[i].id == ID) {
            return i;
        }
    }
    return 0;
}
int ListLength(SqList L) {
    return L.length;
}
//输入都是从1开始，存储以及修改都是从0开始 
int main() {
    SqList L;
    InitList(L);
 
    cin >> n;
 
    for (int i = 1; i <= n; i++) {
        ElemType e;    
        cin >> e.id>> e.name;
        ListInsert(L, i, e);
    }
    string choice;
    while (cin >> choice) {
        if (choice == "insert") {
            int i;
        
            cin >> i;
            ElemType e;
            
            cin >> e.id >> e.name;
            if (ListInsert(L,i, e)) {
                cout<<0<<endl;
            }
            else {
                cout<<-1<<endl;
            }
        }
        if (choice == "remove") {
            ElemType e;
            int j;
            cin >> j;
            if (ListDelete(L, j, e)) {
                cout<<0<<endl;
                
            
            }
            else {
                cout<<-1<<endl;
            }
 
        }
        if (choice == "check") {
            cin >> choice;
            if (choice == "name") {
                string nam;
            
                cin >> nam;
                int i = LocateName(L, nam);
                if (i == 0) {
                
                    cout << -1 << endl;
                }
                else {
                
                    cout << i << " " << L.elem[i].id << " " << L.elem[i].name << endl;
                }
            }
            if (choice == "no") {
                string ID;
            
                cin >> ID;
                int i = LocateID(L, ID);
                if (i == 0) {
                
                    cout << -1 << endl;
                }
                else {
                
                    cout << i << " " << L.elem[i].id << " " << L.elem[i].name << endl;
                }
            }
        }
        
        if (choice == "end") {
           
            cout << ListLength(L) << endl;
            return 0;
        }
    }
 
    return 0;
}