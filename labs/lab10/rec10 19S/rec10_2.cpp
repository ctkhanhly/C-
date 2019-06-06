
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Instrument;
class MILL{
    //stores,tests, lends
private:
    vector<Instrument*> instruments;
public:
    void receiveInstr(Instrument& i);
    size_t availableInsSpot() const;
    void dailyTestPlay() const;
    size_t availableInsToLoan() const;
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

class Trumpet: public BrassInstrument{
private:
    int size;
public:
    Trumpet(int size): BrassInstrument(size){}
    //dont need makeSound here b/c parent already override -> not abstract


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
    //     //Instrument::makeSound();
    //     BrassInstrument::makeSound();
    // }
    void play() const {
        cout << "Blat";
    }
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
        // else{
        //     cout << "\n";
        // }
        
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
    //     instruments.push_back(nullptr);///what is wrong with this? because this is a const method
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
// PART TWO
int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

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

} // main

