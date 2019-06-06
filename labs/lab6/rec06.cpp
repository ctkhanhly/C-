/*
  Recitation 06
  CS2124
 
  Focus: Dynamic arrays and copy control
 */
//size_t 4 bytes, unsigned: 2 bytes
#include <iostream>
#include <string>
#include <iostream>
using namespace std;
/*
Fill in the missing code for the Directory add method.
Overload Directory's output operator. Test your code now!
Implement the Big 3 (i.e., destructor, copy constructor and assignment operator) for the Directory class. At the beginning of each of these functions, add a print statement to show when you have entered them. This will help you understand when / where they are each being used.
Overload Directory's [] operator to allow looking up a person's phone number, by passing in their name.
You should (as always) consider if there is any way to further expand the code in main() to test your new features.

Note that the Directory is responsible for both the Entries and the dynamic array itself.
*/
class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
//everything has a default copy constructor
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
        : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }

    //added
    unsigned getRoom() const { return room; }
    Position* getPosition() const { return pos; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& d){
        os << "Entries: ";
        for(size_t i = 0; i < d.size; i++){
            os << endl;
            os << "\t";
            os << *(d.entries[i]);
            // ->getName() << ": " << "phone: " << d.entries[i]-> getPhone() 
            // << ", room: " << d.entries[i]->getRoom() << ", postion: " << *(d.entries[i]->getPosition());
        }
        return os;
    }
public:
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...
    Directory(): size(0), capacity(1), entries(new Entry*[1]){}
    //didnt create entries on heap
    Directory(const Directory& d): size(d.size), capacity(d.capacity), entries(new Entry*[d.capacity]){
        for(size_t i = 0; i < size; i++){
            //********
            // add(d.entries[i]->getName(), d.entries[i]->getRoom(), d.entries[i]->getPhone(),
            // *d.entries[i]->getPosition();
            //add entry to array that doesnt exist if not initialized entries
            entries[i] = new Entry(*d.entries[i]);
        }
    }
    ~Directory(){
        for(size_t i = 0; i < size; i++){
            delete entries[i];
        }
        delete [] entries;
    }
    Directory& operator=(const Directory& d){
        if(this != &d){
            for(size_t i = 0; i < size; i++){
                delete entries[i];
            }
            delete [] entries;

            size = d.size;

            entries = new Entry*[d.capacity];
            for(size_t i = 0; i < size; i++){
                //********
                // add(d.entries[i]->getName(), d.entries[i]->getRoom(), d.entries[i]->getPhone(),
                // *d.entries[i]->getPosition() );
                //add beyound size
                entries[i] = new Entry(*d.entries[i]);
            }

        }

        return *this;
        
    }
    
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)	{
            // something is missing!!!  Add it!
            //local pointer
            Entry** oldEntries = entries;
            capacity = 2* capacity;
            entries = new Entry*[capacity];
            for(size_t i = 0; i < size; i++){
                entries[i] = oldEntries[i];//each member in new entries still point to the same, old one
                //=> dont delete each member here
            }
            //delete what this pointer points to
            delete [] oldEntries; //is oldEntries automatically destructed?
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

    unsigned operator[](const string& name) const {
        //return  phone number
        //cannot use range for for array in heap? - doesnt have iterator?
        for(size_t i = 0; i < size; i++){
            if(entries[i]->getName() == name){
                return entries[i]->getPhone();
            }
        }
        return -1;
    }


private:	
    Entry** entries; 
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
	
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
	
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;
	
} // main

