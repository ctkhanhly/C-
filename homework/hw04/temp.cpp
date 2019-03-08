/*
Name: Ly Cao
DLEC
Game of Medieval Times with Nobles and Warriors
*/

#include <iostream>
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
    size_t strength;
    bool isHired;
public:
    //why I couldnt do this->name(name)?
    Warrior(const string& name, size_t strength): name(name), strength(strength)
            , isHired(false){
        // isHired = false;
    }
    void setStrength(size_t strength){
        this->strength = strength;
    }
    void setIsHired(bool isHired){
        this->isHired = isHired;
    }
    size_t getStrength() const{
        return strength;
    }
    const string& getName() const{
        return name;
    }
    //should i do const ref for boolean, char?
    bool getIsHired() const {
        return isHired;
    }
};
    
class Noble{
private:
    string name;
    size_t strength;
    bool isDead;
    vector<Warrior*> armyOfwarriors;

public:
    Noble(const string& name): name(name), isDead(false), strength(0){
        // isDead = false;
        // strength = 0;
    };
    void setIsDead(bool isDead){
        this->isDead = isDead;
    }
    void setStrength(size_t strength){
        this->strength = strength;
    }
    size_t getStrength() const{
        return strength;
    }
    //this is  constant!!!!!!! the Warrior* is constant, cannot make ref to this pointer, cannot change these pointers
    //that's why when do for(Warrior*& warrior: armyOfwarrior) in display and battle has error

    const vector<Warrior*>& getArmyOfwarriors() const{
        return armyOfwarriors;
    }
    const string& getName() const {
        return name;
    }
    bool getIsDead() const {
        return isDead;
    }
    // bool isDead(){
    //     //do i need const ref for pointers?
    //     for(const Warrior*&: armyOfwarriors){

    //     }
    // }
    bool hire(Warrior& warrior){
        if(warrior.getIsHired() | this->isDead){
            return false;
        }
        else{
            armyOfwarriors.push_back(&warrior);
            strength += warrior.getStrength();
            warrior.setIsHired(true);
            return true;
        }
    }
    bool fire(Warrior& warrior){
        //Tarzan, you're fired! -- King Arthur
        cout << warrior.getName() << ", you're fired! -- "
        << this->name << endl;

        if(this->isDead){
            return false;
        }
        else{
            size_t wIndex;
            for(size_t i = 0; i < armyOfwarriors.size(); ++i){
                if(armyOfwarriors[i] == &warrior){
                    wIndex = i;
                    break;
                }
            }
            for(size_t i = wIndex; i < armyOfwarriors.size() - 1; ++i){
                armyOfwarriors[i] = armyOfwarriors[i+1];
            }
            armyOfwarriors.pop_back();
            strength -= warrior.getStrength();
            warrior.setIsHired(false);
            return true;
        }
    }
    //is display const?
    void display() const {
        cout << this->name << "has an army of " << armyOfwarriors.size() << endl;
        //couldnt do const Warrior*&
        //not a const?
        //copy of pointer - ok because they both have address to object
        //can change obj  directly
        for(const Warrior* const warrior : armyOfwarriors){
            
            cout << "\t" << *warrior << endl;
        }
    }
    void setScoreLoser(Noble& noble){
        for(Warrior* const warrior : noble.getArmyOfwarriors()){
            //warrior->setStrength(0);
            warrior->setIsDead(true);
        }
        //noble.setStrength(0);
        noble.setIsDead(true);
    }
    void battle(Noble& noble){
        cout << this->name << " battles " << noble.getName() << endl;
        size_t enemyStrength = noble.getStrength();
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

            //are we allowed to use casting?
            float ratio = this->strength / enemyStrength;
            for(Warrior* const warrior : noble.getArmyOfwarriors()){
                //this has to be - (*warrior).getStrength()
                size_t curr_strength = warrior->getStrength();
                warrior->setStrength((size_t)curr_strength*(1-ratio));
            }

            noble.setStrength(noble.getStrength() * (1 - ratio));
            this->setStrength(0);
            this->isDead = true;
        }
        else if(this->strength == enemyStrength){
            cout << "Mutual Annihalation: " << this->name << " and "
            << noble.getName() << " die at each other's hands" << endl;

            for(Warrior* const warrior : noble.getArmyOfwarriors()){
                warrior->setStrength(0);
            }
            //cannot manipulate warrior object as const from its address.
            //const Warrior* warrior = *(armyOfwarriors[0]);

            for(Warrior* const warrior : armyOfwarriors){
                warrior->setStrength(0);
            }
            this->setStrength(0);
            noble.setStrength(0);
            this->isDead = true;
            noble.setIsDead(true);
        }
        else{
            cout << this->name << " defeats " << noble.getName() << endl;

            float ratio = (float) enemyStrength / this->strength;
            
            for(Warrior* const warrior : armyOfwarriors){
                size_t curr_strength = warrior->getStrength();
                //curr_strength * this->strength - curr_strength * enemyStrength) / this->strength
                warrior->setStrength((size_t)curr_strength*(1-ratio));
            }
            this->setStrength(this->getStrength() * (size_t)(1 - ratio));
            noble.setStrength(0);
            noble.setIsDead(true);
        }
    }
};

int main() {

	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

    // art.battle(lance);
    // cout << art.getStrength() << endl;
    // cout << lance.getStrength() << endl;
	// jim.battle(lance);
    // cout << jim.getStrength() << endl;
    // cout << lance.getStrength() << endl;
	// linus.battle(billie);
    // cout << linus.getStrength() << endl;
    // cout << billie.getStrength() << endl;
	// billie.battle(lance);
    // cout << lance.getStrength() << endl;
    // cout << billie.getStrength() << endl;


    //cout << 5/2 << endl;
    //a ref of type const Warrior*& cannot be intialized with value of ty[e Warrior *const
    // for(const Warrior*& const warrior : jim.getArmyOfwarriors()){
    //     cout << warrior->getName() << ", " << warrior-> getStrength() << endl;
    // }
    // cout << 5*3/2 << endl;
    // cout<< (int)((float)5/2*3) << endl;
    // cout << (1013 - 7)/13 << endl;
    // cout << (int)((10 - (float)7/13 *10)) << endl;
}
