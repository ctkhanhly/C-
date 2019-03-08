#include <iostream>
using namespace std;

int reverseNumber(int num){
    int res = 0;
    while(num >= 1){
        res = res * 10 + (num % 10);
        num = num / 10;
    }  
    return res;
}
int converter(int num1, int num2){
    num1 = reverseNumber(num1);
    num2 = reverseNumber(num2);
    int total = num1 + num2;
    total = reverseNumber(total);
    return total;
}


int main(){
    int num1;
    int num2;
    cin >> num1 >> num2;
    cout << converter(num1,num2) << endl;
}

//adjacency list better than matrix