#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//82,8,,108,183,189
//82, 90, 111, 188, 198
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
public: 
    Noble(const string& name): name(name){}
    // ~Noble(){

    // }
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
    //cannot change army but can access?
    const vector<Warrior*>& getArmyOfWarriors() const {
        return armyOfWarriors;
    }
    bool hire(Warrior& warrior){
        //************ check on this error
        //Check if the warrior exists

        //check in main

        // if(!warrior){
        //     cerr << "This warrior does not exist" << endl;
        //     exit(1);
        // }
        //Check if this noble exists 
        //******* What does this mean??? 'this' pointer cannot be null in well-defined C++
    //code; pointer may be assumed to always convert to true
        // if(!this){
        //     cerr << "This noble does not exist" << endl;
        //     exit(1);
        // }

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
        //Check if the Noble exists.

        // if(!this){
        //     return false;
        // }

        //Check if there is a warrior in the army 
        //that has the same name as this warrior
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
            size_t wIndex;
            for(size_t i = 0; i < armyOfWarriors.size(); ++i){
                if(armyOfWarriors[i] ==  &warrior){
                    wIndex = i;
                }
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
    This method takes in the Noble that wins and the Noble that loses
    and resets the strength of the noble that wins.
    */
    void setStrengthWinner(Noble& winner, Noble& loser){
        double ratio = loser.getStrength() / winner.getStrength();
        for(Warrior* const warrior : winner.getArmyOfWarriors()){
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
        for(Warrior* const warrior : noble.getArmyOfWarriors()){
            warrior->setStrength(0);
            warrior->setIsDead(true);
        }
        noble.setStrength(0);
        noble.setIsDead(true);
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
        //Check if this noble exists

        // if(!this){
        //     cerr << "This noble does not exist" << endl;
        //     exit(1);
        // }

        //!(this && &noble)
        //Check if the enemy noble exists

    //     reference cannot be bound to dereferenced null pointer
    //   in well-defined C++ code; pointer may be assumed to always convert to true
    //Check in main
        // if(!noble){
        //     cerr << "This enemy noble does not exist" << endl;
        //     exit(1);
        // }

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

void WarriorCommand(const string& name, double strength, vector<Warrior*>& warriors){
    for(Warrior* warrior: warriors){
        if(warrior->getName() == name){
            cerr << "This warrior already exists" << endl;
            exit(1);
        }
    }
    warriors.push_back(new Warrior(name, strength));
}
void NobleCommand(const string& name, vector<Noble*>& nobles){
    for(Noble* noble: nobles){
        if(noble->getName() == name){
            cerr << "This noble already exists" << endl;
            exit(1);
        }
    }
    nobles.push_back(new Noble(name));
}
void StatusCommand(vector<Noble*>& nobles, vector<Warrior*>& warriors){
    //cout << nobles.size() << endl;
    size_t numOfNoblesInHeap = 0;
    for(Noble* noble: nobles){
        if(noble){
            cout << *noble << endl;
            numOfNoblesInHeap++;
        }
    }
    if(nobles.size() - numOfNoblesInHeap == nobles.size()){
        cout << "NONE" << endl;
    }
    cout << "Unemployed Warriors:" << endl;
    size_t numOfWarriorsInHeap = 0;
    int numOfHiredWarriors = 0;
    for(Warrior* warrior: warriors){
        //&& warrior to make sure it's not deleted
        if(warrior){
            numOfWarriorsInHeap++;
        }
        else{
            continue;
        }
        //
        if(warrior->getIsHired()){
            numOfHiredWarriors ++;
        }
        else{
            cout << *warrior << endl;
        }
    }
    if(warriors.size() - numOfHiredWarriors == 0 ||
        warriors.size() - numOfWarriorsInHeap == warriors.size()){
        cout << "NONE" << endl;
    }
}
void HireCommand(const string& name1, const string& name2,
    vector<Noble*>& nobles, vector<Warrior*>& warriors){

    Noble* theNoble;
    Warrior* theWarrior;
    for(Noble* noble: nobles){
        if(name1 == noble->getName()){
            theNoble =  noble;
            break;
        }
    }
    if(!theNoble){
        cerr << "This Noble does not exist" << endl;
        exit(1);
    } 
    for(Warrior* warrior: warriors){
        if(name2 == warrior->getName()){
            theWarrior =  warrior; 
            break;
        }
    }
    if(!theWarrior){
        cerr << "This Warrior does not exist" << endl;
        exit(1);
    }
    theNoble->hire(*theWarrior);//**** hire(theWarrior*)?
}
void FireCommand(const string& name1, const string& name2, 
    vector<Noble*>& nobles, vector<Warrior*>& warriors){

    Noble* theNoble;
    Warrior* theWarrior;
    for(Noble* noble: nobles){
        if(name1 == noble->getName()){
            theNoble =  noble;
            break;
        }
    }
    if(!theNoble){
        cerr << "This Noble does not exist" << endl;
        exit(1);
    }
    for(Warrior* warrior: warriors){
        if(name2 == warrior->getName()){
            theWarrior =  warrior; 
            break;
        }
    }
    if(!theWarrior){
        cerr << "This Warrior does not exist" << endl;
        exit(1);
    }
    theNoble->fire(*theWarrior);//**** hire(theWarrior*)?
    cout << "You don't work for me anymore" << theWarrior->getName() <<
    "! -- " << theNoble->getName() << "." << endl;
}
void BattleCommand(const string& name1, const string& name2, vector<Noble*>& nobles){
    Noble* theNoble1;
    Noble* theNoble2;
    for(Noble* noble: nobles){
        if(name1 == noble->getName()){
            theNoble1 =  noble;
            break;
        }
    }
    for(Noble* noble: nobles){
        if(name2 == noble->getName()){
            theNoble2 =  noble;
            break;
        }
    }
    if(!theNoble1){
        cerr << "This Noble does not exist" << endl;
        exit(1);
    }
    if(!theNoble2){
        cerr << "The enemy Noble does not exist" << endl;
        exit(1);
    }
    theNoble1->battle(*theNoble2);
}

void ClearCommand(vector<Noble*>& nobles, vector<Warrior*>& warriors){
     //i need the reference in both cases
    //order doesnt matter
    for(Warrior*& warrior: warriors){
        delete warrior;
        warrior = nullptr;
    }
    for(Noble*& noble: nobles){
        delete noble;
        noble = nullptr;
    }
}


int main(){
    ifstream nobleText("nobleWarriors.txt");//single quote failed here

    if(!nobleText){
        cerr << "File not found" << endl;
        exit(1);
    }
// Each time a warrior or a noble is defined, we will create it on the heap.
// We will keep track of the nobles in a vector of pointers to nobles.
// We will keep track of all warriors using a vector of pointers to warriors.


// Noble. Create a Noble on the heap.
// Warrior. Create a Warrior on the heap.
// Hire. Call the Noble's hire method.
// Fire. Call the Noble's fire method.
// Battle. Call the Noble's battle method.
// Status. The status command shows the nobles, together with their armies, 
// as we did previously. In addition, it will show separately the 
// warriors who do not currentle have a employer
// Clear. Clear out all the nobles and warriors that were created.



// Our application is going to rely on each Noble having a unique name 
//and each Warrior having a unique name. Otherwise, how would we be sure who we 
// were hiring (or firing). Note that this is not a requirement of the Noble and 
// Warrior classes themselves, just of this particular use of them, i.e. our application.


//so dont have to check for it in the class itself?


// Now we would like you to take some responsibility for checking the input. 
// First, we still guarantee that the format of the file will be correct. 
// That means that the Warrior command will always have a name and a strength.
//  The Battle command will always have two names. The Status command will not have any other information on it than just the word Status.

// However, you will need to detect and report any issues indicating inconsistencies, such as:

// Noble command: if a Noble with a given name already exists.
// Warrior command:if a Warrior with a given name already exists.
// Hire command: If a Noble tries to hire a Warrior and either of them do not exist.
// Fire command: If a Noble tries to fire a Warrior and either the Noble does not exist or does not have the Warrior by that name in this army.
// Battle command: If a Noble initiates a battle with another Noble, but one or the other does not exist.

    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    string command, name;
    double strength;
    while(nobleText >> command){
        string name1, name2;
        //can create string name and strength here?
        if(command == "Noble"){
            nobleText >> name;
            NobleCommand(name, nobles);
            // for(Noble* noble: nobles){
            //     if(noble->getName() == name){
            //         cerr << "This noble already exists" << endl;
            //         exit(1);
            //     }
            // }
            // nobles.push_back(new Noble(name));
        }
        else if(command == "Warrior"){
            nobleText >> name;
            nobleText >> strength;
            WarriorCommand(name, strength, warriors);
            // for(Warrior* warrior: warriors){
            //     if(warrior->getName() == name){
            //         cerr << "This warrior already exists" << endl;
            //         exit(1);
            //     }
            // }
            // warriors.push_back(new Warrior(name, strength));
        }
        else if(command == "Status"){
            cout << "Status" << endl;
            cout << "======" << endl;
            cout << "Nobles:" << endl;
            
            StatusCommand(nobles, warriors);
            // for(Noble* noble: nobles){
            //     cout << *noble << endl;
            // }
            // cout << "Unemployed Warriors:" << endl;
            // int numOfHiredWarriors = 0;
            // for(Warrior* warrior: warriors){
            //     if(warrior->getIsHired()){
            //         numOfHiredWarriors ++;
            //     }
            //     else{
            //         cout << *warrior << endl;
            //     }
            // }
            // if(warriors.size() - numOfHiredWarriors == 0){
            //     cout << "NONE" << endl;
            // }
            
        }
        else if(command == "Hire"){
            nobleText >> name1;
            nobleText >> name2;
            HireCommand(name1, name2, nobles, warriors);
            // Noble* theNoble;
            // Warrior* theWarrior;
            // for(Noble* noble: nobles){
            //     if(name1 == noble->getName()){
            //         theNoble =  noble;
            //         break;
            //     }
            // }
            // if(!theNoble){
            //     cerr << "This Noble does not exist" << endl;
            //     exit(1);
            // } 
            // for(Warrior* warrior: warriors){
            //     if(name2 == warrior->getName()){
            //         theWarrior =  warrior; 
            //         break;
            //     }
            // }
            // if(!theWarrior){
            //     cerr << "This Warrior does not exist" << endl;
            //     exit(1);
            // }
            // theNoble->hire(*theWarrior);//**** hire(theWarrior*)?
        }
        else if(command == "Fire"){
            nobleText >> name1;
            nobleText >> name2;
            FireCommand(name1, name2, nobles, warriors);
            // Noble* theNoble;
            // Warrior* theWarrior;
            // for(Noble* noble: nobles){
            //     if(name1 == noble->getName()){
            //         theNoble =  noble;
            //         break;
            //     }
            // }
            // if(!theNoble){
            //     cerr << "This Noble does not exist" << endl;
            //     exit(1);
            // }
            // for(Warrior* warrior: warriors){
            //     if(name2 == warrior->getName()){
            //         theWarrior =  warrior; 
            //         break;
            //     }
            // }
            // if(!theWarrior){
            //     cerr << "This Warrior does not exist" << endl;
            //     exit(1);
            // }
            // theNoble->fire(*theWarrior);//**** hire(theWarrior*)?
            // cout << "You don't work for me anymore" << theWarrior->getName() <<
            // "! -- " << theNoble->getName() << "." << endl;
        }
        else if(command == "Battle"){
            nobleText >> name1;
            nobleText >> name2;
        BattleCommand(name1, name2, nobles);
        //     Noble* theNoble1;
        //     Noble* theNoble2;
        //     for(Noble* noble: nobles){
        //         if(name1 == noble->getName()){
        //             theNoble1 =  noble;
        //             break;
        //         }
        //     }
        //     for(Noble* noble: nobles){
        //         if(name2 == noble->getName()){
        //             theNoble2 =  noble;
        //             break;
        //         }
        //     }
        //     if(!theNoble1){
        //         cerr << "This Noble does not exist" << endl;
        //         exit(1);
        //     }
        //     if(!theNoble2){
        //         cerr << "The enemy Noble does not exist" << endl;
        //         exit(1);
        //     }
        //     theNoble1->battle(*theNoble2);
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