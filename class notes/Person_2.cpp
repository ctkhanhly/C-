#include <iostream>
#include <string>
using namespace  std;

class Person{
    friend  ostream& operator<<(ostream& os, const Person& rhs){
        os << "Name: " << rhs.name;
        os <<  ' '  << (rhs.spous != nullptr) ? "marries":"single");
        if(rhs.spouse != nullptr){
            // os << (rhs.spouse).name;
            os <<  rhs.spouse-> name;
        }
        return os;
    }
    //whether i'm married single or multiple marries
    //marries and single must be of the same type.

public:
    //nullptr: novalid address, pointer primitive no need to be initialized, do it anyway
    Person(const string& name): name(name), spouse(nullptr){}

    //PASS by value - make a copy that lasts until the end of the function
    void marries(const Person& betrothed){
        if(spouse == nullptr &&  betrothed.spouse == nullptr ){
            spouse =  &betrothed;
            //betrothed.spouse =  spouse;
            //equal to a pointer
            spouse->name  = "Matthilda"; // 
            //betrothed.spouse = this;
            //check if they're already married
        }

    }
private:
    string name;
    //Person& spouse; - why not this?, not a person we marry, a separate person
    //doesnt quite do what we want
    //All pointer variables are primitive
    //field of exact same  type, not going to work. size of Person and a string inside size Person
    //IMPOSSIBLE
    Person* spouse;
};

//writing test code before any function
int main(){
    Person  john("John");
    Person  mary("Mary");
    cout << john << endl;
    cout << mary << endl;

    john.marries(marry);

    int x  =  17;
    cout << x << endl;
    cout  << &x << endl; //hexadecimal number -  address, address-of operator

    //variable that can hold an address is a pointer, has to have type
    int* p = &x; //most prefered definition
    // int *p = &x;
    // int * p = &x;

    cout << p << endl;
    //from pointer to value
    cout << *p << endl;
    *p = 42;  //Java hamstring the pointer- no access - safer - no mistake

    const int y = 2;
    //iny* p = &y- illegal
    //pointer  to const  int, have to know what type  x is
    const  int*  q = &y;
    q = &x;// q treat anything  it sets to as const
    x= 100;
    //*q = 64; -  illegal //  cannot change x by  assigning to the ref
    //obvious
    int*  const r = &x;// address can never change
    //int* r = &x;
    *r = 28;

    int z = 49;
    r = &z;

    //Person Fred;// what is this? enough Heap space - make a Person obj, if not, heap automatically grows
    //in python every obj is heap.
    Person* pptr  = new Person("George");// C++ know  put it anywhere we want  - new allocated space and return new address
    //new to allocate on heap

    //....
    
    //remove from heap,  
    delete pptr;
}
//vector.emplace_back("Fred", 17);, Thing string s, int n.- not a copy?
//2 objects want to have rls -  can use pointers
//spouse  by reference if John marries many Mary
//ref has to be established be4 variable