
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Instrument;
class MILL{
    //stores,tests, lends
private:
    vector<Instrument*> instruments;
    size_t availableInsSpot() const;
    size_t availableInsToLoan() const;
public:
    //void borrows()
    void receiveInstr(Instrument& i);
    void dailyTestPlay() const;
    Instrument* loanOut();
};
// Musical Instrument Lending Library that stores them, lends them and tests them out.
class Instrument{
private:
    MILL  mill;
public:
    virtual void makeSound()const = 0;
    virtual void play() const = 0;
};
void Instrument::makeSound() const {
    cout << "To make a sound... ";
};

//trumpets and trombones
class BrassInstrument: public Instrument{
private: 
    int size;
public:
    BrassInstrument(int size): size(size){}
    void makeSound() const{
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << size;
    }
    //void play() const {}//dont call parent's play!!!!!!!! ---> abstract
};

// violins and cellos
class StringInstrument: public Instrument{
//String instruments in this world have only one string and it has a pitch (an unsigned) w
private:
    unsigned pitch;
public:
    StringInstrument(unsigned pitch): pitch(pitch){}
    //To make a sound... bow a string with pitch 567
    void makeSound() const{
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch;
    }
    //void play() const {}
};
class PercussionInstrument: public Instrument{
private:
//no fields
public:
    void makeSound() const{
        Instrument::makeSound();
        cout << "hit me";
    }
    //void play() const {}
};

class WindInstrument: public Instrument{//woodwind family
private:
//no fields
public:
    void makeSound() const{
        Instrument::makeSound();
        cout << "blow me in a chill way";
    }
    //void play() const {}//they don't have to have play
};

class Trumpet: public BrassInstrument{
private:
    int size;
public:
    Trumpet(int size): BrassInstrument(size){}
    // void makeSound() const{
    //     BrassInstrument::makeSound();
    // }
    void play() const {
        cout << "Toot";
    }
};

class Trombone: public BrassInstrument{
private:
    int size;
public:
    Trombone(int size): BrassInstrument(size){}
    // void makeSound() const{
    //     //when I didnt have this, error:cannot initialize object parameter of type
    //   //'const Instrument' with an expression of type 'const BrassInstrument'
    //     BrassInstrument::makeSound();
    // }
    void play() const {
        cout << "Blat";
    }
};
class Flugelhorn: public BrassInstrument{ 
public:
    void play() const {}
};
class Bugle: public BrassInstrument{ 
public:
    void play() const {}
};
class FrenchHorn: public BrassInstrument{ 
public:
    void play() const {}
};
class Euphonium: public BrassInstrument{ 
public:
    void play() const {}
};
class Tuba: public BrassInstrument{ void play() const {}};
class CordeChasses: public BrassInstrument{ 
public:
    void play() const {}
};
class Sackbutt: public BrassInstrument{ 
public:
    void play() const {}
};
class Zink: public BrassInstrument{ 
public:
    void play() const {}
};
class Sousaphone: public BrassInstrument{ 
    public:
        void play() const {}
};

//Wind instruments in the future
class Flute: public WindInstrument{
public:
    void play() const {}
};

class Saxophone: public WindInstrument{
public:
    void play() const {}
};

class Clarinet: public WindInstrument{
public:
    void play() const {}
};

class Oboe: public WindInstrument{
public:
    void play() const {}
};

class Bassoon: public WindInstrument{
public:
    void play() const {}
};

class Shawm: public WindInstrument{
public:
    void play() const {}
};

class CorAnglais: public WindInstrument{
public:
    void play() const {}
};

class Krummhorn: public WindInstrument{
public:
    void play() const {}
};

class Rackett: public WindInstrument{
public:
    void play() const {}
};

//call makeSound or else it becomes abstract
class Violin: public StringInstrument{
private:
    unsigned pitch;
public:
    Violin(unsigned pitch): StringInstrument(pitch){}
    // void makeSound() const{
    //     StringInstrument::makeSound();
    // }
    void play() const {
        cout << "Screech";
    }
};

class Cello: public StringInstrument{
private:
    unsigned pitch;
public:
    Cello(unsigned pitch): StringInstrument(pitch){}
    // void makeSound() const{
    //     StringInstrument::makeSound();
    // }
    void play() const {
        cout << "Squawk";
    }
};

class Viola: public StringInstrument{ 
public:
    void play() const {}
};

class Guitar: public StringInstrument{ 
public:
    void play() const {}
};

class Lute: public StringInstrument{ 
public:
    void play() const {}
};

class Banjo: public StringInstrument{ 
public:
    void play() const {}
};

class Ukelele: public StringInstrument{ 
public:
    void play() const {}
};

class Balalaika: public StringInstrument{ 
public:
    void play() const {}
};

class Oud: public StringInstrument{ 
public:
    void play() const {}
};

class Sitar: public StringInstrument{ 
public:
    void play() const {}
};

class Zither: public StringInstrument{ 
public:
    void play() const {}
};

class Kora: public StringInstrument{ 
public:
    void play() const {}
};

// drums and cymbals 
//So there will really be nothing except the constructors for drums and cymbals in part one.
//Default constructor
class Drum: public PercussionInstrument{
//
public:
    // void makeSound() const{
    //     PercussionInstrument::makeSound();
    // }
    void play() const {
        cout << "Boom";
    }
};

class Cymbal: public PercussionInstrument{
public: 
    // void makeSound() const{
    //     PercussionInstrument::makeSound();
    // }
    void play() const {
        cout << "Crash";
    }
};

class Tambour: public PercussionInstrument{ 
public:
    void play() const {}
};

class Tambourine: public PercussionInstrument{ 
public:
    void play() const {}
};

class GrandeCasse: public PercussionInstrument{ 
public:
    void play() const {}
};

class Triangle: public PercussionInstrument{ 
public:
    void play() const {}
};

class Bongo: public PercussionInstrument{ 
public:
    void play() const {}
};

class Conga: public PercussionInstrument{ 
public:
    void play() const {}
};

class Timbale: public PercussionInstrument{ 
public:
    void play() const {}
};

class Castanets: public PercussionInstrument{ 
public:
    void play() const {}
};

class Maracas: public PercussionInstrument{ 
public:
    void play() const {}
};

class Guiro: public PercussionInstrument{ 
public:
    void play() const {}
};

class Xylophone: public PercussionInstrument{ 
public:
    void play() const {}
};

class OrchestraBells: public PercussionInstrument{ 
public:
    void play() const {}
};

class Chimes: public PercussionInstrument{ 
public:
    void play() const {}
};

class Marimba: public PercussionInstrument{ 
public:
    void play() const {}
};

class Vibraphone: public PercussionInstrument{ 
public:
    void play() const {}
};

class Crotales: public PercussionInstrument{ 
public:
    void play() const {}
};

class Amgloken: public PercussionInstrument{ 
public:
    void play() const {}
};


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
    void play() const{
        if(instr){
            instr->play();
        }
    }

private:
    Instrument* instr;
};
class Orch{
private:
    vector<Musician*> musicians;
    //Scenario* s;
public:
    void addPlayer(Musician& m){
        //s->join(m, *this);
        musicians.push_back(&m);
    }
    void play() const{
        for(Musician* m: musicians){
            m->play();
            //cout << endl;//remember!!!!!!
        }
        cout << endl;
    }

};
// class Scenario{
// private:
//     MILL mill;
// public:
//     Scenario(MILL mill): mill(mill){}
//     void join(Musician& m, Orchestra& o){

//     }
// };

void MILL::receiveInstr(Instrument& i){// cannot be const here if want to be added into instruments
    i.makeSound();
    cout << endl;
    size_t iIndex = availableInsSpot();
    if(iIndex == instruments.size()){
        instruments.push_back(&i);
    }
    else{
        instruments[iIndex] = &i;
    }
    
}

void MILL::dailyTestPlay() const {
    for(Instrument* ins: instruments){
        if(ins){
            ins->makeSound();
            cout << endl;
        }
        
    }
}
Instrument* MILL::loanOut() {
    Instrument* ins = nullptr;
    size_t iIndex = availableInsToLoan();
    if(iIndex == instruments.size()){
        return ins;
    }
    else{
        ins = instruments[iIndex];
        // cannot assign to return value because function 'operator[]' returns a const value
        //when i make loanOut a const method
        instruments[iIndex] = nullptr;
        return ins;
    }
}

size_t MILL::availableInsSpot() const{
    size_t iIndex = instruments.size();
    if(instruments.size() == 0){
        iIndex = 0;
    }
    else{  
        for(size_t i = 0; i< instruments.size(); i++){
            if(instruments[i] == nullptr){
                iIndex = i;
                return iIndex;
            }
        }
    }
    // if(iIndex == instruments.size()){
    //     instruments.push_back(nullptr);///what is wrong with this?
    // }
    return iIndex;
    
}
size_t MILL::availableInsToLoan() const {
    size_t iIndex = instruments.size();
    for(size_t i = 0; i< instruments.size(); i++){
        if(instruments[i] != nullptr){
            iIndex = i;
            return iIndex;
        }
    }
    return iIndex;
}
// PART ONE
int main() {
    cout << "PART ONE----------------------------------------------------\n";
    cout << "Define some instruments ------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL --------------------------------------------\n";
    MILL mill;
  
    cout << "Put the instruments into the MILL --------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
  
    cout << "Daily test -------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians---------------------------------------\n";
    Musician harpo;
    Musician groucho;
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << endl << endl;
  
    groucho.testPlay();	
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());//1st
    groucho.acceptInstr(mill.loanOut());//2nd
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
  
    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());

  
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << endl;
    cout << endl;
   


//PART TWO
    cout << "PART TWO --------------------------------------------------\n";
    // The initialization phase

    // Drum drum;
    // Cello cello(673);
    // Cymbal cymbal;
    // Trombone tbone(4);
    // Trumpet trpt(12);
    // Violin violin(567);

    // MILL mill;
    // mill.receiveInstr(trpt);
    // mill.receiveInstr(violin);
    // mill.receiveInstr(tbone);
    // mill.receiveInstr(drum);
    // mill.receiveInstr(cello);
    // mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
}
