/*
Ly Cao
DLEC
hw02: Game of Medieval Times
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Warrior{
    int strength;
    string name; 
};


size_t findWarriorByName(const string& name, const vector<Warrior>& warriors);
void addToWarriorVector(ifstream& ifs, vector<Warrior>& warriors);
void getStatus(const vector<Warrior>& warriors);
void battle(size_t w1, size_t w2, vector<Warrior>& warriors);

int main(){
    ifstream warriors_commands ("warriors.txt");
    //Exit if the file cannot be opened
    if(!warriors_commands){
        cerr << "Cannot find the file" << endl;
        exit(1);
    }
    vector<Warrior> warriors;
    string command;
    while(warriors_commands >> command){
        if(command == "Warrior"){
            addToWarriorVector(warriors_commands, warriors);
            cout<< warriors.size()<< warriors.back().name << warriors.back().strength << endl;
        }
        else if(command == "Status"){
            getStatus(warriors);
        }
        //battle
        else if(command == "Battle"){
            //get name of the first warrior
            string name1;
            warriors_commands >> name1;
            //get the warrior's index within a vector of warriors
            size_t w1 = findWarriorByName(name1, warriors);
            //get name of the second warrior
            string name2;
            warriors_commands >> name2;
            //get the warrior's index within a vector of warriors
            size_t w2 = findWarriorByName(name2, warriors);
            //start the battle
            battle(w1, w2, warriors);
        }
    }
    warriors_commands.close();
}

/*
This method takes a name of a warrior and the vector 
of all the warriors and return the index of the warrior
*/
size_t findWarriorByName(const string& name, const vector<Warrior>& warriors){
    for(size_t i = 0; i < warriors.size(); ++i){
        if(warriors[i].name == name){
            return i;
        }
    }
    size_t notInVector = warriors.size();
    return notInVector;
}

/*
This method takes in  the ifstream and a vector of all current warriors,
get the new Warrior's name and strength, 
and then add the Warrior into the vector.
*/
void addToWarriorVector(ifstream& ifs, vector<Warrior>& warriors){
    Warrior warrior;
    ifs >> warrior.name;
    ifs >> warrior.strength;
    warriors.push_back(warrior);
}

/*
This method takes in the vector of all current warriors
and print out each Warrior's name and strength
*/
void getStatus(const vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(const Warrior& warrior: warriors){
        cout << "Warrior: " + warrior.name + ", strength: "
        << warrior.strength << endl;
    }
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

void battle(size_t w1, size_t w2, vector<Warrior>& warriors){
    cout << warriors[w1].name + " battles " + warriors[w2].name << endl;
    if(warriors[w1].strength == 0 && warriors[w2].strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if(warriors[w1].strength == 0){
        cout << "He's dead, " + warriors[w2].name << endl;
    }
    else if(warriors[w2].strength == 0){
        cout << "He's dead, " + warriors[w1].name << endl;
    }
    else if(warriors[w1].strength > warriors[w2].strength){
        warriors[w1].strength = warriors[w1].strength - warriors[w2].strength;
        warriors[w2].strength = 0;
        cout << warriors[w1].name + " defeats " + warriors[w2].name << endl;
    }
    else if(warriors[w2].strength > warriors[w1].strength){
        warriors[w2].strength = warriors[w2].strength - warriors[w1].strength;
        warriors[w1].strength = 0;
        cout << warriors[w2].name + " defeats " + warriors[w1].name << endl;
    }
    else {
        warriors[w1].strength = 0;
        warriors[w2].strength = 0;
        cout << "Mutual Annihilation: ";
        cout << warriors[w1].name + " and " + warriors[w2].name 
        + " die at each other's hands"<< endl;
    }
}