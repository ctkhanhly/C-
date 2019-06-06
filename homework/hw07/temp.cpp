#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Noble;
class Lord;

class Protector{
    //has to defend Lord
    friend ostream& operator<<(ostream& os, const Protector& protector);
private:
    string name;
    double strength;
    bool isHired;
    bool isDead;
    Lord* lord;
public:
    Protector(const string& name, double strength): name(name), strength(strength), 
        isHired(false), isDead(false), lord(nullptr){}
    void setIsHired(bool isHired){
        this->isHired = isHired;
    }
    void setIsDead(bool isDead){
        this->isDead = isDead;
    }
    bool getIsDead() const {
        return isDead;
    }
    //set at birth - but will change when losing battle/ winning
    void setStrength(double strength){
        this->strength = strength;
    }
    //all of the Protectors can quit
    void runaway();
    void setLord(Lord* lord){
        this->lord = lord;
    }
    const string& getLordName() const;
    bool getIsHired() const{
        return isHired;
    }
    const string& getName() const{
        return name;
    }
    double getStrength() const{
        return strength;
    }
    virtual void wayOfDefending() const = 0;//'wayOfDefending' is not virtual and cannot be declared pure

};
//A Protector who is dead, however, cannot fight and so will not have anything to say, 
//even if his Lord does go into battle again.
//***** test this!!!

//sadly this just doesnt work
// void Protector::wayOfDefending()const{
//     if(isDead){
//         return;
//     }
// }


class Noble{
    friend ostream& operator<<(ostream& os, const Noble& noble){ return os;}
private:
    string name;
    double strength; // can child class override this field?
    bool isDead;
public: 
    Noble(const string& name): name(name), strength(0), isDead(false){}
    Noble(const string& name, int strength): name(name), strength(strength), isDead(false){}///*********
     //strength will not be in here because PersonWithStrength is not, neither is Lord.
     //each need getStrength for the battle though
    //has to be able to set for  when it loses
    void setStrength(double strength){
        this->strength = strength;
    }
    void setIsDead(bool isDead){
        this->isDead = isDead;
    }
    bool getIsDead() const{
        return isDead;
    }
    double getStrength() const{
        return strength;
    }
    const string& getName() const{
        return name;
    }
    virtual void wayOfDefending() const = 0;
    //However curiously, as has been seen before, Nobles can declare battle even though they are dead.
    //A Protector who is dead, however, cannot fight and so will not have anything to say, 
    //even if his Lord does go into battle again.

    //When doing battle, one with strength to fight will yell "UGH!!!"
    void battle(Noble& noble){
        cout << this->name << " battles " << noble.getName() << endl;
        double enemyStrength = noble.getStrength();//getStrength public, yes

        noble.wayOfDefending();
        wayOfDefending();
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
            noble.setStrengthWinner(*this); //again, I can use pointer here
            this->setStrengthLoser();
        }
        else if(this->strength == enemyStrength){
            cout << "Mutual Annihalation: " << this->name << " and "
            << noble.getName() << " die at each other's hands" << endl;
            this->setStrengthLoser();
            noble.setStrengthLoser();
        }
        else{
            cout << this->name << " defeats " << noble.getName() << endl;
            //this wins
            this->setStrengthWinner(noble);
            noble.setStrengthLoser();
        }
    }  
    virtual void setStrengthWinner(Noble& loser) = 0;
    virtual void setStrengthLoser() = 0;
};
void Noble::setStrengthLoser(){
    cout << endl<< name <<  " Before battle strength " << strength << endl;
    strength = 0;
    isDead = true;
    cout << "After battle strength " << strength << endl << endl;
};
// void Noble::setStrengthWinner(Noble& loser){
//     double ratio = 
//     strength = strength * (1 - ratio));
// }

class PersonWithStrengthToFight : public Noble{
// private:
//     int strength;//is this strength different than Noble's strength?
public: 
    PersonWithStrengthToFight(const string& name, int strength): Noble(name,strength){}
    void setStrengthLoser(){
        Noble::setStrengthLoser();
    }
    // void setStrengthWinner(Noble& winner, Noble& loser){
    //     Noble::setStrengthWinner(winner,loser); //
    // }//error linking here
    void wayOfDefending() const{
        cout << Noble::getName() << " says: UGH!!!" << endl;
    }
    void setStrengthWinner(Noble& loser){ 
        cout << endl<< Noble::getName() <<  " Before battle strength " << Noble::getStrength() << endl;
        double ratio = loser.getStrength() / Noble::getStrength();
        Noble::setStrength(Noble::getStrength() * (1 - ratio));
        cout << "After battle strength " << Noble::getStrength() << endl << endl;
    }
};

class Lord : public Noble{
private:
    vector<Protector*> armyOfProtectors;
    size_t lookForProtector(Protector& protector) const{
        size_t pIndex = armyOfProtectors.size();
        for(size_t i = 0; i < armyOfProtectors.size(); ++i){
            if(armyOfProtectors[i] ==  &protector){
                pIndex = i;
                break;
            }
        }
        if(pIndex == armyOfProtectors.size()){
            cerr << "You didn't hire this warrior, cannot fire" << endl;
            //exit(1);
        }
        return pIndex;
    }
     
public:
    Lord(const string& name): Noble(name){}

    //I don't think I need this at all!!!!
    // bool findAProtector(const string& name) const{
    //     for(Protector* protector: armyOfProtectors){
    //         if(name == protector->getName()){
    //             return true;
    //         }
    //     }
    //     return false;
    // }// I  use this publicly

    bool hires(Protector& protector){
        //If the Noble is dead, he cannot hire anyone
        //Or if the warrior is already hired, 
        //the noble cannot hire him

        //Lords who are dead are in no position to hire anyone. 
        //Any attempt by a dead Lord to hire someone will simple fail and the Protector will remain unhired.
        //Similarly dead Protectors cannot be hired. Any attempt to hire the dead simple fails.
        if(Noble::getIsDead() || protector.getIsHired() || protector.getIsDead()){
            return false;
        }
        else{
            protector.setIsHired(true);
            protector.setLord(this);
            armyOfProtectors.push_back(&protector);
            Noble::setStrength(Noble::getStrength()+ protector.getStrength());
            return true;
        }
    }
    bool fires(Protector& protector){
       
        // size_t count =  0;
        // for(Protector* theProtector: armyOfProtectors){
        //     if(theProtector->getName() == protector.getName()){
        //         count ++;
        //     }
        // }
        // if(count == 0){
        //     return false;
        // }

        //If the Noble is dead, he cannot fire anyone
        if(Noble::getIsDead()){
            return false;
        }
        else{
            //look for warrior 1
            //size_t pIndex = lookForProtector(protector);
            if(!deleteProtector(protector)){
                cerr << "Couldn't remove the Warrior" << endl;
                return false;
            }
            return true;
        }
    }
    //moved deleteProtector to private
    ///Protector needs access to deleteProtector()!!!!! 
    //strength field belongs to Noble

    //When a Protector is fired, the others in the army close the gap between them, 
    //so that the Protectors maintain the same order they had before in the army. 
    //(Wouldn't want warriors having to run all about just because one of their comrades gets fired.)
    bool deleteProtector(Protector& protector){
        size_t pIndex = lookForProtector(protector);
        if(pIndex == armyOfProtectors.size()){
            return false;
        }
        for(size_t i = pIndex; i < armyOfProtectors.size(); ++i){
            armyOfProtectors[i] = armyOfProtectors[i+1];
        }
        armyOfProtectors.pop_back();
        Noble::setStrength(Noble::getStrength() - protector.getStrength());
        protector.setIsHired(false);
        protector.setLord(nullptr);
        return true;
    }

    void setStrengthLoser(){
        //******
        for(Protector* const protector : armyOfProtectors){
            //protector
            protector->setStrength(0);
            protector->setIsDead(true);
        }
        Noble::setStrengthLoser();
    }   
    //if you call this, you won 
    void setStrengthWinner(Noble& loser){
        cout << endl<< Noble::getName() <<  " Before battle strength " << Noble::getStrength() << endl;

        //this is the winner
        double ratio = loser.getStrength() / Noble::getStrength();
        //has to know this ratio before setting strength of either Noble or Protector
        //protector needs this access to ratio too-> cannot change strength of Noble at Noble class

        for(Protector* const protector : armyOfProtectors){
            double curr_strength = protector->getStrength();
            protector->setStrength(curr_strength*(1-ratio));
        }
        Noble::setStrength(Noble::getStrength() * (1 - ratio));
        cout << "After battle strength " << Noble::getStrength() << endl << endl;
    }
    void wayOfDefending() const{
        for(Protector* protector: armyOfProtectors){
            protector->wayOfDefending();
        }
    }
};

class Wizard : public Protector{
public:
    Wizard(const string& name, int strength): Protector(name, strength){}
    void wayOfDefending() const{
        //I don't inherit this part anymore right?
        //Protector::wayOfDefending();
        if(Protector::getIsDead()){
            return;
        }
        cout << "POOF! " << Protector::getName() << " says: Take that in the name of my lord, ";
        cout << Protector::getLordName() << endl;
    }
};

class Warrior : public Protector{
public:
    Warrior(const string& name, int strength): Protector(name, strength){}
    //does Warrior need to explicitly say getName here?
};

class Archer : public Warrior{
public: 
    Archer(const string& name, int strength): Warrior(name, strength){}
    void wayOfDefending() const{
        //Protector::wayOfDefending();
        if(Warrior::getIsDead()){
            return;
        }
        cout << "TWANG! " << Warrior::getName() << " says: Take that in the name of my lord, " ;
        cout << Warrior::getLordName() << endl;
    }
};

class Swordsman : public Warrior{
public: 
    Swordsman(const string& name, int strength): Warrior(name, strength){}
    void wayOfDefending() const{
        //it just doesnt work?????
        //Protector::wayOfDefending();
        if(Warrior::getIsDead()){
            return;
        }
        cout << "TWANG! " << Warrior::getName() << " says: Take that in the name of my lord, ";
        cout << Warrior::getLordName() << endl;
    }
};

void Protector::runaway(){
    //Tarzan flees in terror, abandoning his lord, King Arthur
    cout << name << " flees in terror, abandoning his lord, ";
    cout << lord->getName() << endl;
    lord->deleteProtector(*this); //because I deleted warrior here, set noble = null already
    //has to print before this line
}
const string& Protector::getLordName() const{
    return lord->getName();
}
int main(){
    // PersonWithStrengthToFight alex("Alex", 10);
    // //alex.Noble::setStrength(15);
    // Lord hehe("Hehe");
    // Swordsman lila("Lila", 5);
    // hehe.hire(lila);
    // hehe.battle(alex);
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    joe.battle(randy);	
    joe.battle(sam);	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    janet.battle(barclay);	
    janet.hires(samantha);	
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);	
    sam.battle(barclay);	
    joe.battle(barclay);

}
