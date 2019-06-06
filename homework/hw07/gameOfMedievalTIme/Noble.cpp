#include "Noble.h"
using namespace std;

namespace WarriorCraft{
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
            noble.wayOfDefending();
            wayOfDefending();
            cout << noble.getName() << " defeats " << this->name << endl;
            noble.setStrengthWinner(*this);
            this->setStrengthLoser();
        }
        else if(this->strength == enemyStrength){
            noble.wayOfDefending();
            wayOfDefending();
            cout << "Mutual Annihalation: " << this->name << " and "
            << noble.getName() << " die at each other's hands" << endl;
            this->setStrengthLoser();
            noble.setStrengthLoser();
        }
        else{
            noble.wayOfDefending();
            wayOfDefending();
            cout << this->name << " defeats " << noble.getName() << endl;
            this->setStrengthWinner(noble);
            noble.setStrengthLoser();
        }
    }  
}