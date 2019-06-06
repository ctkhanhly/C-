#include "Protector.h"
#include "Lord.h"
using namespace std;

namespace WarriorCraft{
    Protector::Protector(const string& name, double strength): name(name), strength(strength), 
        isHired(false), isDead(false), lord(nullptr){}
    void Protector::setIsHired(bool isHired){
        this->isHired = isHired;
    }
    bool Protector::getIsDead() const {
        return isDead;
    }
    void Protector::setIsDead(bool isDead){
        this->isDead = isDead;
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

}