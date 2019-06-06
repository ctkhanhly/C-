#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

// map<int, pair<int,int>> resBitAndCarry = {{-2,{0,1}}, {-1,{1,1}},{0,{0,0}},{1,{1,0}},{2,{0,-1}},{3,{1,-1}}};
map<int, pair<int,int>> resBitAndCarry = {{-2,pair<int,int>(0,1)}, {-1,pair<int,int>(1,1)},{0,pair<int,int>(0,0)}
,{1,pair<int,int>(1,0)},{2,pair<int,int>(0,-1)},{3,pair<int,int>(1,-1)}};

// void printVector(const vector<int>& vec);
void printVector(vector<int> vec);
vector<int> addNegabin(const vector<int>& arr1, const vector<int>& arr2){
    int tracer = max(arr1.size(), arr2.size()) + 3;
    // error: variable-sized object may not be initialized
    //int carry[tracer] = {};
    int carry[tracer];
    for(size_t i = 0; i < tracer; ++i){
        carry[i] = 0;
    }
    //int arr[]
    vector<int> res;
    int curr_sum = 0;
    int tracer1 = arr1.size() - 1;
    int tracer2 = arr2.size() - 1;
    --tracer;
    while(tracer1 >= 0 && tracer2 >= 0){
        //cout << carry[tracer] << endl;
        curr_sum =  arr1[tracer1] + arr2[tracer2] + carry[tracer];
        if(--tracer >= 0) carry[tracer] = resBitAndCarry[curr_sum].second;
        //cout << curr_sum;
        //cout << resBitAndCarry[curr_sum].first;
        res.push_back(resBitAndCarry[curr_sum].first);
        --tracer1; --tracer2;
    }
    
    while(tracer1 >= 0 && tracer2 < 0){
        curr_sum =  arr1[tracer1] + carry[tracer];
        if(--tracer >= 0) carry[tracer] = resBitAndCarry[curr_sum].second;
        res.push_back(resBitAndCarry[curr_sum].first);
        --tracer1;
    }
    while(tracer2 >= 0 && tracer1 < 0){
        curr_sum =  arr2[tracer2] + carry[tracer];
        if(--tracer >= 0) carry[tracer] = resBitAndCarry[curr_sum].second;
        res.push_back(resBitAndCarry[curr_sum].first);
        --tracer2;
    }
    while(tracer >= 0){
        curr_sum =  carry[tracer];
        if(--tracer >= 0) carry[tracer] = resBitAndCarry[curr_sum].second;
        res.push_back(resBitAndCarry[curr_sum].first);
    }
    int n = res.size();
    //cout << endl;
    //printVector(res);
    while(n > 0 && !res[--n]){
        res.pop_back();
        //--n;
    }
    for(size_t i = 0; i < res.size()/2; ++i){
        int temp = res[i];
        res[i] = res[res.size() - 1 - i];
        res[res.size() - 1 - i] = temp;
    }
    //it's dangerous when I tried to print with const ref of a local vector, it changed my vector, damn!
    //printVector is an outside method trying to access local variable of this method!, dangerous!
    //printVector(res);
    // printVector(res);
    //reverse(res.begin(), res.end());
    //printVector(res);
    if(res.size() == 0) res.push_back(0);
    return res;
}
string convertToNegaBin(int N){
    string res;
    while(N){
        //cout << "here" << endl;
        res = to_string(N & 1) + res;
        N = -(N >> 1);
    }
    return res;
}
void printVector(vector<int> vec){
    for(int val: vec){
        cout << val ;
    }
    // for(size_t i = 0; i < vec.size(); ++i){
    //     cout << vec[i];
    // }
    cout << endl;
}
int main(){
    // cout << convertToNagaBin(1) << endl;
    // cout << convertToNagaBin(2) << endl;
    // cout << convertToNagaBin(3) << endl;
    // cout << convertToNagaBin(5) << endl;
    // //not allowed:  resBitAndCarry[2][0]
    // cout << resBitAndCarry[2].first << ' ' << resBitAndCarry[2].second << endl;
    vector<int> vec1 = {1,1,1,1,1};
    vector<int> vec2 = {1,0,1};
    printVector(addNegabin(vec1, vec2));
    // vector<int> res2 = addNegabin({1,0,1,0,1,0,1}, {1,1,1,0,1,0,0});
    // printVector(res2);
    vector<int> vec3 = {1,0,1,0,1,0,1};
    vector<int> vec4 = {1,1,1,0,1,0,0};
    printVector(addNegabin(vec3, vec4));
    vector<int> vec5 = {0};
    vector<int> vec6 = {1};
    printVector(addNegabin(vec5, vec6));
}

/*

// pair::pair example
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

int main () {
  std::pair <std::string,double> product1;                     // default constructor
  std::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
  std::pair <std::string,double> product3 (product2);          // copy constructor

  product1 = std::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

  product2.first = "shoes";                  // the type of first is string
  product2.second = 39.90;                   // the type of second is double

  std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
  std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
  std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
  return 0;
}
Edit & Run

//http://www.cplusplus.com/reference/algorithm/reverse/
*/
/*

//a very neat solution
//https://leetcode.com/problems/adding-two-negabinary-numbers/discuss/303751/C%2B%2BPython-Convert-from-Base-2-Addition
vector<int> addBinary(vector<int>& A, vector<int>& B) {
        vector<int> res;
        int carry = 0, i = A.size() - 1, j = B.size() - 1;
        while (i >= 0 || j >= 0 || carry) {
            if (i >= 0) carry += A[i--];
            if (j >= 0) carry += B[j--];
            res.push_back(carry & 1);
            carry = (carry >> 1);
        }
        reverse(res.begin(), res.end());
        return res;
    }

    vector<int> addNegabinary(vector<int>& A, vector<int>& B) {
        vector<int> res;
        int carry = 0, i = A.size() - 1, j = B.size() - 1;
        while (i >= 0 || j >= 0 || carry) {
            if (i >= 0) carry += A[i--];
            if (j >= 0) carry += B[j--];
            res.push_back(carry & 1);
            carry = -(carry >> 1);
        }
        while (res.size() > 1 && res.back() == 0)
            res.pop_back();
        reverse(res.begin(), res.end());
        return res;
    }
*/