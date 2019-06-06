#include <iostream>
#include <string>
#include <vector>
using namespace std;

class A{
    string name;
public:
    A(const string& name): name(name){}
    const string& getName()  const{
        return name;
    }
    virtual void sayHello(A a){
        cout << name << " hello "<< a.getName();
    }
};

class B: public A{
public:
    B(const string& name): A(name){}
    virtual void sayHello(A a){
        cout << A::getName() << " hello " << a.getName();
    }
};

class C: public A{
public:
    C(const string& name): A(name){}
    virtual void sayHello(A a){
        cout << A::getName() << " hello " << a.getName();
    }
};

int main(){
    A a("A");
    B b ("B");
    C c("C");
    a.sayHello(b);
    cout << endl;
    b.sayHello(c);
    cout << endl;
    c.sayHello(a);
    cout << endl;
    a.sayHello(c);
    cout << endl;
}