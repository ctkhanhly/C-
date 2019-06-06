#include "Archer.h"
using namespace std;

namespace WarriorCraft{
    Archer::Archer(const string& name, int strength): Warrior(name, strength){}
    void Archer::wayOfDefending() const{
        if(Warrior::getIsDead()){
            return;
        }
        cout << "TWANG! " << Warrior::getName() << " says: Take that in the name of my lord, " ;
        cout << Warrior::getLordName() << endl;
    }
}
