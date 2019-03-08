#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Vector{
public:
    Vector() : data(nullptr){}

    //Copy controll
    //~Vector();
    //Vector(const  Vecto&rhs)
    //Vector& operator=(constVector& rhs)

    //void push_back
private:
    //C++ cannot have 2 members of same name - field name size versus method name size
    size_t theSize;
    size_t the Capacity;
    int* data;
}
class Thing{
    friend ostream& operator<<(ostream& os, const Thing& rhs){
        return os  << "Thing: " << rhs.p;
    }
public:
    Thing(int x) { p = new int(x);}



    //copy controll
    //copy constructor - replicating everything from one obj to another in a different memory space
    Thing(const Thing& rhs) { //not passing by value!!
        //allocate sth on the heap
        p = new int(*rhs.p);//precidence - dot is prioritized over *
    }
    //when do you copy from one obj to another: assignment  x=y.
    //not initializing because only initilze when it has not existed, not initialized
    //not  yet initialized would be: Foo x = y



    void setValue(int val) { sp =  val; }
    //void  cleanup() { 
    //destructor 
    //will be called when a func of sth ceases to exist 
    ~Thing() { //like constructor no return value
        delete p;
        //p = nullptr;
    }
    //can  have this  address but cannot modify it
    const int* getP() const { return p; }

    //right hand side
    Thing& \operator==(const Thing& rhs){
        //0. Check for self-assignment
        if(this != rhs){
            // 1. Free up heap space
            delete p; //delete
             the field

            // 2, 3. copy: allocate a new obj and initialize it
            p = new int( *rhs.p );
        }
        return *this;
    }
private:
    int* p;
};

void doSomething(Thing something) { cout << something.getP() << endl; }

//constructor in parameter
void doNothing(Thing something){ return p;} 

//when finishing simplefunc, that func gets popped up
// a heap down here that has 17, variable p in the local area points to 17.
//then no pointer to that item to the heap
//important because now we don't have a way to delete the 17.
//memory leak 


//************* what is happening here?
void simpleFunc() {
    Thing aThing(17);
    cout << aThing << endl;
    //~Thing called at the end of scope - end of func/ a loop
    //dont do sth? 
    //aThing.cleapup() - sometimes  we forget to call
    //a replacement is destructor: atomatically gets called when sth is deleted from the heap
    doNothing(aThing); // a copy is being made,

    Thing anotherThing(42);
    aThing = anotherThing;
    aThing.operator=(anotherThing);
}

int main() {
    simpleFunc();
    //be aware of what you allocate and free it up later when not used
}

//do shallow copy to primitive  types and any type of pointers (primitive)
