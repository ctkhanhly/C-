/*
  Copy Control
  Sec D
 */

#include <iostream>
using namespace std;

class Thing {
    friend ostream& operator<<(ostream& os, const Thing& rhs) {
        return os << "Thing: " << *rhs.p;
    }
public:
    Thing(int x) { p = new int(x); }
    //void display() const { cout << *p << endl; }
    void setValue(int val) { *p = val; }
    //void cleanup() { 
    ~Thing() {  // destructor
        //p = nullptr; 
        delete p;
    }
    const int* getP() const { return p; }


private:
    int* p;
};

void doNothing(Thing something) { cout << something.getP() << endl; }

void simpleFunc() {
    Thing aThing(17);
    cout << aThing.getP() << endl; 
    cout << aThing << endl;
    //aThing.cleanup();
    doNothing(aThing);
}

int main() {
    simpleFunc();
}
