#include "Swordsman.h"
using namespace std;

namespace WarriorCraft{
    Swordsman::Swordsman(const string& name, int strength): Warrior(name, strength){}
    void Swordsman::wayOfDefending() const{
        if(Warrior::getIsDead()){
            return;
        }
        cout << "CLANG! " << Warrior::getName() << " says: Take that in the name of my lord, ";
        cout << Warrior::getLordName() << endl;
    }
}
