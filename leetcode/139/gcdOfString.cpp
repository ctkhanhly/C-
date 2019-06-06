#include <iostream>
#include <string>
using namespace std;

string findUnit(const string& str){
    int startTracer = 0, endTracer = 1, start = 0, end = 1;
    int count = 0;
    bool done =  false;
    string res;
    while( endTracer < str.size() && startTracer <= endTracer){
        ++count;
        if(str[endTracer] == str[startTracer]){
            start = startTracer;
            end = endTracer - 1;
            //cout << count << endl;
            int prevCount = count;
            while(str[endTracer++] == str[startTracer++] && --count > 0){}
            //cout << count<< endl;
            if(count > 0){
                endTracer = ++end;
                startTracer = start;
                count = prevCount;
            }
            else{
                //cout << start << ' ' << end << endl;
                if(prevCount )
                res = str.substr(start, prevCount);
                //done = true;
                //break;
            }
        }
        //cout << done << endl;
        //if(done) break;
        ++endTracer;
    }
    start = 0;
    //cout << "there" << endl;
    //end = res.size() - 1;
    while(start < str.size() && str.substr(start, res.size()) == res && res != ""){
        start += res.size();
    }
    //cout << "here" << endl;
    //if str[start] never = str[end]
    //cout << start << ' ' << str.size() << ' ' << res.size() << ' ' << res << endl;
    if(start == str.size()){
        return res;
    }
    else{
        return str;
    }
    
}
int gcd(int a, int b){
    if(b==0){
        return a;
    }
    else{
        return gcd(b, a%b);
    }
}
string gcdOfString(const string& str1, const string& str2){
    string unit1 = findUnit(str1);
    string unit2 = findUnit(str2);
    if(unit1 == unit2){
        int num1 = str1.size() / unit1.size();
        int num2 = str2.size() / unit2.size();
        int gcdNum = gcd(num1,num2);
        string res;
        while(gcdNum -- > 0){
            res+= unit1;
           // --gcdNum;
        }
        return res;
    }
    else{
        return "";
    }
    
}

int main(){
    string str = findUnit("leet");
    cout << str << endl;
    cout << findUnit("leet") << endl;
    cout << findUnit("ABCAXABCAXABCAX") << endl;
    cout << findUnit("ABCAX") << endl;
    cout << findUnit("ABCAB") << endl;
    cout << findUnit("ABAB") << endl;
    cout << findUnit("FFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKST") << endl;
    cout << findUnit("FFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKST") << endl;
    cout << endl;
    cout << gcdOfString("ABCABC", "ABC") << endl;
    cout << gcdOfString("ABABAB", "ABAB") << endl;
    cout << gcdOfString("LEET", "CODE") << endl;
//     "FFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKST"
// "FFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKSTFFBNXKST"

}

// ++count;
        // while(str[endTracer] == str[startTracer] && count > 0){//inifite loop
        //     ++startTracer;
        //     ++endTracer;
        //     --count;
        // }