#include <iostream>
#include <set>
#include  <vector>
#include <string>
#include <cmath>
using namespace std;

//pow(base,power)
//sqrt(square)
vector<bool> primeNumbers (pow(10,7), true);
bool isPrime(int num){
    if(num == 2){
        return true;
    }
    int count = 0;
    for(int i = 1;  i <= (int)(sqrt(num))+1; ++i){
        if(num % i == 0){
            count++;
        }
    }
    return count * 2 == 2;
}


size_t primeNumberLessThanYou(int num){
   // vector<int> primeSequence;
   if(primeNumbers[num]){
       return num;
   }
    for(size_t i = 2; i <= (int)(sqrt(num))+1; ++i){
        //set<int>::iterator it;
        if(num % i == 0 && primeNumbers[i]){
            //if(primeNumbers[i]){
            return i;
            // }
            // else{
            //     return num / i ;
            // }
        } 
    }
    return 1;
}
int nthElement(int n){
    if(n == 0 || n == 1){
        return 0;
    }
    else{
        return nthElement(n-1) + primeNumberLessThanYou(n);
    }
}
int main(){
    //total first 10^3 primes.
    //vector<bool> primeNumbers (pow(10,7), true);
    primeNumbers[0] = false;
    primeNumbers[1] = false;
    for(size_t i = 2; i < pow(10,7); ++i){
        if(primeNumbers[i]){
            for(size_t x = pow(i,2); x < pow(10,7); x+=i){
                primeNumbers[x] = false;
            }
        }
    }
    // cout<< primeNumbers[2] << endl;
    // cout << primeNumbers[3] << endl;
    //cout << primeNumbers[0] << " " << primeNumbers[1];
    // for(bool x: primeNumbers){
    //     cout << x << " ";
    // }
    // cout << endl;
    //inputs
    vector<int> testSequence;
    int testCasesNum;

    cin >> testCasesNum;
    int num; 
    while(testCasesNum > 0){
        cin  >> num;
        testSequence.push_back(num);
        testCasesNum--;
    }
    cout<< "sequence: " << endl;

    // cout << endl;
    // cout << isPrime(2) << endl;
    // cout << primeNumberLessThanYou(2) << " " << primeNumberLessThanYou(3)<< " " << primeNumberLessThanYou(4) << endl;

    for(int i : testSequence){
        cout << nthElement(i) << endl;
    }
}