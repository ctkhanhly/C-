#include <iostream>
#include <string>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    string alphabet = "abcdefghijklmnopqrstuvwxyz"; // single quotes for characters?
    string smallestAskedString;
    int count = 0;
    int index = 0;
    while(count < m && n > 0){
        smallestAskedString.push_back(alphabet[index]);
        count++;
        if(count == m){
            count = 0;
            index++;
        }
        n--;
    }
    cout << smallestAskedString << endl;
}