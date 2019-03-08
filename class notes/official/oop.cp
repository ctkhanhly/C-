/*
  Sec D
 */
#include <string>
#include <iostream>
using namespace std;

class Date { 
    friend ostream& operator<<(ostream& os, const Date& theDate);
    // {
    //     os << theDate.month << '/' << theDate.day << '/' << theDate.year;
    //     return os;
    // }

public:
    Date(int m, int d, int y) : month(m), day(d), year(y) { }
    void display() const { cout << month << '/' << day << '/' << year; }
private:
    int month, day, year;
};

ostream& operator<<(ostream& os, const Date& theDate) {
    os << theDate.month << '/' << theDate.day << '/' << theDate.year;
    return os;
}

//struct Person {
class Person {
public:

    //Person(const string& theName, int theAge) {
    //Person(const string& theName, int theAge) : name(theName) {
    //Person(const string& theName, int theAge) : name(theName), age(theAge) {
    Person(const string& name, int age, int m, int d, int y) 
        : name(name), age(age), dob(m, d, y)
    {
        //name = theName;
        //age = theAge;
    }

    //    Person() {}


    void run() { cout << name << " running\n"; }
    void setName(const string& theName) {
        name = theName;
    }

    const string& getName() const { 
        // name = "fred";
        return name; 
    }

    // void setAge(int theAge) {
    //     age = theAge;
    // }

    const Date& getDOB() const { return dob; }

private:    
    string name;
    const int age;
    Date dob;
};



void displayPerson(const Person& somebody) {
    cout << "Person: " << somebody.getName() << ", ";
    somebody.getDOB().display();
    cout << endl;
}
                   

int main() {
    //    Person fred;
    Person fred("Fred", 19);
    // //    fred.name = "Fred";
    // fred.setName("Fred");
    // //fred.age = 19;
    // fred.setAge(19);
    fred.run();

    //Person mary; // Do we really want to define mary without her name...?
    //Person mary(); // Function prototype
    Date independence(7, 4, 1776);
    independence.display();
    cout << independence << endl;
    //operator<<(cout, independence);
    

}
