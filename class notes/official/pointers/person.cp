/*
  CS2124 - 2019 Spring
  Sec D
 */

#include <iostream>
#include <string>
using namespace std;

class Person {
    friend ostream& operator<<(ostream& os, const Person& rhs) {
        os << "Name: " << rhs.name;
        os << ' ' << ( (rhs.spouse != nullptr) ? "marries" : "single"); 
        if (rhs.spouse != nullptr) {
            //            os << (*rhs.spouse).name;
            os << rhs.spouse->name;
        }
        return os;
    }
public:
    Person(const string& name) : name(name), spouse(nullptr) {}

    //    void marries(const Person& betrothed) {
    void marries(Person& betrothed) {
        if (spouse == nullptr && betrothed.spouse == nullptr ) {
            spouse = &betrothed;
            //spouse->name = "Matthilda";
            betrothed.spouse = this;
        }
    }

private:
    string name;
    //Person spouse;
    //    Person& spouse;
    Person* spouse;
};

int main() {
    Person john("John");
    Person mary("Mary");
    cout << john << endl;
    cout << mary << endl;
    john.marries(mary);

    int x = 17;
    cout << x << endl;
    cout << &x << endl; // address-of operator

    int* p = &x;
    //int *p = &x;
    //int * p = &x;

    cout << p << endl;
    cout << *p  << endl; // dereference operator
    *p = 42;


    const int y = 2;
    //int* q = &y; // illegal 
    const int* q = &y;
    q = &x;

    x = 100;
    //*q = 64; // illegal

    int* const r = &x;
    *r = 28;

    int z = 49;
    r = &z; // illegal

    //Person fred;
    Person* pptr = new Person("George");

    // ...

    delete pptr;
}

