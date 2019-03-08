#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Warrior{
private:
    class Weapon{
    private:
        int strength;
        string weaponName;
    public:
        Weapon(string theWeaponName, int theStrength): weaponName(theWeaponName), strength(theStrength){};
        void changeWeaponStrength(int theStrength){
            strength = theStrength;
        }
        int getWeaponStrength()  const {
            return strength;
        }
        const string& getWeaponName() const {
            return weaponName;
        }
    };

    string name;
    Weapon weapon;
public:
    Warrior(string name, string weaponName, int strength): name(name), weapon(weaponName,strength){
    };
    const string& getWarriorName() const {
        return name;
    }
    void changeWeaponStrength(int strength){
        //cannot do weapon.strength here.
        weapon.changeWeaponStrength(strength);
    }
    int getWeaponStrength() const {
        return weapon.getWeaponStrength();
    }
    //const Weapon& weapon
    const string& getWeaponName() const {
        return weapon.getWeaponName();
    }
     //missed const here
    // void printWeapon() const {
    //     //weapon.operator<<(cout);
    //     operator<<(cout, weapon);
    // }
};
// ostream& operator<<(ostream& os, const Weapon& theWeapon){
//     os << theWeapon.weaponName << ' ' << theWeapon.strength;
//     return os;
// }
ostream& operator<<(ostream& os, const Warrior& theWarrior){
    os << "Warrior: " << theWarrior.getWarriorName() << ", weapon: "
        << theWarrior.getWeaponName() << ", " << theWarrior.getWeaponStrength() << endl;
    return os;
} 

//do i have to mark const for all fucntions even not within  class?
void displayStatus(const vector<Warrior>& warriors){
    cout << "There are " << warriors.size() << " warriors" << endl;
    for(const Warrior& warrior : warriors){
        //warrior is  of  type constant => can only use methods with types constant
        operator<<(cout, warrior);
        //cout << ", ";
        //warrior.printWeapon();
        cout << endl;
    }
}
size_t getWarriorByName(const string& name, const vector<Warrior>& warriors){
    for(size_t i = 0; i < warriors.size(); ++i){
        if(warriors[i].getWarriorName() == name){
            return i;
        }
    }
    return warriors.size();
}

void battle(const string& name1, const string& name2, vector<Warrior>& warriors){
    cout << name1 << " battles " << name2 << endl;
    size_t w1 =  getWarriorByName(name1, warriors);
    size_t w2 =  getWarriorByName(name2, warriors);

    if(warriors[w1].getWeaponStrength() == 0 && warriors[w2].getWeaponStrength() == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if(warriors[w1].getWeaponStrength() == 0){
        cout << "He's dead, " + warriors[w2].getWarriorName() << endl;
    }
    else if(warriors[w2].getWeaponStrength() == 0){
        cout << "He's dead, " + warriors[w1].getWarriorName() << endl;
    }
    else if(warriors[w1].getWeaponStrength() > warriors[w2].getWeaponStrength()){
        warriors[w1].changeWeaponStrength(warriors[w1].getWeaponStrength() - warriors[w2].getWeaponStrength());
        warriors[w2].changeWeaponStrength(0);
        cout << warriors[w1].getWarriorName() + " defeats " + warriors[w2].getWarriorName() << endl;
    }
    else if(warriors[w2].getWeaponStrength() > warriors[w1].getWeaponStrength()){
        warriors[w2].changeWeaponStrength(warriors[w2].getWeaponStrength() - warriors[w1].getWeaponStrength());
        warriors[w1].changeWeaponStrength(0);
        cout << warriors[w2].getWarriorName() + " defeats " + warriors[w1].getWarriorName() << endl;
    }
    else {
        warriors[w1].changeWeaponStrength(0);
        warriors[w2].changeWeaponStrength(0);
        cout << "Mutual Annihilation: ";
        cout << warriors[w1].getWarriorName() + " and " + warriors[w2].getWarriorName() 
        + " die at each other's hands"<< endl;
    }
}
int main(){
    ifstream warriorText("warrior.txt");
    string command, name, weaponName;
    int strength;
    vector<Warrior> warriors;
    while(warriorText >> command){
        if(command == "Warrior"){
            warriorText >> name;
            warriorText >> weaponName;
            warriorText >> strength;
            Warrior warrior(name, weaponName, strength);
            warriors.push_back(warrior);
        }
        else if(command == "Status"){
            displayStatus(warriors);
        }
        else if(command == "Battle"){
            string name1, name2;
            warriorText >> name1 >> name2;
            battle(name1, name2, warriors);
        }
    }
    //error: 'weapon' is a private member of 'Warrior'

    //cout<<  warriors[0].weapon.strength <<endl;
}