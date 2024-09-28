#include<iostream>
using namespace std;
 
string mapsuit(int i) {
    if (i == 1) {
        return "Spade";
    }
    if (i == 2) {
        return "Heart";
    }
    if (i == 3) {
        return "Club";
    }
    if (i == 4) {
        return "Diamond";
    }
 
 
}
int suitmap(string s) {
    if (s == "Spade") {
        return 1;
    }
    if (s == "Heart") {
        return 2;
    }
    if (s == "Club") {
        return 3;
    }
    if (s == "Diamond") {
        return 4;
    }
}
int nubmap(string s) {
    if (s == "A") {
        return 1;
    }
    if (s == "J") {
        return 11;
    }    
    if (s == "Q") {
        return 12;
    }    
    if (s == "K") {
        return 13;
    }    
 
    if (s == "2") {
        return 2;
    }
    if (s == "3") {
        return 3;
    }    
    if (s == "4") {
        return 4;
    }    
    if (s == "5") {
        return 5;
    }    
    if (s == "6") {
        return 6;
    }    
    if (s == "7") {
        return 7;
    }    
    if (s == "8") {
        return 8;
    }
    if (s == "9") {
        return 9;
    }
    if (s == "10") {
        return 10;
    }
 
}
 
string mapnub(int a) {
    if (a == 1) {
        return "A";
    }
    if (a == 11) {
        return "J";
    }
    if (a ==12 ) {
        return"Q" ;
    }
    if (a == 13) {
        return"K";
    }
 
    if (a == 2) {
        return "2";
    }
    if (a ==3) {
        return "3";
    }
    if (a == 4) {
        return "4";
    }
    if (a == 5) {
        return "5";
    }
    if (a == 6) {
        return "6";
    }
    if (a == 7) {
        return"7" ;
    }
    if (a == 8) {
        return "8";
    }
    if (a ==9 ) {
        return "9";
    }
    if (a == 10) {
        return "10";
    }
}
 
 
typedef struct {
    int suit;
    int nub;
}poke;
 
typedef poke ElemType;
typedef struct Dnode {
    ElemType data;
    struct Dnode* prior, * next;
}Dnode, * DLinklist;
DLinklist TailAdd(Dnode*& tail, Dnode* temp) {
    DLinklist node = (DLinklist)malloc(sizeof(Dnode));
    tail->next = node;
    node->data.nub = temp->data.nub;
    node->prior = tail;
    node->next = NULL;
    node->data.suit = temp->data.suit;
    tail = node;
    return tail;
}
DLinklist DestroyList(DLinklist& L) {
    if (L->next == NULL) {
        return L;
    }
 
    Dnode* p = L->next;
 
    while (p != NULL) {
        Dnode *q = p;
        p = p->next;
        free(q);
    }
    return L;
 
}
 
 
DLinklist SortElem(DLinklist& L, Dnode* &tail) {
    Dnode* p = L->next;
    int color;
    if (p != NULL) {
        color = p->data.suit;
    }
    if (p == NULL) {
        return L;
    }
    int sum[14] = { 0 };
    while (p != NULL) {
        sum[p->data.nub]++;
        p = p->next;
    }
    DestroyList (L);
    tail = L;
    Dnode* node = (Dnode*)malloc(sizeof(Dnode));
    node->data.suit = color;
    for (int i = 1; i <= 13; i++) {
        while (sum[i] != 0) {
            node->data.nub =i ;
            tail=TailAdd(tail,node);
            sum[i]--;
        }
    }
    return L;
}
 
DLinklist Extract(DLinklist& L, Dnode* &tail,int choice) {
    DLinklist L2 = (DLinklist)malloc(sizeof(Dnode));
    Dnode* tail2 = L2;
    L2->next = NULL;
    Dnode* p, * q=NULL;
    p = L->next;
    if (p != NULL) {
        q = p->next;
    }
    if (q == NULL) {
        return L;
    }
    if (p == NULL) {
        return L;
    }
    while (p != NULL) {
        if (p->data.suit == choice) {
            q->prior = p->prior;
            p->prior->next = q;
            tail2= TailAdd(tail2,p);
        }
        p = p->next;
        if (p == NULL) {
            break;
        }
        if (p->next == NULL&&p->data.suit==choice) {
            tail = p->prior;
            p->prior->next = NULL;
            tail2 = TailAdd(tail2, p);
            p = p->next;
            continue;
        }
        if (p->next!=NULL) {
            q = p->next;
        }
    }
    if (L2->next != NULL) {
        SortElem(L2, tail2);
        tail2->next = L->next;
        if (L->next != NULL) {
            L->next->prior = tail2;
        }
        if (L->next == NULL) {
            tail = tail2;
        }
        L->next = L2->next;
        L2->next->prior = L;
    }
    return L;
}
DLinklist Reverse(DLinklist& L, Dnode* &tail) {
    if (L->next == NULL) {
        return L;
    }
    DLinklist L2 = (DLinklist)malloc(sizeof(Dnode));
    L2->next = NULL;
    Dnode* tail2 = L2; //尾指针 
    while (tail != L) {
        tail2 = TailAdd(tail2, tail);
        tail = tail->prior;
 
    }
    tail = tail2;
    return L2;
 
}
 
DLinklist Pop(DLinklist& L, ElemType& e) {
    if (L->next == NULL) {
        e.suit = 0;
        return L;
    }
    Dnode* temp = L->next;
    e.suit = L->next->data.suit;
    e.nub= L->next->data.nub;
    if (L->next->next != NULL) {
        L->next->next->prior = L;
        L->next = L->next->next;
    }
    else {
        L->next = NULL;
    }
    free(temp);
    
    return L;
}
 
void DListPrint(DLinklist L) {
    Dnode *p = L->next;
    if (p == NULL) {
        cout  << "NULL" << endl;
        return;
    }
    int m, n;
    while (p != NULL) {
        m = p->data.suit;
        n = p->data.nub;
        cout << mapsuit(m) << " " << mapnub(n) << endl;
 
        p = p->next;
    }
}
int main() {
    
    int n;
    string order;
    DLinklist L = (DLinklist)malloc(sizeof(Dnode));
    L->next = NULL;
    Dnode* tail = L; //尾指针 
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> order;
         if (order == "Append") {
            string s; string nu;
            Dnode *temp=(DLinklist)malloc(sizeof(Dnode));
            
             cin >>s >> nu;
            temp->data.suit = suitmap(s);
            temp->data.nub = nubmap(nu);
            tail = TailAdd(tail, temp);
        }
        if (order == "Extract") {
            string choice;
            cin >> choice;
 
            L = Extract(L, tail,suitmap(choice));
        }
        if (order == "Revert") {
             L = Reverse(L, tail);
        }
        if (order == "Pop") {
            ElemType e;
            L = Pop(L, e);
            if (L->next == NULL) {
                tail = L;
            }
            if (e.suit == 0) {
                cout<< "NULL" << endl;
            }
            else {
                cout << mapsuit(e.suit) << " " <<mapnub(e.nub) << endl;//////////
            }
        }
    }
    DListPrint(L);
    return 0;
}