#include "Lord.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft{
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
}