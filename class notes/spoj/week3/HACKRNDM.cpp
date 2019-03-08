#include <iostream>
#include <vector>
#include <map>
using namespace std;

//binary search: 1 + diff > or < than middle
//C++ takes longer time for search map
//2 pointers to track the difference.
//use set
int countWantedDifference(int diff, const map<int,int>& set){
    // int count = 0;
    // for(size_t i = 0; i< set.size(); ++i){
    //     for(size_t x = i+1; x < set.size(); ++x){
    //         if(abs(set[i]-set[x])== diff){
    //             count++;
    //         }
    //     }
    // }
    // return count;
    int count = 0;
    for(auto& [x,k] : set){
        if(set.find(x.first +diff) != set.end()){
            count++;
        }
    }
    return count;
}
int main(){
    int n, k;
    cin >> n >> k;
    //vector<int> set;
    map<int,int> set;
    cout << endl;
    
    while(n>0){
        int member;
        cin >> member;
        set.insert({member, member+k});
        n--;
    }
    cout << countWantedDifference(k,set)<< endl;
}