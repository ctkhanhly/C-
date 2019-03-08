#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Warrior{
    int strength;
    string name; 
};

//better ways than this 
size_t getWarriorByName(const string& name, const vector<Warrior>& warriors);

//const stream?
//there was a compiler problem when i used constant ifs
void addToWarriorVector(ifstream& ifs, vector<Warrior>& warriors){
    Warrior warrior;
    ifs >> warrior.name;
    ifs >> warrior.strength;
    warriors.push_back(warrior);
    // while(ifs >> warrior.name >> warrior.strength){
    //     warriors.push_back(warrior);
    // }
}
void getStatus(const vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(const Warrior& warrior: warriors){
        cout << "Warrior: " + warrior.name + ", strength: "
        << warrior.strength << endl;
    }
}

void battle(size_t w1, size_t w2, vector<Warrior>& warriors){
//void battle(string& name1, string& name2, vector<Warrior>& warriors){
    // Warrior warrior1;
    // Warrior warrior2;
    // for( Warrior& w : warriors){
    //     if(w.name == name1){
    //         warrior1 = w;
    //     }
    //     else if(w.name == name2){
    //          warrior2 = w;
    //     }
    // }
    //creating copies right here
    Warrior warrior1 = warriors[w1];
    Warrior warrior2 = warriors[w2];
    cout << warrior1.name + " battles " + warrior2.name << endl;
    if(warrior1.strength == 0){
        cout << "He's dead, " + warrior2.name << endl;
    }
    else if(warrior2.strength == 0){
        cout << "He's dead, " + warrior1.name << endl;
    }
    else if(warrior1.strength == 0 && warrior2.strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if(warrior1.strength > warrior2.strength){
        // warrior1.strength = warrior1.strength - warrior2.strength;
        // warrior2.strength = 0;
        warriors[w1].strength = warriors[w1].strength - warriors[w2].strength;
        warriors[w2].strength = 0;
        cout << warrior1.name + " defeats " + warrior2.name << endl;
    }
    else if(warrior2.strength > warrior1.strength){
        // warrior2.strength = warrior2.strength - warrior1.strength;
        // warrior1.strength = 0;
        warriors[w2].strength = warriors[w2].strength - warriors[w1].strength;
        warriors[w1].strength = 0;
        cout << warrior2.name + " defeats " + warrior1.name << endl;
    }
    else if(warrior1.strength == warrior2.strength){
        // warrior1.strength = 0;
        // warrior2.strength = 0;
        warriors[w1].strength = 0;
        warriors[w2].strength = 0;
        cout << warrior1.name + " and " + warrior2.name 
        + " die at each other's hands"<< endl;
    }
}

int main(){
    ifstream warriors_commands ("warriors.txt");
    if(!warriors_commands){
        cerr << "Cannot find the file" << endl;
        exit(1);
    }
    vector<Warrior> warriors;
    string command;
    while(warriors_commands >> command){
        //cout<< command << endl;
        if(command == "Warrior"){
            //cout<< "Warrior" << endl;
            addToWarriorVector(warriors_commands, warriors);
            //getline(warriors_commands, command);
            cout<< warriors.size()<< warriors.back().name << warriors.back().strength << endl;
            // warriors_commands >> command;
            // warriors_commands >> command;
            // cout <<command << "hey"<<endl;
        }
        else if(command == "Status"){
            getStatus(warriors);
            //getline(warriors_commands, command);
        }
        else{
            string name1;
            warriors_commands >> name1;
            //this won't let me access to the actual warrior
            size_t w1 = getWarriorByName(name1, warriors);
            string name2;
            warriors_commands >> name2;
            size_t w2 = getWarriorByName(name2, warriors);
            //battle(getWarriorByName(name1, warriors), getWarriorByName(name2, warriors));
            battle(w1, w2, warriors);
            //getline(warriors_commands, command);
        }
    }
}

//push_back(&warrior)

// game_of_medieval_times.cpp:19:1: warning: control may reach end of non-void
//       function [-Wreturn-type]
// }

size_t getWarriorByName(const string& name, const vector<Warrior>& warriors){
    //const: the strength could not change in battle method

    //outside it's not const anymore, no change nor const, warriors still non-const
    //for(const Warrior& w : warriors)

    for(size_t i = 0; i < warriors.size(); ++i){
        if(warriors[i].name == name){
            //this is not const
            return i;
        }
    }
    size_t notInVector = warriors.size();
    return notInVector;
}