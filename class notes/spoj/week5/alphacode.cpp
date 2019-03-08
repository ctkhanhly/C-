#include <iostream>
#include <string>
#include <vector>
using namespace std;

//dynamic programming = recursive
size_t countNumOfDecodings(string& number, size_t low){
    if(low >= number.size() - 1){
        //return make_tuple(true, 1);
        return 1;
    }
    else if(number[low] == '0'){
        return 0;
    }
    // else if(number[low] == '1' || (number[low] == '2' && number[low+1] < '7') && 
    //     (number[low+1] == '1' || (number[low+1] == '2' && number[low+2] < '7') ){

    // }
    else if(number[low] == '1' || (number[low] == '2' && number[low+1] < '7') ){
        return 2 * countNumOfDecodings(number, low + 2);// + countNumOfDecodings(number, low + 2);
    }
    else{
        return countNumOfDecodings(number, low + 1);
    }
}

int main(){
    string number;
    vector<string> numbers;
    while(cin >> number){
        if(number == "0" || number[0] == '0'){
            //cin.eof();
            break;
            //exit(0);
        }
        numbers.push_back(number);
    }
    
    for(string& number: numbers){
       cout << countNumOfDecodings(number,0) << endl;
    }
    
}