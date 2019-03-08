//you don't define a method
/*
define_a_type.cpp
CS2124 Sec D
2019 Spring
*/
#include <string>
#include <iostream>
using namespace std;

struct wheel();
struct Motorcycle{
    int numCyl;
    string brand;
    string model;
    vector<wheel> wheels;
};

void printMotorcycle(const Motorcycle& someBike);

int main(){
    //C always has to put struct in front of the type
    Motorcycle aBike;

    //cannot print out vector, or customized type Motorcycle
    //we havent written a code for Motorcycle methods
    //#include <string> - print is defined here.
    //cout << aBike << endl;

    printMotorcycle(aBike);
    aBike.brand = "Suzuki";
    aBike.model = "Vstrom";
    aBike.numCyl = 2;
    printMotorcycle(aBike);

    ifstream ifs("bikes.txt");
    if(!ifs){
        cerr << "Cannot find the file" << endl;
        exit(1);
    }

    vector<Motorcycle> vm;
    //avoid new
    //new for allocating heap like Java
    Motorcycle someBike;
    while(fs >> someBike.brand >> someBike.model >> someBike.numCyl){
        vm.push_back(someBike);
    }
    //if they have not been initialized, like a string- empty string
    //using default constructor- 
    //in C++: a constructor that can't take any argument

    string brand, model;
    int cyl;
    while(ifs >> brand >> model >> cyl){
        //each time in the loop, this is reinitialized
        //after loop, I cannot refer to this motorcycle
        Motorcycle someOtherBike;
        someOtherBike.brand = brand;
        someOtherBike.model = model;
        someOtherBike.numCyl = cyl;
        vm.pushback(someOtherBike);
    }
}

void printMotorcycle(const Motorcycle& someBike){

    //2 types of variables: str and primitive
    //primitive may not be initialized in in this case
    //string s; 
    //string obj is defined with string default constructor
    //same idea with vector<int> v;

    cout << "Motorcycle: " << someBike.brand << ' ' 
    << someBike.model << ' ' << someBike.numCyl << endl;
}