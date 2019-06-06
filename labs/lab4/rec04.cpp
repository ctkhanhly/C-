/*
Ly Cao
Lab 4: Debug pointer-related code
*/

#include  <iostream>
#include <vector>
#include <string>
using namespace std;

struct Complex {
    double real;
    double img;
};

 class PlainOldClass {
    public:
    PlainOldClass() : x(-72) {}
    int getX() const { return x; }
    void setX( int val )  { x = val; }
    private:
    int x;
};

class PlainOldClassV2 {  
    public:
        PlainOldClassV2() : x(-72) {}
        int getX() const { return x; }
       // void setX( int x )  { x = x; } // HMMMM???
        void setX( int x )  { this->x = x; } // No confusion!
    private:
        int x;
};
class Colour {  
public:       
    Colour(const string& name, unsigned r, unsigned g, unsigned b)       
        : name(name), r(r), g(g), b(b) {}       
    void display() const { 
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")"; 
    }   
private:       
    string name;      // what we call this colour       
    unsigned r, g, b; // red/green/blue values for displaying  
};         

class SpeakerSystem {
   public:
   void vibrateSpeakerCones(unsigned signal) const {

      cout << "Playing: " << signal << "Hz sound..." << endl;
      cout << "Buzz, buzzy, buzzer, bzap!!!\n";
   }
};

class Amplifier {
public:
  void attachSpeakers(const SpeakerSystem& spkrs)
   {
      if(attachedSpeakers) // not nullptr
         cout << "already have speakers attached!\n";
      else
         attachedSpeakers = &spkrs;// cannot assign normal value of speakersystem to a const one.
   }
  
   void detachSpeakers() { // should there be an "error" message if not attached?
      attachedSpeakers = nullptr; 
   } 
  
   void playMusic( ) const {
      if (attachedSpeakers)
         attachedSpeakers -> vibrateSpeakerCones(440); //default
      else
         cout << "No speakers attached\n"; 
   }
private:
   const SpeakerSystem* attachedSpeakers = nullptr; //changed this
};
//two association by adding a Amplifier in Speaker

class Person {  
public:       
    Person(const string& name) : name(name) {}
    void movesInWith(Person& newRoomate) {
        if(!newRoomate.roomie && !roomie && &newRoomate!=this){
            roomie = &newRoomate;        // now I have a new roomie            
            newRoomate.roomie = this;    // and now they do too   
        }  
        else{
            cout << newRoomate.name << " already had a roommate" << endl;
        }  
    }       
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }  
private:
    Person* roomie;       
    string name;  
};     

int main(){
    int x;  
    x = 10;  
    cout << "x = " << x << endl;
    int* p;  
    p = &x;  
    //p = 0x0012fed4;
    cout << "p = " << p << endl;
    cout << "p points to where " << *p << " is stored\n";  
    cout << "*p contains " << *p << endl;
    *p = -2763;  
    cout << "p points to where " << *p << " is      stored\n";  
    cout << "*p now contains " << *p << endl;  
    cout << "x now contains " << x << endl;

    int y(13);      
    cout << "y contains " << y << endl;      
    p = &y;      
    cout << "p now points to where " << *p << " is stored\n";      
    cout << "*p now contains " << *p << endl;      
    *p = 980;      
    cout << "p points to where " << *p << " is stored\n";      
    cout << "*p now contains " << *p << endl;      
    cout << "y now contains " << y << endl;

    int* q;      
    q = p;      
    cout << "q points to where " << *q << " is stored\n";      
    cout << "*q contains " << *q << endl;

    double d(33.44);      
    double* pD(&d);   
    *pD = *p;      
    *pD = 73.2343;      
    *p  = *pD;      
    *q  = *p;      
    // pD  = p; //pD: double*,  p: int*  
    // p   = pD;

    int joe = 24;  
    const int sal = 19;    
    int*  pI;  
    //  pI = &joe;  
    // *pI = 234;  
    //  pI = &sal; //cannot assign an int* to the address of a const int 
    // *pI = 7623;    

    // const int* pcI;
    //  pcI = &joe;  
    // *pcI = 234;  //cannot change const int
    //  pcI = &sal;   //now pcI pointer says it accept const int, then ok to assign to address of a const int
    // *pcI = 7623;   //cannot change const int

    // int* const cpI; //const pointer requires an initializer
    // int* const cpI(&joe);
    // int* const cpI(&sal);// sal is  const int,  cannot be assigned  to const pointer (int* const)
    //  cpI = &joe;  //const pointer cannot be changed,  int* const
    // *cpI = 234;  
    //  cpI = &sal;  //const pointer cannot be changed,  int* const
    // *cpI = 7623;    

    // const int* const cpcI; //const variable requires an initializer
    // const int* const cpcI(&joe);
    // const int* const cpcI(&sal);
    //  cpcI = &joe;  // *cpcI = 234;  //cannot change const value
    //  cpcI = &sal;  //cannot change const value, sal is const itself, but its address is not const
    // *cpcI = 7623; //value of const int* const is also const

//does const int* needs to be initialized

    Complex c = {11.23,45.67};      
    Complex* pC(&c);

    //cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl; //need parentheses
    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;


    PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;

    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap      
    *pDyn = 17;

    cout << "The " << *pDyn
    << " is stored at address " << pDyn
    << " which is in the heap\n";

    cout << pDyn << endl;  
    delete pDyn;  
    cout << pDyn << endl;

    //cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";  
    //cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";//it crashed
    pDyn = nullptr;

    double* pDouble = nullptr;

    // cout << "Can we dereference nullptr?  " << *pDyn << endl;   - no    
    // cout << "Can we dereference nullptr?  " << *pDouble << endl;
    //can delete nullptr

    double* pTest = new double(12);      
    delete pTest;      
    pTest = nullptr;      
    delete pTest; // safe

    short* pShrt = new short(5);      
    delete pShrt;  
    pShrt = nullptr;    
   // delete pShrt;// crash at 2nd delete

    long jumper = 12238743;      
    //delete jumper;// this is not a pointer
    long* ptrTolong = &jumper;      
    //delete ptrTolong;   //delete can only be used for heap     
    Complex cmplx;      
    //delete cmplx;// not a pointer


    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        tmpPCmplx = new Complex; // create a new Complex object on the heap
        tmpPCmplx->real = ndx;   // set real and img to be the
        tmpPCmplx->img  = ndx;   // value of the current ndx
        complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }      
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {         
        cout << complV[ ndx ]->real << endl;         
        cout << complV[ ndx ]->img  << endl;      
    }      
    // release the heap space pointed at by the pointers in the vector      
    for (size_t ndx = 0; ndx < 3; ++ndx) {         
        delete complV[ndx];
        complV[ndx] == nullptr;
    }      
    // clear the vector      
    complV.clear();
///////////////

    vector<Colour*> colours;         
    string inputName;       
    unsigned inputR, inputG, inputB;

    // fill vector with Colours from the file       
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));       
    }         

    // display all the Colours in the vector:       
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {            
        colours[ndx]->display();            
        cout << endl;       
    }

    Amplifier a1,a2,a3;
    SpeakerSystem s1,s2,s3;

    a1.playMusic();
    a2.attachSpeakers(s2);
    a2.playMusic();
    a3.attachSpeakers(s3);
    a3.playMusic();
    a3.attachSpeakers(s2);
    a3.playMusic();
    a3.attachSpeakers(s1);
    a3.playMusic();

    // write code to model two people in this world       
    Person joeBob("Joe Bob"), billyJane("Billy Jane");         

    // now model these two becoming roommates       
    joeBob.movesInWith(billyJane);         

    // did this work out?       
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;

    joeBob.movesInWith(billyJane);



}