#include "PersonWithStrengthToFight.h"
using namespace std;

namespace WarriorCraft{
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
}