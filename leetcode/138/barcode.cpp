#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> barcode(const vector<int>& org){
    int n_max = org[0], freq_max = 0, N = org.size();
    //for(size_t i = )
    unordered_map<int,int> um;
    vector<int> res(N);
    // for(int val : org) { ++um[val] > freq_max ? n_max = val, freq_max = um[val];}
    for(int val : org) { ++um[val] > freq_max ? n_max = val, freq_max = um[val]: freq_max = freq_max;}
    size_t i = 0;
    for(i = 0; i < freq_max*2 ; i+=2 ) res[i] = n_max;
    um.erase(n_max);
    for(pair<int,int> p : um){
        while(p.second > 0){
            i = i >= N ? 1 : i;
            res[i] = p.first;
            --p.second;
            i+=2;
        }
    }
    return res;
}
void printVector(const vector<int>& vec){
    for(int val: vec){
        cout << val << ' ';
    }
    cout << endl;
}
int main(){
    vector<int> v = {1,1,1,2,2,2};
    printVector(barcode(v));
}