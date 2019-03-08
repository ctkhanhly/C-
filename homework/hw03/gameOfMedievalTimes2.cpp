/*
Ly Cao
Game of Medieval Times
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
    class Weapon{
        //overloading output operator to print out the weapon
        friend ostream& operator<<(ostream& os, const Weapon& weapon){
            os << "weapon: " <<  weapon.weaponName << ", "
            << weapon.strength;
            return os;
        }
    private:
        //Fields of weapon
        int strength;
        string weaponName;
    public:
        Weapon(string theWeaponName, int theStrength): weaponName(theWeaponName), strength(theStrength){};

        //setter method of field strength, takes in an int strength and change field strength to that value
        void changeWeaponStrength(int theStrength){
            strength = theStrength;
        }
        //getter method of field strength, return the int of strength
        int getWeaponStrength() const {
            return strength;
        }
        //getter method of field weaponName, return the string of weaponName.
        const string& getWeaponName() const {
            return weaponName;
        }
        
    };
    
    //Fields of Warrior
    string name;
    Weapon weapon;
public:
    Warrior(string name, string weaponName, int strength): name(name), weapon(weaponName,strength){
    };
    const string& getWarriorName() const {
        return name;
    }
    void changeWeaponStrength(int strength){
        weapon.changeWeaponStrength(strength);
    }
    int getWeaponStrength() const {
        return weapon.getWeaponStrength();
    }
    const string& getWeaponName() const {
        return weapon.getWeaponName();
    }
    const Weapon& getWeapon() const {
        return weapon;
    }
};

void displayStatus(const vector<Warrior>& warriors);
size_t getWarriorByName(const string& name, const vector<Warrior>& warriors);
void battle(const string& name1, const string& name2, vector<Warrior>& warriors);

int main(){
    ifstream warriorText("warrior.txt");
    //Exit if the file cannot be opened
    if(!warriorText){
        cerr << "Cannot find the file" << endl;
        exit(1);
    }
    string command, name, weaponName;
    int strength;
    vector<Warrior> warriors;

    //read in commands and the arguments necessary to implement those commands
    while(warriorText >> command){
        if(command == "Warrior"){
            //reads in name, weapon name, and strength of the warrior
            //and add warrior to the warriors vector
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
            //reads the names of the warriors and perform the battle method
            string name1, name2;
            warriorText >> name1 >> name2;
            battle(name1, name2, warriors);
        }
    }
     warriorText.close();
}

//overloading output operator to print out the Warrior
ostream& operator<<(ostream& os, const Warrior& theWarrior){
    os << "Warrior: " << theWarrior.getWarriorName() << ", " << theWarrior.weapon;
    return os;
}

/*
This method takes in the vector of all current warriors
and print out each Warrior's name and strength
*/
void displayStatus(const vector<Warrior>& warriors){
    cout << "There are " << warriors.size() << " warriors" << endl;
    for(const Warrior& warrior : warriors){
        operator<<(cout, warrior);
        cout << endl;
    }
}

/*
This method takes a name of a warrior and the vector 
of all the warriors and return the index of the warrior
*/
size_t getWarriorByName(const string& name, const vector<Warrior>& warriors){
    for(size_t i = 0; i < warriors.size(); ++i){
        if(warriors[i].getWarriorName() == name){
            return i;
        }
    }
    return warriors.size();
}

/*
This method starts the battle by taking the indexes of two warriors
and the vector of all warriors, and then change each warrior's strength
according to the following rules:
    If a warrior has less strength then he loses all his strength and 
the stronger warrior loses only the amount of strength equal to his opponent's
    If two warriors have the same strength, they both lose all strength
Then, this method prints out the result of the battle.
*/
void battle(const string& name1, const string& name2, vector<Warrior>& warriors){
    cout << name1 << " battles " << name2 << endl;
    size_t w1 =  getWarriorByName(name1, warriors);
    size_t w2 =  getWarriorByName(name2, warriors);
    if(w1>warriors.size() ){
        cout << "Warrior 1 is invalid" << endl;
        // break; // error breakstatement not in loop
        return;
    }
    if(w2 > warriors.size()){
        cout << "Warrior 2 is invalid" << endl;
        //break;
        return;
    }
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