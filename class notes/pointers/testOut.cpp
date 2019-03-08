#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person{
public:
    Person(const string& name, int age): name(name), spouse(nullptr), age(age){}
//private:
    string name;
    int age;
    Person* spouse;
};
int main(){
    vector<Person*> pp;
    vector<Person> p;

    string name;
    int age;

    while(cin >> name >> age){
        Person someone(name, age);
        pp.push_back(&someone);
        p.push_back(someone);
    }

    for(Person* p: pp){
        cout << p << " ";
         cout<< p->age << " " << p->name << ", ";
    }
    cout << endl;

    for(Person& p: p){
        cout << &p << " ";
        cout<< p.age << " " << p.name << ", ";
    }
    cout << endl;

}