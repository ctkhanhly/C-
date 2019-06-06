#include <iostream>
#include <vector>
using namespace std;

int maxSatisfied(const vector<int>& customers, const vector<int>& grumpy, int X){
    int satisfied = 0, maxConseCounting = 0, curr_counting = 0;
    for(size_t i = 0; i < customers.size(); ++i){
        if(grumpy[i]){
            curr_counting += customers[i];
        }
        else{
            satisfied += customers[i];
        }
        if(i >= X && grumpy[i-X]) curr_counting -= customers[i-X];
        maxConseCounting = max(curr_counting, maxConseCounting);
    }
    //added satisfied instead of maxConseCounting better
    return maxConseCounting + satisfied;
}
int main(){
    vector<int> customers = {1,0,1,2,1,1,7,5};
    vector<int> grumpy = {0,1,0,1,0,1,0,1};
    int X = 3;
   
    // vector<int> customers = {1};
    // vector<int> grumpy = {0};
    // int X = 1;
    cout << maxSatisfied(customers, grumpy, X) << endl;
}

/*

int maxSatisfied(vector<int>& cs, vector<int>& grumpy, int X) {
    auto satisfied = 0, m_add_satisfied = 0, add_satisfied = 0;
    for (auto i = 0; i < cs.size(); ++i) {
        satisfied += grumpy[i] ? 0 : cs[i];
        add_satisfied += grumpy[i] ? cs[i] : 0;
        if (i >= X) add_satisfied -= grumpy[i - X] ? cs[i - X] : 0;
        m_add_satisfied = max(m_add_satisfied, add_satisfied);
    }
    return satisfied + m_add_satisfied;
}
*/