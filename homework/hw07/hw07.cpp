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
    Protector(const string& name, double strength);
    void setIsHired(bool isHired);
    void setIsDead(bool isDead){
        this->isDead = isDead;
    }
    bool getIsDead() const;
    void setStrength(double strength);
    void runaway();
    void setLord(Lord* lord);
    const string& getLordName() const;
    bool getIsHired() const;
    const string& getName() const;
    double getStrength() const;
    virtual void wayOfDefending() const = 0;//'wayOfDefending' is not virtual and cannot be declared pure

};

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& noble){ return os;}
private:
    string name;
    double strength;
    bool isDead;
public: 
    Noble(const string& name): name(name), strength(0), isDead(false){}
    Noble(const string& name, int strength): name(name), strength(strength), isDead(false){}
    void setStrength(double strength);
    void setIsDead(bool isDead);
    bool getIsDead() const;
    double getStrength() const;
    const string& getName() const;
    void battle(Noble& noble);
    virtual void wayOfDefending() const = 0;
    virtual void setStrengthWinner(Noble& loser) = 0;
    virtual void setStrengthLoser() = 0;
};

class PersonWithStrengthToFight : public Noble{
// private:
//     int strength;//is this strength different than Noble's strength?
public: 
    PersonWithStrengthToFight(const string& name, int strength);
    void setStrengthLoser();
    void wayOfDefending() const;
    void setStrengthWinner(Noble& loser);
};

class Lord : public Noble{
private:
    vector<Protector*> armyOfProtectors;
    size_t lookForProtector(Protector& protector) const;   
public:
    Lord(const string& name);
    bool hires(Protector& protector);
    bool fires(Protector& protector);
    bool deleteProtector(Protector& protector);

    void setStrengthLoser();
    void setStrengthWinner(Noble& loser);
    void wayOfDefending() const;
};

class Wizard : public Protector{
public:
    Wizard(const string& name, int strength);
    void wayOfDefending() const;
};

class Warrior : public Protector{
public:
    Warrior(const string& name, int strength);
};

class Archer : public Warrior{
public: 
    Archer(const string& name, int strength);
    void wayOfDefending() const;
};

class Swordsman : public Warrior{
public: 
    Swordsman(const string& name, int strength);
    void wayOfDefending() const;
};

//PROTECTOR

Protector::Protector(const string& name, double strength): name(name), strength(strength), 
    isHired(false), isDead(false), lord(nullptr){}
void Protector::setIsHired(bool isHired){
    this->isHired = isHired;
}
bool Protector::getIsDead() const {
    return isDead;
}
void Protector::setStrength(double strength){
    this->strength = strength;
}

void Protector::runaway(){
    cout << name << " flees in terror, abandoning his lord, ";
    cout << lord->getName() << endl;
    lord->deleteProtector(*this);
}
void Protector::setLord(Lord* lord){
    this->lord = lord;
}
const string& Protector::getLordName() const{
    return lord->getName();
}
bool Protector::getIsHired() const{
    return isHired;
}
const string& Protector::getName() const{
    return name;
}
double Protector::getStrength() const{
    return strength;
}

//NOBLE

void Noble::setStrengthLoser(){
    strength = 0;
    isDead = true;
};
void Noble::setStrength(double strength){
    this->strength = strength;
}
void Noble::setIsDead(bool isDead){
    this->isDead = isDead;
}
bool Noble::getIsDead() const{
    return isDead;
}
double Noble::getStrength() const{
    return strength;
}
const string& Noble::getName() const{
    return name;
}
void Noble::battle(Noble& noble){
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

//PersonWithStrengthToFight

PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, int strength): Noble(name,strength){}
void PersonWithStrengthToFight::setStrengthLoser(){
    Noble::setStrengthLoser();
}
void PersonWithStrengthToFight::wayOfDefending() const{
    cout << Noble::getName() << " says: UGH!!!" << endl;
}
void PersonWithStrengthToFight::setStrengthWinner(Noble& loser){ 
    double ratio = loser.getStrength() / Noble::getStrength();
    Noble::setStrength(Noble::getStrength() * (1 - ratio));
}

//LORD

size_t Lord::lookForProtector(Protector& protector) const{
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

Lord::Lord(const string& name): Noble(name){}
bool Lord::hires(Protector& protector){
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
bool Lord::fires(Protector& protector){
    if(Noble::getIsDead()){
        return false;
    }
    else{
        if(!deleteProtector(protector)){
            cerr << "Couldn't remove the Warrior" << endl;
            return false;
        }
        return true;
    }
}
bool Lord::deleteProtector(Protector& protector){
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

void Lord::setStrengthLoser(){
    for(Protector* const protector : armyOfProtectors){
        protector->setStrength(0);
        protector->setIsDead(true);
    }
    //just doesnt have to call this, doesnt have strength
    Noble::setStrengthLoser();
} 
void Lord::setStrengthWinner(Noble& loser){
    double ratio = loser.getStrength() / Noble::getStrength();

    for(Protector* const protector : armyOfProtectors){
        double curr_strength = protector->getStrength();
        protector->setStrength(curr_strength*(1-ratio));
    }
    Noble::setStrength(Noble::getStrength() * (1 - ratio));
}
void Lord::wayOfDefending() const{
    for(Protector* protector: armyOfProtectors){
        protector->wayOfDefending();
    }
}

//WIZZARD

Wizard::Wizard(const string& name, int strength): Protector(name, strength){}
void Wizard::wayOfDefending() const{
    if(Protector::getIsDead()){
        return;
    }
    cout << "POOF! " << endl;
}

//WARRIOR

Warrior::Warrior(const string& name, int strength): Protector(name, strength){}

//ARCHER

Archer::Archer(const string& name, int strength): Warrior(name, strength){}
void Archer::wayOfDefending() const{
    if(Warrior::getIsDead()){
        return;
    }
    cout << "TWANG! " << Warrior::getName() << " says: Take that in the name of my lord, " ;
    cout << Warrior::getLordName() << endl;
}

//SWORDSMAN

Swordsman::Swordsman(const string& name, int strength): Warrior(name, strength){}
void Swordsman::wayOfDefending() const{
    if(Warrior::getIsDead()){
        return;
    }
    cout << "CLANG! " << Warrior::getName() << " says: Take that in the name of my lord, ";
    cout << Warrior::getLordName() << endl;
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
