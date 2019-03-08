#include <iostream>
#include <string>
using namespace std;

void convertToTime(int sec){
    int day, hour, min, second;
    string format;
    day = sec / 3600 / 24;
    hour = sec / 3600;
    min = (sec % 3600)/60;
    second = sec % 60;
    if(hour < 10){
        cout << "0" << hour << ":";
        // format.push_back("0");
        // format.push_back(hour);
        // format.push_back(":");
    }
    else{
        cout << hour << ":";
        // format.push_back(hour);
        // format.push_back(":");
    }
    // format.push_back(min);
    // format.push_back(":");
    //cout << min << ":";
    //cout << second << endl;
    if(min < 10){
        cout << "0" << min << ":";
    }
    else{
        cout << min << ":";
    }
    if(second < 10){
        cout << "0" << second << endl;
    }
    else{
        cout << second << endl;
    }
    //format.push_back(second);
    //return format;
}
int main(){
    int sec;
    cin >> sec;
    if(sec < 0){
        cout << "total second must be a positive integer" << endl;
    }
    else{
        //cout << convertToTime(sec)<< endl;
        convertToTime(sec);
        cout<< endl;
    }
}
