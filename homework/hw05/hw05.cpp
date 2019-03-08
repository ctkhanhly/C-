#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& warrior){
        os << warrior.name << ": " << warrior.strength;
        return os;
    }
private:
    string name;
    double strength;
    bool isHired;
    bool isDead;
public:
    Warrior(const string& name, double strength): name(name), strength(strength), 
        isHired(false), isDead(false){}
    void setIsHired(bool isHired){
        this->isHired = isHired;
    }
    void setIsDead(bool isDead){
        this->isDead = isDead;
    }
    void setStrength(double strength){
        this-> strength = strength;
    }
    bool getIsHired() const {
        return isHired;
    }
    const string& getName() const {
        return name;
    }
    double getStrength() const {
        return strength;
    }
};

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& noble){
        if(noble.armyOfWarriors.size() == 0){
            os << "NONE";
        }
        else{
            os << noble.name << " has an army of " << noble.armyOfWarriors.size();
            for(Warrior* warrior: noble.armyOfWarriors){
                os << endl;
                os << "\t" << *warrior;
            }
        }
        return os;
    }
private:
    string name;
    double strength;
    bool isDead;
    vector<Warrior*> armyOfWarriors;

    /*
    This method takes in the Noble that wins and the Noble that loses
    and resets the strength of the noble that wins.
    */
    void setStrengthWinner(Noble& winner, Noble& loser){
        double ratio = loser.getStrength() / winner.getStrength();
        for(Warrior* const warrior : winner.armyOfWarriors){
            double curr_strength = warrior->getStrength();
            warrior->setStrength(curr_strength*(1-ratio));
        }
        winner.setStrength(winner.getStrength() * (1 - ratio));
    }

    /*
    This method takes in the Noble that loses and announces 
    that the Noble and all his Warriors are now dead
    */
    void setStrengthLoser(Noble& noble){
        for(Warrior* const warrior : noble.armyOfWarriors){
            warrior->setStrength(0);
            warrior->setIsDead(true);
        }
        noble.setStrength(0);
        noble.setIsDead(true);
    }
public: 
    Noble(const string& name): name(name){}
    void setStrength(double strength){
        this->strength = strength;
    }
    void setIsDead(bool isDead){
        this->isDead = isDead;
    }
    bool getIsDead() const {
        return isDead;
    }
    double getStrength() const {
        return strength;
    }
    const string& getName() const {
        return name;
    }
    /*
    This method returns true if a warrior 
    of the specified name is found in the army
    */
    bool findAWarrior(const string& name){
        for(Warrior* warrior: armyOfWarriors){
            if(name == warrior->getName()){
                return true;
            }
        }
        return false;
    }
    bool hire(Warrior& warrior){

        //If the Noble is dead, he cannot hire anyone
        //Or if the warrior is already hired, 
        //the noble cannot hire him
        if(isDead || warrior.getIsHired()){
            return false;
        }
        else{
            warrior.setIsHired(true);
            armyOfWarriors.push_back(&warrior);
            strength+= warrior.getStrength();
            return true;
        }
    }
    bool fire(Warrior& warrior){
    
        size_t count =  0;
        for(Warrior* theWarrior: armyOfWarriors){
            if(theWarrior->getName() == warrior.getName()){
                count ++;
            }
        }
        if(count == 0){
            return false;
        }

        //If the Noble is dead, he cannot fire anyone
        if(isDead){
            return false;
        }
        else{
            size_t wIndex = armyOfWarriors.size();
            for(size_t i = 0; i < armyOfWarriors.size(); ++i){
                if(armyOfWarriors[i] ==  &warrior){
                    wIndex = i;
                }
            }
            if(wIndex == armyOfWarriors.size()){
                cerr << "You didn't hire this warrior, cannot fire" << endl;
                exit(1);
            }
            for(size_t i = wIndex; i < armyOfWarriors.size(); ++i){
                armyOfWarriors[i] = armyOfWarriors[i+1];
            }
            armyOfWarriors.pop_back();
            strength -= warrior.getStrength();
            warrior.setIsHired(false);
            return true;
        }
    }

/*
This method starts the battle by taking in the Noble this object 
this fighting against, and then change each warrior's strength
according to the following rules:
    If a Noble has less strength then he and all of his Warriors are dead and 
the stronger Noble and each Warrior loses only the amount of strength 
that is proportional to his enemy's total army strength over his total
army strength

    If two warriors have the same strength, they both lose all strength
Then, this method prints out the result of the battle.
*/
    void battle(Noble& noble){

        cout << this->name << " battles " << noble.getName() << endl;
        double enemyStrength = noble.getStrength();
        if(this->isDead && noble.getIsDead()){
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        }
        else if(this->isDead){
            cout << "He's dead, " << noble.getName() << endl;
        }
        else if(noble.getIsDead()){
            cout << "He's dead, " << this->name << endl;
        }
        else if(this->strength < enemyStrength){
            cout << noble.getName() << " defeats " << this->name << endl;
            setStrengthWinner(noble, *this);
            setStrengthLoser(*this);
        }
        else if(this->strength == enemyStrength){
            cout << "Mutual Annihalation: " << this->name << " and "
            << noble.getName() << " die at each other's hands" << endl;
            setStrengthLoser(*this);
            setStrengthLoser(noble);
        }
        else{
            cout << this->name << " defeats " << noble.getName() << endl;
            setStrengthWinner(*this, noble);
            setStrengthLoser(noble);
        }
    }
};

/*
This method performs creates the Warrior 
with the specified name and push the Warrior in 
a vector of all Warrior pointers
*/
void WarriorCommand(const string& name, double strength, vector<Warrior*>& warriors){
    for(Warrior* warrior: warriors){
        if(warrior->getName() == name){
            cerr << "This warrior already exists" << endl;
            exit(1);
        }
    }
    warriors.push_back(new Warrior(name, strength));
}

/*
This method performs creates the Noble 
with the specified name and push the Noble in 
a vector of Noble pointers
*/
void NobleCommand(const string& name, vector<Noble*>& nobles){
    for(Noble* noble: nobles){
        if(noble->getName() == name){
            cerr << "This noble already exists" << endl;
            exit(1);
        }
    }
    nobles.push_back(new Noble(name));
}
/*
This method prints out all the Nobles and Warriors
*/
void StatusCommand(vector<Noble*>& nobles, vector<Warrior*>& warriors){
   
    size_t numOfNoblesInHeap = 0;
    //Print out all the Nobles
    for(Noble* noble: nobles){
        if(noble){
            cout << *noble << endl;
            numOfNoblesInHeap++;
        }
    }

    //If all Nobles are not in the heap, numOfNoblesInHeap = 0
    if(nobles.size() - numOfNoblesInHeap == nobles.size()){
        cout << "NONE" << endl;
    }
    cout << "Unemployed Warriors:" << endl;
    size_t numOfWarriorsInHeap = 0;
    int numOfHiredWarriors = 0;

    //Print out all the unemployed Warriors
    for(Warrior* warrior: warriors){
        //Check if the Warrior is still in the heap
        if(warrior){
            numOfWarriorsInHeap++;
        }
        //
        if(warrior->getIsHired()){
            numOfHiredWarriors ++;
        }
        else{
            cout << *warrior << endl;
        }
    }

    //If all Warriors are not in the heap, 
    //numOfWarriorsInHeap = 0
    
    if(warriors.size() - numOfHiredWarriors == 0 ||
        warriors.size() - numOfWarriorsInHeap == warriors.size()){
        cout << "NONE" << endl;
    }
}
/*
This method looks for the Noble and Warrior with 
the specified name and allow the Noble to hire that
Warrior
*/
void HireCommand(const string& name1, const string& name2,
    vector<Noble*>& nobles, vector<Warrior*>& warriors){

    Noble* theNoble;
    Warrior* theWarrior;

    //Look for the noble with the specified name
    for(Noble* noble: nobles){
        if(name1 == noble->getName()){
            theNoble =  noble;
            break;
        }
    }

    //Check if the Noble exists
    if(!theNoble){
        cerr << "This Noble does not exist" << endl;
        exit(1);
    } 

    //Look for all available workers to 
    //find the worker with the specified name

    for(Warrior* warrior: warriors){
        if(name2 == warrior->getName()){
            theWarrior =  warrior; 
            break;
        }
    }

    //Check if the Warrior exists
    if(!theWarrior){
        cerr << "This Warrior does not exist" << endl;
        exit(1);
    }
    theNoble->hire(*theWarrior);//**** hire(theWarrior*)?
}
/*
This method looks for the Noble and Warrior with 
the specified name and allow the Noble to fire that
Warrior
*/
void FireCommand(const string& name1, const string& name2, 
    vector<Noble*>& nobles, vector<Warrior*>& warriors){

    Noble* theNoble;
    Warrior* theWarrior;
    //Look for the noble with the specified name
    for(Noble* noble: nobles){
        if(name1 == noble->getName()){
            theNoble =  noble;
            break;
        }
    }
    //Check if the Noble exists
    if(!theNoble){
        cerr << "This Noble does not exist" << endl;
        exit(1);
    }
    
    //Check if the Warrior is in the Noble's army
    if(!theNoble->findAWarrior(name2)){
        cerr << "This Warrior is not in" << theNoble->getName()
        << "'s army" << endl;
        exit(1);
    }
    //Look for the warrior with the specified name
    for(Warrior* warrior: warriors){
        if(name2 == warrior->getName()){
            theWarrior =  warrior; 
            break;
        }
    }
    //Fire the warrior
    theNoble->fire(*theWarrior);
    cout << "You don't work for me anymore " << theWarrior->getName() <<
        "! -- " << theNoble->getName() << "." << endl;
}
/*
This method finds the Noble associated the two 
Nobles of specified names and let the first Noble 
battle the second Noble
*/
void BattleCommand(const string& name1, const string& name2, vector<Noble*>& nobles){
    Noble* theNoble1;
    Noble* theNoble2;
    //Look for the noble with the specified name
    for(Noble* noble: nobles){
        if(name1 == noble->getName()){
            theNoble1 =  noble;
            break;
        }
    }
    //Look for the enemy noble with the specified name
    for(Noble* noble: nobles){
        if(name2 == noble->getName()){
            theNoble2 =  noble;
            break;
        }
    }
    //Check if the Noble exists
    if(!theNoble1){
        cerr << "This Noble does not exist" << endl;
        exit(1);
    }
    //Check if the enemy Noble exists
    if(!theNoble2){
        cerr << "The enemy Noble does not exist" << endl;
        exit(1);
    }

    //Start the battle
    theNoble1->battle(*theNoble2);
}

/*
This method clears out all the Nobles and Warriors 
created on the heap
*/
void ClearCommand(vector<Noble*>& nobles, vector<Warrior*>& warriors){
   //Delete each element in the vector of Noble pointers
    for(Noble*& noble: nobles){
        delete noble;
        noble = nullptr;
    }
    //Delete each element in the vector of Warrior pointers
    for(Warrior*& warrior: warriors){
        delete warrior;
        warrior = nullptr;
    }
}


int main(){
    //Read in the input file

    ifstream nobleText("nobleWarriors.txt");//single quote failed here

    //Check if the file was read successfully

    if(!nobleText){
        cerr << "File not found" << endl;
        exit(1);
    }

    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    string command, name;
    double strength;

    //Read in command name and its parameter 
    //until there is no more command

    while(nobleText >> command){
        string name1, name2;
        //can create string name and strength here?
        if(command == "Noble"){
            nobleText >> name;
            NobleCommand(name, nobles);
        }
        else if(command == "Warrior"){
            nobleText >> name;
            nobleText >> strength;
            WarriorCommand(name, strength, warriors);
        }
        else if(command == "Status"){
            cout << "Status" << endl;
            cout << "======" << endl;
            cout << "Nobles:" << endl;
            
            StatusCommand(nobles, warriors);
        }
        else if(command == "Hire"){
            nobleText >> name1;
            nobleText >> name2;
            HireCommand(name1, name2, nobles, warriors);
        }
        else if(command == "Fire"){
            nobleText >> name1;
            nobleText >> name2;
            FireCommand(name1, name2, nobles, warriors);
        }
        else if(command == "Battle"){
            nobleText >> name1;
            nobleText >> name2;
        BattleCommand(name1, name2, nobles);
        }
        else if(command == "Clear"){
            ClearCommand(nobles, warriors);
        }
        else{
            cerr << "Command does not exist" << endl;
            exit(1);
        }
    }

    nobleText.close();

}