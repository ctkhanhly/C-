#include "Wizard.h"
using namespace std;

namespace WarriorCraft{
    Wizard::Wizard(const string& name, int strength): Protector(name, strength){}
    void Wizard::wayOfDefending() const{
        if(Protector::getIsDead()){
            return;
        }
        cout << "POOF! " << endl;
    }
}
