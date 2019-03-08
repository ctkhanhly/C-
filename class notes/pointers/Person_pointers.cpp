
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Person{
    friend ostream& operator<<(ostream& os, const Person& someone){
        os << "Person: " << someone.name << ", " << someone.age;
        return os;
    }
public:
    Person(const string& name, int age): name(name), age(age){}
    const string& getName() const { return name; }
private: 
    string name;
    int age;
};

int main(){
    ifstream ifs("stooges.txt");

    vector<Person*> stooges;

    string name;
    int age;

    while(ifs >> name >> age){
        //Person someone(name, age);
        //stooges.push_back(&someone);
        Person* p = new Person(name, age);
        stooges.push_back(p);
        cout << stooges.back() << endl;
    }

    //push address of some temporary variable 
    //already planned out an entry for each local variable,
    //variable reinitialize each time in the loop
    //all members are the last member
    //p is not modified 
    for(const Person* p : stooges){
        cout << p << ' ' << p->getName() << endl;
    }
    ifs.close();

    //now delete whatever I allocated to the heap

    for(Person*& p: stooges){
        //******* no const ref but still have sth similar to Person& 
        //direct access to the memory, no copy of memory
        delete  p;
        p = nullptr;
    }

    
}
