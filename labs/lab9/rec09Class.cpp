#include <iostream>
#include <vector>
using namespace std;

// Making a method pure make the class it is an abstract class - 
// that means that C++ will not allow an object of that type to be created.
// It also means that any class deriving from that abstract class must 
// override that pure virutal method to create a concrete class - 
// that means that C++ will allow objects to be created.
// (A concrete class is a class with no pure virtual methods - all pureness has been overridden.)


//The syntax for making a virtual method be 
// a pure virtual method is to add the designation
//  "= 0" after the closing parenthsis of the parameter 
//  list (or after the const if it's an accessor). 
//  A pure virual method can have a body or it can just be a declaraion.
//   Which to choose depends on what such an abstract class could do. 

// void nonConstMethodDeclar( ) = 0; // the normal way 
// void constMethodDeclar( ) const = 0; // the normal way 
// void nonConstMethodWithBody( ) = 0 {} // INCORRECT! Even though your compiler may accept it. 
// void constMethodWithBody( ) const = 0 {} // INCORRECT! Even though your compiler may accept it.

class PrintedMaterial {
    friend ostream& operator<<(ostream& os, const PrintedMaterial& pm){
        os << pm.numberOfPages;
        return os;
    }
public:
    PrintedMaterial(unsigned numberOfPages): numberOfPages(numberOfPages){}
    unsigned getNumberOfPages() const { return numberOfPages;}
    //PrintedMaterial(): numberOfPages(0){}
    //Recall that the virtual mechanism works with either pointers to base class 
    //or reference to base class.
    virtual void displayNumPages() const = 0; //{ cout << numberOfPages; }
protected:
private:
    unsigned numberOfPages;
};
//have to define body outside the calss????
void PrintedMaterial::displayNumPages() const {
  cout << numberOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages): PrintedMaterial(numberOfPages){}
    void displayNumPages() const {
        PrintedMaterial::displayNumPages();
    }
protected:
private:
    //unsigned numberOfPages;//everywhere
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages): PrintedMaterial(numberOfPages){}
    //  void displayNumPages() const {
    //     PrintedMaterial::displayNumPages();
    // }
    //if pure method is not overrided => it stays abstract
protected:
private:
    //unsigned numberOfPages;
    //TextBooks also have an index and thus a numOfIndexPages data member.
    
};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages, unsigned numOfIndexPages): Book(numberOfPages), numOfIndexPages(numOfIndexPages){}
    //NOTE even without writing "virtual" this overriden method IS virtual.
    void displayNumPages() const {// remember const!!!!!
        //cout << numberOfPages ;// can I do this??? dont have access to numberOfPages though
        cout << "Pages ";
        PrintedMaterial::displayNumPages();
        cout << " Index Pages ";
        cout << ' '  << numOfIndexPages << endl;
    }
protected:
private:
    //unsigned numberOfPages;
    unsigned numOfIndexPages; 
};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages): Book(numberOfPages){}
    void displayNumPages() const {
         PrintedMaterial::displayNumPages();
    }
protected:
private:
    //unsigned numberOfPages;
};

// virtual void displayNumberOfPages(PrintedMaterial& pm){
//     cout << pm.getNumberOfPages();
// }

// note that reference to PrintedMaterial is the parameter type
// so now we can use the dot member operator (the .)
// if use the -> operator, that's not going to work (try it!)

// void displayNumberOfPages( const PrintedMaterial& anyPM )
// {
// 	anyPM.displayNumPages();
// }

void displayNumberOfPages(PrintedMaterial* anyPM )
{
	anyPM->displayNumPages();
}

// tester/modeler code
int main()
{
    // TextBook t;
	// Novel n;
	// Magazine m;
    TextBook t(5430, 23);
	Novel n(213);
	Magazine m(6);
	// TextBook t = TextBook(10);
	// Novel n = Novel(20);
	// Magazine m = Magazine(100);

    // Lets considervector<PrintedMaterial>.

    // We can test if this will work without working with a vector - yet.
    // This is a good development practice: try something little and get it working before putting that little thing into a bigger problem.
    // If you can't get it to work by itself in a simple context, it will be harder to solve a more complex problem with non-working code! 
    // Recall that push_back makes a COPY of the thing stored.
    // It's like an assignment statement inside the vector.


    //vector<PrintedMaterial>.
    // PrintedMaterial pm = t; // like putting a t into a vector of PrintedMaterials
    // pm.displayNumPages();
/*
    cout << "\nA PrintedMaterial material object!\n";
    PrintedMaterial pm(2345);
    pm.displayNumPages();
    pm = t;
    cout << "\nA PrintedMaterial variable containing a TextBook value\n";
	pm.displayNumPages();//print like a printed material not as a text ----- need to use virtual!!!!!!!!!!!!
    // A place that can hold a Base class pointer value can hold a pointer to ANY object that inherits from Base.
    // The virtual mechanism is only invoked when pointer to base classes are used (or reference 
    // to base class in function parameters).
    // So you must use the -> to invoke the virtual mechanism.

    // When you dereference a pointer to an base class in an 
    // inheritance hierarchy which holds the address of an object 
    // of a type that was publicly derived from the base class, 
    // you get the BASE part of the derived class! (whew! so many words!)


    cout << endl;

   // PrintedMaterial pt(300);
    // TextBook t1(200,6);
    // pt = t1;
    // pt.displayNumPages();

    // vector<PrintedMaterial*>

    // PrintedMaterial(300) pt;
    // TextBook(200,6) t1;

    cout << "Try using pointer to base type\n";
    PrintedMaterial* pmPtr;// Still not work!!!!
    pmPtr = &t;
    // instead of putting an actual PrintedMaterial
    // object into the vector, we put a pointer to
    // a PrintedMaterial object (t) into a vector
    // of pointers-to-PrintedMaterial
    // (that is, pointers to the Base class)
    // we'll be "managing" our objects by using
    // pointers to PrintedMaterial values.

    

    pmPtr->displayNumPages();//a Printed Material, does not have index 
    cout << endl;
*/
 
    cout << "\nA Print out TextBook\n";
    t.displayNumPages();
    cout << endl;
    cout << "\nA Print out Novel\n";
    n.displayNumPages();
    cout << endl;
    cout << "\nA Print out Magazine\n";
    m.displayNumPages();

    cout <<"\nA test with vector of pointers\n"; 
    vector<PrintedMaterial*> pms;
    pms.push_back(&t);
    pms.push_back(&n);
    pms.push_back(&m);
    for(PrintedMaterial* pm:pms){
        pm->displayNumPages();
        //cout << endl;
    }

    cout << endl;
    cout << t;
    cout << endl;
    cout << n;
    cout << endl;
}