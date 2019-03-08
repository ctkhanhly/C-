#include <iostream>
#include <set>
#include  <vector>
#include <string>
using namespace std;

//2<=T<=100: nested for loop is ok

void printNonOverlapped(set<int> S, set<int>Q){
     set<int>::iterator it;
     for (it = S.begin(); it!=S.end();  ++it) {
        if(Q.find(*it)== Q.end()){
            cout << *it << " ";
        } 
     }
     cout << endl;
}
int main(){
    set<int> S;
    set<int> Q;
    int n;
    int m;

    int Si;
    int Qi;

    cin  >> n;
    while(n > 0){
        cin >> Si;
        S.insert(Si);
        n--;
    }

    cin  >> m;
    while(m > 0){
        cin >> Qi;
        Q.insert(Qi);
        m--;
    }

    printNonOverlapped(S,Q);
}