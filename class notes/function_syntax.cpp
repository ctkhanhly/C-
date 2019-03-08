#include <iostream>
//include for any non-primitive
#include <vector>
using namespace std;

void addOne(int someInt); //function prototype

int addOneV2(int someInt){ 
    someInt++;
    return someInt;
}

void addOneRef(int& someInt){ //pass by reference
    someInt++; //+=1
    //cout <<someInt << endl;
}

//copy is being made in parameter
//first thing a function does is making a copy of the parameter
//always pass in by const reference for vectors!!!!!!!!!
void printVec(const vector<int>& someVec){ // pass by const-ref
//else, must comment to let ppl know intentionally pass by value.
//passing a primitive by reference is more work than by value.

    //someVec[0] = 42; //not just printing, now change the code too.
    for (int item: someVec){
        cout << item << ' '; //space at the end of each one
    }
    cout << endl;
}
int main(){
    int x = 17;

    //the compiler has to already have seen this function to call this
    //else it would make this an error.
    addOne(x);
    cout << x << endl;

    //it's not modifying x, for addOne void, 
    //fix by returning an int type

    x = addOneV2(x);
    cout << x << endl;

    addOneRef(x);
    cout << x << endl;

    vector<int> v1{1,1,2,3,4,8};
    //cout << vi <, endl;

    printVec(v1);

    for(int someInt : vi){
        cout << someInt << ' ';
    }

    //this won't change anything
    //or we can do const reference.
    for(int someInt : vi){
        someInt += 1;
    }

    for(int someInt : vi){
        cout << someInt << ' ';
    }

    //this will change
    for(int& someInt : vi){
        someInt += 1;
    }

    for(int someInt : vi){
        cout << someInt << ' ';
    }
}

void addOne(int someInt){ //pass by value
    someInt++; //+=1
    //cout <<someInt << endl;
}
