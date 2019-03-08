/*
Name: Ly Cao
DLEC
Game of Medieval Times with Nobles and Warriors
*/

//no function longer than 40 lines
//no line longer than 8 words


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
    double strength;
    bool isHired;
    bool isDead;
public:
    Warrior(const string& name, double strength): name(name), strength(strength)
            , isHired(false){}
    
    //Getters and setters of each field as needed
    void setStrength(double strength){
        this->strength = strength;
    }
    void setIsHired(bool isHired){
        this->isHired = isHired;
    }
    void setIsDead(bool isDead){
        this->isDead = isDead;
    }
    double getStrength() const{
        return strength;
    }
    const string& getName() const{
        return name;
    }
    bool getIsHired() const {
        return isHired;
    }
};
    
class Noble{
private:
    string name;
    double strength;
    bool isDead;
    vector<Warrior*> armyOfWarriors;

public:
    Noble(const string& name): name(name), isDead(false), strength(0){};

    //Getters and setters of each field as needed
    void setIsDead(bool isDead){
        this->isDead = isDead;
    }
    void setStrength(double strength){
        this->strength = strength;
    }
    double getStrength() const{
        return strength;
    }
    const vector<Warrior*>& getArmyOfWarriors() const{
        return armyOfWarriors;
    }
    const string& getName() const {
        return name;
    }
    bool getIsDead() const {
        return isDead;
    }

    /*
    This method takes in a Warrior that 
    this Noble wants to hire and returns whether or not
    the Noble is eligible to hire the Warrior.
    */
    bool hire(Warrior& warrior){
        if(warrior.getIsHired() | this->isDead){
            return false;
        }
        else{
            armyOfWarriors.push_back(&warrior);
            strength += warrior.getStrength();
            warrior.setIsHired(true);
            return true;
        }
    }

    /*
    This method takes in a Warrior that 
    this Noble wants to fire and returns whether or not
    the Noble is eligible to fire the Warrior.
    */
    bool fire(Warrior& warrior){

        cout << warrior.getName() << ", you're fired! -- "
        << this->name << endl;

        //Dead Noble cannot fire any Warrior, so no Dead Warrior will be available to hire
        if(this->isDead){
            return false;
        }
        else{
            size_t wIndex;
            for(size_t i = 0; i < armyOfWarriors.size(); ++i){
                if(armyOfWarriors[i] == &warrior){
                    wIndex = i;
                    break;
                }
            }
            for(size_t i = wIndex; i < armyOfWarriors.size() - 1; ++i){
                armyOfWarriors[i] = armyOfWarriors[i+1];
            }

            armyOfWarriors.pop_back();
            strength -= warrior.getStrength();

            //Other Nobles can now hire this Warriors
            warrior.setIsHired(false);
            return true;
        }
    }


    /*
    This method displays the army of a Noble, the army size, a
    nd the strength and name of each Warrior
    */
    void display() const {
        cout << this->name << " has an army of " << armyOfWarriors.size() << endl;
        for(const Warrior* const warrior : armyOfWarriors){   
            cout << "\t" << *warrior << endl;
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
    cout << art.getStrength() << endl;
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

    // NEW OUTPUT CODE
    cout << "==========\n"
         << "Status after all battles, etc.\n";
    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();

}
