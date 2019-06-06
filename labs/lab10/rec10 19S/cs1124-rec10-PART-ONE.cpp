
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class MusicalInstrumentLendingLibrary{
    //stores,tests, lends
private:
    vector<Instrument*> instruments;

};
// Musical Instrument Lending Library that stores them, lends them and tests them out.
class Instrument{
private:
    MusicalInstrumentLendingLibrary  mill;
public:
    virtual void makeSound()const = 0;
};
void Instrument::makeSound() const {

}
class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << "have no instr\n";
    }

private:
    Instrument* instr;
};


// PART ONE
int main() {

    // cout << "Define some instruments ------------------------------------\n";
    // Drum drum;
    // Cello cello(673);
    // Cymbal cymbal;
    // Trombone tbone(4);
    // Trumpet trpt(12) ;
    // Violin violin(567) ;
  
    // // use the debugger to look at the mill
    // cout << "Define the MILL --------------------------------------------\n";
    // MILL mill;
  
    // cout << "Put the instruments into the MILL --------------------------\n";
    // mill.receiveInstr(trpt);
    // mill.receiveInstr(violin);
    // mill.receiveInstr(tbone);
    // mill.receiveInstr(drum);
    // mill.receiveInstr(cello);
    // mill.receiveInstr(cymbal);
  
    // cout << "Daily test -------------------------------------------------\n";
    // cout << endl;
    // cout << "dailyTestPlay()" << endl;
    // mill.dailyTestPlay();
    // cout << endl;
  
    // cout << "Define some Musicians---------------------------------------\n";
    // Musician harpo;
    // Musician groucho;
  	
    // cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    // groucho.testPlay();	
    // cout << endl;
    // groucho.acceptInstr(mill.loanOut());
    // cout << endl;
    // groucho.testPlay();
    // cout << endl;
    // cout << "dailyTestPlay()" << endl;
    // mill.dailyTestPlay();
  
    // cout << endl << endl;
  
    // groucho.testPlay();	
    // cout << endl;
    // mill.receiveInstr(*groucho.giveBackInstr());
    // harpo.acceptInstr(mill.loanOut());
    // groucho.acceptInstr(mill.loanOut());
    // cout << endl;
    // groucho.testPlay();
    // cout << endl;
    // harpo.testPlay();
    // cout << endl;
    // cout << "dailyTestPlay()" << endl;
    // mill.dailyTestPlay();
  
    // cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
  
    // // fifth
    // mill.receiveInstr(*groucho.giveBackInstr());
    // cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    // mill.receiveInstr(*harpo.giveBackInstr());

  
    // cout << endl;
    // cout << "dailyTestPlay()" << endl;
    // mill.dailyTestPlay();
    // cout << endl;
  
    // cout << endl;
}
