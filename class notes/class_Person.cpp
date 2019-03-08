#include <string>
using namespace std;

//struct Person - for no bahavior - just plain old data POD
//use class for struct too, but can also have behavior
//class attributes are private by default - until you separate with public?

class Date{
    //trust with private possession
    //as friend - shouldnt have so many friends if we can  call them w/o -  like if they had getters  and  setters
    //put here so that ppl can see it right off
    //access to internal asset of strem
    friend ostream& operator<<(ostream& os, const Date& theDate);//{                                                                                                                                                                                                                                                                                                      
    //     os << theDate.month << '/' << theDate.day << '/' << theDate.year;
    //     return os;
    // }
public:
    Date(int m, int d, int y) :  month(m), day(d), year(y){}
    //not changing anything, mark it const
    void display() const { cout << month << day << '/' << year; }
private:
    int month, day, year;
};
//stream are not to be copied - if does, will have compilation error
//non-member function => need a friend 
ostream& operator<<(ostream& os, const Date& theDate){
    //ostream& operator<<(ostream& os, const Date& theDate){
        //dusty deck: program been around for so long - no1 looks - dusts in code
        //once call getter - always a public method
        //compilation error bc  these are private filedp
        os << theDate.month << '/' << theDate.day << '/' << theDate.year;
        return os;
    }
//nested class only used by parent class
class Person{
public:
    //anything has name of class is a constructor, does not have return
    //let me go through a list of primitive variables, initialize all primitives
    //or let them from default constructor of string
    //initialization list: list of fields

    //age is a primtive - how get intialized by default? not get intilized 
    //just some name location in memory, no code is run to initialize age,
    //no waste of time

    //not  required to put all fields in initialized list
    //ONLY REQUIRE TO PUT ALL NON-PRIMITIVE FIELDS THERE - more efficient

    //no intialized an empty string and modify it
    // Person(const string& theName, int theAge) : go thru primitives here - initialization list: {
    //inside parenthesis - tighter scope of where name is name-field(name- closest name)

    // Person(const string& theName, int theAge): name(theName), age(theAge) {
    //     // name = theName;
    //     // age = theAge;
    // }

    //NON-PRIMITIVE you give constructor to do default value
    //str copy constructor name(name)
    //if not initalized date here - call default constructor, but we had customized one - compilation error
    Person(const string& name, int age, int m, int d, int y): name(name), age(age), dob(m,d,y) {
       
    }

    //the language gives you a default constructor until you define your own
    //=> stops providing you
    //default cosntructor - any constructor with no argument
    //make it empty str, default str empty constructor, define all default non-primitive
    //Person(): str defined here, initialization list {}
    //every obj has a meaningful value - give them constructor and default
    Person(){}

    void run() { cout << name << " running\n: "}
    void setName(const string& theName){
        name = theName;
    }
    //only getter and setter if needed
    //added const (),{} to say the func is safe
    //give the person access to real name, no copy, but don't let them change it
    const string& getName() const { 
        //name = "fred"; // compilation error - you told me it's const
        return name;
    }

    void setAge(const string& theAge){
        age = theAge;
    }

    const Date& getDOB() const {
        return dob;
    }
private:
    string name;
    int age;
    //const int age // have to initialize it in constructor, no change later, cannot setAge
    //class Date must appear before this line
    Date dob;
}; //IMPORTANT COMMA

//NEVER PASS BY VALUE FOR NON-PRIMITIVES
void displayPerson(const Person& somebody){
    //how compiler knows that method is not modifying somebody?
    cout << "Person: " << somebody.getpName() << ", ";
    somebody.display();
    cout << endl;
};

int main(){
    Person fred("Fred", 19);
    //COMPILATION ERROR: no default constructor for date
    //Person fred;
    //private by default, cannot access like this
    // fred.name = "Fred";
    //**fred.setName("Fred");
    // fred.age = 19;
    //**fred.setAge(19);

    //cannot call run b/c it is in the private section
    //hope the problem to be in compiler time not during run time
    fred.run();

    //**********has to add default constructor above in the class
    Person mary; //cannot define mary now
    //what function is called for initialization - constructor
    //Person mary(); // function prototype - func named mary return Person.

    Date independence(7,4,1776);
    independence.display();
    cout << independence;// << endl; //need overloading method - in python: __ methods
    //cout << independence << endl; //(cout << independence )error unless return a stream
    //cout<<a  <<b = (cout<<a ) <<b: the left has to be a stream otherwise i can't change output
    //has to have same stream,
    //a + b +c = (a+b) + c : left has to be an integer for I to change addition
    operator<<(cout, independence);//function

    //Polymorphism - Inheritance
    //Abstraction (ADT)
    //Encapsulation
    //Data hiding
}

//variable can hold 
//17 cannot be modified, cannot pass it in
//calling that function with a literal value
void foo(int& x){}
int a = 5;
//ok here
foo(a);
//not ok here
foo(17);


//help me out here too 
    //this is an infinite loop. there is no negative 1 -> does not stop
    //when it reaches -1. Instead, it wraps around the largest value
    for(size_t i = lines.size() - 1; i > 0; --i){
        cout << decryptString(lines[i], caesar_shift) << endl;
    }
    cout << decryptString(lines[0], caesar_shift) << endl;

    //Decrypt each line and then print the decrypted line
    // for(string& eachLine : lines){
    //     cout << decryptString(eachLine, caesar_shift) << endl;
    // }

//privacy is to the class not to the instance of the  class
//not accessing field of other class by you making sure that wouldnt happen in ur code
//all fields in class  are private
//no  global